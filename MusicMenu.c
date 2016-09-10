void LoadMusicMenu(pvr_ptr_t* MusicMenuBackGroundTexture, sfxhnd_t* ModeSelectSFX){

char FileDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];

int BluffX, BluffY;

sprintf(FileDir, "%s/MENU/MUSICMENU.ogg", FileSystemUsed);
SoundLoad(FileDir);

sprintf(FileDir, "%s/MENU/MUSICMENU.img", FileSystemUsed);
sprintf(MountPoint, "/MUSICMENU");

FileDirToRomDisk(FileDir, MountPoint);

sprintf(FileDir, "%s/BACKGROUND.pkg", MountPoint);
*MusicMenuBackGroundTexture = pvr_mem_malloc(512*512*2);
TextureLoadPKG(FileDir, MusicMenuBackGroundTexture, &BluffX, &BluffY, ReAllocateTextureMemory);

sprintf(FileDir, "%s/SELECT.wav", MountPoint);
*ModeSelectSFX = snd_sfx_load(FileDir);

fs_romdisk_unmount(MountPoint);

sprintf(FileDir, "%s/MENU/MUSICMENU.ogg", FileSystemUsed);
SoundPlay(FileDir, MusicMenuTrack);

}

void DeLoadMusicMenu(pvr_ptr_t* MusicMenuBackGroundTexture){

pvr_mem_free(*MusicMenuBackGroundTexture);

}

void DrawMusicMenuBackGround(pvr_ptr_t* Texture){

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 512, 512, *Texture, PVR_FILTER_BILINEAR);

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


void DrawVolumeSFX(int ScreenPositionX, int ScreenPositionY, int Color){

int PixelsX;

int PositionOffsetX = 0;
int PositionOffsetY = 0;


PixelsX = VolumeSFX*1.56862745;


while(PositionOffsetX <= PixelsX){
 if(PositionOffsetX%10 == 0) PositionOffsetY++;
 DrawColorBox(ScreenPositionX+PositionOffsetX, ScreenPositionY-PositionOffsetY, LowerGuiPositionZ, 1, 1+(PositionOffsetY*2), Color);
 PositionOffsetX++;
 }

}

void DrawVolumeCDDA(int ScreenPositionX, int ScreenPositionY, int Color){

int PixelsX;

int PositionOffsetX = 0;
int PositionOffsetY = 0;


PixelsX = VolumeCDDA*26.6666667;

while(PositionOffsetX <= PixelsX){
 if(PositionOffsetX%10 == 0) PositionOffsetY++;
 DrawColorBox(ScreenPositionX+PositionOffsetX, ScreenPositionY-PositionOffsetY, LowerGuiPositionZ, 1, 1+(PositionOffsetY*2), Color);
 PositionOffsetX++;
 }

}

