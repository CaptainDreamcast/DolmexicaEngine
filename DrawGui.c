   void PointsAdd(char PointArray[], int AdditionalPoints, int CharCrouchPosition, int EnemyCrouchPosition, int CharGroundLevel, int EnemyGroundLevel){

   if(EnemyCrouchPosition == 2) AdditionalPoints *= 2;
   if(EnemyGroundLevel == 0) AdditionalPoints *= 3;
   if(CharGroundLevel == 0) AdditionalPoints *= 2;
   if(CharCrouchPosition == 2) AdditionalPoints *= 3;

   PointArray[0] += AdditionalPoints/10000;
   AdditionalPoints-= (AdditionalPoints/10000)*10000;
   PointArray[1] += AdditionalPoints/1000;
   AdditionalPoints-= (AdditionalPoints/1000)*1000;
   PointArray[2] += AdditionalPoints/100;
   AdditionalPoints-= (AdditionalPoints/100)*100;
   PointArray[3] += AdditionalPoints/10;
   AdditionalPoints-= (AdditionalPoints/10)*10;
   PointArray[4] += AdditionalPoints;

   if(PointArray[4] > 57){
   PointArray[3]+=1;
   PointArray[4] -= 10;
   }
   if(PointArray[3] > 57){
   PointArray[2]+=1;
   PointArray[3] -= 10;
   }
   if(PointArray[2] > 57){
   PointArray[1]+=1;
   PointArray[2] -= 10;
   }
   if(PointArray[1] > 57){
   PointArray[0]+=1;
   PointArray[1] -= 10;
   }
   if(PointArray[0] > 57){
   PointArray[0] = 48;
   }              
   }

/*
void DrawNumber(int Number, int ScreenPositionX, int ScreenPositionY, int Size, int ScreenPositionZ){

int MaximumDigits = 3;

float FilePositionX[MaximumDigits];
float FilePositionY[MaximumDigits];

int TemporaryNumber;
int SubtractionValue;

int i, j;

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 128, 128, TimerTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

for(i = MaximumDigits-1; i >= 0; i--){

TemporaryNumber = Number;
j = i;
SubtractionValue = 1;
while(j > 0){ 
TemporaryNumber = TemporaryNumber/10;
SubtractionValue = SubtractionValue*10;
j--;
}
FilePositionX[i] = (TemporaryNumber%5)*0.1953125;
if(TemporaryNumber >= 5) FilePositionY[i] = 0.375;
else FilePositionY[i] = 0;
while(Number >= SubtractionValue) Number -= SubtractionValue;

}

i = MaximumDigits-1;

while(i >= 0){

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = ScreenPositionZ;
    vert.u = FilePositionX[i];
    vert.v = FilePositionY[i];
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+Size;
    vert.y = ScreenPositionY;
    vert.z = ScreenPositionZ;
    vert.u = FilePositionX[i]+0.1953125;
    vert.v = FilePositionY[i];
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+Size;
    vert.z = ScreenPositionZ;
    vert.u = FilePositionX[i];
    vert.v = FilePositionY[i]+0.375;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+Size;
    vert.y = ScreenPositionY+Size;
    vert.z = ScreenPositionZ;
    vert.u = FilePositionX[i]+0.1953125;
    vert.v = FilePositionY[i]+0.375;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

ScreenPositionX+=Size;

i--;
}


}

*/

/*void OldDrawTimer(int TimerValue1, int TimerValue2){

float FilePositionX = (TimerValue1%5)*0.1953125;
float FilePositionY = 0;
if(TimerValue1 >= 5) FilePositionY = 0.375;
int ScreenPositionX = 270;
int ScreenPositionY = 30;



    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 128, 128, TimerTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = LowerGuiPositionZ;
    vert.u = FilePositionX;
    vert.v = FilePositionY;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+50;
    vert.y = ScreenPositionY;
    vert.z = LowerGuiPositionZ;
    vert.u = FilePositionX+0.1953125;
    vert.v = FilePositionY;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+50;
    vert.z = LowerGuiPositionZ;
    vert.u = FilePositionX;
    vert.v = FilePositionY+0.375;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+50;
    vert.y = ScreenPositionY+50;
    vert.z = LowerGuiPositionZ;
    vert.u = FilePositionX+0.1953125;
    vert.v = FilePositionY+0.375;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

FilePositionX = (TimerValue2%5)*0.1953125;
if(TimerValue2 >= 5) FilePositionY = 0.375;
else FilePositionY = 0;
ScreenPositionX+= 50;

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = LowerGuiPositionZ;
    vert.u = FilePositionX;
    vert.v = FilePositionY;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+50;
    vert.y = ScreenPositionY;
    vert.z = LowerGuiPositionZ;
    vert.u = FilePositionX+0.1953125;
    vert.v = FilePositionY;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+50;
    vert.z = LowerGuiPositionZ;
    vert.u = FilePositionX;
    vert.v = FilePositionY+0.375;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+50;
    vert.y = ScreenPositionY+50;
    vert.z = LowerGuiPositionZ;
    vert.u = FilePositionX+0.1953125;
    vert.v = FilePositionY+0.375;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

}*/

