void DrawShadow(int DrawCharX, int DrawCharY, int CharWidth, char CharIsLeft, int StageGround){

    int DrawLeft, DrawRight, DrawY, Size, Smallerizer;
    float LeftSide, RightSide;
    

    Smallerizer = (StageGround - DrawCharY)/4;
    if(Smallerizer > (CharWidth/2)+16) Smallerizer = (CharWidth/2)+16;
    if(CharIsLeft == 0 ){
    LeftSide = 1.0;
    RightSide = 0.0;
    DrawLeft = DrawCharX+256-(CharWidth*5/4)+Smallerizer;
    DrawRight = DrawCharX+256+(CharWidth/4)-Smallerizer;
    }
    else{
    DrawLeft = DrawCharX-(CharWidth/4)+Smallerizer;
    DrawRight = DrawCharX+(CharWidth*5/4)-Smallerizer;
    LeftSide = 0.0;
    RightSide = 1.0;
    }
    Size = DrawRight-DrawLeft;
    DrawY = StageGround+256-(Size/2);


    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 64, 64, ShadowTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = DrawLeft;
    vert.y = DrawY;
    vert.z = 3;
    vert.u = LeftSide;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = DrawRight;
    vert.y = DrawY;
    vert.z = 3;
    vert.u = RightSide;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = DrawLeft;
    vert.y = DrawY+Size;
    vert.z = 3;
    vert.u = LeftSide;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = DrawRight;
    vert.y = DrawY + Size;
    vert.z = 3;
    vert.u = RightSide;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

}