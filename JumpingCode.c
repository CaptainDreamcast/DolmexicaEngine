    //JUMPING-related code

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
    PosCharY1 = PosCharY1+JumpVelocity1;
    PosCharX1 = PosCharX1-JumpDirection1;
    } 
    PosCharY1 = PosCharY1-JumpVelocity1;
    PosCharX1 = PosCharX1+JumpDirection1;
    JumpVelocity1 -=1;


    if(JumpTicks1%JumpAnimationSpeed1 == 0){
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

    JumpReadCompulsory(WhichJumpStage1-1, CharacterName1, JumpNameBuffer1, &JumpAnimationSpeed1, &JumpFrameAmount1, &JumpLoop1, JumpType1);
    
    if(AnimationType1 == 1){
    AnimationID1 = -100-WhichJumpStage1;
    AnimationLoop1 = JumpLoop1;
    FrameAmount1 = JumpFrameAmount1;
    AnimationSpeed1 = JumpAnimationSpeed1;
    for (i=0; i<8; i++) AnimationBuffer1[i] = JumpNameBuffer1[i];
    WhichAnimationFrame1 = WhichJumpFrame1;
    }
    
    JumpTicks1++;
    if(JumpTicks1 == 61){
    JumpTicks1=1;
    }



    if(PosCharY1 >= StageGround-CharacterTextureSizeDrawn && JumpVelocity1 < 0){
        PosCharY1 = StageGround-CharacterTextureSizeDrawn;
        JumpVelocity1 = -480;
        JumpDirection1 = 0;
        GroundLevel1 = 1;
        if(CharHitStatus1 == 4){
        snd_sfx_play(KnockDownSFX, SoundEffectVolume, 128);
        MovementReadCompulsory(8, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
        //AnimationBuffer1 = "GETTINUP";
        WhichAnimationFrame1 = 1;
        AnimationTicks1 = 1;
        AnimationID1 = -9;
        CharHitStatus1 = 5;
        CharHitAcceleration1 = 0;
        //printf("Check!\n");
        //printf("Name: %s\n", AnimationBuffer1);
        //printf("Speed: %d\n", AnimationSpeed1);
        //printf("Amount: %d\n", FrameAmount1);
        //printf("Loop: %d\n", AnimationLoop1);
        //printf("Type: %d\n", AnimationType1);
        //printf("CharHitStatus: %d\n", CharHitStatus1);
        //printf("Which: %d\n", WhichAnimationFrame1);
        DirectionalInputAllowed1 = 0;
        }
        else{
        if((JumpAnimationFlags1 & 1) != 0){
        //AnimationBuffer1 = "JUMP_REC";
        WhichAnimationFrame1 = 1;
        FrameAmount1 = 4;
        AnimationSpeed1 = 5;
        AnimationLoop1 = 0;
        AnimationTicks1 = 1;
        AnimationType1 = 1;
        }
        else{
        MovementReadCompulsory(0, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
        //AnimationBuffer1 = "STANDING";
        WhichAnimationFrame1 = 1;
        AnimationTicks1 = 1;
        AnimationID1 = -1;
        }
        DirectionalInputAllowed1 = 1;
        }
        JumpLoop1 = 0;
        JumpFrameAmount1 = 0;
        JumpAnimationSpeed1 = 1;


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
    PosCharY2 = PosCharY2+JumpVelocity2;
    PosCharX2 = PosCharX2-JumpDirection2;
    } 
    PosCharY2 = PosCharY2-JumpVelocity2;
    PosCharX2 = PosCharX2+JumpDirection2;
    JumpVelocity2 -=1;

    if(JumpTicks2%JumpAnimationSpeed2 == 0){
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

    JumpReadCompulsory(WhichJumpStage2-1, CharacterName2, JumpNameBuffer2, &JumpAnimationSpeed2, &JumpFrameAmount2, &JumpLoop2, JumpType2);
    
    if(AnimationType2 == 1){
    AnimationID2 = -100-WhichJumpStage2;
    AnimationLoop2 = JumpLoop2;
    FrameAmount2 = JumpFrameAmount2;
    AnimationSpeed2 = JumpAnimationSpeed2;
    for (i=0; i<8; i++) AnimationBuffer2[i] = JumpNameBuffer2[i];
    WhichAnimationFrame2 = WhichJumpFrame2;
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
        if(AnimationType2 == 4){
        snd_sfx_play(KnockDownSFX, SoundEffectVolume, 128);
        MovementReadCompulsory(8, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
        //AnimationBuffer2 = "GETTINUP";
        WhichAnimationFrame2 = 1;
        AnimationTicks2 = 1;
        AnimationID2 = -9;
        DirectionalInputAllowed2 = 0;
        }
        else{
        if((JumpAnimationFlags2 & 1) != 0){
        //AnimationBuffer2 = "JUMP_REC";
        WhichAnimationFrame2 = 1;
        FrameAmount2 = 4;
        AnimationSpeed2 = 5;
        AnimationLoop2 = 0;
        AnimationTicks2 = 1;
        AnimationType2 = 1;
        }
        else{
        MovementReadCompulsory(0, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
        //AnimationBuffer1 = "STANDING";
        WhichAnimationFrame2 = 1;
        AnimationTicks2 = 1;
        AnimationID2 = -1;
        }
        DirectionalInputAllowed2 = 1;
        }
        JumpLoop2 = 0;
        JumpFrameAmount2 = 0;
        JumpAnimationSpeed2 = 0;


    }

    }
