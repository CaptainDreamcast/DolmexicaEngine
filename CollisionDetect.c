// Idea: When performing a special attack, only check the Fireball's attack layer.

void CollisionDetect(char CharacterName1[], char AnimationName1[], int FrameID1, char CharacterName2[], char AnimationName2[], int FrameID2, int RealDrawCharX1, int RealDrawCharX2, int PosCharY1, int PosCharY2, char CharIsLeft1, char CharIsLeft2, char* CharHitStatus1, char* CharHitStatus2, int* HitPositionX1, int* HitPositionY1, int* HitPositionX2, int* HitPositionY2, int CharacterStretchFactor, int CharacterTextureSize, int SpecialEffectStage1, int SpecialEffectSizeX1, int SpecialEffectSizeY1, int SpecialEffectDrawX1, int SpecialEffectDrawY1, int SpecialEffectWhichFrame1, char SpecialEffectNameBuffer1[])
{

file_t TemporaryCLAFile1;
file_t TemporaryCLAFile2;
file_t TemporaryCLAFile3;

int DrawCharX1 = RealDrawCharX1;
int DrawCharX2 = RealDrawCharX2;
char FileDir1[30];
char FileDir2[30];
char EffectFileDir1[30];
int Bluff1;
int Bluff2;
Bluff1 = sprintf(FileDir1, "/%.8s_CRA/%.8s%d.cra", CharacterName1, AnimationName1, FrameID1);
Bluff2 = sprintf(FileDir2, "/%.8s_CRA/%.8s%d.cra", CharacterName2, AnimationName2, FrameID2);
int StartOffset1 = 0;
int StartOffset2 = 0;
long CurrentOffset1 = 0;
long CurrentOffset2 = 0;
long MoveOffset1 = 0;
long MoveOffset2 = 0;

unsigned long long ExistenceDetection1 = 0;
unsigned long long AttackDetection1 = 0;
unsigned long long BlockDetection1 = 0;
unsigned long long HitString1 = 0;
unsigned long long ExistenceDetection2 = 0;
unsigned long long AttackDetection2 = 0;
unsigned long long BlockDetection2 = 0;
unsigned long long HitString2 = 0;
//int HitPositionCheckerX1 = 0;
//int HitPositionCheckerX2 = 0;
unsigned int c;

CrashLayerDecompress(FileDir1, "/ram/Temporary1.cla");
TemporaryCLAFile1 = fs_open("/ram/Temporary1.cla", O_RDONLY);

CrashLayerDecompress(FileDir2, "/ram/Temporary2.cla");
TemporaryCLAFile2 = fs_open("/ram/Temporary2.cla", O_RDONLY);

//printf("%c\n", data1[(55*128+67)-1]); //ASCII 1=49 etc...
//int HitDetected1 = 0;
//int HitDetected2 = 0;
//int CheckPositionRightX = 2;
int CheckPositionY1;
int CheckPositionY2;
//int CheckPositionLeftX;
int CheckLengthY;
int CheckPositionX1 = 0;
//int CheckPositionX2;
int CheckLengthX;
//int PositionCheckerY = 0;
int CheckDifference;

if(PosCharY1 < PosCharY2){
CheckPositionY1 = (PosCharY2-PosCharY1)/CharacterStretchFactor;
CheckPositionY2 = 0;
CheckLengthY = (PosCharY1+CharacterTextureSize-PosCharY2)/CharacterStretchFactor;
}
else{
CheckPositionY1 = 0;
CheckPositionY2 = (PosCharY1-PosCharY2)/CharacterStretchFactor;
CheckLengthY = (PosCharY2+CharacterTextureSize-PosCharY1)/CharacterStretchFactor;
}

if(CharIsLeft1 == 1){
StartOffset1 = 0;
}
else{
StartOffset1 = 1536;
}

if(CharIsLeft2 == 1){
StartOffset2 = 0;
}
else{
StartOffset2 = 1536;
}

int DataOffset1 = CheckPositionY1*3*8;
int DataOffset2 = CheckPositionY2*3*8;
MoveOffset1 = StartOffset1+DataOffset1;
MoveOffset2 = StartOffset2+DataOffset2;




if(DrawCharX1 >= DrawCharX2){
CheckDifference = (DrawCharX1-DrawCharX2)/CharacterStretchFactor;
if(CheckDifference > SizeOfLongLong) CheckLengthY = -1;

CheckLengthX = (DrawCharX2+CharacterTextureSize-DrawCharX1)/CharacterStretchFactor;
//printf("X-Axis Difference %d\n", CheckDifference);

while(CheckLengthY >= 0){
//printf("AttackString Before: %llu! \n", AttackDetection1);
//printf("DetectionString Before: %llu! \n", ExistenceDetection2);

ExistenceDetection1 = 0;
AttackDetection1 = 0;
//BlockDetection1 = 0;
ExistenceDetection2 = 0;
AttackDetection2 = 0;
//BlockDetection2 = 0;

CurrentOffset1 = fs_seek(TemporaryCLAFile1, MoveOffset1, 0);
//printf("Offset1: %ld!\n", CurrentOffset1);
fs_read(TemporaryCLAFile1, &ExistenceDetection1, 8);
CurrentOffset1 = fs_seek(TemporaryCLAFile1, MoveOffset1+8, 0);
fs_read(TemporaryCLAFile1, &AttackDetection1, 8);

MoveOffset1+=24;

CurrentOffset2 = fs_seek(TemporaryCLAFile2, MoveOffset2, 0);
//printf("Offset2: %ld!\n", CurrentOffset2);
fs_read(TemporaryCLAFile2, &ExistenceDetection2, 8);
CurrentOffset2 = fs_seek(TemporaryCLAFile2, MoveOffset2+8, 0);
fs_read(TemporaryCLAFile2, &AttackDetection2, 8);
//CurrentOffset2 = fs_seek(TemporaryCLAFile2, MoveOffset2+16, 0);
//fs_read(TemporaryCLAFile2, &BlockDetection2, 8);
MoveOffset2+=24;

if(((AttackDetection1 >> CheckDifference) & ExistenceDetection2) != 0){
//printf("HIT!\n");
//printf("AttackString: %llu! \n", AttackDetection1);
//printf("DetectionString: %llu! \n", ExistenceDetection2);
//printf("DetectionString shifted: %llu! \n", (ExistenceDetection2 << CheckDifference));
//printf("CheckLength: %d!\n", CheckLengthY);
//printf("X-Axis Difference %d\n", CheckDifference);
*CharHitStatus2 = 3;
CheckLengthY = -1;
HitString2 = ((AttackDetection1 >> CheckDifference) & ExistenceDetection2);
}



if(((ExistenceDetection1 >> CheckDifference) & AttackDetection2) != 0){
*CharHitStatus1 = 3;
CheckLengthY = -1;
HitString1 = ((AttackDetection2 << CheckDifference) & ExistenceDetection1);
}


//CurrentOffset1 = fs_seek(TemporaryCLAFile1, CurrentOffset1+8, 0);
//fs_read(TemporaryCLAFile1, &ExistenceDetection1, 8);



CheckLengthY-=1;
}

}
else{
CheckDifference = (DrawCharX2-DrawCharX1)/CharacterStretchFactor;
if(CheckDifference > SizeOfLongLong) CheckLengthY = -1;

CheckLengthX = (DrawCharX1+CharacterTextureSize-DrawCharX2)/CharacterStretchFactor;
//printf("X-Axis Difference %d\n", CheckDifference);

while(CheckLengthY >= 0){
//printf("AttackString Before: %llu! \n", AttackDetection1);
//printf("DetectionString Before: %llu! \n", ExistenceDetection2);

ExistenceDetection1 = 0;
AttackDetection1 = 0;
//BlockDetection1 = 0;
ExistenceDetection2 = 0;
AttackDetection2 = 0;
//BlockDetection2 = 0;

CurrentOffset1 = fs_seek(TemporaryCLAFile1, MoveOffset1, 0);
//printf("Offset1: %ld!\n", CurrentOffset1);
fs_read(TemporaryCLAFile1, &ExistenceDetection1, 8);
CurrentOffset1 = fs_seek(TemporaryCLAFile1, MoveOffset1+8, 0);
fs_read(TemporaryCLAFile1, &AttackDetection1, 8);
//CurrentOffset1 = fs_seek(TemporaryCLAFile1, MoveOffset1+16, 0);
//fs_read(TemporaryCLAFile1, &BlockDetection1, 8);
MoveOffset1+=24;

CurrentOffset2 = fs_seek(TemporaryCLAFile2, MoveOffset2, 0);
//printf("Offset2: %ld!\n", CurrentOffset2);
fs_read(TemporaryCLAFile2, &ExistenceDetection2, 8);
CurrentOffset2 = fs_seek(TemporaryCLAFile2, MoveOffset2+8, 0);
fs_read(TemporaryCLAFile2, &AttackDetection2, 8);
//CurrentOffset2 = fs_seek(TemporaryCLAFile2, MoveOffset2+16, 0);
//fs_read(TemporaryCLAFile2, &BlockDetection2, 8);
MoveOffset2+=24;

if(((ExistenceDetection2 >> CheckDifference) & AttackDetection1) != 0){
//printf("HIT!\n");
//printf("AttackString: %llu! \n", AttackDetection1);
//printf("DetectionString: %llu! \n", ExistenceDetection2);
//printf("DetectionString shifted: %llu! \n", (ExistenceDetection2 << CheckDifference));
//printf("CheckLength: %d!\n", CheckLengthY);
//printf("X-Axis Difference %d\n", CheckDifference);
*CharHitStatus2 = 3;
CheckLengthY = -1;
HitString2 = ((AttackDetection1 << CheckDifference) & ExistenceDetection2);
}

if(((AttackDetection2 >> CheckDifference) & ExistenceDetection1) != 0){

*CharHitStatus1 = 3;
CheckLengthY = -1;
HitString1 = ((AttackDetection2 >> CheckDifference) & ExistenceDetection1);
}

CheckLengthY-=1;
}
}



if(*CharHitStatus2 == 3){

*HitPositionY2 = PosCharY2+((((MoveOffset2-24)%1536)/(3*8))*CharacterStretchFactor);

 // c will be the number of zero bits on the right

if(HitString2 & 0x1){
 c= 0;
}
else{
 c = 1;
 
if((HitString2 & 0xFFFFFFFF) == 0){
 HitString2 >>= 32;
 c += 32;
}
if((HitString2 & 0xFFFF) == 0){
 HitString2 >>= 16;
 c += 16;
}
if((HitString2 & 0xFF) == 0){
 HitString2 >>= 8;
 c += 8;
}
if((HitString2 & 0xF) == 0){
 HitString2 >>= 4;
 c += 4;
}
if((HitString2 & 0x3) == 0){
 HitString2 >>= 2;
 c += 2;
}
c -= HitString2 & 0x1;
}

//printf("Number of bits on the right: %d.\n", c);

*HitPositionX2 = DrawCharX2+CharacterTextureSize-c*CharacterStretchFactor;

BlockDetection2 = 0;
fs_seek(TemporaryCLAFile2, MoveOffset2-8, 0);
fs_read(TemporaryCLAFile2, &BlockDetection2, 8);

if(DrawCharX1 < DrawCharX2 && ((BlockDetection2 >> CheckDifference) & AttackDetection1) != 0){
*CharHitStatus2 = 2;
}
if(DrawCharX1 >= DrawCharX2 && ((AttackDetection1 >> CheckDifference) & BlockDetection2) != 0){
*CharHitStatus2 = 2;
}

//printf("Hit Position X/Y: %d/%d.\n", *HitPositionX2, *HitPositionY2);
}


if(*CharHitStatus1 == 3){

*HitPositionY1 = PosCharY1+((((MoveOffset1-24)%1536)/(3*8))*CharacterStretchFactor);

 // c will be the number of zero bits on the right

if(HitString1 & 0x1){
 c= 0;
}
else{
 c = 1;
 
if((HitString1 & 0xFFFFFFFF) == 0){
 HitString1 >>= 32;
 c += 32;
}
if((HitString1 & 0xFFFF) == 0){
 HitString1 >>= 16;
 c += 16;
}
if((HitString1 & 0xFF) == 0){
 HitString1 >>= 8;
 c += 8;
}
if((HitString1 & 0xF) == 0){
 HitString1 >>= 4;
 c += 4;
}
if((HitString1 & 0x3) == 0){
 HitString1 >>= 2;
 c += 2;
}
c -= HitString1 & 0x1;
}

//printf("Number of bits on the right: %d.\n", c);

*HitPositionX1 = DrawCharX1+CharacterTextureSize-c*CharacterStretchFactor;

BlockDetection1 = 0;
fs_seek(TemporaryCLAFile1, MoveOffset1-8, 0);
fs_read(TemporaryCLAFile1, &BlockDetection1, 8);

if(DrawCharX1 < DrawCharX2  && ((AttackDetection2 >> CheckDifference) & BlockDetection1) != 0){
*CharHitStatus1 = 2;
}

if(DrawCharX1 >= DrawCharX2 && ((BlockDetection1 >> CheckDifference) & AttackDetection2) != 0){
*CharHitStatus1 = 2;
}
//printf("Hit Position X/Y: %d/%d.\n", *HitPositionX1, *HitPositionY1);
}


//}
//printf("DONE\n");




if(SpecialEffectStage1 == 2){ // && (SpecialEffectDrawX1+SpecialEffectSizeX1 >= DrawCharX2 && SpecialEffectDrawX1 <= DrawCharX2+256 )){
Bluff1 = sprintf(EffectFileDir1, "/%.8s_CRA/%.8s%d.cra", CharacterName1, SpecialEffectNameBuffer1, SpecialEffectWhichFrame1);

CrashLayerDecompress(EffectFileDir1, "/ram/Temporary3.cla");
TemporaryCLAFile3 = fs_open("/ram/Temporary3.cla", O_RDONLY);

if(SpecialEffectDrawY1 < PosCharY2){
CheckPositionY1 = (PosCharY2-SpecialEffectDrawY1)/CharacterStretchFactor;
CheckPositionY2 = 0;
CheckLengthY = (SpecialEffectDrawY1+CharacterTextureSize-PosCharY2)/CharacterStretchFactor;
}
else{
CheckPositionY1 = 0;
CheckPositionY2 = (SpecialEffectDrawY1-PosCharY2)/CharacterStretchFactor;
CheckLengthY = (PosCharY2+CharacterTextureSize-SpecialEffectDrawY1)/CharacterStretchFactor;
}

if(CharIsLeft1 == 1){
StartOffset1 = 0;
CheckPositionX1 = (SpecialEffectDrawX1);
}
else{
StartOffset1 = 512;
CheckPositionX1 = (SpecialEffectDrawX1-CharacterTextureSize+SpecialEffectSizeX1);
}

if(CharIsLeft2 == 1){
StartOffset2 = 0;
}
else{
StartOffset2 = 1536;
}

DataOffset1 = CheckPositionY1*8;
DataOffset2 = CheckPositionY2*3*8;

MoveOffset1 = StartOffset1+DataOffset1;
MoveOffset2 = StartOffset2+DataOffset2;


if(CheckPositionX1 >= DrawCharX2){
CheckDifference = (CheckPositionX1-DrawCharX2)/CharacterStretchFactor;
if(CheckDifference > SizeOfLongLong) CheckLengthY = -1;

CheckLengthX = (DrawCharX2+CharacterTextureSize-CheckPositionX1)/CharacterStretchFactor;


while(CheckLengthY >= 0){
//printf("AttackString Before: %llu! \n", AttackDetection1);
//printf("DetectionString Before: %llu! \n", ExistenceDetection2);

ExistenceDetection1 = 0;

ExistenceDetection2 = 0;


CurrentOffset1 = fs_seek(TemporaryCLAFile3, MoveOffset1, 0);
//printf("Offset1: %ld!\n", CurrentOffset1);
fs_read(TemporaryCLAFile3, &ExistenceDetection1, 8);

MoveOffset1+=8;

CurrentOffset2 = fs_seek(TemporaryCLAFile2, MoveOffset2, 0);
//printf("Offset2: %ld!\n", CurrentOffset2);
fs_read(TemporaryCLAFile2, &ExistenceDetection2, 8);

MoveOffset2+=24;

if(((ExistenceDetection1 >> CheckDifference) & ExistenceDetection2) != 0){
//printf("HIT!\n");
//printf("AttackString: %llu! \n", AttackDetection1);
//printf("DetectionString: %llu! \n", ExistenceDetection2);
//printf("DetectionString shifted: %llu! \n", (ExistenceDetection2 << CheckDifference));
//printf("CheckLength: %d!\n", CheckLengthY);
//printf("X-Axis Difference %d\n", CheckDifference);
*CharHitStatus2 = 7;
CheckLengthY = -1;
HitString2 = ((ExistenceDetection1 >> CheckDifference) & ExistenceDetection2);
}


//CurrentOffset1 = fs_seek(TemporaryCLAFile1, CurrentOffset1+8, 0);
//fs_read(TemporaryCLAFile1, &ExistenceDetection1, 8);



CheckLengthY-=1;
}

}
else{

CheckDifference = (DrawCharX2-CheckPositionX1)/CharacterStretchFactor;
if(CheckDifference > SizeOfLongLong) CheckLengthY = -1;

CheckLengthX = (CheckPositionX1+CharacterTextureSize-DrawCharX2)/CharacterStretchFactor;

while(CheckLengthY >= 0){

ExistenceDetection1 = 0;

ExistenceDetection2 = 0;


CurrentOffset1 = fs_seek(TemporaryCLAFile3, MoveOffset1, 0);
//printf("Offset1: 0x%X!\n", CurrentOffset1);
fs_read(TemporaryCLAFile3, &ExistenceDetection1, 8);

MoveOffset1+=8;

CurrentOffset2 = fs_seek(TemporaryCLAFile2, MoveOffset2, 0);
//printf("Offset2: 0x%X!\n", CurrentOffset2);
fs_read(TemporaryCLAFile2, &ExistenceDetection2, 8);

MoveOffset2+=24;

if(((ExistenceDetection2 >> CheckDifference) & ExistenceDetection1) != 0){

*CharHitStatus2 = 7;
CheckLengthY = -1;
HitString2 = ((ExistenceDetection1 << CheckDifference) & ExistenceDetection2);
}

CheckLengthY-=1;

}
}




if(*CharHitStatus2 == 7){

*HitPositionY2 = PosCharY2+((((MoveOffset2-24)%1536)/(3*8))*CharacterStretchFactor);

 // c will be the number of zero bits on the right

if(HitString2 & 0x1){
 c= 0;
}
else{
 c = 1;
 
if((HitString2 & 0xFFFFFFFF) == 0){
 HitString2 >>= 32;
 c += 32;
}
if((HitString2 & 0xFFFF) == 0){
 HitString2 >>= 16;
 c += 16;
}
if((HitString2 & 0xFF) == 0){
 HitString2 >>= 8;
 c += 8;
}
if((HitString2 & 0xF) == 0){
 HitString2 >>= 4;
 c += 4;
}
if((HitString2 & 0x3) == 0){
 HitString2 >>= 2;
 c += 2;
}
c -= HitString2 & 0x1;
}

//printf("Number of bits on the right: %d.\n", c);

*HitPositionX2 = DrawCharX2+CharacterTextureSize-c*CharacterStretchFactor;

BlockDetection2 = 0;
fs_seek(TemporaryCLAFile2, MoveOffset2-8, 0);
fs_read(TemporaryCLAFile2, &BlockDetection2, 8);

if(DrawCharX2 < DrawCharX1  && ((AttackDetection1 >> CheckDifference) & BlockDetection2) != 0){
*CharHitStatus2 = 8;
}

if(DrawCharX2 >= DrawCharX1 && ((BlockDetection2 >> CheckDifference) & AttackDetection1) != 0){
*CharHitStatus2 = 8;
}

}

fs_close(TemporaryCLAFile3);
fs_unlink("/ram/Temporary3.cla");

}



    fs_close(TemporaryCLAFile1);
    fs_close(TemporaryCLAFile2);
    fs_unlink("/ram/Temporary1.cla");
    fs_unlink("/ram/Temporary2.cla");


}
