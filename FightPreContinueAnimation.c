if(CharIsHuman[WhichCharLost] == 1 && CharIsHuman[Winner] == 0) FightStage = FightContinueAnimation;
else{
if(WhichMode == ArcadeModeIdentifier) CharIsHuman[WhichCharLost] = 0;
FightStage = FightShutDown;
}