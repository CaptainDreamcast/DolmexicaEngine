int ArcadeMode(int* WhichPlayerActive, ModifiableOptionStruct* ModifiableOptionData){

int CurrentChar;
int Bluff;

char PointsArray[MaxCharsOnScreen][SurvivalModeBeatableEnemyArrayLength];
char CharacterName[MaxCharsOnScreen][9];
int PlayerID[MaxCharsOnScreen];
int CharHealth[MaxCharsOnScreen];
char CharIsHuman[MaxCharsOnScreen];
char BackGroundName[NormalNameSize];

uint8 Difficulty;


CurrentChar = CharacterOne;
do{

sprintf(PointsArray[CurrentChar], "00000");
sprintf(CharacterName[CurrentChar], "NULLNULL");
CharHealth[CurrentChar] = CharHealthMax;
PlayerID[CurrentChar] = -1;
if(CurrentChar == (*WhichPlayerActive)) CharIsHuman[CurrentChar] = 1;
else CharIsHuman[CurrentChar] = 0;

CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);

int ArcadeLength;

//ArcadeHeaderReadingFunction
ArcadeLength = 8;

int CharIDCPU[ArcadeLength];

CurrentChar = 0;
do{

CharIDCPU[CurrentChar] = -1;

CurrentChar++;
} while(CurrentChar < ArcadeLength);

int Winner = -1;
int WhichCharacterFight = 0;

int OffTo = 1;

int ArcadeLoop = 1;
int ArcadeStage = FighterSelectStage;

Difficulty = ModifiableOptionData->Difficulty;

while(ArcadeLoop == 1){

 if(ArcadeStage == FighterSelectStage){
  ArcadeStage = NewFighterSelect(ArcadeModeIdentifier, PlayerID, CharIDCPU, &WhichCharacterFight, CharacterName, CharIsHuman, BackGroundName);
  if(ArcadeStage == -1) ArcadeStage = ModeNotAvailable();
  printf("First Character: %s\n", CharacterName[CharacterOne]);
  printf("Second Character: %s\n", CharacterName[CharacterTwo]);
  }
 if(ArcadeStage == FirstTimeCharacterSelectedStage){
 ArcadeStage = WhoAgainstWhoStage;
 }
 if(ArcadeStage == InbetweenStage){
  ArcadeStage = ShowArcadeWayToGo(ArcadeLength, PlayerID, CharIDCPU, &WhichCharacterFight, CharacterName, CharIsHuman, BackGroundName);
  }
 if(ArcadeStage == WhoAgainstWhoStage){
  ArcadeStage = WhoAgainstWho(ArcadeModeIdentifier, CharacterName);
  }
 if(ArcadeStage == ActualFightStage){
  Winner = -1;
  Winner = NewmalFight(ArcadeModeIdentifier, CharacterName, BackGroundName, CharIsHuman, CharHealth, PlayerID, PointsArray, &Difficulty, ModifiableOptionData->FirstTimerStartValue, ModifiableOptionData->SecondTimerStartValue);
  //Winner = CharacterOne;
  printf("Winner: (%d)\n", Winner);
  if(Winner == StairWayToHeavenIdentifier) ArcadeStage = FinalExitStage;
  else if(Winner == SelectNewCharacterIdentifier){
  CurrentChar = CharacterOne;
  do{
  if(CharIsHuman[CurrentChar]) PlayerID[CurrentChar] = -1;
  CurrentChar++;
  } while(CurrentChar <= MaxCharsLoopValue);
  ArcadeStage = FighterSelectStage;
  }
  else if(Winner >= NewPlayerJoinsInIdentifier && Winner < NewPlayerJoinsInIdentifier+MaxCharsOnScreen){
  CurrentChar = Winner-NewPlayerJoinsInIdentifier;
  PlayerID[CurrentChar] = -1;
  CharIsHuman[CurrentChar] = 1;
  ArcadeStage = FighterSelectStage;
  }
  else if(Winner == -1 || CharIsHuman[Winner] == 0) ArcadeStage = GameOverStage;
  else ArcadeStage = InbetweenStage;
  }
 if(ArcadeStage == CreditStage){

  if(ArcadePlayEnding(CharacterName[*WhichPlayerActive])) ArcadeStage = CreditFunction();
  else ArcadeStage = FinalExitStage;
  }
 if(ArcadeStage == GameOverStage){

  Winner = GameOverNoDrawPoints;
  Bluff = 0;

  CurrentChar = CharacterOne;
  do{
  if(CharIsHuman[CurrentChar]){ Bluff = CurrentChar; Winner = GameOverDrawPoints;}
  CurrentChar++;
  } while(CurrentChar <= MaxCharsLoopValue);

  ArcadeStage = GameOver(PointsArray[Bluff], Winner, WhichPlayerActive);
  }

 if(ArcadeStage == FinalExitStage){
  ArcadeLoop = 0;
  }
 }
return(OffTo);
}