int MovementReadHuman(
int AnimationID, int GroundLevel, int CrouchPosition, char CharacterName[], char AnimationNameBuffer[], 
char* AnimationSpeed, char* FrameAmount, char* AnimationLoop, char* AnimationEnemyAccelerationX, 
char* AnimationEnemyAccelerationY, char* AnimationType, short* AnimationStrength, char* WhichSpecial, 
uint8* WhichMissSoundEffect, char* WhichSoundEffectFrame, uint8* WhichHitSoundEffect, uint8* AnimationAddOn, 
short* SpecialLeft){

file_t MoveArchive;

char MVTFile[NormalFileDirSize];

uint32 OffsetOffset;
uint32 MoveOffset;

int FirstValue;

uint16 SpecialNeeded;

uint8 AvailabilityCheck;

sprintf(MVTFile, "/ram/%.8s.mvt", CharacterName);
MoveArchive = FileOpen(MVTFile, O_RDONLY);

if(GroundLevel == 0) FirstValue = 1;
else if(CrouchPosition != 0) FirstValue = 2;
else FirstValue = 0;

FileSeek(MoveArchive, NormalAttackOffsetPositionHuman, 0);
FileRead(MoveArchive, &OffsetOffset, HeaderOffsetSize);

MoveOffset = (FirstValue*MoveAmount+AnimationID)*NormalAttackRegisterSize+OffsetOffset;


FileSeek(MoveArchive, MoveOffset+2, 0);
FileRead(MoveArchive, &AvailabilityCheck, 1);

FileSeek(MoveArchive, MoveOffset+30, 0);
FileRead(MoveArchive, &SpecialNeeded, 2);

if(AvailabilityCheck == 0 || CrouchPosition == 1 || *SpecialLeft < SpecialNeeded){
//printf("Move doesn't exist!\n");
FileClose(MoveArchive);
return(0);
}
else{
FileSeek(MoveArchive, MoveOffset+4, 0);
FileRead(MoveArchive, AnimationNameBuffer, 8);

FileRead(MoveArchive, FrameAmount, 1);
FileRead(MoveArchive, AnimationSpeed, 1);
FileRead(MoveArchive, AnimationType, 1);
FileRead(MoveArchive, AnimationLoop, 1); //16

FileRead(MoveArchive, AnimationEnemyAccelerationX, 1);
FileRead(MoveArchive, AnimationEnemyAccelerationY, 1);
FileRead(MoveArchive, AnimationStrength, 2);


FileSeek(MoveArchive, MoveOffset+24, 0);
FileRead(MoveArchive, WhichMissSoundEffect, 1);
FileRead(MoveArchive, WhichSoundEffectFrame, 1);
FileRead(MoveArchive, WhichHitSoundEffect, 1);
FileRead(MoveArchive, WhichSpecial, 1);

FileRead(MoveArchive, AnimationAddOn, 1);

FileClose(MoveArchive);
return(1);
}
printf("HUH?\n");
FileClose(MoveArchive);
return(-1);

}

int FirstSpecialReadHuman(
char CharacterName[], char AnimationNameBuffer[], char* FrameAmount, char* AnimationType, char WhichSpecial, 
long* SpecialOffset)
{
file_t MoveArchive;

char MVTFile[NormalFileDirSize];

uint32 MoveOffset;
uint32 OffsetOffset;

sprintf(MVTFile, "/ram/%.8s.mvt", CharacterName);

MoveArchive = FileOpen(MVTFile, O_RDONLY);

if(*AnimationType == 5){

FileSeek(MoveArchive, ThrowAttackOffsetPositionHuman, 0);
FileRead(MoveArchive, &OffsetOffset, HeaderOffsetSize);
//printf("Offset Offset: %ld.\n", MoveOffset);

MoveOffset = OffsetOffset+(WhichSpecial-1)*sizeof(ThrowHeaderStruct)+SpecialAttackHeaderSize;
//printf("Table Offset: %ld.\n", MoveOffset);

FileSeek(MoveArchive, MoveOffset+2, 0);
FileRead(MoveArchive, AnimationNameBuffer, 8); 
FileRead(MoveArchive, FrameAmount, 1);
//printf("Frame Amount: %d\n", *FrameAmount);

FileSeek(MoveArchive, MoveOffset+12, 0);
FileRead(MoveArchive, SpecialOffset, 4);
//printf("Read Offset: %ld.\n", *SpecialOffset);
}

if(*AnimationType == 6){

FileSeek(MoveArchive, CoolerAttackOffsetPositionHuman, 0);
FileRead(MoveArchive, &OffsetOffset, HeaderOffsetSize);
//printf("Offset Offset: %X.\n", OffsetOffset);

MoveOffset = OffsetOffset+(WhichSpecial-1)*sizeof(CoolerAttackHeaderStruct)+SpecialAttackHeaderSize;
//printf("Table Offset: %ld.\n", MoveOffset);

FileSeek(MoveArchive, MoveOffset+10, 0);
FileRead(MoveArchive, FrameAmount, 1);
//printf("Frame Amount: %d\n", *FrameAmount);

FileSeek(MoveArchive, MoveOffset+12, 0);
FileRead(MoveArchive, SpecialOffset, 4);
//printf("Read Offset: %X.\n", *SpecialOffset);
}

FileClose(MoveArchive);
return(1);

}

