int SurvivalCalculateNextFight(int PlayerID[], char CharacterName[][10], char CharIsHuman[], int StartHealth[], char EnemiesBeaten[][SurvivalModeBeatableEnemyArrayLength], uint8 CharsAreIdentical){

int OffTo;

int ReadyToRock;
int DirtyDeedsDoneDirtCheap;
int Bluff;

short CharAmount;
int FinalAICharSelected;

int CurrentOuterChar;
int CurrentChar;

OffTo = ActualFightStage;

FetchCharacterAmount(SurvivalModeIdentifier, &CharAmount);

CurrentChar = CharacterOne;
do{

if(CharIsHuman[CurrentChar] == 1){

StartHealth[CurrentChar] += (CharHealthMax*0.2f);
if(StartHealth[CurrentChar] > CharHealthMax) StartHealth[CurrentChar] = CharHealthMax;

ReadyToRock = 1;
DirtyDeedsDoneDirtCheap = 0;
while(ReadyToRock){
if(EnemiesBeaten[CurrentChar][DirtyDeedsDoneDirtCheap] == 0) ReadyToRock = 0;
else DirtyDeedsDoneDirtCheap++;
}
DirtyDeedsDoneDirtCheap--;

ReadyToRock = 1;
while(ReadyToRock){
EnemiesBeaten[CurrentChar][DirtyDeedsDoneDirtCheap]++;
if(EnemiesBeaten[CurrentChar][DirtyDeedsDoneDirtCheap] > HexNumberValueOffset+9){
if(DirtyDeedsDoneDirtCheap == 0){
EnemiesBeaten[CurrentChar][DirtyDeedsDoneDirtCheap] = HexNumberValueOffset;
for(Bluff = SurvivalModeBeatableEnemyArrayLength-2; Bluff >= 0; Bluff--)  EnemiesBeaten[CurrentChar][Bluff+1] = EnemiesBeaten[CurrentChar][Bluff];
EnemiesBeaten[CurrentChar][DirtyDeedsDoneDirtCheap] = HexNumberValueOffset+1;
}
else{EnemiesBeaten[CurrentChar][DirtyDeedsDoneDirtCheap] = HexNumberValueOffset; EnemiesBeaten[CurrentChar][DirtyDeedsDoneDirtCheap-1]++; DirtyDeedsDoneDirtCheap--;}
}
//else ReadyToRock = 0;
ReadyToRock = 0;
}

} // if CharIsHuman
else{

DeLoadCharRomDisk(CharacterName[CurrentChar], CharsAreIdentical, CurrentChar);

StartHealth[CurrentChar] = CharHealthMax;

srand(rtc_unix_secs());
FinalAICharSelected = ((rand()%CharAmount));

printf("CPU Selected Before: (%d)\n", FinalAICharSelected);


DirtyDeedsDoneDirtCheap = 0;
ReadyToRock = 1;

while(ReadyToRock){
ReadyToRock = 0;

CurrentOuterChar = CharacterOne;
do{
if(FinalAICharSelected == PlayerID[CurrentOuterChar]) ReadyToRock = 1;
CurrentOuterChar++;
} while(CurrentOuterChar <= MaxCharsOnScreen);

if(ReadyToRock) FinalAICharSelected++;
if(FinalAICharSelected == CharAmount){ 
if(DirtyDeedsDoneDirtCheap) ReadyToRock = 0;
else DirtyDeedsDoneDirtCheap = 1;
FinalAICharSelected = 0;
}

}

printf("CPU Selected: (%d)\n", FinalAICharSelected);

PlayerID[CurrentChar] = FetchNewEnemy(SurvivalModeIdentifier, CharacterName[CurrentChar], FinalAICharSelected);
}

CurrentChar++;
} while (CurrentChar <= MaxCharsLoopValue);

return(OffTo);
}