void ReLoadFont(uint8 WhichFont){

file_t InputFile;

char FileDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];

int Bluff;

if(WhichFont == FontHeaderData.WhichFont) return;

FontHeaderData.WhichFont = WhichFont;

sprintf(FileDir, "%s/FONTS/%d.fnt", FileSystemUsed, WhichFont);
sprintf(MountPoint, "/FONTS");

FileDirToRomDisk(FileDir, MountPoint);

sprintf(FileDir, "%s/TEXTURE.pkg", MountPoint);
TextureLoadPKG(FileDir, &FontTexture, &FontHeaderData.TextureSizeX, &FontHeaderData.TextureSizeY, ReAllocateTextureMemory);

sprintf(FileDir, "%s/HEADER.hdr", MountPoint);
InputFile = fs_open(FileDir, O_RDONLY);

fs_seek(InputFile, 0, 0);
for(Bluff=0; Bluff<FontCharacterAmount; Bluff++) fs_read(InputFile, &FontCharacterData[Bluff], sizeof(FontSingleCharacterStruct));

fs_close(InputFile);
fs_romdisk_unmount(MountPoint);
}

void InitiateDefaultFont(){

FontHeaderData.WhichFont = DefaultFontIdentifier+1;
FontTexture = pvr_mem_malloc(512*512*2);

ReLoadFont(DefaultFontIdentifier);
}