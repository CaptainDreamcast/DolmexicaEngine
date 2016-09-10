void DrawCoolStage(int LeftStageBorder, BackGroundHeaderStruct BackGroundHeaderData, BackGroundStruct BackGroundData[], BackGroundAnimationStruct BackGroundAnimationData[], pvr_ptr_t BackGroundTexture[]){


pvr_poly_cxt_t cxt;
pvr_poly_hdr_t hdr;
pvr_vertex_t vert;

int Bluff;
int UpperLayerPositionX;
int LowerLayerPositionX;
int UpperLayerSizeX;
//int UpperLayerSizeY;
int LowerLayerSizeX;
//int LowerLayerSizeY;
int UpperLayerOffset;
int LowerLayerOffset;
float UpperLayerPositionLeft;
float LowerLayerPositionLeft;
float UpperLayerPositionRight;
float LowerLayerPositionRight;
float LayerFileMovement;

int CurrentUpperLayerScreenPosition;
int CurrentLowerLayerScreenPosition;
short DrawnBackGround;

Bluff = 0;

while(BackGroundData[Bluff].BackGroundActive != 0 && Bluff < BackGroundAmountMaxIdentifier){

UpperLayerPositionX = (BackGroundData[Bluff].UpperLayerSizeX-640.0)/(BackGroundHeaderData.RealStageSize-640)*LeftStageBorder;
LowerLayerPositionX = (BackGroundData[Bluff].LowerLayerSizeX-640.0)/(BackGroundHeaderData.RealStageSize-640)*LeftStageBorder;

UpperLayerSizeX = BackGroundScreenSizeX[i]-(UpperLayerPositionX%BackGroundScreenSizeX[i]);
LowerLayerSizeX = BackGroundScreenSizeX[i]-(LowerLayerPositionX%BackGroundScreenSizeX[i]);

UpperLayerOffset = BackGroundScreenSizeX[i]-UpperLayerSizeX;
LowerLayerOffset = BackGroundScreenSizeX[i]-LowerLayerSizeX;

LayerFileMovement = 1.0/BackGroundScreenSizeX[i];

UpperLayerPositionLeft = UpperLayerOffset*LayerFileMovement;
LowerLayerPositionLeft = LowerLayerOffset*LayerFileMovement;

CurrentUpperLayerScreenPosition = 0;
CurrentLowerLayerScreenPosition = 0;

DrawnBackGround = UpperLayerPositionX/BackGroundScreenSizeX[i];

if(i == 0) UseThisTexture = BackGroundTextures1;
else if(i == 1) UseThisTexture = BackGroundTextures2;
else if(i == 2) UseThisTexture = BackGroundTextures3;
else if(i == 3) UseThisTexture = BackGroundTextures4;
else UseThisTexture = BackGroundTextures5;

while(CurrentUpperLayerScreenPosition < 640){

if(CurrentUpperLayerScreenPosition+UpperLayerSizeX <= 640) UpperLayerPositionRight = 1.0;
else{ 
UpperLayerSizeX = 640-CurrentUpperLayerScreenPosition;
UpperLayerPositionRight = (UpperLayerOffset + UpperLayerSizeX)*LayerFileMovement; 
}
if(CurrentLowerLayerScreenPosition+LowerLayerSizeX <= 640) LowerLayerPositionRight = 1.0;
else{ 
LowerLayerSizeX = 640-CurrentLowerLayerScreenPosition;
LowerLayerPositionRight = (LowerLayerOffset + LowerLayerSizeX)*LayerFileMovement;
}

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, BackGroundTextureSizeX[i], BackGroundTextureSizeY[i], UseThisTexture[DrawnBackGround], PVR_FILTER_NONE);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = CurrentUpperLayerScreenPosition;
    vert.y = 0;
    vert.z = BackGroundUpperLayerPositionZ[i];
    vert.u = UpperLayerPositionLeft;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = CurrentUpperLayerScreenPosition+UpperLayerSizeX;
    vert.y = 0;
    vert.z = BackGroundUpperLayerPositionZ[i];
    vert.u = UpperLayerPositionRight;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = CurrentLowerLayerScreenPosition;
    vert.y = 480;
    vert.z = BackGroundLowerLayerPositionZ[i];
    vert.u = LowerLayerPositionLeft;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = CurrentLowerLayerScreenPosition+LowerLayerSizeX;
    vert.y = 480;
    vert.z = BackGroundLowerLayerPositionZ[i];
    vert.u = LowerLayerPositionRight;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));


LowerLayerPositionLeft = 0.0;
UpperLayerPositionLeft = 0.0;
LowerLayerOffset = 0;
UpperLayerOffset = 0;

CurrentUpperLayerScreenPosition += UpperLayerSizeX;
CurrentLowerLayerScreenPosition += LowerLayerSizeX;
DrawnBackGround++;

UpperLayerSizeX = BackGroundScreenSizeX[i];
LowerLayerSizeX = BackGroundScreenSizeX[i];
}
i++;
}
}
