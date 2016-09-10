void DrawSelectionBackGround(){
    

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 16, 16, SelectionBackGroundTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
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


}

void DrawArrow(int ScreenPositionX, int ScreenPositionY, int Size){

   

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 32, 32, SelectionArrowTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = 4;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+Size;
    vert.y = ScreenPositionY;
    vert.z = 4;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+Size;
    vert.z = 4;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+Size;
    vert.y = ScreenPositionY+Size;
    vert.z = 4;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));


}


int FighterSelection(char *GameLoop, char CharacterName1[], char CharacterName2[]){

    file_t CharacterList;

    maple_device_t *cont;
    cont_state_t *st;

    /*
    SelectionArrowTexture = pvr_mem_malloc(32*32*2);
    png_to_texture("/rd/ARROW.png", SelectionArrowTexture, PNG_FULL_ALPHA);

    SelectionBackGroundTexture = pvr_mem_malloc(16*16*2);
    png_to_texture("/rd/WHITE.png", SelectionBackGroundTexture, PNG_FULL_ALPHA);
    */

    int SelectionLoop = 1;
    int ButtonInputAllowed = 1;
    int CharacterAmount = 6;
    int TextSize = 40;
    int WhichCharSelect = 1;
    int PointerLocation = 1;
    int PointerDrawX = 20;
    int PointerDrawY = ((PointerLocation-1)*TextSize)+80; //80-15
    char CharacterNameBuffer1[9];
    char CharacterNameBuffer2[9];
    int i;
    long CurrentOffset;

    while(SelectionLoop){
    
    if((cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER)) != NULL) {
    st = (cont_state_t *)maple_dev_status(cont);

        if ((st->buttons & CONT_START) && ButtonInputAllowed == 1) {
            *GameLoop = 0;
            return(1);
			}

        if ((st->buttons & CONT_DPAD_DOWN) && ButtonInputAllowed == 1) {
            PointerLocation++;
            if(PointerLocation > CharacterAmount) PointerLocation = CharacterAmount;
            ButtonInputAllowed = 0;
			}

        if ((st->buttons & CONT_DPAD_UP) && ButtonInputAllowed == 1) {
            PointerLocation--;
            if(PointerLocation < 1) PointerLocation = 1;
            ButtonInputAllowed = 0;
			}

        if ((st->buttons & CONT_A) && ButtonInputAllowed == 1) {
            CharacterList = fs_open("/rd/CHARACTERLIST.lst", O_RDONLY);
            
            if(WhichCharSelect == 1) {
            CurrentOffset = fs_seek(CharacterList, (PointerLocation-1)*8+16, 0);
            fs_read(CharacterList, CharacterNameBuffer1, 8);
            //CharacterNameBuffer1[8] = '\0';
            }

            if(WhichCharSelect == 2){
            CurrentOffset = fs_seek(CharacterList, (PointerLocation-1)*8+16, 0);
            fs_read(CharacterList, CharacterNameBuffer2, 8);
            //CharacterNameBuffer2[8] = '\0';
            }

            fs_close(CharacterList);
            WhichCharSelect++;
            if(WhichCharSelect >= 3) {
printf("Character1: %s\n", CharacterNameBuffer1);
printf("Character2: %s\n", CharacterNameBuffer2);
i = 0;
for(i=0; i<8; i++) CharacterName2[i] = CharacterNameBuffer2[i];
CharacterName2[8] = '\0';
i = 0;
for(i=0; i<8; i++) CharacterName1[i] = CharacterNameBuffer1[i];
CharacterName1[8] = '\0';

printf("Character1: %s\n", CharacterName1);
printf("Character2: %s\n", CharacterName2);
return(0);
}
            ButtonInputAllowed = 0;
			}

        if (!(st->buttons & CONT_DPAD_UP) && !(st->buttons & CONT_DPAD_DOWN) && !(st->buttons & CONT_A) && ButtonInputAllowed == 0) {
            ButtonInputAllowed = 1;
			}
    }

    PointerDrawY = ((PointerLocation-1)*TextSize)+80;

    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    DrawSelectionBackGround();
    if(WhichCharSelect == 1) DrawArray("CHOOSE FIRST FIGHTER", 20, 0, 20, 1); 
    if(WhichCharSelect == 2) DrawArray("CHOOSE SECOND FIGHTER", 20, 0, 20, 1); 
    DrawArray("SAGAT", 50, 80, TextSize, 1);
    DrawArray("JOHNNY CAGE", 50, 80+TextSize, TextSize, 1);
    DrawArray("RYU", 50, 80+TextSize*2, TextSize, 1);
    DrawArray("DIO BRANDO", 50, 80+TextSize*3, TextSize, 1);
    DrawArray("MARCO", 50, 80+TextSize*4, TextSize, 1);
    DrawArray("GLACIUS", 50, 80+TextSize*5, TextSize, 1);
    DrawArrow(PointerDrawX, PointerDrawY, 30);
    pvr_list_finish();
    pvr_scene_finish();
}
return(1);
}