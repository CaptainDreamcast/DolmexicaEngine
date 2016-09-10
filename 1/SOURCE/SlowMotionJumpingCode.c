    if(GroundLevel[CurrentChar] == 0 && JumpVelocity[CurrentChar] != -480){

    if(JumpVelocity[CurrentChar] <= 1 && JumpVelocity[CurrentChar] >= -1 && WhichJumpStage[CurrentChar] == 2 && ((JumpAnimationFlags[CurrentChar] & 16) != 0)){
    WhichJumpStage[CurrentChar] = 3;
    WhichJumpFrame[CurrentChar] = 1;
    JumpTicks[CurrentChar] = 1;
    }
    if((JumpVelocity[CurrentChar] >= 3) && WhichJumpStage[CurrentChar] == 1 && ((JumpAnimationFlags[CurrentChar] & 128) != 0)){
    WhichJumpStage[CurrentChar] = 2;
    WhichJumpFrame[CurrentChar] = 1;
    JumpTicks[CurrentChar] = 1;
    } 
    if((JumpVelocity[CurrentChar] <=-3) && ((JumpAnimationFlags[CurrentChar] & 4) != 0) && WhichJumpStage[CurrentChar] != 4){
    WhichJumpStage[CurrentChar] = 4;
    WhichJumpFrame[CurrentChar] = 1;
    JumpTicks[CurrentChar] = 1;
    }
    if(JumpVelocity[CurrentChar] > JumpStrength[CurrentChar] && AnimationType[CurrentChar] != 4){
    WhichJumpStage[CurrentChar] = 1;
    PosCharY[CurrentChar] = PosCharY[CurrentChar]+JumpVelocity[CurrentChar]/SlowDownFactor;
    PosCharX[CurrentChar] = PosCharX[CurrentChar]-JumpDirection[CurrentChar]/SlowDownFactor;
    } 
    PosCharY[CurrentChar] = PosCharY[CurrentChar]-JumpVelocity[CurrentChar]/SlowDownFactor;
    PosCharX[CurrentChar] = PosCharX[CurrentChar]+JumpDirection[CurrentChar]/SlowDownFactor;
    JumpVelocity[CurrentChar] -=1;

    if((JumpAnimationSpeed[CurrentChar]*SlowDownFactor)%JumpTicks[CurrentChar] == 0){
    WhichJumpFrame[CurrentChar]++;  
    if(WhichJumpFrame[CurrentChar] > JumpFrameAmount[CurrentChar]){
    if(WhichJumpStage[CurrentChar] == 2 && ((JumpAnimationFlags[CurrentChar] & 64) != 0)){
    WhichJumpStage[CurrentChar] = 4;
    }
    if(WhichJumpStage[CurrentChar] == 2 && ((JumpAnimationFlags[CurrentChar] & 32) != 0)){
    WhichJumpStage[CurrentChar] = 3; 
    }
    if(WhichJumpStage[CurrentChar] == 3 && ((JumpAnimationFlags[CurrentChar] & 2) != 0)){
    WhichJumpStage[CurrentChar] = 4; 
    }
    if(WhichJumpStage[CurrentChar] == 1 && ((JumpAnimationFlags[CurrentChar] & 136) == 0)){
    WhichJumpStage[CurrentChar] = 4; 
    }
    WhichJumpFrame[CurrentChar] = 1;
    JumpTicks[CurrentChar] = 1;    
    }
    }
    

    JumpReadCompulsory(WhichJumpStage[CurrentChar]-1, CharacterName[CurrentChar], JumpNameBuffer[CurrentChar], &JumpAnimationSpeed[CurrentChar], &JumpFrameAmount[CurrentChar], &JumpLoop[CurrentChar], 1);
    
    if(AnimationType[CurrentChar] == 1){
    AnimationID[CurrentChar] = -100-WhichJumpStage[CurrentChar];
    AnimationLoop[CurrentChar] = JumpLoop[CurrentChar];
    FrameAmount[CurrentChar] = JumpFrameAmount[CurrentChar];
    AnimationSpeed[CurrentChar] = JumpAnimationSpeed[CurrentChar];
    for (Bluff=0; Bluff<8; Bluff++) AnimationBuffer[CurrentChar][Bluff] = JumpNameBuffer[CurrentChar][Bluff];
    }
    
    JumpTicks[CurrentChar]++;
    if(JumpTicks[CurrentChar] == 61){
    JumpTicks[CurrentChar]=1;
    }



    if(PosCharY[CurrentChar] >= StageGround-CharacterTextureSizeDrawn && JumpVelocity[CurrentChar] < 0){
        PosCharY[CurrentChar] = StageGround-CharacterTextureSizeDrawn;
        JumpVelocity[CurrentChar] = -480;
        JumpDirection[CurrentChar] = 0;
        GroundLevel[CurrentChar] = 1;
        
        WhichAnimationFrame[CurrentChar] = FrameAmount[CurrentChar];
        JumpLoop[CurrentChar] = 0;
        JumpFrameAmount[CurrentChar] = 0;
        JumpAnimationSpeed[CurrentChar] = 0;
     


        DirectionalInputAllowed[CurrentChar] = 1;
    }

    }