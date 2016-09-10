void DeLoadCredits(file_t* InputFile, CreditSingleLineStruct SingleLineData[]){

char FileDir[NormalFileDirSize];
int DirtyDeedsDoneDirtCheap;

fs_close(*InputFile);

sprintf(FileDir, "/ram/TEXT");
fs_unlink(FileDir);

for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<CreditLinesOnScreenMax; DirtyDeedsDoneDirtCheap++){
if(SingleLineData[DirtyDeedsDoneDirtCheap].LineActive){
free(SingleLineData[DirtyDeedsDoneDirtCheap].Text);
}
}

}

void DeLoadCreditSingleLine(CreditSingleLineStruct* SingleLineData){

free(SingleLineData->Text);

SingleLineData->LineActive = 0;
}

void LoadNextCreditSingleLine(file_t* InputFile, CreditSingleLineStruct SingleLineData[], CreditHeaderStruct* CreditHeaderData){

uint32 LineLength;
uint32 OriginalOffset;
uint32 BailOutValue;
char ZeroValue;
int DirtyDeedsDoneDirtCheap;

DirtyDeedsDoneDirtCheap = 0;
while(SingleLineData[DirtyDeedsDoneDirtCheap].LineActive == 1){ 
DirtyDeedsDoneDirtCheap++;
if(DirtyDeedsDoneDirtCheap >= CreditLinesOnScreenMax) printf("More lines than possible!\n");
}

BailOutValue = fs_total(*InputFile);
OriginalOffset = fs_tell(*InputFile);
ZeroValue = 0;

LineLength = 0;
do{
fs_read((*InputFile), &ZeroValue, 1);
LineLength++;
if(OriginalOffset+LineLength >= BailOutValue){CreditHeaderData->FinalLine = DirtyDeedsDoneDirtCheap; ZeroValue = 0xA;}
} while(ZeroValue != 0x0A);

SingleLineData[DirtyDeedsDoneDirtCheap].Text = (char*) malloc (LineLength);
fs_seek((*InputFile), OriginalOffset, 0);
fs_read((*InputFile), SingleLineData[DirtyDeedsDoneDirtCheap].Text, LineLength);

LineLength--;

SingleLineData[DirtyDeedsDoneDirtCheap].Text[LineLength] = '\0';

SingleLineData[DirtyDeedsDoneDirtCheap].PositionX = (ScreenSizeX/2)-(((CreditHeaderData->SizeX)*LineLength)/2);
SingleLineData[DirtyDeedsDoneDirtCheap].PositionY = CreditHeaderData->LineStartPositionY;

CreditHeaderData->LineStartPositionY += (CreditHeaderData->SizeY+CreditHeaderData->FreeSpaceY);

SingleLineData[DirtyDeedsDoneDirtCheap].LineActive = 1;
}

void LoadCredits(file_t* InputFile, CreditHeaderStruct* CreditHeaderData, CreditSingleLineStruct SingleLineData[]){

int DirtyDeedsDoneDirtCheap;
char OriginalFileDir[NormalFileDirSize];
char FileDir[NormalFileDirSize];


sprintf(OriginalFileDir, "%s/CREDITS/CREDITS.hdr", FileSystemUsed);
(*InputFile) = fs_open(OriginalFileDir, O_RDONLY);
fs_seek((*InputFile), 0, 0);
fs_read((*InputFile), CreditHeaderData, sizeof(CreditHeaderStruct));
fs_close(*InputFile);

sprintf(OriginalFileDir, "%s/CREDITS/CREDITS.txt", FileSystemUsed);
sprintf(FileDir, "/ram/TEXT");
FileCopyToOtherFileSystem(OriginalFileDir, FileDir);

(*InputFile) = fs_open(FileDir, O_RDONLY);
fs_seek((*InputFile), 0, 0);

for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<CreditLinesOnScreenMax; DirtyDeedsDoneDirtCheap++){
SingleLineData[DirtyDeedsDoneDirtCheap].LineActive = 0;
}

while(CreditHeaderData->LineStartPositionY < ScreenSizeY) LoadNextCreditSingleLine(InputFile, SingleLineData, CreditHeaderData);

}

int CreditFunction(){

file_t TextFile;

maple_device_t *cont;
cont_state_t *st;

CreditSingleLineStruct SingleLineData[CreditLinesOnScreenMax];
CreditHeaderStruct CreditHeaderData;

int OffTo;
int DirtyDeedsDoneDirtCheap;
int ReadyToRock;

int CurrentChar;
uint8 ButtonInputAllowed[MaxCharsOnScreen];

LoadCredits(&TextFile, &CreditHeaderData, SingleLineData);


for(CurrentChar=CharacterOne; CurrentChar<MaxCharsOnScreen; CurrentChar++) ButtonInputAllowed[CurrentChar] = 0;

OffTo = GameOverStage;
ReadyToRock = 1;

while(ReadyToRock){

pvr_wait_ready();
pvr_scene_begin();
pvr_list_begin(PVR_LIST_TR_POLY);

for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<CreditLinesOnScreenMax; DirtyDeedsDoneDirtCheap++){
if(SingleLineData[DirtyDeedsDoneDirtCheap].LineActive){
//DrawCreditLine(SingleLineData[DirtyDeedsDoneDirtCheap]);
DrawArray(SingleLineData[DirtyDeedsDoneDirtCheap].Text, SingleLineData[DirtyDeedsDoneDirtCheap].PositionX, SingleLineData[DirtyDeedsDoneDirtCheap].PositionY, 1, CreditHeaderData.SizeY, WhiteColor);
}
}
pvr_list_finish();
pvr_scene_finish();

//CONTROL CODE

for(CurrentChar = CharacterOne; CurrentChar<MaxCharsOnScreen; CurrentChar++){
if((cont = maple_enum_dev(CurrentChar, 0)) != NULL) {
st = (cont_state_t *)maple_dev_status(cont);

if ((st->buttons & CONT_START) && ButtonInputAllowed[CurrentChar] == 1) ReadyToRock = 0;

if ((st->buttons == 0) && ButtonInputAllowed[CurrentChar] == 0) ButtonInputAllowed[CurrentChar] = 1;

if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
OffTo = FinalExitStage;
ReadyToRock = 0;
}

}
}

//CONTROL CODE


CreditHeaderData.LineStartPositionY -= CreditHeaderData.ScrollSpeedY;

for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<CreditLinesOnScreenMax; DirtyDeedsDoneDirtCheap++){
if(SingleLineData[DirtyDeedsDoneDirtCheap].LineActive){

SingleLineData[DirtyDeedsDoneDirtCheap].PositionY -= CreditHeaderData.ScrollSpeedY;

if(SingleLineData[DirtyDeedsDoneDirtCheap].PositionY+CreditHeaderData.SizeY+CreditHeaderData.FreeSpaceY < 0){
if(DirtyDeedsDoneDirtCheap == CreditHeaderData.FinalLine) ReadyToRock = 0;
else DeLoadCreditSingleLine(&SingleLineData[DirtyDeedsDoneDirtCheap]);
}
if(CreditHeaderData.LineStartPositionY < ScreenSizeY && CreditHeaderData.FinalLine == 0xff) LoadNextCreditSingleLine(&TextFile, SingleLineData, &CreditHeaderData);
}
}

}

DeLoadCredits(&TextFile, SingleLineData);


return(OffTo);
}