    //ResettingTheScreen

    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);

    DrawCoolStage(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, BackGroundDrawAnimated);

    CurrentChar = CharacterOne;
    do{
    DrawCharLiteStandard();    
    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);    

    pvr_list_finish();
    pvr_scene_finish();