/*void DrawPoints(char PointArray1[], char PointArray2[]){

int CurrentValue = 0;
int ScreenPositionX = 95;
int ScreenPositionY = 10;
char TextSize = 20;
float FilePositionX;
float FilePositionY;

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 128, 128, TimerTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

while(PointArray1[CurrentValue] != '\0'){

FilePositionX = ((PointArray1[CurrentValue]-48)%5)*0.1953125;
FilePositionY = 0;
if(PointArray1[CurrentValue] >= 53) FilePositionY = 0.375;






    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = LowerGuiPositionZ;
    vert.u = FilePositionX;
    vert.v = FilePositionY;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+TextSize;
    vert.y = ScreenPositionY;
    vert.z = LowerGuiPositionZ;
    vert.u = FilePositionX+0.1953125;
    vert.v = FilePositionY;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+TextSize;
    vert.z = LowerGuiPositionZ;
    vert.u = FilePositionX;
    vert.v = FilePositionY+0.375;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+TextSize;
    vert.y = ScreenPositionY+TextSize;
    vert.z = LowerGuiPositionZ;
    vert.u = FilePositionX+0.1953125;
    vert.v = FilePositionY+0.375;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

CurrentValue++;
ScreenPositionX+=TextSize;

}

CurrentValue = 0;
ScreenPositionX = 445;


while(PointArray2[CurrentValue] != '\0'){

FilePositionX = ((PointArray2[CurrentValue]-48)%5)*0.1953125;
FilePositionY = 0;
if(PointArray2[CurrentValue] >= 53) FilePositionY = 0.375;

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = LowerGuiPositionZ;
    vert.u = FilePositionX;
    vert.v = FilePositionY;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+TextSize;
    vert.y = ScreenPositionY;
    vert.z = LowerGuiPositionZ;
    vert.u = FilePositionX+0.1953125;
    vert.v = FilePositionY;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+TextSize;
    vert.z = LowerGuiPositionZ;
    vert.u = FilePositionX;
    vert.v = FilePositionY+0.375;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+TextSize;
    vert.y = ScreenPositionY+TextSize;
    vert.z = LowerGuiPositionZ;
    vert.u = FilePositionX+0.1953125;
    vert.v = FilePositionY+0.375;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

CurrentValue++;
ScreenPositionX+=TextSize;
}

}
*/

/*
void OldDrawArray(char Array[], int ScreenPositionX, int ScreenPositionY, int ScreenPositionZ, int Size, char Color){
int WhichChar = 0;
float FilePositionX;
float FilePositionY;
float Red, Green ,Blue;
if(Color == BlackColor) Red = Green = Blue = 0;
else if(Color == RedColor){ Red = 1.0f; Green = Blue = 0;}
else if(Color == GreenColor){ Green = 1.0f; Red = Blue = 0;}
else if(Color == BlueColor){ Blue = 1.0f; Green = Red = 0;}
else if(Color == YellowColor){ Green = Red = 1.0f; Blue = 0;}
else Red = Green = Blue = 1.0f;

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 512, 512, GuiTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

while(Array[WhichChar] != '\0'){
if(Array[WhichChar] >= 65 && Array[WhichChar] <= 90){
FilePositionX = ((Array[WhichChar]-65)%13)*0.076171875;
if(Array[WhichChar] >= 78) FilePositionY = 0.60546875;
else FilePositionY = 0.45703125;
}
else{ 
FilePositionX = 11*0.076171875;
FilePositionY = 0.75390625;
}
    vert.argb = PVR_PACK_COLOR(1.0f, Red, Green, Blue);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = ScreenPositionZ;
    vert.u = FilePositionX;
    vert.v = FilePositionY;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+Size;
    vert.y = ScreenPositionY;
    vert.z = ScreenPositionZ;
    vert.u = FilePositionX+0.076171875;
    vert.v = FilePositionY;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+Size;
    vert.z = ScreenPositionZ;
    vert.u = FilePositionX;
    vert.v = FilePositionY+0.1484375;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+Size;
    vert.y = ScreenPositionY+Size;
    vert.z = ScreenPositionZ;
    vert.u = FilePositionX+0.076171875;
    vert.v = FilePositionY+0.1484375;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

ScreenPositionX+=Size;
WhichChar++;
}

}
*/

