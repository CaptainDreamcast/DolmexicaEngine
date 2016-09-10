int CaptainDraw(int CapX, int CapY, int FromWhere, int CurrentLocation, int RunningAnimation)
{
    float TileSetPositionX = 0.25;
    float TileSetPositionY = 0.0;


    if((RunningAnimation >= 20 && RunningAnimation <= 39) || (RunningAnimation >= 60 && RunningAnimation <= 79)){
    TileSetPositionX = 0.25;
    }
    if(RunningAnimation >= 0 && RunningAnimation <= 19){
    TileSetPositionX = 0.0;
    }
    if(RunningAnimation >= 40 && RunningAnimation <= 59){
    TileSetPositionX = 0.5;
    }



    if(FromWhere == 1){
    TileSetPositionY = 0.5;
    }
    if(FromWhere == 2){
    TileSetPositionY = 0.0;
    }
    if(FromWhere == 3){
    TileSetPositionY = 0.25;
    }
    if(FromWhere == 4){
    TileSetPositionY = 0.75;
    }

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 128, 128, captaindc, PVR_FILTER_BILINEAR);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = CapX;
    vert.y = CapY;
    vert.z = 3;
    vert.u = TileSetPositionX+0.0078125;
    vert.v = TileSetPositionY+0.0078125;
    pvr_prim(&vert, sizeof(vert));

    vert.x = CapX+40;
    vert.y = CapY;
    vert.z = 3;
    vert.u = TileSetPositionX+0.2421875;
    vert.v = TileSetPositionY+0.0078125;
    pvr_prim(&vert, sizeof(vert));

    vert.x = CapX;
    vert.y = CapY+40;
    vert.z = 3;
    vert.u = TileSetPositionX+0.0078125;
    vert.v = TileSetPositionY+0.2421875;
    pvr_prim(&vert, sizeof(vert));

    vert.x = CapX+40;
    vert.y = CapY+40;
    vert.z = 3;
    vert.u = TileSetPositionX+0.2421875;
    vert.v = TileSetPositionY+0.2421875;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));
