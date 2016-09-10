uint8 FetchCharacterAmount(int WhichMode, short* CharAmount){

file_t CharacterArchive;

char CharArchive[NormalFileDirSize];
char MountPoint[NormalMountPointSize];


switch(WhichMode){
case ArcadeModeIdentifier:
sprintf(MountPoint, "/ARCADE");
break;
case SurvivalModeIdentifier:
sprintf(MountPoint, "/SURVIVAL");
break;
case StoryModeIdentifier:
sprintf(MountPoint, "/STORY");
break;

}


sprintf(CharArchive, "%s%s/CHARACTERS.lst", FileSystemUsed, MountPoint);

if(!FileExists(CharArchive)) return(0);

CharacterArchive = FileOpen(CharArchive, O_RDONLY);
FileSeek(CharacterArchive, 0, 0);
FileRead(CharacterArchive, CharAmount, 2);

FileClose(CharacterArchive);

if(*CharAmount == 0) return(0);
else return(1);
}


void DrawSpecialTexture(pvr_ptr_t TextureUsed, FighterSelectSpecialStruct* FighterSelectSpecialBuffer){

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    float FilePositionLeft, FilePositionRight;
    int TruePositionLeft, TruePositionRight;

    FilePositionLeft = (1.0/FighterSelectSpecialBuffer->SizeX)*(FighterSelectSpecialBuffer->PositionLeft);
    FilePositionRight = 1.0;
    TruePositionRight = FighterSelectSpecialBuffer->ScreenPositionX+FighterSelectSpecialBuffer->SizeX-(FighterSelectSpecialBuffer->PositionLeft);
    TruePositionLeft = FighterSelectSpecialBuffer->ScreenPositionX;


    do{

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, FighterSelectSpecialBuffer->TextureSizeX, FighterSelectSpecialBuffer->TextureSizeY, TextureUsed, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = TruePositionLeft;
    vert.y = FighterSelectSpecialBuffer->ScreenPositionY;
    vert.z = 5;
    vert.u = FilePositionLeft;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = TruePositionRight;
    vert.y = FighterSelectSpecialBuffer->ScreenPositionY;
    vert.z = 5;
    vert.u = FilePositionRight;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = TruePositionLeft;
    vert.y = FighterSelectSpecialBuffer->ScreenPositionY+FighterSelectSpecialBuffer->SizeY;
    vert.z = 5;
    vert.u = FilePositionLeft;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = TruePositionRight;
    vert.y = FighterSelectSpecialBuffer->ScreenPositionY+FighterSelectSpecialBuffer->SizeY;
    vert.z = 5;
    vert.u = FilePositionRight;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

    FilePositionRight = FilePositionLeft;
    FilePositionLeft = 0;
    TruePositionLeft = TruePositionRight;
    TruePositionRight = TruePositionLeft+FighterSelectSpecialBuffer->PositionLeft;

} while(FilePositionRight != 0.0);

FighterSelectSpecialBuffer->PositionLeft++;
if(FighterSelectSpecialBuffer->PositionLeft >= FighterSelectSpecialBuffer->SizeX) FighterSelectSpecialBuffer->PositionLeft = 0;
}

void DrawFighterSelectBackGround(pvr_ptr_t BackGroundTexture){
  
    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
  
    if(BackGroundTexture != 0){

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 512, 512, BackGroundTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = 0;
    vert.y = 0;
    vert.z = 1;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 640;
    vert.y = 0;
    vert.z = 1;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 0;
    vert.y = 480;
    vert.z = 1;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 640;
    vert.y = 480;
    vert.z = 1;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));
}

}

void DrawSpecialColorTransparencyFrame(int ScreenPositionX, int ScreenPositionY, int SizeX, int SizeY, int Width, int Ticks, char SelectionDone, char Color){

   pvr_poly_cxt_t cxt;
   pvr_poly_hdr_t hdr;
   pvr_vertex_t vert;
   
   float CurrentTransparency;
   float Red, Green, Blue;

   if(SelectionDone == 0) CurrentTransparency = 0.01 * Ticks;
   else CurrentTransparency = 0.2 * Ticks;   

   int WidthOffset = (Width-1)/2;

    if(Color == 1){ Red = 1.0f; Green = 0.0f; Blue = 0.0f; }
    else if(Color == 2){ Red = 0.0f; Green = 0.0f; Blue = 1.0f; }
    else{ Red = 0.0f; Green = 0.0f; Blue = 0.0f; }

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 16, 16, LoadingBackGroundTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

//-------

    vert.argb = PVR_PACK_COLOR(CurrentTransparency, Red, Green, Blue);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX-WidthOffset;
    vert.y = ScreenPositionY-WidthOffset;
    vert.z = 4;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));
    //Correct


    vert.x = ScreenPositionX+SizeX+WidthOffset;
    vert.y = ScreenPositionY-WidthOffset;
    vert.z = 4;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX-WidthOffset;
    vert.y = ScreenPositionY+WidthOffset;
    vert.z = 4;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX+WidthOffset;
    vert.y = ScreenPositionY+WidthOffset;
    vert.z = 4;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

//--------

    vert.argb = PVR_PACK_COLOR(CurrentTransparency, Red, Green, Blue);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX-WidthOffset;
    vert.y = ScreenPositionY+SizeY-WidthOffset;
    vert.z = 4;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));


    vert.x = ScreenPositionX+SizeX+WidthOffset;
    vert.y = ScreenPositionY+SizeY-WidthOffset;
    vert.z = 4;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX-WidthOffset;
    vert.y = ScreenPositionY+SizeY+WidthOffset;
    vert.z = 4;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX+WidthOffset;
    vert.y = ScreenPositionY+SizeY+WidthOffset;
    vert.z = 4;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

