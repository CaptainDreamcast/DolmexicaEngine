
void DrawChar(char CharacterName[], CharacterTextureStruct* CharacterTexture, char AnimationName[], int FrameID, int DrawX, int DrawY, char CharIsLeft1, PaletteData CharPalette, int StageGround, int ShadowPositionX, int ShadowPositionY, int CharacterTextureSizeDrawn, uint8 DrawCharDifferently)
{

pvr_poly_cxt_t cxt;
pvr_poly_hdr_t hdr;
pvr_vertex_t vert;

float LeftSide;
float RightSide;
float MasterColor;

char FileDir[NormalFileDirSize];
int TextureSizeX, TextureSizeY;
uint32 FormatValue;


sprintf(FileDir, "/%.8s_PKG/%.8s%d.pkg", CharacterName, AnimationName, FrameID);
CharacterTexture->WhichTextureInUse = (CharacterTexture->WhichTextureInUse+1)%CharacterTextureBufferAmount;

TextureLoadPKG(FileDir, &CharacterTexture->Texture[CharacterTexture->WhichTextureInUse], &TextureSizeX, &TextureSizeY, NoAllocateTextureMemory);

if(DrawCharDifferently) MasterColor = DrawCharDifferentlyGreyTintValue;
else MasterColor = 1.0f;

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

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, FormatValue, TextureSizeX, TextureSizeY, CharacterTexture->Texture[CharacterTexture->WhichTextureInUse], PVR_FILTER_NONE);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, MasterColor, MasterColor, MasterColor);
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

void DrawCharLite(CharacterTextureStruct* CharacterTexture, int DrawX, int DrawY, char CharIsLeft1, PaletteData CharPalette, int StageGround, int ShadowPositionX, int ShadowPositionY, int CharacterTextureSizeDrawn, int CharacterTextureSizeReal, uint8 DrawCharDifferently)
{

uint32 FormatValue;

pvr_poly_cxt_t cxt;
pvr_poly_hdr_t hdr;
pvr_vertex_t vert;

float LeftSide;
float RightSide;
float MasterColor;

if(DrawCharDifferently) MasterColor = DrawCharDifferentlyGreyTintValue;
else MasterColor = 1.0f;

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

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, FormatValue, CharacterTextureSizeReal, CharacterTextureSizeReal, CharacterTexture->Texture[CharacterTexture->WhichTextureInUse], PVR_FILTER_NONE);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, MasterColor, MasterColor, MasterColor);
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