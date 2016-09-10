    int CoolFightFadeIn(int FightStage, int LeftStageBorder, BackGroundHeaderStruct BackGroundHeaderData, BackGroundStruct BackGroundData[], BackGroundAnimationStruct BackGroundAnimationData[], pvr_ptr_t BackGroundTextures[], char CharacterName[][10], pvr_ptr_t CharacterTexture[], char AnimationBuffer[][10], char WhichAnimationFrame[], int DrawCharX[], int PosCharY[], char CharIsLeft[], PaletteData CharPalette[], int StageGround, int ShadowPositionX, int ShadowPositionY, int CharacterTextureSizeDrawn){

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
    DrawChar(CharacterName[CurrentChar], CharacterTexture[CurrentChar], AnimationBuffer[CurrentChar], WhichAnimationFrame[CurrentChar], DrawCharX[CurrentChar], PosCharY[CurrentChar], CharIsLeft[CurrentChar], CharPalette[CurrentChar], StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn);
    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);

    pvr_list_finish();
    pvr_scene_finish();


    SuperCoolEffectTicks++;

    }

    return(FightStage);

}