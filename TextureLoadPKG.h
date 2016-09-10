void TextureLoadPKG(char WhichFileUsed[], pvr_ptr_t* TextureUsed, int* TextureSizeX, int* TextureSizeY, char MemoryReAllocation){

qlz_state_decompress *state_decompress = (qlz_state_decompress *)malloc(sizeof(qlz_state_decompress));
size_t BufferLength;
file_t PKGFile;
char* MipMapData;
char* KMGData;

PKGFile = FileOpen(WhichFileUsed, O_RDONLY);

if(PKGFile == FILEHND_INVALID) printf("\nCouldn't open: (%s)\nAborting Kernel any minute now...\n", WhichFileUsed);

BufferLength = FileTotal(PKGFile);

MipMapData = FileMemoryMap(PKGFile);

BufferLength = qlz_size_decompressed(MipMapData);
//printf("BufferLength uncompressed: %d!\n", BufferLength);

KMGData = (char*) malloc(BufferLength);

   // decompress and write result
BufferLength = qlz_decompress(MipMapData, KMGData, state_decompress);
FileClose(PKGFile);
free(state_decompress);

memcpy4(TextureSizeX, KMGData+16, sizeof(*TextureSizeX));
memcpy4(TextureSizeY, KMGData+20, sizeof(*TextureSizeY));

//printf("Texture Size: %d/%d\n", *TextureSizeX, *TextureSizeY);

if(MemoryReAllocation == ReAllocateTextureMemory){
pvr_mem_free(*TextureUsed);
(*TextureUsed) = pvr_mem_malloc(BufferLength-HeaderSizeKMG);
}
else if(MemoryReAllocation == PreAllocateTextureMemory) (*TextureUsed) = pvr_mem_malloc(BufferLength-HeaderSizeKMG);

sq_cpy((*TextureUsed), KMGData+HeaderSizeKMG, BufferLength-HeaderSizeKMG);

//printf("Freeing KMG data!\n");
free(KMGData);


}


void TextureLoadKMG(char WhichFileUsed[], pvr_ptr_t TextureUsed, int* TextureSizeX, int* TextureSizeY, char MemoryReAllocation){


size_t BufferLength;
file_t KMGFile;
char* KMGData;

KMGFile = FileOpen(WhichFileUsed, O_RDONLY);

if(KMGFile == FILEHND_INVALID) printf("\nCouldn't open: (%s)\nAborting Kernel any minute now...\n", WhichFileUsed);

BufferLength = FileTotal(KMGFile);

KMGData = FileMemoryMap(KMGFile);


memcpy4(TextureSizeX, KMGData+16, sizeof(*TextureSizeX));
memcpy4(TextureSizeY, KMGData+20, sizeof(*TextureSizeY));

//printf("Texture Size: %d/%d\n", *TextureSizeX, *TextureSizeY);

if(MemoryReAllocation == ReAllocateTextureMemory){
pvr_mem_free(TextureUsed);
TextureUsed = NULL;
TextureUsed = pvr_mem_malloc(BufferLength-HeaderSizeKMG);
}

//memcpy4(TextureUsed, KMGData+HeaderSizeKMG, BufferLength-HeaderSizeKMG);
sq_cpy(TextureUsed, KMGData+HeaderSizeKMG, BufferLength-HeaderSizeKMG);


FileClose(KMGFile);

}