void DrawWhoAgainstWhoBackGround(pvr_ptr_t WhoAgainstWhoBackGroundTexture){
    

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    if(WhoAgainstWhoBackGroundTexture != 0){    

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 512, 512, WhoAgainstWhoBackGroundTexture, PVR_FILTER_BILINEAR);

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

void LoadWhoAgainstWhoBackGround(int WhichMode, pvr_ptr_t* WhoAgainstWhoBackGroundTexture){

char OriginalFileDir[NormalFileDirSize];
char FileDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];

int BluffX, BluffY;

switch(WhichMode){
case ArcadeModeIdentifier:
sprintf(MountPoint, "/ARCADE");
break;
}

sprintf(OriginalFileDir, "%s%s/SHOWOFFBG.pkg", FileSystemUsed, MountPoint);
if(FileExists(OriginalFileDir)){
sprintf(FileDir, "/ram/SHOWOFFBG.pkg");
FileCopyToOtherFileSystem(OriginalFileDir, FileDir);
*WhoAgainstWhoBackGroundTexture = pvr_mem_malloc(512*512*2);
TextureLoadPKG(FileDir, WhoAgainstWhoBackGroundTexture, &BluffX, &BluffY, NoAllocateTextureMemory);
FileUnlink(FileDir);
}
else *WhoAgainstWhoBackGroundTexture = 0;
}

void LoadWhoAgainstWho
(char CharacterName[], pvr_ptr_t WhoAgainstWhoTextures[], 
WhoAgainstWhoTextureDataStruct TextureDataBuffer[]){

char FileDir[NormalFileDirSize];
char OtherFileDir[NormalFileDirSize];

sprintf(FileDir, "/BIGPORTRAITS/%.8s.pkg", CharacterName);
WhoAgainstWhoTextures[WhoAgainstWhoBigPortraitIdentifier] = pvr_mem_malloc(2*2*2);
if(!FileExists(FileDir)){
sprintf(OtherFileDir, "%s/FALLBACK/BIGPORTRAIT.pkg", FileSystemUsed);
sprintf(FileDir, "/ram/BIGPORTRAIT.pkg");
FileCopyToOtherFileSystem(OtherFileDir, FileDir);
TextureLoadPKG(FileDir, &WhoAgainstWhoTextures[WhoAgainstWhoBigPortraitIdentifier], &TextureDataBuffer[WhoAgainstWhoBigPortraitIdentifier].TextureSizeX, &TextureDataBuffer[WhoAgainstWhoBigPortraitIdentifier].TextureSizeY, ReAllocateTextureMemory);
FileUnlink(FileDir);
}
else TextureLoadPKG(FileDir, &WhoAgainstWhoTextures[WhoAgainstWhoBigPortraitIdentifier], &TextureDataBuffer[WhoAgainstWhoBigPortraitIdentifier].TextureSizeX, &TextureDataBuffer[WhoAgainstWhoBigPortraitIdentifier].TextureSizeY, ReAllocateTextureMemory);

sprintf(FileDir, "/NAMES/%.8s.pkg", CharacterName);
WhoAgainstWhoTextures[WhoAgainstWhoNameIdentifier] = pvr_mem_malloc(2*2*2);
if(!FileExists(FileDir)){
sprintf(OtherFileDir, "%s/FALLBACK/NAME.pkg", FileSystemUsed);
sprintf(FileDir, "/ram/NAME.pkg");
FileCopyToOtherFileSystem(OtherFileDir, FileDir);
TextureLoadPKG(FileDir, &WhoAgainstWhoTextures[WhoAgainstWhoNameIdentifier], &TextureDataBuffer[WhoAgainstWhoNameIdentifier].TextureSizeX, &TextureDataBuffer[WhoAgainstWhoNameIdentifier].TextureSizeY, ReAllocateTextureMemory);
FileUnlink(FileDir);
}
else TextureLoadPKG(FileDir, &WhoAgainstWhoTextures[WhoAgainstWhoNameIdentifier], &TextureDataBuffer[WhoAgainstWhoNameIdentifier].TextureSizeX, &TextureDataBuffer[WhoAgainstWhoNameIdentifier].TextureSizeY, ReAllocateTextureMemory);


sprintf(FileDir, "/LOGOS/%.8s.pkg", CharacterName);
WhoAgainstWhoTextures[WhoAgainstWhoLogoIdentifier] = pvr_mem_malloc(2*2*2);
if(!FileExists(FileDir)){ 
sprintf(OtherFileDir, "%s/FALLBACK/LOGO.pkg", FileSystemUsed);
sprintf(FileDir, "/ram/LOGO.pkg");
FileCopyToOtherFileSystem(OtherFileDir, FileDir);
TextureLoadPKG(FileDir, &WhoAgainstWhoTextures[WhoAgainstWhoLogoIdentifier], &TextureDataBuffer[WhoAgainstWhoLogoIdentifier].TextureSizeX, &TextureDataBuffer[WhoAgainstWhoLogoIdentifier].TextureSizeY, ReAllocateTextureMemory);
FileUnlink(FileDir);
}
else TextureLoadPKG(FileDir, &WhoAgainstWhoTextures[WhoAgainstWhoLogoIdentifier], &TextureDataBuffer[WhoAgainstWhoLogoIdentifier].TextureSizeX, &TextureDataBuffer[WhoAgainstWhoLogoIdentifier].TextureSizeY, ReAllocateTextureMemory);

}