int FrameSpecialReadHuman(
char CharacterName[], long MoveOffset, char* AnimationSpeed, char* AnimationEnemyAccelerationX, 
char* AnimationEnemyAccelerationY, char AnimationType, short* AnimationStrength, short* CharPositionChangeX, 
short* CharPositionChangeY, short* EnemyPositionChangeX, short* EnemyPositionChangeY, char* EnemyAlignment, 
int* EnemyJumpVelocity, short* CharComboMovementX, short* CharComboMovementY)
{
file_t MoveArchive;

char MVTFile[NormalFileDirSize];
uint8 ThrowStage;
uint8 Minus;


sprintf(MVTFile, "/ram/%.8s.mvt", CharacterName);

MoveArchive = FileOpen(MVTFile, O_RDONLY);

//printf("Offset: %ld.\n", MoveOffset);
if(AnimationType == 5){
FileSeek(MoveArchive, MoveOffset+1, 0);
FileRead(MoveArchive, &ThrowStage, 1);
//printf("Current Stage: %d.", ThrowStage);

FileRead(MoveArchive, EnemyAlignment, 1);
//printf("Enemy Alignment: %d\n", *EnemyAlignment);

FileRead(MoveArchive, AnimationSpeed, 1);
//printf("Animation Speed: %d\n", *AnimationSpeed);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, CharPositionChangeX, 2);
if(Minus == 1){
*CharPositionChangeX = -*CharPositionChangeX;
}
//printf("CharPositionChange X-Axis: %d\n", *CharPositionChangeX);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, CharPositionChangeY, 2);
if(Minus == 1){
*CharPositionChangeY = -*CharPositionChangeY;
}
//printf("CharPositionChange Y-Axis: %d\n", *CharPositionChangeY);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, EnemyPositionChangeX, 2);
if(Minus == 1){
*EnemyPositionChangeX = -*EnemyPositionChangeX;
}
//printf("EnemyPositionChange X-Axis: %d\n", *EnemyPositionChangeX);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, EnemyPositionChangeY, 2);
if(Minus == 1){
*EnemyPositionChangeY = -*EnemyPositionChangeY;
}
//printf("EnemyPositionChange Y-Axis: %d\n", *EnemyPositionChangeY);



if(ThrowStage == 2){

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, AnimationEnemyAccelerationX, 1);

if(Minus == 1){
*AnimationEnemyAccelerationX = -*AnimationEnemyAccelerationX;
}
//printf("EnemyAcceleration Y-Axis: %d\n", *AnimationEnemyAccelerationX);

*AnimationEnemyAccelerationY = 0;
FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, AnimationEnemyAccelerationY, 1);

if(Minus == 1){
*AnimationEnemyAccelerationY = -*AnimationEnemyAccelerationY;
}



//printf("Current Velocity: %d\n", *EnemyJumpVelocity);

*AnimationStrength = 0;
FileRead(MoveArchive, AnimationStrength, 2);

}
//printf("Current Velocity: %d\n", *EnemyJumpVelocity);
//printf("Current Strength: %d\n", *AnimationStrength);
}

// -------------------------------------------------------------------------------------------------------------

