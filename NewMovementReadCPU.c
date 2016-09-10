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
CPUMoveArchive = FileOpen(MVTFile, O_RDONLY);

MoveOffset = AnimationID*sizeof(NormalAttackStruct)+HeaderSizeHumanMVT;

FileSeek(CPUMoveArchive, MoveOffset+4, 0);
FileRead(CPUMoveArchive, AnimationNameBuffer, 8);

FileRead(CPUMoveArchive, FrameAmount, 1);
//printf("Frame Amount: %d\n", *FrameAmount);

FileRead(CPUMoveArchive, AnimationSpeed, 1);
//printf("Speed: %d\n", *AnimationSpeed);

FileRead(CPUMoveArchive, AnimationType, 1);
//printf("Type: %d\n", *AnimationType);

FileRead(CPUMoveArchive, AnimationLoop, 1);
//printf("Loop: %d\n", *AnimationLoop);

FileRead(CPUMoveArchive, AnimationEnemyAccelerationX, 1);
//printf("Frame Amount: %d\n", *FrameAmount);

FileRead(CPUMoveArchive, AnimationEnemyAccelerationY, 1);

FileSeek(CPUMoveArchive, MoveOffset+18, 0);
FileRead(CPUMoveArchive, AnimationStrength, 2);
//printf("Frame Amount: %d\n", *FrameAmount);

FileSeek(CPUMoveArchive, MoveOffset+24, 0);
FileRead(CPUMoveArchive, WhichMissSoundEffect, 1);
FileRead(CPUMoveArchive, WhichSoundEffectFrame, 1);
FileRead(CPUMoveArchive, WhichHitSoundEffect, 1);
FileRead(CPUMoveArchive, WhichSpecial, 1);

FileRead(CPUMoveArchive, AnimationAddOn, 1);

FileClose(CPUMoveArchive);
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

char MVTFile[NormalFileDirSize];
long MoveOffset;
int MoveBorderOffset = 0;
char MoveBorderMin = 0;
char MoveBorderMax = 0;
uint32 RandomNumber;
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
RandomNumber = rand();

