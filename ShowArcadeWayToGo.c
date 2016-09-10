void LoadShowWayToGoHeader(
ShowWayToGoTextureDataStruct CharTextureData[][WhoAgainstWhoTextureAmount], 
ShowWayToGoTextureDataStruct AdditionalTextureData[], ShowWayToGoEnemyDataStruct* EnemyData, 
pvr_ptr_t BonusTextures[], pvr_ptr_t ConnectionTextures[], pvr_ptr_t* BackGroundTexture, char CharacterName[][9],
pvr_ptr_t BigPortraitTextures[], pvr_ptr_t NameTextures[], pvr_ptr_t LogoTextures[]
){

file_t HeaderFile;

char FileDir[NormalFileDirSize];
char OtherFileDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];

int Bluff;
int BluffX, BluffY;
int CurrentChar;

sprintf(MountPoint, "/ARCADE");

//LOADING BACKGROUND
sprintf(FileDir, "%s%s/SHOWWAYTOGOBG.img", FileSystemUsed, MountPoint);
FileDirToRomDisk(FileDir, MountPoint);
sprintf(FileDir, "%s/1.pkg", MountPoint);
(*BackGroundTexture) = pvr_mem_malloc(2*2*2);
TextureLoadPKG(FileDir, BackGroundTexture, &BluffX, &BluffY, ReAllocateTextureMemory);
fs_romdisk_unmount(MountPoint);

//LOADING BACKGROUND

//MOUNTING ROMDISKS
sprintf(FileDir, "%s%s/BIGPORTRAITS.img", FileSystemUsed, MountPoint);
FileDirToRomDisk(FileDir, "/BIGPORTRAITS");

sprintf(FileDir, "%s%s/NAMES.img", FileSystemUsed, MountPoint);
FileDirToRomDisk(FileDir, "/NAMES");

sprintf(FileDir, "%s%s/LOGOS.img", FileSystemUsed, MountPoint);
FileDirToRomDisk(FileDir, "/LOGOS");
//MOUNTING ROMDISKS

sprintf(FileDir, "%s%s/SHOWWAYTOGO.hdr", FileSystemUsed, MountPoint);
HeaderFile = FileOpen(FileDir, O_RDONLY);

FileSeek(HeaderFile, 0, SEEK_SET);

