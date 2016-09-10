int MovementReadCPU(
int AnimationID, char CharacterName[], char AnimationNameBuffer[], char* AnimationSpeed, char* FrameAmount, 
char* AnimationLoop, char* AnimationEnemyAccelerationX, char* AnimationEnemyAccelerationY, char* AnimationType, 
short* AnimationStrength, char* WhichSpecial, uint8* WhichMissSoundEffect, char* WhichSoundEffectFrame, 
uint8* WhichHitSoundEffect, uint8* AnimationAddOn)
{

file_t CPUMoveArchive;
char MVTFile[NormalFileDirSize];
uint32 MoveOffset;


sprintf(MVTFile, "/ram/%.8s.mvt", CharacterName);
CPUMoveArchive = fs_open(MVTFile, O_RDONLY);

MoveOffset = AnimationID*sizeof(NormalAttackStruct)+HeaderSizeHumanMVT;

fs_seek(CPUMoveArchive, MoveOffset+4, 0);
fs_read(CPUMoveArchive, AnimationNameBuffer, 8);

fs_read(CPUMoveArchive, FrameAmount, 1);
//printf("Frame Amount: %d\n", *FrameAmount);

fs_read(CPUMoveArchive, AnimationSpeed, 1);
//printf("Speed: %d\n", *AnimationSpeed);

fs_read(CPUMoveArchive, AnimationType, 1);
//printf("Type: %d\n", *AnimationType);

fs_read(CPUMoveArchive, AnimationLoop, 1);
//printf("Loop: %d\n", *AnimationLoop);

fs_read(CPUMoveArchive, AnimationEnemyAccelerationX, 1);
//printf("Frame Amount: %d\n", *FrameAmount);

fs_read(CPUMoveArchive, AnimationEnemyAccelerationY, 1);

fs_seek(CPUMoveArchive, MoveOffset+18, 0);
fs_read(CPUMoveArchive, AnimationStrength, 2);
//printf("Frame Amount: %d\n", *FrameAmount);

fs_seek(CPUMoveArchive, MoveOffset+24, 0);
fs_read(CPUMoveArchive, WhichMissSoundEffect, 1);
fs_read(CPUMoveArchive, WhichSoundEffectFrame, 1);
fs_read(CPUMoveArchive, WhichHitSoundEffect, 1);
fs_read(CPUMoveArchive, WhichSpecial, 1);

fs_read(CPUMoveArchive, AnimationAddOn, 1);

fs_close(CPUMoveArchive);
return(1);
}


