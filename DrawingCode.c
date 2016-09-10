    pvr_wait_ready();
    pvr_scene_begin();

    /*pvr_list_begin(PVR_LIST_PT_POLY);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    DrawChar1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawChar2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);

    pvr_list_finish();*/
    pvr_list_begin(PVR_LIST_TR_POLY);


    //DebuggingMode
    #include "DebuggingMode.c"

    //Drawing Stuff
    DrawLifeBar(CharHealth1, CharHealth2);
    DrawTimer(FirstTimerValue,SecondTimerValue);
    DrawArray(RealCharName1, 35, 75, LowerGuiPositionZ, 15, 1);
    DrawArray(RealCharName2, 385, 75, LowerGuiPositionZ, 15, 1);
    DrawPoints(PointArray1, PointArray2);
    //DrawShadow(DrawCharX1, PosCharY1, CharWidth1, CharIsLeft1, StageGround);
    //DrawShadow(DrawCharX2, PosCharY2, CharWidth2, CharIsLeft2, StageGround);
    //DrawStage(LeftStageBorder);
    DrawCoolStage(LeftStageBorder, RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);
    DrawChar1(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, DrawCharX1, PosCharY1, CharIsLeft1, CharPalette1, StageGround, ShadowPositionX, ShadowPositionY);
    DrawChar2(CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX2, PosCharY2, CharIsLeft2, CharPalette2, StageGround, ShadowPositionX, ShadowPositionY);

    if(WhichEffect2 != 0)    {
    EffectTicks2++;
    if(EffectTicks2 == 101){
    EffectTicks2 = 1;
    }
    DrawEffect(HitPositionX2, HitPositionY2, WhichEffect2, WhichEffectFrame2);
    if(EffectTicks2%2 == 0){
    WhichEffectFrame2++;
    }
    if(WhichEffectFrame2 == EffectFrameAmount2+1){
    WhichEffectFrame2 = 0;
    EffectFrameAmount2 = 0;
    WhichEffect2 = 0;
    }
    }

    if(WhichEffect1 != 0)    {
    EffectTicks1++;
    if(EffectTicks1 == 101){
    EffectTicks1 = 1;
    }
    DrawEffect(HitPositionX1, HitPositionY1, WhichEffect1, WhichEffectFrame1);
    if(EffectTicks1%2 == 0){
    WhichEffectFrame1++;
    }
    if(WhichEffectFrame1 == EffectFrameAmount1+1){
    WhichEffectFrame1 = 0;
    EffectFrameAmount1 = 0;
    WhichEffect1 = 0;
    }
    }

    if(SpecialEffectStage1 != 0){
    DrawSpecialEffect(CharacterName1, SpecialEffectNameBuffer1, SpecialEffectWhichFrame1, SpecialEffectDrawX1, SpecialEffectDrawY1, SpecialEffectTextureSizeX1, SpecialEffectTextureSizeY1, CharIsLeft1, &SpecialEffectTexture1);    
    }
    if(SpecialEffectStage2 != 0){
    DrawSpecialEffect(CharacterName2, SpecialEffectNameBuffer2, SpecialEffectWhichFrame2, SpecialEffectDrawX2, SpecialEffectDrawY2, SpecialEffectTextureSizeX2, SpecialEffectTextureSizeY2, CharIsLeft2, &SpecialEffectTexture2);    
    }

    //TestDraw();


    pvr_list_finish();
    pvr_scene_finish();
