int StoryModePreFetchTheStory(char CharacterName[], int* StoryLength){

StoryModeHeaderStruct StoryModeHeaderData;

file_t InputFile;

char OriginalFileDir[NormalFileDirSize];
char FileDir[NormalFileDirSize];

int OffTo;

sprintf(OriginalFileDir, "%s/%s/%s.sto", FileSystemUsed, CharacterName, CharacterName);
sprintf(FileDir, "/ram/STORYHEADER");

FileCopyToOtherFileSystem(OriginalFileDir, FileDir);

InputFile = FileOpen(FileDir, O_RDONLY);

FileSeek(InputFile, 0, 0);
FileRead(InputFile, &StoryModeHeaderData, sizeof(StoryModeHeaderStruct));

FileClose(InputFile);
FileUnlink(FileDir);

(*StoryLength) = StoryModeHeaderData.FightAmount;

OffTo = InbetweenStage;

return(OffTo);

}