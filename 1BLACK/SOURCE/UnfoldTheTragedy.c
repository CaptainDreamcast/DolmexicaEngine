int UnfoldTheTragedy(int* WhichPlayerActive, int* StoryLength, int* WhichCharacterFight, char CharacterName[][9], int PlayerID[], int CharIDCPU[], char CharIsHuman[], char BackGroundName[]){

int OffTo;
int Bluff;

short CharAmount;
int ReadyToRock;
int CurrentChar;

file_t InputFile;

char FileDir[NormalFileDirSize];
char OriginalFileDir[NormalFileDirSize];

uint8 WhichStoryBoard;
uint8 EnemyPoolLength;
uint8 FinalAICharSelected;

uint32 CurrentOffset;


sprintf(OriginalFileDir, "%s/%s/%s.sto", FileSystemUsed, CharacterName[(*WhichPlayerActive)], CharacterName[(*WhichPlayerActive)]);
sprintf(FileDir, "/ram/STORYHEADER");

FileCopyToOtherFileSystem(OriginalFileDir, FileDir);

InputFile = fs_open(FileDir, O_RDONLY);

CurrentOffset = sizeof(StoryModeHeaderStruct)+(sizeof(uint32)*(*WhichCharacterFight));
fs_seek(InputFile, CurrentOffset, 0);
fs_read(InputFile, &CurrentOffset, sizeof(uint32));

fs_seek(InputFile, CurrentOffset, 0);

fs_read(InputFile, &WhichStoryBoard, sizeof(uint8));
fs_read(InputFile, BackGroundName, ActualNameSize);
BackGroundName[ActualNameSize] = '\0';

fs_read(InputFile, &EnemyPoolLength, sizeof(uint8));

CurrentOffset = fs_tell(InputFile);
//CurrentOffset++;


if(EnemyPoolLength == 0) FetchCharacterAmount(StoryModeIdentifier, &CharAmount);
else CharAmount = EnemyPoolLength;

srand(rtc_unix_secs());
FinalAICharSelected = ((rand()%CharAmount));

ReadyToRock = 1;

while(ReadyToRock){
ReadyToRock = 0;

CurrentChar = CharacterOne;
do{
if(EnemyPoolLength == 0 && FinalAICharSelected == PlayerID[CurrentChar]) ReadyToRock = 1;
CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);

if(EnemyPoolLength == 0){
for(Bluff=0; Bluff<(*WhichCharacterFight); Bluff++) if(FinalAICharSelected == CharIDCPU[Bluff]) ReadyToRock = 1;
}

if(ReadyToRock) FinalAICharSelected++;
if(FinalAICharSelected == CharAmount) FinalAICharSelected = 0;
}

if(EnemyPoolLength != 0){
CurrentOffset+=FinalAICharSelected;
fs_seek(InputFile, CurrentOffset, 0);
fs_read(InputFile, &FinalAICharSelected, sizeof(uint8));
}
fs_close(InputFile);
fs_unlink(FileDir);

if((*WhichPlayerActive) == CharacterOne) CurrentChar = CharacterTwo;
else CurrentChar = CharacterOne;

PlayerID[CurrentChar] = FetchNewEnemy(StoryModeIdentifier, CharacterName[CurrentChar], FinalAICharSelected);
CharIDCPU[(*WhichCharacterFight)] = PlayerID[CurrentChar];

if(WhichStoryBoard != 0){
sprintf(FileDir, "%s/%s/BOARDS/%d.sbd", FileSystemUsed, CharacterName[(*WhichPlayerActive)], WhichStoryBoard);
if(LetsSeeTheStory(FileDir) == StairWayToHeavenIdentifier) return(FinalExitStage);
}

if((*WhichCharacterFight) >= (*StoryLength)) OffTo = CreditStage;
else OffTo = ActualFightStage;

(*WhichCharacterFight)++;

return(OffTo);
}