CurrentChar = CharacterOne;
do{

for(Bluff=0; Bluff<WhoAgainstWhoTextureAmount; Bluff++) FileRead(HeaderFile, &CharTextureData[CurrentChar][Bluff], sizeof(ShowWayToGoTextureDataStruct));

sprintf(FileDir, "/BIGPORTRAITS/%s.pkg", CharacterName[CurrentChar]);
BigPortraitTextures[CurrentChar] = pvr_mem_malloc(2*2*2);
if(!FileExists(FileDir)){ 
sprintf(OtherFileDir, "%s/FALLBACK/BIGPORTRAIT.pkg", FileSystemUsed);
sprintf(FileDir, "/ram/BIGPORTRAIT.pkg");
FileCopyToOtherFileSystem(OtherFileDir, FileDir);
TextureLoadPKG(FileDir, &BigPortraitTextures[CurrentChar], &CharTextureData[CurrentChar][WhoAgainstWhoBigPortraitIdentifier].TextureSizeX, &CharTextureData[CurrentChar][WhoAgainstWhoBigPortraitIdentifier].TextureSizeY, ReAllocateTextureMemory);
FileUnlink(FileDir);
}
else TextureLoadPKG(FileDir, &BigPortraitTextures[CurrentChar], &CharTextureData[CurrentChar][WhoAgainstWhoBigPortraitIdentifier].TextureSizeX, &CharTextureData[CurrentChar][WhoAgainstWhoBigPortraitIdentifier].TextureSizeY, ReAllocateTextureMemory);


sprintf(FileDir, "/NAMES/%s.pkg", CharacterName[CurrentChar]);
NameTextures[CurrentChar] = pvr_mem_malloc(2*2*2);
if(!FileExists(FileDir)){
sprintf(OtherFileDir, "%s/FALLBACK/NAME.pkg", FileSystemUsed);
sprintf(FileDir, "/ram/NAME.pkg");
FileCopyToOtherFileSystem(OtherFileDir, FileDir);
TextureLoadPKG(FileDir, &NameTextures[CurrentChar], &CharTextureData[CurrentChar][WhoAgainstWhoNameIdentifier].TextureSizeX, &CharTextureData[CurrentChar][WhoAgainstWhoNameIdentifier].TextureSizeY, ReAllocateTextureMemory);
FileUnlink(FileDir);
}
else TextureLoadPKG(FileDir, &NameTextures[CurrentChar], &CharTextureData[CurrentChar][WhoAgainstWhoNameIdentifier].TextureSizeX, &CharTextureData[CurrentChar][WhoAgainstWhoNameIdentifier].TextureSizeY, ReAllocateTextureMemory);


sprintf(FileDir, "/LOGOS/%s.pkg", CharacterName[CurrentChar]);
LogoTextures[CurrentChar] = pvr_mem_malloc(2*2*2);
if(!FileExists(FileDir)){ 
sprintf(OtherFileDir, "%s/FALLBACK/LOGO.pkg", FileSystemUsed);
sprintf(FileDir, "/ram/LOGO.pkg");
FileCopyToOtherFileSystem(OtherFileDir, FileDir);
TextureLoadPKG(FileDir, &LogoTextures[CurrentChar], &CharTextureData[CurrentChar][WhoAgainstWhoLogoIdentifier].TextureSizeX, &CharTextureData[CurrentChar][WhoAgainstWhoLogoIdentifier].TextureSizeY, ReAllocateTextureMemory);
FileUnlink(FileDir);
}
else TextureLoadPKG(FileDir, &LogoTextures[CurrentChar], &CharTextureData[CurrentChar][WhoAgainstWhoLogoIdentifier].TextureSizeX, &CharTextureData[CurrentChar][WhoAgainstWhoLogoIdentifier].TextureSizeY, ReAllocateTextureMemory);


CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);

FileRead(HeaderFile, EnemyData, sizeof(ShowWayToGoEnemyDataStruct));

CurrentChar = 0;
do{
FileRead(HeaderFile, &AdditionalTextureData[CurrentChar], sizeof(ShowWayToGoTextureDataStruct));
CurrentChar++;
} while(CurrentChar < ShowWayToGoAdditionalTextureDataAmount);


sprintf(FileDir, "%s%s/SHOWWAYTOGOBONUS.img", FileSystemUsed, MountPoint);
FileDirToRomDisk(FileDir, MountPoint);

for(CurrentChar=0;CurrentChar<ShowWayToGoBonusTextureAmount; CurrentChar++){
sprintf(FileDir, "%s/%d.pkg", MountPoint, CurrentChar);
BonusTextures[CurrentChar] = pvr_mem_malloc(2*2*2);
TextureLoadPKG(FileDir, &BonusTextures[CurrentChar], &AdditionalTextureData[CurrentChar].TextureSizeX, &AdditionalTextureData[CurrentChar].TextureSizeY, ReAllocateTextureMemory);
}
fs_romdisk_unmount(MountPoint);

sprintf(FileDir, "%s%s/SHOWWAYTOGOCONNECTION.img", FileSystemUsed, MountPoint);
FileDirToRomDisk(FileDir, MountPoint);

for(CurrentChar=0;CurrentChar<ShowWayToGoConnectionTextureAmount; CurrentChar++){
sprintf(FileDir, "%s/%d.pkg", MountPoint, CurrentChar);
ConnectionTextures[CurrentChar] = pvr_mem_malloc(2*2*2);
TextureLoadPKG(FileDir, &ConnectionTextures[CurrentChar], &AdditionalTextureData[ConnectionDataIdentifier].TextureSizeX, &AdditionalTextureData[ConnectionDataIdentifier].TextureSizeY, ReAllocateTextureMemory);
}
fs_romdisk_unmount(MountPoint);

FileClose(HeaderFile);

}

