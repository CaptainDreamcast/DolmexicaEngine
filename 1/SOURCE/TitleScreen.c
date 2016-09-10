void DrawTitleScreenBackGround(pvr_ptr_t* Texture){
    

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

void DrawPressStart(TitleScreenStruct TitleScreenData, pvr_ptr_t* Texture, int Ticks, char StartPressed){
    
    float a;
 
    if(StartPressed == 0) a = 0.01 * Ticks;
    else a = 0.2 * Ticks;

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 256, 64, *Texture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(a, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = TitleScreenData.PressStartPositionX;
    vert.y = TitleScreenData.PressStartPositionY;
    vert.z = 2;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = TitleScreenData.PressStartPositionX+TitleScreenData.PressStartSizeX;
    vert.y = TitleScreenData.PressStartPositionY;
    vert.z = 2;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = TitleScreenData.PressStartPositionX;
    vert.y = TitleScreenData.PressStartPositionY+TitleScreenData.PressStartSizeY;
    vert.z = 2;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = TitleScreenData.PressStartPositionX+TitleScreenData.PressStartSizeX;
    vert.y = TitleScreenData.PressStartPositionY+TitleScreenData.PressStartSizeY;
    vert.z = 2;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));


}


void LoadTitleScreen(TitleScreenStruct* TitleScreenData, pvr_ptr_t* PressStartTexture, pvr_ptr_t* TitleScreenBackGroundTexture, sfxhnd_t* ModeSelectedSFX){

file_t InputFile;

char FileDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];
int BluffX, BluffY;


sprintf(FileDir, "%s/MENU/TITLE.img", FileSystemUsed);
sprintf(MountPoint, "/TITLE");

FileDirToRomDisk(FileDir, MountPoint);

sprintf(FileDir, "%s/BACKGROUND.pkg", MountPoint);

*TitleScreenBackGroundTexture = pvr_mem_malloc(512*512*2);
TextureLoadPKG(FileDir, TitleScreenBackGroundTexture, &BluffX, &BluffY, ReAllocateTextureMemory);

sprintf(FileDir, "%s/PRESSSTART.pkg", MountPoint);

*PressStartTexture = pvr_mem_malloc(256*64*2);
TextureLoadPKG(FileDir, PressStartTexture, &BluffX, &BluffY, ReAllocateTextureMemory);

sprintf(FileDir, "%s/SELECTED.wav", MountPoint);
*ModeSelectedSFX = snd_sfx_load(FileDir);

sprintf(FileDir, "%s/TITLE.hdr", MountPoint);
InputFile = fs_open(FileDir, O_RDONLY);
fs_seek(InputFile, 0, 0);
fs_read(InputFile, TitleScreenData, sizeof(TitleScreenStruct));
fs_close(InputFile);

fs_romdisk_unmount(MountPoint);
}

void DeLoadTitleScreen(pvr_ptr_t* PressStartTexture, pvr_ptr_t* TitleScreenBackGroundTexture){

pvr_mem_free(*TitleScreenBackGroundTexture);
pvr_mem_free(*PressStartTexture);
}

int DrawTitleScreen(int* WhichPlayerActive)
{

pvr_ptr_t PressStartTexture;
pvr_ptr_t TitleScreenBackGroundTexture;
sfxhnd_t ModeSelectedSFX;

TitleScreenStruct TitleScreenData;

maple_device_t *cont;
cont_state_t *st;

uint8 ButtonInputAllowed[MaxCharsOnScreen];
int CurrentChar;
uint8 Reload;
uint16 ReloadTicks = 0;

int Ticks = 1;
char StartPressed = 0;
int TitleLoop = 1;

char TicksGoUp = 1;
char TimeToGoOn = 0;
int SuperCoolEffectTicks = 1;
int OffTo = 13;
char DrawIntro = 1;

Reload = Intro(CheckIntro);

for(CurrentChar=CharacterOne; CurrentChar<MaxCharsOnScreen; CurrentChar++) ButtonInputAllowed[CurrentChar] = 0;
LoadTitleScreen(&TitleScreenData, &PressStartTexture, &TitleScreenBackGroundTexture, &ModeSelectedSFX);


while(TimeToGoOn == 0)
 {

 pvr_wait_ready();
 pvr_scene_begin();
 pvr_list_begin(PVR_LIST_TR_POLY);
 DrawTitleScreenBackGround(&TitleScreenBackGroundTexture);
 DrawPressStart(TitleScreenData, &PressStartTexture, Ticks, StartPressed);
 if(TitleLoop > TitleScreenData.PressStartDuration)
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


 for(CurrentChar = CharacterOne; CurrentChar<MaxCharsOnScreen; CurrentChar++){

 if((cont = maple_enum_dev(CurrentChar, 0)) != NULL) {

  st = (cont_state_t *)maple_dev_status(cont);

  if ((st->buttons & CONT_START) && StartPressed == 0 && ButtonInputAllowed[CurrentChar] == 1) {
   OffTo = 2;
   StartPressed = 1;
   SuperCoolEffectTicks = 1;
   Ticks = 5;
   *WhichPlayerActive = CurrentChar;
   snd_sfx_play(ModeSelectedSFX, VolumeSFX, 128);
   }

  if ((st->buttons == 0) && ButtonInputAllowed[CurrentChar] == 0) {
   ButtonInputAllowed[CurrentChar] = 1;
  }

  if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven) && ButtonInputAllowed[CurrentChar] == 1) {
   OffTo = GameStageDeath;
   TimeToGoOn = 1;
  }

  }

 }
 

 if(Reload && !StartPressed){
 ReloadTicks++;
 if(ReloadTicks >= TitleScreenData.ScreenReloadDuration){
 OffTo = GameStageIntro;  
 StartPressed = 1;
 SuperCoolEffectTicks = 1;
 Ticks = 5;
 TitleLoop = TitleScreenData.PressStartDuration+1;
 }
 }  


 if(TicksGoUp == 1)Ticks++;
 else Ticks--;

 if(StartPressed== 0 && Ticks >= 100) TicksGoUp = 0;
 if(StartPressed== 0 && Ticks <= 1) TicksGoUp = 1;

 if(StartPressed== 1 && Ticks >= 5) TicksGoUp = 0;
 if(StartPressed== 1 && Ticks <= 1) TicksGoUp = 1;

 if(StartPressed== 1) TitleLoop++;
 }
//DeLoadTitleScreen(&PressStartTexture, &TitleScreenBackGroundTexture);
pvr_mem_free(TitleScreenBackGroundTexture);
pvr_mem_free(PressStartTexture);

snd_sfx_unload(ModeSelectedSFX);
return(OffTo);
}