if(AnimationType == 6){

FileSeek(MoveArchive, MoveOffset+2, 0);
FileRead(MoveArchive, EnemyAlignment, 1);
//printf("Enemy Alignment: %d\n", *EnemyAlignment);

FileRead(MoveArchive, AnimationSpeed, 1);
//printf("Animation Speed: %d\n", *AnimationSpeed);


FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, CharPositionChangeX, 2);
if(Minus == 1){
*CharPositionChangeX = -*CharPositionChangeX;
}
//printf("CharPositionChange X-Axis: %d\n", *CharPositionChangeX);


FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, CharPositionChangeY, 2);
if(Minus == 1){
*CharPositionChangeY = -*CharPositionChangeY;
}
//printf("CharPositionChange Y-Axis: %d\n", *CharPositionChangeY);

*CharComboMovementX = 0;
FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, CharComboMovementX, 2);
if(Minus == 1){
*CharComboMovementX = -*CharComboMovementX;
}
//printf("Char Movement X-Axis: %d\n", *CharComboMovementX);

*CharComboMovementY = 0;
FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, CharComboMovementY, 2);
if(Minus == 1){
*CharComboMovementY = -*CharComboMovementY;
}
//printf("Char Movement Y-Axis: %d\n", *CharComboMovementY);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, AnimationEnemyAccelerationX, 1);

if(Minus == 1){
*AnimationEnemyAccelerationX = -*AnimationEnemyAccelerationX;
}
//printf("EnemyAcceleration Y-Axis: %d\n", *AnimationEnemyAccelerationX);


*AnimationEnemyAccelerationY = 0;
FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, AnimationEnemyAccelerationY, 1);

if(Minus == 1){
*AnimationEnemyAccelerationY = -*AnimationEnemyAccelerationY;
}



//printf("Current Velocity: %d\n", *EnemyJumpVelocity);

*AnimationStrength = 0;
FileRead(MoveArchive, AnimationStrength, 2);

}
FileClose(MoveArchive);
return(1);

}

//---------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------

int FirstSpecialEffectReadHuman(
char CharacterName[], char WhichSpecial, long* SpecialOffset, short* SpecialEffectSizeX, short* SpecialEffectSizeY, 
short* SpecialEffectPosX, short* SpecialEffectPosY, char* SpecialEffectPosCharRelativity, char* SpecialEffectWhichFrame, 
short* SpecialEffectRange, short* SpecialEffectSpeedX, short* SpecialEffectSpeedY, uint8* SpecialEffectSideEffect, 
short* SpecialEffectSideEffectDuration, uint8* SpecialEffectHitSoundEffect
){

file_t MoveArchive;

char MVTFile[NormalFileDirSize];

uint32 MoveOffset;

uint32 OffsetOffset;
uint8 Minus;

sprintf(MVTFile, "/ram/%.8s.mvt", CharacterName);

MoveArchive = FileOpen(MVTFile, O_RDONLY);

FileSeek(MoveArchive, SpecialEffectOffsetPositionHuman, 0);
FileRead(MoveArchive, &OffsetOffset, HeaderOffsetSize);
//printf("Offset Offset: %ld.\n", OffsetOffset);

MoveOffset = OffsetOffset+(WhichSpecial-1)*sizeof(SpecialEffectHeaderStruct)+SpecialAttackHeaderSize;
//printf("Table Offset: %ld.\n", MoveOffset);

FileSeek(MoveArchive, MoveOffset+2, 0);
FileRead(MoveArchive, SpecialOffset, 4);
//printf("SpecialOffset: %ld\n", *SpecialOffset);

FileRead(MoveArchive, SpecialEffectSizeX, 2);
//printf("SpecialEffectSize X-Axis: %d\n", *SpecialEffectSizeX);

FileRead(MoveArchive, SpecialEffectSizeY, 2);
//printf("SpecialEffectSize Y-Axis: %d\n", *SpecialEffectSizeY);

FileRead(MoveArchive, SpecialEffectPosCharRelativity, 1);
//printf("SpecialEffectPosCharRelativity: %d\n", *SpecialEffectPosCharRelativity);

*SpecialEffectPosX = 0;
FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, SpecialEffectPosX, 2);

