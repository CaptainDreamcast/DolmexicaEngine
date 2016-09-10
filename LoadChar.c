void LoadCharRomDisk(char CharacterName[], uint8 CharsAreIdentical, int CurrentChar)
{
file_t RomDiskFile;

uint8* RomDiskBufferPKG;
uint8* RomDiskBufferCRA;

long RomDiskSize;

char RomDiskDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];

sprintf(RomDiskDir, "%s/%.8s/%.8s_PKG.img", FileSystemUsed, CharacterName, CharacterName);
if(!CharsAreIdentical) sprintf(MountPoint, "/%.8s_PKG", CharacterName);
else sprintf(MountPoint, "/%.7s%d_PKG", CharacterName, CurrentChar);

RomDiskFile = FileOpen(RomDiskDir, O_RDONLY);

RomDiskSize = FileTotal(RomDiskFile);

RomDiskBufferPKG = (uint8 *)malloc(RomDiskSize);

FileRead(RomDiskFile, RomDiskBufferPKG, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBufferPKG, 1);

FileClose(RomDiskFile);


sprintf(RomDiskDir, "%s/%.8s/%.8s_CRA.img", FileSystemUsed, CharacterName, CharacterName);
if(!CharsAreIdentical) sprintf(MountPoint, "/%.8s_CRA", CharacterName);
else sprintf(MountPoint, "/%.7s%d_CRA", CharacterName, CurrentChar);

RomDiskFile = FileOpen(RomDiskDir, O_RDONLY);

RomDiskSize = FileTotal(RomDiskFile);

RomDiskBufferCRA = (uint8 *)malloc(RomDiskSize);

FileRead(RomDiskFile, RomDiskBufferCRA, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBufferCRA, 1);

FileClose(RomDiskFile);
}

void LoadCharRegister(char CharacterName[], char CharIsHuman, uint8 CharsAreIdentical, int CurrentChar){

char RegisterDir[NormalFileDirSize];
char RamDir[NormalFileDirSize];

#ifndef LUA_VERSION_NONE
int Bluff;

sprintf(RegisterDir, "%s/%.8s/%.8s_AI.lua", FileSystemUsed, CharacterName, CharacterName);
if(!CharIsHuman && FileExists(RegisterDir)){
sprintf(RamDir, "/ram/%d.lua", CurrentChar);
FileCopyToOtherFileSystem(RegisterDir, RamDir);

Bluff = luaL_dofile(LuaState, RamDir);
if(Bluff == LUA_ERRMEM) printf("lua: memory allocation error\n");
else if (Bluff == LUA_ERRERR) printf("lua: error in error message\n");
FileUnlink(RamDir);

lua_getglobal(LuaState, "ArtificialIntelligence");
sprintf(RegisterDir, "%d_Intelligence", CurrentChar);
lua_setglobal (LuaState, RegisterDir);
lua_pushnil(LuaState);
lua_setglobal(LuaState, "ArtificialIntelligence");

}
#endif

if(CharIsHuman == 1) sprintf(RegisterDir, "%s/%.8s/%.8s_HUMAN.mvt", FileSystemUsed, CharacterName, CharacterName);
else sprintf(RegisterDir, "%s/%.8s/%.8s_CPU.mvt", FileSystemUsed, CharacterName, CharacterName);

if(!CharsAreIdentical) sprintf(RamDir, "/ram/%.8s.mvt", CharacterName);
else sprintf(RamDir, "/ram/%.7s%d.mvt", CharacterName, CurrentChar);

FileCopyToOtherFileSystem(RegisterDir, RamDir);
}

