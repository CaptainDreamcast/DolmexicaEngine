char BackGroundAmountMax = 5;

int RealStageSize = 1280;

int BackGroundAmount[BackGroundAmountMax];
int BackGroundScreenPositionX[BackGroundAmountMax];
int BackGroundScreenPositionY[BackGroundAmountMax];
int BackGroundTextureSizeX[BackGroundAmountMax];
int BackGroundTextureSizeY[BackGroundAmountMax];
int BackGroundScreenSizeX[BackGroundAmountMax];
int BackGroundScreenSizeY[BackGroundAmountMax];
int BackGroundUpperLayerSizeX[BackGroundAmountMax];
int BackGroundLowerLayerSizeX[BackGroundAmountMax];
int BackGroundUpperLayerPositionZ[BackGroundAmountMax];
int BackGroundLowerLayerPositionZ[BackGroundAmountMax];

DirtyDeedsDoneDirtCheap = 0;

while(DirtyDeedsDoneDirtCheap < BackGroundAmountMax){
BackGroundAmount[DirtyDeedsDoneDirtCheap] = FetchBackGroundAmount(StageName, DirtyDeedsDoneDirtCheap);
DirtyDeedsDoneDirtCheap++;
}

pvr_ptr_t BackGroundTextures1[BackGroundAmount[0]];
pvr_ptr_t BackGroundTextures2[BackGroundAmount[1]];
pvr_ptr_t BackGroundTextures3[BackGroundAmount[2]];
pvr_ptr_t BackGroundTextures4[BackGroundAmount[3]];
pvr_ptr_t BackGroundTextures5[BackGroundAmount[4]];


LoadStageTotally(StageName, &RealStageSize, BackGroundAmountMax, BackGroundAmount, BackGroundScreenPositionX, BackGroundScreenPositionY, BackGroundTextureSizeX, BackGroundTextureSizeY, BackGroundScreenSizeX, BackGroundScreenSizeY, BackGroundUpperLayerSizeX, BackGroundLowerLayerSizeX, BackGroundUpperLayerPositionZ, BackGroundLowerLayerPositionZ, BackGroundTextures1, BackGroundTextures2, BackGroundTextures3, BackGroundTextures4, BackGroundTextures5);