#ifndef LUA_VERSION_NONE
sprintf(MVTFile, "%d_Intelligence", CurrentChar);
lua_getglobal(LuaState, MVTFile);
if(!lua_isnil(LuaState, -1)){



lua_pushinteger(LuaState, EnemyHitStatus);
lua_pushinteger(LuaState, RandomNumber);
lua_pushinteger(LuaState, (*AnimationID));
lua_pushinteger(LuaState, Ticks);
lua_pushinteger(LuaState, CharGroundLevel);
lua_pushinteger(LuaState, EnemyGroundLevel);
lua_pushinteger(LuaState, CharCrouchPosition);
lua_pushinteger(LuaState, EnemyCrouchPosition);
lua_pushinteger(LuaState, *Difficulty);
lua_pushinteger(LuaState, CharHealth);
lua_pushinteger(LuaState, EnemyHealth);
lua_pushinteger(LuaState, CharacterTextureSizeDrawn);
lua_pushinteger(LuaState, DrawCharX);
lua_pushinteger(LuaState, EnemyDrawX);
lua_pushinteger(LuaState, CharDistanceX);
lua_pushinteger(LuaState, CharDistanceY);
lua_pushinteger(LuaState, EnemyAnimationType);
lua_pushinteger(LuaState, SpecialEffectStage[CurrentChar]);
lua_pushinteger(LuaState, SpecialEffectStage[OtherChar]);
lua_pushinteger(LuaState, CharWidth);
lua_pushinteger(LuaState, EnemyWidth);
lua_pushstring(LuaState, CharacterName);
lua_pushinteger(LuaState, RealCharDistanceX);

lua_createtable(LuaState, ComputerCounterAmount, 0);

#ifdef LUA_VERSION_502 

lua_pushinteger(LuaState, NeedsMoreCounters[CurrentChar][GroundHitCounter]);
lua_setfield(LuaState, -2, "GroundHitCounter");
lua_pushinteger(LuaState, NeedsMoreCounters[CurrentChar][CrouchHitCounter]);
lua_setfield(LuaState, -2, "CrouchHitCounter");
lua_pushinteger(LuaState, NeedsMoreCounters[CurrentChar][AirHitCounter]);
lua_setfield(LuaState, -2, "AirHitCounter");
lua_pushinteger(LuaState, NeedsMoreCounters[CurrentChar][GroundBeingHitCounter]);
lua_setfield(LuaState, -2, "GroundBeingHitCounter");
lua_pushinteger(LuaState, NeedsMoreCounters[CurrentChar][CrouchBeingHitCounter]);
lua_setfield(LuaState, -2, "CrouchBeingHitCounter");
lua_pushinteger(LuaState, NeedsMoreCounters[CurrentChar][AirBeingHitCounter]);
lua_setfield(LuaState, -2, "AirBeingHitCounter");

#else
lua_pushstring(LuaState, "GroundHitCounter");
lua_pushinteger(LuaState, NeedsMoreCounters[CurrentChar][GroundHitCounter]);
lua_settable (LuaState, -3);
lua_pushstring(LuaState, "CrouchHitCounter");
lua_pushinteger(LuaState, NeedsMoreCounters[CurrentChar][CrouchHitCounter]);
lua_settable (LuaState, -3);
lua_pushstring(LuaState, "AirHitCounter");
lua_pushinteger(LuaState, NeedsMoreCounters[CurrentChar][AirHitCounter]);
lua_settable (LuaState, -3);
lua_pushstring(LuaState, "GroundBeingHitCounter");
lua_pushinteger(LuaState, NeedsMoreCounters[CurrentChar][GroundBeingHitCounter]);
lua_settable (LuaState, -3);
lua_pushstring(LuaState, "CrouchBeingHitCounter");
lua_pushinteger(LuaState, NeedsMoreCounters[CurrentChar][CrouchBeingHitCounter]);
lua_settable (LuaState, -3);
lua_pushstring(LuaState, "AirBeingHitCounter");
lua_pushinteger(LuaState, NeedsMoreCounters[CurrentChar][AirBeingHitCounter]);
lua_settable (LuaState, -3);
#endif



if(lua_pcall(LuaState, 24, 3, 0) != LUA_OK){

if(lua_isstring(LuaState, -1)) printf("Error: (%s)\n", lua_tostring(LuaState, -1));
lua_settop(LuaState, 0);
return(ComputerAttackSelectNoAttackFound);
}



if(lua_isnumber(LuaState, -1)){ 
RandomNumber = lua_tointeger(LuaState, -1);
lua_pop(LuaState, 3);
return(RandomNumber);
}
else if(lua_isnumber(LuaState, -2)){
MoveBorderOffset = 0;
MoveBorderMin = lua_tointeger(LuaState, -3);
MoveBorderMax = lua_tointeger(LuaState, -2);
}
else if(lua_isnumber(LuaState, -3)){
MoveBorderOffset = lua_tointeger(LuaState, -3);
MoveBorderMin = 0;
MoveBorderMax = 0;
}
else{
lua_pop(LuaState, 3);
return(ComputerAttackSelectNoAttackFound);
}

lua_pop(LuaState, 3);

}
else{
lua_pop(LuaState, 1);

#endif

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

#ifndef LUA_VERSION_NONE
}
#endif

sprintf(MVTFile, "/ram/%.8s.mvt", CharacterName);
CPUMoveArchive = FileOpen(MVTFile, O_RDONLY);

do{
FileSeek(CPUMoveArchive, MoveBorderOffset, 0);
FileRead(CPUMoveArchive, &MoveBorderMin, 1);
FileRead(CPUMoveArchive, &MoveBorderMax, 1);

MoveBorderOffset = MoveBorderIdleStrongOffset;
} while(MoveBorderMax == 0);

if(MoveBorderMax > MoveBorderMin) MoveBorderMax = MoveBorderMin+(rand()%(MoveBorderMax-MoveBorderMin+1));
MoveOffset = MoveBorderMax*sizeof(NormalAttackStruct)+HeaderSizeHumanMVT;


FileSeek(CPUMoveArchive, MoveOffset+20, 0);
FileRead(CPUMoveArchive, &AnimationRangeX, 2);
FileRead(CPUMoveArchive, &AnimationRangeY, 2);

//if(AnimationRangeX >= RealCharDistanceX && AnimationRangeY >= CharDistanceY){ //Y U NO DO --- WHAT YOU SHOULD DO
if(AnimationRangeX >= RealCharDistanceX || CharGroundLevel == 0){
*AnimationID = 0;
FileSeek(CPUMoveArchive, MoveOffset+1, 0);
FileRead(CPUMoveArchive, AnimationID, 1);

FileClose(CPUMoveArchive);
return(ComputerAttackSelectAttackFound);
}
else{
*AnimationID = -1;
FileClose(CPUMoveArchive);
if(CharGroundLevel == 1 && CharCrouchPosition == 0) return(ComputerAttackSelectMoveForward);
else return(ComputerAttackSelectNoAttackFound);
}

FileClose(CPUMoveArchive);
return(ComputerAttackSelectSomethingMessedUp);


}