//--------

    vert.argb = PVR_PACK_COLOR(CurrentTransparency, Red, Green, Blue);;
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX-WidthOffset;
    vert.y = ScreenPositionY-WidthOffset;
    vert.z = 4;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+WidthOffset;
    vert.y = ScreenPositionY-WidthOffset;
    vert.z = 4;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX-WidthOffset;
    vert.y = ScreenPositionY+SizeY+WidthOffset;
    vert.z = 4;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+WidthOffset;
    vert.y = ScreenPositionY+SizeY+WidthOffset;
    vert.z = 4;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

//--------

    vert.argb = PVR_PACK_COLOR(CurrentTransparency, Red, Green, Blue);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX+SizeX-WidthOffset;
    vert.y = ScreenPositionY-WidthOffset;
    vert.z = 4;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX+WidthOffset;
    vert.y = ScreenPositionY-WidthOffset;
    vert.z = 4;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX-WidthOffset;
    vert.y = ScreenPositionY+SizeY+WidthOffset;
    vert.z = 4;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX+WidthOffset;
    vert.y = ScreenPositionY+SizeY+WidthOffset;
    vert.z = 4;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

}

void LoadFighterSelectHeader(FighterSelectHeaderStruct FighterSelectHeaderBuffer[], FighterSelectSpecialStruct* FighterSelectSpecialBuffer, pvr_ptr_t* BonusTexture, pvr_ptr_t FrameTexture[], pvr_ptr_t* BackGroundTexture, int WhichMode, sfxhnd_t SoundEffects[]){

file_t HeaderFile;

char FileDir[NormalFileDirSize];
char OtherFileDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];

int BluffX;
int BluffY;

int CurrentChar;


switch(WhichMode){
case ArcadeModeIdentifier:
sprintf(MountPoint, "/ARCADE");
break;
case SurvivalModeIdentifier:
sprintf(MountPoint, "/SURVIVAL");
break;
case StoryModeIdentifier:
sprintf(MountPoint, "/STORY");
break;
}



sprintf(FileDir, "%s%s/SFX.img", FileSystemUsed, MountPoint);
FileDirToRomDisk(FileDir, MountPoint);

sprintf(FileDir, "%s/SELECT.wav", MountPoint);
SoundEffects[MenuSelectSoundEffectIdentifier] = snd_sfx_load(FileDir);

sprintf(FileDir, "%s/SELECTED.wav", MountPoint);
SoundEffects[MenuSelectedSoundEffectIdentifier] = snd_sfx_load(FileDir);

sprintf(FileDir, "%s/DENIED.wav", MountPoint);
SoundEffects[MenuDeniedSoundEffectIdentifier] = snd_sfx_load(FileDir);

fs_romdisk_unmount(MountPoint);



sprintf(FileDir, "%s%s/BIGPORTRAITS.img", FileSystemUsed, MountPoint);
FileDirToRomDisk(FileDir, "/BIGPORTRAITS");

sprintf(FileDir, "%s%s/NAMES.img", FileSystemUsed, MountPoint);
FileDirToRomDisk(FileDir, "/NAMES");

sprintf(FileDir, "%s%s/LOGOS.img", FileSystemUsed, MountPoint);
FileDirToRomDisk(FileDir, "/LOGOS");


sprintf(OtherFileDir, "%s/FALLBACK/BIGPORTRAIT.pkg", FileSystemUsed);
sprintf(FileDir, "/ram/BIGPORTRAIT.pkg");
FileCopyToOtherFileSystem(OtherFileDir, FileDir);

sprintf(OtherFileDir, "%s/FALLBACK/NAME.pkg", FileSystemUsed);
sprintf(FileDir, "/ram/NAME.pkg");
FileCopyToOtherFileSystem(OtherFileDir, FileDir);


sprintf(FileDir, "%s%s/FIGHTERSELECT.hdr", FileSystemUsed, MountPoint);

HeaderFile = FileOpen(FileDir, O_RDONLY);
FileSeek(HeaderFile, 0, 0);

CurrentChar = CharacterOne;
do{

FileRead(HeaderFile, &FighterSelectHeaderBuffer[CurrentChar], sizeof(FighterSelectHeaderStruct));

CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);

sprintf(FileDir, "%s%s/TEXTURES.img", FileSystemUsed, MountPoint);
FileDirToRomDisk(FileDir, MountPoint);

FileRead(HeaderFile, FighterSelectSpecialBuffer, sizeof(FighterSelectSpecialStruct));

if(FighterSelectSpecialBuffer->ThisBonusIsScrolling != 0){

sprintf(FileDir, "%s/%d.pkg", MountPoint, FighterSelectSpecialBuffer->ThisBonusIsScrolling);

*BonusTexture = pvr_mem_malloc((FighterSelectSpecialBuffer->TextureSizeX)*(FighterSelectSpecialBuffer->TextureSizeY)*2);
TextureLoadPKG(FileDir, BonusTexture, &BluffX, &BluffY, ReAllocateTextureMemory);

}
FileClose(HeaderFile);

CurrentChar = CharacterOne;
do{

sprintf(FileDir, "%s/FRAME%d.pkg", MountPoint, CurrentChar);
FrameTexture[CurrentChar] = pvr_mem_malloc(128*128*2);
TextureLoadPKG(FileDir, &FrameTexture[CurrentChar], &BluffX, &BluffY, ReAllocateTextureMemory);

CurrentChar++;
} while(CurrentChar <= MaxCharsOnScreen); 

