void DrawCoolStage(int LeftStageBorder, BackGroundHeaderStruct BackGroundHeaderData, BackGroundStruct BackGroundData[], BackGroundAnimationStruct BackGroundAnimationData[], pvr_ptr_t BackGroundTextures[], uint8 DrawAnimated){

pvr_ptr_t TextureUsed;

pvr_poly_cxt_t cxt;
pvr_poly_hdr_t hdr;
pvr_vertex_t vert;

int Bluff;
int ReadyToRock;

int PositionX1;
int PositionX2;

float TextureOffsetX1;
float TextureOffsetX2;

float LayerFileMovement;
uint32 FormatValue;

if(BackGroundHeaderData.TextureType == PaletteType) FormatValue = (PVR_TXRFMT_PAL8BPP | PVR_TXRFMT_8BPP_PAL(BackGroundPalette));
else FormatValue = PVR_TXRFMT_ARGB4444;

Bluff = 0;
while(Bluff < BackGroundHeaderData.BackGroundAmount){

ReadyToRock = 1;

LayerFileMovement = 1.0/BackGroundData[Bluff].SizeX;

if(BackGroundHeaderData.RealStageSize == ScreenSizeX) PositionX1 = 0;
else PositionX1 = BackGroundData[Bluff].PositionX-(((BackGroundData[Bluff].LayerSizeX-ScreenSizeX)*1.0)/(BackGroundHeaderData.RealStageSize-ScreenSizeX))*LeftStageBorder;
PositionX2 = PositionX1+BackGroundData[Bluff].SizeX;

if(PositionX1 < 0){
TextureOffsetX1 = LayerFileMovement*(-PositionX1);
PositionX1 = 0;
if(PositionX2 < 0) ReadyToRock = 0;
}
else TextureOffsetX1 = 0.0;

if(PositionX2 > ScreenSizeX){
TextureOffsetX2 = 1.0-(LayerFileMovement*(PositionX2-ScreenSizeX));
PositionX2 = ScreenSizeX;
if(PositionX1 > ScreenSizeX) ReadyToRock = 0;
}
else TextureOffsetX2 = 1.0;

if(ReadyToRock){

if(BackGroundData[Bluff].BackGroundAnimated != 0){
ReadyToRock = (BackGroundData[Bluff].BackGroundAnimated)-1;

if(DrawAnimated){
BackGroundAnimationData[ReadyToRock].Data.Ticks++;
if(BackGroundAnimationData[ReadyToRock].Data.Ticks > BackGroundAnimationData[ReadyToRock].Data.Speed){
BackGroundAnimationData[ReadyToRock].Data.WhichFrame++;
BackGroundAnimationData[ReadyToRock].Data.Ticks = 0;
if(BackGroundAnimationData[ReadyToRock].Data.WhichFrame >= BackGroundAnimationData[ReadyToRock].Data.FrameAmount){
if(BackGroundAnimationData[ReadyToRock].Data.Loop) BackGroundAnimationData[ReadyToRock].Data.WhichFrame = 0;
else{ 
BackGroundAnimationData[ReadyToRock].Data.WhichFrame = BackGroundAnimationData[ReadyToRock].Data.FrameAmount;
BackGroundAnimationData[ReadyToRock].Data.Speed = 0xFF;
}
}
}
}

TextureUsed = BackGroundAnimationData[ReadyToRock].Texture[BackGroundAnimationData[ReadyToRock].Data.WhichFrame];
}
else TextureUsed = BackGroundTextures[Bluff];

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, FormatValue, BackGroundData[Bluff].TextureSizeX, BackGroundData[Bluff].TextureSizeY, TextureUsed, PVR_FILTER_NONE);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = PositionX1;
    vert.y = BackGroundData[Bluff].PositionY;
    vert.z = BackGroundData[Bluff].PositionZ;
    vert.u = TextureOffsetX1;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX2;
    vert.y = BackGroundData[Bluff].PositionY;
    vert.z = BackGroundData[Bluff].PositionZ;
    vert.u = TextureOffsetX2;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX1;
    vert.y = BackGroundData[Bluff].PositionY+BackGroundData[Bluff].SizeY;
    vert.z = BackGroundData[Bluff].PositionZ;
    vert.u = TextureOffsetX1;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX2;
    vert.y = BackGroundData[Bluff].PositionY+BackGroundData[Bluff].SizeY;
    vert.z = BackGroundData[Bluff].PositionZ;
    vert.u = TextureOffsetX2;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

}

Bluff++;
}
}
