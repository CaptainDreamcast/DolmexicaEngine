void FileCopyToOtherFileSystem(char InputFileName[], char OutputFileName[]){

file_t InputFile;
file_t OutputFile;

size_t FileLength;

char* DataBuffer;

InputFile = fs_open(InputFileName, O_RDONLY);

if(InputFile == FILEHND_INVALID){

printf("Could not copy from: (%s)\n", InputFileName);
fs_close(InputFile);
return;
}

FileLength = fs_total(InputFile);

DataBuffer = (char*) malloc(FileLength);

fs_read(InputFile, DataBuffer, FileLength);

fs_close(InputFile);

OutputFile = fs_open(OutputFileName, O_WRONLY);

fs_write(OutputFile, DataBuffer, FileLength);

fs_close(OutputFile);

free(DataBuffer);

}