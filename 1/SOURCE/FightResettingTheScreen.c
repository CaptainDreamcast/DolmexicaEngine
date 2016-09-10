    //ResettingTheScreen

    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);

    DrawCoolStage(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, BackGroundDrawAnimated);

    CurrentChar = CharacterOne;
    do{
    DrawCharLite(CharacterTexture[CurrentChar], DrawCharX[CurrentChar], PosCharY[CurrentChar], CharIsLeft[CurrentChar], CharPalette[CurrentChar], StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn, CharacterTextureSizeReal[CurrentChar]);
    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);    

    pvr_list_finish();
    pvr_scene_finish();