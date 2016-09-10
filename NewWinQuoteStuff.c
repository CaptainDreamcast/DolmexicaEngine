void DrawNewWinQuote(WinQuoteStruct WinQuoteData, char ActualQuote[]){


int ScreenPositionX, ScreenPositionY;

int CurrentChar;
int CurrentDrawnChar;
int Bluff;

char WordLength;

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, FontHeaderData.TextureSizeX, FontHeaderData.TextureSizeY, FontTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

ScreenPositionX = WinQuoteData.QuotePositionX;
ScreenPositionY = WinQuoteData.QuotePositionY;


CurrentChar = 0;
CurrentDrawnChar = 0;

while(CurrentChar < WinQuoteData.QuoteLength){

WordLength = 1;

while(ActualQuote[CurrentChar] != 0x20 && CurrentChar < WinQuoteData.QuoteLength){

CurrentChar++;
WordLength++;

}

if(ScreenPositionX+WordLength*WinQuoteData.FontSize > WinQuoteData.QuotePositionX+WinQuoteData.QuoteSizeX){
ScreenPositionY+=WinQuoteData.FontSize+WinQuoteData.BreakSizeY;
ScreenPositionX = WinQuoteData.QuotePositionX;
}

while(CurrentDrawnChar <= CurrentChar){


Bluff = ActualQuote[CurrentDrawnChar];

if(Bluff < 32 || Bluff > 122) Bluff = 0;
Bluff -= 32;


    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = UpperGuiPositionZ2;
    vert.u = FontCharacterData[Bluff].FilePositionX1;
    vert.v = FontCharacterData[Bluff].FilePositionY1;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+WinQuoteData.FontSize;
    vert.y = ScreenPositionY;
    vert.z = UpperGuiPositionZ2;
    vert.u = FontCharacterData[Bluff].FilePositionX2;
    vert.v = FontCharacterData[Bluff].FilePositionY1;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+WinQuoteData.FontSize;
    vert.z = UpperGuiPositionZ2;
    vert.u = FontCharacterData[Bluff].FilePositionX1;
    vert.v = FontCharacterData[Bluff].FilePositionY2;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+WinQuoteData.FontSize;
    vert.y = ScreenPositionY+WinQuoteData.FontSize;
    vert.z = UpperGuiPositionZ2;
    vert.u = FontCharacterData[Bluff].FilePositionX2;
    vert.v = FontCharacterData[Bluff].FilePositionY2;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));


ScreenPositionX+=WinQuoteData.FontSize;

CurrentDrawnChar++;
}

CurrentChar++;

}
}

void DrawNewWinPortrait(WinQuoteStruct WinQuoteData, pvr_ptr_t PortraitTexture){


    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, WinQuoteData.TextureSizeX, WinQuoteData.TextureSizeY, PortraitTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = WinQuoteData.PortraitPositionX;
    vert.y = WinQuoteData.PortraitPositionY;
    vert.z = UpperGuiPositionZ1;
    vert.u = 0.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = WinQuoteData.PortraitPositionX+WinQuoteData.PortraitSizeX;
    vert.y = WinQuoteData.PortraitPositionY;
    vert.z = UpperGuiPositionZ1;
    vert.u = 1.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = WinQuoteData.PortraitPositionX;
    vert.y = WinQuoteData.PortraitPositionY+WinQuoteData.PortraitSizeY;
    vert.z = UpperGuiPositionZ1;
    vert.u = 0.0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = WinQuoteData.PortraitPositionX+WinQuoteData.PortraitSizeX;;
    vert.y = WinQuoteData.PortraitPositionY+WinQuoteData.PortraitSizeY;
    vert.z = UpperGuiPositionZ1;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

}

uint8 ReadNewWinStuff(char CharacterName[], WinQuoteStruct* WinQuoteData, char* ActualQuote, pvr_ptr_t* PortraitTexture){

file_t InputFile;

char FileDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];

sprintf(FileDir, "%s/%.8s/%.8s.win", FileSystemUsed, CharacterName, CharacterName);

if(!FileExists(FileDir)) return(0);

sprintf(MountPoint, "/DUH_WINNING");
FileDirToRomDisk(FileDir, MountPoint);

sprintf(FileDir, "%s/DATA.hdr", MountPoint);
InputFile = FileOpen(FileDir, O_RDONLY);

FileSeek(InputFile, 0, 0);
FileRead(InputFile, WinQuoteData, sizeof(WinQuoteStruct));

free(ActualQuote);
ActualQuote = (char*) malloc((WinQuoteData->QuoteLength)+1);

FileRead(InputFile, ActualQuote, WinQuoteData->QuoteLength);

ActualQuote[WinQuoteData->QuoteLength] = '\0';

FileClose(InputFile);

//*PortraitTexture = pvr_mem_malloc(512*512*2); //HAS BEEN MOVED BEFORE THE EXISTENCE CHECK
sprintf(FileDir, "%s/PORTRAIT.pkg", MountPoint);
TextureLoadPKG(FileDir, PortraitTexture, &WinQuoteData->TextureSizeX, &WinQuoteData->TextureSizeY, ReAllocateTextureMemory);

fs_romdisk_unmount(MountPoint);

return(1);
}