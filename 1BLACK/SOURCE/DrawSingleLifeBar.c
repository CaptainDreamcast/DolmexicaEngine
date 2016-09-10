void DrawLifeBar(int CharHealth, short SpecialLeft, int CharWins, SingleLifeBarStruct LifeBarData, pvr_ptr_t LifeBarTexture, pvr_ptr_t VictoryTexture){

pvr_poly_cxt_t cxt;
pvr_poly_hdr_t hdr;
pvr_vertex_t vert;

int DirtyDeedsDoneDirtCheap;

int BarLeft;
uint8 BarColor;

pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, LifeBarData.LifeBarTextureSizeX, LifeBarData.LifeBarTextureSizeY, LifeBarTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = LifeBarData.LifeBarScreenPositionX;
    vert.y = LifeBarData.LifeBarScreenPositionY;
    vert.z = LowerGuiPositionZ;
    vert.u = 0.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = LifeBarData.LifeBarScreenPositionX+LifeBarData.LifeBarSizeX;
    vert.y = LifeBarData.LifeBarScreenPositionY;
    vert.z = LowerGuiPositionZ;
    vert.u = 1.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = LifeBarData.LifeBarScreenPositionX;
    vert.y = LifeBarData.LifeBarScreenPositionY+LifeBarData.LifeBarSizeY;
    vert.z = LowerGuiPositionZ;
    vert.u = 0.0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = LifeBarData.LifeBarScreenPositionX+LifeBarData.LifeBarSizeX;
    vert.y = LifeBarData.LifeBarScreenPositionY+LifeBarData.LifeBarSizeY;
    vert.z = LowerGuiPositionZ;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));



BarLeft = ((CharHealth*1.0)/CharHealthMax)*LifeBarData.LifeFullSizeX;

if(CharHealth > LifeBarData.FirstColorChange) BarColor = LifeBarData.FirstColor;
else if(CharHealth > LifeBarData.SecondColorChange) BarColor = LifeBarData.SecondColor;
else BarColor = LifeBarData.ThirdColor;

DrawColorBox(LifeBarData.LifeStartPositionX, LifeBarData.LifeStartPositionY, LifeBarPositionZ, BarLeft, LifeBarData.LifeFullSizeY, BarColor);

if(LifeBarData.SpecialFullSizeX > 0){
BarLeft = ((SpecialLeft*1.0)/SpecialBarValueMax)*LifeBarData.SpecialFullSizeX;

if(SpecialLeft > LifeBarData.FirstSpecialColorChange) BarColor = LifeBarData.FirstSpecialColor;
else if(SpecialLeft > LifeBarData.SecondSpecialColorChange) BarColor = LifeBarData.SecondSpecialColor;
else BarColor = LifeBarData.ThirdSpecialColor;

DrawColorBox(LifeBarData.SpecialStartPositionX, LifeBarData.SpecialStartPositionY, LifeBarPositionZ, BarLeft, LifeBarData.SpecialFullSizeY, BarColor);
}


pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, LifeBarData.VictoryTextureSizeX, LifeBarData.VictoryTextureSizeY, VictoryTexture, PVR_FILTER_BILINEAR);
pvr_poly_compile(&hdr, &cxt);
pvr_prim(&hdr, sizeof(hdr));

DirtyDeedsDoneDirtCheap = 1;

while(DirtyDeedsDoneDirtCheap <= CharWins){


    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = LifeBarData.VictoryScreenPositionX;
    vert.y = LifeBarData.VictoryScreenPositionY;
    vert.z = LowerGuiPositionZ;
    vert.u = 0.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = LifeBarData.VictoryScreenPositionX+LifeBarData.VictorySizeX;
    vert.y = LifeBarData.VictoryScreenPositionY;
    vert.z = LowerGuiPositionZ;
    vert.u = 1.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = LifeBarData.VictoryScreenPositionX;
    vert.y = LifeBarData.VictoryScreenPositionY+LifeBarData.VictorySizeY;
    vert.z = LowerGuiPositionZ;
    vert.u = 0.0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = LifeBarData.VictoryScreenPositionX+LifeBarData.VictorySizeX;
    vert.y = LifeBarData.VictoryScreenPositionY+LifeBarData.VictorySizeY;
    vert.z = LowerGuiPositionZ;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));


LifeBarData.VictoryScreenPositionX += LifeBarData.VictorySizeX;
DirtyDeedsDoneDirtCheap++;
}

}