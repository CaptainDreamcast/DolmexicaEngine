void LoadFightAnimationSoundEffect(sfxhnd_t FightAnimationSoundEffect[], char MountPoint[]){

file_t RegisterFile;

int DirtyDeedsDoneDirtCheap;
char FileDir[NormalFileDirSize];
char NewMountPoint[NormalMountPointSize];
uint8* RomDiskBuffer;
long RomDiskSize;

short SoundEffectAmount;

sprintf(FileDir, "/ram/%s", MountPoint);

RegisterFile = fs_open(FileDir, O_RDONLY);
fs_seek(RegisterFile, FightAnimationSoundEffectAmountOffset, 0);
fs_read(RegisterFile, &SoundEffectAmount, 2);
fs_close(RegisterFile);

if(SoundEffectAmount > 0){

sprintf(FileDir, "%s/ANIMATIONS/%s.sfa", FileSystemUsed, MountPoint);
sprintf(NewMountPoint, "/%s", MountPoint);
RegisterFile = fs_open(FileDir, O_RDONLY);
RomDiskSize = fs_total(RegisterFile);
RomDiskBuffer = (uint8 *)malloc(RomDiskSize);
fs_read(RegisterFile, RomDiskBuffer, RomDiskSize);
fs_romdisk_mount(NewMountPoint, RomDiskBuffer, 1);
fs_close(RegisterFile);



DirtyDeedsDoneDirtCheap = 1;

while(DirtyDeedsDoneDirtCheap <= SoundEffectAmount){

sprintf(FileDir, "/%s/%d.wav", NewMountPoint, DirtyDeedsDoneDirtCheap);
FightAnimationSoundEffect[DirtyDeedsDoneDirtCheap] = snd_sfx_load(FileDir);

DirtyDeedsDoneDirtCheap++;
}
fs_romdisk_unmount(NewMountPoint);
}
}

void DeLoadFightAnimationSoundEffect(sfxhnd_t FightAnimationSoundEffect[], char MountPoint[]){

file_t RegisterFile;

int DirtyDeedsDoneDirtCheap;
char FileDir[NormalFileDirSize];

short SoundEffectAmount;

sprintf(FileDir, "/ram/%s", MountPoint);

RegisterFile = fs_open(FileDir, O_RDONLY);
fs_seek(RegisterFile, FightAnimationSoundEffectAmountOffset, 0);
fs_read(RegisterFile, &SoundEffectAmount, 2);
fs_close(RegisterFile);

DirtyDeedsDoneDirtCheap = 1;

while(DirtyDeedsDoneDirtCheap <= SoundEffectAmount){

snd_sfx_unload(FightAnimationSoundEffect[DirtyDeedsDoneDirtCheap]);

DirtyDeedsDoneDirtCheap++;
}
}

void LoadAllKindsOfAnimations(sfxhnd_t FightAnimationSoundEffect[][MaxFightAnimationSoundEffect], uint16* FightAnimationFlags){

file_t RomDiskFile;

uint8* RomDiskBufferFightAnimation;
uint8* RomDiskBufferRoundAnimation;
uint8* RomDiskBufferPerfectAnimation;
uint8* RomDiskBufferContinueAnimation;

int Bluff;

char* RegisterContent;

long RomDiskSize;

char RomDiskDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];

//--------------------FightAnimation Start------------------------

Bluff = sprintf(RomDiskDir, "%s/ANIMATIONS/FIGHTANIMATION.fam", FileSystemUsed);

Bluff = sprintf(MountPoint, "/ram/FIGHTANIMATION");

RomDiskFile = fs_open(RomDiskDir, O_RDONLY);