void PrepareCharRegisterHuman(char CharacterName[], int CharacterTextureSizeDrawn, uint8 CharsAreIdentical, int CurrentChar){

file_t RegisterFile;

NormalAttackStruct NormalAttackBuffer;

ThrowHeaderStruct ThrowHeaderBuffer;
ThrowAttackStruct ThrowAttackBuffer;

CoolerAttackHeaderStruct CoolerAttackHeaderBuffer;
CoolerAttackStruct CoolerAttackBuffer;

SpecialEffectHeaderStruct SpecialEffectHeaderBuffer;
//SpecialEffectStruct SpecialEffectBuffer;

ComboAttackStruct ComboAttackBuffer;

OmniHeaderStruct OmniHeaderBuffer;
OmniAttackStruct OmniAttackBuffer;

char FileDir[NormalFileDirSize];
long CurrentOffset;
int DirtyDeedsDoneDirtCheap; 
uint16 OriginalTextureSize;
long NormalAttackOffset;
double StretchFactor;
uint8 AttackAmount;



if(!CharsAreIdentical) sprintf(FileDir, "/ram/%.8s.mvt", CharacterName);
else sprintf(FileDir, "/ram/%.7s%d.mvt", CharacterName, CurrentChar);

RegisterFile = FileOpen(FileDir, O_RDWR);

CurrentOffset = OriginalTextureSizePositionHuman;
FileSeek(RegisterFile, CurrentOffset, 0);
FileRead(RegisterFile, &OriginalTextureSize, 2);

StretchFactor = (CharacterTextureSizeDrawn*1.0)/OriginalTextureSize;

// NORMAL ATTACK START

NormalAttackOffset = 0;
CurrentOffset = NormalAttackOffsetPositionHuman;
FileSeek(RegisterFile, CurrentOffset, 0);
FileRead(RegisterFile, &NormalAttackOffset, HeaderOffsetSize);
CurrentOffset = NormalAttackOffset;

AttackAmount = ((ButtonAmountValue*AttackVariationValue)+1)*PositionAmountValue;

DirtyDeedsDoneDirtCheap = 1;

while(DirtyDeedsDoneDirtCheap <= AttackAmount){

FileSeek(RegisterFile, CurrentOffset, 0);
FileRead(RegisterFile, &NormalAttackBuffer, sizeof(NormalAttackStruct));

if(NormalAttackBuffer.AvailabilityCheck == 1){
NormalAttackBuffer.EnemyAccelerationX *= StretchFactor;
NormalAttackBuffer.EnemyAccelerationY *= StretchFactor;
NormalAttackBuffer.RangeX *= StretchFactor;
NormalAttackBuffer.RangeY *= StretchFactor;
FileSeek(RegisterFile, CurrentOffset, 0);
FileWrite(RegisterFile, &NormalAttackBuffer, sizeof(NormalAttackStruct));
}

CurrentOffset+= sizeof(NormalAttackStruct);
DirtyDeedsDoneDirtCheap++;
}
// NORMAL ATTACK END

// THROW ATTACK START

NormalAttackOffset = 0;
CurrentOffset = ThrowAttackOffsetPositionHuman;
FileSeek(RegisterFile, CurrentOffset, 0);
FileRead(RegisterFile, &NormalAttackOffset, HeaderOffsetSize);

if(NormalAttackOffset != 0){
CurrentOffset = NormalAttackOffset;

FileSeek(RegisterFile, CurrentOffset+1, 0);
FileRead(RegisterFile, &AttackAmount, 1);

CurrentOffset += SpecialAttackHeaderSize;

DirtyDeedsDoneDirtCheap = 1;

while(DirtyDeedsDoneDirtCheap <= AttackAmount){

FileSeek(RegisterFile, CurrentOffset, 0);
FileRead(RegisterFile, &ThrowHeaderBuffer, sizeof(ThrowHeaderStruct));

while(ThrowHeaderBuffer.FrameAmount > 0){

FileSeek(RegisterFile, ThrowHeaderBuffer.SpecialOffset, 0);
FileRead(RegisterFile, &ThrowAttackBuffer, sizeof(ThrowAttackStruct));

ThrowAttackBuffer.CharPositionChangeX *= StretchFactor;
ThrowAttackBuffer.CharPositionChangeY *= StretchFactor;
ThrowAttackBuffer.EnemyPositionChangeX *= StretchFactor;
ThrowAttackBuffer.EnemyPositionChangeY *= StretchFactor;
ThrowAttackBuffer.EnemyAccelerationX *= StretchFactor;
ThrowAttackBuffer.EnemyAccelerationY *= StretchFactor;

FileSeek(RegisterFile, ThrowHeaderBuffer.SpecialOffset, 0);
FileWrite(RegisterFile, &ThrowAttackBuffer, sizeof(ThrowAttackStruct));

ThrowHeaderBuffer.SpecialOffset += sizeof(ThrowAttackStruct);
ThrowHeaderBuffer.FrameAmount--;
}

CurrentOffset += sizeof(ThrowHeaderStruct);
DirtyDeedsDoneDirtCheap++;
}
}

//THROW ATTACK END

// COOLER ATTACK START

NormalAttackOffset = 0;
CurrentOffset = CoolerAttackOffsetPositionHuman;
FileSeek(RegisterFile, CurrentOffset, 0);
FileRead(RegisterFile, &NormalAttackOffset, HeaderOffsetSize);

if(NormalAttackOffset != 0){
CurrentOffset = NormalAttackOffset;

FileSeek(RegisterFile, CurrentOffset+1, 0);
FileRead(RegisterFile, &AttackAmount, 1);


CurrentOffset += SpecialAttackHeaderSize;

DirtyDeedsDoneDirtCheap = 1;

while(DirtyDeedsDoneDirtCheap <= AttackAmount){

FileSeek(RegisterFile, CurrentOffset, 0);
FileRead(RegisterFile, &CoolerAttackHeaderBuffer, sizeof(CoolerAttackHeaderStruct));

while(CoolerAttackHeaderBuffer.FrameAmount > 0){

FileSeek(RegisterFile, CoolerAttackHeaderBuffer.SpecialOffset, 0);
FileRead(RegisterFile, &CoolerAttackBuffer, sizeof(CoolerAttackStruct));

CoolerAttackBuffer.CharPositionChangeX *= StretchFactor;
CoolerAttackBuffer.CharPositionChangeY *= StretchFactor;
CoolerAttackBuffer.CharComboMovementX *= StretchFactor;
CoolerAttackBuffer.CharComboMovementY *= StretchFactor;
CoolerAttackBuffer.EnemyAccelerationX *= StretchFactor;
CoolerAttackBuffer.EnemyAccelerationY *= StretchFactor;

FileSeek(RegisterFile, CoolerAttackHeaderBuffer.SpecialOffset, 0);
FileWrite(RegisterFile, &CoolerAttackBuffer, sizeof(CoolerAttackStruct));

CoolerAttackHeaderBuffer.SpecialOffset += sizeof(CoolerAttackStruct);
CoolerAttackHeaderBuffer.FrameAmount--;
}

CurrentOffset += sizeof(CoolerAttackHeaderStruct);
DirtyDeedsDoneDirtCheap++;
}
}

//COOLER ATTACK END

// SPECIAL EFFECT START

NormalAttackOffset = 0;
CurrentOffset = SpecialEffectOffsetPositionHuman;
FileSeek(RegisterFile, CurrentOffset, 0);
FileRead(RegisterFile, &NormalAttackOffset, HeaderOffsetSize);

if(NormalAttackOffset != 0){
CurrentOffset = NormalAttackOffset;


FileSeek(RegisterFile, CurrentOffset+1, 0);
FileRead(RegisterFile, &AttackAmount, 1);




CurrentOffset += SpecialAttackHeaderSize;

DirtyDeedsDoneDirtCheap = 1;

while(DirtyDeedsDoneDirtCheap <= AttackAmount){


FileSeek(RegisterFile, CurrentOffset, 0);
FileRead(RegisterFile, &SpecialEffectHeaderBuffer, sizeof(SpecialEffectHeaderStruct));

if(SpecialEffectHeaderBuffer.SpecialEffectPosCharRelativity == 1){
SpecialEffectHeaderBuffer.SpecialEffectSizeX *= StretchFactor;
SpecialEffectHeaderBuffer.SpecialEffectSizeY *= StretchFactor;
SpecialEffectHeaderBuffer.SpecialEffectPosX *= StretchFactor;
SpecialEffectHeaderBuffer.SpecialEffectPosY *= StretchFactor;
SpecialEffectHeaderBuffer.SpecialEffectRange *= StretchFactor;
SpecialEffectHeaderBuffer.SpecialEffectSpeedX *= StretchFactor;
SpecialEffectHeaderBuffer.SpecialEffectSpeedY *= StretchFactor;
SpecialEffectHeaderBuffer.SpecialEffectCollisionOffsetX *= StretchFactor;
SpecialEffectHeaderBuffer.SpecialEffectCollisionOffsetY *= StretchFactor;

FileSeek(RegisterFile, CurrentOffset, 0);
FileWrite(RegisterFile, &SpecialEffectHeaderBuffer, sizeof(SpecialEffectHeaderStruct));
}

CurrentOffset += sizeof(SpecialEffectHeaderStruct);
DirtyDeedsDoneDirtCheap++;
}
}

//SPECIAL EFFECT END

//COMBO ATTACK START

NormalAttackOffset = 0;
CurrentOffset = ComboAttackOffsetPositionHuman;
FileSeek(RegisterFile, CurrentOffset, 0);
FileRead(RegisterFile, &NormalAttackOffset, HeaderOffsetSize);

if(NormalAttackOffset != 0){
CurrentOffset = NormalAttackOffset;



FileSeek(RegisterFile, CurrentOffset+1, 0);
FileRead(RegisterFile, &AttackAmount, 1);




CurrentOffset += SpecialAttackHeaderSize;

DirtyDeedsDoneDirtCheap = 1;

while(DirtyDeedsDoneDirtCheap <= AttackAmount){


FileSeek(RegisterFile, CurrentOffset, 0);
FileRead(RegisterFile, &ComboAttackBuffer, sizeof(ComboAttackStruct));

ComboAttackBuffer.EnemyAccelerationX *= StretchFactor;
ComboAttackBuffer.EnemyAccelerationY *= StretchFactor;
ComboAttackBuffer.CharPositionChangeX *= StretchFactor;
ComboAttackBuffer.CharPositionChangeY *= StretchFactor;

FileSeek(RegisterFile, CurrentOffset, 0);
FileWrite(RegisterFile, &ComboAttackBuffer, sizeof(ComboAttackStruct));

CurrentOffset += sizeof(ComboAttackStruct);
DirtyDeedsDoneDirtCheap++;
}
}

//COMBO ATTACK END

// OMNI ATTACK START

NormalAttackOffset = 0;
CurrentOffset = OmniAttackOffsetPositionHuman;
FileSeek(RegisterFile, CurrentOffset, 0);
FileRead(RegisterFile, &NormalAttackOffset, HeaderOffsetSize);

if(NormalAttackOffset != 0){
CurrentOffset = NormalAttackOffset;


FileSeek(RegisterFile, CurrentOffset+1, 0);
FileRead(RegisterFile, &AttackAmount, 1);

CurrentOffset += SpecialAttackHeaderSize;

DirtyDeedsDoneDirtCheap = 0;

while(DirtyDeedsDoneDirtCheap < AttackAmount){


FileSeek(RegisterFile, CurrentOffset, 0);
FileRead(RegisterFile, &OmniHeaderBuffer, sizeof(OmniHeaderStruct));

while(OmniHeaderBuffer.ActionAmount > 0){

FileSeek(RegisterFile, OmniHeaderBuffer.SpecialOffset, 0);
FileRead(RegisterFile, &OmniAttackBuffer, sizeof(OmniAttackStruct));



if(OmniAttackBuffer.NewSpecialEffectAnimation != 0){
OmniAttackBuffer.SpecialEffectSizeX *= StretchFactor;
OmniAttackBuffer.SpecialEffectSizeY *= StretchFactor;
if(OmniAttackBuffer.SpecialEffectPosCharRelativity){
OmniAttackBuffer.SpecialEffectPosX *= StretchFactor;
OmniAttackBuffer.SpecialEffectPosY *= StretchFactor;
}
OmniAttackBuffer.SpecialEffectRange *= StretchFactor;
OmniAttackBuffer.SpecialEffectSpeedX *= StretchFactor;
OmniAttackBuffer.SpecialEffectSpeedY *= StretchFactor;
}
OmniAttackBuffer.CharPositionChangeX *= StretchFactor;
OmniAttackBuffer.CharPositionChangeY *= StretchFactor;
OmniAttackBuffer.EnemyPositionChangeX *= StretchFactor;
OmniAttackBuffer.EnemyPositionChangeY *= StretchFactor;
OmniAttackBuffer.CharComboMovementX *= StretchFactor;
OmniAttackBuffer.CharComboMovementY *= StretchFactor;
OmniAttackBuffer.EnemyComboMovementX *= StretchFactor;
OmniAttackBuffer.EnemyComboMovementY *= StretchFactor;

if(OmniAttackBuffer.PosCharRelativity){
OmniAttackBuffer.CharPositionFixedX *= StretchFactor;
OmniAttackBuffer.CharPositionFixedY *= StretchFactor;
}
if(OmniAttackBuffer.PosEnemyRelativity){
OmniAttackBuffer.EnemyPositionFixedX *= StretchFactor;
OmniAttackBuffer.EnemyPositionFixedY *= StretchFactor;
}
OmniAttackBuffer.EnemyAccelerationX *= StretchFactor;
OmniAttackBuffer.EnemyAccelerationY *= StretchFactor;



FileSeek(RegisterFile, OmniHeaderBuffer.SpecialOffset, 0);
FileWrite(RegisterFile, &OmniAttackBuffer, sizeof(OmniAttackStruct));

OmniHeaderBuffer.SpecialOffset += sizeof(OmniAttackStruct);
OmniHeaderBuffer.ActionAmount--;
}

CurrentOffset += sizeof(OmniHeaderStruct);
DirtyDeedsDoneDirtCheap++;
}
}

//OMNI ATTACK END

FileClose(RegisterFile);
}

