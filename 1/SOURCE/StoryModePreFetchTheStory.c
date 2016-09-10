int StoryModePreFetchTheStory(char CharacterName[], int* StoryLength){

StoryModeHeaderStruct StoryModeHeaderData;

file_t InputFile;

char OriginalFileDir[NormalFileDirSize];
char FileDir[NormalFileDirSize];

int OffTo;

sprintf(OriginalFileDir, "%s/%s/%s.sto", FileSystemUsed, CharacterName, CharacterName);
sprintf(FileDir, "/ram/STORYHEADER");

FileCopyToOtherFileSystem(OriginalFileDir, FileDir);

InputFile = fs_open(FileDir, O_RDONLY);

fs_seek(InputFile, 0, 0);
fs_read(InputFile, &StoryModeHeaderData, sizeof(StoryModeHeaderStruct));

fs_close(InputFile);
fs_unlink(FileDir);

(*StoryLength) = StoryModeHeaderData.FightAmount;

OffTo = InbetweenStage;

return(OffTo);

}