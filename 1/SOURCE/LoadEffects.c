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

RomDiskFile = fs_open(FileDir, O_RDONLY);

RomDiskSize = fs_total(RomDiskFile);

RomDiskBuffer = (uint8 *)malloc(RomDiskSize);

fs_read(RomDiskFile, RomDiskBuffer, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBuffer, 1);

fs_close(RomDiskFile);

Bluff = sprintf(FileDir, "%s/EFFECTS/STANDARDHITEFFECTS.hem", FileSystemUsed);
Bluff = sprintf(FileDirRam, "/ram/STANDARDHITEFFECTS");

FileCopyToOtherFileSystem(FileDir, FileDirRam);

RomDiskFile = fs_open(FileDirRam, O_RDONLY);

RomDiskSize = fs_total(RomDiskFile);

CurrentOffset = 0;

fs_seek(RomDiskFile, CurrentOffset, 0);
fs_read(RomDiskFile, HitEffectAmount, sizeof(uint16));

fs_seek(RomDiskFile, CurrentOffset+4, 0);
fs_read(RomDiskFile, MediumHitEffectLimit, sizeof(uint16));
fs_read(RomDiskFile, StrongHitEffectLimit, sizeof(uint16));

CurrentHitEffect = 0;
CurrentOffset+=HeaderSizeHitEffects;
fs_seek(RomDiskFile, CurrentOffset, 0);

while(CurrentHitEffect < *HitEffectAmount){

fs_read(RomDiskFile, &HitEffectBuffer, sizeof(LoadHitEffectStruct));

HitEffectFrameAmount[CurrentHitEffect] = HitEffectBuffer.HitEffectFrameAmount;
HitEffectSpeed[CurrentHitEffect] = HitEffectBuffer.HitEffectSpeed;

CurrentHitEffectFrame = 1;

while(CurrentHitEffectFrame <= HitEffectBuffer.HitEffectFrameAmount){

fs_read(RomDiskFile, &HitEffects[CurrentHitEffect][CurrentHitEffectFrame], sizeof(UseHitEffectStruct));

sprintf(FileDir, "%s/%.8s/%d.kmg", MountPoint, HitEffectBuffer.HitEffectName, CurrentHitEffectFrame);
//printf("%s\n", FileDir);

HitEffectTextures[CurrentHitEffect][CurrentHitEffectFrame] = pvr_mem_malloc(HitEffects[CurrentHitEffect][CurrentHitEffectFrame].HitEffectTextureSizeX*HitEffects[CurrentHitEffect][CurrentHitEffectFrame].HitEffectTextureSizeY*2);

TextureLoadKMG(FileDir, HitEffectTextures[CurrentHitEffect][CurrentHitEffectFrame], &Bluff, &DirtyDeedsDoneDirtCheap, NoAllocateTextureMemory);

CurrentHitEffectFrame++;
}

CurrentHitEffect++;
}

fs_close(RomDiskFile);
fs_unlink(FileDirRam);

fs_romdisk_unmount(MountPoint);

}
