void DrawFighterSelectBackGround(){
    

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 16, 16, LoadingBackGroundTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(0.0f, 1.0f, 1.0f, 1.0f);
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


void LoadSelectableCharacters(int PositionX[], int PositionY[], int SizeX[], int SizeY[], int CharGoUp[], int CharGoDown[], int CharGoLeft[], int CharGoRight[], char CharacterName[][10], pvr_ptr_t SmallPortraitTextures[]){

file_t CharacterArchive;

int Bluff;
char CharArchive[39];
char FileDirPortrait[39];

int CharacterAmount = 0;
long CurrentOffset;
long DesiredOffset = 0;
int CurrentLoadedCharacter = 0;

Bluff = sprintf(CharArchive, "%s/CHARACTERS.lst", FileSystemUsed);

CharacterArchive = fs_open(CharArchive, O_RDONLY);

CurrentOffset = fs_seek(CharacterArchive, DesiredOffset, 0);
fs_read(CharacterArchive, &CharacterAmount, 2);

while(CurrentLoadedCharacter < CharacterAmount){
 DesiredOffset+=32;

 CurrentOffset = fs_seek(CharacterArchive, DesiredOffset+4, 0);
 fs_read(CharacterArchive, CharacterName[CurrentLoadedCharacter], 8);
 CharacterName[CurrentLoadedCharacter][8] = '\0';
 //printf("CharacterName: %s \n", CharacterName[CurrentLoadedCharacter]);

 CharGoUp[CurrentLoadedCharacter] = 0;
 CurrentOffset = fs_seek(CharacterArchive, DesiredOffset+12, 0);
 fs_read(CharacterArchive, &CharGoUp[CurrentLoadedCharacter], 2);
 //printf("CharGoSomewhere: %x \n", CharGoUp[CurrentLoadedCharacter]);

 CharGoDown[CurrentLoadedCharacter] = 0;
 CurrentOffset = fs_seek(CharacterArchive, DesiredOffset+14, 0);
 fs_read(CharacterArchive, &CharGoDown[CurrentLoadedCharacter], 2);

 CharGoLeft[CurrentLoadedCharacter] = 0;
 CurrentOffset = fs_seek(CharacterArchive, DesiredOffset+16, 0);
 fs_read(CharacterArchive, &CharGoLeft[CurrentLoadedCharacter], 2);

 CharGoRight[CurrentLoadedCharacter] = 0;
 CurrentOffset = fs_seek(CharacterArchive, DesiredOffset+18, 0);
 fs_read(CharacterArchive, &CharGoRight[CurrentLoadedCharacter], 2);

 PositionX[CurrentLoadedCharacter] = 0;
 CurrentOffset = fs_seek(CharacterArchive, DesiredOffset+20, 0);
 fs_read(CharacterArchive, &PositionX[CurrentLoadedCharacter], 2);
 //printf("PositionX: %x \n", PositionX[CurrentLoadedCharacter]);

 PositionY[CurrentLoadedCharacter] = 0;
 CurrentOffset = fs_seek(CharacterArchive, DesiredOffset+22, 0);
 fs_read(CharacterArchive, &PositionY[CurrentLoadedCharacter], 2);
 //printf("PositionY: %x \n", PositionY[CurrentLoadedCharacter]);

 SizeX[CurrentLoadedCharacter] = 0;
 CurrentOffset = fs_seek(CharacterArchive, DesiredOffset+24, 0);
 fs_read(CharacterArchive, &SizeX[CurrentLoadedCharacter], 2);
 //printf("SizeX: %x \n", SizeX[CurrentLoadedCharacter] );

 SizeY[CurrentLoadedCharacter] = 0;
 CurrentOffset = fs_seek(CharacterArchive, DesiredOffset+26, 0);
 fs_read(CharacterArchive, &SizeY[CurrentLoadedCharacter], 2);
 //printf("SizeY: %x \n", SizeY[CurrentLoadedCharacter] );

 Bluff = sprintf(FileDirPortrait, "%s/%.8s/SMALLPORTRAIT.png", FileSystemUsed, CharacterName[CurrentLoadedCharacter]);

 SmallPortraitTextures[CurrentLoadedCharacter] = pvr_mem_malloc(128*128*2);
 png_to_texture(FileDirPortrait, SmallPortraitTextures[CurrentLoadedCharacter], PNG_FULL_ALPHA);


 CurrentLoadedCharacter++;
 }

fs_close(CharacterArchive);
}

void LoadFighterSelectBigPortraitFirst(char CharacterName[], pvr_ptr_t* BigPortraitTexture, pvr_ptr_t* NameTexture){

int Bluff;
char FileDir[39];

Bluff = sprintf(FileDir, "%s/%.8s/BIGPORTRAIT.png", StreamingFileSystemUsed, CharacterName);


*BigPortraitTexture = pvr_mem_malloc(256*256*2);
png_to_texture(FileDir, *BigPortraitTexture, PNG_FULL_ALPHA);


Bluff = sprintf(FileDir, "%s/%.8s/CHARACTERNAME.png", StreamingFileSystemUsed, CharacterName);


*NameTexture = pvr_mem_malloc(256*64*2);
png_to_texture(FileDir, *NameTexture, PNG_FULL_ALPHA);

}

void LoadFighterSelectBigPortrait(char CharacterName[], pvr_ptr_t* BigPortraitTexture, pvr_ptr_t* NameTexture){

int Bluff;
char FileDir[39];

Bluff = sprintf(FileDir, "%s/%.8s/BIGPORTRAIT.png", StreamingFileSystemUsed, CharacterName);

pvr_mem_free(*BigPortraitTexture);
*BigPortraitTexture = pvr_mem_malloc(256*256*2);

png_to_texture(FileDir, *BigPortraitTexture, PNG_FULL_ALPHA);



Bluff = sprintf(FileDir, "%s/%.8s/CHARACTERNAME.png", StreamingFileSystemUsed, CharacterName);

pvr_mem_free(*NameTexture);
*NameTexture = pvr_mem_malloc(256*64*2);
png_to_texture(FileDir, *NameTexture, PNG_FULL_ALPHA);

}

void DrawFighterSelectBigPortrait(pvr_ptr_t* BigPortraitTexture, pvr_ptr_t* NameTexture, int PortraitExists, int ScreenPositionX, int ScreenPositionY, int SizeX, int SizeY, int Mirrored){

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

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = 2;
    vert.u = FilePositionLeft;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX;
    vert.y = ScreenPositionY;
    vert.z = 2;
    vert.u = FilePositionRight;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+SizeY;
    vert.z = 2;
    vert.u = FilePositionLeft;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX;
    vert.y = ScreenPositionY+SizeY;
    vert.z = 2;
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

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+SizeY-64;
    vert.z = 3;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX;
    vert.y = ScreenPositionY+SizeY-64;
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
}

void DrawSmallPortraits(int PositionX[], int PositionY[], int SizeX[], int SizeY[], pvr_ptr_t SmallPortraitTextures[], int CharAmount){

   pvr_poly_cxt_t cxt;
   pvr_poly_hdr_t hdr;
   pvr_vertex_t vert;

int CurrentLoadedCharacter = 0;

while(CurrentLoadedCharacter < CharAmount){

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 16, 16, LoadingBackGroundTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = PositionX[CurrentLoadedCharacter];
    vert.y = PositionY[CurrentLoadedCharacter];
    vert.z = 2;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX[CurrentLoadedCharacter]+SizeX[CurrentLoadedCharacter];
    vert.y = PositionY[CurrentLoadedCharacter];
    vert.z = 2;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX[CurrentLoadedCharacter];
    vert.y = PositionY[CurrentLoadedCharacter]+SizeY[CurrentLoadedCharacter];
    vert.z = 2;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX[CurrentLoadedCharacter]+SizeX[CurrentLoadedCharacter];
    vert.y = PositionY[CurrentLoadedCharacter]+SizeY[CurrentLoadedCharacter];
    vert.z = 2;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));


    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 128, 128, SmallPortraitTextures[CurrentLoadedCharacter], PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = PositionX[CurrentLoadedCharacter]+1;
    vert.y = PositionY[CurrentLoadedCharacter]+1;
    vert.z = 3;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX[CurrentLoadedCharacter]+SizeX[CurrentLoadedCharacter]-1;
    vert.y = PositionY[CurrentLoadedCharacter]+1;
    vert.z = 3;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX[CurrentLoadedCharacter]+1;
    vert.y = PositionY[CurrentLoadedCharacter]+SizeY[CurrentLoadedCharacter]-1;
    vert.z = 3;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX[CurrentLoadedCharacter]+SizeX[CurrentLoadedCharacter]-1;
    vert.y = PositionY[CurrentLoadedCharacter]+SizeY[CurrentLoadedCharacter]-1;
    vert.z = 3;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

 CurrentLoadedCharacter++;
 }
}