void DrawWhoAgainstWho(pvr_ptr_t Texture, WhoAgainstWhoTextureDataStruct TextureData, int PositionZ, int Mirrored){

   float FilePositionLeft, FilePositionRight;

   if(Mirrored == 1){ FilePositionLeft = 1.0; FilePositionRight = 0.0; }
   else{ FilePositionLeft = 0.0; FilePositionRight = 1.0;}


   pvr_poly_cxt_t cxt;
   pvr_poly_hdr_t hdr;
   pvr_vertex_t vert;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, TextureData.TextureSizeX, TextureData.TextureSizeY, Texture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = TextureData.ScreenPositionX;
    vert.y = TextureData.ScreenPositionY;
    vert.z = PositionZ;
    vert.u = FilePositionLeft;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = TextureData.ScreenPositionX+TextureData.SizeX;
    vert.y = TextureData.ScreenPositionY;
    vert.z = PositionZ;
    vert.u = FilePositionRight;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = TextureData.ScreenPositionX;
    vert.y = TextureData.ScreenPositionY+TextureData.SizeY;
    vert.z = PositionZ;
    vert.u = FilePositionLeft;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = TextureData.ScreenPositionX+TextureData.SizeX;
    vert.y = TextureData.ScreenPositionY+TextureData.SizeY;
    vert.z = PositionZ;
    vert.u = FilePositionRight;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

}

void DrawWhoAgainstWhoFrame(WhoAgainstWhoTextureDataStruct TextureData, WhoAgainstWhoTextureDataStruct FrameData, pvr_ptr_t FrameTexture){


   pvr_poly_cxt_t cxt;
   pvr_poly_hdr_t hdr;
   pvr_vertex_t vert;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, FrameData.TextureSizeX, FrameData.TextureSizeY, FrameTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = TextureData.ScreenPositionX;
    vert.y = TextureData.ScreenPositionY;
    vert.z = 5;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = TextureData.ScreenPositionX+TextureData.SizeX;
    vert.y = TextureData.ScreenPositionY;
    vert.z = 5;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = TextureData.ScreenPositionX;
    vert.y = TextureData.ScreenPositionY+TextureData.SizeY;
    vert.z = 5;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = TextureData.ScreenPositionX+TextureData.SizeX;
    vert.y = TextureData.ScreenPositionY+TextureData.SizeY;
    vert.z = 5;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

}

void LoadWhoAgainstWhoHeader(int WhichMode, char CharacterName[][9], WhoAgainstWhoTextureDataStruct TextureData[][WhoAgainstWhoTextureAmount], pvr_ptr_t FrameTextures[], WhoAgainstWhoTextureDataStruct FrameData[]){

file_t HeaderFile;

char FileDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];

int CurrentChar;
int WhichTexture;

switch(WhichMode){
case ArcadeModeIdentifier:
sprintf(MountPoint, "/ARCADE");
break;
}

sprintf(FileDir, "%s%s/WHOAGAINSTWHO.ogg", FileSystemUsed, MountPoint);
SoundLoad(FileDir);

sprintf(FileDir, "%s%s/WHOAGAINSTWHO.hdr", FileSystemUsed, MountPoint);

HeaderFile = FileOpen(FileDir, O_RDONLY);
FileSeek(HeaderFile, 0, SEEK_SET);

CurrentChar = CharacterOne;
do{

for(WhichTexture=0; WhichTexture < WhoAgainstWhoTextureAmount; WhichTexture++){ 
FileRead(HeaderFile, &TextureData[CurrentChar][WhichTexture], sizeof(WhoAgainstWhoTextureDataStruct));
}

CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);

FileClose(HeaderFile);