int MusicMenu(int* WhichPlayerActive, int* GameStage){

pvr_ptr_t MusicMenuBackGroundTexture;

sfxhnd_t ModeSelectSFX;

maple_device_t *cont;
cont_state_t *st;

int WhichModeSelected = 1;

int VolumePositionCDDAX = 104;
int VolumePositionCDDAY = 371+40;

int VolumePositionSFXX = 104;
int VolumePositionSFXY = 191+40;

char TimeToGoOn = 0;
uint8 ButtonInputAllowed = 0;
uint8 OriginalButtonInputAllowed = 0;
int OffTo = 0;

int PlaySFXTicks = 60;

int SuperCoolEffectTicks = 1;

char DrawIntro = 1;
char DrawOutro = 0;

char ColorSFX = 1;
char ColorCDDA = 1;

if((*GameStage) != GameStageMusicMode && (*GameStage) != GameStageOptionMenu) return(*GameStage);

LoadMusicMenu(&MusicMenuBackGroundTexture, &ModeSelectSFX);


while(TimeToGoOn == 0){

 if(WhichModeSelected == 1) ColorSFX = 2;
 else ColorSFX = 1;

 if(WhichModeSelected == 2) ColorCDDA = 2;
 else ColorCDDA = 1;

 pvr_wait_ready();
 pvr_scene_begin();
 pvr_list_begin(PVR_LIST_TR_POLY);

 DrawMusicMenuBackGround(&MusicMenuBackGroundTexture);
 DrawVolumeSFX(VolumePositionSFXX, VolumePositionSFXY, ColorSFX);  
 DrawVolumeCDDA(VolumePositionCDDAX, VolumePositionCDDAY, ColorCDDA); 

 if(DrawIntro == 1)
  { 
  DrawIntro = DrawSuperCoolEffect(SuperCoolEffectTicks);
  SuperCoolEffectTicks++;

  }
 if(DrawOutro == 1)
  {
  TimeToGoOn = FadeToBlack(SuperCoolEffectTicks);
  SuperCoolEffectTicks++;
  }

 pvr_list_finish();
 pvr_scene_finish();

 if((cont = maple_enum_dev((*WhichPlayerActive), 0)) != NULL) {
  st = (cont_state_t *)maple_dev_status(cont);

  if ((st->buttons & CONT_B) && DrawOutro == 0 && OriginalButtonInputAllowed == 1) {
   if((*GameStage) == GameStageMusicMode) OffTo = GameStageModeMenu;
   else OffTo = GameStageOptionMenu;

   DrawOutro = 1;
   SuperCoolEffectTicks = 1;
   }

  if (((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && DrawOutro == 0 && ButtonInputAllowed == 1) {
   if(WhichModeSelected == 1){
    VolumeSFX--;
    if(VolumeSFX < 0) VolumeSFX = 0;
    PlaySFXTicks++;
    if(PlaySFXTicks > 60){ PlaySFXTicks = 1; snd_sfx_play(ModeSelectSFX, VolumeSFX, 128); }    
    }
   if(WhichModeSelected == 2){
    VolumeCDDA--;
    if(VolumeCDDA < 0) VolumeCDDA = 0;
    spu_cdda_volume(VolumeCDDA, VolumeCDDA);
    sndoggvorbis_volume((VolumeCDDA/(float)VolumeMaxCDDA)*VolumeMaxOGG);
    snd_sfx_play(ModeSelectSFX, VolumeSFX, 128);
    ButtonInputAllowed = 0;
    }



   }

  if (((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && DrawOutro == 0 && ButtonInputAllowed == 1) {

   if(WhichModeSelected == 1){
    VolumeSFX++;
    if(VolumeSFX > 255) VolumeSFX = 255;
    PlaySFXTicks++;
    if(PlaySFXTicks > 60){ PlaySFXTicks = 1; snd_sfx_play(ModeSelectSFX, VolumeSFX, 128); }    
    }
   if(WhichModeSelected == 2){
    VolumeCDDA++;
    if(VolumeCDDA > 15) VolumeCDDA = 15;
    spu_cdda_volume(VolumeCDDA, VolumeCDDA);
    sndoggvorbis_volume((VolumeCDDA/(float)VolumeMaxCDDA)*VolumeMaxOGG);
    snd_sfx_play(ModeSelectSFX, VolumeSFX, 128);
    ButtonInputAllowed = 0;
    }
   }

  if (((st->buttons & CONT_DPAD_UP)  || (st->joyy <= -64)) && DrawOutro == 0 && ButtonInputAllowed == 1) {
   WhichModeSelected--;
   if(WhichModeSelected < 1) WhichModeSelected = 2;
   snd_sfx_play(ModeSelectSFX, VolumeSFX, 128);
   ButtonInputAllowed = 0;
   }

  if (((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && DrawOutro == 0 && ButtonInputAllowed == 1) {
   WhichModeSelected++;
   if(WhichModeSelected > 2) WhichModeSelected = 1;
   snd_sfx_play(ModeSelectSFX, VolumeSFX, 128);
   ButtonInputAllowed = 0;
   }

  if(!((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && !((st->buttons & CONT_DPAD_UP)  || (st->joyy <= -64)) && !((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && !((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && ButtonInputAllowed == 0){
  ButtonInputAllowed = 1;
  }

  if(!(st->buttons & CONT_START) && !(st->buttons & CONT_B) && OriginalButtonInputAllowed == 0){
  OriginalButtonInputAllowed = 1;
  }

  if(!((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && !((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64))){
  PlaySFXTicks = 60;
  }

  if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
   OffTo = GameStageTitleScreen;
   TimeToGoOn = 1;
  }

 }

}
//LoadMusicMenu(&MusicMenuBackGroundTexture);

pvr_mem_free(MusicMenuBackGroundTexture);

snd_sfx_unload(ModeSelectSFX);
SoundStop();

return(OffTo);

}