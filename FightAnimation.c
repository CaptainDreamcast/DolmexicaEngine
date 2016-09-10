void LoadFightAnimationSoundEffect(sfxhnd_t FightAnimationSoundEffect[], char MountPoint[]){

file_t RegisterFile;

int DirtyDeedsDoneDirtCheap;
char FileDir[NormalFileDirSize];
char NewMountPoint[NormalMountPointSize];
uint8* RomDiskBuffer;
long RomDiskSize;

short SoundEffectAmount;

sprintf(FileDir, "/ram/%s", MountPoint);

RegisterFile = FileOpen(FileDir, O_RDONLY);
FileSeek(RegisterFile, FightAnimationSoundEffectAmountOffset, 0);
FileRead(RegisterFile, &SoundEffectAmount, 2);
FileClose(RegisterFile);

if(SoundEffectAmount > 0){

sprintf(FileDir, "%s/ANIMATIONS/%s.sfa", FileSystemUsed, MountPoint);
sprintf(NewMountPoint, "/%s", MountPoint);
RegisterFile = FileOpen(FileDir, O_RDONLY);
RomDiskSize = FileTotal(RegisterFile);
RomDiskBuffer = (uint8 *)malloc(RomDiskSize);
FileRead(RegisterFile, RomDiskBuffer, RomDiskSize);
fs_romdisk_mount(NewMountPoint, RomDiskBuffer, 1);
FileClose(RegisterFile);



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

RegisterFile = FileOpen(FileDir, O_RDONLY);
FileSeek(RegisterFile, FightAnimationSoundEffectAmountOffset, 0);
FileRead(RegisterFile, &SoundEffectAmount, 2);
FileClose(RegisterFile);

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

char* RegisterContent;

long RomDiskSize;

char RomDiskDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];

//--------------------FightAnimation Start------------------------

sprintf(RomDiskDir, "%s/ANIMATIONS/FIGHTANIMATION.fam", FileSystemUsed);

sprintf(MountPoint, "/ram/FIGHTANIMATION");

RomDiskFile = FileOpen(RomDiskDir, O_RDONLY);

if(RomDiskFile != FILEHND_INVALID){

*FightAnimationFlags |= FightAnimationFlag;

RomDiskSize = FileTotal(RomDiskFile);

RegisterContent = (char *)malloc(RomDiskSize);

FileRead(RomDiskFile, RegisterContent, RomDiskSize);

FileClose(RomDiskFile);

RomDiskFile = FileOpen(MountPoint, O_WRONLY);

FileWrite(RomDiskFile, RegisterContent, RomDiskSize);

FileClose(RomDiskFile);

free(RegisterContent);


sprintf(MountPoint, "FIGHTANIMATION");
LoadFightAnimationSoundEffect(FightAnimationSoundEffect[FightAnimationSoundEffectIdentifier], MountPoint);


sprintf(RomDiskDir, "%s/ANIMATIONS/FIGHTANIMATION.faa", FileSystemUsed);
sprintf(MountPoint, "/FIGHTANIMATION");

RomDiskFile = FileOpen(RomDiskDir, O_RDONLY);

RomDiskSize = FileTotal(RomDiskFile);

RomDiskBufferFightAnimation = (uint8 *)malloc(RomDiskSize);

FileRead(RomDiskFile, RomDiskBufferFightAnimation, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBufferFightAnimation, 1);

FileClose(RomDiskFile);

}



//--------------------FightAnimation END------------------------


//--------------------RoundAnimation Start------------------------

sprintf(RomDiskDir, "%s/ANIMATIONS/ROUNDANIMATION.ram", FileSystemUsed);

sprintf(MountPoint, "/ram/ROUNDANIMATION");

RomDiskFile = FileOpen(RomDiskDir, O_RDONLY);

if(RomDiskFile != FILEHND_INVALID){

*FightAnimationFlags |= RoundAnimationFlag;

RomDiskSize = FileTotal(RomDiskFile);

RegisterContent = (char *)malloc(RomDiskSize);

FileRead(RomDiskFile, RegisterContent, RomDiskSize);

FileClose(RomDiskFile);

RomDiskFile = FileOpen(MountPoint, O_WRONLY);

FileWrite(RomDiskFile, RegisterContent, RomDiskSize);

FileClose(RomDiskFile);

free(RegisterContent);


sprintf(MountPoint, "ROUNDANIMATION");
LoadFightAnimationSoundEffect(FightAnimationSoundEffect[RoundAnimationSoundEffectIdentifier], MountPoint);


sprintf(RomDiskDir, "%s/ANIMATIONS/ROUNDANIMATION.raa", FileSystemUsed);
sprintf(MountPoint, "/ROUNDANIMATION");

RomDiskFile = FileOpen(RomDiskDir, O_RDONLY);

RomDiskSize = FileTotal(RomDiskFile);

RomDiskBufferRoundAnimation = (uint8 *)malloc(RomDiskSize);

FileRead(RomDiskFile, RomDiskBufferRoundAnimation, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBufferRoundAnimation, 1);

FileClose(RomDiskFile);

}

//--------------------RoundAnimation END------------------------

//--------------------PerfectAnimation Start------------------------

sprintf(RomDiskDir, "%s/ANIMATIONS/PERFECTANIMATION.pam", FileSystemUsed);

sprintf(MountPoint, "/ram/PERFECTANIMATION");

RomDiskFile = FileOpen(RomDiskDir, O_RDONLY);

if(RomDiskFile != FILEHND_INVALID){

*FightAnimationFlags |= PerfectAnimationFlag;

RomDiskSize = FileTotal(RomDiskFile);

RegisterContent = (char *)malloc(RomDiskSize);

FileRead(RomDiskFile, RegisterContent, RomDiskSize);

FileClose(RomDiskFile);

RomDiskFile = FileOpen(MountPoint, O_WRONLY);

FileWrite(RomDiskFile, RegisterContent, RomDiskSize);

FileClose(RomDiskFile);

free(RegisterContent);


sprintf(MountPoint, "PERFECTANIMATION");
LoadFightAnimationSoundEffect(FightAnimationSoundEffect[PerfectAnimationSoundEffectIdentifier], MountPoint);


sprintf(RomDiskDir, "%s/ANIMATIONS/PERFECTANIMATION.paa", FileSystemUsed);
sprintf(MountPoint, "/PERFECTANIMATION");

RomDiskFile = FileOpen(RomDiskDir, O_RDONLY);

RomDiskSize = FileTotal(RomDiskFile);

RomDiskBufferPerfectAnimation = (uint8 *)malloc(RomDiskSize);

FileRead(RomDiskFile, RomDiskBufferPerfectAnimation, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBufferPerfectAnimation, 1);

FileClose(RomDiskFile);

}

//--------------------PerfectAnimation END------------------------

//--------------------ContinueAnimation Start------------------------

sprintf(RomDiskDir, "%s/ANIMATIONS/CONTINUEANIMATION.cam", FileSystemUsed);

sprintf(MountPoint, "/ram/CONTINUEANIMATION");

RomDiskFile = FileOpen(RomDiskDir, O_RDONLY);

if(RomDiskFile != FILEHND_INVALID){

*FightAnimationFlags |= ContinueAnimationFlag;

RomDiskSize = FileTotal(RomDiskFile);

RegisterContent = (char *)malloc(RomDiskSize);

FileRead(RomDiskFile, RegisterContent, RomDiskSize);

FileClose(RomDiskFile);

RomDiskFile = FileOpen(MountPoint, O_WRONLY);

FileWrite(RomDiskFile, RegisterContent, RomDiskSize);

FileClose(RomDiskFile);

free(RegisterContent);


sprintf(MountPoint, "CONTINUEANIMATION");
LoadFightAnimationSoundEffect(FightAnimationSoundEffect[ContinueAnimationSoundEffectIdentifier], MountPoint);


sprintf(RomDiskDir, "%s/ANIMATIONS/CONTINUEANIMATION.caa", FileSystemUsed);
sprintf(MountPoint, "/CONTINUEANIMATION");

RomDiskFile = FileOpen(RomDiskDir, O_RDONLY);

RomDiskSize = FileTotal(RomDiskFile);

RomDiskBufferContinueAnimation = (uint8 *)malloc(RomDiskSize);

FileRead(RomDiskFile, RomDiskBufferContinueAnimation, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBufferContinueAnimation, 1);

FileClose(RomDiskFile);

}

//--------------------ContinueAnimation END------------------------

//--------------------NewRivalAnimation Start------------------------

sprintf(RomDiskDir, "%s/ANIMATIONS/JOININANIMATION.jam", FileSystemUsed);

sprintf(MountPoint, "/ram/JOININANIMATION");

RomDiskFile = FileOpen(RomDiskDir, O_RDONLY);

if(RomDiskFile != FILEHND_INVALID){

*FightAnimationFlags |= NewRivalAnimationFlag;

RomDiskSize = FileTotal(RomDiskFile);

RegisterContent = (char *)malloc(RomDiskSize);

FileRead(RomDiskFile, RegisterContent, RomDiskSize);

FileClose(RomDiskFile);

RomDiskFile = FileOpen(MountPoint, O_WRONLY);

FileWrite(RomDiskFile, RegisterContent, RomDiskSize);

FileClose(RomDiskFile);

free(RegisterContent);


sprintf(MountPoint, "JOININANIMATION");
LoadFightAnimationSoundEffect(FightAnimationSoundEffect[ContinueAnimationSoundEffectIdentifier], MountPoint);


sprintf(RomDiskDir, "%s/ANIMATIONS/JOININANIMATION.jaa", FileSystemUsed);
sprintf(MountPoint, "/JOININANIMATION");

RomDiskFile = FileOpen(RomDiskDir, O_RDONLY);

RomDiskSize = FileTotal(RomDiskFile);

RomDiskBufferContinueAnimation = (uint8 *)malloc(RomDiskSize);

FileRead(RomDiskFile, RomDiskBufferContinueAnimation, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBufferContinueAnimation, 1);

FileClose(RomDiskFile);

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
FileUnlink(MountPoint);
}

if(FightAnimationFlags & RoundAnimationFlag){
sprintf(MountPoint, "ROUNDANIMATION");
DeLoadFightAnimationSoundEffect(FightAnimationSoundEffect[RoundAnimationSoundEffectIdentifier], MountPoint);
sprintf(MountPoint, "/ROUNDANIMATION");
fs_romdisk_unmount(MountPoint);
sprintf(MountPoint, "/ram/ROUNDANIMATION");
FileUnlink(MountPoint);
}

if(FightAnimationFlags & PerfectAnimationFlag){
sprintf(MountPoint, "PERFECTANIMATION");
DeLoadFightAnimationSoundEffect(FightAnimationSoundEffect[PerfectAnimationSoundEffectIdentifier], MountPoint);
sprintf(MountPoint, "/PERFECTANIMATION");
fs_romdisk_unmount(MountPoint);
sprintf(MountPoint, "/ram/PERFECTANIMATION");
FileUnlink(MountPoint);
}

if(FightAnimationFlags & ContinueAnimationFlag){
sprintf(MountPoint, "CONTINUEANIMATION");
DeLoadFightAnimationSoundEffect(FightAnimationSoundEffect[ContinueAnimationSoundEffectIdentifier], MountPoint);
sprintf(MountPoint, "/CONTINUEANIMATION");
fs_romdisk_unmount(MountPoint);
sprintf(MountPoint, "/ram/CONTINUEANIMATION");
FileUnlink(MountPoint);
}

if(FightAnimationFlags & NewRivalAnimationFlag){
sprintf(MountPoint, "JOININANIMATION");
DeLoadFightAnimationSoundEffect(FightAnimationSoundEffect[ContinueAnimationSoundEffectIdentifier], MountPoint);
sprintf(MountPoint, "/JOININANIMATION");
fs_romdisk_unmount(MountPoint);
sprintf(MountPoint, "/ram/JOININANIMATION");
FileUnlink(MountPoint);
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

char MVTFile[NormalFileDirSize];
long MoveOffset;



sprintf(MVTFile, "/ram/%s", MountPoint);

MoveArchive = FileOpen(MVTFile, O_RDONLY);

MoveOffset = HeaderSizeFightAnimation+((WhichFrame-1)*sizeof(FightAnimationStruct));


FileSeek(MoveArchive, MoveOffset+2, 0);
FileRead(MoveArchive, VoiceClipChecker, 2);
FileRead(MoveArchive, SizeX, 2);
FileRead(MoveArchive, SizeY, 2);
FileRead(MoveArchive, ScreenPositionX, 2);
FileRead(MoveArchive, ScreenPositionY, 2);
FileRead(MoveArchive, FrameID, 1);
FileRead(MoveArchive, FightAnimationSpeed, 1);
FileRead(MoveArchive, EndIt, 1);

FileSeek(MoveArchive, MoveOffset+16, 0);
FileRead(MoveArchive, TextureSizeX, 4);
FileRead(MoveArchive, TextureSizeY, 4);

FileClose(MoveArchive);

}

void ReadNewRoundAnimation(char WhichRound, char WhichFrame, char* FrameID, char* FightAnimationSpeed, int* TextureSizeX, int* TextureSizeY, short* SizeX, short* SizeY, short* ScreenPositionX, short* ScreenPositionY, short* VoiceClipChecker, char* EndIt, char MountPoint[]){

file_t MoveArchive;

char MVTFile[NormalFileDirSize];
long MoveOffset;

long OffsetOffset = 0;

sprintf(MVTFile, "/ram/%s", MountPoint);

MoveArchive = FileOpen(MVTFile, O_RDONLY);

FileSeek(MoveArchive, HeaderSizeRoundAnimationRegister+((WhichRound-1)*4), 0);
FileRead(MoveArchive, &OffsetOffset, 4);

MoveOffset = (WhichFrame-1)*sizeof(FightAnimationStruct)+OffsetOffset;

FileSeek(MoveArchive, MoveOffset+2, 0);
FileRead(MoveArchive, VoiceClipChecker, 2);
FileRead(MoveArchive, SizeX, 2);
FileRead(MoveArchive, SizeY, 2);
FileRead(MoveArchive, ScreenPositionX, 2);
FileRead(MoveArchive, ScreenPositionY, 2);
FileRead(MoveArchive, FrameID, 1);
FileRead(MoveArchive, FightAnimationSpeed, 1);
FileRead(MoveArchive, EndIt, 1);

FileSeek(MoveArchive, MoveOffset+16, 0);
FileRead(MoveArchive, TextureSizeX, 4);
FileRead(MoveArchive, TextureSizeY, 4);



FileClose(MoveArchive);

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