sprintf(FileDir, "%s%s/TEXTURES.img", FileSystemUsed, MountPoint);
FileDirToRomDisk(FileDir, MountPoint);

for(CurrentChar = CharacterOne; CurrentChar < MaxCharsOnScreen; CurrentChar++){
sprintf(FileDir, "%s/FRAME%d.pkg", MountPoint, CurrentChar);
FrameTextures[CurrentChar] = pvr_mem_malloc(128*128*2);
TextureLoadPKG(FileDir, &FrameTextures[CurrentChar], &FrameData[CurrentChar].TextureSizeX, &FrameData[CurrentChar].TextureSizeY, ReAllocateTextureMemory);
}

fs_romdisk_unmount(MountPoint);
}


int WhoAgainstWho(int WhichMode, char CharacterName[][9]){

pvr_mem_stats();

pvr_ptr_t WhoAgainstWhoBackGroundTexture;

pvr_ptr_t WhoAgainstWhoTextures[MaxCharsOnScreen][WhoAgainstWhoTextureAmount];
pvr_ptr_t FrameTextures[MaxCharsOnScreen];

WhoAgainstWhoTextureDataStruct TextureData[MaxCharsOnScreen][WhoAgainstWhoTextureAmount];
WhoAgainstWhoTextureDataStruct FrameData[MaxCharsOnScreen];

maple_device_t *cont;
cont_state_t *st;

int CurrentChar;
int Bluff;

int ButtonInputAllowed = 0;
char ReadyToRock = 0;

int Mirrored;

char TimeToGoOn = 0;
int SuperCoolEffectTicks = 1;

int ScreenDuration = 300;
int DurationTicks = 1;

int OffTo = ActualFightStage;
char DrawIntro = 1;

LoadWhoAgainstWhoHeader(WhichMode, CharacterName, TextureData, FrameTextures, FrameData);
LoadWhoAgainstWhoBackGround(WhichMode, &WhoAgainstWhoBackGroundTexture);

CurrentChar = CharacterOne;
do{

LoadWhoAgainstWho(CharacterName[CurrentChar], WhoAgainstWhoTextures[CurrentChar], TextureData[CurrentChar]);

CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);

WhoAgainstWhoSoundPlay(WhichMode);

while(TimeToGoOn == 0)
 {



 pvr_wait_ready();
 pvr_scene_begin();
 pvr_list_begin(PVR_LIST_TR_POLY);

  DrawWhoAgainstWhoBackGround(WhoAgainstWhoBackGroundTexture);

  CurrentChar = CharacterOne;
  do{

  for(Bluff=0; Bluff<WhoAgainstWhoTextureAmount; Bluff++){
  if(Bluff == 0 && CurrentChar == CharacterTwo) Mirrored = 1;
  else Mirrored = 0;
  DrawWhoAgainstWho(WhoAgainstWhoTextures[CurrentChar][Bluff], TextureData[CurrentChar][Bluff], (Bluff+2), Mirrored);
  }

  DrawWhoAgainstWhoFrame(TextureData[CurrentChar][WhoAgainstWhoBigPortraitIdentifier], FrameData[CurrentChar], FrameTextures[CurrentChar]);

  CurrentChar++;
  } while(CurrentChar <= MaxCharsLoopValue);

 if(ReadyToRock == 1)
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


 if((cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER)) != NULL) {
  st = (cont_state_t *)maple_dev_status(cont);

  if ((st->buttons & CONT_START) && ButtonInputAllowed) TimeToGoOn = 1;


  if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
   OffTo = FinalExitStage;
   TimeToGoOn = 1;
  }

  if (!(st->buttons & CONT_START) && !ButtonInputAllowed) ButtonInputAllowed = 1;
  }


 if(DurationTicks < ScreenDuration){
  DurationTicks++;
  }
 else if(DurationTicks == ScreenDuration){
  DurationTicks++;
  ReadyToRock = 1;
  SuperCoolEffectTicks = 1;
  }

 }

fs_romdisk_unmount("/BIGPORTRAITS");
fs_romdisk_unmount("/NAMES");
fs_romdisk_unmount("/LOGOS");

if(WhoAgainstWhoBackGroundTexture != 0) pvr_mem_free(WhoAgainstWhoBackGroundTexture);

CurrentChar = CharacterOne;
do{
for(Bluff=0; Bluff<WhoAgainstWhoTextureAmount; Bluff++) pvr_mem_free(WhoAgainstWhoTextures[CurrentChar][Bluff]);
pvr_mem_free(FrameTextures[CurrentChar]);
CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);

SoundStop();

pvr_mem_stats();

return(OffTo);
}