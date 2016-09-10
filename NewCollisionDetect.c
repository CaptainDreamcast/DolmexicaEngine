void NewCollisionDetect(char CharacterName[][10], char AnimationName[][10], char FrameID[], int DrawCharX[], int PosCharY[], char CharIsLeft[], char CharHitStatus[], int HitPositionX[], int HitPositionY[], int CharacterStretchFactor, int CharacterTextureSize, int SpecialEffectStage[], short SpecialEffectSizeX[], short SpecialEffectSizeY[], int SpecialEffectDrawX[], int SpecialEffectDrawY[], char SpecialEffectWhichFrame[], char SpecialEffectNameBuffer[][8])
{

unsigned long long* CrashLayerBuffer[MaxCharsOnScreen];
unsigned long long* SpecialEffectCrashLayerBuffer;

char FileDir[MaxCharsOnScreen][NormalFileDirSize];

int CurrentChar;
int OtherChar;

int LeftChar;
int RightChar;
int SpecialEffectLeftChar;
int SpecialEffectRightChar;
int UpperChar;
int BailOutValue;

int StartOffset[MaxCharsOnScreen];
short SpecialEffectUniversalDrawX[MaxCharsOnScreen];
uint32 MoveOffset[MaxCharsOnScreen];
uint32 SpecialEffectMoveOffset[MaxCharsOnScreen];
unsigned long long HitString[MaxCharsOnScreen];

unsigned int c;

int CheckPositionY[MaxCharsOnScreen];
int CheckLengthY;
int CheckDifference;


if(PosCharY[CharacterOne] < PosCharY[CharacterTwo]){
CheckPositionY[CharacterOne] = (PosCharY[CharacterTwo]-PosCharY[CharacterOne])/CharacterStretchFactor;
CheckPositionY[CharacterTwo] = 0;
CheckLengthY = (PosCharY[CharacterOne]+CharacterTextureSize-PosCharY[CharacterTwo])/CharacterStretchFactor;
UpperChar = CharacterOne;
}
else{
CheckPositionY[CharacterOne] = 0;
CheckPositionY[CharacterTwo] = (PosCharY[CharacterOne]-PosCharY[CharacterTwo])/CharacterStretchFactor;
CheckLengthY = (PosCharY[CharacterTwo]+CharacterTextureSize-PosCharY[CharacterOne])/CharacterStretchFactor;
UpperChar = CharacterTwo;
}

BailOutValue = 0;

for(CurrentChar = CharacterOne; CurrentChar<MaxCharsOnScreen; CurrentChar++){

CrashLayerBuffer[CurrentChar] = (unsigned long long*) malloc(CrashLayerExistenceTypeAmount*sizeof(unsigned long long)*BasicCharacterTextureSizeDrawn*2);
sprintf(FileDir[CurrentChar], "/%.8s_CRA/%.8s%d.cra", CharacterName[CurrentChar], AnimationName[CurrentChar], FrameID[CurrentChar]);
NewCrashLayerDecompress(FileDir[CurrentChar], CrashLayerBuffer[CurrentChar]);


if(CharIsLeft[CurrentChar]) StartOffset[CurrentChar] = 0;
else StartOffset[CurrentChar] = CrashLayerExistenceTypeAmount*BasicCharacterTextureSizeDrawn;


if(CurrentChar == UpperChar) BailOutValue = StartOffset[CurrentChar]+CrashLayerExistenceTypeAmount*BasicCharacterTextureSizeDrawn;

MoveOffset[CurrentChar] = StartOffset[CurrentChar]+(CheckPositionY[CurrentChar]*CrashLayerExistenceTypeAmount);

}

if(DrawCharX[CharacterOne] >= DrawCharX[CharacterTwo]){
LeftChar = CharacterTwo;
RightChar = CharacterOne;
}
else{
LeftChar = CharacterOne;
RightChar = CharacterTwo;
}


CheckDifference = (DrawCharX[RightChar]-DrawCharX[LeftChar])/CharacterStretchFactor;
if(CheckDifference > SizeOfLongLong) BailOutValue = 0;


while(BailOutValue > MoveOffset[UpperChar]){


if(((CrashLayerBuffer[RightChar][MoveOffset[RightChar]+CrashLayerAttackExistenceOffset] >> CheckDifference) & CrashLayerBuffer[LeftChar][MoveOffset[LeftChar]]) != 0){
CharHitStatus[LeftChar] = 3;
BailOutValue = 0;
HitString[LeftChar] = ((CrashLayerBuffer[RightChar][MoveOffset[RightChar]+CrashLayerAttackExistenceOffset] >> CheckDifference) & CrashLayerBuffer[LeftChar][MoveOffset[LeftChar]]);
}
else if(((CrashLayerBuffer[RightChar][MoveOffset[RightChar]] >> CheckDifference) & CrashLayerBuffer[LeftChar][MoveOffset[LeftChar]+CrashLayerAttackExistenceOffset]) != 0){
CharHitStatus[RightChar] = 3;
BailOutValue = 0;
HitString[RightChar] = ((CrashLayerBuffer[LeftChar][MoveOffset[LeftChar]+CrashLayerAttackExistenceOffset] << CheckDifference) & CrashLayerBuffer[RightChar][MoveOffset[RightChar]]);
}


MoveOffset[CharacterOne] += CrashLayerExistenceTypeAmount;
MoveOffset[CharacterTwo] += CrashLayerExistenceTypeAmount;


CheckLengthY-=1;
}

MoveOffset[CharacterOne] -= CrashLayerExistenceTypeAmount;
MoveOffset[CharacterTwo] -= CrashLayerExistenceTypeAmount;

OtherChar = CharacterTwo;
for(CurrentChar = CharacterOne; CurrentChar < MaxCharsOnScreen; CurrentChar++){


if(CharHitStatus[CurrentChar] == 3){

HitPositionY[CurrentChar] = PosCharY[CurrentChar]+(((MoveOffset[CurrentChar]%(CrashLayerExistenceTypeAmount*BasicCharacterTextureSizeDrawn))/(CrashLayerExistenceTypeAmount))*CharacterStretchFactor);

 // c will be the number of zero bits on the right

if(HitString[CurrentChar] & 0x1){
 c= 0;
}
else{
 c = 1;
 
if((HitString[CurrentChar] & 0xFFFFFFFF) == 0){
 HitString[CurrentChar] >>= 32;
 c += 32;
}
if((HitString[CurrentChar] & 0xFFFF) == 0){
 HitString[CurrentChar] >>= 16;
 c += 16;
}
if((HitString[CurrentChar] & 0xFF) == 0){
 HitString[CurrentChar] >>= 8;
 c += 8;
}
if((HitString[CurrentChar] & 0xF) == 0){
 HitString[CurrentChar] >>= 4;
 c += 4;
}
if((HitString[CurrentChar] & 0x3) == 0){
 HitString[CurrentChar] >>= 2;
 c += 2;
}
c -= HitString[CurrentChar] & 0x1;
}

//printf("Number of bits on the right: %d.\n", c);

HitPositionX[CurrentChar] = DrawCharX[CurrentChar]+CharacterTextureSize-c*CharacterStretchFactor;

if(CurrentChar == RightChar && ((CrashLayerBuffer[RightChar][MoveOffset[RightChar]+CrashLayerBlockExistenceOffset] >> CheckDifference) & CrashLayerBuffer[LeftChar][MoveOffset[LeftChar]+CrashLayerAttackExistenceOffset]) != 0){
CharHitStatus[CurrentChar] = 2;
}
else if(CurrentChar == LeftChar && ((CrashLayerBuffer[RightChar][MoveOffset[RightChar]+CrashLayerAttackExistenceOffset] >> CheckDifference) & CrashLayerBuffer[LeftChar][MoveOffset[LeftChar]+CrashLayerBlockExistenceOffset]) != 0){
CharHitStatus[CurrentChar] = 2;
}

}


if(SpecialEffectStage[CurrentChar] != 0){

if(SpecialEffectDrawY[CurrentChar] < PosCharY[OtherChar]){
CheckPositionY[CurrentChar] = (PosCharY[OtherChar]-SpecialEffectDrawY[CurrentChar])/CharacterStretchFactor;
CheckPositionY[OtherChar] = 0;
CheckLengthY = (SpecialEffectDrawY[CurrentChar]+CharacterTextureSize-PosCharY[CharacterTwo])/CharacterStretchFactor;
UpperChar = CurrentChar;
}
else{
CheckPositionY[CurrentChar] = 0;
CheckPositionY[OtherChar] = (SpecialEffectDrawY[CurrentChar]-PosCharY[OtherChar])/CharacterStretchFactor;
CheckLengthY = (PosCharY[OtherChar]+CharacterTextureSize-SpecialEffectDrawY[CurrentChar])/CharacterStretchFactor;
UpperChar = OtherChar;
}

BailOutValue = 0;



SpecialEffectCrashLayerBuffer = (unsigned long long*) malloc(sizeof(unsigned long long)*BasicCharacterTextureSizeDrawn*2);
sprintf(FileDir[CurrentChar], "/%.8s_CRA/%.8s%d.cra", CharacterName[CurrentChar], SpecialEffectNameBuffer[CurrentChar], SpecialEffectWhichFrame[CurrentChar]);
NewCrashLayerDecompress(FileDir[CurrentChar], SpecialEffectCrashLayerBuffer);

if(CharIsLeft[CurrentChar]) StartOffset[CurrentChar] = 0;
else StartOffset[CurrentChar] = BasicCharacterTextureSizeDrawn;

if(CurrentChar == UpperChar) BailOutValue = StartOffset[CurrentChar]+BasicCharacterTextureSizeDrawn;
SpecialEffectMoveOffset[CurrentChar] = StartOffset[CurrentChar]+(CheckPositionY[CurrentChar]);



if(CharIsLeft[OtherChar]) StartOffset[OtherChar] = 0;
else StartOffset[OtherChar] = CrashLayerExistenceTypeAmount*BasicCharacterTextureSizeDrawn;

if(OtherChar == UpperChar) BailOutValue = StartOffset[OtherChar]+CrashLayerExistenceTypeAmount*BasicCharacterTextureSizeDrawn;
SpecialEffectMoveOffset[OtherChar] = StartOffset[OtherChar]+(CheckPositionY[OtherChar]*CrashLayerExistenceTypeAmount);

if(CharIsLeft[CurrentChar]) SpecialEffectUniversalDrawX[CurrentChar] = SpecialEffectDrawX[CurrentChar];
else SpecialEffectUniversalDrawX[CurrentChar] = SpecialEffectDrawX[CurrentChar]-CharacterTextureSize+SpecialEffectSizeX[CurrentChar];

SpecialEffectUniversalDrawX[OtherChar] = DrawCharX[OtherChar];

if(SpecialEffectUniversalDrawX[CurrentChar] >= SpecialEffectUniversalDrawX[OtherChar]){
SpecialEffectLeftChar = OtherChar;
SpecialEffectRightChar = CurrentChar;
}
else{
SpecialEffectLeftChar = CurrentChar;
SpecialEffectRightChar = OtherChar;
}

CheckDifference = (SpecialEffectUniversalDrawX[SpecialEffectRightChar]-SpecialEffectUniversalDrawX[SpecialEffectLeftChar])/CharacterStretchFactor;
if(CheckDifference > SizeOfLongLong) BailOutValue = 0;


while(BailOutValue > SpecialEffectMoveOffset[UpperChar]){


if(SpecialEffectRightChar == CurrentChar && ((SpecialEffectCrashLayerBuffer[SpecialEffectMoveOffset[SpecialEffectRightChar]] >> CheckDifference) & CrashLayerBuffer[SpecialEffectLeftChar][SpecialEffectMoveOffset[SpecialEffectLeftChar]]) != 0){
CharHitStatus[SpecialEffectLeftChar] = 7;
BailOutValue = 0;
//SpecialEffectHitString[SpecialEffectLeftChar] = ((SpecialEffectCrashLayerBuffer[SpecialEffectMoveOffset[SpecialEffectRightChar]] >> CheckDifference) & CrashLayerBuffer[SpecialEffectLeftChar][SpecialEffectMoveOffset[SpecialEffectLeftChar]]);
}
else if(SpecialEffectLeftChar == CurrentChar && ((CrashLayerBuffer[SpecialEffectRightChar][SpecialEffectMoveOffset[SpecialEffectRightChar]] >> CheckDifference) & SpecialEffectCrashLayerBuffer[SpecialEffectMoveOffset[SpecialEffectLeftChar]]) != 0){
CharHitStatus[SpecialEffectRightChar] = 7;
BailOutValue = 0;
//SpecialEffectHitString[SpecialEffectRightChar] = ((SpecialEffectCrashLayerBuffer[SpecialEffectMoveOffset[SpecialEffectLeftChar]] << CheckDifference) & CrashLayerBuffer[SpecialEffectRightChar][SpecialEffectMoveOffset[SpecialEffectRightChar]]);
}


SpecialEffectMoveOffset[CurrentChar]++;
SpecialEffectMoveOffset[OtherChar] += CrashLayerExistenceTypeAmount;


CheckLengthY-=1;
}

SpecialEffectMoveOffset[CurrentChar] --;
SpecialEffectMoveOffset[OtherChar] -= CrashLayerExistenceTypeAmount;

if(CharHitStatus[OtherChar] == 7){

if(SpecialEffectRightChar == CurrentChar && ((SpecialEffectCrashLayerBuffer[SpecialEffectMoveOffset[SpecialEffectRightChar]] >> CheckDifference) & CrashLayerBuffer[SpecialEffectLeftChar][SpecialEffectMoveOffset[SpecialEffectLeftChar]+CrashLayerBlockExistenceOffset]) != 0){
CharHitStatus[SpecialEffectLeftChar] = 8;
}
else if(SpecialEffectLeftChar == CurrentChar && ((CrashLayerBuffer[SpecialEffectRightChar][SpecialEffectMoveOffset[SpecialEffectRightChar]+CrashLayerBlockExistenceOffset] >> CheckDifference) & SpecialEffectCrashLayerBuffer[SpecialEffectMoveOffset[SpecialEffectLeftChar]]) != 0){
CharHitStatus[SpecialEffectRightChar] = 8;
}

}

free(SpecialEffectCrashLayerBuffer);
}

OtherChar--;
}

free(CrashLayerBuffer[CharacterOne]);
free(CrashLayerBuffer[CharacterTwo]);

}