if(Minus == 1){
*SpecialEffectPosX = -*SpecialEffectPosX;
}
//printf("SpecialEffect Position X-Axis: %d\n", *SpecialEffectPosX);

*SpecialEffectPosY = 0;
FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, SpecialEffectPosY, 2);
if(Minus == 1){
*SpecialEffectPosY = -*SpecialEffectPosY;
}
//printf("SpecialEffectPosY: %d\n", *SpecialEffectPosY);

FileRead(MoveArchive, SpecialEffectWhichFrame, 1);
//printf("Which Frame: %d\n", *SpecialEffectWhichFrame);

FileRead(MoveArchive, SpecialEffectRange, 2);
//printf("SpecialEffectRange: %d\n", *SpecialEffectRange);

*SpecialEffectSpeedX = 0;
FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, SpecialEffectSpeedX, 2);
if(Minus == 1){
*SpecialEffectSpeedX = -*SpecialEffectSpeedX;
}
//printf("Speed X-Axis: %d\n", *SpecialEffectSpeedX);

*SpecialEffectSpeedY = 0;
FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, SpecialEffectSpeedY, 2);
if(Minus == 1){
*SpecialEffectSpeedY = -*SpecialEffectSpeedY;
}
//printf("Speed Y-Axis: %d\n", *SpecialEffectSpeedY);

*SpecialEffectSideEffect = 0;
FileRead(MoveArchive, SpecialEffectSideEffect, 1);
//printf("Side Effect: %d\n", *SpecialEffectSideEffect);

*SpecialEffectSideEffectDuration = 0;
FileRead(MoveArchive, SpecialEffectSideEffectDuration, 2);
//printf("Side Effect Duration: %d\n", *SpecialEffectSideEffectDuration);

FileRead(MoveArchive, SpecialEffectHitSoundEffect, 1); 

FileClose(MoveArchive);
return(1);
}

int SpecialEffectReadHuman(
char CharacterName[], char SpecialEffectNameBuffer[], int SpecialEffectOffset, char* SpecialEffectAnimationSpeed, 
char* SpecialEffectFrameAmount
){

file_t MoveArchive;

char MVTFile[NormalFileDirSize];

sprintf(MVTFile, "/ram/%.8s.mvt", CharacterName);

MoveArchive = FileOpen(MVTFile, O_RDONLY);

FileSeek(MoveArchive, SpecialEffectOffset+2, 0);
FileRead(MoveArchive, SpecialEffectNameBuffer, 8);
//printf("Name: %.8s\n", SpecialEffectNameBuffer);

FileRead(MoveArchive, SpecialEffectAnimationSpeed, 1);
//printf("Speed: %d\n", *SpecialEffectAnimationSpeed);

FileRead(MoveArchive, SpecialEffectFrameAmount, 1); 
//printf("FrameAmount: %d\n", *SpecialEffectFrameAmount);

FileClose(MoveArchive);
return(1);
}

//---------------------------------------------------------------------------------------------

int MovementReadCompulsory(
int AnimationID, char CharacterName[], char AnimationNameBuffer[], char* AnimationSpeed, char* FrameAmount, 
char* AnimationLoop, char* AnimationType
){

file_t MoveArchive;

char MVTFile[NormalFileDirSize];

uint32 MoveOffset;

sprintf(MVTFile, "/ram/%.8s.mvt", CharacterName);

MoveArchive = FileOpen(MVTFile, O_RDONLY);

MoveOffset = (AnimationID*NormalAttackRegisterSize)+HeaderSizeHumanMVT;

FileSeek(MoveArchive, MoveOffset+4, 0);
FileRead(MoveArchive, AnimationNameBuffer, 8);

FileRead(MoveArchive, FrameAmount, 1);
//printf("Frame Amount: %d\n", *FrameAmount);

FileRead(MoveArchive, AnimationSpeed, 1);

FileRead(MoveArchive, AnimationType, 1);

FileRead(MoveArchive, AnimationLoop, 1);

FileClose(MoveArchive);
return(1);
}