sprintf(FileDir, "%s/BACKGROUND.pkg", MountPoint);
if(FileExists(FileDir)){
*BackGroundTexture = pvr_mem_malloc(512*512*2);
TextureLoadPKG(FileDir, BackGroundTexture, &BluffX, &BluffY, NoAllocateTextureMemory);
}
else *BackGroundTexture = 0;

fs_romdisk_unmount(MountPoint);


sprintf(FileDir, "%s%s/FIGHTERSELECT.ogg", FileSystemUsed, MountPoint);
SoundPlay(FileDir, FighterSelectTrack);
}

void LoadSelectableCharacters(FighterSelectSmallPortraitStruct FighterSelectSmallPortraitBuffer[], pvr_ptr_t SmallPortraitTextures[], int WhichMode){

file_t CharacterArchive;

char OriginalCharArchive[NormalFileDirSize];
char CharArchive[NormalFileDirSize];
char FileDirPortrait[NormalFileDirSize];
char MountPoint[NormalMountPointSize];

short CharacterAmount = 0;
long DesiredOffset = 0;
int CurrentLoadedCharacter = 0;

switch(WhichMode){
case ArcadeModeIdentifier:
sprintf(MountPoint, "/ARCADE");
break;
case SurvivalModeIdentifier:
sprintf(MountPoint, "/SURVIVAL");
break;
case StoryModeIdentifier:
sprintf(MountPoint, "/STORY");
break;
}

sprintf(CharArchive, "%s%s/FIGHTERSELECT.ogg", FileSystemUsed, MountPoint);
SoundLoad(CharArchive);

sprintf(CharArchive, "%s%s/SMALLPORTRAITS.img", FileSystemUsed, MountPoint);
FileDirToRomDisk(CharArchive, MountPoint);

sprintf(OriginalCharArchive, "%s%s/CHARACTERS.lst", FileSystemUsed, MountPoint);
sprintf(CharArchive, "/ram/CHARACTERS.lst");
FileCopyToOtherFileSystem(OriginalCharArchive, CharArchive);

CharacterArchive = FileOpen(CharArchive, O_RDONLY);

FileSeek(CharacterArchive, DesiredOffset, 0);
FileRead(CharacterArchive, &CharacterAmount, 2);
DesiredOffset+=HeaderSizeCharacterArchive;
FileSeek(CharacterArchive, DesiredOffset, 0);


sprintf(OriginalCharArchive, "%s/FALLBACK/SMALLPORTRAIT.pkg", FileSystemUsed);
sprintf(FileDirPortrait, "/ram/SMALLPORTRAIT.pkg");
FileCopyToOtherFileSystem(OriginalCharArchive, FileDirPortrait);

while(CurrentLoadedCharacter < CharacterAmount){

 FileRead(CharacterArchive, &FighterSelectSmallPortraitBuffer[CurrentLoadedCharacter], sizeof(FighterSelectSmallPortraitStruct));

 sprintf(FileDirPortrait, "%s/%.8s.pkg", MountPoint, FighterSelectSmallPortraitBuffer[CurrentLoadedCharacter].CharacterName);

 SmallPortraitTextures[CurrentLoadedCharacter] = pvr_mem_malloc(2*2*2);
 if(!FileExists(FileDirPortrait)) sprintf(FileDirPortrait, "/ram/SMALLPORTRAIT.pkg");
 TextureLoadPKG(FileDirPortrait, &SmallPortraitTextures[CurrentLoadedCharacter], &FighterSelectSmallPortraitBuffer[CurrentLoadedCharacter].TextureSizeX, &FighterSelectSmallPortraitBuffer[CurrentLoadedCharacter].TextureSizeY, ReAllocateTextureMemory);


 CurrentLoadedCharacter++;
 }

FileUnlink("/ram/SMALLPORTRAIT.pkg");

fs_romdisk_unmount(MountPoint);

FileClose(CharacterArchive);
FileUnlink(CharArchive);
}

void LoadFighterSelectBigPortraitFirst(char CharacterName[], pvr_ptr_t* BigPortraitTexture, pvr_ptr_t* NameTexture){

char FileDir[NormalFileDirSize];
int BluffX;
int BluffY;

sprintf(FileDir, "/BIGPORTRAITS/%.8s.pkg", CharacterName);
*BigPortraitTexture = pvr_mem_malloc(256*256*2);
if(!FileExists(FileDir)) sprintf(FileDir, "/ram/BIGPORTRAIT.pkg");
TextureLoadPKG(FileDir, BigPortraitTexture, &BluffX, &BluffY, NoAllocateTextureMemory);

sprintf(FileDir, "/NAMES/%.8s.pkg", CharacterName);
*NameTexture = pvr_mem_malloc(256*64*2);
if(!FileExists(FileDir)) sprintf(FileDir, "/ram/NAME.pkg");
TextureLoadPKG(FileDir, NameTexture, &BluffX, &BluffY, NoAllocateTextureMemory);

}

void LoadFighterSelectBigPortrait(char CharacterName[], pvr_ptr_t* BigPortraitTexture, pvr_ptr_t* NameTexture){

char FileDir[NormalFileDirSize];
int BluffX;
int BluffY;

sprintf(FileDir, "/BIGPORTRAITS/%.8s.pkg", CharacterName);
if(!FileExists(FileDir)) sprintf(FileDir, "/ram/BIGPORTRAIT.pkg");
TextureLoadPKG(FileDir, BigPortraitTexture, &BluffX, &BluffY, ReAllocateTextureMemory);


sprintf(FileDir, "/NAMES/%.8s.pkg", CharacterName);
if(!FileExists(FileDir)) sprintf(FileDir, "/ram/NAME.pkg");
TextureLoadPKG(FileDir, NameTexture, &BluffX, &BluffY, ReAllocateTextureMemory);


}

