int FetchNewEnemy(uint8 ModeIdentifier, char CharacterName[], int CharacterSelected){

FighterSelectSmallPortraitStruct CharacterBuffer;

file_t InputFile;
char FileDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];

switch(ModeIdentifier){

case SurvivalModeIdentifier:
sprintf(MountPoint, "/SURVIVAL");
break;

case StoryModeIdentifier:
sprintf(MountPoint, "/STORY");
break;
}

sprintf(FileDir, "%s%s/CHARACTERS.lst", FileSystemUsed, MountPoint);

InputFile = FileOpen(FileDir, O_RDONLY);

FileSeek(InputFile, HeaderSizeCharacterArchive+(CharacterSelected*(sizeof(FighterSelectSmallPortraitStruct))), 0);
FileRead(InputFile, &CharacterBuffer, sizeof(FighterSelectSmallPortraitStruct));

FileClose(InputFile);

printf("CharacterName Before: (%s)\n", CharacterBuffer.CharacterName);
sprintf(CharacterName, "%.8s", CharacterBuffer.CharacterName);
printf("CharacterName: (%s)\n", CharacterName);

return(CharacterSelected);
}