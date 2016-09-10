
void DrawChar(char CharacterName[], pvr_ptr_t CharacterTexture, char AnimationName[], int FrameID, int DrawX, int DrawY, char CharIsLeft1, PaletteData CharPalette, int StageGround, int ShadowPositionX, int ShadowPositionY, int CharacterTextureSizeDrawn)
{
char FileDir[39];
int Bluff;
int TextureSizeX, TextureSizeY;

Bluff = sprintf(FileDir, "/%.8s_PKG/%.8s%d.pkg", CharacterName, AnimationName, FrameID);
//Bluff = sprintf(FileDir, "/ram/8BIT.pkg");

    TextureLoadPKG(FileDir, &CharacterTexture, &TextureSizeX, &TextureSizeY, NoAllocateTextureMemory);

    float LeftSide;
    float RightSide;

    if(CharIsLeft1 == 0 ){
    LeftSide = 1.0;
    RightSide = 0.0;
    }
    else{
    LeftSide = 0.0;
    RightSide = 1.0;
    }

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    uint32 FormatValue;

    if(CharPalette.PaletteInUse == 1) FormatValue = (PVR_TXRFMT_PAL8BPP | PVR_TXRFMT_8BPP_PAL(CharPalette.WhichBufferPaletteUsed));
    else FormatValue = PVR_TXRFMT_ARGB4444;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, FormatValue, TextureSizeX, TextureSizeY, CharacterTexture, PVR_FILTER_NONE);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = DrawX;
    vert.y = DrawY;
    vert.z = CharacterPositionZMax;
    vert.u = LeftSide;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = DrawX+CharacterTextureSizeDrawn;
    vert.y = DrawY;
    vert.z = CharacterPositionZMax;
    vert.u = RightSide;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = DrawX;
    vert.y = DrawY+CharacterTextureSizeDrawn;
    vert.z = CharacterPositionZMax;
    vert.u = LeftSide;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = DrawX + CharacterTextureSizeDrawn;
    vert.y = DrawY + CharacterTextureSizeDrawn;
    vert.z = CharacterPositionZMax;
    vert.u = RightSide;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

//-------------------------------DrawTheDamnShadow!

    vert.argb = PVR_PACK_COLOR(0.6f, 0.0f, 0.0f, 0.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = DrawX;
    vert.y = StageGround;
    vert.z = ShadowPositionZ;
    vert.u = LeftSide;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = DrawX+CharacterTextureSizeDrawn;
    vert.y = StageGround;
    vert.z = ShadowPositionZ;
    vert.u = RightSide;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = DrawX + ShadowPositionX;
    vert.y = StageGround+ShadowPositionY;
    vert.z = ShadowPositionZ;
    vert.u = LeftSide;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = DrawX + CharacterTextureSizeDrawn + ShadowPositionX;
    vert.y = StageGround+ShadowPositionY;
    vert.z = ShadowPositionZ;
    vert.u = RightSide;
    vert.v = 0.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));
}

void DrawCharLite(pvr_ptr_t CharacterTexture, int DrawX, int DrawY, char CharIsLeft1, PaletteData CharPalette, int StageGround, int ShadowPositionX, int ShadowPositionY, int CharacterTextureSizeDrawn, int CharacterTextureSizeReal)
{

uint32 FormatValue;

    float LeftSide;
    float RightSide;

    if(CharIsLeft1 == 0 ){
    LeftSide = 1.0;
    RightSide = 0.0;
    }
    else{
    LeftSide = 0.0;
    RightSide = 1.0;
    }


    if(CharPalette.PaletteInUse == 1) FormatValue = (PVR_TXRFMT_PAL8BPP | PVR_TXRFMT_8BPP_PAL(CharPalette.WhichBufferPaletteUsed));
    else FormatValue = PVR_TXRFMT_ARGB4444;

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, FormatValue, CharacterTextureSizeReal, CharacterTextureSizeReal, CharacterTexture, PVR_FILTER_NONE);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = DrawX;
    vert.y = DrawY;
    vert.z = CharacterPositionZMax;
    vert.u = LeftSide;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = DrawX+CharacterTextureSizeDrawn;
    vert.y = DrawY;
    vert.z = CharacterPositionZMax;
    vert.u = RightSide;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = DrawX;
    vert.y = DrawY+CharacterTextureSizeDrawn;
    vert.z = CharacterPositionZMax;
    vert.u = LeftSide;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = DrawX + CharacterTextureSizeDrawn;
    vert.y = DrawY + CharacterTextureSizeDrawn;
    vert.z = CharacterPositionZMax;
    vert.u = RightSide;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

//-------------------------------DrawTheDamnShadow!

    vert.argb = PVR_PACK_COLOR(0.6f, 0.0f, 0.0f, 0.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = DrawX;
    vert.y = StageGround;
    vert.z = ShadowPositionZ;
    vert.u = LeftSide;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = DrawX+CharacterTextureSizeDrawn;
    vert.y = StageGround;
    vert.z = ShadowPositionZ;
    vert.u = RightSide;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = DrawX + ShadowPositionX;
    vert.y = StageGround+ShadowPositionY;
    vert.z = ShadowPositionZ;
    vert.u = LeftSide;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = DrawX + CharacterTextureSizeDrawn + ShadowPositionX;
    vert.y = StageGround+ShadowPositionY;
    vert.z = ShadowPositionZ;
    vert.u = RightSide;
    vert.v = 0.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));
}