/*
//Spikes
    pixelRGBA(screen, CapX+13, CapY+1,255,0,0,255);
    pixelRGBA(screen, CapX+14, CapY+1,255,0,0,255);
    pixelRGBA(screen, CapX+16, CapY+1,255,0,0,255);
    pixelRGBA(screen, CapX+17, CapY+1,255,0,0,255);
    pixelRGBA(screen, CapX+19, CapY+1,255,0,0,255);
    pixelRGBA(screen, CapX+20, CapY+1,255,0,0,255);
    pixelRGBA(screen, CapX+22, CapY+1,255,0,0,255);
    pixelRGBA(screen, CapX+23, CapY+1,255,0,0,255);
    pixelRGBA(screen, CapX+25, CapY+1,255,0,0,255);
    pixelRGBA(screen, CapX+26, CapY+1,255,0,0,255);

//Hair
    boxRGBA(screen,CapX+13,CapY+2, CapX+27, CapY+3, 255, 255, 255, 255);
    hlineRGBA(screen, CapX+13, CapX+18, CapY+4, 255, 255, 255, 255);
    hlineRGBA(screen, CapX+22, CapX+27, CapY+4, 255, 255, 255, 255);
    boxRGBA(screen,CapX+13,CapY+5, CapX+14, CapY+6, 255, 255, 255, 255);
    boxRGBA(screen,CapX+25,CapY+5, CapX+27, CapY+6, 255, 255, 255, 255);

//head
//    boxRGBA(screen,CapX+19,CapY+4, CapX+21, CapY+19, 255, 255, 255, 255);



    hlineRGBA(screen, CapX+19, CapX+21, CapY+4, 255, 255, 255, 255);
    hlineRGBA(screen, CapX+15, CapX+24, CapY+5, 255, 255, 255, 255);
    hlineRGBA(screen, CapX+15, CapX+17, CapY+6, 255, 255, 255, 255);
    hlineRGBA(screen, CapX+19, CapX+21, CapY+6, 255, 255, 255, 255);
    hlineRGBA(screen, CapX+23, CapX+24, CapY+6, 255, 255, 255, 255);
    hlineRGBA(screen, CapX+14, CapX+17, CapY+7, 255, 255, 255, 255);
    hlineRGBA(screen, CapX+19, CapX+21, CapY+7, 255, 255, 255, 255);
    hlineRGBA(screen, CapX+23, CapX+26, CapY+7, 255, 255, 255, 255);
    boxRGBA(screen, CapX+14, CapY+8, CapX+26, CapY+9, 255, 255, 255, 255);
    hlineRGBA(screen, CapX+15, CapX+25, CapY+10, 255, 255, 255, 255);
    hlineRGBA(screen, CapX+16, CapX+24, CapY+11, 255, 255, 255, 255);
    boxRGBA(screen, CapX+18, CapY+12, CapX+22, CapY+13, 255, 255, 255, 255);

//eyes
    vlineRGBA(screen, CapX+18, CapY+6, CapY+7, 255, 255, 255, 255);
    vlineRGBA(screen, CapX+22, CapY+6, CapY+7, 255, 255, 255, 255);

//Torso
    hlineRGBA(screen, CapX+16, CapX+24, CapY+14, 255, 255, 255, 255);
    boxRGBA(screen, CapX+14, CapY+15, CapX+26, CapY+17, 255, 255, 255, 255);
    boxRGBA(screen, CapX+15, CapY+18, CapX+25, CapY+22, 255, 255, 255, 255);
    boxRGBA(screen, CapX+15, CapY+23, CapX+18, CapY+24, 255, 255, 255, 255);
    boxRGBA(screen, CapX+22, CapY+23, CapX+25, CapY+24, 255, 255, 255, 255);

//Belt + Buckle

    hlineRGBA(screen, CapX+19, CapX+21, CapY+23, 255, 255, 255, 255);
    pixelRGBA(screen, CapX+19, CapY+24,255,0,0,255);
    pixelRGBA(screen, CapX+20, CapY+24,255,255,255,255);
    pixelRGBA(screen, CapX+21, CapY+24,255,0,0,255);
    hlineRGBA(screen, CapX+18, CapX+22, CapY+25, 255, 255, 255, 255);
    pixelRGBA(screen, CapX+18, CapY+26,255,255,255,255);
    pixelRGBA(screen, CapX+22, CapY+26,255,0,0,255);

    hlineRGBA(screen, CapX+15, CapX+17, CapY+25, 255, 255, 255, 255);
    hlineRGBA(screen, CapX+23, CapX+25, CapY+25, 255, 255, 255, 255);

//Upper part of Pants

    hlineRGBA(screen, CapX+15, CapX+17, CapY+26, 255, 255, 255, 255);
    hlineRGBA(screen, CapX+19, CapX+21, CapY+26, 255, 255, 255, 255);
    hlineRGBA(screen, CapX+23, CapX+25, CapY+26, 255, 255, 255, 255);
    boxRGBA(screen, CapX+15, CapY+27, CapX+25, CapY+28, 255, 255, 255, 255);
    boxRGBA(screen, CapX+15, CapY+29, CapX+19, CapY+33, 255, 255, 255, 255);
    boxRGBA(screen, CapX+22, CapY+29, CapX+25, CapY+33, 255, 255, 255, 255);

//Specific parts of pants

    boxRGBA(screen, CapX+15, CapY+34, CapX+19, CapY+35, 255, 255, 255, 255);
    boxRGBA(screen, CapX+22, CapY+34, CapX+25, CapY+35, 255, 255, 255, 255);
    boxRGBA(screen, CapX+13, CapY+36, CapX+19, CapY+37, 255, 255, 255, 255);
    boxRGBA(screen, CapX+22, CapY+36, CapX+27, CapY+37, 255, 255, 255, 255);
*/

//EventHandler(screen, PosCapX, PosCapY, &CurrentLocation, &FromWhere);
}
