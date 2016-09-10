    CurrentChar = CharacterOne;
    OtherChar = CharacterTwo;

    do{



    if(CharHitStatus[CurrentChar] == 3 || CharHitStatus[CurrentChar] == 2){

    SpecialLeft[OtherChar] += (AnimationStrength[OtherChar]*SpecialMultiplicationFactor);
    if(SpecialLeft[OtherChar] > SpecialBarValueMax) SpecialLeft[OtherChar] = SpecialBarValueMax;
    
    if(AnimationType[OtherChar] == 3 || AnimationType[OtherChar] == 6 || AnimationType[OtherChar] == 8){

    if(CharHitStatus[CurrentChar] == 2){
    if(AnimationID[CurrentChar] != -10 && AnimationID[CurrentChar] != -11){ ButtonInputAllowed[CurrentChar] = 0; ResetToStance[CurrentChar] = 0;}
    if(GroundLevel[CurrentChar] == 1 && CrouchPosition[CurrentChar] == 0 && (CrouchPosition[OtherChar] != 0 || AnimationAddOn[OtherChar] == SweepAddOnIdentifier)) CharHitStatus[CurrentChar] = 3;
    else if(CrouchPosition[CurrentChar] != 0 && (GroundLevel[OtherChar] == 0 || AnimationAddOn[OtherChar] == OverHeadAddOnIdentifier)) CharHitStatus[CurrentChar] = 3;
    else{
    if(CrouchPosition[CurrentChar] == 0){

    AnimationID[CurrentChar] = -10;
    MovementReadCompulsory(9, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &CharHitAnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;


    if(AnimationStrength[OtherChar] >= StrongHitEffectLimit) WhichEffect[CurrentChar] = 5;
    else if(AnimationStrength[OtherChar] >= MediumHitEffectLimit) WhichEffect[CurrentChar] = 4;
    else WhichEffect[CurrentChar] = 3;

    WhichEffectFrame[CurrentChar] = 1;
    EffectTicks[CurrentChar] = 0;

    }
    else{
    AnimationID[CurrentChar] = -11;
    MovementReadCompulsory(10, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &CharHitAnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);

    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;

    CrouchPosition[CurrentChar] = 2;

    if(AnimationStrength[OtherChar] >= StrongHitEffectLimit) WhichEffect[CurrentChar] = 5;
    else if(AnimationStrength[OtherChar] >= MediumHitEffectLimit) WhichEffect[CurrentChar] = 4;
    else WhichEffect[CurrentChar] = 3;

    WhichEffectFrame[CurrentChar] = 1;
    EffectTicks[CurrentChar] = 0;

    }
    CharHitStatus[CurrentChar] = 4;
    }
    }

    UpdateComputerCounters(NeedsMoreCounters, CurrentChar, OtherChar, CharHitStatus, GroundLevel, CrouchPosition, CharIsHuman, Difficulty);


    if(CharHitStatus[CurrentChar] == 3){

    if(AnimationAddOn[OtherChar] == OmniAddOnIdentifier){

    AnimationType[OtherChar] = OmniAttackAnimationIdentifier;
    FirstOmniReadHuman(CharacterName[OtherChar], WhichSpecial[OtherChar], &SpecialOffset[OtherChar], &SpecialAnimationFrameAmount[OtherChar]);

    SpecialAnimationFrame[OtherChar] = 0;
    SpecialAnimationTicks[OtherChar] = 0;
    SpecialAnimationDuration[OtherChar] = 0;

    AnimationID[OtherChar] = -6;
    MovementReadCompulsory(5, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &CharHitAnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
    WhichAnimationFrame[CurrentChar] = 1;
    AnimationSpeed[CurrentChar] = 61;
    AnimationTicks[CurrentChar] = 1;
    CharHitStatus[CurrentChar] = 6; 

    DirectionalInputAllowed[CurrentChar] = 0;

    }
    else{
    if(AnimationEnemyAccelerationY[OtherChar] != 0){
    //if(JumpVelocity[CurrentChar] != -480) JumpVelocity[CurrentChar] += AnimationEnemyAccelerationY[OtherChar];
    //else JumpVelocity[CurrentChar] = AnimationEnemyAccelerationY[OtherChar];
    JumpVelocity[CurrentChar] = AnimationEnemyAccelerationY[OtherChar];
    WhichJumpStage[CurrentChar] = 4;
    GroundLevel[CurrentChar] = 0;
    }


    if(GroundLevel[CurrentChar] == 0){
    CharHealth[CurrentChar] = CharHealth[CurrentChar]-AnimationStrength[OtherChar];
    if(WhichMode == ArcadeModeIdentifier) PointsAdd(PointArray[OtherChar], AnimationStrength[OtherChar], CrouchPosition[OtherChar], CrouchPosition[CurrentChar], GroundLevel[OtherChar], GroundLevel[CurrentChar]);
    if(WhichHitSoundEffect[OtherChar] != 0) snd_sfx_play(CharacterSFX[OtherChar][WhichHitSoundEffect[OtherChar]], VolumeSFX, 128);

    AnimationID[CurrentChar] = -8;
    MovementReadCompulsory(7, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &CharHitAnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);

    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;

    if(AnimationStrength[OtherChar] >= StrongHitEffectLimit) WhichEffect[CurrentChar] = 2;
    else if(AnimationStrength[OtherChar] >= MediumHitEffectLimit) WhichEffect[CurrentChar] = 1;
    else WhichEffect[CurrentChar] = 0;

    WhichEffectFrame[CurrentChar] = 1;
    EffectTicks[CurrentChar] = 0;
    }
    else if(CharHitStatus[CurrentChar] == 3 && CrouchPosition[CurrentChar] != 0){
    CharHealth[CurrentChar] = CharHealth[CurrentChar]-AnimationStrength[OtherChar];
    if(WhichMode == ArcadeModeIdentifier) PointsAdd(PointArray[OtherChar], AnimationStrength[OtherChar], CrouchPosition[OtherChar], CrouchPosition[CurrentChar], GroundLevel[OtherChar], GroundLevel[CurrentChar]);
    if(WhichHitSoundEffect[OtherChar] != 0) snd_sfx_play(CharacterSFX[OtherChar][WhichHitSoundEffect[OtherChar]], VolumeSFX, 128);

    AnimationID[CurrentChar] = -13;
    MovementReadCompulsory(12, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &CharHitAnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);

    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;
    
    CrouchPosition[CurrentChar] = 2;  
    TimeSlotLength[CurrentChar] = 0;

    if(AnimationStrength[OtherChar] >= StrongHitEffectLimit) WhichEffect[CurrentChar] = 2;
    else if(AnimationStrength[OtherChar] >= MediumHitEffectLimit) WhichEffect[CurrentChar] = 1;
    else WhichEffect[CurrentChar] = 0;

    WhichEffectFrame[CurrentChar] = 1;
    EffectTicks[CurrentChar] = 0;
 

    }
    else if(HitPositionY[CurrentChar] < PosCharY[CurrentChar]+CharacterTextureSizeDrawn-CharHeight[CurrentChar]/3){
    if(WhichHitSoundEffect[OtherChar] != 0) snd_sfx_play(CharacterSFX[OtherChar][WhichHitSoundEffect[OtherChar]], VolumeSFX, 128);

    CharHealth[CurrentChar] = CharHealth[CurrentChar]-AnimationStrength[OtherChar];
    if(WhichMode == ArcadeModeIdentifier) PointsAdd(PointArray[OtherChar], AnimationStrength[OtherChar], CrouchPosition[OtherChar], CrouchPosition[CurrentChar], GroundLevel[OtherChar], GroundLevel[CurrentChar]);

    AnimationID[CurrentChar] = -6;
    MovementReadCompulsory(5, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &CharHitAnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;

    if(AnimationStrength[OtherChar] >= StrongHitEffectLimit) WhichEffect[CurrentChar] = 2;
    else if(AnimationStrength[OtherChar] >= MediumHitEffectLimit) WhichEffect[CurrentChar] = 1;
    else WhichEffect[CurrentChar] = 0;

    WhichEffectFrame[CurrentChar] = 1;
    EffectTicks[CurrentChar] = 0;


    }
    else if(HitPositionY[CurrentChar] >= PosCharY[CurrentChar]+CharacterTextureSizeDrawn-CharHeight[CurrentChar]/3){

    if(WhichHitSoundEffect[OtherChar] != 0) snd_sfx_play(CharacterSFX[OtherChar][WhichHitSoundEffect[OtherChar]], VolumeSFX, 128);

    CharHealth[CurrentChar] = CharHealth[CurrentChar]-AnimationStrength[OtherChar];
    if(WhichMode == ArcadeModeIdentifier) PointsAdd(PointArray[OtherChar], AnimationStrength[OtherChar], CrouchPosition[OtherChar], CrouchPosition[CurrentChar], GroundLevel[OtherChar], GroundLevel[CurrentChar]);

    AnimationID[CurrentChar] = -8;
    MovementReadCompulsory(7, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &CharHitAnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);

    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;

    if(AnimationStrength[OtherChar] >= StrongHitEffectLimit) WhichEffect[CurrentChar] = 2;
    else if(AnimationStrength[OtherChar] >= MediumHitEffectLimit) WhichEffect[CurrentChar] = 1;
    else WhichEffect[CurrentChar] = 0;

    WhichEffectFrame[CurrentChar] = 1;
    EffectTicks[CurrentChar] = 0;
 

    }
    CharHitStatus[CurrentChar] = 4;
    }
    }

    if(AnimationEnemyAccelerationX[OtherChar] != 0){
     if(GroundLevel[CurrentChar] == 1){
      AnimationSpeed[CurrentChar] = 61;
      if(CharIsLeft[OtherChar] == 1){
       CharHitAcceleration[CurrentChar] = AnimationEnemyAccelerationX[OtherChar];
       HitEffectIsLeft[CurrentChar] = 1;
       }
      else{
       CharHitAcceleration[CurrentChar] = -AnimationEnemyAccelerationX[OtherChar];
       HitEffectIsLeft[CurrentChar] = 0;
       }
      CharHitDuration[CurrentChar] = (AnimationEnemyAccelerationX[OtherChar]/10)+1;
      }
     else{
      AnimationSpeed[CurrentChar] = CharHitAnimationSpeed[CurrentChar];
      CharHitAnimationSpeed[CurrentChar] = 61;
      CharHitDuration[CurrentChar] = 0;
      
      if(CharIsLeft[OtherChar] == 1){
       JumpDirection[CurrentChar] = 0;
       CharHitAcceleration[CurrentChar] = AnimationEnemyAccelerationX[OtherChar];

       }
      if(CharIsLeft[OtherChar] == 0){
       JumpDirection[CurrentChar] = 0;
       CharHitAcceleration[CurrentChar] = -AnimationEnemyAccelerationX[OtherChar];
       } 
      }
    }

    if(AnimationEnemyAccelerationX[OtherChar] == 0){
    AnimationSpeed[CurrentChar] = CharHitAnimationSpeed[CurrentChar];
    }


    if(SpecialEffect[CurrentChar] == 1 && SpecialEffectStage[CurrentChar] == 0) SpecialEffect[CurrentChar] = 0;
    if(CharacterStatusAilment[CurrentChar] == CharacterIsFrozen) CharacterStatusAilment[CurrentChar] = CharacterIsNormal;

    SpecialAnimationFrame[CurrentChar] = 0;
    WhichMissSoundEffect[CurrentChar] = 0;
    AnimationLoop[CurrentChar] = 0;
    AnimationTicks[CurrentChar] = 1;



    DirectionalInputAllowed[CurrentChar] = 0;
    }
    else if(AnimationType[OtherChar] == 5){
    //printf("Attempting Throw!\n");
    //printf("Now Loading: Special #%d.\n", WhichSpecial[OtherChar]);
    FirstSpecialReadHuman(CharacterName[OtherChar], AnimationBuffer[OtherChar], &FrameAmount[OtherChar], &AnimationType[OtherChar], WhichSpecial[OtherChar], &SpecialOffset[OtherChar]);
    //printf("First Offset: %ld.\n", SpecialOffset[OtherChar]);
    WhichAnimationFrame[OtherChar] = 1;
    AnimationTicks[OtherChar] = 1;
    SpecialAnimationFrame[OtherChar] = 0;
    DirectionalInputAllowed[OtherChar] = 0;
    AnimationLoop[OtherChar] = 0;

    CharHitStatus[CurrentChar] = 6;

    HitPositionX[CurrentChar] = (ScreenSizeX/2);
    HitPositionY[CurrentChar] = (ScreenSizeY/2);


    JumpVelocity[CurrentChar] = -480;
    SpecialAnimationFrame[CurrentChar] = 0;
    

    }
    else CharHitStatus[CurrentChar] = 0;
 
    }
    else if(CharHitStatus[CurrentChar] == 7 || CharHitStatus[CurrentChar] == 8){ //SHOOTING is fun.

    
    if(SpecialEffectSideEffect[OtherChar] == OmniAttackAnimationIdentifier && CharHitStatus[CurrentChar] == 7){


    AnimationType[OtherChar] = OmniAttackAnimationIdentifier;
    WhichSpecial[OtherChar] = SpecialEffectSideEffectDuration[OtherChar];
    FirstOmniReadHuman(CharacterName[OtherChar], WhichSpecial[OtherChar], &SpecialOffset[OtherChar], &SpecialAnimationFrameAmount[OtherChar]);

    SpecialAnimationFrame[OtherChar] = 0;
    SpecialAnimationTicks[OtherChar] = 0;
    SpecialAnimationDuration[OtherChar] = 0;

    SpecialEffect[OtherChar] = 0;
    SpecialEffectStage[OtherChar] = 0;
    pvr_mem_free(SpecialEffectTexture[OtherChar]);

    AnimationID[CurrentChar] = -6;
    MovementReadCompulsory(5, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &CharHitAnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
    WhichAnimationFrame[CurrentChar] = 1;
    AnimationSpeed[CurrentChar] = 61;
    AnimationTicks[CurrentChar] = 1;
    CharHitStatus[CurrentChar] = 6; 

    DirectionalInputAllowed[CurrentChar] = 0;
    DirectionalInputAllowed[OtherChar] = 0;

    }
    else{

    if(CharHitStatus[CurrentChar] == 7){
    CharHealth[CurrentChar] = CharHealth[CurrentChar]-SpecialEffectStrength[OtherChar];
    if(WhichMode == ArcadeModeIdentifier) PointsAdd(PointArray[OtherChar], SpecialEffectStrength[OtherChar], CrouchPosition[OtherChar], CrouchPosition[CurrentChar], GroundLevel[OtherChar], GroundLevel[CurrentChar]);

    if(SpecialEffectHitSoundEffect[OtherChar] != 0) snd_sfx_play(CharacterSFX[OtherChar][SpecialEffectHitSoundEffect[OtherChar]], VolumeSFX, 128);

    if(SpecialEffectAccelerationY[OtherChar] != 0){

    JumpVelocity[CurrentChar] = SpecialEffectAccelerationY[OtherChar];
    WhichJumpStage[CurrentChar] = 4;
    GroundLevel[CurrentChar] = 0;
    }

    if(SpecialEffectSideEffect[OtherChar] == CharacterIsNormal){
    AnimationID[CurrentChar] = -6;
    MovementReadCompulsory(5, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &CharHitAnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);

    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;
    CharHitStatus[CurrentChar] = GettingHitIdentifier; 
    }
    else if(SpecialEffectSideEffect[OtherChar] == CharacterIsFrozen){
    CharacterStatusAilment[CurrentChar] = SpecialEffectSideEffect[OtherChar];
    StatusAilmentDuration[CurrentChar] = SpecialEffectSideEffectDuration[OtherChar];
    AnimationSpeed[CurrentChar] = 61;
    CharHitAnimationSpeed[CurrentChar] = 61;
    AnimationType[CurrentChar] = GettingHitIdentifier;
    CharHitStatus[CurrentChar] = RecoveryIdentifier; 

    //WhichAIPattern[CurrentChar] = 0; TimeSlotTicks[CurrentChar] = 1; TimeSlotLength[CurrentChar] = 2; //TimeSlotLength[CurrentChar] = StatusAilmentDuration[CurrentChar];

    }
    }
    else{

    if(CrouchPosition[CurrentChar] == 0){

    AnimationID[CurrentChar] = -10;
    MovementReadCompulsory(9, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &CharHitAnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;
    }
    else{
    AnimationID[CurrentChar] = -11;
    MovementReadCompulsory(10, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &CharHitAnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;
    CrouchPosition[CurrentChar] = 2;
    }
    CharHitStatus[CurrentChar] = GettingHitIdentifier; 

    }


    if(SpecialEffectAccelerationX[OtherChar] != 0){
     if(GroundLevel[CurrentChar] == 1){
      AnimationSpeed[CurrentChar] = 61;
      if(CharIsLeft[OtherChar] == 1){
       CharHitAcceleration[CurrentChar] = SpecialEffectAccelerationX[OtherChar];
       HitEffectIsLeft[CurrentChar] = 1;
       }
      if(CharIsLeft[OtherChar] == 0){
       CharHitAcceleration[CurrentChar] = -SpecialEffectAccelerationX[OtherChar];
       HitEffectIsLeft[CurrentChar] = 0;
       }
      CharHitDuration[CurrentChar] = (SpecialEffectAccelerationX[OtherChar]/10)+1;
      }
     else{
      AnimationSpeed[CurrentChar] = CharHitAnimationSpeed[CurrentChar];
      CharHitAnimationSpeed[CurrentChar] = 61;
      CharHitDuration[CurrentChar] = 0;
      
      if(CharIsLeft[OtherChar] == 1){
       JumpDirection[CurrentChar] = 0;
       CharHitAcceleration[CurrentChar] = SpecialEffectAccelerationX[OtherChar];

       }
      if(CharIsLeft[OtherChar] == 0){
       JumpDirection[CurrentChar] = 0;
       CharHitAcceleration[CurrentChar] = -SpecialEffectAccelerationX[OtherChar];
       } 
      }
    }

    if(SpecialEffectAccelerationX[OtherChar] == 0){
    AnimationSpeed[CurrentChar] = CharHitAnimationSpeed[CurrentChar];
    }

    HitPositionX[CurrentChar] = (ScreenSizeX/2);
    HitPositionY[CurrentChar] = (ScreenSizeY/2);


    //SpecialEffectSpeedX[OtherChar] = 0; //??????????????????????
    //SpecialEffectSpeedY[OtherChar] = 0; //??????????????????????

    SpecialEffectReadHuman(CharacterName[OtherChar], SpecialEffectNameBuffer[OtherChar], SpecialEffectOffset[OtherChar]+(sizeof(SpecialEffectStruct)*(SpecialEffectStageHit-1)), &SpecialEffectAnimationSpeed[OtherChar], &SpecialEffectFrameAmount[OtherChar]);   
    SpecialEffectStage[OtherChar] = 4;
    SpecialEffectTicks[OtherChar] = 1;
    SpecialEffectWhichFrame[OtherChar] = 1;

    
    AnimationLoop[CurrentChar] =0;
    AnimationTicks[CurrentChar] = 1;
    SpecialAnimationFrame[CurrentChar] = 0;

    DirectionalInputAllowed[CurrentChar] = 0;
    }
    }

    if (CharHealth[CurrentChar] < 0){
      CharHealth[CurrentChar] = 0;
     printf("DEAD!\n");
     FightStage = FightKnockOutEffect;
     WhichCharLost = CurrentChar;
     WhichCharWon = OtherChar;
    }

    CurrentChar++;
    OtherChar--;
    } while(CurrentChar <= MaxCharsLoopValue);

