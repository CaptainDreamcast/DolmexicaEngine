void LoadModeMenu(ModeMenuStruct* ModeMenuData, pvr_ptr_t* ModeMenuBackGroundTexture, pvr_ptr_t* ModeBackGroundTexture, pvr_ptr_t* ModeBackGroundAlternateTexture, pvr_ptr_t ModeTextTexture[], sfxhnd_t* ModeSelectSFX, sfxhnd_t* ModeSelectedSFX, sfxhnd_t* ModeDeniedSFX){

file_t InputFile;

int BluffX, BluffY;
char FileDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];

sprintf(FileDir, "%s/MENU/MAINMENU.img", FileSystemUsed);
sprintf(MountPoint, "/MAINMENU");

FileDirToRomDisk(FileDir, MountPoint);

sprintf(FileDir, "%s/BACKGROUND.pkg", MountPoint);
*ModeMenuBackGroundTexture = pvr_mem_malloc(512*512*2);
TextureLoadPKG(FileDir, ModeMenuBackGroundTexture, &BluffX, &BluffY, ReAllocateTextureMemory);

sprintf(FileDir, "%s/MODEBACKGROUND.pkg", MountPoint);
*ModeBackGroundTexture = pvr_mem_malloc(256*128*2);
TextureLoadPKG(FileDir, ModeBackGroundTexture, &BluffX, &BluffY, ReAllocateTextureMemory);

sprintf(FileDir, "%s/MODEALTERNATE.pkg", MountPoint);
*ModeBackGroundAlternateTexture = pvr_mem_malloc(256*128*2);
TextureLoadPKG(FileDir, ModeBackGroundAlternateTexture, &BluffX, &BluffY, ReAllocateTextureMemory);

sprintf(FileDir, "%s/ARCADE.pkg", MountPoint);
ModeTextTexture[0] = pvr_mem_malloc(256*128*2);
TextureLoadPKG(FileDir, &ModeTextTexture[0], &BluffX, &BluffY, ReAllocateTextureMemory);

sprintf(FileDir, "%s/STORY.pkg", MountPoint);
ModeTextTexture[1] = pvr_mem_malloc(256*128*2);
TextureLoadPKG(FileDir, &ModeTextTexture[1], &BluffX, &BluffY, ReAllocateTextureMemory);

sprintf(FileDir, "%s/SURVIVAL.pkg", MountPoint);
ModeTextTexture[2] = pvr_mem_malloc(256*128*2);
TextureLoadPKG(FileDir, &ModeTextTexture[2], &BluffX, &BluffY, ReAllocateTextureMemory);

sprintf(FileDir, "%s/OPTIONS.pkg", MountPoint);
ModeTextTexture[3] = pvr_mem_malloc(256*128*2);
TextureLoadPKG(FileDir, &ModeTextTexture[3], &BluffX, &BluffY, ReAllocateTextureMemory);

sprintf(FileDir, "%s/SELECT.wav", MountPoint);
*ModeSelectSFX = snd_sfx_load(FileDir);

sprintf(FileDir, "%s/SELECTED.wav", MountPoint);
*ModeSelectedSFX = snd_sfx_load(FileDir);

sprintf(FileDir, "%s/DENIED.wav", MountPoint);
*ModeDeniedSFX = snd_sfx_load(FileDir);

sprintf(FileDir, "%s/MAINMENU.hdr", MountPoint);
InputFile = fs_open(FileDir, O_RDONLY);
fs_seek(InputFile, 0, 0);
fs_read(InputFile, ModeMenuData, sizeof(ModeMenuStruct));
fs_close(InputFile);

fs_romdisk_unmount(MountPoint);
}

void DeLoadModeMenu(pvr_ptr_t* ModeMenuBackGroundTexture, pvr_ptr_t* ModeBackGroundTexture, pvr_ptr_t* ModeBackGroundAlternateTexture, pvr_ptr_t* ModeTextTexture1, pvr_ptr_t* ModeTextTexture2, pvr_ptr_t* ModeTextTexture3, pvr_ptr_t* ModeTextTexture4){

pvr_mem_free(*ModeMenuBackGroundTexture);

pvr_mem_free(*ModeBackGroundTexture);

pvr_mem_free(*ModeBackGroundAlternateTexture);

pvr_mem_free(*ModeTextTexture1);

pvr_mem_free(*ModeTextTexture2);

pvr_mem_free(*ModeTextTexture3);

pvr_mem_free(*ModeTextTexture4);
}

void DrawModeMenuBackGround(pvr_ptr_t Texture){
    

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 512, 512, Texture, PVR_FILTER_BILINEAR);

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

