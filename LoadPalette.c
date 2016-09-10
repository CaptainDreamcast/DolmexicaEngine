void InitiatePalette(){

pvr_set_pal_format(PVR_PAL_ARGB8888);

}

int FileDirToPalette(char FileDir[], int WhichPalettePosition){

#define PACK_ARGB8888(a,r,g,b) ( ((a & 0xFF) << 24) | ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | ((b & 0xFF)) )

file_t PaletteFile;

int EntryAmount = 256;
size_t FileLength;
long PaletteBufferPosition = 3;
unsigned char* PaletteBuffer;
long PaletteOffset = EntryAmount*WhichPalettePosition;

PaletteFile = FileOpen(FileDir, O_RDONLY);

if(PaletteFile == FILEHND_INVALID){FileClose(PaletteFile); return(0);}


FileLength = FileTotal(PaletteFile);
PaletteBuffer = (unsigned char*) malloc(FileLength);
FileRead(PaletteFile, PaletteBuffer, FileLength);
FileClose(PaletteFile);

pvr_set_pal_entry(PaletteOffset, PACK_ARGB8888(0,0,0,0));
PaletteOffset++;

while(PaletteBufferPosition < FileLength){

pvr_set_pal_entry(PaletteOffset, PACK_ARGB8888(255, PaletteBuffer[PaletteBufferPosition], PaletteBuffer[PaletteBufferPosition+1], PaletteBuffer[PaletteBufferPosition+2]));
PaletteBufferPosition+=3;
PaletteOffset++;
}

free(PaletteBuffer);

return(1);
}

int LoadPalette8(char CharacterName[], int WhichCharPalette, int WhichPalettePosition){

char FileDir[NormalFileDirSize];
sprintf(FileDir, "%s/%.8s/%d.pal", FileSystemUsed, CharacterName, WhichCharPalette);

return(FileDirToPalette(FileDir, WhichPalettePosition));
}