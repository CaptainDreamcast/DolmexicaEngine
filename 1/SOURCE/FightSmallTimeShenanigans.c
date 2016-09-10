

    if(AnimationTicks[CurrentChar]%AnimationSpeed[CurrentChar] == 0){
    WhichAnimationFrame[CurrentChar]++;


    if(WhichAnimationFrame[CurrentChar] >= FrameAmount[CurrentChar]+1 && AnimationLoop[CurrentChar] == 1){
    WhichAnimationFrame[CurrentChar] = 1;
    
    }

    if(WhichAnimationFrame[CurrentChar] >= FrameAmount[CurrentChar]+1 && AnimationLoop[CurrentChar] == 0){

    if(GroundLevel[CurrentChar] == 1 && CrouchPosition[CurrentChar] == 0 && CharHitStatus[CurrentChar] != 4){
    
    //MovementReadCompulsory(0, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
    //AnimationName[CurrentChar] = AnimationBuffer[CurrentChar];    
    DirectionalInputAllowed[CurrentChar] = 1;
    MovementReadCompulsory(0, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
    //AnimationName[CurrentChar] = "STANDING";
    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;
    AnimationID[CurrentChar] = -1;

    CharHitStatus[CurrentChar] = 0;
    ComboMovementX[CurrentChar] = 0;
    ComboMovementY[CurrentChar] = 0;
    }

    if(GroundLevel[CurrentChar] == 1 && CrouchPosition[CurrentChar] != 0){
    AnimationID[CurrentChar] = -5;
    MovementReadCompulsory(4, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
    //AnimationName[CurrentChar] = "CROU_DUR";
    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;

    CharHitStatus[CurrentChar] = 0;
    ComboMovementX[CurrentChar] = 0;
    ComboMovementY[CurrentChar] = 0;
    }
    if(GroundLevel[CurrentChar] == 0){
    if(CharHitStatus[CurrentChar] != 4){
    AnimationType[CurrentChar] = 1;
    WhichAnimationFrame[CurrentChar] = 1;
    AnimationSpeed[CurrentChar] = 61;
    FrameAmount[CurrentChar] = 1;
    AnimationLoop[CurrentChar] =1;
    AnimationTicks[CurrentChar] = 1;
    AnimationID[CurrentChar] = 0;
    CharHitStatus[CurrentChar] = 0;
    ComboMovementX[CurrentChar] = 0;
    ComboMovementY[CurrentChar] = 0;
    }
    else{
    WhichAnimationFrame[CurrentChar] = FrameAmount[CurrentChar];
    AnimationSpeed[CurrentChar] = 61;
    }
    }

    }


    }
    AnimationTicks[CurrentChar]++;
    if(AnimationTicks[CurrentChar] == 61){
    AnimationTicks[CurrentChar]=1;
    }


    if(CharHitAcceleration[CurrentChar] != 0){
    if(WhichAnimationFrame[CurrentChar] < FrameAmount[CurrentChar] && AnimationTicks[CurrentChar]%CharHitAnimationSpeed[CurrentChar] == 0 ){
    WhichAnimationFrame[CurrentChar]++;
    }
    PosCharX[CurrentChar] += CharHitAcceleration[CurrentChar];

    if(PosCharX[CurrentChar]+CharWidth[CurrentChar] > LeftStageBorder+ScreenSizeX){
    if(LeftStageBorder+ScreenSizeX+CharHitAcceleration[CurrentChar] > BackGroundHeaderData.RealStageSize){ 
    PosCharX[CurrentChar] = BackGroundHeaderData.RealStageSize-CharWidth[CurrentChar]; 
    PosCharX[OtherChar] -= ((LeftStageBorder+ScreenSizeX+(CharHitAcceleration[CurrentChar]/PushBackFactor))-BackGroundHeaderData.RealStageSize); 
    LeftStageBorder = BackGroundHeaderData.RealStageSize-ScreenSizeX;
    }
    else{
    LeftStageBorder += CharHitAcceleration[CurrentChar]; 
    }
    }
    else if(PosCharX[CurrentChar] < LeftStageBorder){
    if(LeftStageBorder+CharHitAcceleration[CurrentChar] < 0){ 
    PosCharX[CurrentChar] = 0; 
    PosCharX[OtherChar] += (0-(LeftStageBorder+(CharHitAcceleration[CurrentChar]/PushBackFactor))); 
    LeftStageBorder = 0;
    }
    else{
    LeftStageBorder += CharHitAcceleration[CurrentChar]; 
    }
    }
  
    if(GroundLevel[CurrentChar] == 1) DirtyDeedsDoneDirtCheap = CharHitDeAccelerationSpeedGround;
    else DirtyDeedsDoneDirtCheap = CharHitDeAccelerationSpeedAir;
    Bluff = (DirtyDeedsDoneDirtCheap-1);

    if(CharHitAcceleration[CurrentChar] < Bluff) CharHitAcceleration[CurrentChar] += DirtyDeedsDoneDirtCheap;
    else if(CharHitAcceleration[CurrentChar] > Bluff) CharHitAcceleration[CurrentChar] -= DirtyDeedsDoneDirtCheap;
    else CharHitAcceleration[CurrentChar] = 0;


    }

    if(CharHitStatus[CurrentChar] == 4 && CharHitAcceleration[CurrentChar] == 0 && WhichAnimationFrame[CurrentChar] < FrameAmount[CurrentChar] && AnimationTicks[CurrentChar]%CharHitAnimationSpeed[CurrentChar] == 0){
     WhichAnimationFrame[CurrentChar]++;
    }
    
    if(CharHitStatus[CurrentChar] == 4 && CharHitAcceleration[CurrentChar] == 0 && WhichAnimationFrame[CurrentChar] == FrameAmount[CurrentChar] && GroundLevel[CurrentChar] == 1){
    if(AnimationType[CurrentChar] == 1){
    if(GroundLevel[CurrentChar] == 1 && CrouchPosition[CurrentChar] == 0){
    MovementReadCompulsory(9, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
    //AnimationName[CurrentChar] = "BLOCKING";
    AnimationTicks[CurrentChar] = 1;
    AnimationID[CurrentChar] = -10;
    AnimationLoop[CurrentChar] = 0;
    WhichAnimationFrame[CurrentChar] = FrameAmount[CurrentChar];

    CharHitStatus[CurrentChar] = 5;
    CharHitAcceleration[CurrentChar] = 0;
    }
    else{
    MovementReadCompulsory(10, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
    //AnimationName[CurrentChar] = "CROUBLOC";
    AnimationTicks[CurrentChar] = 1;
    AnimationID[CurrentChar] = -11;
    AnimationLoop[CurrentChar] = 0;
    WhichAnimationFrame[CurrentChar] = FrameAmount[CurrentChar];

    CharHitStatus[CurrentChar] = 5;
    CharHitAcceleration[CurrentChar] = 0;
    }
    }
    else if(AnimationID[CurrentChar] == -13){
    AnimationID[CurrentChar] = -14;
    MovementReadCompulsory(13, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
    //AnimationName[CurrentChar] = "BACKLOUP";
    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;
    CharHitStatus[CurrentChar] = 5;
    CharHitAcceleration[CurrentChar] = 0;
    }
    else if(AnimationID[CurrentChar] == -6){
    AnimationID[CurrentChar] = -7;
    MovementReadCompulsory(6, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
    //AnimationName[CurrentChar] = "BACKHIUP";
    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;
    CharHitStatus[CurrentChar] = 5;
    CharHitAcceleration[CurrentChar] = 0;   
    }
    else{
    AnimationID[CurrentChar] = -9;
    MovementReadCompulsory(8, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
    //AnimationName[CurrentChar] = "GETTINUP";
    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;
    CharHitStatus[CurrentChar] = 5;
    CharHitAcceleration[CurrentChar] = 0;
    }
    }


   if(CharHitStatus[CurrentChar] != 4){
    if(CurrentDizzy[CurrentChar] > 0){ 
     CurrentDizzy[CurrentChar]--;
     if(CurrentDizzy[CurrentChar] > MaxDizzy[CurrentChar] && AnimationType[CurrentChar] == 1){
    AnimationID[CurrentChar] = -13;
    MovementReadCompulsory(12, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);

    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;  
    AnimationLoop[CurrentChar] = 1; 
     }
    }
    else if(AnimationType[CurrentChar] == 9 && CurrentDizzy[CurrentChar] == 0){
     AnimationLoop[CurrentChar] = 0;
    }
   }

   if(SpecialEffectStage[CurrentChar] != 0){ 
    if(SpecialEffectTicks[CurrentChar]%SpecialEffectAnimationSpeed[CurrentChar] == 0){
     SpecialEffectWhichFrame[CurrentChar]++;

     if(SpecialEffectWhichFrame[CurrentChar] >= SpecialEffectFrameAmount[CurrentChar]+1){

      if(SpecialEffectStage[CurrentChar] == 1){

       //printf("Now Reading the 2nd stage!\n");
       SpecialEffectReadHuman(CharacterName[CurrentChar], SpecialEffectNameBuffer[CurrentChar], SpecialEffectOffset[CurrentChar]+sizeof(SpecialEffectStruct), &SpecialEffectAnimationSpeed[CurrentChar], &SpecialEffectFrameAmount[CurrentChar]);   
       //printf("Done Reading the 2nd stage! FrameAmount: %d\n", SpecialEffectFrameAmount[CurrentChar]);
       SpecialEffectStage[CurrentChar] = 2;
       SpecialEffectTicks[CurrentChar] = 1;
      }

      if(SpecialEffectStage[CurrentChar] == 3 || SpecialEffectStage[CurrentChar] == 4){
       SpecialEffectStage[CurrentChar] = 0;
       SpecialEffect[CurrentChar] = 0;
       SpecialEffectRange[CurrentChar] = 0;
       pvr_mem_free(SpecialEffectTexture[CurrentChar]);

      }

      SpecialEffectWhichFrame[CurrentChar] = 1;
     }
    
    }

    SpecialEffectTicks[CurrentChar]++;
    if(SpecialEffectTicks[CurrentChar] ==61){
    SpecialEffectTicks[CurrentChar] = 1;

    }



    }