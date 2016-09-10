void CloseStoryBoardAndCleanUp(file_t* StoryBoardFile){

fs_close((*StoryBoardFile));

fs_romdisk_unmount("/STORY");

}

int OpenStoryBoardAndFetchActionAmount(char FileDir[], file_t* StoryBoardFile){

StoryBoardUberHeaderStruct UberHeaderData;

char MountPoint[NormalMountPointSize];


sprintf(MountPoint, "/STORY");

FileDirToRomDisk(FileDir, MountPoint);

sprintf(FileDir, "%s/STORYBOARD", MountPoint);

(*StoryBoardFile) = fs_open(FileDir, O_RDONLY);
fs_seek((*StoryBoardFile), 0, 0);

fs_read((*StoryBoardFile), &UberHeaderData, sizeof(StoryBoardUberHeaderStruct));

return(UberHeaderData.ActionAmount);
}

void StoryBoardLoadSoundEffect(sfxhnd_t* SoundEffect, StoryBoardSoundEffectStruct SoundEffectData){

char FileDir[NormalFileDirSize];

sprintf(FileDir, "/STORY/%d.wav", SoundEffectData.SoundEffectNameID);

(*SoundEffect) = snd_sfx_load(FileDir);
}

void StoryBoardLoadTexture(pvr_ptr_t Texture, StoryBoardTextureStruct* TextureData){

char FileDir[NormalFileDirSize];

if(TextureData->WhichFrame != 0) sprintf(FileDir, "/STORY/%d_%d.pkg", TextureData->TextureNameID, TextureData->WhichFrame);
else sprintf(FileDir, "/STORY/%d.pkg", TextureData->TextureNameID);

TextureLoadPKG(FileDir, &Texture, &TextureData->TextureSizeX, &TextureData->TextureSizeY, NoAllocateTextureMemory);

}

void StoryBoardDrawTexture(pvr_ptr_t Texture, StoryBoardTextureStruct TextureData){

pvr_poly_cxt_t cxt;
pvr_poly_hdr_t hdr;
pvr_vertex_t vert;
pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, TextureData.TextureSizeX, TextureData.TextureSizeY, Texture, PVR_FILTER_BILINEAR);
pvr_poly_compile(&hdr, &cxt);
pvr_prim(&hdr, sizeof(hdr));


vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
vert.oargb = 0;
vert.flags = PVR_CMD_VERTEX;

vert.x = TextureData.PositionX;
vert.y = TextureData.PositionY;
vert.z = TextureData.PositionZ;
vert.u = TextureData.TexturePositionX1;
vert.v = TextureData.TexturePositionY1;
pvr_prim(&vert, sizeof(vert));

vert.x = TextureData.PositionX+TextureData.SizeX;
vert.y = TextureData.PositionY;
vert.z = TextureData.PositionZ;
vert.u = TextureData.TexturePositionX2;
vert.v = TextureData.TexturePositionY1;
pvr_prim(&vert, sizeof(vert));

vert.x = TextureData.PositionX;
vert.y = TextureData.PositionY+TextureData.SizeY;
vert.z = TextureData.PositionZ;
vert.u = TextureData.TexturePositionX1;
vert.v = TextureData.TexturePositionY2;
pvr_prim(&vert, sizeof(vert));

vert.x = TextureData.PositionX+TextureData.SizeX;
vert.y = TextureData.PositionY+TextureData.SizeY;
vert.z = TextureData.PositionZ;
vert.u = TextureData.TexturePositionX2;
vert.v = TextureData.TexturePositionY2;
vert.flags = PVR_CMD_VERTEX_EOL;
pvr_prim(&vert, sizeof(vert));

}

void StoryBoardDrawText(char DrawnText[], StoryBoardTextStruct TextData){

int ScreenPositionX, ScreenPositionY;
int WordLength;

int Bluff;

int DrawnArrayOffset;
int CurrentArrayOffset;

int OriginalTextSize;
int TextSize;

float Red, Green, Blue;

pvr_poly_cxt_t cxt;
pvr_poly_hdr_t hdr;
pvr_vertex_t vert;
pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, FontHeaderData.TextureSizeX, FontHeaderData.TextureSizeY, FontTexture, PVR_FILTER_BILINEAR);

