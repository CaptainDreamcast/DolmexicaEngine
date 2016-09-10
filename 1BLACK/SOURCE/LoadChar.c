void LoadCharRomDisk(char CharacterName[], uint8 CharsAreIdentical, int CurrentChar)
{
file_t RomDiskFile;

uint8* RomDiskBufferPKG;
uint8* RomDiskBufferCRA;

int Bluff;

long RomDiskSize;

char RomDiskDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];

Bluff = sprintf(RomDiskDir, "%s/%.8s/%.8s_PKG.img", FileSystemUsed, CharacterName, CharacterName);
if(!CharsAreIdentical) sprintf(MountPoint, "/%.8s_PKG", CharacterName);
else sprintf(MountPoint, "/%.7s%d_PKG", CharacterName, CurrentChar);

RomDiskFile = fs_open(RomDiskDir, O_RDONLY);

RomDiskSize = fs_total(RomDiskFile);

RomDiskBufferPKG = (uint8 *)malloc(RomDiskSize);

fs_read(RomDiskFile, RomDiskBufferPKG, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBufferPKG, 1);

fs_close(RomDiskFile);


Bluff = sprintf(RomDiskDir, "%s/%.8s/%.8s_CRA.img", FileSystemUsed, CharacterName, CharacterName);
if(!CharsAreIdentical) sprintf(MountPoint, "/%.8s_CRA", CharacterName);
else sprintf(MountPoint, "/%.7s%d_CRA", CharacterName, CurrentChar);

RomDiskFile = fs_open(RomDiskDir, O_RDONLY);

RomDiskSize = fs_total(RomDiskFile);

RomDiskBufferCRA = (uint8 *)malloc(RomDiskSize);

fs_read(RomDiskFile, RomDiskBufferCRA, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBufferCRA, 1);

fs_close(RomDiskFile);
}

