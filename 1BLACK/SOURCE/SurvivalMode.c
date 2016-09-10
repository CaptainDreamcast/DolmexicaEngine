int SurvivalMode(int* WhichPlayerActive){

int SurvivalStage;
int SurvivalLoop;

int CurrentChar;
int Bluff;
int OffTo;

int Winner;

uint8 Difficulty;

char EnemiesBeaten[MaxCharsOnScreen][SurvivalModeBeatableEnemyArrayLength];
char CharacterName[MaxCharsOnScreen][9];
char BackGroundName[NormalNameSize];

int CharHealth[MaxCharsOnScreen];
int PlayerID[MaxCharsOnScreen];
char CharIsHuman[MaxCharsOnScreen];

int CharIDCPU[1];
int WhichCharacterFight;

OffTo = 1;

CurrentChar = CharacterOne;
do{


for(SurvivalStage=0; SurvivalStage < SurvivalModeBeatableEnemyArrayLength; SurvivalStage++) EnemiesBeaten[CurrentChar][SurvivalStage] = 0;
sprintf(EnemiesBeaten[CurrentChar], "0");

sprintf(CharacterName[CurrentChar], "NULLNULL");
CharHealth[CurrentChar] = CharHealthMax;
PlayerID[CurrentChar] = -1;
if(CurrentChar == (*WhichPlayerActive)) CharIsHuman[CurrentChar] = 1;
else CharIsHuman[CurrentChar] = 0;

CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);

Difficulty = StandardSurvivalDifficulty;

WhichCharacterFight = 0;
SurvivalLoop = 1;
SurvivalStage = FighterSelectStage;

while(SurvivalLoop){

if(SurvivalStage == FighterSelectStage){
SurvivalStage = NewFighterSelect(SurvivalModeIdentifier, PlayerID, CharIDCPU, &WhichCharacterFight, CharacterName, CharIsHuman, BackGroundName);
}
if(SurvivalStage == FirstTimeCharacterSelectedStage){

CurrentChar = CharacterOne;
do{
for(SurvivalStage=0; SurvivalStage < SurvivalModeBeatableEnemyArrayLength; SurvivalStage++) EnemiesBeaten[CurrentChar][SurvivalStage] = 0;
sprintf(EnemiesBeaten[CurrentChar], "0");
CharHealth[CurrentChar] = CharHealthMax;
CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);

Difficulty = StandardSurvivalDifficulty;
SurvivalStage = WhoAgainstWhoStage;
}
if(SurvivalStage == InbetweenStage){
SurvivalStage = GameOverStage;
//SurvivalCalculateNextFight(PlayerID, CharacterName, CharIsHuman, CharHealth, EnemiesBeaten);
}
if(SurvivalStage == WhoAgainstWhoStage){
SurvivalStage = ActualFightStage;
 }
 if(SurvivalStage == ActualFightStage){
  Winner = -1;
  Winner = NewmalFight(SurvivalModeIdentifier, CharacterName, BackGroundName, CharIsHuman, CharHealth, PlayerID, EnemiesBeaten, &Difficulty);
  //Winner = CharacterOne;
  printf("Winner: (%d)\n", Winner);
  if(Winner == StairWayToHeavenIdentifier) SurvivalStage = FinalExitStage;
  else if(Winner == SelectNewCharacterIdentifier){
  CurrentChar = CharacterOne;
  do{
  if(CharIsHuman[CurrentChar]) PlayerID[CurrentChar] = -1;
  CurrentChar++;
  } while(CurrentChar <= MaxCharsLoopValue);
  SurvivalStage = FighterSelectStage;
  }
  else if(Winner == -1 || CharIsHuman[Winner] == 0) SurvivalStage = GameOverStage;
  else SurvivalStage = InbetweenStage;
  }

 if(SurvivalStage == GameOverStage){

  Winner = GameOverNoDrawPoints;
  Bluff = 0;

  CurrentChar = CharacterOne;
  do{
  if(CharIsHuman[CurrentChar]){ Bluff = CurrentChar; Winner = GameOverDrawPoints;}
  CurrentChar++;
  } while(CurrentChar <= MaxCharsLoopValue);

  SurvivalStage = GameOver(EnemiesBeaten[Bluff], Winner, WhichPlayerActive);
  }

 if(SurvivalStage == FinalExitStage){
  SurvivalLoop = 0;
  }

}

return(OffTo);
}