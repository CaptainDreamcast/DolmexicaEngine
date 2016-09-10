void LoadGui()
{
int BluffX, BluffY;
char OriginalFileDir[NormalFileDirSize];
char FileDir[NormalFileDirSize];

InitiateDefaultFont();

sprintf(OriginalFileDir, "%s/WHITE.pkg", FileSystemUsed);
sprintf(FileDir, "/ram/WHITE.pkg");
FileCopyToOtherFileSystem(OriginalFileDir, FileDir);
LoadingBackGroundTexture = pvr_mem_malloc(16*16*2);
TextureLoadPKG(FileDir, &LoadingBackGroundTexture, &BluffX, &BluffY, NoAllocateTextureMemory);
fs_unlink(FileDir);

printf("GUI in memory. \n");
}