void PrepareCharRegisterComputer(char CharacterName[], int CharacterTextureSizeDrawn, uint8 CharsAreIdentical, int CurrentChar){

file_t RegisterFile;

NormalAttackStruct NormalAttackBuffer;

char FileDir[NormalFileDirSize];
long CurrentOffset;
int DirtyDeedsDoneDirtCheap; 
uint16 OriginalTextureSize;
//long NormalAttackOffset;
double StretchFactor;
uint8 AttackAmount;




if(!CharsAreIdentical) sprintf(FileDir, "/ram/%.8s.mvt", CharacterName);
else sprintf(FileDir, "/ram/%.7s%d.mvt", CharacterName, CurrentChar);

RegisterFile = FileOpen(FileDir, O_RDWR);

CurrentOffset = OriginalTextureSizePositionComputer;
FileSeek(RegisterFile, CurrentOffset, 0);
FileRead(RegisterFile, &OriginalTextureSize, 2);

StretchFactor = (CharacterTextureSizeDrawn*1.0)/OriginalTextureSize;

// NORMAL ATTACK START

AttackAmount = 0;
CurrentOffset = AttackAmountPositionComputer;
FileSeek(RegisterFile, CurrentOffset, 0);
FileRead(RegisterFile, &AttackAmount, 1);

CurrentOffset = HeaderSizeComputerMVT;

DirtyDeedsDoneDirtCheap = 0;

while(DirtyDeedsDoneDirtCheap < AttackAmount){

FileSeek(RegisterFile, CurrentOffset, 0);
FileRead(RegisterFile, &NormalAttackBuffer, sizeof(NormalAttackStruct));

if(NormalAttackBuffer.AvailabilityCheck == 1){
NormalAttackBuffer.EnemyAccelerationX *= StretchFactor;
NormalAttackBuffer.EnemyAccelerationY *= StretchFactor;
NormalAttackBuffer.RangeX *= StretchFactor;
NormalAttackBuffer.RangeY *= StretchFactor;
FileSeek(RegisterFile, CurrentOffset, 0);
FileWrite(RegisterFile, &NormalAttackBuffer, sizeof(NormalAttackStruct));
}

CurrentOffset+= sizeof(NormalAttackStruct);
DirtyDeedsDoneDirtCheap++;
}
// NORMAL ATTACK END

FileClose(RegisterFile);
}

void DeLoadCharRomDisk(char CharacterName[], uint8 CharsAreIdentical, int CurrentChar)
{


char MountPoint[NormalMountPointSize];

#ifndef LUA_VERSION_NONE
sprintf(MountPoint, "%d_Intelligence", CurrentChar);
lua_pushnil(LuaState);
lua_setglobal(LuaState, MountPoint);
#endif

if(!CharsAreIdentical) sprintf(MountPoint, "/%.8s_PKG", CharacterName);
else sprintf(MountPoint, "/%.7s%d_PKG", CharacterName, CurrentChar);

fs_romdisk_unmount(MountPoint);

if(!CharsAreIdentical) sprintf(MountPoint, "/%.8s_CRA", CharacterName);
else sprintf(MountPoint, "/%.7s%d_CRA", CharacterName, CurrentChar);

fs_romdisk_unmount(MountPoint);

if(!CharsAreIdentical) sprintf(MountPoint, "/ram/%.8s.mvt", CharacterName);
else sprintf(MountPoint, "/ram/%.7s%d.mvt", CharacterName, CurrentChar);

FileUnlink(MountPoint);
}
