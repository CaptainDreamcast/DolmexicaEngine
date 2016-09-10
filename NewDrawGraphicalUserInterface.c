void DrawArray(char Array[], int ScreenPositionX, int ScreenPositionY, int ScreenPositionZ, int Size, char Color){

pvr_poly_cxt_t cxt;
pvr_poly_hdr_t hdr;
pvr_vertex_t vert;

int WhichChar = 0;
int Bluff;

float Red, Green ,Blue;
if(Color == BlackColor) Red = Green = Blue = 0;
else if(Color == RedColor){ Red = 1.0f; Green = Blue = 0;}
else if(Color == GreenColor){ Green = 1.0f; Red = Blue = 0;}
else if(Color == BlueColor){ Blue = 1.0f; Green = Red = 0;}
else if(Color == YellowColor){ Green = Red = 1.0f; Blue = 0;}
else Red = Green = Blue = 1.0f;

pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, FontHeaderData.TextureSizeX, FontHeaderData.TextureSizeY, FontTexture, PVR_FILTER_BILINEAR);

pvr_poly_compile(&hdr, &cxt);
pvr_prim(&hdr, sizeof(hdr));

while(Array[WhichChar] != '\0'){

if(Array[WhichChar] < 32 || Array[WhichChar] > 122) Bluff = 0;
else Bluff = Array[WhichChar]-32;

vert.argb = PVR_PACK_COLOR(1.0f, Red, Green, Blue);
vert.oargb = 0;
vert.flags = PVR_CMD_VERTEX;

vert.x = ScreenPositionX;
vert.y = ScreenPositionY;
vert.z = ScreenPositionZ;
vert.u = FontCharacterData[Bluff].FilePositionX1;
vert.v = FontCharacterData[Bluff].FilePositionY1;
pvr_prim(&vert, sizeof(vert));

vert.x = ScreenPositionX+Size;
vert.y = ScreenPositionY;
vert.z = ScreenPositionZ;
vert.u = FontCharacterData[Bluff].FilePositionX2;
vert.v = FontCharacterData[Bluff].FilePositionY1;
pvr_prim(&vert, sizeof(vert));

vert.x = ScreenPositionX;
vert.y = ScreenPositionY+Size;
vert.z = ScreenPositionZ;
vert.u = FontCharacterData[Bluff].FilePositionX1;
vert.v = FontCharacterData[Bluff].FilePositionY2;
pvr_prim(&vert, sizeof(vert));

vert.x = ScreenPositionX+Size;
vert.y = ScreenPositionY+Size;
vert.z = ScreenPositionZ;
vert.u = FontCharacterData[Bluff].FilePositionX2;
vert.v = FontCharacterData[Bluff].FilePositionY2;
vert.flags = PVR_CMD_VERTEX_EOL;
pvr_prim(&vert, sizeof(vert));

ScreenPositionX+=Size;
WhichChar++;
}

}

void DrawTimer(pvr_ptr_t NewTimerTexture, TimerStruct TimerHeaderData, FontSingleCharacterStruct TimerCharacterData[], int TimerValue1, int TimerValue2){

pvr_poly_cxt_t cxt;
pvr_poly_hdr_t hdr;
pvr_vertex_t vert;

int WhichValue;
int CurrentValue;

pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, TimerHeaderData.TextureSizeX, TimerHeaderData.TextureSizeY, NewTimerTexture, PVR_FILTER_BILINEAR);
pvr_poly_compile(&hdr, &cxt);
pvr_prim(&hdr, sizeof(hdr));

WhichValue = TimerValue1;
CurrentValue = 0;
while(CurrentValue < MaximumTimerLength && WhichValue != -1){

if(WhichValue == 10){ 
TimerHeaderData.SizeX[CurrentValue] = (TimerHeaderData.PositionX[CurrentValue+1]+TimerHeaderData.SizeX[CurrentValue+1])-TimerHeaderData.PositionX[CurrentValue];
}



vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
vert.oargb = 0;
vert.flags = PVR_CMD_VERTEX;

vert.x = TimerHeaderData.PositionX[CurrentValue];
vert.y = TimerHeaderData.PositionY[CurrentValue];
vert.z = LowerGuiPositionZ;
vert.u = TimerCharacterData[WhichValue].FilePositionX1;
vert.v = TimerCharacterData[WhichValue].FilePositionY1;
pvr_prim(&vert, sizeof(vert));

vert.x = TimerHeaderData.PositionX[CurrentValue]+TimerHeaderData.SizeX[CurrentValue];
vert.y = TimerHeaderData.PositionY[CurrentValue];
vert.z = LowerGuiPositionZ;
vert.u = TimerCharacterData[WhichValue].FilePositionX2;
vert.v = TimerCharacterData[WhichValue].FilePositionY1;
pvr_prim(&vert, sizeof(vert));

vert.x = TimerHeaderData.PositionX[CurrentValue];
vert.y = TimerHeaderData.PositionY[CurrentValue]+TimerHeaderData.SizeY[CurrentValue];
vert.z = LowerGuiPositionZ;
vert.u = TimerCharacterData[WhichValue].FilePositionX1;
vert.v = TimerCharacterData[WhichValue].FilePositionY2;
pvr_prim(&vert, sizeof(vert));

vert.x = TimerHeaderData.PositionX[CurrentValue]+TimerHeaderData.SizeX[CurrentValue];
vert.y = TimerHeaderData.PositionY[CurrentValue]+TimerHeaderData.SizeY[CurrentValue];
vert.z = LowerGuiPositionZ;
vert.u = TimerCharacterData[WhichValue].FilePositionX2;
vert.v = TimerCharacterData[WhichValue].FilePositionY2;
vert.flags = PVR_CMD_VERTEX_EOL;
pvr_prim(&vert, sizeof(vert));

WhichValue = TimerValue2;
CurrentValue++;
}



}