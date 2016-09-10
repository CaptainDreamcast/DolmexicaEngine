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

InputFile = fs_open(FileDir, O_RDONLY);

fs_seek(InputFile, HeaderSizeCharacterArchive+(CharacterSelected*(sizeof(FighterSelectSmallPortraitStruct))), 0);
fs_read(InputFile, &CharacterBuffer, sizeof(FighterSelectSmallPortraitStruct));

fs_close(InputFile);

printf("CharacterName Before: (%s)\n", CharacterBuffer.CharacterName);
sprintf(CharacterName, "%.8s", CharacterBuffer.CharacterName);
printf("CharacterName: (%s)\n", CharacterName);

return(CharacterSelected);
}