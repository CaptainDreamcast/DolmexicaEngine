int FetchBackGroundAmount(char StageName[], int WhichBackGround){

file_t BackGroundRegister;

char RegisterFileDir[39];
int Bluff;

long BackGroundOffset = WhichBackGround*32+32;
long CurrentOffset;

int BackGroundAmount = 0;

Bluff = sprintf(RegisterFileDir, "%s/%.8s.bgr", FileSystemUsed, StageName);

BackGroundRegister = fs_open(RegisterFileDir, O_RDONLY);

CurrentOffset = fs_seek(BackGroundRegister, BackGroundOffset+2, 0);

fs_read(BackGroundRegister, &BackGroundAmount, 2);

fs_close(BackGroundRegister);

return(BackGroundAmount);
}

void LoadStageTotally(char StageName[], int* RealStageSize, char BackGroundAmountMax, int BackGroundAmount[], int BackGroundScreenPositionX[], int BackGroundScreenPositionY[], int BackGroundTextureSizeX[], int BackGroundTextureSizeY[], int BackGroundScreenSizeX[], int BackGroundScreenSizeY[], int BackGroundUpperLayerSizeX[], int BackGroundLowerLayerSizeX[], int BackGroundUpperLayerPositionZ[], int BackGroundLowerLayerPositionZ[], pvr_ptr_t BackGroundTextures1[], pvr_ptr_t BackGroundTextures2[], pvr_ptr_t BackGroundTextures3[], pvr_ptr_t BackGroundTextures4[], pvr_ptr_t BackGroundTextures5[]){

file_t BackGroundRegister;
file_t BackGroundArchive;
file_t TemporaryPNG;

char RegisterFileDir[NormalFileDirSize];
char ArchiveFileDir[NormalFileDirSize];
int Bluff;
int DirtyDeedsDoneDirtCheap = 0;
int BurningDownTheHouse = 0;
long BackGroundOffset;
long ArchiveOffset = 0;
long CurrentOffset;
long TextureSize = 0;

char* data;

Bluff = sprintf(RegisterFileDir, "%s/%.8s.bgr", FileSystemUsed, StageName);
Bluff = sprintf(ArchiveFileDir, "%s/%.8s.bga", FileSystemUsed, StageName);


BackGroundRegister = fs_open(RegisterFileDir, O_RDONLY);
BackGroundArchive = fs_open(ArchiveFileDir, O_RDONLY);


CurrentOffset = fs_seek(BackGroundRegister, 0, 0);
fs_read(BackGroundRegister, RealStageSize, 2);

while(DirtyDeedsDoneDirtCheap < BackGroundAmountMax){
if(BackGroundAmount[DirtyDeedsDoneDirtCheap] != 0){
BackGroundOffset = DirtyDeedsDoneDirtCheap*32+32;

CurrentOffset = fs_seek(BackGroundRegister, BackGroundOffset+4, 0);
BackGroundScreenPositionX[DirtyDeedsDoneDirtCheap] = 0;
fs_read(BackGroundRegister, &BackGroundScreenPositionX[DirtyDeedsDoneDirtCheap], 2);

CurrentOffset = fs_seek(BackGroundRegister, BackGroundOffset+6, 0);
BackGroundScreenPositionY[DirtyDeedsDoneDirtCheap] = 0;
fs_read(BackGroundRegister, &BackGroundScreenPositionY[DirtyDeedsDoneDirtCheap], 2);

CurrentOffset = fs_seek(BackGroundRegister, BackGroundOffset+8, 0);
BackGroundTextureSizeX[DirtyDeedsDoneDirtCheap] = 0;
fs_read(BackGroundRegister, &BackGroundTextureSizeX[DirtyDeedsDoneDirtCheap], 2);

CurrentOffset = fs_seek(BackGroundRegister, BackGroundOffset+10, 0);
BackGroundTextureSizeY[DirtyDeedsDoneDirtCheap] = 0;
fs_read(BackGroundRegister, &BackGroundTextureSizeY[DirtyDeedsDoneDirtCheap], 2);

CurrentOffset = fs_seek(BackGroundRegister, BackGroundOffset+12, 0);
BackGroundScreenSizeX[DirtyDeedsDoneDirtCheap] = 0;
fs_read(BackGroundRegister, &BackGroundScreenSizeX[DirtyDeedsDoneDirtCheap], 2);

CurrentOffset = fs_seek(BackGroundRegister, BackGroundOffset+14, 0);
BackGroundScreenSizeY[DirtyDeedsDoneDirtCheap] = 0;
fs_read(BackGroundRegister, &BackGroundScreenSizeY[DirtyDeedsDoneDirtCheap], 2);

CurrentOffset = fs_seek(BackGroundRegister, BackGroundOffset+16, 0);
BackGroundUpperLayerSizeX[DirtyDeedsDoneDirtCheap] = 0;
fs_read(BackGroundRegister, &BackGroundUpperLayerSizeX[DirtyDeedsDoneDirtCheap], 2);

CurrentOffset = fs_seek(BackGroundRegister, BackGroundOffset+18, 0);
BackGroundLowerLayerSizeX[DirtyDeedsDoneDirtCheap] = 0;
fs_read(BackGroundRegister, &BackGroundLowerLayerSizeX[DirtyDeedsDoneDirtCheap], 2);

CurrentOffset = fs_seek(BackGroundRegister, BackGroundOffset+20, 0);
BackGroundUpperLayerPositionZ[DirtyDeedsDoneDirtCheap] = 0;
fs_read(BackGroundRegister, &BackGroundUpperLayerPositionZ[DirtyDeedsDoneDirtCheap], 2);

CurrentOffset = fs_seek(BackGroundRegister, BackGroundOffset+22, 0);
BackGroundLowerLayerPositionZ[DirtyDeedsDoneDirtCheap] = 0;
fs_read(BackGroundRegister, &BackGroundLowerLayerPositionZ[DirtyDeedsDoneDirtCheap], 2);

BackGroundOffset = DirtyDeedsDoneDirtCheap*4+32;

CurrentOffset = fs_seek(BackGroundArchive, BackGroundOffset, 0);
fs_read(BackGroundArchive, &ArchiveOffset, 4);

BurningDownTheHouse = 0;
while(BurningDownTheHouse < BackGroundAmount[DirtyDeedsDoneDirtCheap]){

CurrentOffset = fs_seek(BackGroundArchive, ArchiveOffset, 0);
TextureSize = 0;
fs_read(BackGroundArchive, &TextureSize, 4);
printf("TextureSize: %ld\n", TextureSize);

    data = (char *)malloc(TextureSize);

CurrentOffset = fs_seek(BackGroundArchive, ArchiveOffset+16, 0);
fs_read(BackGroundArchive, data, TextureSize);

TemporaryPNG = fs_open("/ram/TEMPORARY.png", O_WRONLY);
CurrentOffset = fs_seek(TemporaryPNG, 0, 0);
fs_write(TemporaryPNG, data, TextureSize);
fs_close(TemporaryPNG);
free(data);

if(DirtyDeedsDoneDirtCheap == 0){
BackGroundTextures1[BurningDownTheHouse] = pvr_mem_malloc(BackGroundTextureSizeX[DirtyDeedsDoneDirtCheap]*BackGroundTextureSizeY[DirtyDeedsDoneDirtCheap]*2);
png_to_texture("/ram/TEMPORARY.png", BackGroundTextures1[BurningDownTheHouse], PNG_FULL_ALPHA);
}
else if(DirtyDeedsDoneDirtCheap == 1){
BackGroundTextures2[BurningDownTheHouse] = pvr_mem_malloc(BackGroundTextureSizeX[DirtyDeedsDoneDirtCheap]*BackGroundTextureSizeY[DirtyDeedsDoneDirtCheap]*2);
png_to_texture("/ram/TEMPORARY.png", BackGroundTextures2[BurningDownTheHouse], PNG_FULL_ALPHA);
}
else if(DirtyDeedsDoneDirtCheap == 2){
BackGroundTextures3[BurningDownTheHouse] = pvr_mem_malloc(BackGroundTextureSizeX[DirtyDeedsDoneDirtCheap]*BackGroundTextureSizeY[DirtyDeedsDoneDirtCheap]*2);
png_to_texture("/ram/TEMPORARY.png", BackGroundTextures3[BurningDownTheHouse], PNG_FULL_ALPHA);
}
else if(DirtyDeedsDoneDirtCheap == 3){
BackGroundTextures4[BurningDownTheHouse] = pvr_mem_malloc(BackGroundTextureSizeX[DirtyDeedsDoneDirtCheap]*BackGroundTextureSizeY[DirtyDeedsDoneDirtCheap]*2);
png_to_texture("/ram/TEMPORARY.png", BackGroundTextures4[BurningDownTheHouse], PNG_FULL_ALPHA);
}
else if(DirtyDeedsDoneDirtCheap == 4){
BackGroundTextures5[BurningDownTheHouse] = pvr_mem_malloc(BackGroundTextureSizeX[DirtyDeedsDoneDirtCheap]*BackGroundTextureSizeY[DirtyDeedsDoneDirtCheap]*2);
png_to_texture("/ram/TEMPORARY.png", BackGroundTextures5[BurningDownTheHouse], PNG_FULL_ALPHA);
}


fs_unlink("/ram/TEMPORARY.png");

ArchiveOffset += 16+TextureSize;
while(ArchiveOffset % 16 != 0){
ArchiveOffset++;
}

BurningDownTheHouse++;
}

}
DirtyDeedsDoneDirtCheap++;
}
fs_close(BackGroundRegister);
fs_close(BackGroundArchive);
}
