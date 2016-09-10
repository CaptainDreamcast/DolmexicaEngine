char DrawSuperCoolEffect(Ticks){

    char SizeY = 10;
    int SizeX = 640;
    int RealSizeY = SizeY-(Ticks);
    if(RealSizeY <= 0) return(FightIntroAnimation);
    int ScreenPositionX = 0;
    int ScreenPositionY = 0;
    float r, g, b;
    r = g = b = 0;

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 16, 16, LoadingBackGroundTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    while(ScreenPositionY < ScreenSizeY){

    vert.argb = PVR_PACK_COLOR(1.0f, r, g, b);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = AboveAllPositionZ;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX;
    vert.y = ScreenPositionY;
    vert.z = AboveAllPositionZ;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+RealSizeY;
    vert.z = AboveAllPositionZ;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX;
    vert.y = ScreenPositionY+RealSizeY;
    vert.z = AboveAllPositionZ;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

    ScreenPositionY+=SizeY;
    }

return(FightFadeInEffect);

}

char FadeToBlack(Ticks){

    char ReturnValue = 0;
    char SizeY = 10;
    int SizeX = 640;
    int RealSizeY = (Ticks);
    if(RealSizeY > SizeY) ReturnValue = 1;
    int ScreenPositionX = 0;
    int ScreenPositionY = 0;
    float r, g, b;
    r = g = b = 0;

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 16, 16, LoadingBackGroundTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    while(ScreenPositionY < ScreenSizeY){

    vert.argb = PVR_PACK_COLOR(1.0f, r, g, b);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = AboveAllPositionZ;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX;
    vert.y = ScreenPositionY;
    vert.z = AboveAllPositionZ;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+RealSizeY;
    vert.z = AboveAllPositionZ;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX;
    vert.y = ScreenPositionY+RealSizeY;
    vert.z = AboveAllPositionZ;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

    ScreenPositionY+=SizeY;
    }

return(ReturnValue);

}

void NowLoading(){


    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    
    float r, g, b;
    
    r = g = b = 0;

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 16, 16, LoadingBackGroundTexture, PVR_FILTER_NONE);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, r, g, b);
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

    DrawArray("NOW LOADING", 17, 213, LowerGuiPositionZ, 55, 2);

    pvr_list_finish();
    pvr_scene_finish();
}

