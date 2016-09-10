int BattleInputInterfaceDraw() {
int PositionX = 316;
int PositionY = 324;
int DrawCycle = 1;
float TileSetPositionX = 0;
float TileSetPositionY = 0;

while(DrawCycle <= 4){

if(DrawCycle == 1){
TileSetPositionX = 0;
TileSetPositionY = 0.75;
}
if(DrawCycle == 2){
TileSetPositionX = 0.75;
TileSetPositionY = 0.5;
}
if(DrawCycle == 3){
TileSetPositionX = 0.5;
TileSetPositionY = 0.5;
}
if(DrawCycle == 4){
TileSetPositionX = 0.25;
TileSetPositionY = 0.5;
}

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 256, 256, UI_TileSet, PVR_FILTER_BILINEAR);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = PositionX;
    vert.y = PositionY;
    vert.z = 2;
    vert.u = TileSetPositionX+0.00390625;
    vert.v = TileSetPositionY+0.00390625;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX+128;
    vert.y = PositionY;
    vert.z = 2;
    vert.u = TileSetPositionX+0.24609375;
    vert.v = TileSetPositionY+0.00390625;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX;
    vert.y = PositionY+64;
    vert.z = 2;
    vert.u = TileSetPositionX+0.00390625;
    vert.v = TileSetPositionY+0.24609375;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX+128;
    vert.y = PositionY+64;
    vert.z = 2;
    vert.u = TileSetPositionX+0.24609375;
    vert.v = TileSetPositionY+0.24609375;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

    PositionX = PositionX+128;
    if(PositionX >= 572){
    PositionX = 316;
    PositionY = PositionY+64;
    }

DrawCycle++;
}

DrawCycle = 1;
TileSetPositionX = 0;
TileSetPositionY = 0;

while(DrawCycle <= 4){

if(DrawCycle == 1){ //X
PositionX = 412;
PositionY = 372;
TileSetPositionX = 0.25;
TileSetPositionY = 0.875;
}
if(DrawCycle == 2){ //B
PositionX = 444;
PositionY = 372;
TileSetPositionX = 0.5;
TileSetPositionY = 0.75;
}
if(DrawCycle == 3){ //Y
PositionX = 428;
PositionY = 356;
TileSetPositionX = 0.5;
TileSetPositionY = 0.875;
}
if(DrawCycle == 4){ //A
PositionX = 428;
PositionY = 388;
TileSetPositionX = 0.25;
TileSetPositionY = 0.75;
}

    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 256, 256, UI_TileSet, PVR_FILTER_BILINEAR);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = PositionX;
    vert.y = PositionY;
    vert.z = 3;
    vert.u = TileSetPositionX;//+0.00390625;
    vert.v = TileSetPositionY;//+0.00390625;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX+32;
    vert.y = PositionY;
    vert.z = 3;
    vert.u = TileSetPositionX+0.125;//+0.12109375;
    vert.v = TileSetPositionY;//+0.00390625;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX;
    vert.y = PositionY+32;
    vert.z = 3;
    vert.u = TileSetPositionX;//+0.00390625;
    vert.v = TileSetPositionY+0.125;//+0.12109375;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX+32;
    vert.y = PositionY+32;
    vert.z = 3;
    vert.u = TileSetPositionX+0.125;//+0.12109375;
    vert.v = TileSetPositionY+0.125;//+0.12109375;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));



DrawCycle++;
}
char FightString[5] = "FIGHT";
char RunString[3] = "RUN";
char ItemString[4] = "ITEM";
char HattariString[5] = "SKILL";
DrawString(FightString, 4, 419, 415, 10, 15);
DrawString(RunString, 2, 429, 336, 10, 15);
DrawString(ItemString, 3, 481, 372, 10, 15);
DrawString(HattariString, 4, 357, 372, 10, 15);
}

