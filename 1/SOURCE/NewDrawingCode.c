    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);

    //Drawing Stuff
    DrawTimer(NewTimerTexture, TimerHeaderData, TimerCharacterData, FirstTimerValue, SecondTimerValue);
    DrawCoolStage(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, BackGroundDrawAnimated);

    CurrentChar = CharacterOne;
    do{

    DrawArray(RealCharName[CurrentChar], OtherGuiData[CurrentChar].NamePositionX, OtherGuiData[CurrentChar].NamePositionY, LowerGuiPositionZ, OtherGuiData[CurrentChar].NameSizeX, 1);
    if(CharIsHuman[CurrentChar]) DrawArray(PointArray[CurrentChar], OtherGuiData[CurrentChar].ArrayPositionX, OtherGuiData[CurrentChar].ArrayPositionY, LowerGuiPositionZ, OtherGuiData[CurrentChar].ArraySizeX, YellowColor);
    else DrawArray("PRESS START", OtherGuiData[CurrentChar].ArrayPositionX, OtherGuiData[CurrentChar].ArrayPositionY, LowerGuiPositionZ, OtherGuiData[CurrentChar].ArraySizeX, YellowColor);

    DrawLifeBar(CharHealth[CurrentChar], SpecialLeft[CurrentChar], CharWins[CurrentChar], LifeBarData[CurrentChar], LifeBarTexture[CurrentChar], VictoryTexture[CurrentChar]);

    DrawChar(CharacterName[CurrentChar], CharacterTexture[CurrentChar], AnimationBuffer[CurrentChar], WhichAnimationFrame[CurrentChar], DrawCharX[CurrentChar], PosCharY[CurrentChar], CharIsLeft[CurrentChar], CharPalette[CurrentChar], StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn);

    if(WhichEffect[CurrentChar] != -1){
    EffectTicks[CurrentChar]++;
    if(EffectTicks[CurrentChar] == 101){
    EffectTicks[CurrentChar] = 1;
    }
    NewDrawEffect(HitEffectTextures[WhichEffect[CurrentChar]][WhichEffectFrame[CurrentChar]], HitEffects[WhichEffect[CurrentChar]][WhichEffectFrame[CurrentChar]], HitPositionX[CurrentChar], HitPositionY[CurrentChar], HitEffectIsLeft[CurrentChar]);
    if(EffectTicks[CurrentChar]%HitEffectSpeed[WhichEffect[CurrentChar]] == 0){
    WhichEffectFrame[CurrentChar]++;
    }
    if(WhichEffectFrame[CurrentChar] == HitEffectFrameAmount[WhichEffect[CurrentChar]]+1){
    WhichEffectFrame[CurrentChar] = 0;
    WhichEffect[CurrentChar] = -1;
    }
    }

    if(SpecialEffectStage[CurrentChar] != 0){
    DrawSpecialEffect(CharacterName[CurrentChar], SpecialEffectNameBuffer[CurrentChar], SpecialEffectWhichFrame[CurrentChar], SpecialEffectDrawX[CurrentChar], SpecialEffectDrawY[CurrentChar], SpecialEffectSizeX[CurrentChar], SpecialEffectSizeY[CurrentChar], CharIsLeft[CurrentChar], SpecialEffectTexture[CurrentChar]);    
    }

    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);


    pvr_list_finish();
    pvr_scene_finish();