void DrawShowWayToGoBackGround(pvr_ptr_t BackGroundTexture){

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
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

void DrawShowWayToGoBigPortraits(
pvr_ptr_t BigPortraitTexture, pvr_ptr_t NameTexture, pvr_ptr_t LogoTexture, 
ShowWayToGoTextureDataStruct CharTextureData[], char CharIsHuman, 
pvr_ptr_t BonusTextures[], ShowWayToGoTextureDataStruct AdditionalTextureData[], int CurrentAction, int CharIsRight
){

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    int CurrentLoopStage;

    float LeftSide, RightSide;



    if(CharIsHuman == 1 || CurrentAction >= ShowWayToGoFlashyStuff) CurrentLoopStage = WhoAgainstWhoLogoIdentifier;
    else CurrentLoopStage = WhoAgainstWhoBigPortraitIdentifier;

    //DEBUG
    CurrentLoopStage = WhoAgainstWhoBigPortraitIdentifier;
    //DEBUG

    while(CurrentLoopStage >= WhoAgainstWhoBigPortraitIdentifier){

    if(CharIsRight && CurrentLoopStage == WhoAgainstWhoBigPortraitIdentifier){LeftSide = 1.0f; RightSide = 0.0f;}
    else{LeftSide = 0.0f; RightSide = 1.0f;}


    if(CurrentLoopStage == WhoAgainstWhoNameIdentifier){
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, CharTextureData[CurrentLoopStage].TextureSizeX, CharTextureData[CurrentLoopStage].TextureSizeX, NameTexture, PVR_FILTER_BILINEAR);
    }
    else if(CurrentLoopStage == WhoAgainstWhoLogoIdentifier){
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, CharTextureData[CurrentLoopStage].TextureSizeX, CharTextureData[CurrentLoopStage].TextureSizeX, LogoTexture, PVR_FILTER_BILINEAR);
    }
    else if(CurrentLoopStage == WhoAgainstWhoBigPortraitIdentifier){
    if(CharIsHuman == 1 || CurrentAction >= ShowWayToGoFlashyStuff) pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, CharTextureData[CurrentLoopStage].TextureSizeX, CharTextureData[CurrentLoopStage].TextureSizeX, BigPortraitTexture, PVR_FILTER_BILINEAR);
    else{ 
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, AdditionalTextureData[MysteryOpponentBigPortraitDataIdentifier].TextureSizeX, AdditionalTextureData[MysteryOpponentBigPortraitDataIdentifier].TextureSizeX, BonusTextures[MysteryOppenentBigPortraitTextureIdentifier], PVR_FILTER_BILINEAR);
    LeftSide = 0.0f; RightSide = 1.0f;
    }
    }
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = CharTextureData[CurrentLoopStage].ScreenPositionX;
    vert.y = CharTextureData[CurrentLoopStage].ScreenPositionY;
    vert.z = 4+CurrentLoopStage;
    vert.u = LeftSide;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = CharTextureData[CurrentLoopStage].ScreenPositionX+CharTextureData[CurrentLoopStage].SizeX;
    vert.y = CharTextureData[CurrentLoopStage].ScreenPositionY;
    vert.z = 4+CurrentLoopStage;
    vert.u = RightSide;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = CharTextureData[CurrentLoopStage].ScreenPositionX;
    vert.y = CharTextureData[CurrentLoopStage].ScreenPositionY+CharTextureData[CurrentLoopStage].SizeY;
    vert.z = 4+CurrentLoopStage;
    vert.u = LeftSide;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = CharTextureData[CurrentLoopStage].ScreenPositionX+CharTextureData[CurrentLoopStage].SizeX;
    vert.y = CharTextureData[CurrentLoopStage].ScreenPositionY+CharTextureData[CurrentLoopStage].SizeY;
    vert.z = 4+CurrentLoopStage;
    vert.u = RightSide;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

CurrentLoopStage--;
}

}