int FighterSelect(int* PlayerID1, int* PlayerID2, int* CharIDCPU1, int* CharIDCPU2, int* CharIDCPU3, int* CharIDCPU4, int* CharIDCPU5, int* CharIDCPU6, int* CharIDCPU7, int* CharIDCPU8, int* WhichCharacterFight, char CharacterName1[], char CharacterName2[], char* CharIsHuman1, char* CharIsHuman2){

pvr_mem_stats();

int CharAmount = 10;

pvr_ptr_t SmallPortraitTextures[CharAmount];
pvr_ptr_t BigPortraitTexture1;
pvr_ptr_t BigPortraitTexture2;
pvr_ptr_t NameTexture1;
pvr_ptr_t NameTexture2;

sfxhnd_t ModeSelectSFX;
sfxhnd_t ModeSelectedSFX;
sfxhnd_t ModeDeniedSFX;

maple_device_t *cont;
cont_state_t *st;

int Bluff;
char TemporaryFileDir[40];

int BigPortraitScreenPositionX1 = 20;
int BigPortraitScreenPositionY1 = 8;
int BigPortraitScreenPositionX2 = 364;
int BigPortraitScreenPositionY2 = 8;

int BigPortraitSizeX1 = 256;
int BigPortraitSizeY1 = 256;
int BigPortraitSizeX2 = 256;
int BigPortraitSizeY2 = 256;

int Ticks1 = 99;
int Ticks2 = 99;

char SelectionDone1 = 0;
char SelectionDone2 = 0;

char SelectionDisplayed1 = 1;
char SelectionDisplayed2 = 0;
int SelectionDurationTicks1 = 1;
int SelectionDuration1 = 100;
int SelectionDurationTicks2 = 1;
int SelectionDuration2 = 100;

char TicksGoUp1 = 1;
char TicksGoUp2 = 1;

char ReadyToRock1 = 0;
char ReadyToRock2 = 0;


char TimeToGoOn = 0;
int SuperCoolEffectTicks = 1;
int OffTo = 13;
char DrawIntro = 1;

int WhichCharSelected1 = 1;
int WhichCharSelected2 = 1;

int PortraitExists1 = 1;
int PortraitExists2 = 0;

char ButtonInputAllowed1 = 0;
char ButtonInputAllowed2 = 0;

int PositionX[CharAmount];
int PositionY[CharAmount];
int SizeX[CharAmount];
int SizeY[CharAmount];

int CharGoUp[CharAmount];
int CharGoDown[CharAmount];
int CharGoLeft[CharAmount];
int CharGoRight[CharAmount];

int FinalAICharSelected = 0;
int AILoopsDone = 0;
int AILoopsRequired = 3;

char CharacterName[CharAmount][10];
int i = 0;

LoadSelectableCharacters(PositionX, PositionY, SizeX, SizeY, CharGoUp, CharGoDown, CharGoLeft, CharGoRight, CharacterName, SmallPortraitTextures);

Bluff = sprintf(TemporaryFileDir, "%s/MENU/MENUSFX/MENUSELECT.WAV", FileSystemUsed);

ModeSelectSFX = snd_sfx_load(TemporaryFileDir);

Bluff = sprintf(TemporaryFileDir, "%s/MENU/MENUSFX/MENUSELECTED.WAV", FileSystemUsed);

ModeSelectedSFX = snd_sfx_load(TemporaryFileDir);

Bluff = sprintf(TemporaryFileDir, "%s/MENU/MENUSFX/MENUDENIED.WAV", FileSystemUsed);

ModeDeniedSFX = snd_sfx_load(TemporaryFileDir);

if(*CharIsHuman1 == 1){
PortraitExists1 = 1;
WhichCharSelected1 = 1;
SelectionDisplayed1 = 1;
SelectionDurationTicks1 = 1;
SelectionDuration1 = 100;
LoadFighterSelectBigPortraitFirst(CharacterName[WhichCharSelected1], &BigPortraitTexture1, &NameTexture1);
}

if(*CharIsHuman2 == 0){
PortraitExists2 = 0;

WhichCharSelected2 = -1;
//WhichCharSelected2 = ((rand()%CharAmount));
//printf("CPU Selected: %X!\n", WhichCharSelected2);
SelectionDisplayed2 = 0;
SelectionDurationTicks2 = 1;
SelectionDuration2 = 100;
}

if(MusicWorks == 1) cdrom_cdda_play(FighterSelectTrack, FighterSelectTrack, 16, CDDA_TRACKS);


while(TimeToGoOn == 0)
 {

 //printf("Loop is still running. \n");

 pvr_wait_ready();
 pvr_scene_begin();
 pvr_list_begin(PVR_LIST_TR_POLY);


  DrawFighterSelectBackGround();
  DrawSmallPortraits(PositionX, PositionY, SizeX, SizeY, SmallPortraitTextures, CharAmount);
  DrawFighterSelectBigPortrait(&BigPortraitTexture1, &NameTexture1, PortraitExists1, BigPortraitScreenPositionX1, BigPortraitScreenPositionY1, BigPortraitSizeX1, BigPortraitSizeY1, 0);
  DrawFighterSelectBigPortrait(&BigPortraitTexture2, &NameTexture2, PortraitExists2, BigPortraitScreenPositionX2, BigPortraitScreenPositionY2, BigPortraitSizeX2, BigPortraitSizeY2, 1);
  if(SelectionDisplayed1 == 1) DrawSpecialColorTransparencyFrame(PositionX[WhichCharSelected1], PositionY[WhichCharSelected1], SizeX[WhichCharSelected1], SizeY[WhichCharSelected1], 5, Ticks1, SelectionDone1, 1); 
  if(SelectionDisplayed2 == 1) DrawSpecialColorTransparencyFrame(PositionX[WhichCharSelected2], PositionY[WhichCharSelected2], SizeX[WhichCharSelected2], SizeY[WhichCharSelected2], 5, Ticks2, SelectionDone2, 2); 


 if(ReadyToRock1 == 1 && ReadyToRock2 == 1)
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

 if(SelectionDurationTicks1 > SelectionDuration1 && ReadyToRock1 == 0){
  ReadyToRock1 = 1;
  Ticks1 = 5;
  *PlayerID1 = WhichCharSelected1;
  //CharacterName1 = CharacterName[WhichCharSelected1];
  Bluff = sprintf(CharacterName1, "%.8s", CharacterName[WhichCharSelected1]);
  

  if(*PlayerID2 == -2){
   WhichCharSelected2 = 0;
   PortraitExists2 = 1;
   
   srand(rtc_unix_secs());
   FinalAICharSelected = ((rand()%CharAmount));

//-----------------------BETA Mode

if(WhichCharSelected1 == 1) FinalAICharSelected = 3;
else FinalAICharSelected = 1;

//-----------------------END

   while(FinalAICharSelected == WhichCharSelected1 || FinalAICharSelected == *CharIDCPU1 || FinalAICharSelected == *CharIDCPU2 || FinalAICharSelected == *CharIDCPU3 || FinalAICharSelected == *CharIDCPU4 || FinalAICharSelected == *CharIDCPU5 || FinalAICharSelected == *CharIDCPU6 || FinalAICharSelected == *CharIDCPU7 || FinalAICharSelected == *CharIDCPU8){
    FinalAICharSelected++;
    if(FinalAICharSelected == CharAmount) FinalAICharSelected = 0;
    }
   printf("CPU Selected: %X!\n", WhichCharSelected2);
   SelectionDisplayed2 = 1;
   LoadFighterSelectBigPortraitFirst(CharacterName[WhichCharSelected2], &BigPortraitTexture2, &NameTexture2);
   }
  }

 if(SelectionDurationTicks2 > SelectionDuration2 && ReadyToRock2 == 0){
  ReadyToRock2 = 1;
  Ticks2 = 5;
  if(CharIsHuman2 == 0){
  if(*CharIDCPU1 == -1) *CharIDCPU1 = WhichCharSelected2;
  else if(*CharIDCPU2 == -1) *CharIDCPU2 = WhichCharSelected2;
  else if(*CharIDCPU3 == -1) *CharIDCPU3 = WhichCharSelected2;
  else if(*CharIDCPU4 == -1) *CharIDCPU4 = WhichCharSelected2;
  else if(*CharIDCPU5 == -1) *CharIDCPU5 = WhichCharSelected2;
  else if(*CharIDCPU6 == -1) *CharIDCPU6 = WhichCharSelected2;
  else if(*CharIDCPU7 == -1) *CharIDCPU7 = WhichCharSelected2;
  else *CharIDCPU8 = WhichCharSelected2;
  }
  else *PlayerID2 = WhichCharSelected2;
  //CharacterName2 = CharacterName[WhichCharSelected2];
  Bluff = sprintf(CharacterName2, "%.8s", CharacterName[WhichCharSelected2]);
  }

 if(*PlayerID2 == -2 && SelectionDisplayed2 == 1 && SelectionDone2 == 0){
  
   WhichCharSelected2++;
   Ticks2 = 99;
   if(WhichCharSelected2 == CharAmount){ WhichCharSelected2 = 0; AILoopsDone++; }
   LoadFighterSelectBigPortrait(CharacterName[WhichCharSelected2], &BigPortraitTexture2, &NameTexture2);
   snd_sfx_play(ModeSelectSFX, VolumeSFX, 128);

   if(AILoopsDone == AILoopsRequired && WhichCharSelected2 == FinalAICharSelected){
    SelectionDone2 = 1;
    SuperCoolEffectTicks = 1;  
    snd_sfx_play(ModeSelectedSFX, VolumeSFX, 128);
    }
  
  }

   

 if((cont = maple_enum_dev(0, 0)) != NULL) {
  st = (cont_state_t *)maple_dev_status(cont);

   if ((st->buttons & CONT_START) && SelectionDone1 == 0 && ButtonInputAllowed1 == 1 && *CharIsHuman1 == 0) {
   PortraitExists1 = 1;
   *PlayerID1 = -1;
   *CharIsHuman1 = 1;
   SelectionDurationTicks1 = 1;
   SelectionDuration1 = 100;
   if(SelectionDisplayed1 == 0){
   SelectionDisplayed1 = 1;
   WhichCharSelected1 = 1;
   LoadFighterSelectBigPortraitFirst(CharacterName[WhichCharSelected1], &BigPortraitTexture1, &NameTexture1);
   }
   ButtonInputAllowed1 = 0;
   }

   if (((st->buttons & CONT_START) || (st->buttons & CONT_A)) && SelectionDone1 == 0 && ButtonInputAllowed1 == 1 && *CharIsHuman1 == 1) {
   if((WhichCharSelected1 == 1 || WhichCharSelected1 == 3) && (SelectionDone2 == 0 || WhichCharSelected1 != WhichCharSelected2)){
   OffTo = 3;
   SelectionDone1 = 1;
   SuperCoolEffectTicks = 1;
   snd_sfx_play(ModeSelectedSFX, VolumeSFX, 128);
   }
   else{
   snd_sfx_play(ModeDeniedSFX, VolumeSFX, 128);
   }
   ButtonInputAllowed1 = 0;
   }

  if ((st->buttons & CONT_B) && SelectionDone1 == 0 && ButtonInputAllowed1 == 1 && *CharIsHuman1 == 1) {
   OffTo = 13;
   //SelectionDone = 0;
   ReadyToRock1 = 1;
   ReadyToRock2 = 1;
   SuperCoolEffectTicks = 1;
   ButtonInputAllowed1 = 0;
   }

  if ((st->buttons & CONT_DPAD_LEFT) && SelectionDone1 == 0 && ButtonInputAllowed1 == 1 && *CharIsHuman1 == 1) {
   WhichCharSelected1 = CharGoLeft[WhichCharSelected1];
   LoadFighterSelectBigPortrait(CharacterName[WhichCharSelected1], &BigPortraitTexture1, &NameTexture1);
   snd_sfx_play(ModeSelectSFX, VolumeSFX, 128);
   Ticks1 = 99;
   ButtonInputAllowed1 = 0;
   }

  if ((st->buttons & CONT_DPAD_RIGHT) && SelectionDone1 == 0 && ButtonInputAllowed1 == 1 && *CharIsHuman1 == 1) {
   WhichCharSelected1 = CharGoRight[WhichCharSelected1];
   LoadFighterSelectBigPortrait(CharacterName[WhichCharSelected1], &BigPortraitTexture1, &NameTexture1);
   snd_sfx_play(ModeSelectSFX, VolumeSFX, 128);
   Ticks1 = 99;
   ButtonInputAllowed1 = 0;

   }

  if ((st->buttons & CONT_DPAD_UP) && SelectionDone1 == 0 && ButtonInputAllowed1 == 1 && *CharIsHuman1 == 1) {
   WhichCharSelected1 = CharGoUp[WhichCharSelected1];
   LoadFighterSelectBigPortrait(CharacterName[WhichCharSelected1], &BigPortraitTexture1, &NameTexture1);
   snd_sfx_play(ModeSelectSFX, VolumeSFX, 128);
   Ticks1 = 99;
   ButtonInputAllowed1 = 0;
   }

  if ((st->buttons & CONT_DPAD_DOWN) && SelectionDone1 == 0 && ButtonInputAllowed1 == 1 && *CharIsHuman1 == 1) {
   WhichCharSelected1 = CharGoDown[WhichCharSelected1];
   LoadFighterSelectBigPortrait(CharacterName[WhichCharSelected1], &BigPortraitTexture1, &NameTexture1);
   snd_sfx_play(ModeSelectSFX, VolumeSFX, 128);
   Ticks1 = 99;
   ButtonInputAllowed1 = 0;
   }

  if(!(st->buttons & CONT_DPAD_DOWN) && !(st->buttons & CONT_DPAD_UP) && !(st->buttons & CONT_DPAD_RIGHT) && !(st->buttons & CONT_DPAD_LEFT) && !(st->buttons & CONT_START) && !(st->buttons & CONT_A) && !(st->buttons & CONT_B) && !(st->buttons & CONT_X) && !(st->buttons & CONT_Y) && ButtonInputAllowed1 == 0){
  ButtonInputAllowed1 = 1;

  }

  }

 if((cont = maple_enum_dev(1, 0)) != NULL) {
  st = (cont_state_t *)maple_dev_status(cont);

   if ((st->buttons & CONT_START) && SelectionDone2 == 0 && ButtonInputAllowed2 == 1 && *CharIsHuman2 == 0) {
   PortraitExists2 = 1;
   *PlayerID2 = -1;
   *CharIsHuman2 = 1;
   SelectionDurationTicks2 = 1;
   SelectionDuration2 = 100;
   if(SelectionDisplayed2 == 0){
   SelectionDisplayed2 = 1;
   WhichCharSelected2 = 1;
   LoadFighterSelectBigPortraitFirst(CharacterName[WhichCharSelected2], &BigPortraitTexture2, &NameTexture2);
   }
   ButtonInputAllowed2 = 0;
   }

   if (((st->buttons & CONT_START) || (st->buttons & CONT_A)) && SelectionDone2 == 0 && ButtonInputAllowed2 == 1 && *CharIsHuman2 == 1) {
   if((WhichCharSelected2 == 1 || WhichCharSelected2 == 3) && (SelectionDone1 == 0 || WhichCharSelected2 != WhichCharSelected1)){
   OffTo = 3;
   SelectionDone2 = 1;
   SuperCoolEffectTicks = 1;
   snd_sfx_play(ModeSelectedSFX, VolumeSFX, 128);
   }
   else{
   snd_sfx_play(ModeDeniedSFX, VolumeSFX, 128);
   }
   ButtonInputAllowed1 = 0;
   }

  if ((st->buttons & CONT_B) && SelectionDone2 == 0 && ButtonInputAllowed2 == 1 && *CharIsHuman2 == 1) {
   OffTo = 13;
   //SelectionDone = 0;
   ReadyToRock1 = 1;
   ReadyToRock2 = 1;
   SuperCoolEffectTicks = 1;
   ButtonInputAllowed2 = 0;
   }

  if ((st->buttons & CONT_DPAD_LEFT) && SelectionDone2 == 0 && ButtonInputAllowed2 == 1 && *CharIsHuman2 == 1) {
   WhichCharSelected2 = CharGoLeft[WhichCharSelected2];
   LoadFighterSelectBigPortrait(CharacterName[WhichCharSelected2], &BigPortraitTexture2, &NameTexture2);
   snd_sfx_play(ModeSelectSFX, VolumeSFX, 128);
   Ticks2 = 99;
   ButtonInputAllowed2 = 0;
   }

  if ((st->buttons & CONT_DPAD_RIGHT) && SelectionDone2 == 0 && ButtonInputAllowed2 == 1 && *CharIsHuman2 == 1) {
   WhichCharSelected2 = CharGoRight[WhichCharSelected2];
   LoadFighterSelectBigPortrait(CharacterName[WhichCharSelected2], &BigPortraitTexture2, &NameTexture2);
   snd_sfx_play(ModeSelectSFX, VolumeSFX, 128);
   Ticks2 = 99;
   ButtonInputAllowed2 = 0;

   }

  if ((st->buttons & CONT_DPAD_UP) && SelectionDone2 == 0 && ButtonInputAllowed2 == 1 && *CharIsHuman2 == 1) {
   WhichCharSelected2 = CharGoUp[WhichCharSelected2];
   LoadFighterSelectBigPortrait(CharacterName[WhichCharSelected2], &BigPortraitTexture2, &NameTexture2);
   snd_sfx_play(ModeSelectSFX, VolumeSFX, 128);
   Ticks2 = 99;
   ButtonInputAllowed2 = 0;
   }

  if ((st->buttons & CONT_DPAD_DOWN) && SelectionDone2 == 0 && ButtonInputAllowed2 == 1 && *CharIsHuman2 == 1) {
   WhichCharSelected2 = CharGoDown[WhichCharSelected2];
   LoadFighterSelectBigPortrait(CharacterName[WhichCharSelected2], &BigPortraitTexture2, &NameTexture2);
   snd_sfx_play(ModeSelectSFX, VolumeSFX, 128);
   Ticks2 = 99;
   ButtonInputAllowed2 = 0;
   }

  if(!(st->buttons & CONT_DPAD_DOWN) && !(st->buttons & CONT_DPAD_UP) && !(st->buttons & CONT_DPAD_RIGHT) && !(st->buttons & CONT_DPAD_LEFT) && !(st->buttons & CONT_START) && !(st->buttons & CONT_A) && !(st->buttons & CONT_B) && !(st->buttons & CONT_X) && !(st->buttons & CONT_Y) && ButtonInputAllowed2 == 0){
  ButtonInputAllowed2 = 1;

  }

  }

 if(ReadyToRock1 == 0){
  if(TicksGoUp1 == 1)Ticks1++;
  else Ticks1--;
  }

 if(SelectionDone1 == 0 && Ticks1 >= 100) TicksGoUp1 = 0;
 if(SelectionDone1 == 0 && Ticks1 <= 1) TicksGoUp1 = 1;

 if(SelectionDone1 == 1 && ReadyToRock1 == 0 && Ticks1 >= 5) TicksGoUp1 = 0;
 if(SelectionDone1 == 1 && ReadyToRock1 == 0 && Ticks1 <= 1) TicksGoUp1 = 1;

 if(SelectionDone1 == 1 && ReadyToRock1 == 0) SelectionDurationTicks1++;


 if(ReadyToRock2 == 0){
  if(TicksGoUp2 == 1)Ticks2++;
  else Ticks2--;
  }

 if(SelectionDone2 == 0 && Ticks2 >= 100) TicksGoUp2 = 0;
 if(SelectionDone2 == 0 && Ticks2 <= 1) TicksGoUp2 = 1;

 if(SelectionDone2 == 1 && ReadyToRock2 == 0 && Ticks2 >= 5) TicksGoUp2 = 0;
 if(SelectionDone2 == 1 && ReadyToRock2 == 0 && Ticks2 <= 1) TicksGoUp2 = 1;

 if(SelectionDone2 == 1 && ReadyToRock2 == 0) SelectionDurationTicks2++;
 }

for(i = 0; i<=CharAmount-1; i++){
pvr_mem_free(SmallPortraitTextures[i]);
}
if(PortraitExists1 == 1){ pvr_mem_free(BigPortraitTexture1); pvr_mem_free(NameTexture1);}
if(PortraitExists2 == 1){ pvr_mem_free(BigPortraitTexture2); pvr_mem_free(NameTexture2);}
snd_sfx_unload(ModeSelectSFX);
snd_sfx_unload(ModeSelectedSFX);
snd_sfx_unload(ModeDeniedSFX);
cdrom_cdda_pause();

pvr_mem_stats();

return(OffTo);
}









