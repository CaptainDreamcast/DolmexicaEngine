int NewCharStatsLoad(char CharacterName[], int CharacterTextureSizeDrawn, int* CharOffset, int* CharWidth, int* CharHeight, int* CharSpeed, uint16* JumpIdleUpStrength, int* CharDefense, char RealCharName[], char* JumpIdleUpFlags, char* JumpForwardFlags, char* JumpBackFlags, uint8* BackBlocking, uint8* PaletteInUse, uint16* JumpForwardSpeed, uint16* JumpForwardStrength, uint16* JumpBackSpeed, uint16* JumpBackStrength)
{
//printf("Loading Stats!\n");

CharacterBaseValuesStruct ValueBuffer;
//printf("Size of CharStatsLoadStruct: %ld", sizeof(CharacterBaseValuesStruct));

file_t CharStatsFile;
long OriginalOffset = 0;
char STAFile[NormalFileDirSize];
float StretchFactor;

sprintf(STAFile, "%s/%.8s/%.8s.sta", FileSystemUsed, CharacterName, CharacterName);


CharStatsFile = FileOpen(STAFile, O_RDONLY);

FileSeek(CharStatsFile, OriginalOffset, 0);
FileRead(CharStatsFile, &ValueBuffer, sizeof(CharacterBaseValuesStruct));

FileClose(CharStatsFile);

StretchFactor = (CharacterTextureSizeDrawn*1.0)/ValueBuffer.OriginalTextureSize;

*CharOffset = StretchFactor * ValueBuffer.CharacterOffset;

*CharWidth = StretchFactor * ValueBuffer.CharacterWidth;

*CharHeight = StretchFactor * ValueBuffer.CharacterHeight;

*CharSpeed = StretchFactor * ValueBuffer.CharacterSpeed;
if(*CharSpeed == 0) *CharSpeed = 1;

*JumpForwardSpeed = StretchFactor * ValueBuffer.JumpForwardSpeed;
if(*JumpForwardSpeed == 0) *JumpForwardSpeed = 1;

*JumpBackSpeed = StretchFactor * ValueBuffer.JumpBackSpeed;
if(*JumpBackSpeed == 0) *JumpBackSpeed = 1;

*JumpIdleUpStrength = StretchFactor * ValueBuffer.JumpIdleUpStrength;
if(*JumpIdleUpStrength == 0) *JumpIdleUpStrength = 1;

*JumpForwardStrength = StretchFactor * ValueBuffer.JumpForwardStrength;
if(*JumpForwardStrength == 0) *JumpForwardStrength = 1;

*JumpBackStrength = StretchFactor * ValueBuffer.JumpBackStrength;
if(*JumpBackStrength == 0) *JumpBackStrength = 1;

*CharDefense = ValueBuffer.CharacterDefense;

*JumpIdleUpFlags = ValueBuffer.JumpIdleUpFlags;

*JumpForwardFlags = ValueBuffer.JumpForwardFlags;
*JumpBackFlags = ValueBuffer.JumpBackFlags;

*BackBlocking = ValueBuffer.BackBlocking;

*PaletteInUse = ValueBuffer.PaletteInUse;

sprintf(RealCharName, "%.16s", ValueBuffer.RealCharName);


return(1);
}