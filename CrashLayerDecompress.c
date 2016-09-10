void CrashLayerDecompress(char InputFileDir[], char OutputFileDir[]){

file_t InputFile;
file_t OutputFile;
char *src;
char* data; 
qlz_state_decompress *state_decompress = (qlz_state_decompress *)malloc(sizeof(qlz_state_decompress));
size_t len;


InputFile = FileOpen(InputFileDir, O_RDONLY);

src = FileMemoryMap(InputFile);

len = qlz_size_decompressed(src);

data = (char*) malloc(len);

len = qlz_decompress(src, data, state_decompress);

FileClose(InputFile);
free(state_decompress);


OutputFile = FileOpen(OutputFileDir, O_WRONLY);
FileWrite(OutputFile, data, len);
FileClose(OutputFile);

free(data);



//return(OutputFile);

}

void NewCrashLayerDecompress(char FileDir[], unsigned long long* CrashLayerBuffer){

file_t InputFile;
char* src;
char* data;
size_t len; 
qlz_state_decompress *state_decompress = (qlz_state_decompress *)malloc(sizeof(qlz_state_decompress));

InputFile = FileOpen(FileDir, O_RDONLY);

src = FileMemoryMap(InputFile);

len = qlz_size_decompressed(src);

data = (char*) malloc(len);

len = qlz_decompress(src, data, state_decompress);

memcpy4(CrashLayerBuffer, data, len);

FileClose(InputFile);

free(state_decompress);

free(data);


}