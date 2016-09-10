int CollisionDetect(char* CharacterName1, char* AnimationName1, int FrameID1, char* CharacterName2, char* AnimationName2, int FrameID2, int RealDrawCharX1, int RealDrawCharX2, int PosCharY1, int PosCharY2, int WhichCharLeft, int* CharHitStatus1, int* CharHitStatus2, int* HitPositionX1, int* HitPositionY1, int* HitPositionX2, int* HitPositionY2)
{
gzFile f1;
gzFile f2;
file_t f3;
file_t f4;
file_t TemporaryCLAFile1;
file_t TemporaryCLAFile2;
//printf("STARTING\n");
int DrawCharX1 = RealDrawCharX1;//2;
int DrawCharX2 = RealDrawCharX2;//2;
char FileDir1[30];
char FileDir2[30];
int Bluff1;
int Bluff2;
Bluff1 = sprintf(FileDir1, "/rd/%.8s_%.8s_%d.cra", CharacterName1, AnimationName1, FrameID1);
Bluff2 = sprintf(FileDir2, "/rd/%.8s_%.8s_%d.cra", CharacterName2, AnimationName2, FrameID2);
int StartOffset1 = 0;
int StartOffset2 = 0;
long CurrentOffset1 = 0;
long CurrentOffset2 = 0;
long MoveOffset1 = 0;
long MoveOffset2 = 0;
//printf("DECLARING\n");
//printf("WhichAnimationFrame2: %d\n", FrameID2);
unsigned long long* data1;
unsigned long long* data2;
unsigned long long ExistenceDetection1 = 0;
unsigned long long AttackDetection1 = 0;
unsigned long long BlockDetection1 = 0;
unsigned long long ExistenceDetection2 = 0;
unsigned long long AttackDetection2 = 0;
unsigned long long BlockDetection2 = 0;

char *src, *dst, *scratch;
qlz_state_decompress *state_decompress = (qlz_state_decompress *)malloc(sizeof(qlz_state_decompress));
size_t len;

//printf("OPENING\n");
f3 = fs_open(FileDir1, O_RDONLY);
   // allocate source buffer
len = fs_total(f3);
src = (char*) malloc(len);
//printf("%ld\n", len);
   // read file and allocate destination buffer
fs_read(f3, src, len);
len = qlz_size_decompressed(src);
//printf("%ld\n", len);
data1 = (char*) malloc(len);
//printf("DECOMPRESSING\n");
   // decompress and write result
len = qlz_decompress(src, data1, state_decompress);
//printf("DECOMPRESSED\n");
fs_close(f3);

free(src);
//printf("ATTEMPTING READING AGAIN\n");
f4 = fs_open(FileDir2, O_RDONLY);
   // allocate source buffer
len = fs_total(f4);
//printf("%ld\n", len);
//printf("ALLOCATING BUFFER\n");
src = (char*) malloc(len);

   // read file and allocate destination buffer
fs_read(f4, src, len);
len = qlz_size_decompressed(src);
//printf("%ld\n", len);
data2 = (char*) malloc(len);
//printf("DECOMPRESSING AGAIN\n");
   // decompress and write result
len = qlz_decompress(src, data2, state_decompress);
fs_close(f4);


/*
int length1 = zlib_getlength(FileDir1);
int length2 = zlib_getlength(FileDir2);
data1 = (unsigned long long int *)malloc(length1+1); // I am not freeing it
data2 = (unsigned long long int *)malloc(length2+1); // I am NOT freeing it

f1 = gzopen(FileDir1, "r");
gzread(f1, data1, length1);
data1[length1] = 0;
gzclose(f1);

f2 = gzopen(FileDir2, "r");
gzread(f2, data2, length2);
data2[length2] = 0;
gzclose(f2);
*/

//printf("%c\n", data1[(55*128+67)-1]); //ASCII 1=49 etc...
int HitDetected1 = 0;
int HitDetected2 = 0;
//int CheckPositionRightX = 2;
int CheckPositionY1;
int CheckPositionY2;
//int CheckPositionLeftX;
int CheckLengthY;
int CheckPositionX1;
int CheckPositionX2;
int CheckLengthX;
int PositionCheckerY = 0;
int CheckDifference;

if(PosCharY1 < PosCharY2){
CheckPositionY1 = (PosCharY2-PosCharY1)/4;
CheckPositionY2 = 0;
CheckLengthY = (PosCharY1+256-PosCharY2)/4;
}
if(PosCharY1 >= PosCharY2){
CheckPositionY1 = 0;
CheckPositionY2 = (PosCharY1-PosCharY2)/4;
CheckLengthY = (PosCharY2+256-PosCharY1)/4;
}

if(WhichCharLeft == 1){
StartOffset1 = 0;
StartOffset2 = 128*3;
}
if(WhichCharLeft == 2){
StartOffset1 = 128*3;
StartOffset2 = 0;
}

int DataOffset1 = CheckPositionY1*3;
int DataOffset2 = CheckPositionY2*3;
MoveOffset1 = StartOffset1+DataOffset1;
MoveOffset2 = StartOffset2+DataOffset2;



if(DrawCharX1 >= DrawCharX2){
CheckDifference = (DrawCharX1-DrawCharX2)/4;
CheckLengthX = (DrawCharX2+256-DrawCharX1)/4;
//printf("X-Axis Difference %d\n", CheckDifference);

while(CheckLengthY >= 0){
//printf("AttackString Before: %llu! \n", AttackDetection1);
//printf("DetectionString Before: %llu! \n", ExistenceDetection2);

if(((data1[MoveOffset1+1] >> CheckDifference) & data2[MoveOffset2]) != 0){
printf("HIT!\n");
printf("AttackString: %llu! \n", AttackDetection1);
printf("AttackString shifted: %llu! \n", (AttackDetection1 << CheckDifference));
printf("DetectionString: %llu! \n", ExistenceDetection2);
printf("CheckLength: %d!\n", CheckLengthY);
printf("X-Axis Difference %d\n", CheckDifference);
CheckLengthY = -1;
}

//CurrentOffset1 = fs_seek(TemporaryCLAFile1, CurrentOffset1+8, 0);
//fs_read(TemporaryCLAFile1, &ExistenceDetection1, 8);


MoveOffset1+=3;

MoveOffset2+=3;

CheckLengthY-=1;
}

}
else{
CheckDifference = (DrawCharX2-DrawCharX1)/4;
CheckLengthX = (DrawCharX1+256-DrawCharX2)/4;
//printf("X-Axis Difference %d\n", CheckDifference);

while(CheckLengthY >= 0){
//printf("AttackString Before: %llu! \n", AttackDetection1);
//printf("DetectionString Before: %llu! \n", ExistenceDetection2);

if(((data2[MoveOffset2] >> CheckDifference) & data1[MoveOffset1+1]) != 0){
printf("HIT!\n");
printf("AttackString: %llu! \n", AttackDetection1);
printf("DetectionString: %llu! \n", ExistenceDetection2);
printf("DetectionString shifted: %llu! \n", (ExistenceDetection2 << CheckDifference));
printf("CheckLength: %d!\n", CheckLengthY);
printf("X-Axis Difference %d\n", CheckDifference);
CheckLengthY = -1;
}


MoveOffset1+=3;

MoveOffset2+=3;

CheckLengthY-=1;
}
}



if(HitDetected2 != 0){

}
//printf("DONE\n");

    free(src); // Okay, I am freeing it.
    free(data1);
    free(data2);
    free(state_decompress);

}
