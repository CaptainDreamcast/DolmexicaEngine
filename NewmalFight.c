
#include "DrawNewWinningAnimation.c"
#include "FightMenu.c"
#include "FightFadeInEffect.c"
#include "FightFadingOut.c"
#include "FightJustNormalAnimation.c"
#include "FightWinningAnimation.c"
#include "NewWinQuoteStuff.c"
#include "FightWinQuote.c"
#include "FightContinueAnimation.c"

int NewmalFight(int WhichMode, char OriginalCharacterName[][NormalNameSize], char StageName[], char CharIsHuman[], int StartHealth[], int PlayerID[], char PointArray[][SurvivalModeBeatableEnemyArrayLength], uint8* Difficulty, char FirstTimerStartValue, char SecondTimerStartValue){

int Bluff;
int DirtyDeedsDoneDirtCheap;

CharacterTextureStruct CharacterTexture[MaxCharsOnScreen];
pvr_ptr_t SpecialEffectTexture[MaxCharsOnScreen];
pvr_ptr_t LifeBarTexture[MaxCharsOnScreen];
pvr_ptr_t VictoryTexture[MaxCharsOnScreen];

pvr_ptr_t HitEffectTextures[MaxHitEffectAmount][MaxHitEffectFrames];

pvr_ptr_t NewTimerTexture;

sfxhnd_t FightAnimationSoundEffect[SoundEffectIdentifierArraySize][MaxFightAnimationSoundEffect];
sfxhnd_t CharacterSFX[MaxCharsOnScreen][MaxSoundEffectsAllowed];

sfxhnd_t KnockDownSFX;

maple_device_t *cont;
cont_state_t *st;

TimerStruct TimerHeaderData;
FontSingleCharacterStruct TimerCharacterData[TimerCharacterAmount];
SingleLifeBarStruct LifeBarData[MaxCharsOnScreen];
OtherGuiStruct OtherGuiData[MaxCharsOnScreen];

UseHitEffectStruct HitEffects[MaxHitEffectAmount][MaxHitEffectFrames];

int FightStage;
int WhichRound;
char FightLoop;

uint8 CharsAreIdentical;
uint16 FightAnimationFlags;

int CharacterStretchFactor;
int CharacterTextureSizeDrawn;
int CharacterTextureSizeReal[MaxCharsOnScreen];

char CharWins[MaxCharsOnScreen];
int Winner;

char CharacterName[MaxCharsOnScreen][10];
//char CharIsHuman[MaxCharsOnScreen];

//CharIsHuman[CharacterOne] = CharIsHuman1;
//CharIsHuman[CharacterTwo] = CharIsHuman2;

int CurrentChar;
int OtherChar;

CurrentChar = CharacterOne;
do{

sprintf(CharacterName[CurrentChar], "%s", OriginalCharacterName[CurrentChar]);

CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);

CharsAreIdentical = 1;
for(Bluff = 0; Bluff < ActualNameSize; Bluff++){ 
if(OriginalCharacterName[CharacterOne][Bluff] != OriginalCharacterName[CharacterTwo][Bluff]) CharsAreIdentical = 0;
}

NowLoading();

int LeftStageBorder;
int StageGround;
    

char FirstTimerValue;
char SecondTimerValue;
int TimerTicks;
char TimerSpeed;



int WhichCharLost;
int WhichCharWon;
char SlowDownFactor;


int WhichEffectFrame[MaxCharsOnScreen];
int WhichEffect[MaxCharsOnScreen]; 
int EffectTicks[MaxCharsOnScreen];
uint8 HitEffectIsLeft[MaxCharsOnScreen];
int HitEffectFrameAmount[MaxHitEffectAmount];
uint8 HitEffectSpeed[MaxHitEffectAmount];
uint16 MediumHitEffectLimit;
uint16 StrongHitEffectLimit;
uint16 HitEffectAmount;


PaletteData CharPalette[MaxCharsOnScreen];


    int CharWidth[MaxCharsOnScreen]; //The *real* Character Width. Not to be confused with the overall width of the image file (128)
    int CharHeight[MaxCharsOnScreen];
    int CharOffset[MaxCharsOnScreen];
    int CharSpeed[MaxCharsOnScreen]; // Overall speed. Affects running and Jumping
    int AnimationTicks[MaxCharsOnScreen]; // Constantly running from 1 to 60. I think it's preferable to use ticks generated from the game code rather than from the timer inside the console.
    int DirectionalInputAllowed[MaxCharsOnScreen];
    int ButtonInputAllowed[MaxCharsOnScreen];
    char FrameAmount[MaxCharsOnScreen]; // The amount of frames an animation has. There's virtually no limit.
    char AnimationType[MaxCharsOnScreen]; // 1= Idle 3 = Attack 2 = Defense 0 = Invincible 4 = Taking a hit 5 = Throwing & Recovering (Double-assignment fail) 6 = ? 7 = Long-Range 8 = Combo 9 = Dizzy
    char AnimationLoop[MaxCharsOnScreen]; // Does the animation loop or not?
    char AnimationSpeed[MaxCharsOnScreen]; // How fast is the animation? Quick Jab or strong slow punch?
    short AnimationStrength[MaxCharsOnScreen]; // Strength of Attacks
    char AnimationEnemyAccelerationX[MaxCharsOnScreen];
    char AnimationEnemyAccelerationY[MaxCharsOnScreen];
    int AnimationID[MaxCharsOnScreen];
    char TemporaryAnimationID[MaxCharsOnScreen];
    int CharHitAcceleration[MaxCharsOnScreen];
    int PosCharX[MaxCharsOnScreen];
    int DrawCharX[MaxCharsOnScreen];
    int PosCharY[MaxCharsOnScreen];
    int GroundLevel[MaxCharsOnScreen]; // Is the character on the ground?
    int JumpStrength[MaxCharsOnScreen]; //How high can the character jump?
    int JumpDirection[MaxCharsOnScreen]; //Where does the char jump?
    int JumpVelocity[MaxCharsOnScreen]; //Just the Acceleration. -480 equals an idle position
    int JumpBlock[MaxCharsOnScreen]; //Decides wether the character is allowed to jump.
    int CrouchPosition[MaxCharsOnScreen]; // What Stage of Crouching. 0 = Nothing; 1 = Going into crouch; 2 = Crouch
    int CharHealth[MaxCharsOnScreen]; // Duh.
    int CharDefense[MaxCharsOnScreen]; // Amount substracted from enemy blows.
    char CharHitStatus[MaxCharsOnScreen]; // What kind of hit did the char receive? 3 = CollisionDetectPositive 4 = HIT(?) 5= Getting Up 6 = Getting Thrown 7 = SpecialEffectCollisionDetect
    int HitPositionX[MaxCharsOnScreen];
    int HitPositionY[MaxCharsOnScreen];
    char CharHitAnimationSpeed[MaxCharsOnScreen];
    int AnimationValidityCheck[MaxCharsOnScreen];
    char WhichSpecial[MaxCharsOnScreen];
    int SpecialAnimationFrame[MaxCharsOnScreen];
    char SpecialAnimationFrameAmount[MaxCharsOnScreen];
    int SpecialAnimationTicks[MaxCharsOnScreen];
    short SpecialAnimationDuration[MaxCharsOnScreen];
    short SpecialCharChangeX[MaxCharsOnScreen];
    short SpecialCharChangeY[MaxCharsOnScreen];
    char SpecialCharAlignment[MaxCharsOnScreen]; //Deals with both the Enemy Animation during Throws and the kind of throwback during Combos
    long SpecialOffset[MaxCharsOnScreen];
    char CharIsLeft[MaxCharsOnScreen];
    short ComboMovementX[MaxCharsOnScreen];
    short ComboMovementY[MaxCharsOnScreen];
    int SpecialEffect[MaxCharsOnScreen];
    short SpecialEffectPosX[MaxCharsOnScreen];
    short SpecialEffectPosY[MaxCharsOnScreen];
    int SpecialEffectDrawX[MaxCharsOnScreen];
    int SpecialEffectDrawY[MaxCharsOnScreen];
    short SpecialEffectSpeedX[MaxCharsOnScreen];
    short SpecialEffectSpeedY[MaxCharsOnScreen];
    short SpecialEffectSizeX[MaxCharsOnScreen];
    short SpecialEffectSizeY[MaxCharsOnScreen];
    short SpecialEffectRange[MaxCharsOnScreen]; //Gets substracted every pixel moved until it is zero.
    short SpecialEffectStrength[MaxCharsOnScreen];
    int SpecialEffectAccelerationX[MaxCharsOnScreen];
    int SpecialEffectAccelerationY[MaxCharsOnScreen];
    char SpecialEffectFrameAmount[MaxCharsOnScreen];
    char SpecialEffectWhichFrame[MaxCharsOnScreen];
    char SpecialEffectAnimationSpeed[MaxCharsOnScreen];
    uint8 SpecialEffectHitSoundEffect[MaxCharsOnScreen];
    int SpecialEffectStage[MaxCharsOnScreen]; //0 = Not yet thrown 1 = Before 2 = During(Loop) 3 = Vanish 4 = HIT
    char SpecialEffectNameBuffer[MaxCharsOnScreen][8];
    //char* SpecialEffectName[MaxCharsOnScreen] = SpecialEffectNameBuffer[MaxCharsOnScreen];
    char SpecialEffectPosCharRelativity;
    int SpecialEffectTicks[MaxCharsOnScreen];
    long SpecialEffectOffset[MaxCharsOnScreen];
    uint8 SpecialEffectSideEffect[MaxCharsOnScreen];
    short SpecialEffectSideEffectDuration[MaxCharsOnScreen];
    char JumpIdleUpFlags[MaxCharsOnScreen];
    char JumpForwardFlags[MaxCharsOnScreen];
    char JumpBackFlags[MaxCharsOnScreen];
    char JumpAnimationFlags[MaxCharsOnScreen];
    char WhichJumpStage[MaxCharsOnScreen];
    char WhichJumpFrame[MaxCharsOnScreen];
    char JumpFrameAmount[MaxCharsOnScreen];
    int JumpTicks[MaxCharsOnScreen];
    char JumpAnimationSpeed[MaxCharsOnScreen];
    //char CurrentJumpStage[MaxCharsOnScreen];
    char JumpNameBuffer[MaxCharsOnScreen][9];
    char JumpLoop[MaxCharsOnScreen];
    char JumpType[MaxCharsOnScreen]; // 0 = Up 1 = Forward // 2 = Back
    char ComboID[MaxCharsOnScreen];
    char ComboChecker[MaxCharsOnScreen];
    char DirectionalComboChecker[MaxCharsOnScreen];
    uint8 BackBlocking[MaxCharsOnScreen];
    uint16 JumpIdleUpStrength[MaxCharsOnScreen];
    uint16 JumpForwardStrength[MaxCharsOnScreen];
    uint16 JumpBackStrength[MaxCharsOnScreen];
    uint16 JumpForwardSpeed[MaxCharsOnScreen];
    uint16 JumpBackSpeed[MaxCharsOnScreen];

    uint8 WhichHitSoundEffect[MaxCharsOnScreen];
    uint8 WhichMissSoundEffect[MaxCharsOnScreen];
    char WhichSoundEffectFrame[MaxCharsOnScreen];
    char StartAnimationFlag[MaxCharsOnScreen];
    char KnockOutAnimationFlag[MaxCharsOnScreen];
    char VictoryAnimationFlag[MaxCharsOnScreen];
//    char DizzyAnimationFlag[MaxCharsOnScreen];
    int CurrentDizzy[MaxCharsOnScreen];
    int MaxDizzy[MaxCharsOnScreen];
    uint8 AnimationAddOn[MaxCharsOnScreen];
    uint8 DrawCharDifferently[MaxCharsOnScreen];

    short CharacterStatusAilment[MaxCharsOnScreen];
    short StatusAilmentDuration[MaxCharsOnScreen];

    short SpecialLeft[MaxCharsOnScreen];

    int ResetToStance[MaxCharsOnScreen]; // COULD THAT VALUE BE REPLACED? FEELS KINDA CHEAP. QUITE UNLIKE CAPSLOCK. CAPSLOCK FEELS EXPENSIVE.

    int WhichAIPattern[MaxCharsOnScreen];
    int TimeSlotLength[MaxCharsOnScreen];
    int TimeSlotTicks[MaxCharsOnScreen];
    short NeedsMoreCounters[MaxCharsOnScreen][ComputerCounterAmount];

    char WhichAnimationFrame[MaxCharsOnScreen];
    char AnimationBuffer[MaxCharsOnScreen][10];
    char RealCharName[MaxCharsOnScreen][20];

    int ShadowPositionX;
    int ShadowPositionY;

    #include "NewLoadCoolStage.c"
    CharacterTextureSizeDrawn = BasicCharacterTextureSizeDrawn*CharacterStretchFactor;

//??????????????????

Winner = -1;

FirstTimerValue = FirstTimerStartValue;
SecondTimerValue = SecondTimerStartValue;
TimerTicks = 1;
TimerSpeed = 60;

//??????????????????

    FightAnimationFlags = 0;
    LoadAllKindsOfAnimations(FightAnimationSoundEffect, &FightAnimationFlags);

    NewLoadEffects(HitEffects, HitEffectTextures, &HitEffectAmount, HitEffectFrameAmount, HitEffectSpeed, &MediumHitEffectLimit, &StrongHitEffectLimit, CharacterName);

    LoadPreFightSoundEffects(&KnockDownSFX);

    LoadCharacterSoundEffects(CharacterSFX, OriginalCharacterName);

    CurrentChar = CharacterOne;
    do{

    NewCharStatsLoad(CharacterName[CurrentChar], CharacterTextureSizeDrawn, &CharOffset[CurrentChar], &CharWidth[CurrentChar], &CharHeight[CurrentChar], &CharSpeed[CurrentChar], &JumpIdleUpStrength[CurrentChar], &CharDefense[CurrentChar], RealCharName[CurrentChar], &JumpIdleUpFlags[CurrentChar], &JumpForwardFlags[CurrentChar], &JumpBackFlags[CurrentChar], &BackBlocking[CurrentChar], &CharPalette[CurrentChar].PaletteInUse, &JumpForwardSpeed[CurrentChar], &JumpForwardStrength[CurrentChar], &JumpBackSpeed[CurrentChar], &JumpBackStrength[CurrentChar]);

    if(CharPalette[CurrentChar].PaletteInUse == 1){
    CharPalette[CurrentChar].WhichBufferPaletteUsed = CurrentChar; 
    CharacterTextureSizeReal[CurrentChar] = 256;

    for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<CharacterTextureBufferAmount; DirtyDeedsDoneDirtCheap++) CharacterTexture[CurrentChar].Texture[DirtyDeedsDoneDirtCheap] = pvr_mem_malloc(256*256);

    if(CurrentChar == CharacterTwo && CharsAreIdentical == 1){
    if(LoadPalette8(CharacterName[CurrentChar], 2, CharPalette[CurrentChar].WhichBufferPaletteUsed)){
    DrawCharDifferently[CurrentChar] = 0;
    }
    else {
    LoadPalette8(CharacterName[CurrentChar], 1, CharPalette[CurrentChar].WhichBufferPaletteUsed);
    DrawCharDifferently[CurrentChar] = 1;
    }   
    }
    else{
    CharPalette[CurrentChar].WhichCharPaletteUsed = 1;
    LoadPalette8(CharacterName[CurrentChar], CharPalette[CurrentChar].WhichCharPaletteUsed, CharPalette[CurrentChar].WhichBufferPaletteUsed);
    DrawCharDifferently[CurrentChar] = 0;
    }
    }

    else{
    CharacterTextureSizeReal[CurrentChar] = 128;
    for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<CharacterTextureBufferAmount; DirtyDeedsDoneDirtCheap++) CharacterTexture[CurrentChar].Texture[DirtyDeedsDoneDirtCheap] = pvr_mem_malloc(128*128*2);
    if(CurrentChar == CharacterTwo && CharsAreIdentical == 1) DrawCharDifferently[CurrentChar] = 1;
    else DrawCharDifferently[CurrentChar] = 0;
    }

    SpecialEffect[CurrentChar] = 0;

    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);


    LoadGraphicalUserInterface(WhichMode, LifeBarTexture, VictoryTexture, &NewTimerTexture, CharacterName, RealCharName, LifeBarData, &TimerHeaderData, TimerCharacterData, OtherGuiData, PointArray, CharIsHuman);


    CurrentChar = CharacterOne;
    do{

    LoadCharRegister(CharacterName[CurrentChar], CharIsHuman[CurrentChar], CharsAreIdentical, CurrentChar);

    if(CharIsHuman[CurrentChar] == 1) PrepareCharRegisterHuman(CharacterName[CurrentChar], CharacterTextureSizeDrawn, CharsAreIdentical, CurrentChar);
    else PrepareCharRegisterComputer(CharacterName[CurrentChar], CharacterTextureSizeDrawn, CharsAreIdentical, CurrentChar);
        
    LoadCharRomDisk(CharacterName[CurrentChar], CharsAreIdentical, CurrentChar);

    if(CharsAreIdentical) sprintf(CharacterName[CurrentChar], "%.7s%d", CharacterName[CurrentChar], CurrentChar);

    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);
    

    FightLoop = 1;
    FightStage = FightEntireReset;
    WhichRound = 1;
    WhichCharLost = -1;
    WhichCharWon = -1;
    OtherChar = CharacterTwo;
    SlowDownFactor = 4;
    StageGround = 431; //XXXXXXXXXXXXXXXX

    while(FightLoop){
    if(FightStage == FightEntireReset){
    #include "StarPlatinumResetTheWorld.c"
    }
    if(FightStage == FightPreRoundReset){
    #include "StartTheRound.c"
    }
    if(FightStage == FightFadeInEffect){
    FightStage = CoolFightFadeIn(FightStage, LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, CharacterName, CharacterTexture, AnimationBuffer, WhichAnimationFrame, DrawCharX, PosCharY, CharIsLeft, CharPalette, StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn, DrawCharDifferently);
    }
    while(FightStage == FightIntroAnimation){
    #include "FightIntroAnimation.c"
    }
    if(FightStage == FightRoundAnimation){
    FightJustNormalAnimation(FightStage, LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, CharacterName, CharacterTexture, AnimationBuffer, WhichAnimationFrame, DrawCharX, PosCharY, CharIsLeft, CharPalette, StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn, CharacterTextureSizeReal, WhichRound, FightAnimationSoundEffect, FightRoundAnimation, &Winner, FightAnimationFlags, DrawCharDifferently);
    if(Winner != StairWayToHeavenIdentifier) FightStage = FightFightAnimation;
    else FightStage = FightShutDown;
    }
    if(FightStage == FightFightAnimation){
    FightJustNormalAnimation(FightStage, LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, CharacterName, CharacterTexture, AnimationBuffer, WhichAnimationFrame, DrawCharX, PosCharY, CharIsLeft, CharPalette, StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn, CharacterTextureSizeReal, WhichRound, FightAnimationSoundEffect, FightFightAnimation, &Winner, FightAnimationFlags, DrawCharDifferently);
    if(Winner != StairWayToHeavenIdentifier) FightStage = FightActualFight;
    else FightStage = FightShutDown;
    }
    while(FightStage == FightActualFight){
    #include "FightActualFight.c"
    }
    if(FightStage == FightMenu){
    FightStage = FightMenuFunction(FightStage, LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, CharacterName, CharacterTexture, AnimationBuffer, WhichAnimationFrame, DrawCharX, PosCharY, CharIsLeft, CharHealth, SpecialLeft, RealCharName, PointArray, CharPalette, StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn, CharacterTextureSizeReal, FirstTimerValue, SecondTimerValue, NewTimerTexture, TimerHeaderData, TimerCharacterData, CharWins, LifeBarData, LifeBarTexture, VictoryTexture, OtherGuiData, CharIsHuman, &Winner, DrawCharDifferently, StageName);
    ButtonInputAllowed[CharacterOne] = 0;
    ButtonInputAllowed[CharacterTwo] = 0;
    }
    if(FightStage == FightTimeOut){
    #include "FightCheckingTimeOut.c"
    }
    if(FightStage == FightKnockOutEffect){
    #include "FightSuperCoolKnockOutEffect.c"
    }
    if(FightStage == FightPreKnockOutAnimation){
    #include "FightPreKnockOutAnimation.c"
    }
    if(FightStage == FightKnockOutAnimation){
    #include "FightKnockOutSlowMotion.c"
    }
    if(FightStage == FightVictoryPose){
    #include "FightVictoryPose.c"
    }
    if(FightStage == FightCheckingStuff){
    #include "FightCheckingStuff.c"
    }
    if(FightStage == FightNewRivalAnimation){
    FightJustNormalAnimation(FightStage, LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, CharacterName, CharacterTexture, AnimationBuffer, WhichAnimationFrame, DrawCharX, PosCharY, CharIsLeft, CharPalette, StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn, CharacterTextureSizeReal, WhichRound, FightAnimationSoundEffect, FightNewRivalAnimation, &Winner, FightAnimationFlags, DrawCharDifferently);
    FightStage = FightShutDown;
    }
    if(FightStage == FightPerfectAnimation){
    FightJustNormalAnimation(FightStage, LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, CharacterName, CharacterTexture, AnimationBuffer, WhichAnimationFrame, DrawCharX, PosCharY, CharIsLeft, CharPalette, StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn, CharacterTextureSizeReal, WhichRound, FightAnimationSoundEffect, FightPerfectAnimation, &Winner, FightAnimationFlags, DrawCharDifferently);
    if(Winner != StairWayToHeavenIdentifier) FightStage = FightLetsSeeWhatHappens;
    else FightStage = FightShutDown;
    }
    if(FightStage == FightLetsSeeWhatHappens){
    #include "FightLetsSeeWhatHappens.c"
    } 
    if(FightStage == FightWinningAnimation){
    FightStage = FightWinningAnimationFunction(FightStage, LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, CharacterName, CharacterTexture, AnimationBuffer, WhichAnimationFrame, DrawCharX, PosCharY, CharIsLeft, CharPalette, StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn, CharacterTextureSizeReal, CharIsHuman, WhichCharLost, &Winner, WhichMode, DrawCharDifferently);    
    } 
    if(FightStage == FightWinQuote){
    FightStage = FightWinQuoteFunction(FightStage, LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, CharacterName, CharacterTexture, AnimationBuffer, WhichAnimationFrame, DrawCharX, PosCharY, CharIsLeft, CharPalette, StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn, CharacterTextureSizeReal, &Winner, OriginalCharacterName[Winner], CharIsHuman, WhichMode, DrawCharDifferently);    
    } 
    if(FightStage == FightPreContinueAnimation){
    #include "FightPreContinueAnimation.c"
    } 
    if(FightStage == FightContinueAnimation){
    FightStage = FightContinueAnimationFunction(FightStage, LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, CharacterName, CharacterTexture, AnimationBuffer, WhichAnimationFrame, DrawCharX, PosCharY, CharIsLeft, CharPalette, StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn, CharacterTextureSizeReal, FightAnimationSoundEffect, WhichCharLost, TimerHeaderData, TimerCharacterData, NewTimerTexture, &Winner, PointArray, FightAnimationFlags, DrawCharDifferently);    
    }
    if(FightStage == FightSurvivalCalculateNextFight){

    FightFadingOut(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, CharacterName, CharacterTexture, AnimationBuffer, WhichAnimationFrame, DrawCharX, PosCharY, CharIsLeft, CharPalette, StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn, CharacterTextureSizeReal, DrawCharDifferently);
 
    DeLoadCharacterSoundEffects(CharacterSFX, OriginalCharacterName); 
    SurvivalCalculateNextFight(PlayerID, CharacterName, CharIsHuman, CharHealth, PointArray, CharsAreIdentical);

    

    CharsAreIdentical = 1;
    for(Bluff = 0; Bluff < ActualNameSize; Bluff++){ 
    if(CharacterName[CharacterOne][Bluff] != CharacterName[CharacterTwo][Bluff]) CharsAreIdentical = 0;
    }
    
    for(CurrentChar=0; CurrentChar<MaxCharsOnScreen; CurrentChar++){
    if(!CharIsHuman[CurrentChar]) sprintf(OriginalCharacterName[CurrentChar], "%.8s", CharacterName[CurrentChar]);
    }

    LoadCharacterSoundEffects(CharacterSFX, OriginalCharacterName);

    CurrentChar = CharacterOne;
    do{

    if(CharIsHuman[CurrentChar] == 0){

    

    NewCharStatsLoad(CharacterName[CurrentChar], CharacterTextureSizeDrawn, &CharOffset[CurrentChar], &CharWidth[CurrentChar], &CharHeight[CurrentChar], &CharSpeed[CurrentChar], &JumpIdleUpStrength[CurrentChar], &CharDefense[CurrentChar], RealCharName[CurrentChar], &JumpIdleUpFlags[CurrentChar], &JumpForwardFlags[CurrentChar], &JumpBackFlags[CurrentChar], &BackBlocking[CurrentChar], &CharPalette[CurrentChar].PaletteInUse, &JumpForwardSpeed[CurrentChar], &JumpForwardStrength[CurrentChar], &JumpBackSpeed[CurrentChar], &JumpBackStrength[CurrentChar]);

    if(CharPalette[CurrentChar].PaletteInUse == 1){
    CharPalette[CurrentChar].WhichBufferPaletteUsed = CurrentChar; 
    CharacterTextureSizeReal[CurrentChar] = 256;

    for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<CharacterTextureBufferAmount; DirtyDeedsDoneDirtCheap++){
    pvr_mem_free(CharacterTexture[CurrentChar].Texture[DirtyDeedsDoneDirtCheap]);
    CharacterTexture[CurrentChar].Texture[DirtyDeedsDoneDirtCheap] = pvr_mem_malloc(256*256);
    }

    if(CurrentChar == CharacterTwo && CharsAreIdentical == 1){
    if(LoadPalette8(CharacterName[CurrentChar], 2, CharPalette[CurrentChar].WhichBufferPaletteUsed)){
    DrawCharDifferently[CurrentChar] = 0;
    }
    else {
    LoadPalette8(CharacterName[CurrentChar], 1, CharPalette[CurrentChar].WhichBufferPaletteUsed);
    DrawCharDifferently[CurrentChar] = 1;
    }   
    }
    else{
    CharPalette[CurrentChar].WhichCharPaletteUsed = 1;
    LoadPalette8(CharacterName[CurrentChar], CharPalette[CurrentChar].WhichCharPaletteUsed, CharPalette[CurrentChar].WhichBufferPaletteUsed);
    DrawCharDifferently[CurrentChar] = 0;
    }
    }

    else{
    CharacterTextureSizeReal[CurrentChar] = 128;

    for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<CharacterTextureBufferAmount; DirtyDeedsDoneDirtCheap++){
    pvr_mem_free(CharacterTexture[CurrentChar].Texture[DirtyDeedsDoneDirtCheap]);
    CharacterTexture[CurrentChar].Texture[DirtyDeedsDoneDirtCheap] = pvr_mem_malloc(128*128*2);
    }

    if(CurrentChar == CharacterTwo && CharsAreIdentical == 1) DrawCharDifferently[CurrentChar] = 1;
    else DrawCharDifferently[CurrentChar] = 0;
    }


    LoadCharRegister(CharacterName[CurrentChar], CharIsHuman[CurrentChar], CharsAreIdentical, CurrentChar);
    PrepareCharRegisterComputer(CharacterName[CurrentChar], CharacterTextureSizeDrawn, CharsAreIdentical, CurrentChar);
    LoadCharRomDisk(CharacterName[CurrentChar], CharsAreIdentical, CurrentChar); 

    if(CharsAreIdentical) sprintf(CharacterName[CurrentChar], "%.7s%d", CharacterName[CurrentChar], CurrentChar);
    }

    StartHealth[CurrentChar] = CharHealth[CurrentChar];

    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);

    FightStage = FightEntireReset;
    }
    if(FightStage == FightShutDown){
    #include "FightShutDown.c"
    }

}   


return(Winner);

}