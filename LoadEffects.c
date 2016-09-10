void NewLoadEffects(UseHitEffectStruct HitEffects[][MaxHitEffectFrames], pvr_ptr_t HitEffectTextures[][MaxHitEffectFrames], uint16* HitEffectAmount, int HitEffectFrameAmount[], uint8 HitEffectSpeed[], uint16* MediumHitEffectLimit, uint16* StrongHitEffectLimit, char CharacterName[][10]){

LoadHitEffectStruct HitEffectBuffer;

file_t RomDiskFile;
size_t RomDiskSize;
uint8* RomDiskBuffer;

char FileDir[NormalFileDirSize];
char FileDirRam[NormalFileDirSize];
char MountPoint[NormalMountPointSize];
int Bluff;
int DirtyDeedsDoneDirtCheap;

int CurrentHitEffect;
int CurrentHitEffectFrame;

long CurrentOffset;

Bluff = sprintf(FileDir, "%s/EFFECTS/STANDARDHITEFFECTS.hea", FileSystemUsed);
Bluff = sprintf(MountPoint, "/TEMPORARYMOUNT");

RomDiskFile = FileOpen(FileDir, O_RDONLY);

RomDiskSize = FileTotal(RomDiskFile);

RomDiskBuffer = (uint8 *)malloc(RomDiskSize);

FileRead(RomDiskFile, RomDiskBuffer, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBuffer, 1);

FileClose(RomDiskFile);

Bluff = sprintf(FileDir, "%s/EFFECTS/STANDARDHITEFFECTS.hem", FileSystemUsed);
Bluff = sprintf(FileDirRam, "/ram/STANDARDHITEFFECTS");

FileCopyToOtherFileSystem(FileDir, FileDirRam);

RomDiskFile = FileOpen(FileDirRam, O_RDONLY);

RomDiskSize = FileTotal(RomDiskFile);

CurrentOffset = 0;

FileSeek(RomDiskFile, CurrentOffset, 0);
FileRead(RomDiskFile, HitEffectAmount, sizeof(uint16));

FileSeek(RomDiskFile, CurrentOffset+4, 0);
FileRead(RomDiskFile, MediumHitEffectLimit, sizeof(uint16));
FileRead(RomDiskFile, StrongHitEffectLimit, sizeof(uint16));

CurrentHitEffect = 0;
CurrentOffset+=HeaderSizeHitEffects;
FileSeek(RomDiskFile, CurrentOffset, 0);

while(CurrentHitEffect < *HitEffectAmount){

FileRead(RomDiskFile, &HitEffectBuffer, sizeof(LoadHitEffectStruct));

HitEffectFrameAmount[CurrentHitEffect] = HitEffectBuffer.HitEffectFrameAmount;
HitEffectSpeed[CurrentHitEffect] = HitEffectBuffer.HitEffectSpeed;

CurrentHitEffectFrame = 1;

while(CurrentHitEffectFrame <= HitEffectBuffer.HitEffectFrameAmount){

FileRead(RomDiskFile, &HitEffects[CurrentHitEffect][CurrentHitEffectFrame], sizeof(UseHitEffectStruct));

sprintf(FileDir, "%s/%.8s/%d.kmg", MountPoint, HitEffectBuffer.HitEffectName, CurrentHitEffectFrame);
//printf("%s\n", FileDir);

HitEffectTextures[CurrentHitEffect][CurrentHitEffectFrame] = pvr_mem_malloc(HitEffects[CurrentHitEffect][CurrentHitEffectFrame].HitEffectTextureSizeX*HitEffects[CurrentHitEffect][CurrentHitEffectFrame].HitEffectTextureSizeY*2);

TextureLoadKMG(FileDir, HitEffectTextures[CurrentHitEffect][CurrentHitEffectFrame], &Bluff, &DirtyDeedsDoneDirtCheap, NoAllocateTextureMemory);

CurrentHitEffectFrame++;
}

CurrentHitEffect++;
}

FileClose(RomDiskFile);
FileUnlink(FileDirRam);

fs_romdisk_unmount(MountPoint);

}
