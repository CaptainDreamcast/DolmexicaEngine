if(VictoryAnimationFlag[WhichCharWon] == 0 && Winner == -1){
FightStage = FightCheckingStuff;
}
else{
    AnimationID[WhichCharWon] = -12;
    MovementReadCompulsory(11, CharacterName[WhichCharWon], AnimationBuffer[WhichCharWon], &AnimationSpeed[WhichCharWon], &FrameAmount[WhichCharWon], &AnimationLoop[WhichCharWon], &AnimationType[WhichCharWon]);
    //AnimationName[WhichCharWon] = "VICTORY1";
    WhichAnimationFrame[WhichCharWon] = 1;
    AnimationTicks[WhichCharWon] = 1;


    while(FightStage == FightVictoryPose){
    
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);

    DrawCoolStage(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, BackGroundDrawAnimated);

    CurrentChar = CharacterOne;
    do{

    DrawCharStandard();    

    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);

    pvr_list_finish();
    pvr_scene_finish();

    if(AnimationTicks[WhichCharWon]%AnimationSpeed[WhichCharWon] == 0){
    WhichAnimationFrame[WhichCharWon]++;
    if(WhichAnimationFrame[WhichCharWon] >= FrameAmount[WhichCharWon]+1){
    WhichAnimationFrame[WhichCharWon] = FrameAmount[WhichCharWon];
    FightStage = FightCheckingStuff;
    }
    }

    AnimationTicks[WhichCharWon]++;
    if(AnimationTicks[WhichCharWon] == 61){
    AnimationTicks[WhichCharWon]=1;
    }

    if((cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER)) != NULL) {
    st = (cont_state_t *)maple_dev_status(cont);
    if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
    FightStage = FightShutDown;
    Winner = StairWayToHeavenIdentifier;
    }
    }

}
}