void ShowWayToGoDrawMysteryOpponent(
pvr_ptr_t MysteryTexture, ShowWayToGoTextureDataStruct MysteryTextureData, ShowWayToGoEnemyDataStruct EnemyData,
int WhichCharacterDrawn
){

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, MysteryTextureData.TextureSizeX, MysteryTextureData.TextureSizeY, MysteryTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = EnemyData.PositionX[WhichCharacterDrawn];
    vert.y = EnemyData.PositionY[WhichCharacterDrawn];
    vert.z = 3;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = EnemyData.PositionX[WhichCharacterDrawn]+EnemyData.SizeX;
    vert.y = EnemyData.PositionY[WhichCharacterDrawn];
    vert.z = 3;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = EnemyData.PositionX[WhichCharacterDrawn];
    vert.y = EnemyData.PositionY[WhichCharacterDrawn]+EnemyData.SizeY;
    vert.z = 3;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = EnemyData.PositionX[WhichCharacterDrawn]+EnemyData.SizeX;
    vert.y = EnemyData.PositionY[WhichCharacterDrawn]+EnemyData.SizeY;
    vert.z = 3;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

}

int ShowWayToGoRevealMysteryOpponent(
pvr_ptr_t MysteryTexture, ShowWayToGoTextureDataStruct MysteryTextureData, int WhichCharacterDrawn, 
pvr_ptr_t SmallPortraitTexture, FighterSelectSmallPortraitStruct SmallPortraitData, 
ShowWayToGoEnemyDataStruct EnemyData, int* Ticks, int* TicksGoUp
){

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    if(!(*TicksGoUp)) pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, MysteryTextureData.TextureSizeX, MysteryTextureData.TextureSizeY, MysteryTexture, PVR_FILTER_BILINEAR);
    else pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, SmallPortraitData.TextureSizeX, SmallPortraitData.TextureSizeY, SmallPortraitTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = EnemyData.PositionX[WhichCharacterDrawn]+EnemyData.SizeX-(*Ticks);
    vert.y = EnemyData.PositionY[WhichCharacterDrawn];
    vert.z = 3;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = EnemyData.PositionX[WhichCharacterDrawn]+(*Ticks);
    vert.y = EnemyData.PositionY[WhichCharacterDrawn];
    vert.z = 3;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = EnemyData.PositionX[WhichCharacterDrawn]+EnemyData.SizeX-(*Ticks);
    vert.y = EnemyData.PositionY[WhichCharacterDrawn]+EnemyData.SizeY;
    vert.z = 3;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = EnemyData.PositionX[WhichCharacterDrawn]+(*Ticks);
    vert.y = EnemyData.PositionY[WhichCharacterDrawn]+EnemyData.SizeY;
    vert.z = 3;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

    printf("Ticks: (%d)\n", (*Ticks));

    if(!(*TicksGoUp)) (*Ticks)--;
    else (*Ticks)++;

    if((*Ticks) <= 0) (*TicksGoUp) = 1;
    
    if((*Ticks) == EnemyData.SizeX) return(ShowWayToGoFlashyStuff);
    else return(ShowWayToGoReadyToReveal);

}

void ShowWayToGoDrawSmallPortrait(
int WhichCharacterDrawn, pvr_ptr_t SmallPortraitTexture, FighterSelectSmallPortraitStruct SmallPortraitData,
ShowWayToGoEnemyDataStruct EnemyData, int EnemyDefeated
){


    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, SmallPortraitData.TextureSizeX, SmallPortraitData.TextureSizeY, SmallPortraitTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = EnemyData.PositionX[WhichCharacterDrawn];
    vert.y = EnemyData.PositionY[WhichCharacterDrawn];
    vert.z = 3;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = EnemyData.PositionX[WhichCharacterDrawn]+EnemyData.SizeX;
    vert.y = EnemyData.PositionY[WhichCharacterDrawn];
    vert.z = 3;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = EnemyData.PositionX[WhichCharacterDrawn];
    vert.y = EnemyData.PositionY[WhichCharacterDrawn]+EnemyData.SizeY;
    vert.z = 3;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = EnemyData.PositionX[WhichCharacterDrawn]+EnemyData.SizeX;
    vert.y = EnemyData.PositionY[WhichCharacterDrawn]+EnemyData.SizeY;
    vert.z = 3;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

}