void DrawModeBackGround(int WhichMode, pvr_ptr_t ModeBackGroundTexture, pvr_ptr_t ModeBackGroundAlternateTexture, int ScreenPositionX, int ScreenPositionY, int WhichModeSelected, int Ticks, char SelectionDone){ 

pvr_poly_cxt_t cxt;
pvr_poly_hdr_t hdr;
 pvr_vertex_t vert;

int SizeX = 256;
int SizeY = 128;

float AlternateTextureTransparency;

if(WhichMode != WhichModeSelected) AlternateTextureTransparency = 0.0;
else
 {
 if(SelectionDone == 0) AlternateTextureTransparency = 0.01 * Ticks;
 else AlternateTextureTransparency = 0.2 * Ticks;
 }

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, SizeX, SizeY, ModeBackGroundTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = 2;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX;
    vert.y = ScreenPositionY;
    vert.z = 2;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+SizeY;
    vert.z = 2;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX;
    vert.y = ScreenPositionY+SizeY;
    vert.z = 2;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));


//--------------------------------------

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, SizeX, SizeY, ModeBackGroundAlternateTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(AlternateTextureTransparency, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = 3;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX;
    vert.y = ScreenPositionY;
    vert.z = 3;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+SizeY;
    vert.z = 3;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX;
    vert.y = ScreenPositionY+SizeY;
    vert.z = 3;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));



}

void DrawModeText( pvr_ptr_t Texture, int ScreenPositionX, int ScreenPositionY){ 

pvr_poly_cxt_t cxt;
pvr_poly_hdr_t hdr;
 pvr_vertex_t vert;

int SizeX = 256;
int SizeY = 128;


    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, SizeX, SizeY, Texture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = 4;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX;
    vert.y = ScreenPositionY;
    vert.z = 4;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+SizeY;
    vert.z = 4;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX;
    vert.y = ScreenPositionY+SizeY;
    vert.z = 4;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));




}

