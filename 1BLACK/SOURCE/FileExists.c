uint8 FileExists(char FileDir[]){

file_t InputFile;
uint8 ReturnValue;

InputFile = fs_open(FileDir, O_RDONLY);

if(InputFile == FILEHND_INVALID) ReturnValue = 0;
else ReturnValue = 1;

fs_close(InputFile);
return(ReturnValue);

}