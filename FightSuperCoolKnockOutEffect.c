    //int FightSuperCoolKnockOutEffect(int FightStage, int LeftStageBorder, int RealStageSize, int BackGroundAmountMax, int BackGroundAmount[], int BackGroundScreenPositionX[], int BackGroundScreenPositionY[], int BackGroundTextureSizeX[], int BackGroundTextureSizeY[], int BackGroundScreenSizeX[], int BackGroundScreenSizeY[], int BackGroundUpperLayerSizeX[], int BackGroundLowerLayerSizeX[], int BackGroundUpperLayerPositionZ[], int BackGroundLowerLayerPositionZ[], pvr_ptr_t BackGroundTextures1[], pvr_ptr_t BackGroundTextures2[], pvr_ptr_t BackGroundTextures3[], pvr_ptr_t BackGroundTextures4[], pvr_ptr_t BackGroundTextures5[], char CharacterName[][10], pvr_ptr_t CharacterTexture[], char AnimationBuffer[][10], int WhichAnimationFrame[], int DrawCharX[], int PosCharY[], char CharIsLeft[], int CharHealth[], char RealCharName[][20], char PointArray[][9], PaletteData CharPalette[], int StageGround, int ShadowPositionX, int ShadowPositionY, char FirstTimerValue, char SecondTimerValue){

    DirtyDeedsDoneDirtCheap = 1;

    while(FightStage == FightKnockOutEffect){

    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);

    DrawCoolStage(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, BackGroundNoDrawAnimated);

    DrawAnotherSuperCoolEffect(DirtyDeedsDoneDirtCheap, HitPositionX[WhichCharLost], HitPositionY[WhichCharLost]);
    if(DirtyDeedsDoneDirtCheap%2 == 0) DrawCharX[WhichCharLost] +=5;
    else DrawCharX[WhichCharLost]-=5;

    CurrentChar = CharacterOne;
    do{
    DrawCharStandard();    

    if(WhichEffect[CurrentChar] != -1)    {
    EffectTicks[CurrentChar]++;
    if(EffectTicks[CurrentChar] == 101){
    EffectTicks[CurrentChar] = 1;
    }
    NewDrawEffect(HitEffectTextures[WhichEffect[CurrentChar]][WhichEffectFrame[CurrentChar]], HitEffects[WhichEffect[CurrentChar]][WhichEffectFrame[CurrentChar]], HitPositionX[CurrentChar], HitPositionY[CurrentChar], 1);
    if(EffectTicks[CurrentChar]%(HitEffectSpeed[WhichEffect[CurrentChar]]*5) == 0){
    WhichEffectFrame[CurrentChar]++;
    }
    if(WhichEffectFrame[CurrentChar] == HitEffectFrameAmount[WhichEffect[CurrentChar]]+1){
    WhichEffectFrame[CurrentChar] = 0;
    WhichEffect[CurrentChar] = -1;
    }
    }

    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);

    pvr_list_finish();
    pvr_scene_finish();



    DirtyDeedsDoneDirtCheap++;
    
    if(WhichEffect[CharacterOne] == -1 && WhichEffect[CharacterTwo] == -1 && DirtyDeedsDoneDirtCheap >= 60) FightStage = FightPreKnockOutAnimation;

    if((cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER)) != NULL) {
    st = (cont_state_t *)maple_dev_status(cont);
    if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
    FightStage = FightShutDown;
    Winner = StairWayToHeavenIdentifier;
    }
    }

    }
    
    //return(FightStage);
    //}