int DrawModeMenu(int* WhichPlayerActive){

ModeMenuStruct ModeMenuData;

pvr_ptr_t ModeMenuBackGroundTexture;
pvr_ptr_t ModeBackGroundTexture;
pvr_ptr_t ModeBackGroundAlternateTexture;
pvr_ptr_t ModeTextTexture[ModeAmount];


sfxhnd_t ModeSelectSFX;
sfxhnd_t ModeSelectedSFX;
sfxhnd_t ModeDeniedSFX;

maple_device_t *cont;
cont_state_t *st;

int DirtyDeedsDoneDirtCheap;

int WhichModeSelected = 1;

char TimeToGoOn = 0;
char SelectionDone = 0;
uint8 OriginalButtonInputAllowed = 0;
uint8 ButtonInputAllowed = 0;
int OffTo = 0;

int AfterInputTicks = 1;

int SuperCoolEffectTicks = 1;

char DrawIntro = 1;

int Ticks = 1;
char TicksGoUp = 1;

LoadModeMenu(&ModeMenuData, &ModeMenuBackGroundTexture, &ModeBackGroundTexture, &ModeBackGroundAlternateTexture, ModeTextTexture, &ModeSelectSFX, &ModeSelectedSFX, &ModeDeniedSFX);

if(MusicWorks == 1) cdrom_cdda_play(ModeMenuTrack, ModeMenuTrack, 16, CDDA_TRACKS);

while(TimeToGoOn == 0){

 pvr_wait_ready();
 pvr_scene_begin();
 pvr_list_begin(PVR_LIST_TR_POLY);

 DrawModeMenuBackGround(ModeMenuBackGroundTexture);
 

 for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<4; DirtyDeedsDoneDirtCheap++){
 DrawModeBackGround(DirtyDeedsDoneDirtCheap+1, ModeBackGroundTexture, ModeBackGroundAlternateTexture, ModeMenuData.SingleMode[DirtyDeedsDoneDirtCheap].PositionX, ModeMenuData.SingleMode[DirtyDeedsDoneDirtCheap].PositionY, WhichModeSelected, Ticks, SelectionDone);
 DrawModeText(ModeTextTexture[DirtyDeedsDoneDirtCheap], ModeMenuData.SingleMode[DirtyDeedsDoneDirtCheap].PositionX, ModeMenuData.SingleMode[DirtyDeedsDoneDirtCheap].PositionY);
 }
 
 if(DrawIntro == 1)
  { 
  DrawIntro = DrawSuperCoolEffect(SuperCoolEffectTicks);
  SuperCoolEffectTicks++;
  }
 if(AfterInputTicks > ModeMenuData.AfterInputDuration)
  {
  TimeToGoOn = FadeToBlack(SuperCoolEffectTicks);
  SuperCoolEffectTicks++;
  }

 pvr_list_finish();
 pvr_scene_finish();

 if((cont = maple_enum_dev((*WhichPlayerActive), 0)) != NULL) {
  st = (cont_state_t *)maple_dev_status(cont);

  if (((st->buttons & CONT_START) || (st->buttons & CONT_A)) && SelectionDone == 0 && OriginalButtonInputAllowed == 1) {

   OffTo = WhichModeSelected+2;
   SelectionDone = 1;
   SuperCoolEffectTicks = 1;
   snd_sfx_play(ModeSelectedSFX, VolumeSFX, 128);
   }

  if ((st->buttons & CONT_B) && SelectionDone == 0 && OriginalButtonInputAllowed == 1) {
   OffTo = 1;
   SelectionDone = 1;
   AfterInputTicks = ModeMenuData.AfterInputDuration+1;
   SuperCoolEffectTicks = 1;
   }

  if (((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && SelectionDone == 0 && ButtonInputAllowed == 1) {
   WhichModeSelected--;
   if(WhichModeSelected < 1) WhichModeSelected += 4;
   Ticks = 99;
   snd_sfx_play(ModeSelectSFX, VolumeSFX, 128);
   }

  if (((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && SelectionDone == 0 && ButtonInputAllowed == 1) {
   WhichModeSelected++;
   if(WhichModeSelected > 4) WhichModeSelected -= 4;
   Ticks = 99;
   snd_sfx_play(ModeSelectSFX, VolumeSFX, 128);
   }

  if (((st->buttons & CONT_DPAD_UP)  || (st->joyy <= -64)) && SelectionDone == 0 && ButtonInputAllowed == 1) {
   WhichModeSelected-=2;
   if(WhichModeSelected < 1) WhichModeSelected += 4;
   Ticks = 99;
   snd_sfx_play(ModeSelectSFX, VolumeSFX, 128);
   }

  if (((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && SelectionDone == 0 && ButtonInputAllowed == 1) {
   WhichModeSelected+=2;
   if(WhichModeSelected > 4) WhichModeSelected -= 4;
   Ticks = 99;
   snd_sfx_play(ModeSelectSFX, VolumeSFX, 128);
   }

  if(!((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && !((st->buttons & CONT_DPAD_UP)  || (st->joyy <= -64)) && !((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && !((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && ButtonInputAllowed == 0){
  ButtonInputAllowed = 1;
  }
  
  if(((st->buttons & CONT_DPAD_DOWN) || (st->buttons & CONT_DPAD_UP) || (st->buttons & CONT_DPAD_RIGHT) || (st->buttons & CONT_DPAD_LEFT) || (st->joyy >= 64) || (st->joyy <= -64) || (st->joyx >= 64) || (st->joyx <= -64)) && ButtonInputAllowed) ButtonInputAllowed = 0;

  if(!(st->buttons & CONT_START) && !(st->buttons & CONT_A) && !(st->buttons & CONT_B) && !(st->buttons & CONT_X) && !(st->buttons & CONT_Y) && OriginalButtonInputAllowed == 0){
  OriginalButtonInputAllowed = 1;
  }

  if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
   OffTo = GameStageTitleScreen;
   TimeToGoOn = 1;
  }

 }

 if(TicksGoUp == 1)Ticks++;
 else Ticks--;

 if(SelectionDone== 0 && Ticks >= 100) TicksGoUp = 0;
 if(SelectionDone== 0 && Ticks <= 1) TicksGoUp = 1;

 if(SelectionDone== 1 && Ticks >= 5) TicksGoUp = 0;
 if(SelectionDone== 1 && Ticks <= 1) TicksGoUp = 1;

 if(SelectionDone== 1) AfterInputTicks++;

}
//DeLoadModeMenu(&ModeMenuBackGroundTexture, &ModeBackGroundTexture, &ModeBackGroundAlternateTexture, &ModeTextTexture1, &ModeTextTexture2, &ModeTextTexture3, &ModeTextTexture4);

pvr_mem_free(ModeMenuBackGroundTexture);
pvr_mem_free(ModeBackGroundTexture);
pvr_mem_free(ModeBackGroundAlternateTexture);

for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<4; DirtyDeedsDoneDirtCheap++) pvr_mem_free(ModeTextTexture[DirtyDeedsDoneDirtCheap]);

snd_sfx_unload(ModeSelectSFX);
snd_sfx_unload(ModeSelectedSFX);
snd_sfx_unload(ModeDeniedSFX);
cdrom_cdda_pause();

return(OffTo);
}