if(RomDiskFile != FILEHND_INVALID){

*FightAnimationFlags |= FightAnimationFlag;

RomDiskSize = fs_total(RomDiskFile);

RegisterContent = (char *)malloc(RomDiskSize);

fs_read(RomDiskFile, RegisterContent, RomDiskSize);

fs_close(RomDiskFile);

RomDiskFile = fs_open(MountPoint, O_WRONLY);

fs_write(RomDiskFile, RegisterContent, RomDiskSize);

fs_close(RomDiskFile);

free(RegisterContent);


Bluff = sprintf(MountPoint, "FIGHTANIMATION");
LoadFightAnimationSoundEffect(FightAnimationSoundEffect[FightAnimationSoundEffectIdentifier], MountPoint);


Bluff = sprintf(RomDiskDir, "%s/ANIMATIONS/FIGHTANIMATION.faa", FileSystemUsed);
Bluff = sprintf(MountPoint, "/FIGHTANIMATION");

RomDiskFile = fs_open(RomDiskDir, O_RDONLY);

RomDiskSize = fs_total(RomDiskFile);

RomDiskBufferFightAnimation = (uint8 *)malloc(RomDiskSize);

fs_read(RomDiskFile, RomDiskBufferFightAnimation, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBufferFightAnimation, 1);

fs_close(RomDiskFile);

}



//--------------------FightAnimation END------------------------


//--------------------RoundAnimation Start------------------------

Bluff = sprintf(RomDiskDir, "%s/ANIMATIONS/ROUNDANIMATION.ram", FileSystemUsed);

Bluff = sprintf(MountPoint, "/ram/ROUNDANIMATION");

RomDiskFile = fs_open(RomDiskDir, O_RDONLY);

if(RomDiskFile != FILEHND_INVALID){

*FightAnimationFlags |= RoundAnimationFlag;

RomDiskSize = fs_total(RomDiskFile);

RegisterContent = (char *)malloc(RomDiskSize);

fs_read(RomDiskFile, RegisterContent, RomDiskSize);

fs_close(RomDiskFile);

RomDiskFile = fs_open(MountPoint, O_WRONLY);

fs_write(RomDiskFile, RegisterContent, RomDiskSize);

fs_close(RomDiskFile);

free(RegisterContent);


Bluff = sprintf(MountPoint, "ROUNDANIMATION");
LoadFightAnimationSoundEffect(FightAnimationSoundEffect[RoundAnimationSoundEffectIdentifier], MountPoint);


Bluff = sprintf(RomDiskDir, "%s/ANIMATIONS/ROUNDANIMATION.raa", FileSystemUsed);
Bluff = sprintf(MountPoint, "/ROUNDANIMATION");

RomDiskFile = fs_open(RomDiskDir, O_RDONLY);

RomDiskSize = fs_total(RomDiskFile);

RomDiskBufferRoundAnimation = (uint8 *)malloc(RomDiskSize);

fs_read(RomDiskFile, RomDiskBufferRoundAnimation, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBufferRoundAnimation, 1);

fs_close(RomDiskFile);

}

//--------------------RoundAnimation END------------------------

//--------------------PerfectAnimation Start------------------------

Bluff = sprintf(RomDiskDir, "%s/ANIMATIONS/PERFECTANIMATION.pam", FileSystemUsed);

Bluff = sprintf(MountPoint, "/ram/PERFECTANIMATION");

RomDiskFile = fs_open(RomDiskDir, O_RDONLY);

if(RomDiskFile != FILEHND_INVALID){

*FightAnimationFlags |= PerfectAnimationFlag;

RomDiskSize = fs_total(RomDiskFile);

RegisterContent = (char *)malloc(RomDiskSize);

fs_read(RomDiskFile, RegisterContent, RomDiskSize);

fs_close(RomDiskFile);

RomDiskFile = fs_open(MountPoint, O_WRONLY);

fs_write(RomDiskFile, RegisterContent, RomDiskSize);

fs_close(RomDiskFile);

free(RegisterContent);


Bluff = sprintf(MountPoint, "PERFECTANIMATION");
LoadFightAnimationSoundEffect(FightAnimationSoundEffect[PerfectAnimationSoundEffectIdentifier], MountPoint);


Bluff = sprintf(RomDiskDir, "%s/ANIMATIONS/PERFECTANIMATION.paa", FileSystemUsed);
Bluff = sprintf(MountPoint, "/PERFECTANIMATION");

RomDiskFile = fs_open(RomDiskDir, O_RDONLY);

RomDiskSize = fs_total(RomDiskFile);

RomDiskBufferPerfectAnimation = (uint8 *)malloc(RomDiskSize);

fs_read(RomDiskFile, RomDiskBufferPerfectAnimation, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBufferPerfectAnimation, 1);

fs_close(RomDiskFile);

}

//--------------------PerfectAnimation END------------------------

