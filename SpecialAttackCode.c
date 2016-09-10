    if(AnimationType[CurrentChar] == 5 && (SpecialAnimationFrame[CurrentChar] != 0 || CharHitStatus[OtherChar] == 6)){
    if(WhichAnimationFrame[CurrentChar] != SpecialAnimationFrame[CurrentChar]){
    FrameSpecialReadHuman(CharacterName[CurrentChar], SpecialOffset[CurrentChar], &AnimationSpeed[CurrentChar], &AnimationEnemyAccelerationX[CurrentChar], &AnimationEnemyAccelerationY[CurrentChar], AnimationType[CurrentChar], &AnimationStrength[CurrentChar], &SpecialCharChangeX[CurrentChar], &SpecialCharChangeY[CurrentChar], &SpecialCharChangeX[OtherChar], &SpecialCharChangeY[OtherChar], &SpecialCharAlignment[OtherChar], &JumpVelocity[OtherChar], &ComboMovementX[CurrentChar], &ComboMovementY[CurrentChar]);

    if(!CharIsHuman[CurrentChar]){TimeSlotLength[CurrentChar] = AnimationSpeed[CurrentChar]+2; TimeSlotTicks[CurrentChar] = 0;} 

    if(CharIsLeft[CurrentChar] == 1){
    PosCharX[CurrentChar] += SpecialCharChangeX[CurrentChar];
    PosCharX[OtherChar] += SpecialCharChangeX[OtherChar];
    }
    else{
    PosCharX[CurrentChar] -= SpecialCharChangeX[CurrentChar];
    PosCharX[OtherChar] -= SpecialCharChangeX[OtherChar];
    }

    PosCharY[CurrentChar] += SpecialCharChangeY[CurrentChar];
    PosCharY[OtherChar] += SpecialCharChangeY[OtherChar];


    SpecialCharChangeX[CurrentChar] = 0;
    SpecialCharChangeY[CurrentChar] = 0;
    SpecialCharChangeX[OtherChar] = 0;
    SpecialCharChangeY[OtherChar] = 0;
    if(GroundLevel[CurrentChar] == 1 && PosCharY[CurrentChar] < StageGround-CharacterTextureSizeDrawn){
    GroundLevel[CurrentChar] = 0;
    WhichJumpStage[CurrentChar] = 1;
    CrouchPosition[CurrentChar] = 0;
    }
    if(GroundLevel[OtherChar] == 1 && PosCharY[OtherChar] < StageGround-CharacterTextureSizeDrawn){
    GroundLevel[OtherChar] = 0;
    WhichJumpStage[OtherChar] = 1;
    CrouchPosition[OtherChar] = 0;
    }

    SpecialOffset[CurrentChar]+=sizeof(ThrowAttackStruct);
    SpecialAnimationFrame[CurrentChar] = WhichAnimationFrame[CurrentChar];

    if(SpecialCharAlignment[OtherChar] == 1){
    AnimationID[OtherChar] = -6;
    MovementReadCompulsory(5, CharacterName[OtherChar], AnimationBuffer[OtherChar], &CharHitAnimationSpeed[OtherChar], &FrameAmount[OtherChar], &AnimationLoop[OtherChar], &AnimationType[OtherChar]);

    WhichAnimationFrame[OtherChar] = 1;
    AnimationSpeed[OtherChar] = 61;
    AnimationTicks[OtherChar] = 1;
    CharHitStatus[OtherChar] = 6;

    }
    if(SpecialCharAlignment[OtherChar] == 2){

    MovementReadCompulsory(7, CharacterName[OtherChar], AnimationBuffer[OtherChar], &CharHitAnimationSpeed[OtherChar], &FrameAmount[OtherChar], &AnimationLoop[OtherChar], &AnimationType[OtherChar]);

    WhichAnimationFrame[OtherChar] = FrameAmount[OtherChar];
    AnimationSpeed[OtherChar] = 61;
    AnimationTicks[OtherChar] = 1;
    CharHitStatus[OtherChar] = 6;
    AnimationType[OtherChar] = 5;
    }

    if(AnimationEnemyAccelerationX[CurrentChar] != 0 && (PosCharY[OtherChar] < StageGround-CharacterTextureSizeDrawn || AnimationEnemyAccelerationY[CurrentChar] != 0)){

    JumpAnimationSpeed[OtherChar] = 61;
    MovementReadCompulsory(7, CharacterName[OtherChar], AnimationBuffer[OtherChar], &CharHitAnimationSpeed[OtherChar], &FrameAmount[OtherChar], &AnimationLoop[OtherChar], &AnimationType[OtherChar]);



      AnimationSpeed[OtherChar] = CharHitAnimationSpeed[OtherChar];
      CharHitAnimationSpeed[OtherChar] = 61;
      
      if(CharIsLeft[CurrentChar] == 1){
       JumpDirection[OtherChar] = 0;
       CharHitAcceleration[OtherChar] = AnimationEnemyAccelerationX[CurrentChar];
       }
      else{
       JumpDirection[OtherChar] = 0;
       CharHitAcceleration[OtherChar] = -AnimationEnemyAccelerationX[CurrentChar];
       } 

    WhichAnimationFrame[OtherChar] = FrameAmount[OtherChar];
    AnimationTicks[OtherChar] = 1;
    CharHitStatus[OtherChar] = 4;
    AnimationType[OtherChar] = 4;
    AnimationEnemyAccelerationX[CurrentChar] = 0;
    CharHealth[OtherChar] = CharHealth[OtherChar]-AnimationStrength[CurrentChar];

    WhichJumpStage[OtherChar] = 4;
    GroundLevel[OtherChar] = 0;
    JumpVelocity[OtherChar] = AnimationEnemyAccelerationY[CurrentChar];
    }
    
    
	}

       }
    if(AnimationType[CurrentChar] == 6 && WhichSpecial[CurrentChar] != 0){
    if(SpecialAnimationFrame[CurrentChar] == 0){
    FirstSpecialReadHuman(CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &FrameAmount[CurrentChar], &AnimationType[CurrentChar], WhichSpecial[CurrentChar], &SpecialOffset[CurrentChar]);
    WhichAnimationFrame[CurrentChar] = 1;
    SpecialAnimationFrame[CurrentChar] = 0;
    DirectionalInputAllowed[CurrentChar] = 0;
    AnimationLoop[CurrentChar] = 0;
    }
    if(SpecialAnimationFrame[CurrentChar] < WhichAnimationFrame[CurrentChar]){
    FrameSpecialReadHuman(CharacterName[CurrentChar], SpecialOffset[CurrentChar], &AnimationSpeed[CurrentChar], &AnimationEnemyAccelerationX[CurrentChar], &AnimationEnemyAccelerationY[CurrentChar], AnimationType[CurrentChar], &AnimationStrength[CurrentChar], &SpecialCharChangeX[CurrentChar], &SpecialCharChangeY[CurrentChar], &SpecialCharChangeX[OtherChar], &SpecialCharChangeY[OtherChar], &SpecialCharAlignment[OtherChar], &JumpVelocity[OtherChar], &ComboMovementX[CurrentChar], &ComboMovementY[CurrentChar]);

    if(!CharIsHuman[CurrentChar]){TimeSlotLength[CurrentChar] = AnimationSpeed[CurrentChar]+2; TimeSlotTicks[CurrentChar] = 0;} 
        
    if(CharIsLeft[CurrentChar] == 1){
    PosCharX[CurrentChar] += SpecialCharChangeX[CurrentChar];
    }
    else{
    PosCharX[CurrentChar] -= SpecialCharChangeX[CurrentChar];
    }
    PosCharY[CurrentChar] += SpecialCharChangeY[CurrentChar];
    SpecialCharChangeX[CurrentChar] = 0;
    SpecialCharChangeY[CurrentChar] = 0;

    if(PosCharY[CurrentChar] < StageGround-CharacterTextureSizeDrawn && GroundLevel[CurrentChar] != 0){
    GroundLevel[CurrentChar] = 0;
    JumpVelocity[CurrentChar] = 0;
    WhichJumpStage[CurrentChar] = 4;
    JumpAnimationFlags[CurrentChar] = JumpIdleUpFlags[CurrentChar];
    JumpType[CurrentChar] = 0;
    WhichJumpFrame[CurrentChar] = 1;
    JumpTicks[CurrentChar] = 1;
    JumpAnimationSpeed[CurrentChar] = 1;
    }
    SpecialOffset[CurrentChar]+=sizeof(CoolerAttackStruct);
    SpecialAnimationFrame[CurrentChar] = WhichAnimationFrame[CurrentChar];    
    } 
    if(CharIsLeft[CurrentChar] == 1){
    PosCharX[CurrentChar] += ComboMovementX[CurrentChar];
    }
    else{
    PosCharX[CurrentChar] -= ComboMovementX[CurrentChar];
    }  
    PosCharY[CurrentChar] += ComboMovementY[CurrentChar];
    }

    if(SpecialEffectStage[CurrentChar] != 0){
    SpecialEffectPosX[CurrentChar] += SpecialEffectSpeedX[CurrentChar];
    SpecialEffectPosY[CurrentChar] += SpecialEffectSpeedY[CurrentChar];
    SpecialEffectRange[CurrentChar] -= SpecialEffectSpeedX[CurrentChar];
    if(SpecialEffectStage[CurrentChar] == 2 && ((SpecialEffectRange[CurrentChar] <= 0 && SpecialEffectSpeedX[CurrentChar] >= 0) ||(SpecialEffectRange[CurrentChar] >= 0 && SpecialEffectSpeedX[CurrentChar] <= 0))){
    SpecialEffectReadHuman(CharacterName[CurrentChar], SpecialEffectNameBuffer[CurrentChar], SpecialEffectOffset[CurrentChar]+sizeof(SpecialEffectStruct)*(SpecialEffectStageVanish-1), &SpecialEffectAnimationSpeed[CurrentChar], &SpecialEffectFrameAmount[CurrentChar]);   
    SpecialEffectStage[CurrentChar] = 3;
    SpecialEffectWhichFrame[CurrentChar] = 1;
    SpecialEffectTicks[CurrentChar] = 1;    
    }

    }
    if(AnimationType[CurrentChar] == 7){

    if(SpecialEffect[CurrentChar] == 0){
    FirstSpecialEffectReadHuman(CharacterName[CurrentChar], WhichSpecial[CurrentChar], &SpecialEffectOffset[CurrentChar], &SpecialEffectSizeX[CurrentChar], &SpecialEffectSizeY[CurrentChar], &SpecialEffectPosX[CurrentChar], &SpecialEffectPosY[CurrentChar], &SpecialEffectPosCharRelativity, &SpecialEffectWhichFrame[CurrentChar], &SpecialEffectRange[CurrentChar], &SpecialEffectSpeedX[CurrentChar], &SpecialEffectSpeedY[CurrentChar], &SpecialEffectSideEffect[CurrentChar], &SpecialEffectSideEffectDuration[CurrentChar], &SpecialEffectHitSoundEffect[CurrentChar]);
    SpecialEffect[CurrentChar] = 1;
    SpecialEffectStage[CurrentChar] = 0;
    SpecialEffectStrength[CurrentChar] = AnimationStrength[CurrentChar];
    SpecialEffectAccelerationX[CurrentChar] = AnimationEnemyAccelerationX[CurrentChar];
    SpecialEffectAccelerationY[CurrentChar] = AnimationEnemyAccelerationY[CurrentChar];


    if((SpecialEffectSpeedX[CurrentChar] < 0 && CharIsLeft[CurrentChar] == 1) || (SpecialEffectSpeedX[CurrentChar] > 0 && CharIsLeft[CurrentChar] == 0)){
    SpecialEffectRange[CurrentChar] = -SpecialEffectRange[CurrentChar];
    }
    if(CharIsLeft[CurrentChar] == 0){
    SpecialEffectSpeedX[CurrentChar] = -SpecialEffectSpeedX[CurrentChar];
    }
    printf("Special Effect Position: %d/%d\n", SpecialEffectPosX[CurrentChar], SpecialEffectPosY[CurrentChar]);
  


    if(SpecialEffectPosCharRelativity == 1 && CharIsLeft[CurrentChar] == 1){
    SpecialEffectPosX[CurrentChar] = DrawCharX[CurrentChar]+LeftStageBorder+SpecialEffectPosX[CurrentChar];
    SpecialEffectPosY[CurrentChar] = PosCharY[CurrentChar]+SpecialEffectPosY[CurrentChar];
    }
    if(SpecialEffectPosCharRelativity == 1 && CharIsLeft[CurrentChar] == 0){
    SpecialEffectPosX[CurrentChar] = DrawCharX[CurrentChar]+LeftStageBorder+CharacterTextureSizeDrawn-SpecialEffectPosX[CurrentChar]-(SpecialEffectSizeX[CurrentChar]);
    SpecialEffectPosY[CurrentChar] = PosCharY[CurrentChar]+SpecialEffectPosY[CurrentChar];
    }
    if(SpecialEffectPosCharRelativity == 0){
    SpecialEffectPosX[CurrentChar] = LeftStageBorder+SpecialEffectPosX[CurrentChar];
    }

    }
    //printf("AnimationFrame: %d\n", WhichAnimationFrame[CurrentChar]);
    //printf("SpecialEffect[CurrentChar]: %d\n", SpecialEffect[CurrentChar]);
    //printf("SpecialEffectWhichFrame[CurrentChar]: %d\n", SpecialEffectWhichFrame[CurrentChar]);
    //printf("SpecialEffectStage[CurrentChar]: %d\n", SpecialEffectStage[CurrentChar]);
    if(SpecialEffect[CurrentChar] == 1 && WhichAnimationFrame[CurrentChar] == SpecialEffectWhichFrame[CurrentChar] && SpecialEffectStage[CurrentChar] == 0){
    //printf("Loading Special Effect\n");
    SpecialEffectReadHuman(CharacterName[CurrentChar], SpecialEffectNameBuffer[CurrentChar], SpecialEffectOffset[CurrentChar], &SpecialEffectAnimationSpeed[CurrentChar], &SpecialEffectFrameAmount[CurrentChar]);
    //SpecialEffectReadHuman(CharacterName[CurrentChar], SpecialEffectNameBuffer[CurrentChar], SpecialEffectOffset[CurrentChar], &SpecialEffectAnimationSpeed[CurrentChar], &SpecialEffectFrameAmount[CurrentChar]);
    SpecialEffectStage[CurrentChar] = 1;
    SpecialEffectWhichFrame[CurrentChar] = 1;
    SpecialEffectTicks[CurrentChar] = 1;

    SpecialEffectTexture[CurrentChar] = pvr_mem_malloc(2*2*2);
    }      
    }
    if(AnimationType[CurrentChar] == 8 && WhichSpecial[CurrentChar] != 0){

    if((SpecialAnimationFrame[CurrentChar] == 0) || (ComboChecker[CurrentChar] == 1 && WhichAnimationFrame[CurrentChar] >= FrameAmount[CurrentChar] && AnimationTicks[CurrentChar]%AnimationSpeed[CurrentChar] == 0)){
    ComboReadHuman(AnimationID[CurrentChar], CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationEnemyAccelerationX[CurrentChar], &AnimationEnemyAccelerationY[CurrentChar], &AnimationType[CurrentChar], &AnimationStrength[CurrentChar], &WhichSpecial[CurrentChar], &ComboID[CurrentChar], &SpecialCharChangeX[CurrentChar], &SpecialCharChangeY[CurrentChar], &WhichMissSoundEffect[CurrentChar], &WhichHitSoundEffect[CurrentChar], &WhichSoundEffectFrame[CurrentChar]);
    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;
    ComboChecker[CurrentChar] = 0;
    SpecialAnimationFrame[CurrentChar]++;
    
    if(CharIsLeft[CurrentChar] == 1){
    PosCharX[CurrentChar] += SpecialCharChangeX[CurrentChar];
    }
    else{
    PosCharX[CurrentChar] -= SpecialCharChangeX[CurrentChar];
    }
    PosCharY[CurrentChar] += SpecialCharChangeY[CurrentChar];
    SpecialCharChangeX[CurrentChar] = 0;
    SpecialCharChangeY[CurrentChar] = 0;
    if(PosCharY[CurrentChar] < StageGround-CharacterTextureSizeDrawn){
    GroundLevel[CurrentChar] = 0;
    }
    
    }
    }
    if(AnimationType[CurrentChar] == OmniAttackAnimationIdentifier && WhichSpecial[CurrentChar] != 0){

    SpecialAnimationTicks[CurrentChar]++;
    if(SpecialAnimationTicks[CurrentChar] >= SpecialAnimationDuration[CurrentChar]){

    SpecialAnimationTicks[CurrentChar] = 0;
    SpecialAnimationFrame[CurrentChar]++; 
 
    printf("\n");
    printf("WhichSpecial: (%d)\n", WhichSpecial[CurrentChar]);  
    printf("SpecialAnimationFrame: (%d)\n", SpecialAnimationFrame[CurrentChar]);   
    printf("\n");

    if(SpecialAnimationFrame[CurrentChar] > SpecialAnimationFrameAmount[CurrentChar]){
    AnimationType[CurrentChar] = 1;
    AnimationLoop[CurrentChar] = 0;
    WhichSpecial[CurrentChar] = 0;
    DirectionalInputAllowed[CurrentChar] = 1;
    if(SpecialEffect[CurrentChar]){
    SpecialEffect[CurrentChar] = 0;
    SpecialEffectStage[CurrentChar] = 0;
    pvr_mem_free(SpecialEffectTexture[CurrentChar]);
    }
    }
    else{

    OmniAttackReadHuman
    (CharacterName[CurrentChar], SpecialOffset[CurrentChar], SpecialAnimationFrame[CurrentChar], 
    LeftStageBorder, &PosCharX[CurrentChar], &PosCharY[CurrentChar], &PosCharX[OtherChar], &PosCharY[OtherChar], 
    &WhichAnimationFrame[CurrentChar], &SpecialEffectWhichFrame[CurrentChar], &AnimationTicks[CurrentChar], 
    &SpecialEffectTicks[CurrentChar], &SpecialEffect[CurrentChar], &SpecialEffectStage[CurrentChar], 
    SpecialEffectTexture[CurrentChar], &SpecialAnimationDuration[CurrentChar], &SpecialCharAlignment[OtherChar], 
    AnimationBuffer[CurrentChar], &FrameAmount[CurrentChar], &AnimationSpeed[CurrentChar], 
    SpecialEffectNameBuffer[CurrentChar], &SpecialEffectAnimationSpeed[CurrentChar], 
    &SpecialEffectFrameAmount[CurrentChar], &SpecialEffectSizeX[CurrentChar], &SpecialEffectSizeY[CurrentChar], 
    &SpecialEffectPosCharRelativity, &SpecialEffectPosX[CurrentChar], 
    &SpecialEffectPosY[CurrentChar], &SpecialEffectRange[CurrentChar], &SpecialEffectSpeedX[CurrentChar], 
    &SpecialEffectSpeedY[CurrentChar], &SpecialCharChangeX[CurrentChar], &SpecialCharChangeY[CurrentChar], 
    &SpecialCharChangeX[OtherChar], &SpecialCharChangeY[OtherChar], &ComboMovementX[CurrentChar], 
    &ComboMovementY[CurrentChar], &ComboMovementX[OtherChar], &ComboMovementY[OtherChar], 
    &AnimationEnemyAccelerationX[CurrentChar], &AnimationEnemyAccelerationY[CurrentChar], &AnimationStrength[CurrentChar], CharIsLeft[CurrentChar]);

    //?????????????
    DirectionalInputAllowed[CurrentChar] = 0;
    //?????????????

    if(CharIsLeft[CurrentChar] == 1) PosCharX[CurrentChar] += SpecialCharChangeX[CurrentChar];
    else PosCharX[CurrentChar] -= SpecialCharChangeX[CurrentChar];
    PosCharY[CurrentChar] += SpecialCharChangeY[CurrentChar];
 
    if(CharIsLeft[OtherChar] == 0) PosCharX[OtherChar] += SpecialCharChangeX[OtherChar];
    else PosCharX[OtherChar] -= SpecialCharChangeX[OtherChar];
    PosCharY[OtherChar] += SpecialCharChangeY[OtherChar];

    if(SpecialCharAlignment[OtherChar] == 1){
    AnimationID[OtherChar] = -6;
    MovementReadCompulsory(5, CharacterName[OtherChar], AnimationBuffer[OtherChar], &CharHitAnimationSpeed[OtherChar], &FrameAmount[OtherChar], &AnimationLoop[OtherChar], &AnimationType[OtherChar]);
    WhichAnimationFrame[OtherChar] = 1;
    AnimationSpeed[OtherChar] = 61;
    AnimationTicks[OtherChar] = 1;
    CharHitStatus[OtherChar] = 6;
    }
    else if(SpecialCharAlignment[OtherChar] == 2){
    MovementReadCompulsory(7, CharacterName[OtherChar], AnimationBuffer[OtherChar], &CharHitAnimationSpeed[OtherChar], &FrameAmount[OtherChar], &AnimationLoop[OtherChar], &AnimationType[OtherChar]);
    WhichAnimationFrame[OtherChar] = FrameAmount[OtherChar];
    AnimationSpeed[OtherChar] = 61;
    AnimationTicks[OtherChar] = 1;
    CharHitStatus[OtherChar] = 6;
    AnimationType[OtherChar] = 5;
    }

    if(CharIsLeft[CurrentChar] == 0) SpecialEffectSpeedX[CurrentChar] = -SpecialEffectSpeedX[CurrentChar];

    if(SpecialEffectPosCharRelativity == 1 && CharIsLeft[CurrentChar] == 1){
    SpecialEffectPosX[CurrentChar] = DrawCharX[CurrentChar]+LeftStageBorder+SpecialEffectPosX[CurrentChar];
    SpecialEffectPosY[CurrentChar] = PosCharY[CurrentChar]+SpecialEffectPosY[CurrentChar];
    }
    else if(SpecialEffectPosCharRelativity == 1 && CharIsLeft[CurrentChar] == 0){
    SpecialEffectPosX[CurrentChar] = DrawCharX[CurrentChar]+LeftStageBorder+CharacterTextureSizeDrawn-SpecialEffectPosX[CurrentChar]-(SpecialEffectSizeX[CurrentChar]);
    SpecialEffectPosY[CurrentChar] = PosCharY[CurrentChar]+SpecialEffectPosY[CurrentChar];
    }
    else if(SpecialEffectPosCharRelativity == 0){
    SpecialEffectPosX[CurrentChar] = LeftStageBorder+SpecialEffectPosX[CurrentChar];
    }

    CharHealth[OtherChar] -= AnimationStrength[CurrentChar];
    if(CharHealth[OtherChar] < 0) CharHealth[OtherChar] = 0;

    if(AnimationEnemyAccelerationX[CurrentChar] != 0 || AnimationEnemyAccelerationY[CurrentChar] != 0){
    
    if(AnimationEnemyAccelerationY[CurrentChar] != 0){
    JumpVelocity[OtherChar] = AnimationEnemyAccelerationY[CurrentChar];
    WhichJumpStage[OtherChar] = 4;
    GroundLevel[OtherChar] = 0;
    AnimationEnemyAccelerationY[CurrentChar] = 0;
    }

    MovementReadCompulsory(7, CharacterName[OtherChar], AnimationBuffer[OtherChar], &CharHitAnimationSpeed[OtherChar], &FrameAmount[OtherChar], &AnimationLoop[OtherChar], &AnimationType[OtherChar]);

    WhichAnimationFrame[OtherChar] = FrameAmount[OtherChar];
    AnimationSpeed[OtherChar] = 61;
    AnimationTicks[OtherChar] = 1;
    CharHitStatus[OtherChar] = 4;

    if(CharIsLeft[CurrentChar]) CharHitAcceleration[OtherChar] = AnimationEnemyAccelerationX[CurrentChar];
    else CharHitAcceleration[OtherChar] = -AnimationEnemyAccelerationX[CurrentChar];
    AnimationEnemyAccelerationX[CurrentChar] = 0;

    CharHealth[OtherChar] = CharHealth[OtherChar]-AnimationStrength[CurrentChar];
    }

    }
    }
    if(CharIsLeft[CurrentChar] == 1) PosCharX[CurrentChar] += ComboMovementX[CurrentChar];
    else PosCharX[CurrentChar] -= ComboMovementX[CurrentChar]; 
    PosCharY[CurrentChar] += ComboMovementY[CurrentChar];  
   
    if(CharIsLeft[OtherChar] == 0) PosCharX[OtherChar] += ComboMovementX[OtherChar];
    else PosCharX[OtherChar] -= ComboMovementX[OtherChar]; 
    PosCharY[OtherChar] += ComboMovementY[OtherChar];   
       
    }