pvr_poly_compile(&hdr, &cxt);
pvr_prim(&hdr, sizeof(hdr));

if(TextData.FontColor == BlackColor) Red = Green = Blue = 0;
else if(TextData.FontColor == RedColor){ Red = 1.0f; Green = Blue = 0;}
else if(TextData.FontColor == GreenColor){ Green = 1.0f; Red = Blue = 0;}
else if(TextData.FontColor == BlueColor){ Blue = 1.0f; Green = Red = 0;}
else if(TextData.FontColor == YellowColor){ Green = Red = 1.0f; Blue = 0;}
else Red = Green = Blue = 1.0f;

ScreenPositionX = TextData.PositionX;
ScreenPositionY = TextData.PositionY;

DrawnArrayOffset = 0;
CurrentArrayOffset = 0;

OriginalTextSize = sprintf(TextData.ActualText, "%s", TextData.ActualText);
TextSize = sprintf(DrawnText, "%s", DrawnText);

//printf("\n");
//printf("DrawnText: (%s)\n", DrawnText);
//printf("TextData.ActualText: (%s)\n", TextData.ActualText);
//printf("TextSize: (%d)\n", TextSize);
//printf("OriginalTextSize: (%d)\n", OriginalTextSize);

while(CurrentArrayOffset < TextSize){

WordLength = 0;

while(TextData.ActualText[CurrentArrayOffset] == 0x20) CurrentArrayOffset++;

while(TextData.ActualText[CurrentArrayOffset] != 0x20 && CurrentArrayOffset < OriginalTextSize){

CurrentArrayOffset++;
WordLength++;

}

if(CurrentArrayOffset > TextSize) CurrentArrayOffset = TextSize;

if(ScreenPositionX+WordLength*TextData.FontSizeX > TextData.PositionX+TextData.SizeX){
ScreenPositionY+=TextData.FontSizeY+TextData.BreakSizeY;
ScreenPositionX = TextData.PositionX;
}

while(DrawnArrayOffset <= CurrentArrayOffset){


if(DrawnText[DrawnArrayOffset] < 32 || DrawnText[DrawnArrayOffset] > 122) Bluff = 0;
else Bluff = DrawnText[DrawnArrayOffset]-32;


    vert.argb = PVR_PACK_COLOR(1.0f, Red, Green, Blue);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = TextData.PositionZ;
    vert.u = FontCharacterData[Bluff].FilePositionX1;
    vert.v = FontCharacterData[Bluff].FilePositionY1;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+TextData.FontSizeX;
    vert.y = ScreenPositionY;
    vert.z = TextData.PositionZ;
    vert.u = FontCharacterData[Bluff].FilePositionX2;
    vert.v = FontCharacterData[Bluff].FilePositionY1;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+TextData.FontSizeY;
    vert.z = TextData.PositionZ;
    vert.u = FontCharacterData[Bluff].FilePositionX1;
    vert.v = FontCharacterData[Bluff].FilePositionY2;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+TextData.FontSizeX;
    vert.y = ScreenPositionY+TextData.FontSizeY;
    vert.z = TextData.PositionZ;
    vert.u = FontCharacterData[Bluff].FilePositionX2;
    vert.v = FontCharacterData[Bluff].FilePositionY2;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));


ScreenPositionX+=TextData.FontSizeX;
DrawnArrayOffset++;
}
}

}

