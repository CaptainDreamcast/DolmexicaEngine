if(location != -1)
{
int SizeX, SizeY;
GetMapSize(&SizeX, &SizeY, location);
int TileType[SizeY/40][SizeX/40];

if (location == 2) //Let's just call it a World Map, ok?
{
int TileSet [12][16] = {
1,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};
int Tile_SizeX = 0;
int Tile_SizeY = 0;
while(Tile_SizeX <= SizeX/40){
TileType[Tile_SizeY][Tile_SizeX] = TileSet[Tile_SizeY][Tile_SizeX];
Tile_SizeY++;
if(Tile_SizeY > SizeY/40){
Tile_SizeY = 0;
Tile_SizeX++;
}
}
}
if (location == 1) //Let's just call it a BIGGER World Map, ok?
{

int TileSet [24][32] = {
1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,
2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};
int Tile_SizeX = 0;
int Tile_SizeY = 0;
while(Tile_SizeX <= SizeX/40){
TileType[Tile_SizeY][Tile_SizeX] = TileSet[Tile_SizeY][Tile_SizeX];
Tile_SizeY++;
if(Tile_SizeY > SizeY/40){
Tile_SizeY = 0;
Tile_SizeX++;
}
}
}

int RightBorder = *PosCapX + 319;
int LeftBorder = *PosCapX - 320;
int UpBorder = *PosCapY - 240;
int DownBorder = *PosCapY + 239;
/*
if(LeftBorder < 0) {
LeftBorder = 0;
}
*/
if(LeftBorder >= SizeX-640) {
LeftBorder = SizeX-640;
}

int TileY,TileX;

TileX = 0-(*PosCapX%40);
TileY = 0-(*PosCapY%40);


 int WhichTileX = (LeftBorder/40);
 if(LeftBorder < 0){
 TileX = 0;
 WhichTileX = 0;
 }
 if(LeftBorder+640 >= SizeX){
 TileX = 0;
 WhichTileX = ((SizeX-640)/40);
 }
 int WhichTileY = (UpBorder/40);
  if(UpBorder < 0){
 TileY = 0;
 WhichTileY = 0;
 }
  if(UpBorder+480 >= SizeY){
 TileY = 0;
 WhichTileY = ((SizeY-480)/40);
 }
 while (TileY < 480) {
    int CurrentType = TileType[WhichTileY][WhichTileX];
    BGSingleTileDraw(CurrentType, TileX, TileY);
    WhichTileX++;

    if(*PosCapX%40 != 0 && LeftBorder > 0 && LeftBorder+640 < SizeX) {
    if (WhichTileX >= ((LeftBorder/40)+17))
    {
    WhichTileX = (LeftBorder/40);
    WhichTileY=WhichTileY+1;
    }
    }

    if(*PosCapX%40 == 0 || LeftBorder+640 >= SizeX || LeftBorder <= 0) {
    if (WhichTileX >= ((LeftBorder/40)+16))
    {
    WhichTileX = (LeftBorder/40);

/*
    if (LeftBorder+640 >= SizeX) {
    WhichTileX = ((SizeX-640)/40);
    }

    if (LeftBorder <= 0) {
    WhichTileX = 0;
    }
*/
    WhichTileY=WhichTileY+1;
    }
    }

    TileX = TileX + 40;
    if(TileX >= 640)
    {
        TileX = 0-(*PosCapX%40);
    if(LeftBorder < 0 || LeftBorder+640 >= SizeX){
    TileX = 0;
    }
        TileY = TileY + 40;
    }

 // if(TileY >= 480)
 //{
 //break;
 //}
 /*
 TileX = 0;
TileY = 0;
 int WhichTileX = 0;
 int WhichTileY = 0;
 while (TileY < 480) {
    int CurrentType = TileType[WhichTileY][WhichTileX];
    BGSingleTileDraw(screen, CurrentType, TileX, TileY);
    WhichTileX++;
    if (WhichTileX >= 16)
    {
    */

if(TileY >= 480)
 {
 //FGTileDraw(screen, DrawCapX, DrawCapY, PosCapX, PosCapY);
 }
 }
 }
