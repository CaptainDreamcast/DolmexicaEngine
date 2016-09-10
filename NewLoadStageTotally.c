void NewLoadStageTotally(char StageName[], pvr_ptr_t BackGroundTexture[], BackGroundHeaderStruct* BackGroundHeaderData, BackGroundStruct BackGroundData[], BackGroundAnimationStruct BackGroundAnimationData[]){

file_t InputFile;

int Bluff;
int DirtyDeedsDoneDirtCheap;
int BurningDownTheHouse;

char FileDir[NormalFileDirSize];
char TextureDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];

BackGroundInnerAnimationStruct BackGroundInnerAnimationBuffer;


sprintf(TextureDir, "%s/STAGES/%s.ogg", FileSystemUsed, StageName);
SoundLoad(TextureDir);


sprintf(FileDir, "%s/STAGES/%s.bga", FileSystemUsed, StageName);
sprintf(MountPoint, "/STAGE");
FileDirToRomDisk(FileDir, MountPoint);

sprintf(FileDir, "%s/HEADER.bgr", MountPoint);
InputFile = FileOpen(FileDir, O_RDONLY);

FileSeek(InputFile, 0, 0);
FileRead(InputFile, BackGroundHeaderData, sizeof(BackGroundHeaderStruct));

DirtyDeedsDoneDirtCheap = 0;
while(DirtyDeedsDoneDirtCheap < BackGroundHeaderData->BackGroundAmount){

FileRead(InputFile, &BackGroundData[DirtyDeedsDoneDirtCheap], sizeof(BackGroundStruct));

if(BackGroundData[DirtyDeedsDoneDirtCheap].BackGroundAnimated != 0){

Bluff = (BackGroundData[DirtyDeedsDoneDirtCheap].BackGroundAnimated)-1;
FileRead(InputFile, &BackGroundInnerAnimationBuffer, sizeof(BackGroundInnerAnimationStruct));
BackGroundAnimationData[Bluff].Data = BackGroundInnerAnimationBuffer;

for(BurningDownTheHouse=0; BurningDownTheHouse<BackGroundInnerAnimationBuffer.FrameAmount; BurningDownTheHouse++){
BackGroundAnimationData[Bluff].Texture[BurningDownTheHouse] = pvr_mem_malloc(BackGroundData[DirtyDeedsDoneDirtCheap].TextureSizeX*BackGroundData[DirtyDeedsDoneDirtCheap].TextureSizeY*2);
sprintf(TextureDir, "%s/%d_%d.pkg", MountPoint, DirtyDeedsDoneDirtCheap, BurningDownTheHouse);
TextureLoadPKG(TextureDir, &BackGroundAnimationData[Bluff].Texture[BurningDownTheHouse], &BackGroundData[DirtyDeedsDoneDirtCheap].TextureSizeX, &BackGroundData[DirtyDeedsDoneDirtCheap].TextureSizeY, ReAllocateTextureMemory);
}

}
else{
BackGroundTexture[DirtyDeedsDoneDirtCheap] = pvr_mem_malloc(BackGroundData[DirtyDeedsDoneDirtCheap].TextureSizeX*BackGroundData[DirtyDeedsDoneDirtCheap].TextureSizeY*2);
sprintf(TextureDir, "%s/%d.pkg", MountPoint, DirtyDeedsDoneDirtCheap);
TextureLoadPKG(TextureDir, &BackGroundTexture[DirtyDeedsDoneDirtCheap], &BackGroundData[DirtyDeedsDoneDirtCheap].TextureSizeX, &BackGroundData[DirtyDeedsDoneDirtCheap].TextureSizeY, ReAllocateTextureMemory);
}

DirtyDeedsDoneDirtCheap++;
}

sprintf(TextureDir, "%s/0.pal", MountPoint);
if(FileDirToPalette(TextureDir, BackGroundPalette)) BackGroundHeaderData->TextureType = PaletteType;
else BackGroundHeaderData->TextureType = RedGreenBlueType;


FileClose(InputFile);
FileUnlink(FileDir);
fs_romdisk_unmount(MountPoint);
}