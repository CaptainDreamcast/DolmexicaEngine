void LoadGraphicalUserInterface(uint8 WhichMode, pvr_ptr_t LifeBarTexture[], pvr_ptr_t VictoryTexture[], pvr_ptr_t* NewTimerTexture, char CharacterName[][10], char RealCharName[][20], SingleLifeBarStruct LifeBarData[], TimerStruct* TimerHeaderData, FontSingleCharacterStruct TimerCharacterData[], OtherGuiStruct OtherGuiData[], char PointArray[][SurvivalModeBeatableEnemyArrayLength], char CharIsHuman[]){

file_t InputFile;

char OriginalFileDir[NormalFileDirSize];
char FileDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];

int Bluff;
int CurrentChar;

switch(WhichMode){

case ArcadeModeIdentifier:
sprintf(MountPoint, "/ARCADE");
break;

case SurvivalModeIdentifier:
sprintf(MountPoint, "/SURVIVAL");
break;

case StoryModeIdentifier:
sprintf(MountPoint, "/STORY");
break;

}



sprintf(OriginalFileDir, "%s%s/GUI/GUIHEADER.hdr", FileSystemUsed, MountPoint);
sprintf(FileDir, "/ram/GUIHEADER");

FileCopyToOtherFileSystem(OriginalFileDir, FileDir);

InputFile = FileOpen(FileDir, O_RDONLY);
FileSeek(InputFile, 0, 0);


CurrentChar = CharacterOne;
do{

FileRead(InputFile, &LifeBarData[CurrentChar], sizeof(SingleLifeBarStruct));

if(LifeBarData[CurrentChar].LifeFullSizeX < 0 && LifeBarData[CurrentChar].LifeFullSizeY > 0){
LifeBarData[CurrentChar].LifeStartPositionY += LifeBarData[CurrentChar].LifeFullSizeY;
LifeBarData[CurrentChar].LifeFullSizeY = -LifeBarData[CurrentChar].LifeFullSizeY;
}

if(LifeBarData[CurrentChar].SpecialFullSizeX < 0 && LifeBarData[CurrentChar].SpecialFullSizeY > 0){
LifeBarData[CurrentChar].SpecialStartPositionY += LifeBarData[CurrentChar].SpecialFullSizeY;
LifeBarData[CurrentChar].SpecialFullSizeY = -LifeBarData[CurrentChar].SpecialFullSizeY;
}

CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);



CurrentChar = CharacterOne;
do{
Bluff = sprintf(RealCharName[CurrentChar], "%s", RealCharName[CurrentChar]);
FileRead(InputFile, &OtherGuiData[CurrentChar], sizeof(OtherGuiStruct));
if(OtherGuiData[CurrentChar].WhichNameAlignmentType == DrawnNameAlignedRight) OtherGuiData[CurrentChar].NamePositionX-= Bluff*OtherGuiData[CurrentChar].NameSizeX;

if(OtherGuiData[CurrentChar].WhichArrayAlignmentType == DrawnNameAlignedRight){ 
if(CharIsHuman[CurrentChar]) Bluff = sprintf(PointArray[CurrentChar], "%s", PointArray[CurrentChar]);
else Bluff = sprintf(OriginalFileDir, "PRESS START");
OtherGuiData[CurrentChar].ArrayPositionX-= Bluff*OtherGuiData[CurrentChar].ArraySizeX;
}

CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);



FileRead(InputFile, TimerHeaderData, sizeof(TimerStruct));

for(CurrentChar=0; CurrentChar<TimerCharacterAmount; CurrentChar++) FileRead(InputFile, &TimerCharacterData[CurrentChar], sizeof(FontSingleCharacterStruct));

FileClose(InputFile);
FileUnlink(FileDir);



sprintf(OriginalFileDir, "%s%s/GUI/TIMER.pkg", FileSystemUsed, MountPoint);
sprintf(FileDir, "/ram/TEXTURE"); 

FileCopyToOtherFileSystem(OriginalFileDir, FileDir);

(*NewTimerTexture) = pvr_mem_malloc(TimerHeaderData->TextureSizeX*TimerHeaderData->TextureSizeY*2);
TextureLoadPKG(FileDir, NewTimerTexture, &TimerHeaderData->TextureSizeX, &TimerHeaderData->TextureSizeY, ReAllocateTextureMemory);
FileUnlink(FileDir);

CurrentChar = CharacterOne;
do{

sprintf(OriginalFileDir, "%s%s/GUI/LIFEBAR%d.pkg", FileSystemUsed, MountPoint, (CurrentChar+1));
sprintf(FileDir, "/ram/TEXTURE"); //REMOVE THIS

FileCopyToOtherFileSystem(OriginalFileDir, FileDir);
LifeBarTexture[CurrentChar] = pvr_mem_malloc(LifeBarData[CurrentChar].LifeBarTextureSizeX*LifeBarData[CurrentChar].LifeBarTextureSizeY*2);
TextureLoadPKG(FileDir, &LifeBarTexture[CurrentChar], &LifeBarData[CurrentChar].LifeBarTextureSizeX, &LifeBarData[CurrentChar].LifeBarTextureSizeY, ReAllocateTextureMemory);
FileUnlink(FileDir);

sprintf(OriginalFileDir, "%s/%s/VICTORY.pkg", FileSystemUsed, CharacterName[CurrentChar]);
if((!FileExists(OriginalFileDir)) || WhichMode == SurvivalModeIdentifier) sprintf(OriginalFileDir, "%s/FALLBACK/VICTORY.pkg", FileSystemUsed);
sprintf(FileDir, "/ram/TEXTURE"); //REMOVE THIS

FileCopyToOtherFileSystem(OriginalFileDir, FileDir);
VictoryTexture[CurrentChar] = pvr_mem_malloc(LifeBarData[CurrentChar].VictoryTextureSizeX*LifeBarData[CurrentChar].VictoryTextureSizeY*2);
TextureLoadPKG(FileDir, &VictoryTexture[CurrentChar], &LifeBarData[CurrentChar].VictoryTextureSizeX, &LifeBarData[CurrentChar].VictoryTextureSizeY, ReAllocateTextureMemory);
FileUnlink(FileDir);

CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);


}