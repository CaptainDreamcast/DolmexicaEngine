void CrashLayerDecompress(char InputFileDir[], char OutputFileDir[]){

file_t InputFile;
file_t OutputFile;
char *src;
char* data; 
qlz_state_decompress *state_decompress = (qlz_state_decompress *)malloc(sizeof(qlz_state_decompress));
size_t len;


InputFile = fs_open(InputFileDir, O_RDONLY);

src = fs_mmap(InputFile);

len = qlz_size_decompressed(src);

data = (char*) malloc(len);

len = qlz_decompress(src, data, state_decompress);

fs_close(InputFile);
free(state_decompress);


OutputFile = fs_open(OutputFileDir, O_WRONLY);
fs_write(OutputFile, data, len);
fs_close(OutputFile);

free(data);



//return(OutputFile);

}

void NewCrashLayerDecompress(char FileDir[], unsigned long long* CrashLayerBuffer){

file_t InputFile;
char* src;
char* data;
size_t len; 
qlz_state_decompress *state_decompress = (qlz_state_decompress *)malloc(sizeof(qlz_state_decompress));

InputFile = fs_open(FileDir, O_RDONLY);

src = fs_mmap(InputFile);

len = qlz_size_decompressed(src);

data = (char*) malloc(len);

len = qlz_decompress(src, data, state_decompress);

memcpy4(CrashLayerBuffer, data, len);

fs_close(InputFile);

free(state_decompress);

free(data);


}