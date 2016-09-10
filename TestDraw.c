void TestDraw(){

    file_t fd;
    char* data;

    int length = zlib_getlength("/rd/TEST.gz");
    gzFile f;

    data = (char *)malloc(length+1); // I am not currently freeing it

    f = gzopen("/rd/TEST.gz", "r");
    gzread(f, data, length);
    data[length] = 0;
    gzclose(f);


    fd = fs_open("ram/TemporaryKMG.kmg", O_WRONLY);
    fs_write(fd, data, length);
    fs_close(fd);
    free(data);
    kmg_to_img("/ram/TemporaryKMG.kmg", &IMGFilePlaceholder);
    pvr_txr_load_kimg(&IMGFilePlaceholder, Char2Texture, 0);
    fs_unlink("/ram/TemporaryKMG.kmg");
    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 128, 128, Char2Texture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = 0;
    vert.y = 0;
    vert.z = 1;
    vert.u = 0.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 256;
    vert.y = 0;
    vert.z = 1;
    vert.u = 1.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 0;
    vert.y = 256;
    vert.z = 1;
    vert.u = 0.0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 256;
    vert.y = 256;
    vert.z = 1;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));


}
