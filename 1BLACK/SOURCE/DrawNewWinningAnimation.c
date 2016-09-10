pvr_ptr_t LoadNewWinningAnimation(WinningAnimationStruct* WinningAnimationData, char CharIsHuman, sfxhnd_t* WinningSoundEffect){

pvr_ptr_t Texture;

file_t InputFile;

char MountPoint[NormalMountPointSize];
char FileDir[NormalFileDirSize];

sprintf(FileDir, "%s/WINNING/WINNING.hdr", FileSystemUsed);

InputFile = fs_open(FileDir, O_RDONLY);
fs_read(InputFile, WinningAnimationData, sizeof(WinningAnimationStruct));
fs_close(InputFile);

if(CharIsHuman) sprintf(FileDir, "%s/WINNING/YOUWIN.img", StreamingFileSystemUsed);
else sprintf(FileDir, "%s/WINNING/YOULOSE.img", StreamingFileSystemUsed);
sprintf(MountPoint, "/TEMPORARY");

FileDirToRomDisk(FileDir, MountPoint);

sprintf(FileDir, "%s/TEXTURE.pkg", MountPoint);
Texture = pvr_mem_malloc(WinningAnimationData->TextureSizeX*WinningAnimationData->TextureSizeY*2);
TextureLoadPKG(FileDir, &Texture, &WinningAnimationData->TextureSizeX, &WinningAnimationData->TextureSizeY, ReAllocateTextureMemory);

sprintf(FileDir, "%s/VOICE.wav", MountPoint);
if(FileExists(FileDir)){
*WinningSoundEffect = snd_sfx_load(FileDir);
snd_sfx_play(*WinningSoundEffect, VolumeSFX, 128);
}
else *WinningSoundEffect = 0;

fs_romdisk_unmount(MountPoint);

return(Texture);
}

void DrawNewWinningAnimation(WinningAnimationStruct WinningAnimationData, pvr_ptr_t WinningAnimationTexture){


    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, WinningAnimationData.TextureSizeX, WinningAnimationData.TextureSizeY, WinningAnimationTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = WinningAnimationData.PositionX;
    vert.y = WinningAnimationData.PositionY;
    vert.z = UpperGuiPositionZ1;
    vert.u = 0.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = WinningAnimationData.PositionX+WinningAnimationData.SizeX;
    vert.y = WinningAnimationData.PositionY;
    vert.z = UpperGuiPositionZ1;
    vert.u = 1.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = WinningAnimationData.PositionX;
    vert.y = WinningAnimationData.PositionY+WinningAnimationData.SizeY;
    vert.z = UpperGuiPositionZ1;
    vert.u = 0.0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = WinningAnimationData.PositionX+WinningAnimationData.SizeX;
    vert.y = WinningAnimationData.PositionY+WinningAnimationData.SizeY;
    vert.z = UpperGuiPositionZ1;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

}