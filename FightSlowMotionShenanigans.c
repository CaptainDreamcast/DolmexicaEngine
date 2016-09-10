    if(AnimationTicks[CurrentChar]%AnimationSpeed[CurrentChar] == 0){
    WhichAnimationFrame[CurrentChar]++;
    if(WhichAnimationFrame[CurrentChar] >= FrameAmount[CurrentChar]+1) WhichAnimationFrame[CurrentChar] = FrameAmount[CurrentChar];    
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


    if(WhichCharLost == CurrentChar){
    WhichAnimationFrame[CurrentChar] = FrameAmount[CurrentChar];
    AnimationTicks[CurrentChar] = 1;
    CharHitStatus[CurrentChar] = 5;
    CharHitAcceleration[CurrentChar] = 0;
    }
    else{
    AnimationID[CurrentChar] = -1;
    MovementReadCompulsory(0, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);

    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;
    CharHitStatus[CurrentChar] = 5;
    CharHitAcceleration[CurrentChar] = 0;
    }
    }

    if(AnimationID[CurrentChar] == -(CompulsoryGettingUpIdentifier+1)){

    AnimationID[CurrentChar] = -8;
    MovementReadCompulsory(7, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &CharHitAnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);

    WhichAnimationFrame[CurrentChar] = FrameAmount[CurrentChar];
    AnimationTicks[CurrentChar] = 1;
    }

    AnimationTicks[CurrentChar]++;
    if(AnimationTicks[CurrentChar] == 61){
    AnimationTicks[CurrentChar]=1;
    }