int BattleHealthDraw(int Health, int Hattari)
{
int DrawCycle = 1;
int PositionX = 0;
int PositionY = 0;
float TileSetPositionX = 0.75;
float TileSetPositionY = 0.0;

while (DrawCycle <= 8)
{

if(DrawCycle <= 3){
TileSetPositionX = 0.5;
TileSetPositionY = 0;
}
if(DrawCycle == 4){
TileSetPositionX = 0;
TileSetPositionY = 0.5;
}
if(DrawCycle > 4 && DrawCycle < 8){
TileSetPositionX = 0.75;
TileSetPositionY = 0.25;
}
if(DrawCycle == 8){
TileSetPositionX = 0.25;
TileSetPositionY = 0.25;
}
pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 256, 256, UI_TileSet, PVR_FILTER_BILINEAR);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = PositionX;
    vert.y = PositionY;
    vert.z = 2;
    vert.u = TileSetPositionX+0.00390625;
    vert.v = TileSetPositionY+0.00390625;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX+64;
    vert.y = PositionY;
    vert.z = 2;
    vert.u = TileSetPositionX+0.24609375;
    vert.v = TileSetPositionY+0.00390625;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX;
    vert.y = PositionY+64;
    vert.z = 2;
    vert.u = TileSetPositionX+0.00390625;
    vert.v = TileSetPositionY+0.24609375;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX+64;
    vert.y = PositionY+64;
    vert.z = 2;
    vert.u = TileSetPositionX+0.24609375;
    vert.v = TileSetPositionY+0.24609375;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));
    PositionX = PositionX +64;

    if (PositionX == 256){
        PositionX = 0;
        PositionY = PositionY + 64;
        }
    DrawCycle++;
}
DrawCycle = 1;
PositionX = 8;
PositionY = 10;
int SingleNumber;


while(DrawCycle <= 14) {

if(DrawCycle == 1){
TileSetPositionX = 0;
TileSetPositionY = 0.1171875;
}
if(DrawCycle == 8){
TileSetPositionX = 0.546875;
TileSetPositionY = 0;
}
if(DrawCycle == 2 || DrawCycle == 9){
TileSetPositionX = 0.3125;
TileSetPositionY = 0.1171875;
}
if(DrawCycle == 3 || DrawCycle == 10){
TileSetPositionX = 0.3125 ;
TileSetPositionY = 0.703125;
}
if(DrawCycle == 4 || DrawCycle == 11){
TileSetPositionX = 0.859375;
TileSetPositionY = 0.1171875;
}
if(DrawCycle == 5 || DrawCycle == 12){
TileSetPositionY = 0.8203125;
SingleNumber = Health/100;
TileSetPositionX = SingleNumber *  0.078125;
if(SingleNumber == 0){
TileSetPositionX = TileSetPositionX = 0.859375;
}
while(Health >= 100){
Health = Health -100;
}
}
if(DrawCycle == 6 || DrawCycle == 13){
TileSetPositionY = 0.8203125;
SingleNumber = Health/10;
TileSetPositionX = SingleNumber *  0.078125;
while(Health >= 10){
Health = Health -10;
}
}
if(DrawCycle == 7 || DrawCycle == 14){
TileSetPositionY = 0.8203125;
SingleNumber = Health;
TileSetPositionX = SingleNumber *  0.078125;
Health = Hattari;
}



pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 256, 256, FontSet, PVR_FILTER_BILINEAR);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = PositionX;
    vert.y = PositionY;
    vert.z = 5;
    vert.u = TileSetPositionX+0.00390625;
    vert.v = TileSetPositionY+0.00390625;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX+30;
    vert.y = PositionY;
    vert.z = 5;
    vert.u = TileSetPositionX+0.07421875;
    vert.v = TileSetPositionY+0.00390625;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX;
    vert.y = PositionY+45;
    vert.z = 5;
    vert.u = TileSetPositionX+0.00390625;
    vert.v = TileSetPositionY+0.11328125;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX+30;
    vert.y = PositionY+45;
    vert.z = 5;
    vert.u = TileSetPositionX+0.07421875;
    vert.v = TileSetPositionY+0.11328125;
    vert.flags = PVR_CMD_VERTEX_EOL;

    pvr_prim(&vert, sizeof(vert));

    PositionX = PositionX+30;
    if(PositionX >= 218){
    PositionX = 8;
    PositionY = PositionY+45;
    }


    DrawCycle++;
}

}