void DrawFighterSelectBigPortrait(pvr_ptr_t* BigPortraitTexture, pvr_ptr_t* NameTexture, pvr_ptr_t FrameTexture, int PortraitExists, FighterSelectHeaderStruct FighterSelectHeaderBuffer, int Mirrored){

   float FilePositionLeft, FilePositionRight;

   if(Mirrored == 1){ FilePositionLeft = 1.0; FilePositionRight = 0.0; }
   else{ FilePositionLeft = 0.0; FilePositionRight = 1.0;}


   pvr_poly_cxt_t cxt;
   pvr_poly_hdr_t hdr;
   pvr_vertex_t vert;

   if(PortraitExists != 0){

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 256, 256, *BigPortraitTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = FighterSelectHeaderBuffer.BigPortraitScreenPositionX;
    vert.y = FighterSelectHeaderBuffer.BigPortraitScreenPositionY;
    vert.z = 2;
    vert.u = FilePositionLeft;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = FighterSelectHeaderBuffer.BigPortraitScreenPositionX+FighterSelectHeaderBuffer.BigPortraitSizeX;
    vert.y = FighterSelectHeaderBuffer.BigPortraitScreenPositionY;
    vert.z = 2;
    vert.u = FilePositionRight;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = FighterSelectHeaderBuffer.BigPortraitScreenPositionX;
    vert.y = FighterSelectHeaderBuffer.BigPortraitScreenPositionY+FighterSelectHeaderBuffer.BigPortraitSizeY;
    vert.z = 2;
    vert.u = FilePositionLeft;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = FighterSelectHeaderBuffer.BigPortraitScreenPositionX+FighterSelectHeaderBuffer.BigPortraitSizeX;
    vert.y = FighterSelectHeaderBuffer.BigPortraitScreenPositionY+FighterSelectHeaderBuffer.BigPortraitSizeY;
    vert.z = 2;
    vert.u = FilePositionRight;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

    //------------

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 128, 128, FrameTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = FighterSelectHeaderBuffer.BigPortraitScreenPositionX;
    vert.y = FighterSelectHeaderBuffer.BigPortraitScreenPositionY;
    vert.z = 3;
    vert.u = FilePositionLeft;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = FighterSelectHeaderBuffer.BigPortraitScreenPositionX+FighterSelectHeaderBuffer.BigPortraitSizeX;
    vert.y = FighterSelectHeaderBuffer.BigPortraitScreenPositionY;
    vert.z = 3;
    vert.u = FilePositionRight;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = FighterSelectHeaderBuffer.BigPortraitScreenPositionX;
    vert.y = FighterSelectHeaderBuffer.BigPortraitScreenPositionY+FighterSelectHeaderBuffer.BigPortraitSizeY;
    vert.z = 3;
    vert.u = FilePositionLeft;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = FighterSelectHeaderBuffer.BigPortraitScreenPositionX+FighterSelectHeaderBuffer.BigPortraitSizeX;
    vert.y = FighterSelectHeaderBuffer.BigPortraitScreenPositionY+FighterSelectHeaderBuffer.BigPortraitSizeY;
    vert.z = 3;
    vert.u = FilePositionRight;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

    //------------

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 256, 64, *NameTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = FighterSelectHeaderBuffer.NameScreenPositionX;
    vert.y = FighterSelectHeaderBuffer.NameScreenPositionY;
    vert.z = 4;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = FighterSelectHeaderBuffer.NameScreenPositionX+FighterSelectHeaderBuffer.NameSizeX;
    vert.y = FighterSelectHeaderBuffer.NameScreenPositionY;
    vert.z = 4;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = FighterSelectHeaderBuffer.NameScreenPositionX;
    vert.y = FighterSelectHeaderBuffer.NameScreenPositionY+FighterSelectHeaderBuffer.NameSizeY;
    vert.z = 4;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = FighterSelectHeaderBuffer.NameScreenPositionX+FighterSelectHeaderBuffer.NameSizeX;
    vert.y = FighterSelectHeaderBuffer.NameScreenPositionY+FighterSelectHeaderBuffer.NameSizeY;
    vert.z = 4;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));
    }
}

