


    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);

    DrawCoolStage(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, BackGroundDrawAnimated);

    CurrentChar = CharacterOne;
    do{
    DrawChar(CharacterName[CurrentChar], CharacterTexture[CurrentChar], AnimationBuffer[CurrentChar], WhichAnimationFrame[CurrentChar], DrawCharX[CurrentChar], PosCharY[CurrentChar], CharIsLeft[CurrentChar], CharPalette[CurrentChar], StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn);
    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);

    pvr_list_finish();
    pvr_scene_finish();



    CurrentChar = CharacterOne;
    do{
    if(AnimationTicks[CurrentChar]%AnimationSpeed[CurrentChar] == 0){
    WhichAnimationFrame[CurrentChar]++;
    if(WhichAnimationFrame[CurrentChar] >= FrameAmount[CurrentChar]+1) {
    if(StartAnimationFlag[CurrentChar] == 0) WhichAnimationFrame[CurrentChar] = 1;
    else{
    if(AnimationID[CurrentChar] != -1){
    AnimationID[CurrentChar] = -1;
    MovementReadCompulsory(0, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
    //AnimationName[CurrentChar] = "STANDING";
    WhichAnimationFrame[CurrentChar] = 1;
    AnimationTicks[CurrentChar] = 1;
            }
    }
    }
    }

    AnimationTicks[CurrentChar]++;
    if(AnimationTicks[CurrentChar] == 61){
    AnimationTicks[CurrentChar]=1;
    }

    CurrentChar++;

    } while(CurrentChar <= MaxCharsLoopValue);


    if(StartAnimationFlag[CharacterOne] == 0 && StartAnimationFlag[CharacterTwo] == 0) FightStage = FightRoundAnimation;