void DrawConnectionTexture(pvr_ptr_t ConnectionTexture, ShowWayToGoTextureDataStruct ConnectionData){

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, ConnectionData.TextureSizeX, ConnectionData.TextureSizeY, ConnectionTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ConnectionData.ScreenPositionX;
    vert.y = ConnectionData.ScreenPositionY;
    vert.z = 3;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ConnectionData.ScreenPositionX+ConnectionData.SizeX;
    vert.y = ConnectionData.ScreenPositionY;
    vert.z = 3;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ConnectionData.ScreenPositionX;
    vert.y = ConnectionData.ScreenPositionY+ConnectionData.SizeY;
    vert.z = 3;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ConnectionData.ScreenPositionX+ConnectionData.SizeX;
    vert.y = ConnectionData.ScreenPositionY+ConnectionData.SizeY;
    vert.z = 3;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));



}


void DrawShowWayToGoSmallStuff(
pvr_ptr_t SmallPortraitTextures[], pvr_ptr_t ConnectionTextures[], pvr_ptr_t BonusTextures[],
int WhichCharacterFight, ShowWayToGoEnemyDataStruct EnemyData, FighterSelectSmallPortraitStruct SmallPortraitData[], 
ShowWayToGoTextureDataStruct AdditionalTextureData[], int* CurrentAction, int ArcadeLength,
int* Ticks, int* TicksGoUp, int CharIDCPU[]
){

int WhichConnectionTexture;
int WhichCharacterDrawn;

WhichCharacterDrawn = 0;
while(WhichCharacterDrawn < ArcadeLength){



if(EnemyData.PositionX[WhichCharacterDrawn] < ScreenSizeX && 
   EnemyData.PositionY[WhichCharacterDrawn] < ScreenSizeY &&
   EnemyData.PositionX[WhichCharacterDrawn] > 0 && 
   EnemyData.PositionY[WhichCharacterDrawn] > 0 &&
   EnemyData.PositionX[WhichCharacterDrawn]+EnemyData.SizeX < ScreenSizeX &&
   EnemyData.PositionY[WhichCharacterDrawn]+EnemyData.SizeY < ScreenSizeY &&
   EnemyData.PositionX[WhichCharacterDrawn]+EnemyData.SizeX > 0 &&
   EnemyData.PositionY[WhichCharacterDrawn]+EnemyData.SizeY > 0){

if(WhichCharacterDrawn > WhichCharacterFight){ 
ShowWayToGoDrawMysteryOpponent(BonusTextures[MysteryOpponentTextureIdentifier], AdditionalTextureData[MysteryOpponentDataIdentifier], EnemyData, WhichCharacterDrawn);
WhichConnectionTexture = ConnectionNotConquered;
}
else if(WhichCharacterDrawn == WhichCharacterFight){
if(*CurrentAction <= ShowWayToGoFindTheEnemy) ShowWayToGoDrawMysteryOpponent(BonusTextures[MysteryOpponentTextureIdentifier], AdditionalTextureData[MysteryOpponentDataIdentifier], EnemyData, WhichCharacterDrawn);
else if(*CurrentAction == ShowWayToGoReadyToReveal) *CurrentAction = ShowWayToGoRevealMysteryOpponent(BonusTextures[MysteryOpponentTextureIdentifier], AdditionalTextureData[MysteryOpponentDataIdentifier], WhichCharacterDrawn, SmallPortraitTextures[CharIDCPU[WhichCharacterDrawn]], SmallPortraitData[CharIDCPU[WhichCharacterDrawn]], EnemyData, Ticks, TicksGoUp);
else ShowWayToGoDrawSmallPortrait(WhichCharacterDrawn, SmallPortraitTextures[CharIDCPU[WhichCharacterDrawn]], SmallPortraitData[CharIDCPU[WhichCharacterDrawn]], EnemyData, NoDrawDefeated);
WhichConnectionTexture = ConnectionNotConquered;
}
else{ 
ShowWayToGoDrawSmallPortrait(WhichCharacterDrawn, SmallPortraitTextures[CharIDCPU[WhichCharacterDrawn]], SmallPortraitData[CharIDCPU[WhichCharacterDrawn]], EnemyData, DrawDefeated);
WhichConnectionTexture = ConnectionConquered;
}

if(EnemyData.PositionDifferenceX > 0){ 
AdditionalTextureData[ConnectionDataIdentifier].ScreenPositionX = EnemyData.PositionX[WhichCharacterDrawn]+EnemyData.SizeX;
AdditionalTextureData[ConnectionDataIdentifier].SizeX = EnemyData.PositionX[WhichCharacterDrawn+1]-EnemyData.PositionX[WhichCharacterDrawn]+EnemyData.SizeX;
}
else if(EnemyData.PositionDifferenceX < 0){
AdditionalTextureData[ConnectionDataIdentifier].ScreenPositionX = EnemyData.PositionX[WhichCharacterDrawn];
AdditionalTextureData[ConnectionDataIdentifier].SizeX = EnemyData.PositionX[WhichCharacterDrawn]-EnemyData.PositionX[WhichCharacterDrawn+1]+EnemyData.SizeX;
}
else{
AdditionalTextureData[ConnectionDataIdentifier].ScreenPositionX = EnemyData.PositionX[WhichCharacterDrawn];
AdditionalTextureData[ConnectionDataIdentifier].SizeX = EnemyData.SizeX;
}
if(EnemyData.PositionDifferenceY > 0){ 
AdditionalTextureData[ConnectionDataIdentifier].ScreenPositionY = EnemyData.PositionY[WhichCharacterDrawn]+EnemyData.SizeY;
AdditionalTextureData[ConnectionDataIdentifier].SizeY = EnemyData.PositionY[WhichCharacterDrawn+1]-EnemyData.PositionY[WhichCharacterDrawn]+EnemyData.SizeY;
}
else if(EnemyData.PositionDifferenceY < 0){
AdditionalTextureData[ConnectionDataIdentifier].ScreenPositionY = EnemyData.PositionY[WhichCharacterDrawn];
AdditionalTextureData[ConnectionDataIdentifier].SizeY = EnemyData.PositionY[WhichCharacterDrawn]-EnemyData.PositionY[WhichCharacterDrawn+1]+EnemyData.SizeY;
}
else{
AdditionalTextureData[ConnectionDataIdentifier].ScreenPositionY = EnemyData.PositionY[WhichCharacterDrawn];
AdditionalTextureData[ConnectionDataIdentifier].SizeY = EnemyData.SizeY;
}

DrawConnectionTexture(ConnectionTextures[WhichConnectionTexture], AdditionalTextureData[ConnectionDataIdentifier]);

}



WhichCharacterDrawn++;
}


//FINISH
}


