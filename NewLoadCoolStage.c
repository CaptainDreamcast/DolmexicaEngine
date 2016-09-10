BackGroundHeaderStruct BackGroundHeaderData;
BackGroundStruct BackGroundData[BackGroundAmountMaxIdentifier];
BackGroundAnimationStruct BackGroundAnimationData[BackGroundAnimationAmountMaxIdentifier];
pvr_ptr_t BackGroundTextures[BackGroundAmountMaxIdentifier];

DirtyDeedsDoneDirtCheap = 0;
while(DirtyDeedsDoneDirtCheap < BackGroundAmountMaxIdentifier){
BackGroundData[DirtyDeedsDoneDirtCheap].BackGroundActive = 0;
DirtyDeedsDoneDirtCheap++;
}


NewLoadStageTotally(StageName, BackGroundTextures, &BackGroundHeaderData, BackGroundData, BackGroundAnimationData);

StageGround = BackGroundHeaderData.StageGround;
ShadowPositionX = BackGroundHeaderData.ShadowPositionX;
ShadowPositionY = BackGroundHeaderData.ShadowPositionY;
LeftStageBorder = BackGroundHeaderData.StartLeftStageBorder;
CharacterStretchFactor = BackGroundHeaderData.CharacterStretchFactor;