void ReadAllTheNewCoolStoryBoardStuff(
file_t* StoryBoardFile, StoryBoardHeaderStruct* HeaderBuffer, StoryBoardTextureStruct TextureData[], 
StoryBoardTextStruct TextData[], int TextureActive[], int TextActive[], int TextureTicks[], int TextTicks[], 
pvr_ptr_t Texture[], int CurrentTextPosition[], char DrawnText[][StoryBoardMaximumTextSize],
StoryBoardSoundEffectStruct SoundEffectData[], int SoundEffectActive[], int SoundEffectLoaded[], sfxhnd_t SoundEffect[]
){

StoryBoardTextureStruct TextureBuffer;
StoryBoardTextStruct TextBuffer;
StoryBoardSoundEffectStruct SoundEffectBuffer;

int CurrentStruct;
int Identifier;


fs_read((*StoryBoardFile), HeaderBuffer, sizeof(StoryBoardHeaderStruct));

if(HeaderBuffer->SoundTrack != 0) cdrom_cdda_play(HeaderBuffer->SoundTrack, HeaderBuffer->SoundTrack, 16, CDDA_TRACKS);

CurrentStruct = 1;

while(CurrentStruct <= HeaderBuffer->TextureStructAmount){

fs_read((*StoryBoardFile), &TextureBuffer, sizeof(StoryBoardTextureStruct));

Identifier = TextureBuffer.TextureID;

if(TextureBuffer.TextureAction == StoryBoardDestroyTextureIdentifier) TextureActive[Identifier] = 0;
else{
TextureActive[Identifier] = 1;
if(TextureBuffer.PositionX == 0xFFFF) TextureBuffer.PositionX = TextureData[Identifier].PositionX;
if(TextureBuffer.PositionY == 0xFFFF) TextureBuffer.PositionY = TextureData[Identifier].PositionY;

TextureData[Identifier] = TextureBuffer;

if(TextureBuffer.TextureAction == StoryBoardLoadTextureIdentifier){
StoryBoardLoadTexture(Texture[Identifier], &TextureData[Identifier]);
TextureTicks[Identifier] = 0;
}
//printf("\n");
//printf("Identifier Used/Real: (%d/%d)\n", Identifier, TextureData[Identifier].TextureID);
//printf("TextureAction: (%d)\n", TextureData[Identifier].TextureAction);
//printf("TextureName: (%d)\n", TextureData[Identifier].TextureNameID);
//printf("WhichFrame: (%d)\n", TextureData[Identifier].WhichFrame);
//printf("PositionX/Y/Z: (%d/%d/%d)\n", TextureData[Identifier].PositionX, TextureData[Identifier].PositionY, TextureData[Identifier].PositionZ);
//printf("FilePositionX1/Y1: (%f/%f)\n", TextureData[Identifier].TexturePositionX1, TextureData[Identifier].TexturePositionY1);
//printf("FilePositionX2/Y2: (%f/%f)\n", TextureData[Identifier].TexturePositionX2, TextureData[Identifier].TexturePositionY2);
//printf("SizeX/Y: (%d/%d)\n", TextureData[Identifier].SizeX, TextureData[Identifier].SizeY);
//printf("TextureSizeX/Y: (%d/%d)\n", TextureData[Identifier].TextureSizeX, TextureData[Identifier].TextureSizeY);
//printf("Texture: (%X)\n", Texture[Identifier]);
}
CurrentStruct++;
}

CurrentStruct = 1;
while(CurrentStruct <= HeaderBuffer->TextStructAmount){

fs_read((*StoryBoardFile), &TextBuffer, sizeof(StoryBoardTextStruct));
Identifier = TextBuffer.TextID;

if(TextBuffer.TextAction == StoryBoardDestroyTextIdentifier) TextActive[Identifier] = 0;
else{
TextActive[Identifier] = 1;

if(TextBuffer.BuildUp){ DrawnText[Identifier][0] = '\0'; TextTicks[Identifier] = 1; CurrentTextPosition[Identifier] = -1;}
else CurrentTextPosition[Identifier] = sprintf(DrawnText[Identifier], "%s", TextBuffer.ActualText);

//printf("\n");
//printf("Text: (%s)\n", TextBuffer.ActualText);

TextData[Identifier] = TextBuffer;
}
CurrentStruct++;
}

CurrentStruct = 1;
while(CurrentStruct <= HeaderBuffer->SoundEffectStructAmount){

fs_read((*StoryBoardFile), &SoundEffectBuffer, sizeof(StoryBoardSoundEffectStruct));
Identifier = SoundEffectBuffer.SoundEffectID;

if(SoundEffectBuffer.SoundEffectAction == StoryBoardDestroySoundEffectIdentifier) SoundEffectActive[Identifier] = 0;
else{

SoundEffectActive[Identifier] = 1;

if(SoundEffectLoaded[Identifier]) snd_sfx_unload(SoundEffect[Identifier]);
else SoundEffectLoaded[Identifier] = 1;

StoryBoardLoadSoundEffect(&SoundEffect[Identifier], SoundEffectBuffer);

SoundEffectData[Identifier] = SoundEffectBuffer;

}

CurrentStruct++;
}

}