void DrawColorBox(int ScreenPositionX, int ScreenPositionY, int ScreenPositionZ, int SizeX, int SizeY, char Color){

float Red, Green ,Blue;
if(Color == BlackColor) Red = Green = Blue = 0;
else if(Color == RedColor){ Red = 1.0f; Green = Blue = 0;}
else if(Color == GreenColor){ Green = 1.0f; Red = Blue = 0;}
else if(Color == BlueColor){ Blue = 1.0f; Green = Red = 0;}
else if(Color == YellowColor){ Green = Red = 1.0f; Blue = 0;}
else Red = Green = Blue = 1.0f;


    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 16, 16, LoadingBackGroundTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, Red, Green, Blue);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY;
    vert.z = ScreenPositionZ;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX;
    vert.y = ScreenPositionY;
    vert.z = ScreenPositionZ;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX;
    vert.y = ScreenPositionY+SizeY;
    vert.z = ScreenPositionZ;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = ScreenPositionX+SizeX;
    vert.y = ScreenPositionY+SizeY;
    vert.z = ScreenPositionZ;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

}

#define DrawColorBackGround(Color) DrawColorBox(0, 0, 0, ScreenSizeX, ScreenSizeY, Color)

void DrawColorLine(int StartPointX, int StartPointY, int EndPointX, int EndPointY, char Color){

float Red, Green ,Blue;
if(Color == 1) Red = Green = Blue = 0;
else if(Color == 2){ Red = 1.0f; Green = Blue = 0;}
else if(Color == 3){ Green = 1.0f; Red = Blue = 0;}
else if(Color == 4){ Blue = 1.0f; Green = Red = 0;}
else Red = Green = Blue = 1.0f;


    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 16, 16, LoadingBackGroundTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, Red, Green, Blue);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = StartPointX;
    vert.y = StartPointY;
    vert.z = TransparencyPositionZ;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = StartPointX+10;
    vert.y = StartPointY;
    vert.z = TransparencyPositionZ;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = EndPointX+5;
    vert.y = EndPointY;
    vert.z = TransparencyPositionZ;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = EndPointX;
    vert.y = EndPointY;
    vert.z = TransparencyPositionZ;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

}

void DrawAnotherSuperCoolEffect(int SpecialEffectTicks, int PositionX, int PositionY){

if(SpecialEffectTicks%3 == 0){

DrawColorLine(0, 0, PositionX-10, PositionY-10, 0);
DrawColorLine(320, 0, PositionX, PositionY-10, 0);
DrawColorLine(640, 0, PositionX+10, PositionY-10, 0);
DrawColorLine(640, 240, PositionX+10, PositionY, 0);
DrawColorLine(640, 480, PositionX+10, PositionY+10, 0);
DrawColorLine(320, 480, PositionX, PositionY+10, 0);
DrawColorLine(0, 480, PositionX-10, PositionY+10, 0);
DrawColorLine(0, 240, PositionX-10, PositionY, 0);

}

}

void DrawTransparentGreyBackGround(float TransparencyLevel){


    
    float r, g, b;
    
    //a = 0.6f;
    r = g = b = 0.1f;

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 16, 16, LoadingBackGroundTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(TransparencyLevel, r, g, b);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = 0;
    vert.y = 0;
    vert.z = TransparencyPositionZ;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 640;
    vert.y = 0;
    vert.z = TransparencyPositionZ;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 0;
    vert.y = 480;
    vert.z = TransparencyPositionZ;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 640;
    vert.y = 480;
    vert.z = TransparencyPositionZ;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

}