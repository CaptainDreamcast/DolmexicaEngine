int CollisionDetect(char* CharacterName1, char* AnimationName1, int FrameID1, char* CharacterName2, char* AnimationName2, int FrameID2, int RealDrawCharX1, int RealDrawCharX2, int PosCharY1, int PosCharY2, int WhichCharLeft, int* CharHitStatus1, int* CharHitStatus2, int* HitPositionX1, int* HitPositionY1, int* HitPositionX2, int* HitPositionY2)
{
gzFile f1;
gzFile f2;
file_t f3;
file_t f4;
//printf("STARTING\n");
int DrawCharX1 = RealDrawCharX1;//2;
int DrawCharX2 = RealDrawCharX2;//2;
char FileDir1[30];
char FileDir2[30];
int Bluff1;
int Bluff2;
Bluff1 = sprintf(FileDir1, "/rd/%.8s_%.8s_%d.cra", CharacterName1, AnimationName1, FrameID1);
Bluff2 = sprintf(FileDir2, "/rd/%.8s_%.8s_%d.cra", CharacterName2, AnimationName2, FrameID2);
//printf("DECLARING\n");
//printf("WhichAnimationFrame2: %d\n", FrameID2);
char* data1;
char* data2;

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
data1 = (char *)malloc(length1+1); // I am not freeing it
data2 = (char *)malloc(length2+1); // I am NOT freeing it

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

if(PosCharY1 < PosCharY2){
CheckPositionY1 = PosCharY2-PosCharY1;
CheckPositionY2 = 0;
CheckLengthY = PosCharY1+256-PosCharY2;
}
if(PosCharY1 >= PosCharY2){
CheckPositionY1 = 0;
CheckPositionY2 = PosCharY1-PosCharY2;
CheckLengthY = PosCharY2+256-PosCharY1;
}

if(WhichCharLeft == 1){
if(DrawCharX1 >= DrawCharX2){
CheckPositionX1 = 0;
CheckPositionX2 = DrawCharX1-DrawCharX2;
CheckLengthX = DrawCharX2+256-DrawCharX1;
}
if(DrawCharX1 < DrawCharX2){
CheckPositionX1 = DrawCharX2-DrawCharX1;
CheckPositionX2 = 0;
CheckLengthX = DrawCharX1+256-DrawCharX2;
}
}

if(WhichCharLeft == 2){
if(DrawCharX2 > DrawCharX1){
CheckPositionX1 = DrawCharX2-DrawCharX1;
CheckPositionX2 = 0;
CheckLengthX = DrawCharX1+256-DrawCharX2;
}
if(DrawCharX2 <= DrawCharX1){
CheckPositionX1 = 0;
CheckPositionX2 = DrawCharX1-DrawCharX2;
CheckLengthX = DrawCharX2+256-DrawCharX1;
}
}
//printf("%c\n", data2[5618]); //Should output 1
//printf("%c\n", data1[((57-1)*128+68)-1]); // SHould output 3 during WKPUNCH
//printf("%c\n", data1[((57-1)*128+68)-1]); // SHould output 3 during KICKJMWK

//printf("%c\n", data1[7235]);
int i = 0;
int j = 0;
int PositionX1Checker = CheckPositionX1;
int PositionX2Checker = CheckPositionX2;
while(i <= CheckLengthY && HitDetected1 == 0 && HitDetected2 == 0){

while(j <= CheckLengthX && HitDetected1 == 0 && HitDetected2 == 0){
if(data1[((CheckPositionY1/2-1)*128+PositionX1Checker/2)-1] == 3 &&data2[((CheckPositionY2/2)*128-PositionX2Checker/2)-2] == 1 && WhichCharLeft == 1 && *CharHitStatus2 == 0){
*CharHitStatus2 = 3;
HitDetected2 = 1;

*HitPositionX2 = DrawCharX1+PositionX1Checker-2;
*HitPositionY2 = PosCharY2+CheckPositionY2-2;
//printf("HIT!\n");
}
if(data1[((CheckPositionY1/2)*128-PositionX1Checker/2)-2] == 3 &&data2[((CheckPositionY2/2-1)*128+PositionX2Checker/2)-1] == 1 && WhichCharLeft == 2 && *CharHitStatus2 == 0){
*CharHitStatus2 = 3;
HitDetected2 = 1;
*HitPositionX2 = DrawCharX2+CheckPositionX2+PositionX2Checker-2;
*HitPositionY2 = PosCharY2+CheckPositionY2-2;
//printf("HIT!\n");
}
PositionX1Checker+=2;
PositionX2Checker+=2;
j+=2;
}

PositionX1Checker = CheckPositionX1;
PositionX2Checker = CheckPositionX2;
j= 0;

CheckPositionY1+=2;
CheckPositionY2+=2;
i+=2;
}
/*
if(DrawCharX1 < DrawCharX2 && WhichCharLeft == 1){
while(CheckPositionRightX <= DrawCharX1+256-DrawCharX2 && HitDetected1 == 0 && HitDetected2 == 0){
if(data1[((CheckPositionY1/2-1)*128+CheckPositionLeftX/2)-1] == 51 &&data2[((CheckPositionY2/2)*128-CheckPositionRightX/2)-2] == 49){
printf("HIT!\n");
}
CheckPositionRightX+=2;
CheckPositionLeftX+=2;
}

CheckPositionLeftX = DrawCharX2-DrawCharX1;
}

if(DrawCharX2 > DrawCharX1 && WhichCharLeft == 2){
while(CheckPositionRightX <= DrawCharX1+256-DrawCharX2 && HitDetected1 == 0 && HitDetected2 == 0){
if(data2[((CheckPositionY2/2-1)*128+CheckPositionRightX/2)-1] == 49 &&data1[((CheckPositionY1/2)*128-CheckPositionLeftX/2)-2] == 51 && ){
printf("HIT!\n");
}
CheckPositionRightX+=2;
CheckPositionLeftX+=2;
}
CheckPositionLeftX = DrawCharX2-DrawCharX1;
}

if(DrawCharX2 <= DrawCharX1 && WhichCharLeft == 2){
while(CheckPositionRightX <= DrawCharX2+256-DrawCharX1 && HitDetected1 == 0 && HitDetected2 == 0){
if(data2[((CheckPositionY2/2-1)*128+CheckPositionLeftX/2)-1] == 49 &&data1[((CheckPositionY1/2)*128-CheckPositionRightX/2)-2] == 51){
printf("HIT!\n");
}
CheckPositionRightX+=2;
CheckPositionLeftX+=2;
}


}
*/

if(HitDetected2 != 0){

}
//printf("DONE\n");

    free(src); // Okay, I am freeing it.
    free(data1);
    free(data2);
    free(state_decompress);
}