void DrawFrameTexture(pvr_ptr_t FrameTexture, FighterSelectSmallPortraitStruct PortraitBuffer, float CurrentTransparency){

   pvr_poly_cxt_t cxt;
   pvr_poly_hdr_t hdr;
   pvr_vertex_t vert;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 128, 128, FrameTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(CurrentTransparency, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = PortraitBuffer.PositionX;
    vert.y = PortraitBuffer.PositionY;
    vert.z = 4;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PortraitBuffer.PositionX+PortraitBuffer.SizeX;
    vert.y = PortraitBuffer.PositionY;
    vert.z = 4;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PortraitBuffer.PositionX;
    vert.y = PortraitBuffer.PositionY+PortraitBuffer.SizeY;
    vert.z = 4;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PortraitBuffer.PositionX+PortraitBuffer.SizeX;
    vert.y = PortraitBuffer.PositionY+PortraitBuffer.SizeY;
    vert.z = 4;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

}

void DrawSmallPortraits(FighterSelectSmallPortraitStruct PortraitBuffer[], pvr_ptr_t SmallPortraitTextures[], pvr_ptr_t FrameTexture[], char SelectionDisplayed[], int WhichCharSelected[], int Ticks[], char SelectionDone[], char ReadyToRock[], int CharAmount){

   pvr_poly_cxt_t cxt;
   pvr_poly_hdr_t hdr;
   pvr_vertex_t vert;

float FloatModifier;

int CurrentChar;
int CurrentLoadedCharacter = 0;

while(CurrentLoadedCharacter < CharAmount){

if(CurrentLoadedCharacter == WhichCharSelected[CharacterOne] || CurrentLoadedCharacter == WhichCharSelected[CharacterTwo]) FloatModifier = 1.0f;
else FloatModifier = 0.3f;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 128, 128, SmallPortraitTextures[CurrentLoadedCharacter], PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, FloatModifier, FloatModifier, FloatModifier);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = PortraitBuffer[CurrentLoadedCharacter].PositionX;
    vert.y = PortraitBuffer[CurrentLoadedCharacter].PositionY;
    vert.z = 3;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PortraitBuffer[CurrentLoadedCharacter].PositionX+PortraitBuffer[CurrentLoadedCharacter].SizeX;
    vert.y = PortraitBuffer[CurrentLoadedCharacter].PositionY;
    vert.z = 3;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PortraitBuffer[CurrentLoadedCharacter].PositionX;
    vert.y = PortraitBuffer[CurrentLoadedCharacter].PositionY+PortraitBuffer[CurrentLoadedCharacter].SizeY;
    vert.z = 3;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PortraitBuffer[CurrentLoadedCharacter].PositionX+PortraitBuffer[CurrentLoadedCharacter].SizeX;
    vert.y = PortraitBuffer[CurrentLoadedCharacter].PositionY+PortraitBuffer[CurrentLoadedCharacter].SizeY;
    vert.z = 3;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

 CurrentLoadedCharacter++;
 }


if(SelectionDisplayed[CharacterOne] == 1 && SelectionDisplayed[CharacterTwo] == 1 && WhichCharSelected[CharacterOne] == WhichCharSelected[CharacterTwo]){

if((ReadyToRock[CharacterOne] && ReadyToRock[CharacterTwo]) || (SelectionDone[CharacterOne] && !ReadyToRock[CharacterOne])) FloatModifier = 0.2*Ticks[CharacterOne];
else if(SelectionDone[CharacterTwo] && !ReadyToRock[CharacterTwo]) FloatModifier = 0.2*Ticks[CharacterTwo];
else if(!ReadyToRock[CharacterOne]) FloatModifier = 0.01*Ticks[CharacterOne];
else FloatModifier = 0.01*Ticks[CharacterTwo];
DrawFrameTexture(FrameTexture[MaxCharsOnScreen], PortraitBuffer[WhichCharSelected[CharacterOne]], FloatModifier);
}
else{
CurrentChar = CharacterOne;
do{
if(SelectionDisplayed[CurrentChar] == 1){
if(SelectionDone[CurrentChar] == 1) FloatModifier = 0.2*Ticks[CurrentChar];
else FloatModifier = 0.01*Ticks[CurrentChar];
DrawFrameTexture(FrameTexture[CurrentChar], PortraitBuffer[WhichCharSelected[CurrentChar]], FloatModifier);
}
CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);
}

}


