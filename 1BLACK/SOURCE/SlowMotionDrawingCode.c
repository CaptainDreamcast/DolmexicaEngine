
    Bluff = BackGroundDrawAnimated;

    for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<SlowDownFactor; DirtyDeedsDoneDirtCheap++){

    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);

    DrawCoolStage(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, Bluff);

    CurrentChar = CharacterOne;
    do{
    DrawChar(CharacterName[CurrentChar], CharacterTexture[CurrentChar], AnimationBuffer[CurrentChar], WhichAnimationFrame[CurrentChar], DrawCharX[CurrentChar], PosCharY[CurrentChar], CharIsLeft[CurrentChar], CharPalette[CurrentChar], StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn);

    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);


    pvr_list_finish();
    pvr_scene_finish();

    Bluff = BackGroundNoDrawAnimated;

    }
