void FileCopyToOtherFileSystem(char InputFileName[], char OutputFileName[]){

file_t InputFile;
file_t OutputFile;

size_t FileLength;

char* DataBuffer;

InputFile = FileOpen(InputFileName, O_RDONLY);

if(InputFile == FILEHND_INVALID){

printf("Could not copy from: (%s)\n", InputFileName);
FileClose(InputFile);
return;
}

FileLength = FileTotal(InputFile);

DataBuffer = (char*) malloc(FileLength);

FileRead(InputFile, DataBuffer, FileLength);

FileClose(InputFile);

OutputFile = FileOpen(OutputFileName, O_WRONLY);

FileWrite(OutputFile, DataBuffer, FileLength);

FileClose(OutputFile);

free(DataBuffer);

}