int ShowArcadeWayToGo(int ArcadeLength, int PlayerID[], int CharIDCPU[], int* WhichCharacterFight, char CharacterName[][9], char CharIsHuman[], char BackGroundName[]){

short CharacterAmount;

int CurrentChar;
int OtherChar;

int CurrentAction;

int ReadyToRock;
int DoNotShowTheScreen;
int AbortImmediately;

int Bluff;
int DirtyDeedsDoneDirtCheap;

int Ticks;
int TicksGoUp;

int SuperCoolEffectTicks;
int DrawIntro;

int OffTo;

FetchCharacterAmount(ArcadeModeIdentifier, &CharacterAmount);

maple_device_t *cont;
cont_state_t *st;

pvr_ptr_t SmallPortraitTextures[CharacterAmount];
FighterSelectSmallPortraitStruct SmallPortraitData[CharacterAmount];

pvr_ptr_t BackGroundTexture;

pvr_ptr_t BigPortraitTextures[MaxCharsOnScreen];
pvr_ptr_t NameTextures[MaxCharsOnScreen];
pvr_ptr_t LogoTextures[MaxCharsOnScreen];

pvr_ptr_t ConnectionTextures[ShowWayToGoConnectionTextureAmount];
pvr_ptr_t BonusTextures[ShowWayToGoBonusTextureAmount];

ShowWayToGoTextureDataStruct AdditionalTextureData[ShowWayToGoAdditionalTextureAmount];
ShowWayToGoTextureDataStruct CharTextureData[MaxCharsOnScreen][WhoAgainstWhoTextureAmount];

ShowWayToGoEnemyDataStruct EnemyData;

OffTo = WhoAgainstWhoStage;
DoNotShowTheScreen = 0;
SuperCoolEffectTicks = 1;
DrawIntro =1;

LoadSelectableCharacters(SmallPortraitData, SmallPortraitTextures, ArcadeModeIdentifier);
#include "ArcadeCalculateNextFight.c"

if(!DoNotShowTheScreen){ LoadShowWayToGoHeader(CharTextureData, AdditionalTextureData, &EnemyData, BonusTextures, ConnectionTextures, &BackGroundTexture, CharacterName, BigPortraitTextures, NameTextures, LogoTextures);
AbortImmediately = 0;
}
else AbortImmediately = 1;

//printf("EnemySizeX: (%d)\n", EnemyData.SizeX);
//printf("EnemySizeY: (%d)\n", EnemyData.SizeY);

EnemyData.DesiredFinalPositionX = (ScreenSizeX/2)-(EnemyData.SizeX/2);
EnemyData.DesiredFinalPositionY = (ScreenSizeY/2)-(EnemyData.SizeY/2);

//printf("FinalPositionX: (%d)\n", EnemyData.DesiredFinalPositionX);
//printf("FinalPositionY: (%d)\n", EnemyData.DesiredFinalPositionY);

CurrentChar = 0;
do{

EnemyData.PositionX[CurrentChar] = EnemyData.DesiredFinalPositionX+(EnemyData.PositionDifferenceX*CurrentChar);
EnemyData.PositionY[CurrentChar] = EnemyData.DesiredFinalPositionY+(EnemyData.PositionDifferenceY*CurrentChar);

//printf("EnemyPositionX: (%d)\n", EnemyData.PositionX[CurrentChar]);
//printf("EnemyPositionY: (%d)\n", EnemyData.PositionY[CurrentChar]);
//printf("TextureSizeX: (%d)\n", SmallPortraitData[CurrentChar].TextureSizeX);
//printf("TextureSizeY: (%d)\n", SmallPortraitData[CurrentChar].TextureSizeY);

CurrentChar++;
} while(CurrentChar < ArcadeLength);

Ticks = EnemyData.SizeX-1;
TicksGoUp = 0;

//Their hurt will be mended, when you return to end it.
DoNotShowTheScreen = 1;
//Their hurt will be mended, when you return to end it.

CurrentAction = ShowWayToGoFindTheEnemy;
while(!DoNotShowTheScreen){

pvr_wait_ready();
pvr_scene_begin();
pvr_list_begin(PVR_LIST_TR_POLY);

DrawShowWayToGoBackGround(BackGroundTexture);
DrawShowWayToGoSmallStuff(SmallPortraitTextures, ConnectionTextures, BonusTextures, *WhichCharacterFight, EnemyData, SmallPortraitData, AdditionalTextureData, &CurrentAction, ArcadeLength, &Ticks, &TicksGoUp, CharIDCPU);

CurrentChar = CharacterOne;
do{
DrawShowWayToGoBigPortraits(BigPortraitTextures[CurrentChar], NameTextures[CurrentChar], LogoTextures[CurrentChar], CharTextureData[CurrentChar], CharIsHuman[CurrentChar], BonusTextures, AdditionalTextureData, CurrentAction, CurrentChar);
CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);

if(CurrentAction == ShowWayToGoFinishIt)
{
DoNotShowTheScreen = FadeToBlack(SuperCoolEffectTicks);
SuperCoolEffectTicks++;
}
if(DrawIntro == 1)
{ 
DrawIntro = DrawSuperCoolEffect(SuperCoolEffectTicks);
SuperCoolEffectTicks++;
}



pvr_list_finish();
pvr_scene_finish();

if(CurrentAction == ShowWayToGoOhMyGodItIsHim){
Ticks++;
if(Ticks >= ShowWayToGoEnemyDisplayDuration) CurrentAction = ShowWayToGoFinishIt;
}
else if(CurrentAction == ShowWayToGoFlashyStuff){
SuperCoolEffectTicks = 1;
Ticks = 1;
CurrentAction = ShowWayToGoOhMyGodItIsHim;
}
else if(CurrentAction == ShowWayToGoFindTheEnemy){
if(EnemyData.PositionDifferenceY != 0){
if(EnemyData.PositionDifferenceY > 0){
for(CurrentChar=0; CurrentChar<ArcadeLength; CurrentChar++) EnemyData.PositionY[CurrentChar]--;
if(EnemyData.PositionY[*WhichCharacterFight] <= EnemyData.DesiredFinalPositionY){
if(EnemyData.PositionDifferenceX == 0) CurrentAction = ShowWayToGoReadyToReveal;
else EnemyData.PositionDifferenceY = 0;
EnemyData.PositionY[*WhichCharacterFight] = EnemyData.DesiredFinalPositionY;
}
}
else{
for(CurrentChar=0; CurrentChar<ArcadeLength; CurrentChar++) EnemyData.PositionY[CurrentChar]++;
if(EnemyData.PositionY[*WhichCharacterFight] >= EnemyData.DesiredFinalPositionY){
if(EnemyData.PositionDifferenceX == 0) CurrentAction = ShowWayToGoReadyToReveal;
else EnemyData.PositionDifferenceY = 0;
EnemyData.PositionY[*WhichCharacterFight] = EnemyData.DesiredFinalPositionY;
}
}
}
if(EnemyData.PositionDifferenceX != 0){
if(EnemyData.PositionDifferenceX > 0){
for(CurrentChar=0; CurrentChar<ArcadeLength; CurrentChar++) EnemyData.PositionX[CurrentChar]--;
if(EnemyData.PositionX[*WhichCharacterFight] <= EnemyData.DesiredFinalPositionX){
if(EnemyData.PositionDifferenceY == 0) CurrentAction = ShowWayToGoReadyToReveal;
else EnemyData.PositionDifferenceX = 0;
EnemyData.PositionX[*WhichCharacterFight] = EnemyData.DesiredFinalPositionX;
}
}
else{
for(CurrentChar=0; CurrentChar<ArcadeLength; CurrentChar++) EnemyData.PositionX[CurrentChar]++;
if(EnemyData.PositionX[*WhichCharacterFight] >= EnemyData.DesiredFinalPositionX){
if(EnemyData.PositionDifferenceY == 0) CurrentAction = ShowWayToGoReadyToReveal;
else EnemyData.PositionDifferenceX = 0;
EnemyData.PositionX[*WhichCharacterFight] = EnemyData.DesiredFinalPositionX;
}
}
}
}


if((cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER)) != NULL) {
st = (cont_state_t *)maple_dev_status(cont);

if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
OffTo = FinalExitStage;
DoNotShowTheScreen = 1;
}

}

}
for(Bluff=0; Bluff<CharacterAmount; Bluff++) pvr_mem_free(SmallPortraitTextures[Bluff]);

if(!AbortImmediately){
pvr_mem_free(BackGroundTexture);
for(Bluff=0; Bluff<MaxCharsOnScreen; Bluff++){ 
pvr_mem_free(BigPortraitTextures[Bluff]);
pvr_mem_free(NameTextures[Bluff]);
pvr_mem_free(LogoTextures[Bluff]);
}
for(Bluff=0; Bluff<ShowWayToGoConnectionTextureAmount; Bluff++) pvr_mem_free(ConnectionTextures[Bluff]);
for(Bluff=0; Bluff<ShowWayToGoBonusTextureAmount; Bluff++) pvr_mem_free(BonusTextures[Bluff]);
}
return(OffTo);
}