void LoadCharRegister(char CharacterName[], char CharIsHuman, uint8 CharsAreIdentical, int CurrentChar){

char RegisterDir[NormalFileDirSize];
char RamDir[NormalFileDirSize];

int Bluff;

if(CharIsHuman == 1) Bluff = sprintf(RegisterDir, "%s/%.8s/%.8s_HUMAN.mvt", FileSystemUsed, CharacterName, CharacterName);
else Bluff = sprintf(RegisterDir, "%s/%.8s/%.8s_CPU.mvt", FileSystemUsed, CharacterName, CharacterName);

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

RegisterFile = fs_open(FileDir, O_RDWR);

CurrentOffset = OriginalTextureSizePositionHuman;
fs_seek(RegisterFile, CurrentOffset, 0);
fs_read(RegisterFile, &OriginalTextureSize, 2);

StretchFactor = (CharacterTextureSizeDrawn*1.0)/OriginalTextureSize;

// NORMAL ATTACK START

NormalAttackOffset = 0;
CurrentOffset = NormalAttackOffsetPositionHuman;
fs_seek(RegisterFile, CurrentOffset, 0);
fs_read(RegisterFile, &NormalAttackOffset, HeaderOffsetSize);
CurrentOffset = NormalAttackOffset;

AttackAmount = ((ButtonAmountValue*AttackVariationValue)+1)*PositionAmountValue;

DirtyDeedsDoneDirtCheap = 1;

while(DirtyDeedsDoneDirtCheap <= AttackAmount){

fs_seek(RegisterFile, CurrentOffset, 0);
fs_read(RegisterFile, &NormalAttackBuffer, sizeof(NormalAttackStruct));

if(NormalAttackBuffer.AvailabilityCheck == 1){
NormalAttackBuffer.EnemyAccelerationX *= StretchFactor;
NormalAttackBuffer.EnemyAccelerationY *= StretchFactor;
NormalAttackBuffer.RangeX *= StretchFactor;
NormalAttackBuffer.RangeY *= StretchFactor;
fs_seek(RegisterFile, CurrentOffset, 0);
fs_write(RegisterFile, &NormalAttackBuffer, sizeof(NormalAttackStruct));
}

CurrentOffset+= sizeof(NormalAttackStruct);
DirtyDeedsDoneDirtCheap++;
}
// NORMAL ATTACK END

// THROW ATTACK START

NormalAttackOffset = 0;
CurrentOffset = ThrowAttackOffsetPositionHuman;
fs_seek(RegisterFile, CurrentOffset, 0);
fs_read(RegisterFile, &NormalAttackOffset, HeaderOffsetSize);

if(NormalAttackOffset != 0){
CurrentOffset = NormalAttackOffset;

fs_seek(RegisterFile, CurrentOffset+1, 0);
fs_read(RegisterFile, &AttackAmount, 1);

CurrentOffset += SpecialAttackHeaderSize;

DirtyDeedsDoneDirtCheap = 1;

while(DirtyDeedsDoneDirtCheap <= AttackAmount){

fs_seek(RegisterFile, CurrentOffset, 0);
fs_read(RegisterFile, &ThrowHeaderBuffer, sizeof(ThrowHeaderStruct));

while(ThrowHeaderBuffer.FrameAmount > 0){

fs_seek(RegisterFile, ThrowHeaderBuffer.SpecialOffset, 0);
fs_read(RegisterFile, &ThrowAttackBuffer, sizeof(ThrowAttackStruct));

ThrowAttackBuffer.CharPositionChangeX *= StretchFactor;
ThrowAttackBuffer.CharPositionChangeY *= StretchFactor;
ThrowAttackBuffer.EnemyPositionChangeX *= StretchFactor;
ThrowAttackBuffer.EnemyPositionChangeY *= StretchFactor;
ThrowAttackBuffer.EnemyAccelerationX *= StretchFactor;
ThrowAttackBuffer.EnemyAccelerationY *= StretchFactor;

fs_seek(RegisterFile, ThrowHeaderBuffer.SpecialOffset, 0);
fs_write(RegisterFile, &ThrowAttackBuffer, sizeof(ThrowAttackStruct));

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
fs_seek(RegisterFile, CurrentOffset, 0);
fs_read(RegisterFile, &NormalAttackOffset, HeaderOffsetSize);

if(NormalAttackOffset != 0){
CurrentOffset = NormalAttackOffset;

fs_seek(RegisterFile, CurrentOffset+1, 0);
fs_read(RegisterFile, &AttackAmount, 1);


CurrentOffset += SpecialAttackHeaderSize;

DirtyDeedsDoneDirtCheap = 1;

while(DirtyDeedsDoneDirtCheap <= AttackAmount){

fs_seek(RegisterFile, CurrentOffset, 0);
fs_read(RegisterFile, &CoolerAttackHeaderBuffer, sizeof(CoolerAttackHeaderStruct));

while(CoolerAttackHeaderBuffer.FrameAmount > 0){

fs_seek(RegisterFile, CoolerAttackHeaderBuffer.SpecialOffset, 0);
fs_read(RegisterFile, &CoolerAttackBuffer, sizeof(CoolerAttackStruct));

CoolerAttackBuffer.CharPositionChangeX *= StretchFactor;
CoolerAttackBuffer.CharPositionChangeY *= StretchFactor;
CoolerAttackBuffer.CharComboMovementX *= StretchFactor;
CoolerAttackBuffer.CharComboMovementY *= StretchFactor;
CoolerAttackBuffer.EnemyAccelerationX *= StretchFactor;
CoolerAttackBuffer.EnemyAccelerationY *= StretchFactor;

fs_seek(RegisterFile, CoolerAttackHeaderBuffer.SpecialOffset, 0);
fs_write(RegisterFile, &CoolerAttackBuffer, sizeof(CoolerAttackStruct));

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
fs_seek(RegisterFile, CurrentOffset, 0);
fs_read(RegisterFile, &NormalAttackOffset, HeaderOffsetSize);

if(NormalAttackOffset != 0){
CurrentOffset = NormalAttackOffset;


fs_seek(RegisterFile, CurrentOffset+1, 0);
fs_read(RegisterFile, &AttackAmount, 1);




CurrentOffset += SpecialAttackHeaderSize;

DirtyDeedsDoneDirtCheap = 1;

while(DirtyDeedsDoneDirtCheap <= AttackAmount){


fs_seek(RegisterFile, CurrentOffset, 0);
fs_read(RegisterFile, &SpecialEffectHeaderBuffer, sizeof(SpecialEffectHeaderStruct));

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

fs_seek(RegisterFile, CurrentOffset, 0);
fs_write(RegisterFile, &SpecialEffectHeaderBuffer, sizeof(SpecialEffectHeaderStruct));
}

CurrentOffset += sizeof(SpecialEffectHeaderStruct);
DirtyDeedsDoneDirtCheap++;
}
}

//SPECIAL EFFECT END

//COMBO ATTACK START

NormalAttackOffset = 0;
CurrentOffset = ComboAttackOffsetPositionHuman;
fs_seek(RegisterFile, CurrentOffset, 0);
fs_read(RegisterFile, &NormalAttackOffset, HeaderOffsetSize);

if(NormalAttackOffset != 0){
CurrentOffset = NormalAttackOffset;



fs_seek(RegisterFile, CurrentOffset+1, 0);
fs_read(RegisterFile, &AttackAmount, 1);




CurrentOffset += SpecialAttackHeaderSize;

DirtyDeedsDoneDirtCheap = 1;

while(DirtyDeedsDoneDirtCheap <= AttackAmount){


fs_seek(RegisterFile, CurrentOffset, 0);
fs_read(RegisterFile, &ComboAttackBuffer, sizeof(ComboAttackStruct));

ComboAttackBuffer.EnemyAccelerationX *= StretchFactor;
ComboAttackBuffer.EnemyAccelerationY *= StretchFactor;
ComboAttackBuffer.CharPositionChangeX *= StretchFactor;
ComboAttackBuffer.CharPositionChangeY *= StretchFactor;

fs_seek(RegisterFile, CurrentOffset, 0);
fs_write(RegisterFile, &ComboAttackBuffer, sizeof(ComboAttackStruct));

CurrentOffset += sizeof(ComboAttackStruct);
DirtyDeedsDoneDirtCheap++;
}
}

//COMBO ATTACK END

// OMNI ATTACK START

NormalAttackOffset = 0;
CurrentOffset = OmniAttackOffsetPositionHuman;
fs_seek(RegisterFile, CurrentOffset, 0);
fs_read(RegisterFile, &NormalAttackOffset, HeaderOffsetSize);

if(NormalAttackOffset != 0){
CurrentOffset = NormalAttackOffset;


fs_seek(RegisterFile, CurrentOffset+1, 0);
fs_read(RegisterFile, &AttackAmount, 1);

CurrentOffset += SpecialAttackHeaderSize;

DirtyDeedsDoneDirtCheap = 0;

while(DirtyDeedsDoneDirtCheap < AttackAmount){


fs_seek(RegisterFile, CurrentOffset, 0);
fs_read(RegisterFile, &OmniHeaderBuffer, sizeof(OmniHeaderStruct));

while(OmniHeaderBuffer.ActionAmount > 0){

fs_seek(RegisterFile, OmniHeaderBuffer.SpecialOffset, 0);
fs_read(RegisterFile, &OmniAttackBuffer, sizeof(OmniAttackStruct));



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



fs_seek(RegisterFile, OmniHeaderBuffer.SpecialOffset, 0);
fs_write(RegisterFile, &OmniAttackBuffer, sizeof(OmniAttackStruct));

OmniHeaderBuffer.SpecialOffset += sizeof(OmniAttackStruct);
OmniHeaderBuffer.ActionAmount--;
}

CurrentOffset += sizeof(OmniHeaderStruct);
DirtyDeedsDoneDirtCheap++;
}
}

//OMNI ATTACK END

fs_close(RegisterFile);
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

RegisterFile = fs_open(FileDir, O_RDWR);

CurrentOffset = OriginalTextureSizePositionComputer;
fs_seek(RegisterFile, CurrentOffset, 0);
fs_read(RegisterFile, &OriginalTextureSize, 2);

StretchFactor = (CharacterTextureSizeDrawn*1.0)/OriginalTextureSize;

// NORMAL ATTACK START

AttackAmount = 0;
CurrentOffset = AttackAmountPositionComputer;
fs_seek(RegisterFile, CurrentOffset, 0);
fs_read(RegisterFile, &AttackAmount, 1);

CurrentOffset = HeaderSizeComputerMVT;

DirtyDeedsDoneDirtCheap = 0;

while(DirtyDeedsDoneDirtCheap < AttackAmount){

fs_seek(RegisterFile, CurrentOffset, 0);
fs_read(RegisterFile, &NormalAttackBuffer, sizeof(NormalAttackStruct));

if(NormalAttackBuffer.AvailabilityCheck == 1){
NormalAttackBuffer.EnemyAccelerationX *= StretchFactor;
NormalAttackBuffer.EnemyAccelerationY *= StretchFactor;
NormalAttackBuffer.RangeX *= StretchFactor;
NormalAttackBuffer.RangeY *= StretchFactor;
fs_seek(RegisterFile, CurrentOffset, 0);
fs_write(RegisterFile, &NormalAttackBuffer, sizeof(NormalAttackStruct));
}

CurrentOffset+= sizeof(NormalAttackStruct);
DirtyDeedsDoneDirtCheap++;
}
// NORMAL ATTACK END

fs_close(RegisterFile);
}

void DeLoadCharRomDisk(char CharacterName[], uint8 CharsAreIdentical, int CurrentChar)
{


char MountPoint[NormalMountPointSize];

if(!CharsAreIdentical) sprintf(MountPoint, "/%.8s_PKG", CharacterName);
else sprintf(MountPoint, "/%.7s%d_PKG", CharacterName, CurrentChar);

fs_romdisk_unmount(MountPoint);

if(!CharsAreIdentical) sprintf(MountPoint, "/%.8s_CRA", CharacterName);
else sprintf(MountPoint, "/%.7s%d_CRA", CharacterName, CurrentChar);

fs_romdisk_unmount(MountPoint);

if(!CharsAreIdentical) sprintf(MountPoint, "/ram/%.8s.mvt", CharacterName);
else sprintf(MountPoint, "/ram/%.7s%d.mvt", CharacterName, CurrentChar);

fs_unlink(MountPoint);
}