int JumpReadCompulsory(
int AnimationID, char CharacterName[], char AnimationNameBuffer[], char* AnimationSpeed, char* FrameAmount, 
char* AnimationLoop, char AnimationType
){

file_t MoveArchive;

char MVTFile[NormalFileDirSize];

uint32 MoveOffset;

char CompulsoryValue;

CompulsoryValue = CompulsoryJumpValue+((AnimationType)*JumpVariationAmount);

sprintf(MVTFile, "/ram/%.8s.mvt", CharacterName);
MoveArchive = FileOpen(MVTFile, O_RDONLY);

MoveOffset = ((AnimationID+CompulsoryValue)*NormalAttackRegisterSize)+HeaderSizeHumanMVT;


FileSeek(MoveArchive, MoveOffset+4, 0);
FileRead(MoveArchive, AnimationNameBuffer, 8);

FileRead(MoveArchive, FrameAmount, 1);
//printf("Frame Amount: %d\n", *FrameAmount);

FileRead(MoveArchive, AnimationSpeed, 1);

FileSeek(MoveArchive, MoveOffset+15, 0);
FileRead(MoveArchive, AnimationLoop, 1);

FileClose(MoveArchive);
return(1);
}

int ComboReadHuman(
int AnimationID, char CharacterName[], char AnimationNameBuffer[], char* AnimationSpeed, char* FrameAmount, 
char* AnimationLoop, char* AnimationEnemyAccelerationX, char* AnimationEnemyAccelerationY, char* AnimationType, 
short* AnimationStrength, char* WhichSpecial, char* ComboID, short* CharPositionChangeX, short* CharPositionChangeY, 
uint8* WhichMissSoundEffect, uint8* WhichHitSoundEffect, char* WhichSoundEffectFrame
){

file_t MoveArchive;

char MVTFile[NormalFileDirSize];

uint32 MoveOffset;
uint32 OffsetOffset;

uint8 Minus;

sprintf(MVTFile, "/ram/%.8s.mvt", CharacterName);
MoveArchive = FileOpen(MVTFile, O_RDONLY);


FileSeek(MoveArchive, ComboAttackOffsetPositionHuman, 0);
FileRead(MoveArchive, &OffsetOffset, HeaderOffsetSize);

MoveOffset = OffsetOffset+(*WhichSpecial-1)*sizeof(ComboAttackStruct)+SpecialAttackHeaderSize;

FileSeek(MoveArchive, MoveOffset+1, 0);
FileRead(MoveArchive, ComboID, 1);

FileSeek(MoveArchive, MoveOffset+4, 0);
FileRead(MoveArchive, AnimationNameBuffer, 8);

FileRead(MoveArchive, FrameAmount, 1);
//printf("Frame Amount: %d\n", *FrameAmount);

FileRead(MoveArchive, AnimationSpeed, 1);
FileRead(MoveArchive, AnimationType, 1);
FileRead(MoveArchive, AnimationLoop, 1);
FileRead(MoveArchive, AnimationEnemyAccelerationX, 1);
FileRead(MoveArchive, AnimationEnemyAccelerationY, 1);
FileRead(MoveArchive, AnimationStrength, 2);
FileRead(MoveArchive, WhichSpecial, 1);
FileRead(MoveArchive, &Minus, 1); // Buffer!

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, CharPositionChangeX, 2);
if(Minus == 1){
*CharPositionChangeX = -*CharPositionChangeX;
}
//printf("CharPositionChange X-Axis: %d\n", *CharPositionChangeX);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, CharPositionChangeY, 2);
if(Minus == 1){
*CharPositionChangeY = -*CharPositionChangeY;
}
//printf("CharPositionChange Y-Axis: %d\n", *CharPositionChangeY);

FileRead(MoveArchive, WhichMissSoundEffect, 1);
FileRead(MoveArchive, WhichSoundEffectFrame, 1);
FileRead(MoveArchive, WhichHitSoundEffect, 1);

FileClose(MoveArchive);
return(1);
}