//--------------------ContinueAnimation Start------------------------

Bluff = sprintf(RomDiskDir, "%s/ANIMATIONS/CONTINUEANIMATION.cam", FileSystemUsed);

Bluff = sprintf(MountPoint, "/ram/CONTINUEANIMATION");

RomDiskFile = fs_open(RomDiskDir, O_RDONLY);

if(RomDiskFile != FILEHND_INVALID){

*FightAnimationFlags |= ContinueAnimationFlag;

RomDiskSize = fs_total(RomDiskFile);

RegisterContent = (char *)malloc(RomDiskSize);

fs_read(RomDiskFile, RegisterContent, RomDiskSize);

fs_close(RomDiskFile);

RomDiskFile = fs_open(MountPoint, O_WRONLY);

fs_write(RomDiskFile, RegisterContent, RomDiskSize);

fs_close(RomDiskFile);

free(RegisterContent);


Bluff = sprintf(MountPoint, "CONTINUEANIMATION");
LoadFightAnimationSoundEffect(FightAnimationSoundEffect[ContinueAnimationSoundEffectIdentifier], MountPoint);


Bluff = sprintf(RomDiskDir, "%s/ANIMATIONS/CONTINUEANIMATION.caa", FileSystemUsed);
Bluff = sprintf(MountPoint, "/CONTINUEANIMATION");

RomDiskFile = fs_open(RomDiskDir, O_RDONLY);

RomDiskSize = fs_total(RomDiskFile);

RomDiskBufferContinueAnimation = (uint8 *)malloc(RomDiskSize);

fs_read(RomDiskFile, RomDiskBufferContinueAnimation, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBufferContinueAnimation, 1);

fs_close(RomDiskFile);

}

//--------------------ContinueAnimation END------------------------

//--------------------NewRivalAnimation Start------------------------

Bluff = sprintf(RomDiskDir, "%s/ANIMATIONS/JOININANIMATION.jam", FileSystemUsed);

Bluff = sprintf(MountPoint, "/ram/JOININANIMATION");

RomDiskFile = fs_open(RomDiskDir, O_RDONLY);

if(RomDiskFile != FILEHND_INVALID){

*FightAnimationFlags |= NewRivalAnimationFlag;

RomDiskSize = fs_total(RomDiskFile);

RegisterContent = (char *)malloc(RomDiskSize);

fs_read(RomDiskFile, RegisterContent, RomDiskSize);

fs_close(RomDiskFile);

RomDiskFile = fs_open(MountPoint, O_WRONLY);

fs_write(RomDiskFile, RegisterContent, RomDiskSize);

fs_close(RomDiskFile);

free(RegisterContent);


Bluff = sprintf(MountPoint, "JOININANIMATION");
LoadFightAnimationSoundEffect(FightAnimationSoundEffect[ContinueAnimationSoundEffectIdentifier], MountPoint);


Bluff = sprintf(RomDiskDir, "%s/ANIMATIONS/JOININANIMATION.jaa", FileSystemUsed);
Bluff = sprintf(MountPoint, "/JOININANIMATION");

RomDiskFile = fs_open(RomDiskDir, O_RDONLY);

RomDiskSize = fs_total(RomDiskFile);

RomDiskBufferContinueAnimation = (uint8 *)malloc(RomDiskSize);

fs_read(RomDiskFile, RomDiskBufferContinueAnimation, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBufferContinueAnimation, 1);

fs_close(RomDiskFile);

}

//--------------------NewRivalAnimation END------------------------
}

