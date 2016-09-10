
    float TileSetPositionY = 0;
    float TileSetPositionX = WhichType * 0.125;
    while (TileSetPositionX >= 1){
    TileSetPositionX = TileSetPositionX - 1.0;
    TileSetPositionY = TileSetPositionY + 0.125;
    }

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 512, 512, foreground_tileset, PVR_FILTER_BILINEAR);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = PosX;
    vert.y = PosY;
    vert.z = 2;
    vert.u = TileSetPositionX+0.001953125;
    vert.v = TileSetPositionY+0.001953125;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PosX+40;
    vert.y = PosY;
    vert.z = 2;
    vert.u = TileSetPositionX+0.123046875;
    vert.v = TileSetPositionY+0.001953125;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PosX;
    vert.y = PosY+40;
    vert.z = 2;
    vert.u = TileSetPositionX+0.001953125;
    vert.v = TileSetPositionY+0.123046875;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PosX+40;
    vert.y = PosY+40;
    vert.z = 2;
    vert.u = TileSetPositionX+0.123046875;
    vert.v = TileSetPositionY+0.123046875;
    vert.flags = PVR_CMD_VERTEX_EOL;

    pvr_prim(&vert, sizeof(vert));