int FirstOmniReadHuman(char CharacterName[], int WhichSpecial, long* SpecialOffset, char* OmniActionAmount){

file_t MoveArchive;


char MVTFile[NormalFileDirSize];

uint32 MoveOffset;
uint32 OffsetOffset;

sprintf(MVTFile, "/ram/%.8s.mvt", CharacterName);

MoveArchive = FileOpen(MVTFile, O_RDONLY);

FileSeek(MoveArchive, OmniAttackOffsetPositionHuman, 0);
FileRead(MoveArchive, &OffsetOffset, HeaderOffsetSize);
printf("Offset Offset: %ld.\n", OffsetOffset);

MoveOffset = OffsetOffset+(WhichSpecial-1)*sizeof(OmniHeaderStruct)+SpecialAttackHeaderSize;
printf("Table Offset: %ld.\n", MoveOffset);

FileSeek(MoveArchive, MoveOffset+2, 0);
FileRead(MoveArchive, OmniActionAmount, 1);
printf("OmniActionAmount: (%d)\n", *OmniActionAmount);

FileSeek(MoveArchive, MoveOffset+4, 0);
FileRead(MoveArchive, SpecialOffset, 4);
printf("SpecialOffset: %ld\n", *SpecialOffset);

FileClose(MoveArchive);
return(1);
}

int OmniAttackReadHuman // This function uses a load of parameters, should be rewritten to use structs!

(char CharacterName[], int SpecialOffset, int WhichAction, 
int LeftStageBorder, int* PosCharX, int* PosCharY, int* PosEnemyX, int* PosEnemyY, 
char* WhichAnimationFrame, char* WhichSpecialEffectFrame, int* CharacterAnimationTicks, int* SpecialEffectTicks, 
int* SpecialEffect, int* SpecialEffectStage, pvr_ptr_t SpecialEffectTexture, short* SpecialAnimationDuration, 
char* EnemyAlignment, char CharacterAnimationName[], char* CharacterFrameAmount, char* CharacterAnimationSpeed, 
char SpecialEffectAnimationName[], char* SpecialEffectAnimationSpeed, char* SpecialEffectFrameAmount, 
short* SpecialEffectSizeX, short* SpecialEffectSizeY, char* SpecialEffectPosCharRelativity, short* SpecialEffectPosX, 
short* SpecialEffectPosY, short* SpecialEffectRange, short* SpecialEffectSpeedX, short* SpecialEffectSpeedY, 
short* CharPositionChangeX, short* CharPositionChangeY, short* EnemyPositionChangeX, short* EnemyPositionChangeY, 
short* CharComboMovementX, short* CharComboMovementY, short* EnemyComboMovementX, short* EnemyComboMovementY, 
char* EnemyAccelerationX, char* EnemyAccelerationY, short* AnimationStrength, char CharIsLeft){

file_t MoveArchive;

char MVTFile[NormalFileDirSize];

//The Checking Variables
uint8 NewCharacterAnimation;
uint8 NewSpecialEffectAnimation;
uint8 Minus;
uint16 PositionCheckerX;
uint16 PositionCheckerY;

sprintf(MVTFile, "/ram/%.8s.mvt", CharacterName);

SpecialOffset += ((WhichAction-1)*sizeof(OmniAttackStruct));

MoveArchive = FileOpen(MVTFile, O_RDONLY);

FileSeek(MoveArchive, SpecialOffset+2, 0);
FileRead(MoveArchive, EnemyAlignment, 1);

FileRead(MoveArchive, &NewCharacterAnimation, 1);

if(NewCharacterAnimation == 1){

FileRead(MoveArchive, CharacterAnimationName, 8);

FileRead(MoveArchive, CharacterFrameAmount, 1);

FileRead(MoveArchive, CharacterAnimationSpeed, 1);

FileRead(MoveArchive, WhichAnimationFrame, 1);

*CharacterAnimationTicks = 1;
}

FileSeek(MoveArchive, SpecialOffset+15, 0);
FileRead(MoveArchive, &NewSpecialEffectAnimation, 1);

if(NewSpecialEffectAnimation == 1 || NewSpecialEffectAnimation == 2 || NewSpecialEffectAnimation == 3){

if(NewSpecialEffectAnimation == 1){ 
*SpecialEffect = 1;
SpecialEffectTexture = pvr_mem_malloc(2*2*2);
*SpecialEffectStage = SpecialEffectStageOutOfBounds;
*SpecialEffectTicks = 1;
}
else if(NewSpecialEffectAnimation == 2){
*SpecialEffectTicks = 1;
}


FileRead(MoveArchive, SpecialEffectAnimationName, 8);
FileRead(MoveArchive, SpecialEffectAnimationSpeed, 1);
FileRead(MoveArchive, SpecialEffectFrameAmount, 1);
FileRead(MoveArchive, &Minus, 1);
if(Minus != 0) *WhichSpecialEffectFrame = Minus;

FileRead(MoveArchive, SpecialEffectSizeX, 2);
FileRead(MoveArchive, SpecialEffectSizeY, 2);

FileRead(MoveArchive, SpecialEffectPosCharRelativity, 1);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, SpecialEffectPosX, 2);
if(*SpecialEffectPosCharRelativity == 1 && Minus == 1) *SpecialEffectPosX = -(*SpecialEffectPosX);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, SpecialEffectPosY, 2);
if(*SpecialEffectPosCharRelativity == 1 && Minus == 1) *SpecialEffectPosY = -(*SpecialEffectPosY);