void DeLoadAllKindsOfAnimations(sfxhnd_t FightAnimationSoundEffect[][MaxFightAnimationSoundEffect], uint16 FightAnimationFlags){

char MountPoint[NormalMountPointSize];

if(FightAnimationFlags & FightAnimationFlag){
sprintf(MountPoint, "FIGHTANIMATION");
DeLoadFightAnimationSoundEffect(FightAnimationSoundEffect[FightAnimationSoundEffectIdentifier], MountPoint);
sprintf(MountPoint, "/FIGHTANIMATION");
fs_romdisk_unmount(MountPoint);
sprintf(MountPoint, "/ram/FIGHTANIMATION");
fs_unlink(MountPoint);
}

if(FightAnimationFlags & RoundAnimationFlag){
sprintf(MountPoint, "ROUNDANIMATION");
DeLoadFightAnimationSoundEffect(FightAnimationSoundEffect[RoundAnimationSoundEffectIdentifier], MountPoint);
sprintf(MountPoint, "/ROUNDANIMATION");
fs_romdisk_unmount(MountPoint);
sprintf(MountPoint, "/ram/ROUNDANIMATION");
fs_unlink(MountPoint);
}

if(FightAnimationFlags & PerfectAnimationFlag){
sprintf(MountPoint, "PERFECTANIMATION");
DeLoadFightAnimationSoundEffect(FightAnimationSoundEffect[PerfectAnimationSoundEffectIdentifier], MountPoint);
sprintf(MountPoint, "/PERFECTANIMATION");
fs_romdisk_unmount(MountPoint);
sprintf(MountPoint, "/ram/PERFECTANIMATION");
fs_unlink(MountPoint);
}

if(FightAnimationFlags & ContinueAnimationFlag){
sprintf(MountPoint, "CONTINUEANIMATION");
DeLoadFightAnimationSoundEffect(FightAnimationSoundEffect[ContinueAnimationSoundEffectIdentifier], MountPoint);
sprintf(MountPoint, "/CONTINUEANIMATION");
fs_romdisk_unmount(MountPoint);
sprintf(MountPoint, "/ram/CONTINUEANIMATION");
fs_unlink(MountPoint);
}

if(FightAnimationFlags & NewRivalAnimationFlag){
sprintf(MountPoint, "JOININANIMATION");
DeLoadFightAnimationSoundEffect(FightAnimationSoundEffect[ContinueAnimationSoundEffectIdentifier], MountPoint);
sprintf(MountPoint, "/JOININANIMATION");
fs_romdisk_unmount(MountPoint);
sprintf(MountPoint, "/ram/JOININANIMATION");
fs_unlink(MountPoint);
}

}

void DrawSomeFunkyAnimation(char FrameID, short SizeX, short SizeY, short ScreenPositionX, short ScreenPositionY, char MountPoint[], pvr_ptr_t TextureUsed, uint8 TextureType){

char FileDir[NormalFileDirSize];
uint32 FormatValue;

int TextureSizeX, TextureSizeY;

sprintf(FileDir, "/%s/%d.pkg", MountPoint, FrameID);
TextureLoadPKG(FileDir, &TextureUsed, &TextureSizeX, &TextureSizeY, ReAllocateTextureMemory);

if(TextureType == PaletteType) FormatValue = (PVR_TXRFMT_PAL8BPP | PVR_TXRFMT_8BPP_PAL(AdditionalAnimationPalette));
else FormatValue = PVR_TXRFMT_ARGB4444;

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, FormatValue, TextureSizeX, TextureSizeY, TextureUsed, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = UpperGuiPositionZ1;
    vert.u = 0.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX;
    vert.y = ScreenPositionY;
    vert.z = UpperGuiPositionZ1;
    vert.u = 1.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+SizeY;
    vert.z = UpperGuiPositionZ1;
    vert.u = 0.0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX;;
    vert.y = ScreenPositionY+SizeY;
    vert.z = UpperGuiPositionZ1;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));



}

void ReadNormalAnimation(char WhichFrame, char* FrameID, char* FightAnimationSpeed, int* TextureSizeX, int* TextureSizeY, short* SizeX, short* SizeY, short* ScreenPositionX, short* ScreenPositionY, short* VoiceClipChecker, char* EndIt, char MountPoint[]){

file_t MoveArchive;

int Bluff;
char MVTFile[NormalFileDirSize];
long CurrentOffset;
long MoveOffset;



Bluff = sprintf(MVTFile, "/ram/%s", MountPoint);

MoveArchive = fs_open(MVTFile, O_RDONLY);

MoveOffset = HeaderSizeFightAnimation+((WhichFrame-1)*sizeof(FightAnimationStruct));


CurrentOffset = fs_seek(MoveArchive, MoveOffset+2, 0);
fs_read(MoveArchive, VoiceClipChecker, 2);
fs_read(MoveArchive, SizeX, 2);
fs_read(MoveArchive, SizeY, 2);
fs_read(MoveArchive, ScreenPositionX, 2);
fs_read(MoveArchive, ScreenPositionY, 2);
fs_read(MoveArchive, FrameID, 1);
fs_read(MoveArchive, FightAnimationSpeed, 1);
fs_read(MoveArchive, EndIt, 1);

CurrentOffset = fs_seek(MoveArchive, MoveOffset+16, 0);
fs_read(MoveArchive, TextureSizeX, 4);
fs_read(MoveArchive, TextureSizeY, 4);

fs_close(MoveArchive);

}

