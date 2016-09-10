    if(FirstTimerValue != 10){
    TimerTicks++;
    if(TimerTicks%TimerSpeed == 0){
    TimerTicks = 0;
    SecondTimerValue--;
    if(SecondTimerValue < 0){
    FirstTimerValue--;
    SecondTimerValue = 9;
    if(FirstTimerValue < 0){ 
    FirstTimerValue = 0;
    SecondTimerValue = 0;
    FightStage = FightTimeOut;
    }
    }  
    }
    }

    if(PosCharX[CharacterOne]-LeftStageBorder < BackGroundHeaderData.ScrollingLeftPositionX && PosCharX[CharacterTwo]-LeftStageBorder < BackGroundHeaderData.ScrollingLeftPositionX && LeftStageBorder > 0){
    //<190

    if(LeftStageBorder-BackGroundHeaderData.ScrollSpeedX < 0) Bluff = LeftStageBorder;
    else Bluff = BackGroundHeaderData.ScrollSpeedX;

    LeftStageBorder -= Bluff;
    DrawCharX[CharacterOne] += Bluff;
    DrawCharX[CharacterTwo] += Bluff;
    if(WhichEffect[CharacterOne] != -1) HitPositionX[CharacterOne]+= Bluff;
    if(WhichEffect[CharacterTwo] != -1) HitPositionX[CharacterTwo]+= Bluff;
    }

    if(PosCharX[CharacterOne]-LeftStageBorder > BackGroundHeaderData.ScrollingRightPositionX && PosCharX[CharacterTwo]-LeftStageBorder > 380 && LeftStageBorder < BackGroundHeaderData.RealStageSize-ScreenSizeX){
    //>380

    if(LeftStageBorder+BackGroundHeaderData.ScrollSpeedX > (BackGroundHeaderData.RealStageSize-ScreenSizeX)) Bluff = (BackGroundHeaderData.RealStageSize-ScreenSizeX)-LeftStageBorder;
    else Bluff = BackGroundHeaderData.ScrollSpeedX;

    LeftStageBorder += Bluff;
    DrawCharX[CharacterOne] -= Bluff;
    DrawCharX[CharacterTwo] -= Bluff;
    if(WhichEffect[CharacterOne] != -1) HitPositionX[CharacterOne]-= Bluff;
    if(WhichEffect[CharacterTwo] != -1) HitPositionX[CharacterTwo]-= Bluff;    
    }