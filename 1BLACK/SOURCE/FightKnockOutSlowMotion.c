    #include "GeneralScreenCalculationCode.c"    

    CurrentChar = CharacterOne;
    OtherChar = CharacterTwo;
    do{

    #include "PersonalScreenCalculationCode.c"

    //#include "SlowMotionJumpingCode.c"
    #include "NewJumpingCode.c"

    #include "FightSlowMotionShenanigans.c"

    CurrentChar++;
    OtherChar--;
    } while(CurrentChar <= MaxCharsLoopValue);

    #include "SlowMotionDrawingCode.c"

    if((cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER)) != NULL) {
    st = (cont_state_t *)maple_dev_status(cont);
    if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
    FightStage = FightShutDown;
    Winner = StairWayToHeavenIdentifier;
    }
    }

 if(WhichAnimationFrame[CharacterOne] == FrameAmount[CharacterOne] && WhichAnimationFrame[CharacterTwo] == FrameAmount[CharacterTwo]  && GroundLevel[CharacterOne] == 1 && GroundLevel[CharacterTwo] == 1) FightStage = FightVictoryPose;