void ReadNewRoundAnimation(char WhichRound, char WhichFrame, char* FrameID, char* FightAnimationSpeed, int* TextureSizeX, int* TextureSizeY, short* SizeX, short* SizeY, short* ScreenPositionX, short* ScreenPositionY, short* VoiceClipChecker, char* EndIt, char MountPoint[]){

file_t MoveArchive;

int Bluff;
char MVTFile[NormalFileDirSize];
long CurrentOffset;
long MoveOffset;

long OffsetOffset = 0;

Bluff = sprintf(MVTFile, "/ram/%s", MountPoint);

MoveArchive = fs_open(MVTFile, O_RDONLY);

CurrentOffset = fs_seek(MoveArchive, HeaderSizeRoundAnimationRegister+((WhichRound-1)*4), 0);
fs_read(MoveArchive, &OffsetOffset, 4);

MoveOffset = (WhichFrame-1)*sizeof(FightAnimationStruct)+OffsetOffset;

CurrentOffset = fs_seek(MoveArchive, MoveOffset+2, 0);
fs_read(MoveArchive, VoiceClipChecker, 2);
fs_read(MoveArchive, SizeX, 2);
fs_read(MoveArchive, SizeY, 2);
fs_read(MoveArchive, ScreenPositionX, 2);
fs_read(MoveArchive, ScreenPositionY, 2);
fs_read(MoveArchive, FrameID, 1);
fs_read(MoveArchive, FightAnimationSpeed, 1);
fs_read(MoveArchive, EndIt, 1);

CurrentOffset = fs_seek(MoveArchive, MoveOffset+16, 0);
fs_read(MoveArchive, TextureSizeX, 4);
fs_read(MoveArchive, TextureSizeY, 4);



fs_close(MoveArchive);

}

void DrawContinueCountDown(char TimerValue, int ScreenPositionX, int ScreenPositionY, int Size, TimerStruct TimerHeaderData, FontSingleCharacterStruct TimerCharacterData[], pvr_ptr_t NewTimerTexture, uint8 TextureType){

    int WhichValue;
    uint32 FormatValue;

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    WhichValue = TimerValue;

    if(TextureType == PaletteType) FormatValue = (PVR_TXRFMT_PAL8BPP | PVR_TXRFMT_8BPP_PAL(AdditionalAnimationPalette));
    else FormatValue = PVR_TXRFMT_ARGB4444;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, FormatValue, TimerHeaderData.TextureSizeX, TimerHeaderData.TextureSizeY, NewTimerTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = UpperGuiPositionZ1;
    vert.u = TimerCharacterData[WhichValue].FilePositionX1;
    vert.v = TimerCharacterData[WhichValue].FilePositionY1;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+Size;
    vert.y = ScreenPositionY;
    vert.z = UpperGuiPositionZ1;
    vert.u = TimerCharacterData[WhichValue].FilePositionX2;
    vert.v = TimerCharacterData[WhichValue].FilePositionY1;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+Size;
    vert.z = UpperGuiPositionZ1;
    vert.u = TimerCharacterData[WhichValue].FilePositionX1;
    vert.v = TimerCharacterData[WhichValue].FilePositionY2;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+Size;
    vert.y = ScreenPositionY+Size;
    vert.z = UpperGuiPositionZ1;
    vert.u = TimerCharacterData[WhichValue].FilePositionX2;
    vert.v = TimerCharacterData[WhichValue].FilePositionY2;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));


}



/*
void DeLoadFightAnimationSoundEffect(sfxhnd_t FightAnimationSoundEffect[], short SoundEffectAmount){

while(SoundEffectAmount > 0){
snd_sfx_unload(FightAnimationSoundEffect[SoundEffectAmount]);
SoundEffectAmount--;
}
}
*/