FileRead(MoveArchive, SpecialEffectRange, 2);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, SpecialEffectSpeedX, 2);
if(Minus) *SpecialEffectSpeedX = -(*SpecialEffectSpeedX);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, SpecialEffectSpeedY, 2);
if(Minus) *SpecialEffectSpeedY = -(*SpecialEffectSpeedY);
}
else if(NewSpecialEffectAnimation == 0 && *SpecialEffect == 1){
*SpecialEffect = 0;
pvr_mem_free(SpecialEffectTexture);
*SpecialEffectStage = 0;
}

FileSeek(MoveArchive, SpecialOffset+46, 0);
FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, CharPositionChangeX, 2);
if(Minus) *CharPositionChangeX = -(*CharPositionChangeX);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, CharPositionChangeY, 2);
if(Minus) *CharPositionChangeX = -(*CharPositionChangeY);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, EnemyPositionChangeX, 2);
if(Minus) *EnemyPositionChangeX = -(*EnemyPositionChangeX);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, EnemyPositionChangeY, 2);
if(Minus) *EnemyPositionChangeY = -(*EnemyPositionChangeY);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, CharComboMovementX, 2);
if(Minus) *CharComboMovementX = -(*CharComboMovementX);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, CharComboMovementY, 2);
if(Minus) *CharComboMovementY = -(*CharComboMovementY);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, EnemyComboMovementX, 2);
if(Minus) *EnemyComboMovementX = -(*EnemyComboMovementX);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, EnemyComboMovementY, 2);
if(Minus) *EnemyComboMovementY = -(*EnemyComboMovementY);

FileRead(MoveArchive, &NewCharacterAnimation, 1);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, &PositionCheckerX, 2);
if(Minus) PositionCheckerX = -PositionCheckerX;

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, &PositionCheckerY, 2);
if(Minus) PositionCheckerX = -PositionCheckerY;

if(NewCharacterAnimation == 0) {*PosCharX = PositionCheckerX+LeftStageBorder; *PosCharY = PositionCheckerY;}
else if(NewCharacterAnimation == 1){
if(CharIsLeft) *PosCharX += PositionCheckerX;
else *PosCharX -= PositionCheckerX;
*PosCharY += PositionCheckerY;
}

FileRead(MoveArchive, &NewCharacterAnimation, 1);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, &PositionCheckerX, 2);
if(Minus) PositionCheckerX = -PositionCheckerX;

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, &PositionCheckerY, 2);
if(Minus) PositionCheckerX = -PositionCheckerY;

if(NewCharacterAnimation == 0) {*PosEnemyX = PositionCheckerX+LeftStageBorder; *PosEnemyY = PositionCheckerY;}
else if(NewCharacterAnimation == 1){
if(CharIsLeft) *PosEnemyX += PositionCheckerX; 
else *PosEnemyX -= PositionCheckerX; 
*PosEnemyY += PositionCheckerY;
}

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, EnemyAccelerationX, 1);
if(Minus) *EnemyAccelerationX = -(*EnemyAccelerationX);

FileRead(MoveArchive, &Minus, 1);
FileRead(MoveArchive, EnemyAccelerationY, 1);
if(Minus) *EnemyAccelerationY = -(*EnemyAccelerationY);

FileRead(MoveArchive, AnimationStrength, 2);

FileRead(MoveArchive, SpecialAnimationDuration, 2);

FileClose(MoveArchive);
return(1);
}