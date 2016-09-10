    int CoolFightFadeIn(int FightStage, int LeftStageBorder, BackGroundHeaderStruct BackGroundHeaderData, BackGroundStruct BackGroundData[], BackGroundAnimationStruct BackGroundAnimationData[], pvr_ptr_t BackGroundTextures[], char CharacterName[][10], CharacterTextureStruct CharacterTexture[], char AnimationBuffer[][10], char WhichAnimationFrame[], int DrawCharX[], int PosCharY[], char CharIsLeft[], PaletteData CharPalette[], int StageGround, int ShadowPositionX, int ShadowPositionY, int CharacterTextureSizeDrawn, uint8 DrawCharDifferently[]){

    int SuperCoolEffectTicks;
    int CurrentChar;

    SuperCoolEffectTicks = 0;

    while(FightStage == FightFadeInEffect){

    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);

    

    DrawCoolStage(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, BackGroundNoDrawAnimated);
    FightStage = DrawSuperCoolEffect(SuperCoolEffectTicks);

    CurrentChar = CharacterOne;
    do{
    DrawCharStandard();    
    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);

    pvr_list_finish();
    pvr_scene_finish();


    SuperCoolEffectTicks++;

    }

    return(FightStage);

}