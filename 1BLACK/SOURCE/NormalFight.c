/*
Dolmexica engine ver. 0.00000000000000000000000000000000000000000000000000000000000000000001

One of the (very few) homebrew fighters. Since I tend to be a Capcom fan, this engine is supposed to play a lot like Street Fighter III with a few improvements.
Naturally, this is hardly visible yet, only a few things like Crouching, Jumping and Punching work right now and these still need some more fine-tuning.
Since the engine uses QuickLZ (the fastest compression archive), it'll have to be released under the GPL. Not much of a problem, it was gonna be
a GPL release anyway.
As of right now, I am also researching one possibility, which would be EPIC if it worked: Moddability.
Maybe you've heard of M.U.G.E.N. before and its huge success with modders around the globe. Porting M.U.G.E.N. is impossible, so the only possibility to
get modders interested in the DC is to make an engine which is optimized for our console. But enough of that, it's all nothing more than a concept right now.

This source code is not produced by or under license from Captain DC/Josh Tari. Use at your own risk ;P

*/




int NormalFight(char CharacterName1[], char CharacterName2[], char StageName[], char CharIsHuman1, char CharIsHuman2)
{


    sfxhnd_t KnockDownSFX;


    int GameLoop = 1; // as long as this is 1, the game runs.
    int i;

    int Bluff;
    int DirtyDeedsDoneDirtCheap;
    char REOSpeedwagon[40]; 

    char FightStage = -2;
    char WhichRound = 1;
    char CharLosses1 = 0;
    char CharLosses2 = 0;
    char Winner = 0;


    

    NowLoading();
    int LeftStageBorder = 0; //What part of the background has to be drawn
    int WhichCharLeft = 1; // If Character 1 is left == 1; if Character 2 is left == 2
    //CharacterRightTexture = pvr_mem_malloc(128*128*2);
    int StageGround = 175;
    


    char FirstTimerValue = 9;
    char SecondTimerValue = 9;
    int TimerTicks = 0;
    char TimerSpeed = 60;

    int BGMVolume = 15;
    int SoundEffectVolume = 255;

    char SuperCoolEffectTicks = 0;

    int FightAnimationSizeX = 0;
    int FightAnimationSizeY = 0;
    int FightAnimationTextureSizeX = 0;
    int FightAnimationTextureSizeY = 0;
    char EndFightAnimation = 0;
    char WhichFightAnimationVoiceClipName[9] = "00000000";
    char WhichFightAnimationFrame = 1;
    char FightAnimationVoiceClipChecker = 0;
    int FightAnimationScreenPositionX = 0;
    int FightAnimationScreenPositionY = 0;
    char FightAnimationSpeed = 60;
    char FightAnimationID = 0;
    int FightAnimationTicks = 1;
    
    int WinQuoteScreenPositionX = 100; 
    int WinQuoteScreenPositionY = 250; 
    int WinQuoteSizeX = 350; 
    int WinQuoteSizeY = 200; 
    int WinQuoteFontSize = 20;
    int WinQuoteLength = 0;
    int WinPoseDuration = 1000;

    int WinPortraitScreenPositionX = 450; 
    int WinPortraitScreenPositionY = 100; 
    int WinPortraitSizeX = 256; 
    int WinPortraitSizeY = 256; 
    int WinPortraitTextureSizeX = 256;
    int WinPortraitTextureSizeY = 256;

    char MenuArrowPosition = 1;
    char MenuSelectedOption = 0;
    int MenuScreenPositionX = 150;
    int MenuScreenPositionY = 125;
    int MenuSizeX = 380;
    int MenuSizeY = 200;
    char MenuColor = 4;
    char MenuFontColor = 1;
    int OptionPositionX = 200;
    int OptionPositionY = 140;
    int OptionSize = 20;
    //int MenuArrowSize = 30;
    int WhichMenu = 1;

    char WhichCharLost = 0;
    char SlowDownFactor = 4;


    int EffectFrameAmount1 = 0;
    int WhichEffectFrame1 = 0;
    int WhichEffect1 = 0; //1 = Weak, 2 = Middle, 3 = STRONG!! 0 = Nothing
    int EffectTicks1 = 0;

    int EffectFrameAmount2 = 0;
    int WhichEffectFrame2 = 0;
    int WhichEffect2 = 0; //1 = Weak, 2 = Middle, 3 = STRONG!! 0 = Nothing
    int EffectTicks2 = 0;

    PaletteData CharPalette1;
    CharPalette1.PaletteInUse = 0;

    if(CharPalette1.PaletteInUse == 1){
    CharPalette1.WhichCharPaletteUsed = 1;
    CharPalette1.WhichBufferPaletteUsed = 1; 
    LoadPalette8("RYU_SFIV", CharPalette1.WhichCharPaletteUsed, CharPalette1.WhichBufferPaletteUsed);
    Char1Texture = pvr_mem_malloc(256*256);
    }
    else{
    Char1Texture = pvr_mem_malloc(128*128*2);
    }

    //int WhichChar1 = 1;
    int CharWidth1 = 80; //The *real* Character Width. Not to be confused with the overall width of the image file (128)
    int CharHeight1 = 110;
    int CharOffset1 = 0;
    int CharSpeed1 = 3; // Overall speed. Affects running and Jumping
    int ReleaseButton1 = 0; // 0 = Idle condition. Live with it.
    int AnimationTicks1 = 1; // Constantly running from 1 to 60. I think it's preferable to use ticks generated from the game code rather than from the timer inside the console.
    int DirectionalInputAllowed1 = 1;
    int ButtonInputAllowed1 = 1;
    int FrameAmount1 = 0; // The amount of frames an animation has. There's virtually no limit.
    int AnimationType1 = 1; // 1= Idle 3 = Attack 2 = Defense 0 = Invincible 4 = Taking a hit 5 = Throwing 6 = ? 7 = Long-Range 8 = Combo 9 = Dizzy
    int AnimationLoop1 = 1; // Does the animation loop or not?
    int AnimationSpeed1 = 0; // How fast is the animation? Quick Jab or strong slow punch?
    int AnimationStrength1 = 0; // Strength of Attacks
    int AnimationEnemyAcceleration1 = 0;
    int AnimationID1 = 0;
    int TemporaryAnimationID1 = 0;
    int CharHitAcceleration1 = 0;
    int CharHitDuration1 = 0;
    int PosCharX1 = 200;
    int DrawCharX1 = 200;
    int PosCharY1 = StageGround;
    int GroundLevel1 = 1; // Is the character on the ground?
    int JumpStrength1 = 15; //How high can the character jump?
    int JumpDirection1 = 0; //Where does the char jump?
    int JumpVelocity1 = -480; //Just the Acceleration. -480 equals an idle position
    int JumpBlock1 = 0; //Decides wether the character is allowed to jump.
    int CrouchPosition1 = 0; // What Stage of Crouching. 0 = Nothing; 1 = Going into crouch; 2 = Crouch
    int CharHealth1 = 1000; // Duh.
    int CharDefense1 = 0; // Amount substracted from enemy blows.
    char CharHitStatus1 = 0; // What kind of hit did the char receive? 3 = CollisionDetectPositive 4 = HIT(?) 5= Getting Up 6 = Getting Thrown 7 = SpecialEffectCollisionDetect
    int HitPositionX1 = 0;
    int HitPositionY1 = 0;
    int CharHitAnimationSpeed1 = 1;
    int AnimationValidityCheck1 = 0;
    int WhichSpecial1 = 0;
    int SpecialAnimationFrame1 = 0;
    int SpecialCharChangeX1 = 0;
    int SpecialCharChangeY1 = 0;
    int SpecialCharAnimation1 = 0;
    int SpecialCharAlignment1 = 0; //Deals with both the Enemy Animation during Throws and the kind of throwback during Combos
    long SpecialOffset1 = 0;
    char CharIsLeft1 = 1;
    int ComboMovementX1 = 0;
    int ComboMovementY1 = 0;
    int SpecialEffect1 = 0;
    int SpecialEffectPosX1 = 0;
    int SpecialEffectPosY1 = 0;
    int SpecialEffectDrawX1 = 0;
    int SpecialEffectDrawY1 = 0;
    int SpecialEffectSpeedX1 = 0;
    int SpecialEffectSpeedY1 = 0;
    int SpecialEffectSizeX1 = 0;
    int SpecialEffectSizeY1 = 0;
    int SpecialEffectRange1 = 0; //Gets substracted every pixel moved until it is zero.
    int SpecialEffectStrength1 = 0;
    int SpecialEffectAcceleration1 = 0;
    int SpecialEffectFrameAmount1 = 0;
    int SpecialEffectWhichFrame1 = 0;
    int SpecialEffectAnimationSpeed1 = 0;
    int SpecialEffectStage1 = 0; //0 = Not yet thrown 1 = Before 2 = During(Loop) 3 = Vanish 4 = HIT
    char SpecialEffectNameBuffer1[8] = "NULLVOID";
    //char* SpecialEffectName1 = SpecialEffectNameBuffer1;
    int SpecialEffectPosCharRelativity = 0;
    int SpecialEffectTextureSizeX1 = 0;
    int SpecialEffectTextureSizeY1 = 0;
    int SpecialEffectTicks1 = 0;
    long SpecialEffectOffset1 = 0;
    char JumpIdleUpFlags1 = 0x9C;
    char JumpForwardFlags1 = 0x9C;
    char JumpBackFlags1 = 0x9C;
    char JumpAnimationFlags1 = 0;
    char WhichJumpStage1 = 0;
    char WhichJumpFrame1 = 0;
    char JumpFrameAmount1 = 0;
    int JumpTicks1 = 1;
    char JumpAnimationSpeed1 = 0;
    char CurrentJumpStage1 = 0;
    char JumpNameBuffer1[9] = "JUMPING1";
    char JumpLoop1 = 0;
    char JumpType1 = 0; // 0 = Up 1 = Forward // 2 = Back
    char ComboID1 = 0;
    char ComboChecker1 = 0;
    char DirectionalComboChecker1 = 0;
    char PointArray1[9] = "00000";
    char WhichHitSoundEffect1 = 0;
    char WhichMissSoundEffect1 = 0;
    char WhichSoundEffectFrame1 = 0;
    char StartAnimationFlag1 = 0;
    char KnockOutAnimationFlag1 = 0;
    char VictoryAnimationFlag1 = 1;
//    char DizzyAnimationFlag1 = 0;
    int CurrentDizzy1 = 0;
    int MaxDizzy1 = 100;

    int WhichAIPattern1 = 0;
    int TimeSlotLength1 = 1;
    int TimeSlotTicks1 = 1;
    int RandomAINumber1 = 0;
    int JumpLength1;

    
    
 
    int WhichAnimationFrame1 = 1;
    char AnimationBuffer1[8]; // In the demo, every Animation name MUST be eight characters long. (Despite the fact this buffer can hold nine characters xD)
    char* AnimationName1 = AnimationBuffer1; // Kind of unstable. This part of the code needs to be rewritten.
    //char CharacterNameBuffer1[9]; // In this demo, every Character name must be eight characters long.
    //CharacterName1 = CharacterNameBuffer1; // Needs to be redone.
    //CharacterName1 = "SAGATKMG"; // Sagat is the test character. For more info on the KMG format check the additional PKG.txt in the game files
    //AnimationName1 = "EMPTY000"; // Empty000 doesn't exist. You could write anything here, right now it doesn't matter.
    char RealCharName1[17] = "SAGAT";


    CharStatsLoad(CharacterName1, &CharOffset1, &CharWidth1, &CharHeight1, &CharSpeed1, &JumpStrength1, &CharDefense1, RealCharName1, &JumpIdleUpFlags1, &JumpForwardFlags1, &JumpBackFlags1);

    JumpLength1 = (JumpStrength1*2-4)*CharSpeed1;

    LoadCharRomDisk(CharacterName1, CharIsHuman1);
    AnimationID1 = -1;
    MovementReadCompulsory(0, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    //AnimationName1 = "STANDING";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;


    PaletteData CharPalette2;
    CharPalette2.PaletteInUse = 0;

    if(CharPalette2.PaletteInUse == 1){
    CharPalette2.WhichCharPaletteUsed = 1;
    CharPalette2.WhichBufferPaletteUsed = 1; 
    LoadPalette8("RYU_SFIV", CharPalette2.WhichCharPaletteUsed, CharPalette2.WhichBufferPaletteUsed);
    Char2Texture = pvr_mem_malloc(256*256);
    }
    else{
    Char2Texture = pvr_mem_malloc(128*128*2);
    }

	//Same as above
    //int WhichChar2 = 2;
    int CharWidth2 = 40;
    int CharHeight2 = 100;
    int CharOffset2 = 0;
    int CharSpeed2 = 2;
    int AnimationTicks2 = 1;
    int InputAllowed2 = 1;
    int FrameAmount2 = 3;
    int AnimationLoop2 = 1;
    int AnimationSpeed2 = 3;
    int PosCharX2 = 500;
    int DrawCharX2 = 0;
    int PosCharY2 = StageGround;
    int CharHealth2 = 1000;
    int CharDefense2 = 50;
    char CharHitStatus2 = 0;
    int CharHitAcceleration2 = 0;
    int CharHitDuration2 = 0;
    int HitPositionX2 = 0;
    int HitPositionY2 = 0;
    int CharHitAnimationSpeed2 = 1;
    int AnimationID2 = 0;
    int GroundLevel2 = 1;
    int CrouchPosition2 = 0;
    int AnimationEnemyAcceleration2 = 0;
    int AnimationType2 = 1;
    int AnimationStrength2 = 0;
    int AnimationChange2 = 0;
    int TemporaryAnimationID2 = 0;
    int AnimationValidityCheck2 = 0;
    int WhichSpecial2 = 0;
    int SpecialAnimationFrame2 = 0;
    int SpecialCharChangeX2 = 0;
    int SpecialCharChangeY2 = 0;
    int SpecialCharAnimation2 = 0;
    int SpecialCharAlignment2 = 0;
    long SpecialOffset2 = 0;
    int JumpStrength2 = 15; //How high can the character jump?
    int JumpDirection2 = 0; //Where does the char jump?
    int JumpVelocity2 = -480; //Just the Acceleration. -480 equals an idle position
    int JumpBlock2 = 0; //Decides wether the character is allowed to jump.
    char CharIsLeft2 = 0;
    int ComboMovementX2 = 0;
    int ComboMovementY2 = 0;
    char JumpIdleUpFlags2 = 0;
    char JumpForwardFlags2 = 0;
    char JumpBackFlags2 = 0;
    char JumpAnimationFlags2 = 0;
    char WhichJumpStage2 = 0;
    char WhichJumpFrame2 = 0;
    char JumpFrameAmount2 = 0;
    int JumpTicks2 = 1;
    char JumpAnimationSpeed2 = 0;
    char JumpNameBuffer2[9] = "JUMPING1";
    char JumpLoop2 = 0;
    char JumpType2 = 0;
    char DirectionalInputAllowed2 = 1;
    char PointArray2[9] = "00000";
    char StartAnimationFlag2 = 0;
    char KnockOutAnimationFlag2 = 0;
    char VictoryAnimationFlag2 = 1;
    //char DizzyAnimationFlag2 = 0;
    int CurrentDizzy2 = 0;
    int MaxDizzy2 = 100;
    int ButtonInputAllowed2 = 1;
    char DirectionalComboChecker2 = 0;
    char WhichHitSoundEffect2 = 0;
    char WhichMissSoundEffect2 = 0;
    char WhichSoundEffectFrame2 = 0;
    char ComboID2 = 0;
    char ComboChecker2 = 0;
    int JumpLength2;
    int SpecialEffect2 = 0;
    int SpecialEffectPosX2 = 0;
    int SpecialEffectPosY2 = 0;
    int SpecialEffectDrawX2 = 0;
    int SpecialEffectDrawY2 = 0;
    int SpecialEffectSpeedX2 = 0;
    int SpecialEffectSpeedY2 = 0;
    int SpecialEffectSizeX2 = 0;
    int SpecialEffectSizeY2 = 0;
    int SpecialEffectRange2 = 0; //Gets substracted every pixel moved until it is zero.
    int SpecialEffectStrength2 = 0;
    int SpecialEffectAcceleration2 = 0;
    int SpecialEffectFrameAmount2 = 0;
    int SpecialEffectWhichFrame2 = 0;
    int SpecialEffectAnimationSpeed2 = 0;
    int SpecialEffectStage2 = 0; //0 = Not yet thrown 1 = Before 2 = During(Loop) 3 = Vanish 4 = HIT
    char SpecialEffectNameBuffer2[8] = "NULLVOID";
    int SpecialEffectTextureSizeX2 = 0;
    int SpecialEffectTextureSizeY2 = 0;
    int SpecialEffectTicks2 = 0;
    long SpecialEffectOffset2 = 0;


    int WhichAIPattern2 = 0;
    int TimeSlotLength2 = 1;
    int TimeSlotTicks2 = 1;
    int RandomAINumber2 = 0;

    int WhichAnimationFrame2 = 1;
    char AnimationBuffer2[8];
    //char* AnimationName2 = AnimationBuffer2;
    char* AnimationName2;
    //char CharacterNameBuffer2[9]; 
    //for(i=0; i<8; i++) CharacterNameBuffer2[i] = CharacterName2[i];
    //CharacterName2 = CharacterNameBuffer2;
    //CharacterName2 = "JOHNCAGE"; // MORTAAAAL KOMBAAAT!!!!
    AnimationName2 = "STANDING";
    char RealCharName2[17] = "JOHNNY CAGE";

    CharStatsLoad(CharacterName2, &CharOffset2, &CharWidth2, &CharHeight2, &CharSpeed2, &JumpStrength2, &CharDefense2, RealCharName2, &JumpIdleUpFlags2, &JumpForwardFlags2, &JumpBackFlags2);

    JumpLength2 = (JumpStrength2*2-4)*CharSpeed2;

    LoadCharRomDisk(CharacterName2, CharIsHuman2);
    AnimationID2 = -1;
    MovementReadCompulsory(0, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "STANDING";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;

    int ShadowPositionX = 0;
    int ShadowPositionY = 30;
    #include "LoadCoolStage.c"

    LoadPreFightSoundEffects(&KnockDownSFX);
    //LoadStage(1);
    LoadAllKindsOfAnimations();
    LoadRoundAnimation();
    LoadFightAnimation();
    LoadPerfectAnimation();
    LoadContinueAnimation();
    LoadEffects();
    //LoadShadow();

    //Char1Texture = pvr_mem_malloc(128*128*2); // Allocate Video RAM to store the 128X128 texture of the animation that's drawn to the screen.

    //Char2Texture = pvr_mem_malloc(128*128*2);

    cdfs_test(); // Prints content of the RAMDISK. For Debugging.


    //Debugging and other nonsensical variables
    //int AITestValue = 0;
    char DebuggingMode = 0;
    int DebuggingAnimationSpeed = 32;
    int DebuggingAnimationStrength = 1;
    char DebugButtonInputAllowed = 1;
    char DebuggingSelection = 1;

    //Controller Thingies
    maple_device_t *cont;
    cont_state_t *st;

    //snd_init();    

    //DoneLoading();


    //cdrom_cdda_play(4, 5, 4, CDDA_TRACKS);
    
    while(GameLoop == 1)
    {

    if(FightStage == -2){

    FightStage = -1;
    WhichRound = 1;
    CharLosses1 = 0;
    CharLosses2 = 0;
    Winner = 0;
    for(i = 0; i < 4; i++) PointArray1[i] = '0';
    PointArray1[5] = '\0';
    for(i = 0; i < 4; i++) PointArray2[i] = '0';
    PointArray2[5] = '\0';
    }

    if(FightStage == -1){
    if(MusicWorks == 1) cdrom_cdda_play(FightTrack, FightTrack, 16, CDDA_TRACKS);
    LeftStageBorder = 0;
    WhichCharLeft = 1; // If Character 1 is left == 1; if Character 2 is left == 2

    FirstTimerValue = 9;
    SecondTimerValue = 9;
    TimerTicks = 0;
    TimerSpeed = 60;



    ButtonInputAllowed1 = 1;
    ReleaseButton1 = 0; // 0 = Idle condition. Live with it.
    AnimationTicks1 = 1; // Constantly running from 1 to 60. I think it's preferable to use ticks generated from the game code rather than from the timer inside the console.
    DirectionalInputAllowed1 = 1;
    ButtonInputAllowed1 = 1;
    AnimationStrength1 = 0; // Strength of Attacks
    AnimationEnemyAcceleration1 = 0;
    TemporaryAnimationID1 = 0;
    CharHitAcceleration1 = 0;
    CharHitDuration1 = 0;
    PosCharX1 = 200;
    DrawCharX1 = 200;
    PosCharY1 = StageGround;
    GroundLevel1 = 1; // Is the character on the ground?
    JumpDirection1 = 0; //Where does the char jump?
    JumpVelocity1 = -480; //Just the Acceleration. -480 equals an idle position
    JumpBlock1 = 0; //Decides wether the character is allowed to jump.
    CrouchPosition1 = 0; // What Stage of Crouching. 0 = Nothing; 1 = Going into crouch; 2 = Crouch
    CharHealth1 = 1000; // Duh.
    CharHitStatus1 = 0; // What kind of hit did the char receive? 4 = HIT(?) 5= Getting Up 6 = Getting Thrown
    HitPositionX1 = 0;
    HitPositionY1 = 0;
    AnimationValidityCheck1 = 0;
    WhichSpecial1 = 0;
    SpecialAnimationFrame1 = 0;
    SpecialCharChangeX1 = 0;
    SpecialCharChangeY1 = 0;
    SpecialCharAnimation1 = 0;
    SpecialCharAlignment1 = 0; //Deals with both the Enemy Animation during Throws and the kind of throwback during Combos
    SpecialOffset1 = 0;
    CharIsLeft1 = 1;
    ComboMovementX1 = 0;
    ComboMovementY1 = 0;
    SpecialEffect1 = 0;
    SpecialEffectPosX1 = 0;
    SpecialEffectPosY1 = 0;
    SpecialEffectDrawX1 = 0;
    SpecialEffectDrawY1 = 0;
    SpecialEffectSpeedX1 = 0;
    SpecialEffectSpeedY1 = 0;
    SpecialEffectSizeX1 = 0;
    SpecialEffectSizeY1 = 0;
    SpecialEffectRange1 = 0; //Gets substracted every pixel moved until it is zero.
    SpecialEffectStrength1 = 0;
    SpecialEffectAcceleration1 = 0;
    SpecialEffectWhichFrame1 = 0;
    SpecialEffectStage1 = 0; //0 = Not yet thrown 1 = Before 2 = During(Loop) 3 = Vanish 4 = HIT
    SpecialEffectPosCharRelativity = 0;
    SpecialEffectTextureSizeX1 = 0;
    SpecialEffectTextureSizeY1 = 0;
    SpecialEffectTicks1 = 0;
    SpecialEffectOffset1 = 0;
    JumpAnimationFlags1 = 0;
    WhichJumpStage1 = 0;
    WhichJumpFrame1 = 0;
    JumpFrameAmount1 = 0;
    JumpTicks1 = 1;
    JumpAnimationSpeed1 = 9;
    CurrentJumpStage1 = 0;
    JumpLoop1 = 0;
    JumpType1 = 0;
    ComboID1 = 0;
    ComboChecker1 = 0;
    DirectionalComboChecker1 = 0;

    WhichHitSoundEffect1 = 0;
    WhichMissSoundEffect1 = 0;
    WhichSoundEffectFrame1 = 0;


    AnimationTicks2 = 1;
    InputAllowed2 = 1;
    PosCharX2 = 500;
    DrawCharX2 = 0;
    PosCharY2 = StageGround;
    CharHealth2 = 1000;
    CharHitStatus2 = 0;
    CharHitAcceleration2 = 0;
    CharHitDuration2 = 0;
    HitPositionX2 = 0;
    HitPositionY2 = 0;
    CharHitAnimationSpeed2 = 1;
    GroundLevel2 = 1;
    CrouchPosition2 = 0;
    AnimationEnemyAcceleration2 = 0;
    AnimationStrength2 = 0;
    AnimationChange2 = 0;
    TemporaryAnimationID2 = 0;
    AnimationValidityCheck2 = 0;
    WhichSpecial2 = 0;
    SpecialAnimationFrame2 = 0;
    SpecialCharChangeX2 = 0;
    SpecialCharChangeY2 = 0;
    SpecialCharAnimation2 = 0;
    SpecialCharAlignment2 = 0;
    SpecialOffset2 = 0;
    JumpDirection2 = 0; //Where does the char jump?
    JumpVelocity2 = -480; //Just the Acceleration. -480 equals an idle position
    JumpBlock2 = 0; //Decides wether the character is allowed to jump.
    CharIsLeft2 = 0;
    ComboMovementX2 = 0;
    ComboMovementY2 = 0;
    JumpIdleUpFlags2 = 0;
    JumpAnimationFlags2 = 0;
    WhichJumpStage2 = 0;
    WhichJumpFrame2 = 0;
    JumpFrameAmount2 = 0;
    JumpTicks2 = 1;
    JumpAnimationSpeed2 = 9;
    JumpLoop2 = 0;
    JumpType2 = 0;
    DirectionalInputAllowed2 = 1;


    WhichAIPattern2 = 0;
    TimeSlotLength2 = 1;
    TimeSlotTicks2 = 1;
    RandomAINumber2 = 0;


    AnimationID1 = -1;
    MovementReadCompulsory(0, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    //AnimationName1 = "STANDING";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;

    AnimationID2 = -1;
    MovementReadCompulsory(0, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "STANDING";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;



    FightStage = 1;
    
    
    
    SuperCoolEffectTicks = 0;
    }

    while(FightStage == 1){


    
    #include "ScreenCalculationCode.c" 
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    FightStage = DrawSuperCoolEffect(SuperCoolEffectTicks);
    DrawChar1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawChar2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    pvr_list_finish();
    pvr_scene_finish();


    SuperCoolEffectTicks++;
    }
    while(FightStage == 2){


    
    #include "ScreenCalculationCode.c" 
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawChar1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawChar2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    pvr_list_finish();
    pvr_scene_finish();




    if(AnimationTicks1%AnimationSpeed1 == 0){
    WhichAnimationFrame1++;
    if(WhichAnimationFrame1 >= FrameAmount1+1) {
    if(StartAnimationFlag1 == 0) WhichAnimationFrame1 = 1;
    else{
    if(AnimationID1 != -1){
    AnimationID1 = -1;
    MovementReadCompulsory(0, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    //AnimationName1 = "STANDING";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;
            }
    }
    }
    }
    if(AnimationTicks2%AnimationSpeed2 == 0){
    WhichAnimationFrame2++;
    if(WhichAnimationFrame2 >= FrameAmount2+1) {
    if(StartAnimationFlag2 == 0) WhichAnimationFrame2 = 1;
    else{
    if(AnimationID2 != -1){
    AnimationID2 = -1;
    MovementReadCompulsory(0, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    //AnimationName2 = "STANDING";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;
            }
    }
    }
    }

    AnimationTicks1++;
    if(AnimationTicks1 == 61){
    AnimationTicks1=1;
    }

    AnimationTicks2++;
    if(AnimationTicks2 == 61){
    AnimationTicks2=1;
    }


    if(StartAnimationFlag1 == 0 && StartAnimationFlag2 == 0) FightStage +=1;
    }
    FightAnimationTicks = 1;  
    WhichFightAnimationFrame = 1;
    EndFightAnimation = 0;
    
    if(FightStage == 3){
    while(EndFightAnimation == 0 || FightAnimationTicks%FightAnimationSpeed != 0){ 

    ReadRoundAnimation(WhichRound, WhichFightAnimationFrame, &FightAnimationID, &FightAnimationSpeed, &FightAnimationTextureSizeX, &FightAnimationTextureSizeY, &FightAnimationSizeX, &FightAnimationSizeY, &FightAnimationScreenPositionX, &FightAnimationScreenPositionY, WhichFightAnimationVoiceClipName, &FightAnimationVoiceClipChecker, &EndFightAnimation);
    

    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
 
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawCharLite1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawCharLite2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    DrawRoundAnimation(FightAnimationID, FightAnimationTextureSizeX, FightAnimationTextureSizeY, FightAnimationSizeX, FightAnimationSizeY, FightAnimationScreenPositionX, FightAnimationScreenPositionY);
    pvr_list_finish();
    pvr_scene_finish();


    if(FightAnimationTicks%FightAnimationSpeed == 0){
    WhichFightAnimationFrame++;
    FightAnimationTicks = 0;
    }

    FightAnimationTicks++;
    if(FightAnimationTicks == 0xFFFF){
    FightAnimationTicks=1;
    }

    }


    }


    if(FightStage == 3){

    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawCharLite1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawCharLite2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    pvr_list_finish();
    pvr_scene_finish();

    FightAnimationSizeX = 0;
    FightAnimationSizeY = 0;
    FightAnimationTextureSizeX = 0;
    FightAnimationTextureSizeY = 0;
    EndFightAnimation = 0;
    WhichFightAnimationFrame = 1;
    FightAnimationVoiceClipChecker = 0;
    FightAnimationScreenPositionX = 0;
    FightAnimationScreenPositionY = 0;
    FightAnimationSpeed = 60;
    FightAnimationID = 0;
    FightAnimationTicks = 1;  
    Bluff = sprintf(REOSpeedwagon, "%s/FIGHTSFX/GOFORIT0.WAV", StreamingFileSystemUsed);
    FightAnimationSFX = snd_sfx_load(REOSpeedwagon);
    snd_sfx_play(FightAnimationSFX, VolumeSFX, 128);
    while(FightStage == 3){
    

    ReadFightAnimation(WhichFightAnimationFrame, &FightAnimationID, &FightAnimationSpeed, &FightAnimationTextureSizeX, &FightAnimationTextureSizeY, &FightAnimationSizeX, &FightAnimationSizeY, &FightAnimationScreenPositionX, &FightAnimationScreenPositionY, WhichFightAnimationVoiceClipName, &FightAnimationVoiceClipChecker, &EndFightAnimation);
    
    //#include "ScreenCalculationCode.c" 
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    //DrawLifeBar(CharHealth1, CharHealth2);
    //DrawTimer(FirstTimerValue,SecondTimerValue);
    //DrawArray(RealCharName1, 35, 75, 15, 1);
    //DrawArray(RealCharName2, 385, 75, 15, 1);
    //DrawPoints(PointArray1, PointArray2);
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawCharLite1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawCharLite2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    DrawFightAnimation(FightAnimationID, FightAnimationTextureSizeX, FightAnimationTextureSizeY, FightAnimationSizeX, FightAnimationSizeY, FightAnimationScreenPositionX, FightAnimationScreenPositionY);
    pvr_list_finish();
    pvr_scene_finish();


    /*if(AnimationTicks1%AnimationSpeed1 == 0){
    WhichAnimationFrame1++;
    if(WhichAnimationFrame1 >= FrameAmount1+1) WhichAnimationFrame1 = 1;
    }

    if(AnimationTicks2%AnimationSpeed2 == 0){
    WhichAnimationFrame2++;
    if(WhichAnimationFrame2 >= FrameAmount2+1) WhichAnimationFrame2 = 1;
    }

    AnimationTicks1++;
    if(AnimationTicks1 == 61){
    AnimationTicks1=1;
    }

    AnimationTicks2++;
    if(AnimationTicks2 == 61){
    AnimationTicks2=1;
    }
    */

    if(FightAnimationTicks%FightAnimationSpeed == 0){
    WhichFightAnimationFrame++;
    FightAnimationTicks = 0;
    if(EndFightAnimation == 1)  FightStage+=1;
    }

    FightAnimationTicks++;
    if(FightAnimationTicks == 61){
    FightAnimationTicks=1;
    }

    }
    snd_sfx_unload(FightAnimationSFX);
    }



   
    while(FightStage == 4){

    //printf("Main Loop Restart.\n");

    if(CharIsHuman2 == 0){
    #include "AICalculations2.c"
    //printf("AI Calculated.\n");
    }
    else{
    #include "ControlCode2.c"
    }

    if(CharIsHuman1 == 0){
    #include "AICalculations1.c"
    //printf("AI Calculated.\n");
    }
    else{
    #include "ControlCode1.c"
    }

    //#include "ControlCode1.c"
    //printf("Controls Calculated.\n");

    #include "ScreenCalculationCode.c"
    //printf("Screen Calculated.\n");
    #include "JumpingCode.c"
    //printf("Jumping Calculated.\n");

    if(WhichMissSoundEffect1 != 0 && WhichAnimationFrame1 == WhichSoundEffectFrame1){


    LoadSoundEffect(&MissSFX1, WhichMissSoundEffect1, CharacterName1, SoundEffectVolume);   
    WhichMissSoundEffect1 = 0;
    WhichSoundEffectFrame1 = 0;
    
    }


    if(WhichMissSoundEffect2 != 0 && WhichAnimationFrame2 == WhichSoundEffectFrame2){


    LoadSoundEffect(&MissSFX2, WhichMissSoundEffect2, CharacterName2, SoundEffectVolume);   
    WhichMissSoundEffect2 = 0;
    WhichSoundEffectFrame2 = 0;
    
    }

    #include "CollisionCode.c"
    //printf("Collision Calculated!\n");
    #include "DrawingCode.c"
    //printf("Drawing Worked!\n");



     
    if(AnimationTicks1%AnimationSpeed1 == 0){
    WhichAnimationFrame1++;
    if(WhichAnimationFrame1 >= FrameAmount1+1 && AnimationLoop1 == 1){
    WhichAnimationFrame1 = 1;
    }

    if(WhichAnimationFrame1 >= FrameAmount1+1 && AnimationLoop1 == 0){

    if(GroundLevel1 == 1 && CrouchPosition1 == 0){
    
    //MovementReadCompulsory(0, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    //AnimationName1 = AnimationBuffer1;    
    DirectionalInputAllowed1 = 1;
    MovementReadCompulsory(0, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    //AnimationName1 = "STANDING";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;
    AnimationID1 = -1;

    CharHitStatus1 = 0;
    ComboMovementX1 = 0;
    ComboMovementY1 = 0;
    }
    if(GroundLevel1 == 1 && CrouchPosition1 == 2){
    AnimationID1 = -5;
    MovementReadCompulsory(4, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    //AnimationName1 = "CROU_DUR";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;

    CharHitStatus1 = 0;
    ComboMovementX1 = 0;
    ComboMovementY1 = 0;
    }
    if(GroundLevel1 == 0){
    if(CharHitStatus1 != 4){
    AnimationType1 = 1;
    WhichAnimationFrame1 = 1;
    AnimationSpeed1 = 61;
    FrameAmount1 = 1;
    AnimationLoop1 =1;
    AnimationTicks1 = 1;
    AnimationID1 = 0;
    CharHitStatus1 = 0;
    ComboMovementX1 = 0;
    ComboMovementY1 = 0;
    }
    else{
    WhichAnimationFrame1 = FrameAmount1;
    AnimationSpeed1 = 61;
    }
    }

    }


    }
    AnimationTicks1++;
    if(AnimationTicks1 == 61){
    AnimationTicks1=1;
    }


    if(CharHitAcceleration1 != 0){
    if(WhichAnimationFrame1 < FrameAmount1 && AnimationTicks1%CharHitAnimationSpeed1 == 0 ){
    WhichAnimationFrame1++;
    }
    PosCharX1 += CharHitAcceleration1;
    if(PosCharX1 > 1280) PosCharX1 = 1280;

    if(CharHitAcceleration1 < 1) CharHitAcceleration1 +=2;
    else if(CharHitAcceleration1 > 1) CharHitAcceleration1 -=2;
    else CharHitAcceleration1 = 0;
    }

    if(CharHitStatus1 == 4 && CharHitAcceleration1 == 0 && WhichAnimationFrame1 < FrameAmount1 && AnimationTicks1%CharHitAnimationSpeed1 == 0){
     WhichAnimationFrame1++;
    }
    
    if(CharHitStatus1 == 4 && CharHitAcceleration1 == 0 && WhichAnimationFrame1 == FrameAmount1 && GroundLevel1 == 1){
    if(AnimationID1 == -10){
    MovementReadCompulsory(9, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    //AnimationName1 = "BLOCKING";
    AnimationTicks1 = 1;
    AnimationID1 = -10;
    AnimationLoop1 = 0;
    WhichAnimationFrame1 = FrameAmount1;

    CharHitStatus1 = 5;
    CharHitAcceleration1 = 0;
    }
    else if(AnimationID1 == -11){
    MovementReadCompulsory(10, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    //AnimationName1 = "CROUBLOC";
    AnimationTicks1 = 1;
    AnimationID1 = -11;
    AnimationLoop1 = 0;
    WhichAnimationFrame1 = FrameAmount1;

    CharHitStatus1 = 5;
    CharHitAcceleration1 = 0;
    }
    else if(AnimationID1 == -13){
    AnimationID1 = -14;
    MovementReadCompulsory(13, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    //AnimationName1 = "BACKLOUP";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;
    CharHitStatus1 = 5;
    CharHitAcceleration1 = 0;
    }
    else if(AnimationID1 == -6){
    AnimationID1 = -7;
    MovementReadCompulsory(6, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    //AnimationName1 = "BACKHIUP";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;
    CharHitStatus1 = 5;
    CharHitAcceleration1 = 0;   
    }
    else{
    AnimationID1 = -9;
    MovementReadCompulsory(8, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    //AnimationName1 = "GETTINUP";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;
    CharHitStatus1 = 5;
    CharHitAcceleration1 = 0;
    }
    }


    if(CharHitAcceleration2 != 0){
    if(WhichAnimationFrame2 < FrameAmount2 && AnimationTicks2%CharHitAnimationSpeed2 == 0 ){
    WhichAnimationFrame2++;
    }
    PosCharX2 += CharHitAcceleration2;
    if(PosCharX2 > 1280) PosCharX2 = 1280;
    if(CharHitAcceleration2 < 1) CharHitAcceleration2 +=2;
    else if(CharHitAcceleration2 > 1) CharHitAcceleration2 -=2;
    else CharHitAcceleration2 = 0;
    }

    if(CharHitAcceleration2 == 0 && CharHitStatus2 == 4 && WhichAnimationFrame2 < FrameAmount2 && AnimationTicks2%CharHitAnimationSpeed2 == 0){
     WhichAnimationFrame2++;
    }
    
    if(CharHitStatus2 == 4 && CharHitAcceleration2 == 0 && WhichAnimationFrame2 == FrameAmount2 && GroundLevel2 == 1){
    if(AnimationID2 == -10){
    MovementReadCompulsory(9, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    WhichAnimationFrame2 = FrameAmount2;
    AnimationLoop2 = 0;
    AnimationTicks2 = 1;
    CharHitStatus2 = 5;
    CharHitAcceleration2 = 0;
    }
    else if(AnimationID2 == -11){
    MovementReadCompulsory(10, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    //AnimationName2 = "CROUBLOC";
    AnimationLoop2 = 0;
    AnimationTicks2 = 1;
    AnimationID2 = -11;
    WhichAnimationFrame2 = FrameAmount2;

    CharHitStatus2 = 5;
    CharHitAcceleration2 = 0;
    }
    else if(AnimationID2 == -13){
    AnimationID2 = -14;
    MovementReadCompulsory(13, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    //AnimationName2 = "BACKLOUP";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;
    CharHitStatus2 = 5;
    CharHitAcceleration2 = 0;
    }
    else if(AnimationID2 == -6){
    AnimationID2 = -7;
    MovementReadCompulsory(6, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "BACKHIUP";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;
    CharHitStatus2 = 5;
    CharHitAcceleration2 = 0;
    }
    else if(AnimationID2 == -8){ 

    AnimationID2 = -9;
    MovementReadCompulsory(8, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "GETTINUP";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;
    CharHitStatus2 = 5;
    CharHitAcceleration2 = 0;
    }
    }

    if(AnimationTicks2%AnimationSpeed2 == 0){
    WhichAnimationFrame2++;
    //printf("Current FrameAmount: %d.\n", FrameAmount2);
    //printf("Current AnimationLoop: %d.\n", AnimationLoop2);
    if(WhichAnimationFrame2 >= FrameAmount2+1 && AnimationLoop2 == 1){
    WhichAnimationFrame2 = 1;
    AnimationID2 = -1;
    }
    if(WhichAnimationFrame2 >= FrameAmount2+1 && AnimationLoop2 == 0){
    if(GroundLevel2 == 1 && CrouchPosition2 == 0){
    
    //MovementReadCompulsory(0, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    //AnimationName2 = AnimationBuffer2;    
    DirectionalInputAllowed2 = 1;
    MovementReadCompulsory(0, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    //AnimationName2 = "STANDING";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;
    AnimationID2 = -1;

    CharHitStatus2 = 0;
    ComboMovementX2 = 0;
    ComboMovementY2 = 0;
    }

    if(GroundLevel2 == 1 && CrouchPosition2 == 2){
    AnimationID2 = -5;
    MovementReadCompulsory(4, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    //AnimationName2 = "CROU_DUR";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;

    CharHitStatus2 = 0;
    ComboMovementX2 = 0;
    ComboMovementY2 = 0;
    }
    if(GroundLevel2 == 0){
    if(AnimationType2 != 4){
    AnimationType2 = 1;
    WhichAnimationFrame2 = 1;
    AnimationSpeed2 = 61;
    FrameAmount2 = 1;
    AnimationLoop2 =1;
    AnimationTicks2 = 1;
    AnimationID2 = 0;
    CharHitStatus2 = 0;
    ComboMovementX2 = 0;
    ComboMovementY2 = 0;
    }
    else{
    WhichAnimationFrame2 = FrameAmount2;
    AnimationSpeed2 = 61;
    }
    }
 
    
    }
    //printf("Current AnimationFrameAfter: %d.\n", WhichAnimationFrame2);
    }
    AnimationTicks2++;
    if(AnimationTicks2 == 61){
    AnimationTicks2=1;
    }

   TimerTicks++;
   if(TimerTicks%TimerSpeed == 0){
   TimerTicks = 0;
   SecondTimerValue--;
   if(SecondTimerValue < 0){
   FirstTimerValue--;
   SecondTimerValue = 9;
   if(FirstTimerValue < 0) FirstTimerValue = 9;
   }  
   }


   if(CharHitStatus1 != 4){
    if(CurrentDizzy1 > 0){ 
     CurrentDizzy1--;
     if(CurrentDizzy1 > MaxDizzy1 && AnimationType1 == 1){
    AnimationID1 = -13;
    MovementReadCompulsory(12, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    AnimationName1 = "DIZZZZZY";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;  
    AnimationLoop1 = 1; 
     }
    }
    else if(AnimationType1 == 9 && CurrentDizzy1 == 0){
     AnimationLoop1 = 0;
    }
   }

   if(CharHitStatus2 != 4){
    if(CurrentDizzy2 > 0){ 
     CurrentDizzy2--;
     if(CurrentDizzy2 > MaxDizzy2 && AnimationType2 == 1){
    AnimationID2 = -13;
    MovementReadCompulsory(12, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "DIZZZZZY";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;  
    AnimationLoop2 = 1; 
     }
    }
    else if(AnimationType2 == 9 && CurrentDizzy2 == 0){
     AnimationLoop2 = 0;
    }
   }

   if(SpecialEffectStage1 != 0){ 
    if(SpecialEffectTicks1%SpecialEffectAnimationSpeed1 == 0){
     SpecialEffectWhichFrame1++;

     if(SpecialEffectWhichFrame1 >= SpecialEffectFrameAmount1+1){

      if(SpecialEffectStage1 == 1){

       //printf("Now Reading the 2nd stage!\n");
       SpecialEffectReadHuman(CharacterName1, SpecialEffectNameBuffer1, SpecialEffectOffset1+16, &SpecialEffectAnimationSpeed1, &SpecialEffectFrameAmount1);   
       //printf("Done Reading the 2nd stage!\n");
       SpecialEffectStage1 = 2;
       SpecialEffectTicks1 = 1;
      }

      if(SpecialEffectStage1 == 3 || SpecialEffectStage1 == 4){
       SpecialEffectStage1 = 0;
       SpecialEffect1 = 0;
       SpecialEffectRange1 = 0;
       pvr_mem_free(SpecialEffectTexture1);

      }

      SpecialEffectWhichFrame1 = 1;
     }
    
    }

    SpecialEffectTicks1++;
    if(SpecialEffectTicks1 ==61){
    SpecialEffectTicks1 = 1;

    }



    }

   if(SpecialEffectStage2 != 0){ 
    if(SpecialEffectTicks2%SpecialEffectAnimationSpeed2 == 0){
     SpecialEffectWhichFrame2++;

     if(SpecialEffectWhichFrame2 >= SpecialEffectFrameAmount2+1){

      if(SpecialEffectStage2 == 1){

       //printf("Now Reading the 2nd stage!\n");
       SpecialEffectReadHuman(CharacterName2, SpecialEffectNameBuffer2, SpecialEffectOffset2+16, &SpecialEffectAnimationSpeed2, &SpecialEffectFrameAmount2);   
       //printf("Done Reading the 2nd stage!\n");
       SpecialEffectStage2 = 2;
       SpecialEffectTicks2 = 1;
      }

      if(SpecialEffectStage2 == 3 || SpecialEffectStage2 == 4){
       SpecialEffectStage2 = 0;
       SpecialEffect2 = 0;
       SpecialEffectRange2 = 0;
       pvr_mem_free(SpecialEffectTexture2);

      }

      SpecialEffectWhichFrame2 = 1;
     }
    
    }

    SpecialEffectTicks2++;
    if(SpecialEffectTicks2 ==61){
    SpecialEffectTicks2 = 1;

    }
}
    
    }
    ButtonInputAllowed1 = 0;
    //ButtonInputAllowed2 = 0;
    MenuArrowPosition = 1;
    MenuSelectedOption = 0;

    while(FightStage == 5){
    

    if(WhichMenu == 1){
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    DrawLifeBar(CharHealth1, CharHealth2);
    DrawTimer(FirstTimerValue,SecondTimerValue);
    DrawArray(RealCharName1, 35, 75, LowerGuiPositionZ, 15, 1);
    DrawArray(RealCharName2, 385, 75, LowerGuiPositionZ, 15, 1);
    DrawPoints(PointArray1, PointArray2);
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawColorBox(MenuScreenPositionX, MenuScreenPositionY, UpperGuiPositionZ1, MenuSizeX, MenuSizeY, MenuColor);
    if(MenuArrowPosition == 1) DrawArray("CONTINUE", OptionPositionX, OptionPositionY, UpperGuiPositionZ2, OptionSize, 2);
    else DrawArray("CONTINUE", MenuScreenPositionX, OptionPositionY, UpperGuiPositionZ2, OptionSize, MenuFontColor);
    if(MenuArrowPosition == 2) DrawArray("SELECT CHARACTER", OptionPositionX, OptionPositionY+OptionSize, UpperGuiPositionZ2, OptionSize, 2);
    else DrawArray("SELECT CHARACTER", MenuScreenPositionX, OptionPositionY+OptionSize, UpperGuiPositionZ2, OptionSize, MenuFontColor);
    if(MenuArrowPosition == 3) DrawArray("OPTIONS", OptionPositionX, OptionPositionY+OptionSize*2, UpperGuiPositionZ2, OptionSize, 2);
    else DrawArray("OPTIONS", MenuScreenPositionX, OptionPositionY+OptionSize*2, UpperGuiPositionZ2, OptionSize, MenuFontColor);
    if(MenuArrowPosition == 4) DrawArray("QUIT", OptionPositionX, OptionPositionY+OptionSize*3, UpperGuiPositionZ2, OptionSize, 2);
    else DrawArray("QUIT", MenuScreenPositionX, OptionPositionY+OptionSize*3, UpperGuiPositionZ2, OptionSize, MenuFontColor);
    //DrawArrow(OptionPositionX-MenuArrowSize-5,(MenuArrowPosition-1)*OptionSize+OptionPositionY, MenuArrowSize);
    DrawChar1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawChar2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    pvr_list_finish();
    pvr_scene_finish();


        if((cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER)) != NULL) {
    st = (cont_state_t *)maple_dev_status(cont);


    if ((st->buttons & CONT_START) && ButtonInputAllowed1 == 1) {
            FightStage-=1;
            ButtonInputAllowed1 = 0;
            //ButtonInputAllowed2 = 0;
			}

    if ((st->buttons & CONT_DPAD_UP) && ButtonInputAllowed1 == 1) {
            MenuArrowPosition-=1;
            if(MenuArrowPosition < 1) MenuArrowPosition = 1;
            ButtonInputAllowed1 = 0;
            //ButtonInputAllowed2 = 0;
     }

if((st->buttons & CONT_DPAD_DOWN) && ButtonInputAllowed1 == 1){

            MenuArrowPosition+=1;
            if(MenuArrowPosition > 4) MenuArrowPosition = 4;
            ButtonInputAllowed1 = 0;
            //ButtonInputAllowed2 = 0;


}

if((st->buttons & CONT_A) && ButtonInputAllowed1 == 1) {

            MenuSelectedOption = MenuArrowPosition;
            ButtonInputAllowed1 = 0;
            //ButtonInputAllowed2 = 0;
			}





    if (!(st->buttons & CONT_START) && !(st->buttons & CONT_X) && !(st->buttons & CONT_B) && !(st->buttons & CONT_A) && !(st->buttons & CONT_Y) && !(st->buttons & CONT_DPAD_RIGHT) && !(st->buttons & CONT_DPAD_UP) && !(st->buttons & CONT_DPAD_DOWN) && !(st->buttons & CONT_DPAD_LEFT) && ButtonInputAllowed1 == 0) {
            ButtonInputAllowed1 = 1;
            //printf("INPUT ALLOWED AGAIN!\n");
            //printf("STATUS: %d!\n", ButtonInputAllowed1);
			}
 }


 if(MenuSelectedOption == 0){
    FightStage -= 1;
    }
else if(MenuSelectedOption == 2){
    //FightStage = FightEntireReset;
    }
else if(MenuSelectedOption == 3){
 
    }
else if(MenuSelectedOption == 4){
    FightStage = 13;
    }
else MenuSelectedOption = -1;
    }

if(WhichMenu == 2){
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    DrawLifeBar(CharHealth1, CharHealth2);
    DrawTimer(FirstTimerValue,SecondTimerValue);
    DrawArray(RealCharName1, 35, 75, LowerGuiPositionZ, 15, 1);
    DrawArray(RealCharName2, 385, 75, LowerGuiPositionZ, 15, 1);
    DrawPoints(PointArray1, PointArray2);
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawColorBox(MenuScreenPositionX, MenuScreenPositionY, UpperGuiPositionZ1, MenuSizeX, MenuSizeY, MenuColor);
    DrawArray("MUSIC", OptionPositionX, OptionPositionY, UpperGuiPositionZ2, OptionSize, MenuFontColor);
    DrawArray("SOUNDEFFECTS", OptionPositionX, OptionPositionY+OptionSize, UpperGuiPositionZ2, OptionSize, MenuFontColor);
    //DrawArray("", OptionPositionX, OptionPositionY+OptionSize*2, UpperGuiPositionZ2, OptionSize, MenuFontColor);
    //DrawArray("", OptionPositionX, OptionPositionY+OptionSize*3, UpperGuiPositionZ2, OptionSize, MenuFontColor);
    //DrawArrow(OptionPositionX-MenuArrowSize-5,(MenuArrowPosition-1)*OptionSize+OptionPositionY, MenuArrowSize);
    DrawChar1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawChar2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    pvr_list_finish();
    pvr_scene_finish();


        if((cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER)) != NULL) {
    st = (cont_state_t *)maple_dev_status(cont);


    if ((st->buttons & CONT_START) && ButtonInputAllowed1 == 1) {
            FightStage-=1;
            ButtonInputAllowed1 = 0;
            //ButtonInputAllowed2 = 0;
			}

    if ((st->buttons & CONT_DPAD_UP) && ButtonInputAllowed1 == 1) {
            MenuArrowPosition-=1;
            if(MenuArrowPosition < 1) MenuArrowPosition = 1;
            ButtonInputAllowed1 = 0;
            //ButtonInputAllowed2 = 0;
     }

if((st->buttons & CONT_DPAD_DOWN) && ButtonInputAllowed1 == 1){

            MenuArrowPosition+=1;
            if(MenuArrowPosition > 2) MenuArrowPosition = 2;
            ButtonInputAllowed1 = 0;
            //ButtonInputAllowed2 = 0;


}

if((st->buttons & CONT_A) && ButtonInputAllowed1 == 1) {

            if(MenuArrowPosition == 1){ 
            BGMVolume++;
            if(BGMVolume > 15) BGMVolume = 15;
            //spu_cdda_volume(BGMVolume, BGMVolume);
            //printf("New BGM Volume: %X!\n", BGMVolume);
            ButtonInputAllowed1 = 0;
			}
            if(MenuArrowPosition == 2){ 
            SoundEffectVolume++;
            if(SoundEffectVolume > 0xFF) SoundEffectVolume = 0xFF;
            //printf("New SoundEffect Volume: %X!\n", SoundEffectVolume);
            ButtonInputAllowed1 = 0;
			}

             }

if((st->buttons & CONT_X) && ButtonInputAllowed1 == 1) {

            if(MenuArrowPosition == 1){ 
            BGMVolume--;
            if(BGMVolume < 0) BGMVolume = 0;
            //spu_cdda_volume(BGMVolume, BGMVolume);
            //printf("New BGM Volume: %X!\n", BGMVolume);
            ButtonInputAllowed1 = 0;
			}
            if(MenuArrowPosition == 2){ 
            SoundEffectVolume--;
            if(SoundEffectVolume < 0) SoundEffectVolume = 0;
            //printf("New SoundEffect Volume: %X!\n", SoundEffectVolume);
            ButtonInputAllowed1 = 0;
			}

             }

if((st->buttons & CONT_B) && ButtonInputAllowed1 == 1) {

            WhichMenu = 1;
            MenuSelectedOption = 0;
            MenuArrowPosition = 1;
            ButtonInputAllowed1 = 0;

             }


    if (!(st->buttons & CONT_START) && !(st->buttons & CONT_X) && !(st->buttons & CONT_B) && !(st->buttons & CONT_A) && !(st->buttons & CONT_Y) && !(st->buttons & CONT_DPAD_RIGHT) && !(st->buttons & CONT_DPAD_UP) && !(st->buttons & CONT_DPAD_DOWN) && !(st->buttons & CONT_DPAD_LEFT) && ButtonInputAllowed1 == 0) {
            ButtonInputAllowed1 = 1;
            //printf("INPUT ALLOWED AGAIN!\n");
            //printf("STATUS: %d!\n", ButtonInputAllowed1);
			}
 }


}
    } 
   
while(FightStage == 6){

    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    if(FightAnimationTicks%FightAnimationSpeed == 0){
    WhichFightAnimationFrame++;
    FightAnimationTicks = 0;
    if(EndFightAnimation == 1)  FightStage+=1;
    }

    FightAnimationTicks++;
    if(FightAnimationTicks == 61){
    FightAnimationTicks=1;
    }
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawChar1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawChar2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    if(WhichCharLost == 1){
    DrawAnotherSuperCoolEffect(SuperCoolEffectTicks, HitPositionX1, HitPositionY1);
    if(SuperCoolEffectTicks%2 == 0) DrawCharX1 +=5;
    else DrawCharX1-=5;
    }
    else{
    DrawAnotherSuperCoolEffect(SuperCoolEffectTicks, HitPositionX2, HitPositionY2);
    if(SuperCoolEffectTicks%2 == 0) DrawCharX2 +=5;
    else DrawCharX2 -=5;    
    }

    if(WhichEffect2 != 0)    {
    EffectTicks2++;
    if(EffectTicks2 == 101){
    EffectTicks2 = 1;
    }
    DrawEffect(HitPositionX2, HitPositionY2, WhichEffect2, WhichEffectFrame2);
    if(EffectTicks2%10 == 0){
    WhichEffectFrame2++;
    }
    if(WhichEffectFrame2 == EffectFrameAmount2+1){
    WhichEffectFrame2 = 0;
    EffectFrameAmount2 = 0;
    WhichEffect2 = 0;
    }
    }

    if(WhichEffect1 != 0)    {
    EffectTicks1++;
    if(EffectTicks1 == 101){
    EffectTicks1 = 1;
    }
    DrawEffect(HitPositionX1, HitPositionY1, WhichEffect1, WhichEffectFrame1);
    if(EffectTicks1%10 == 0){
    WhichEffectFrame1++;
    }
    if(WhichEffectFrame1 == EffectFrameAmount1+1){
    WhichEffectFrame1 = 0;
    EffectFrameAmount1 = 0;
    WhichEffect1 = 0;
    }
    }
    pvr_list_finish();
    pvr_scene_finish();



    SuperCoolEffectTicks++;
    
    if(WhichEffect1 == 0 && WhichEffect2 == 0) FightStage += 1;

}

if(FightStage == 7){

if(WhichCharLost == 1){
if(KnockOutAnimationFlag1 == 1){
printf("Uhhhh\n");
}
else{
    AnimationID1 = -8;
    MovementReadCompulsory(7, CharacterName1, AnimationBuffer1, &CharHitAnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    AnimationName1 = "KNOKDOWN";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;
    AnimationSpeed1 = 61;
}
if(AnimationType2 != 3) AnimationSpeed2 = 10;
}
else{
if(KnockOutAnimationFlag2 == 1){
printf("Uhhhh #2\n");
}
else{

    AnimationID2 = -8;
    MovementReadCompulsory(7, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    //AnimationName2 = "KNOKDOWN";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;
    AnimationSpeed2 = 61;

}
if(AnimationType1 != 3) AnimationSpeed1 = 10;
}
FightStage+=1;

}
while(FightStage == 8){

    #include "ScreenCalculationCode.c"    
    
    
    if(GroundLevel1 == 0 && JumpVelocity1 != -480){

    if(JumpVelocity1 <= 1 && JumpVelocity1 >= -1 && WhichJumpStage1 == 2 && ((JumpAnimationFlags1 & 16) != 0)){
    WhichJumpStage1 = 3;
    WhichJumpFrame1 = 1;
    JumpTicks1 = 1;
    }
    if((JumpVelocity1 >= 3) && WhichJumpStage1 == 1 && ((JumpAnimationFlags1 & 128) != 0)){
    WhichJumpStage1 = 2;
    WhichJumpFrame1 = 1;
    JumpTicks1 = 1;
    } 
    if((JumpVelocity1 <=-3) && ((JumpAnimationFlags1 & 4) != 0) && WhichJumpStage1 != 4){
    WhichJumpStage1 = 4;
    WhichJumpFrame1 = 1;
    JumpTicks1 = 1;
    }
    if(JumpVelocity1 > JumpStrength1){
    WhichJumpStage1 = 1;
    PosCharY1 = PosCharY1+JumpVelocity1/SlowDownFactor;
    PosCharX1 = PosCharX1-JumpDirection1/SlowDownFactor;
    } 
    PosCharY1 = PosCharY1-JumpVelocity1/SlowDownFactor;
    PosCharX1 = PosCharX1+JumpDirection1/SlowDownFactor;
    JumpVelocity1 -=1;

    if((JumpAnimationSpeed1*SlowDownFactor)%JumpTicks1 == 0){
    WhichJumpFrame1++;  
    if(WhichJumpFrame1 > JumpFrameAmount1){
    if(WhichJumpStage1 == 2 && ((JumpAnimationFlags1 & 64) != 0)){
    WhichJumpStage1 = 4;
    }
    if(WhichJumpStage1 == 2 && ((JumpAnimationFlags1 & 32) != 0)){
    WhichJumpStage1 = 3; 
    }
    if(WhichJumpStage1 == 3 && ((JumpAnimationFlags1 & 2) != 0)){
    WhichJumpStage1 = 4; 
    }
    if(WhichJumpStage1 == 1 && ((JumpAnimationFlags1 & 136) == 0)){
    WhichJumpStage1 = 4; 
    }
    WhichJumpFrame1 = 1;
    JumpTicks1 = 1;    
    }
    }
    

    JumpReadCompulsory(WhichJumpStage1-1, CharacterName1, JumpNameBuffer1, &JumpAnimationSpeed1, &JumpFrameAmount1, &JumpLoop1, 1);
    
    if(AnimationType1 == 1){
    AnimationID1 = -100-WhichJumpStage1;
    AnimationLoop1 = JumpLoop1;
    FrameAmount1 = JumpFrameAmount1;
    AnimationSpeed1 = JumpAnimationSpeed1;
    for (i=0; i<8; i++) AnimationBuffer1[i] = JumpNameBuffer1[i];
    }
    
    JumpTicks1++;
    if(JumpTicks1 == 61){
    JumpTicks1=1;
    }



    if(PosCharY1 >= StageGround && JumpVelocity1 < 0){
        PosCharY1 = StageGround;
        JumpVelocity1 = -480;
        JumpDirection1 = 0;
        GroundLevel1 = 1;
        
        WhichAnimationFrame1 = FrameAmount1;
        JumpLoop1 = 0;
        JumpFrameAmount1 = 0;
        JumpAnimationSpeed1 = 0;
     


        DirectionalInputAllowed1 = 1;
    }

    }


    if(GroundLevel2 == 0 && JumpVelocity2 != -480){

  

    if(JumpVelocity2 <= 1 && JumpVelocity2 >= -1 && WhichJumpStage2 == 2 && ((JumpAnimationFlags2 & 16) != 0)){
    WhichJumpStage2 = 3;
    WhichJumpFrame2 = 1;
    JumpTicks2 = 1;
    }
    if((JumpVelocity2 >= 3) && WhichJumpStage2 == 1 && ((JumpAnimationFlags2 & 128) != 0)){
    WhichJumpStage2 = 2;
    WhichJumpFrame2 = 1;
    JumpTicks2 = 1;
    } 
    if((JumpVelocity2 <=-3) && ((JumpAnimationFlags2 & 4) != 0) && WhichJumpStage2 != 4){
    WhichJumpStage2 = 4;
    WhichJumpFrame2 = 1;
    JumpTicks2 = 1;
    }
    if(JumpVelocity2 > JumpStrength2){
    WhichJumpStage2 = 1;
    PosCharY2 = PosCharY2+JumpVelocity2/SlowDownFactor;
    PosCharX2 = PosCharX2-JumpDirection2/SlowDownFactor;
    } 
    PosCharY2 = PosCharY2-JumpVelocity2/SlowDownFactor;
    PosCharX2 = PosCharX2+JumpDirection2/SlowDownFactor;
    JumpVelocity2 -=1;

    if((JumpAnimationSpeed2*SlowDownFactor)%JumpTicks2 == 0){
    WhichJumpFrame2++;  
    if(WhichJumpFrame2 > JumpFrameAmount2){
    if(WhichJumpStage2 == 2 && ((JumpAnimationFlags2 & 64) != 0)){
    WhichJumpStage2 = 4;
    }
    if(WhichJumpStage2 == 2 && ((JumpAnimationFlags2 & 32) != 0)){
    WhichJumpStage2 = 3; 
    }
    if(WhichJumpStage2 == 3 && ((JumpAnimationFlags2 & 2) != 0)){
    WhichJumpStage1 = 4; 
    }
    if(WhichJumpStage2 == 1 && ((JumpAnimationFlags2 & 136) == 0)){
    WhichJumpStage2 = 4; 
    }
    WhichJumpFrame2 = 1;
    JumpTicks2 = 1;    
    }
    }

    JumpReadCompulsory(WhichJumpStage2-1, CharacterName2, JumpNameBuffer2, &JumpAnimationSpeed2, &JumpFrameAmount2, &JumpLoop2, 1);
    
    if(AnimationType2 == 1){
    AnimationID2 = -100-WhichJumpStage2;
    AnimationLoop2 = JumpLoop2;
    FrameAmount2 = JumpFrameAmount2;
    AnimationSpeed2 = JumpAnimationSpeed2;
    for (i=0; i<8; i++) AnimationBuffer2[i] = JumpNameBuffer2[i];
    }
    
    JumpTicks2++;
    if(JumpTicks2 == 61){
    JumpTicks2=1;
    } 
 



    if(PosCharY2 >= StageGround && JumpVelocity2 < 0){
        PosCharY2 = StageGround;
        JumpVelocity2 = -480;
        JumpDirection2 = 0;
        GroundLevel2 = 1;
        WhichAnimationFrame2 = FrameAmount2;
  
        JumpLoop2 = 0;
        JumpFrameAmount2 = 0;
        JumpAnimationSpeed2 = 0;



        DirectionalInputAllowed2 = 1;
    }

    }
    
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);

    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawChar1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawChar2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    pvr_list_finish();
    pvr_scene_finish();


    if(CharHitAcceleration1 != 0){
    if(WhichAnimationFrame1 < FrameAmount1 && AnimationTicks1%(CharHitAnimationSpeed1) == 0 ){
    WhichAnimationFrame1++;
    }
    PosCharX1 += CharHitAcceleration1;
    if(PosCharX1 > 1280) PosCharX1 = 1280;

    if(CharHitAcceleration1 < 1) CharHitAcceleration1 +=2;
    else if(CharHitAcceleration1 > 1) CharHitAcceleration1 -=2;
    else CharHitAcceleration1 = 0;
    }

    if(CharHitStatus1 == 4 && CharHitAcceleration1 == 0 && WhichAnimationFrame1 < FrameAmount1 && AnimationTicks1%(CharHitAnimationSpeed1) == 0){
     WhichAnimationFrame1++;
    }
    
    if(CharHitStatus1 == 4 && CharHitAcceleration1 == 0 && WhichAnimationFrame1 == FrameAmount1 && GroundLevel1 == 1){


    if(WhichCharLost == 1){
    WhichAnimationFrame1 = FrameAmount1;
    AnimationTicks1 = 1;
    CharHitStatus1 = 5;
    CharHitAcceleration1 = 0;
    }
    else{
    AnimationID1 = -1;
    MovementReadCompulsory(0, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    AnimationName1 = "STANDING";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;
    CharHitStatus1 = 5;
    CharHitAcceleration1 = 0;
    }
    }


    if(CharHitAcceleration2 != 0){
    if(WhichAnimationFrame2 < FrameAmount2 && AnimationTicks2%(CharHitAnimationSpeed2) == 0 ){
    WhichAnimationFrame2++;
    }
    PosCharX2 += CharHitAcceleration2;
    if(PosCharX2 > 1280) PosCharX2 = 1280;
    if(CharHitAcceleration2 < 1) CharHitAcceleration2 +=2;
    else if(CharHitAcceleration2 > 1) CharHitAcceleration2 -=2;
    else CharHitAcceleration2 = 0;
    }

    if(CharHitAcceleration2 == 0 && CharHitStatus2 == 4 && WhichAnimationFrame2 < FrameAmount2 && AnimationTicks2%(CharHitAnimationSpeed2) == 0){
     WhichAnimationFrame2++;
    }
    
    if(CharHitStatus2 == 4 && CharHitAcceleration2 == 0 && WhichAnimationFrame2 == FrameAmount2 && GroundLevel2 == 1){
 
 
    if(WhichCharLost == 2){
    WhichAnimationFrame2 = FrameAmount2;
    AnimationTicks2 = 1;
    CharHitStatus2 = 5;
    CharHitAcceleration2 = 0;
    }
    else{ 

    AnimationID2 = -1;
    MovementReadCompulsory(0, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "STANDING";
    WhichAnimationFrame2 = 2;
    AnimationTicks2 = 1;
    CharHitStatus2 = 5;
    CharHitAcceleration2 = 0;
    }
    }
   

    if(AnimationTicks1%(AnimationSpeed1*SlowDownFactor) == 0){
    WhichAnimationFrame1++;
    if(WhichAnimationFrame1 >= FrameAmount1+1) WhichAnimationFrame1 = FrameAmount1;
    }

    if(AnimationTicks2%(AnimationSpeed2) == 0){
    WhichAnimationFrame2++;
    if(WhichAnimationFrame2 >= FrameAmount2+1) WhichAnimationFrame2 = FrameAmount2;
    }


 if(WhichAnimationFrame1 == FrameAmount1 && WhichAnimationFrame2 == FrameAmount2  && GroundLevel1 == 1 && GroundLevel2 == 1) FightStage += 1;

    AnimationTicks1++;
    if(AnimationTicks1 == 61){
    AnimationTicks1=1;
    }
    AnimationTicks2++;
    if(AnimationTicks2 == 61){
    AnimationTicks2=1;
    }


}

if(FightStage == 9){

if(WhichCharLost == 1){

if(VictoryAnimationFlag2 == 0 && Winner == 0){
FightStage += 1;
}
else{
AnimationID2 = -12;
    MovementReadCompulsory(11, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    //AnimationName2 = "VICTORY1";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;


    while(FightStage == 9){
    
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);

    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawChar1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawChar2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    pvr_list_finish();
    pvr_scene_finish();

    if(AnimationTicks2%AnimationSpeed2 == 0){
    WhichAnimationFrame2++;
    if(WhichAnimationFrame2 >= FrameAmount2+1){
    WhichAnimationFrame2 = FrameAmount2;
    FightStage += 1;
    }
    }

    AnimationTicks2++;
    if(AnimationTicks2 == 61){
    AnimationTicks2=1;
    }


}
}
}
else{

if(VictoryAnimationFlag1 == 0 && Winner == 0){
FightStage += 1;
}
else{


AnimationID1 = -12;
    MovementReadCompulsory(11, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    //AnimationName1 = "VICTORY1";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;

    while(FightStage == 9){
    
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);

    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawChar1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawChar2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    pvr_list_finish();
    pvr_scene_finish();

    if(AnimationTicks1%AnimationSpeed1 == 0){
    WhichAnimationFrame1++;
    if(WhichAnimationFrame1 >= FrameAmount1+1){
    WhichAnimationFrame1 = FrameAmount1;
    FightStage += 1;
    }
    }

    AnimationTicks1++;
    if(AnimationTicks1 == 61){
    AnimationTicks1=1;
    }


}


}
}

}

if(FightStage == 10){


if(WhichCharLost == 1){

CharLosses1 += 1;
if(CharLosses1 == 2){
Winner = 2;
}
}
else{
CharLosses2 += 1;
if(CharLosses2 == 2){
Winner = 1;
}
}

WhichRound++;

    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawCharLite1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawCharLite2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    pvr_list_finish();
    pvr_scene_finish();

if(CharHealth1 == 1000 || CharHealth2 == 1000){

EndFightAnimation = 0;
FightAnimationTicks = 1;  
WhichFightAnimationFrame = 1;

while(EndFightAnimation == 0 || FightAnimationTicks%FightAnimationSpeed != 0){ 

    ReadPerfectAnimation(WhichFightAnimationFrame, &FightAnimationID, &FightAnimationSpeed, &FightAnimationTextureSizeX, &FightAnimationTextureSizeY, &FightAnimationSizeX, &FightAnimationSizeY, &FightAnimationScreenPositionX, &FightAnimationScreenPositionY, WhichFightAnimationVoiceClipName, &FightAnimationVoiceClipChecker, &EndFightAnimation);
    
    //#include "ScreenCalculationCode.c" 
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    //DrawLifeBar(CharHealth1, CharHealth2);
    //DrawTimer(FirstTimerValue,SecondTimerValue);
    //DrawArray(RealCharName1, 35, 75, 15, 1);
    //DrawArray(RealCharName2, 385, 75, 15, 1);
    //DrawPoints(PointArray1, PointArray2);
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawCharLite1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawCharLite2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    DrawPerfectAnimation(FightAnimationID, FightAnimationTextureSizeX, FightAnimationTextureSizeY, FightAnimationSizeX, FightAnimationSizeY, FightAnimationScreenPositionX, FightAnimationScreenPositionY);
    pvr_list_finish();
    pvr_scene_finish();


    if(FightAnimationTicks%FightAnimationSpeed == 0){
    WhichFightAnimationFrame++;
    FightAnimationTicks = 0;
    }

    FightAnimationTicks++;
    if(FightAnimationTicks == 0xFFFF){
    FightAnimationTicks=1;
    }

}
}

if(Winner == 0){

EndFightAnimation = 0;
SuperCoolEffectTicks = 0;

while(EndFightAnimation == 0){
    #include "ScreenCalculationCode.c" 
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawCharLite1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawCharLite2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    EndFightAnimation = FadeToBlack(SuperCoolEffectTicks);
    pvr_list_finish();
    pvr_scene_finish();


    SuperCoolEffectTicks++;
}

FightStage = -1;
}
else{
FightStage+=2;
}

}

if(FightStage == 12){



    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawCharLite1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawCharLite2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    pvr_list_finish();
    pvr_scene_finish();

EndFightAnimation = 0;
FightAnimationTicks = 1;  
WhichFightAnimationFrame = 1;
FightAnimationSpeed = 200;

while(EndFightAnimation == 0){ 

    //ReadWinningAnimation(WhichFightAnimationFrame, &FightAnimationID, &FightAnimationSpeed, &FightAnimationTextureSizeX, &FightAnimationTextureSizeY, &FightAnimationSizeX, &FightAnimationSizeY, &FightAnimationScreenPositionX, &FightAnimationScreenPositionY, WhichFightAnimationVoiceClipName, &FightAnimationVoiceClipChecker, &EndFightAnimation);
    
    //#include "ScreenCalculationCode.c" 
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    //DrawLifeBar(CharHealth1, CharHealth2);
    //DrawTimer(FirstTimerValue,SecondTimerValue);
    //DrawArray(RealCharName1, 35, 75, 15, 1);
    //DrawArray(RealCharName2, 385, 75, 15, 1);
    //DrawPoints(PointArray1, PointArray2);
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawCharLite1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawCharLite2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    DrawWinningAnimation(CharIsHuman1, CharIsHuman2, CharacterName1, CharacterName2, Winner);

    pvr_list_finish();
    pvr_scene_finish();


    if(FightAnimationTicks%FightAnimationSpeed == 0){
    EndFightAnimation = 1;
    FightAnimationTicks = 0;
    }

    FightAnimationTicks++;
    if(FightAnimationTicks == 30000){
    FightAnimationTicks=1;
    }

}


    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawCharLite1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawCharLite2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    pvr_list_finish();
    pvr_scene_finish();

EndFightAnimation = 0;
FightAnimationTicks = 1;  
WhichFightAnimationFrame = 1;
WinPoseDuration = 1000;


ReadWinStuff(Winner, CharacterName1, CharacterName2, &WinPortraitTextureSizeX, &WinPortraitTextureSizeY, &WinPortraitSizeX, &WinPortraitSizeY, &WinPortraitScreenPositionX, &WinPortraitScreenPositionY, &WinQuoteScreenPositionX, &WinQuoteScreenPositionY, &WinQuoteSizeX, &WinQuoteSizeY, &WinQuoteFontSize, &WinQuoteLength, &WinPoseDuration);



while(EndFightAnimation == 0){ 

    //ReadWinningAnimation(WhichFightAnimationFrame, &FightAnimationID, &FightAnimationSpeed, &FightAnimationTextureSizeX, &FightAnimationTextureSizeY, &FightAnimationSizeX, &FightAnimationSizeY, &FightAnimationScreenPositionX, &FightAnimationScreenPositionY, WhichFightAnimationVoiceClipName, &FightAnimationVoiceClipChecker, &EndFightAnimation);
    
    //#include "ScreenCalculationCode.c" 
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawCharLite1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawCharLite2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    DrawWinPortrait(WinPortraitScreenPositionX, WinPortraitScreenPositionY, WinPortraitTextureSizeX, WinPortraitTextureSizeY, WinPortraitSizeX, WinPortraitSizeY);
    DrawWinQuote(Winner, CharacterName1, CharacterName2, WinQuoteScreenPositionX, WinQuoteScreenPositionY, WinQuoteSizeX, WinQuoteSizeY, WinQuoteFontSize, WinQuoteLength);
    DrawTransparentGreyBackGround(0.6);

    pvr_list_finish();
    pvr_scene_finish();


    if(FightAnimationTicks%WinPoseDuration == 0){
    EndFightAnimation = 1;
    FightAnimationTicks = 0;
    }

    FightAnimationTicks++;
    if(FightAnimationTicks == 30000){
    FightAnimationTicks=1;
    }

}




if(CharIsHuman1 == 1 && CharIsHuman2 == 0 && Winner == 2){
FightStage+=2;
}
else{
FightStage = 13;
}
}


if(FightStage == 14){

    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawCharLite1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawCharLite2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    DrawTransparentGreyBackGround(0.6);
    pvr_list_finish();
    pvr_scene_finish();

FirstTimerValue = 9;
TimerTicks = 1;
TimerSpeed = 60;

EndFightAnimation = 0;
FightAnimationTicks = 1;  
WhichFightAnimationFrame = 1;
FightAnimationSpeed = 200;
ButtonInputAllowed1 = 0;

while(FightStage == 14){

    ReadContinueAnimation(WhichFightAnimationFrame, &FightAnimationID, &FightAnimationSpeed, &FightAnimationTextureSizeX, &FightAnimationTextureSizeY, &FightAnimationSizeX, &FightAnimationSizeY, &FightAnimationScreenPositionX, &FightAnimationScreenPositionY, WhichFightAnimationVoiceClipName, &FightAnimationVoiceClipChecker, &EndFightAnimation);

        if((cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER)) != NULL) {
    st = (cont_state_t *)maple_dev_status(cont);


    if ((st->buttons & CONT_START) && ButtonInputAllowed1 == 1) {
            FightStage= -2;
            ButtonInputAllowed1 = 0;
            //ButtonInputAllowed2 = 0;
			}

    if (!(st->buttons & CONT_START) && ButtonInputAllowed1 == 0) {

            ButtonInputAllowed1 = 1;

			}

 }
 
    //#include "ScreenCalculationCode.c" 
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    //DrawStage(LeftStageBorder);
    DrawCharLite1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawCharLite2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);
    DrawTransparentGreyBackGround(0.6);
    DrawContinueAnimation(FightAnimationID, FightAnimationTextureSizeX, FightAnimationTextureSizeY, FightAnimationSizeX, FightAnimationSizeY, FightAnimationScreenPositionX, FightAnimationScreenPositionY);
    DrawContinueCountDown(FirstTimerValue, 200, 150, 200);

    pvr_list_finish();
    pvr_scene_finish();


    if(TimerTicks%TimerSpeed == 0){
    FirstTimerValue--;
    if(FirstTimerValue<0) FightStage = 13;
    }

    if(FightAnimationTicks%FightAnimationSpeed == 0){
    if(EndFightAnimation == 0) WhichFightAnimationFrame++;
    else{
    WhichFightAnimationFrame = EndFightAnimation;
    EndFightAnimation = 0;
    }
    }

    FightAnimationTicks++;
    if(FightAnimationTicks == 30000){
    FightAnimationTicks=1;
    }

    TimerTicks++;
    if(TimerTicks == 30000){
    TimerTicks=1;
    }
}
}

if(FightStage == 13){

    BackGroundAmount[1]--;
    while(BackGroundAmount[1] >= 0){
    pvr_mem_free(BackGroundTextures1[BackGroundAmount[1]]);
    BackGroundAmount[1]--;    
    }
    BackGroundAmount[2]--;
    while(BackGroundAmount[2] >= 0){
    pvr_mem_free(BackGroundTextures2[BackGroundAmount[2]]);
    BackGroundAmount[2]--;    
    }
    BackGroundAmount[3]--;
    while(BackGroundAmount[3] >= 0){
    pvr_mem_free(BackGroundTextures3[BackGroundAmount[3]]);
    BackGroundAmount[3]--;    
    }
    BackGroundAmount[4]--;
    while(BackGroundAmount[4] >= 0){
    pvr_mem_free(BackGroundTextures4[BackGroundAmount[4]]);
    BackGroundAmount[4]--;    
    }
    BackGroundAmount[5]--;
    while(BackGroundAmount[5] >= 0){
    pvr_mem_free(BackGroundTextures5[BackGroundAmount[5]]);
    BackGroundAmount[5]--;
    }
    DeLoadRoundAnimation();
    DeLoadFightAnimation();
    DeLoadPerfectAnimation();
    DeLoadContinueAnimation();
    DeLoadCharRomDisk(CharacterName1);
    DeLoadCharRomDisk(CharacterName2);
    DeLoadTexturesAfterFight();
    snd_sfx_unload(KnockDownSFX);
cdfs_test(); // Prints content of the RAMDISK. For Debugging.
FightStage = 99;
GameLoop = 0;
cdrom_cdda_pause();
}

    }




	return(Winner);
}

