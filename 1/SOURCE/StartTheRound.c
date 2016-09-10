    LeftStageBorder = BackGroundHeaderData.StartLeftStageBorder;

    FirstTimerValue = 9;
    SecondTimerValue = 9;
    TimerTicks = 0;
    TimerSpeed = 60;

    CharIsLeft[CharacterOne] = 1;
    CharIsLeft[CharacterTwo] = 0;

    //PosCharX[CharacterOne] = 100;
    //DrawCharX[CharacterOne] = 100;
    //PosCharX[CharacterTwo] = 400;
    //DrawCharX[CharacterTwo] = 400;


    CurrentChar = CharacterOne;

    do{
    PosCharX[CurrentChar] = BackGroundHeaderData.StartPositionX[CurrentChar];
    PosCharY[CurrentChar] = StageGround-CharacterTextureSizeDrawn;

    ButtonInputAllowed[CurrentChar] = 1;
    ReleaseButton[CurrentChar] = 0; // 0 = Idle condition. Live with it.
    AnimationTicks[CurrentChar] = 1; // Constantly running from 1 to 60. I think it's preferable to use ticks generated from the game code rather than from the timer inside the console.
    DirectionalInputAllowed[CurrentChar] = 1;
    ButtonInputAllowed[CurrentChar] = 1;
    AnimationStrength[CurrentChar] = 0; // Strength of Attacks
    AnimationEnemyAccelerationX[CurrentChar] = 0;
    AnimationEnemyAccelerationY[CurrentChar] = 0;
    TemporaryAnimationID[CurrentChar] = 0;
    CharHitAcceleration[CurrentChar] = 0;
    CharHitDuration[CurrentChar] = 0;
    GroundLevel[CurrentChar] = 1; // Is the character on the ground?
    JumpDirection[CurrentChar] = 0; //Where does the char jump?
    JumpVelocity[CurrentChar] = -480; //Just the Acceleration. -480 equals an idle position
    JumpBlock[CurrentChar] = 0; //Decides wether the character is allowed to jump.
    CrouchPosition[CurrentChar] = 0; // What Stage of Crouching. 0 = Nothing; 1 = Going into crouch; 2 = Crouch

    CharHealth[CurrentChar] = StartHealth[CurrentChar];
    //CharHealth[CurrentChar] = 1;

    CharHitStatus[CurrentChar] = 0; // What kind of hit did the char receive? 4 = HIT(?) 5= Getting Up 6 = Getting Thrown
    HitPositionX[CurrentChar] = 0;
    HitPositionY[CurrentChar] = 0;
    AnimationValidityCheck[CurrentChar] = 0;
    WhichSpecial[CurrentChar] = 0;
    SpecialAnimationFrame[CurrentChar] = 0;
    SpecialAnimationFrameAmount[CurrentChar] = 0;
    SpecialAnimationTicks[CurrentChar] = 0; 
    SpecialAnimationDuration[CurrentChar] = 0;
    SpecialCharChangeX[CurrentChar] = 0;
    SpecialCharChangeY[CurrentChar] = 0;
    SpecialCharAnimation[CurrentChar] = 0;
    SpecialCharAlignment[CurrentChar] = 0; //Deals with both the Enemy Animation during Throws and the kind of throwback during Combos
    SpecialOffset[CurrentChar] = 0;
    CharIsLeft[CurrentChar] = 1;
    ComboMovementX[CurrentChar] = 0;
    ComboMovementY[CurrentChar] = 0;

    if(SpecialEffect[CurrentChar]) pvr_mem_free(SpecialEffectTexture[CurrentChar]);

    SpecialEffect[CurrentChar] = 0;
    SpecialEffectPosX[CurrentChar] = 0;
    SpecialEffectPosY[CurrentChar] = 0;
    SpecialEffectDrawX[CurrentChar] = 0;
    SpecialEffectDrawY[CurrentChar] = 0;
    SpecialEffectSpeedX[CurrentChar] = 0;
    SpecialEffectSpeedY[CurrentChar] = 0;
    SpecialEffectSizeX[CurrentChar] = 0;
    SpecialEffectSizeY[CurrentChar] = 0;
    SpecialEffectRange[CurrentChar] = 0; //Gets substracted every pixel moved until it is zero.
    SpecialEffectStrength[CurrentChar] = 0;
    SpecialEffectAccelerationX[CurrentChar] = 0;
    SpecialEffectAccelerationY[CurrentChar] = 0;
    SpecialEffectWhichFrame[CurrentChar] = 0;
    SpecialEffectStage[CurrentChar] = 0; //0 = Not yet thrown 1 = Before 2 = During(Loop) 3 = Vanish 4 = HIT
    SpecialEffectPosCharRelativity = 0;
    SpecialEffectTextureSizeX[CurrentChar] = 0;
    SpecialEffectTextureSizeY[CurrentChar] = 0;
    SpecialEffectTicks[CurrentChar] = 0;
    SpecialEffectOffset[CurrentChar] = 0;
    //sprintf(SpecialEffectNameBuffer[CurrentChar], "NULLNULL");
    SpecialEffectAnimationSpeed[CurrentChar] = 1;
    SpecialEffectFrameAmount[CurrentChar] = 0;
    SpecialEffectSideEffect[CurrentChar] = CharacterIsNormal;
    SpecialEffectSideEffectDuration[CurrentChar] = 0;
    SpecialEffectHitSoundEffect[CurrentChar] = 0;
    CharHitAnimationSpeed[CurrentChar] = 1;
    EffectTicks[CurrentChar] = 1;
    WhichEffect[CurrentChar] = -1;
    WhichEffectFrame[CurrentChar] = 0;
    MaxDizzy[CurrentChar] = 100; //XXXXXXXXX
    CurrentDizzy[CurrentChar] = 0;
    VictoryAnimationFlag[CurrentChar] = 1; //XXXXXXXXX
    KnockOutAnimationFlag[CurrentChar] = 0; //XXXXXXXXX
    StartAnimationFlag[CurrentChar] = 0; //XXXXXXXXX
    JumpAnimationFlags[CurrentChar] = 0;
    WhichJumpStage[CurrentChar] = 0;
    WhichJumpFrame[CurrentChar] = 0;
    JumpFrameAmount[CurrentChar] = 0;
    JumpTicks[CurrentChar] = 1;
    JumpAnimationSpeed[CurrentChar] = 9;
    //CurrentJumpStage[CurrentChar] = 0;
    JumpLoop[CurrentChar] = 0;
    JumpType[CurrentChar] = 0;
    sprintf(JumpNameBuffer[CurrentChar], "NULLNULL"); 
    ComboID[CurrentChar] = 0;
    ComboChecker[CurrentChar] = 0;
    DirectionalComboChecker[CurrentChar] = 0;
    AnimationAddOn[CurrentChar] = 0;

    CharacterStatusAilment[CurrentChar] = CharacterIsNormal;
    StatusAilmentDuration[CurrentChar] = 0;

    ResetToStance[CurrentChar] = 0;

    WhichHitSoundEffect[CurrentChar] = 0;
    WhichMissSoundEffect[CurrentChar] = 0;
    WhichSoundEffectFrame[CurrentChar] = 0;

    WhichAIPattern[CurrentChar] = 0;
    TimeSlotLength[CurrentChar] = 1;
    TimeSlotTicks[CurrentChar] = 1;
    RandomAINumber[CurrentChar] = 0;


    AnimationID[CurrentChar] = -1;

    AnimationSpeed[CurrentChar] = 1;
    FrameAmount[CurrentChar] = 1;
    AnimationLoop[CurrentChar] = 1;
    AnimationType[CurrentChar] = 1;

    MovementReadCompulsory(0, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
    //AnimationName[CurrentChar] = "STANDING";
    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;

    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);

    #include "NewScreenCalculationCode.c" 

    FightStage = FightFadeInEffect;