int AttackSelectCPU(
char* AnimationID, char CharacterName[], int DrawCharX, int DrawCharY, int EnemyDrawX, int EnemyDrawY, 
int CharGroundLevel, int EnemyGroundLevel, int CharCrouchPosition, int EnemyCrouchPosition, char SpecialAllowed, 
char CharIsLeft, char EnemyIsLeft, int CharOffset, int EnemyOffset, int CharWidth, int EnemyWidth, 
int CharacterTextureSizeDrawn, int CharAnimationType, int EnemyAnimationType, int CharHitStatus, int EnemyHitStatus, 
int CharHealth, int EnemyHealth, int SpecialEffectStage[], 
int Ticks, uint8* Difficulty, short NeedsMoreCounters[][ComputerCounterAmount], int CurrentChar, int OtherChar
){

file_t CPUMoveArchive;

int Bluff;

char MVTFile[NormalFileDirSize];
long CurrentOffset;
long MoveOffset;
int MoveBorderOffset = 0;
char MoveBorderMin = 0;
char MoveBorderMax = 0;
int RandomNumber;
int CharLeftSide;
int EnemyLeftSide;
int AnimationRangeX = 0;
int AnimationRangeY = 0;
int CharDistanceX;
int RealCharDistanceX;
int CharDistanceY = DrawCharY - EnemyDrawY;
if(CharDistanceY < 0) CharDistanceY = -CharDistanceY;

if(CharIsLeft == 1) CharLeftSide = DrawCharX+CharOffset;
else CharLeftSide = DrawCharX+CharacterTextureSizeDrawn-CharWidth-CharOffset;
if(EnemyIsLeft == 1) EnemyLeftSide = EnemyDrawX+EnemyOffset;
else EnemyLeftSide = EnemyDrawX+CharacterTextureSizeDrawn-EnemyWidth-EnemyOffset;

if(EnemyLeftSide <= CharLeftSide){ 
CharDistanceX = CharLeftSide-(EnemyLeftSide+EnemyWidth);
RealCharDistanceX = DrawCharX+CharacterTextureSizeDrawn-(EnemyLeftSide+EnemyWidth);
}
else{ 
CharDistanceX = EnemyLeftSide-(CharLeftSide+CharWidth);
RealCharDistanceX = EnemyLeftSide-DrawCharX;
}

*AnimationID = -1;

if(EnemyHitStatus != 0) return(ComputerAttackSelectNoAttackFound);

srand(rtc_unix_secs());
RandomNumber = ((rand()%100));

if(RandomNumber > (*Difficulty) && Ticks < 10){
if(CharGroundLevel == 1){

if(CharCrouchPosition != 0) return(ComputerAttackSelectNoAttackFound);
else{
if(RandomNumber < (*Difficulty)/2) return(ComputerAttackSelectMoveBack);
else return(ComputerAttackSelectNoAttackFound);
}
}
else return(ComputerAttackSelectNoAttackFound);

}
else{
srand(rtc_unix_secs()+Ticks);
RandomNumber = ((rand()%1000));


if(EnemyAnimationType == NormalAttackAnimationIdentifier || EnemyAnimationType == CoolerAttackIdentifier || EnemyAnimationType == ComboAttackAnimationIdentifier){
if(CharCrouchPosition != 0){
if(EnemyGroundLevel == 0) return(ComputerAttackSelectStandUp);
else return(ComputerAttackSelectCrouchBlock);
}
else if(CharGroundLevel == 0) MoveBorderOffset = MoveBorderJumpAntiGroundOffset; // Lol, I dunno. Could be better.
else{
if(EnemyCrouchPosition != 0){
if(CharDistanceX < (CharacterTextureSizeDrawn/2)){

if((DrawCharX+CharacterTextureSizeDrawn > ScreenSizeX || DrawCharX < 0) && NeedsMoreCounters[CurrentChar][AirBeingHitCounter] < UpperCounterLimit) return(ComputerAttackSelectJumpForward);
else if(CharHealth > EnemyHealth) return(ComputerAttackSelectJumpBack);
else if(NeedsMoreCounters[CurrentChar][CrouchBeingHitCounter] < LowerCounterLimit) MoveBorderOffset = MoveBorderIdleAntiCrouchOffset;
else return(ComputerAttackSelectIntoCrouch);
}
else return(ComputerAttackSelectNoAttackFound);

}
else return(ComputerAttackSelectBlock);
}
}
else if(EnemyAnimationType == SpecialEffectAnimationIdentifier || SpecialEffectStage[OtherChar] != 0){
if(CharGroundLevel == 1){
if(CharCrouchPosition != 0) return(ComputerAttackSelectCrouchBlock);
else return(ComputerAttackSelectBlock);
}
}
else if(CharCrouchPosition != 0){
if(CharDistanceX > CharWidth) return(ComputerAttackSelectStandUp);
else if(NeedsMoreCounters[CurrentChar][CrouchBeingHitCounter] > UpperCounterLimit){
NeedsMoreCounters[CurrentChar][CrouchBeingHitCounter]--;
return(ComputerAttackSelectStandUp);
}
else if(EnemyGroundLevel == 1) MoveBorderOffset = MoveBorderCrouchAntiIdleOffset;
else MoveBorderOffset = MoveBorderCrouchAntiJumpOffset;
}
else if(CharGroundLevel == 0) MoveBorderOffset = MoveBorderJumpAntiGroundOffset;
else if(SpecialAllowed == 1 && RandomNumber <= 200){
if(CharDistanceX <= 5) MoveBorderOffset = MoveBorderThrowOffset;
else if(CharDistanceX <= 15){
if(RandomNumber > 100) MoveBorderOffset = MoveBorderCoolerOffset;
else MoveBorderOffset = MoveBorderUnidentifiedSpecialOffset;
}
else if(CharDistanceX > 15) MoveBorderOffset = MoveBorderSpecialEffectOffset;
}
else{
if(CharDistanceX > CharWidth) return(ComputerAttackSelectMoveForward);
else if(NeedsMoreCounters[CurrentChar][AirHitCounter] > UpperCounterLimit && NeedsMoreCounters[CurrentChar][AirBeingHitCounter] < UpperCounterLimit) return(ComputerAttackSelectJumpIdleUp);
else if((EnemyCrouchPosition != 0 || NeedsMoreCounters[CurrentChar][CrouchHitCounter] > UpperCounterLimit) && NeedsMoreCounters[CurrentChar][CrouchBeingHitCounter] < UpperCounterLimit) return(ComputerAttackSelectIntoCrouch);
else if(CharDistanceX < (CharWidth/2)) MoveBorderOffset = MoveBorderIdleInterceptorOffset;
else if(EnemyGroundLevel == 0){ 
if(NeedsMoreCounters[CurrentChar][GroundBeingHitCounter] > NeedsMoreCounters[CurrentChar][AirBeingHitCounter]) return(ComputerAttackSelectJumpIdleUp);
else MoveBorderOffset = MoveBorderIdleAntiJumpOffset;
}
else MoveBorderOffset = MoveBorderIdleStrongOffset; 
}
}


Bluff = sprintf(MVTFile, "/ram/%.8s.mvt", CharacterName);
CPUMoveArchive = fs_open(MVTFile, O_RDONLY);

do{
CurrentOffset = fs_seek(CPUMoveArchive, MoveBorderOffset, 0);
fs_read(CPUMoveArchive, &MoveBorderMin, 1);
fs_read(CPUMoveArchive, &MoveBorderMax, 1);

MoveBorderOffset = MoveBorderIdleStrongOffset;
} while(MoveBorderMax == 0);

if(MoveBorderMax > MoveBorderMin) MoveBorderMax = MoveBorderMin+(rand()%(MoveBorderMax-MoveBorderMin+1));
MoveOffset = MoveBorderMax*sizeof(NormalAttackStruct)+HeaderSizeHumanMVT;


CurrentOffset = fs_seek(CPUMoveArchive, MoveOffset+20, 0);
fs_read(CPUMoveArchive, &AnimationRangeX, 2);
fs_read(CPUMoveArchive, &AnimationRangeY, 2);

//if(AnimationRangeX >= RealCharDistanceX && AnimationRangeY >= CharDistanceY){ //Y U NO DO --- WHAT YOU SHOULD DO
if(AnimationRangeX >= RealCharDistanceX || CharGroundLevel == 0){
*AnimationID = 0;
CurrentOffset = fs_seek(CPUMoveArchive, MoveOffset+1, 0);
fs_read(CPUMoveArchive, AnimationID, 1);

fs_close(CPUMoveArchive);
return(ComputerAttackSelectAttackFound);
}
else{
*AnimationID = -1;
fs_close(CPUMoveArchive);
if(CharGroundLevel == 1 && CharCrouchPosition == 0) return(ComputerAttackSelectMoveForward);
else return(ComputerAttackSelectNoAttackFound);
}

fs_close(CPUMoveArchive);
return(ComputerAttackSelectSomethingMessedUp);

}