int NewFighterSelect(int WhichMode, int PlayerID[], int CharIDCPU[], int* WhichCharacterFight, char FinalCharacterName[][9], char CharIsHuman[], char BackGroundName[]){

short CharAmount;

if(!FetchCharacterAmount(WhichMode, &CharAmount)) return(-1);

FighterSelectHeaderStruct FighterSelectHeaderBuffer[MaxCharsOnScreen];
FighterSelectSmallPortraitStruct FighterSelectSmallPortraitBuffer[CharAmount];
FighterSelectSpecialStruct FighterSelectSpecialBuffer; 

pvr_ptr_t BigPortraitTexture[MaxCharsOnScreen];
pvr_ptr_t NameTexture[MaxCharsOnScreen];
pvr_ptr_t FrameTexture[MaxCharsOnScreen+1];
pvr_ptr_t SmallPortraitTextures[CharAmount];
pvr_ptr_t BonusTexture;
pvr_ptr_t BackGroundTexture;

sfxhnd_t SoundEffects[MenuSoundEffectAmount];

maple_device_t *cont;
cont_state_t *st;

int CurrentChar;
int OtherChar;

int Bluff;

int Ticks[MaxCharsOnScreen];

char SelectionDone[MaxCharsOnScreen];
char SelectionDisplayed[MaxCharsOnScreen];
int SelectionDurationTicks[MaxCharsOnScreen];
int SelectionDuration[MaxCharsOnScreen];

char TicksGoUp[MaxCharsOnScreen];
char ReadyToRock[MaxCharsOnScreen];
int WhichCharSelected[MaxCharsOnScreen];
int PortraitExists[MaxCharsOnScreen];
uint8 ButtonInputAllowed[MaxCharsOnScreen];
uint8 OriginalButtonInputAllowed[MaxCharsOnScreen];


char TimeToGoOn = 0;
int SuperCoolEffectTicks = 1;
int OffTo = FinalExitStage;
char DrawIntro = 1;

int FinalAICharSelected = 0;
int AILoopsDone = 0;
int AILoopsRequired = 3;

LoadSelectableCharacters(FighterSelectSmallPortraitBuffer, SmallPortraitTextures, WhichMode);
LoadFighterSelectHeader(FighterSelectHeaderBuffer, &FighterSelectSpecialBuffer, &BonusTexture, FrameTexture, &BackGroundTexture, WhichMode, SoundEffects);



CurrentChar = CharacterOne;
do{

Ticks[CurrentChar] = 99;
TicksGoUp[CurrentChar] = 1;
ButtonInputAllowed[CurrentChar] = 0;
OriginalButtonInputAllowed[CurrentChar] = 0;

if(PlayerID[CurrentChar] != -1){

ReadyToRock[CurrentChar] = 1;
SelectionDone[CurrentChar] = 1;
PortraitExists[CurrentChar] = 1;
WhichCharSelected[CurrentChar] = PlayerID[CurrentChar];
SelectionDisplayed[CurrentChar] = 1;
SelectionDurationTicks[CurrentChar] = 1;
SelectionDuration[CurrentChar] = 100;
LoadFighterSelectBigPortraitFirst(FighterSelectSmallPortraitBuffer[WhichCharSelected[CurrentChar]].CharacterName, &BigPortraitTexture[CurrentChar], &NameTexture[CurrentChar]);
}

else{
ReadyToRock[CurrentChar] = 0;
SelectionDone[CurrentChar] = 0;

if(CharIsHuman[CurrentChar] == 1){
PortraitExists[CurrentChar] = 1;
WhichCharSelected[CurrentChar] = 0;
SelectionDisplayed[CurrentChar] = 1;
SelectionDurationTicks[CurrentChar] = 1;
SelectionDuration[CurrentChar] = 100;
LoadFighterSelectBigPortraitFirst(FighterSelectSmallPortraitBuffer[WhichCharSelected[CurrentChar]].CharacterName, &BigPortraitTexture[CurrentChar], &NameTexture[CurrentChar]);
}
else{
PortraitExists[CurrentChar] = 0;
WhichCharSelected[CurrentChar] = -1;
SelectionDisplayed[CurrentChar] = 0;
SelectionDurationTicks[CurrentChar] = 1;
SelectionDuration[CurrentChar] = 100;
}
}

CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);




while(TimeToGoOn == 0)
 {

 //printf("Loop is still running. \n");

 pvr_wait_ready();
 pvr_scene_begin();
 pvr_list_begin(PVR_LIST_TR_POLY);

  Bluff = 0;
  CurrentChar = CharacterOne;
  do{

  DrawFighterSelectBigPortrait(&BigPortraitTexture[CurrentChar], &NameTexture[CurrentChar], FrameTexture[CurrentChar], PortraitExists[CurrentChar], FighterSelectHeaderBuffer[CurrentChar], Bluff);

  Bluff = 1;
  CurrentChar++;
  } while(CurrentChar <= MaxCharsLoopValue);

  DrawFighterSelectBackGround(BackGroundTexture);
  DrawSmallPortraits(FighterSelectSmallPortraitBuffer, SmallPortraitTextures, FrameTexture, SelectionDisplayed, WhichCharSelected, Ticks, SelectionDone, ReadyToRock, CharAmount);

  if(FighterSelectSpecialBuffer.ThisBonusIsScrolling != 0) DrawSpecialTexture(BonusTexture, &FighterSelectSpecialBuffer);

 if(ReadyToRock[CharacterOne] == 1 && ReadyToRock[CharacterTwo] == 1)
  {
  TimeToGoOn = FadeToBlack(SuperCoolEffectTicks);
  SuperCoolEffectTicks++;
  }
 if(DrawIntro == 1)
  { 
  DrawIntro = DrawSuperCoolEffect(SuperCoolEffectTicks);
  SuperCoolEffectTicks++;
  }

 pvr_list_finish();
 pvr_scene_finish();

 CurrentChar = CharacterOne;
 OtherChar = CharacterTwo;
 do{

 if(SelectionDurationTicks[CurrentChar] > SelectionDuration[CurrentChar] && ReadyToRock[CurrentChar] == 0){
  ReadyToRock[CurrentChar] = 1;
  Ticks[CurrentChar] = 5;

  if(CharIsHuman[CurrentChar] == 0) CharIDCPU[*WhichCharacterFight] = WhichCharSelected[CurrentChar];


  //CharacterName[CurrentChar] = CharacterName[WhichCharSelected[CurrentChar]];
  sprintf(FinalCharacterName[CurrentChar], "%.8s", FighterSelectSmallPortraitBuffer[WhichCharSelected[CurrentChar]].CharacterName);
  if(CurrentChar == CharacterTwo) sprintf(BackGroundName, "%.8s", FighterSelectSmallPortraitBuffer[WhichCharSelected[CurrentChar]].BackGroundName);
  PlayerID[CurrentChar] = WhichCharSelected[CurrentChar];

  if(PlayerID[OtherChar] == -1 && CharIsHuman[OtherChar] == 0){

  if(WhichMode == StoryModeIdentifier) ReadyToRock[OtherChar] = 1;
  else{

   WhichCharSelected[OtherChar] = 0;
   PortraitExists[OtherChar] = 1;
   
   srand(rtc_unix_secs());
   FinalAICharSelected = ((rand()%CharAmount));

   ReadyToRock[OtherChar] = 1;

   while(ReadyToRock[OtherChar]){
   ReadyToRock[OtherChar] = 0;

    if(FinalAICharSelected == WhichCharSelected[CurrentChar]) ReadyToRock[OtherChar] = 1;
    for(Bluff = 0; Bluff < *WhichCharacterFight; Bluff++) {
    if(FinalAICharSelected == CharIDCPU[Bluff]) ReadyToRock[OtherChar] = 1;
    }

    if(ReadyToRock[OtherChar]) FinalAICharSelected++;
    if(FinalAICharSelected == CharAmount) FinalAICharSelected = 0;
    }
   printf("CPU Selected: %X!\n", WhichCharSelected[OtherChar]);
   SelectionDisplayed[OtherChar] = 1;
   LoadFighterSelectBigPortraitFirst(FighterSelectSmallPortraitBuffer[WhichCharSelected[OtherChar]].CharacterName, &BigPortraitTexture[OtherChar], &NameTexture[OtherChar]);
 
   }
   }

  }

 if(PlayerID[CurrentChar] == -1 && CharIsHuman[CurrentChar] == 0 && SelectionDisplayed[CurrentChar] == 1 && SelectionDone[CurrentChar] == 0){
  
   WhichCharSelected[CurrentChar]++;
   Ticks[CurrentChar] = 99;
   if(WhichCharSelected[CurrentChar] == CharAmount){ WhichCharSelected[CurrentChar] = 0; AILoopsDone++; }
   LoadFighterSelectBigPortrait(FighterSelectSmallPortraitBuffer[WhichCharSelected[CurrentChar]].CharacterName, &BigPortraitTexture[CurrentChar], &NameTexture[CurrentChar]);
   snd_sfx_play(SoundEffects[MenuSelectSoundEffectIdentifier], VolumeSFX, 128);

   if(AILoopsDone == AILoopsRequired && WhichCharSelected[CurrentChar] == FinalAICharSelected){
    SelectionDone[CurrentChar] = 1;
    SuperCoolEffectTicks = 1;  
    snd_sfx_play(SoundEffects[MenuSelectedSoundEffectIdentifier], VolumeSFX, 128);
    }
  
  }   

 if((cont = maple_enum_dev(CurrentChar, 0)) != NULL) {
  st = (cont_state_t *)maple_dev_status(cont);

   if ((st->buttons & CONT_START) && SelectionDone[CurrentChar] == 0 && OriginalButtonInputAllowed[CurrentChar] == 1 && CharIsHuman[CurrentChar] == 0) {
   PortraitExists[CurrentChar] = 1;
   PlayerID[CurrentChar] = -1;
   CharIsHuman[CurrentChar] = 1;
   SelectionDurationTicks[CurrentChar] = 1;
   SelectionDuration[CurrentChar] = 100;
   if(SelectionDisplayed[CurrentChar] == 0){
   SelectionDisplayed[CurrentChar] = 1;
   WhichCharSelected[CurrentChar] = 0;
   LoadFighterSelectBigPortraitFirst(FighterSelectSmallPortraitBuffer[WhichCharSelected[CurrentChar]].CharacterName, &BigPortraitTexture[CurrentChar], &NameTexture[CurrentChar]);
   }
   OriginalButtonInputAllowed[CurrentChar] = 0;
   }

   if (((st->buttons & CONT_START) || (st->buttons & CONT_A)) && SelectionDone[CurrentChar] == 0 && OriginalButtonInputAllowed[CurrentChar] == 1 && CharIsHuman[CurrentChar] == 1) {

   OffTo = FirstTimeCharacterSelectedStage;
   SelectionDone[CurrentChar] = 1;
   SuperCoolEffectTicks = 1;
   snd_sfx_play(SoundEffects[MenuSelectedSoundEffectIdentifier], VolumeSFX, 128);

   OriginalButtonInputAllowed[CurrentChar] = 0;
   }

  if ((st->buttons & CONT_B) && SelectionDone[CurrentChar] == 0 && OriginalButtonInputAllowed[CurrentChar] == 1 && CharIsHuman[CurrentChar] == 1) {

   if(CharIsHuman[OtherChar] && !ReadyToRock[OtherChar] && SelectionDurationTicks[OtherChar] < SelectionDuration[OtherChar]){
   CharIsHuman[CurrentChar] = 0;
   ReadyToRock[CurrentChar] = 0;
   SelectionDone[CurrentChar] = 0;
   PortraitExists[CurrentChar] = 0;
   WhichCharSelected[CurrentChar] = -1;
   SelectionDisplayed[CurrentChar] = 0;
   SelectionDurationTicks[CurrentChar] = 1;
   SelectionDuration[CurrentChar] = 100;
   }
   else{
   OffTo = FinalExitStage;
   WhichMode = SurvivalModeIdentifier;

   SelectionDone[CurrentChar] = 1;
   ReadyToRock[CurrentChar] = 1;
   ReadyToRock[OtherChar] = 1;
   SuperCoolEffectTicks = 1;
   OriginalButtonInputAllowed[CurrentChar] = 0;
   }
  }

  if ((st->buttons & CONT_B) && ReadyToRock[CurrentChar] && !ReadyToRock[OtherChar] && OriginalButtonInputAllowed[CurrentChar] == 1 && CharIsHuman[CurrentChar] == 1) {

   SelectionDurationTicks[CurrentChar] = 1;
   PlayerID[CurrentChar] = -1;
   Ticks[CurrentChar] = 99;
   SelectionDone[CurrentChar] = 0;
   ReadyToRock[CurrentChar] = 0;
   OriginalButtonInputAllowed[CurrentChar] = 0;
   }

  if (((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && SelectionDone[CurrentChar] == 0 && ButtonInputAllowed[CurrentChar] == 1 && CharIsHuman[CurrentChar] == 1) {
   WhichCharSelected[CurrentChar] = FighterSelectSmallPortraitBuffer[WhichCharSelected[CurrentChar]].CharGoLeft;
   LoadFighterSelectBigPortrait(FighterSelectSmallPortraitBuffer[WhichCharSelected[CurrentChar]].CharacterName, &BigPortraitTexture[CurrentChar], &NameTexture[CurrentChar]);
   snd_sfx_play(SoundEffects[MenuSelectSoundEffectIdentifier], VolumeSFX, 128);
   Ticks[CurrentChar] = 99;
   }

  if (((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && SelectionDone[CurrentChar] == 0 && ButtonInputAllowed[CurrentChar] == 1 && CharIsHuman[CurrentChar] == 1) {
   WhichCharSelected[CurrentChar] = FighterSelectSmallPortraitBuffer[WhichCharSelected[CurrentChar]].CharGoRight;
   LoadFighterSelectBigPortrait(FighterSelectSmallPortraitBuffer[WhichCharSelected[CurrentChar]].CharacterName, &BigPortraitTexture[CurrentChar], &NameTexture[CurrentChar]);
   snd_sfx_play(SoundEffects[MenuSelectSoundEffectIdentifier], VolumeSFX, 128);
   Ticks[CurrentChar] = 99;

   }

  if (((st->buttons & CONT_DPAD_UP)  || (st->joyy <= -64)) && SelectionDone[CurrentChar] == 0 && ButtonInputAllowed[CurrentChar] == 1 && CharIsHuman[CurrentChar] == 1) {
   WhichCharSelected[CurrentChar] = FighterSelectSmallPortraitBuffer[WhichCharSelected[CurrentChar]].CharGoUp;
   LoadFighterSelectBigPortrait(FighterSelectSmallPortraitBuffer[WhichCharSelected[CurrentChar]].CharacterName, &BigPortraitTexture[CurrentChar], &NameTexture[CurrentChar]);
   snd_sfx_play(SoundEffects[MenuSelectSoundEffectIdentifier], VolumeSFX, 128);
   Ticks[CurrentChar] = 99;
   }

  if (((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && SelectionDone[CurrentChar] == 0 && ButtonInputAllowed[CurrentChar] == 1 && CharIsHuman[CurrentChar] == 1) {
   WhichCharSelected[CurrentChar] = FighterSelectSmallPortraitBuffer[WhichCharSelected[CurrentChar]].CharGoDown;
   LoadFighterSelectBigPortrait(FighterSelectSmallPortraitBuffer[WhichCharSelected[CurrentChar]].CharacterName, &BigPortraitTexture[CurrentChar], &NameTexture[CurrentChar]);
   snd_sfx_play(SoundEffects[MenuSelectSoundEffectIdentifier], VolumeSFX, 128);
   Ticks[CurrentChar] = 99;
   }

  if(!((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && !((st->buttons & CONT_DPAD_UP)  || (st->joyy <= -64)) && !((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && !((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && ButtonInputAllowed[CurrentChar] == 0){
  ButtonInputAllowed[CurrentChar] = 1;
  }

  if(((st->buttons & CONT_DPAD_DOWN) || (st->buttons & CONT_DPAD_UP) || (st->buttons & CONT_DPAD_RIGHT) || (st->buttons & CONT_DPAD_LEFT) || (st->joyy >= 64) || (st->joyy <= -64) || (st->joyx >= 64) || (st->joyx <= -64)) && ButtonInputAllowed[CurrentChar]){ 
  ButtonInputAllowed[CurrentChar] = 0;
  }

  if(!(st->buttons & CONT_START) && !(st->buttons & CONT_A) && !(st->buttons & CONT_B) && !(st->buttons & CONT_X) && !(st->buttons & CONT_Y) && OriginalButtonInputAllowed[CurrentChar] == 0){
  OriginalButtonInputAllowed[CurrentChar] = 1;
  }

  if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
   WhichMode = SurvivalModeIdentifier;
   OffTo = FinalExitStage;
   TimeToGoOn = 1;
  }

  }

 if(ReadyToRock[CurrentChar] == 0){
  if(TicksGoUp[CurrentChar] == 1)Ticks[CurrentChar]++;
  else Ticks[CurrentChar]--;
  }

 if(SelectionDone[CurrentChar] == 0 && Ticks[CurrentChar] >= 100) TicksGoUp[CurrentChar] = 0;
 if(SelectionDone[CurrentChar] == 0 && Ticks[CurrentChar] <= 1) TicksGoUp[CurrentChar] = 1;

 if(SelectionDone[CurrentChar] == 1 && ReadyToRock[CurrentChar] == 0 && Ticks[CurrentChar] >= 5) TicksGoUp[CurrentChar] = 0;
 if(SelectionDone[CurrentChar] == 1 && ReadyToRock[CurrentChar] == 0 && Ticks[CurrentChar] <= 1) TicksGoUp[CurrentChar] = 1;

 if(SelectionDone[CurrentChar] == 1 && ReadyToRock[CurrentChar] == 0) SelectionDurationTicks[CurrentChar]++;

 CurrentChar++;
 OtherChar--;
 } while(CurrentChar <= MaxCharsLoopValue);

 }

for(Bluff = 0; Bluff<=CharAmount-1; Bluff++) pvr_mem_free(SmallPortraitTextures[Bluff]);

CurrentChar = CharacterOne;
do{
if(PortraitExists[CurrentChar] == 1){ pvr_mem_free(BigPortraitTexture[CurrentChar]); pvr_mem_free(NameTexture[CurrentChar]);}
pvr_mem_free(FrameTexture[CurrentChar]);
CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);

pvr_mem_free(FrameTexture[MaxCharsOnScreen]);

if(BackGroundTexture != 0) pvr_mem_free(BackGroundTexture);

if(FighterSelectSpecialBuffer.ThisBonusIsScrolling != 0) pvr_mem_free(BonusTexture);

if(WhichMode != ArcadeModeIdentifier){
fs_romdisk_unmount("/BIGPORTRAITS");
fs_romdisk_unmount("/NAMES");
fs_romdisk_unmount("/LOGOS");
}

FileUnlink("/ram/BIGPORTRAIT.pkg");
FileUnlink("/ram/NAME.pkg");

for(Bluff = 0; Bluff < MenuSoundEffectAmount; Bluff++) snd_sfx_unload(SoundEffects[Bluff]);

SoundStop();

return(OffTo);
}