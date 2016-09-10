void NewDrawEffect(pvr_ptr_t HitEffectTexture, UseHitEffectStruct HitEffects, int HitPositionX, int HitPositionY, uint8 HitEffectIsLeft){
    
    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    float LeftPosition, RightPosition;

    if(HitEffectIsLeft == 1){ LeftPosition = 0.0; RightPosition = 1.0; }
    else{ LeftPosition = 1.0; RightPosition = 0.0; }

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, HitEffects.HitEffectTextureSizeX, HitEffects.HitEffectTextureSizeY, HitEffectTexture, PVR_FILTER_BILINEAR);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = HitPositionX-(HitEffects.HitEffectSizeX/2);
    vert.y = HitPositionY-(HitEffects.HitEffectSizeY/2);
    vert.z = EffectPositionZ;
    vert.u = LeftPosition;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = HitPositionX+(HitEffects.HitEffectSizeX/2);
    vert.y = HitPositionY-(HitEffects.HitEffectSizeY/2);
    vert.z = EffectPositionZ;
    vert.u = RightPosition;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = HitPositionX-(HitEffects.HitEffectSizeX/2);
    vert.y = HitPositionY+(HitEffects.HitEffectSizeY/2);
    vert.z = EffectPositionZ;
    vert.u = LeftPosition;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = HitPositionX+(HitEffects.HitEffectSizeX/2);
    vert.y = HitPositionY+(HitEffects.HitEffectSizeY/2);
    vert.z = EffectPositionZ;
    vert.u = RightPosition;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));
}


void DrawSpecialEffect(char CharacterName[], char SpecialEffectNameBuffer[], int SpecialEffectWhichFrame, int SpecialEffectDrawX, int SpecialEffectDrawY, int SpecialEffectSizeX, int SpecialEffectSizeY, char CharIsLeft, pvr_ptr_t SpecialEffectTextureUsed){
char FileDir[NormalFileDirSize];
int Bluff;
int SpecialEffectTextureSizeX, SpecialEffectTextureSizeY;

Bluff = sprintf(FileDir, "/%.8s_PKG/%.8s%d.kmg", CharacterName, SpecialEffectNameBuffer, SpecialEffectWhichFrame);

    TextureLoadKMG(FileDir, SpecialEffectTextureUsed, &SpecialEffectTextureSizeX, &SpecialEffectTextureSizeY, ReAllocateTextureMemory);

    float LeftSide;
    float RightSide;

    if(CharIsLeft == 0){
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
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, SpecialEffectTextureSizeX, SpecialEffectTextureSizeY, SpecialEffectTextureUsed, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = SpecialEffectDrawX;
    vert.y = SpecialEffectDrawY;
    vert.z = EffectPositionZ;
    vert.u = LeftSide;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = SpecialEffectDrawX+SpecialEffectSizeX;
    vert.y = SpecialEffectDrawY;
    vert.z = EffectPositionZ;
    vert.u = RightSide;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = SpecialEffectDrawX;
    vert.y = SpecialEffectDrawY+SpecialEffectSizeY;
    vert.z = EffectPositionZ;
    vert.u = LeftSide;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = SpecialEffectDrawX + SpecialEffectSizeX;
    vert.y = SpecialEffectDrawY + SpecialEffectSizeY;
    vert.z = EffectPositionZ;
    vert.u = RightSide;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));


}