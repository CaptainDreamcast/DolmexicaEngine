    void FightFadingOut(int LeftStageBorder, BackGroundHeaderStruct BackGroundHeaderData, BackGroundStruct BackGroundData[], BackGroundAnimationStruct BackGroundAnimationData[], pvr_ptr_t BackGroundTextures[], char CharacterName[][10], CharacterTextureStruct CharacterTexture[], char AnimationBuffer[][10], char WhichAnimationFrame[], int DrawCharX[], int PosCharY[], char CharIsLeft[], PaletteData CharPalette[], int StageGround, int ShadowPositionX, int ShadowPositionY, int CharacterTextureSizeDrawn, int CharacterTextureSizeReal[], uint8 DrawCharDifferently[]){

    int EndFightAnimation = 0;
    int SuperCoolEffectTicks = 0;
    int CurrentChar;

    while(EndFightAnimation == 0){

    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);

    DrawCoolStage(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, BackGroundNoDrawAnimated);

    CurrentChar = CharacterOne;
    do{
    DrawCharLiteStandard();    
    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);   

    EndFightAnimation = FadeToBlack(SuperCoolEffectTicks);
    pvr_list_finish();
    pvr_scene_finish();


    SuperCoolEffectTicks++;
    } 
 

    }