void DrawWarningScreen()
    {

    pvr_ptr_t WarningTexture;
    int Bluff;
    int Ticks = 1;
    int Duration = 180;
    int ScreenPositionX = 0;
    int ScreenPositionY = 0;
    int SizeX = 640;
    int SizeY = 480;
    char FileDir[40];
    int SuperCoolEffectTicks = 1;
    char TimeToGoOn = 0;

    Bluff = sprintf(FileDir, "%s/WARNING.png", FileSystemUsed);

    WarningTexture = pvr_mem_malloc(512*512*2);
    png_to_texture(FileDir, WarningTexture, PNG_FULL_ALPHA);

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;


     while(TimeToGoOn == 0){

     pvr_wait_ready();
     pvr_scene_begin();
     pvr_list_begin(PVR_LIST_TR_POLY);

     if(Ticks > Duration){
      TimeToGoOn = FadeToBlack(SuperCoolEffectTicks);
      SuperCoolEffectTicks++;       
      }
     pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 512, 512, WarningTexture, PVR_FILTER_BILINEAR);
     pvr_poly_compile(&hdr, &cxt);
     pvr_prim(&hdr, sizeof(hdr));

     vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
     vert.oargb = 0;
     vert.flags = PVR_CMD_VERTEX;

     vert.x = ScreenPositionX;
     vert.y = ScreenPositionY;
     vert.z = 1;
     vert.u = 0.0;
     vert.v = 0.0;
     pvr_prim(&vert, sizeof(vert));

     vert.x = ScreenPositionX+SizeX;
     vert.y = ScreenPositionY;
     vert.z = 1;
     vert.u = 1.0;
     vert.v = 0.0;
     pvr_prim(&vert, sizeof(vert));

     vert.x = ScreenPositionX;
     vert.y = ScreenPositionY+SizeY;
     vert.z = 1;
     vert.u = 0.0;
     vert.v = 1.0;
     pvr_prim(&vert, sizeof(vert));

     vert.x = ScreenPositionX+SizeX;
     vert.y = ScreenPositionY+SizeY;
     vert.z = 1;
     vert.u = 1.0;
     vert.v = 1.0;
     vert.flags = PVR_CMD_VERTEX_EOL;
     pvr_prim(&vert, sizeof(vert));
 
     pvr_list_finish();
     pvr_scene_finish();

     Ticks++;
     }
 
    pvr_mem_free(WarningTexture);
    }