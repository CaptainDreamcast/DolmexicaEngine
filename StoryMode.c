int StoryMode(int* WhichPlayerActive, ModifiableOptionStruct* ModifiableOptionData){

int StoryStage;
int StoryLoop;

int CurrentChar;
int OffTo;

int Winner;

char CharacterName[MaxCharsOnScreen][9];
char PointsArray[MaxCharsOnScreen][SurvivalModeBeatableEnemyArrayLength];
char BackGroundName[NormalNameSize];

int CharHealth[MaxCharsOnScreen];
int PlayerID[MaxCharsOnScreen];
char CharIsHuman[MaxCharsOnScreen];

int CharIDCPU[MaximumStoryModeLength];
int WhichCharacterFight;

int StoryLength;
uint8 Difficulty;


OffTo = 1;

CharIDCPU[0] = -1;

CurrentChar = CharacterOne;
do{

sprintf(CharacterName[CurrentChar], "NULLNULL");
CharHealth[CurrentChar] = CharHealthMax;
PlayerID[CurrentChar] = -1;
if(CurrentChar == (*WhichPlayerActive)) CharIsHuman[CurrentChar] = 1;
else CharIsHuman[CurrentChar] = 0;

CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);

WhichCharacterFight = 0;
StoryLoop = 1;
StoryStage = FighterSelectStage;

Difficulty = ModifiableOptionData->Difficulty;

while(StoryLoop){

if(StoryStage == FighterSelectStage){
StoryStage = NewFighterSelect(StoryModeIdentifier, PlayerID, CharIDCPU, &WhichCharacterFight, CharacterName, CharIsHuman, BackGroundName);
}
if(StoryStage == FirstTimeCharacterSelectedStage){

WhichCharacterFight = 0;
for(CurrentChar=0; CurrentChar<=MaxCharsLoopValue; CurrentChar++) if(CharIsHuman[CurrentChar]) (*WhichPlayerActive) = CurrentChar;
CurrentChar = (*WhichPlayerActive);

StoryStage = StoryModePreFetchTheStory(CharacterName[CurrentChar], &StoryLength);

}
if(StoryStage == InbetweenStage){
if(CharIsHuman[CharacterOne] && CharIsHuman[CharacterTwo]) StoryStage = ActualFightStage;
else StoryStage = UnfoldTheTragedy(WhichPlayerActive, &StoryLength, &WhichCharacterFight, CharacterName, PlayerID, CharIDCPU, CharIsHuman, BackGroundName);
}
if(StoryStage == WhoAgainstWhoStage){
StoryStage = ActualFightStage;
 }
 if(StoryStage == ActualFightStage){
  Winner = -1;
  Winner = NewmalFight(StoryModeIdentifier, CharacterName, BackGroundName, CharIsHuman, CharHealth, PlayerID, PointsArray, &Difficulty, ModifiableOptionData->FirstTimerStartValue, ModifiableOptionData->SecondTimerStartValue);
  //Winner = CharacterOne;
  printf("Winner: (%d)\n", Winner);
  if(Winner == StairWayToHeavenIdentifier) StoryStage = FinalExitStage;
  else if(Winner == SelectNewCharacterIdentifier){ 
  CurrentChar = CharacterOne;
  do{
  if(CharIsHuman[CurrentChar]) PlayerID[CurrentChar] = -1;
  CurrentChar++;
  } while(CurrentChar <= MaxCharsLoopValue);
  StoryStage = FighterSelectStage;
  }
  else if(Winner >= NewPlayerJoinsInIdentifier && Winner < NewPlayerJoinsInIdentifier+MaxCharsOnScreen){
  CurrentChar = Winner-NewPlayerJoinsInIdentifier;
  PlayerID[CurrentChar] = -1;
  CharIsHuman[CurrentChar] = 1;
  StoryStage = FighterSelectStage;
  }
  else if(Winner == -1 || CharIsHuman[Winner] == 0) StoryStage = GameOverStage;
  else StoryStage = InbetweenStage;
  }
 if(StoryStage == CreditStage){
  StoryStage = CreditFunction();
  }
 if(StoryStage == GameOverStage){
  StoryStage = GameOver(PointsArray[0], GameOverNoDrawPoints, WhichPlayerActive);
  }

 if(StoryStage == FinalExitStage){
  StoryLoop = 0;
  }

}

return(OffTo);
}