int CollissionDetect(int* CapX, int* CapY, int FromWhere, int CurrentLocation, int MapSizeX, int MapSizeY)
{

int TileType[MapSizeY][MapSizeX];

if(CurrentLocation == 1){
int TileSet [24][32] = {
1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,

1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,

1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,

1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,

1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,

1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,
1,0, 0,0, 0,1, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,

1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,

1,0, 1,1, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,

1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,

1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,

1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,

1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,1,
1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1,
};
int TileSizeX = 0;
int TileSizeY = 0;
while(TileSizeX <= MapSizeX/40){
TileType[TileSizeY][TileSizeX] = TileSet[TileSizeY][TileSizeX];
TileSizeY++;
if(TileSizeY > MapSizeY/40){
TileSizeY = 0;
TileSizeX++;
}
}
}

if(CurrentLocation == 2){
int TileSet [12][16] = {
1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
1,0, 0,0, 0,1, 0,0, 0,0, 0,0, 0,0, 0,0
};
int TileSizeX = 0;
int TileSizeY = 0;
while(TileSizeX <= MapSizeX/40){
TileType[TileSizeY][TileSizeX] = TileSet[TileSizeY][TileSizeX];
TileSizeY++;
if(TileSizeY > MapSizeY/40){
TileSizeY = 0;
TileSizeX++;
}
}
}
//int CollissionDetect = 0;
int TileX, TileY;
if(FromWhere==1) //DOWN
{
TileY = (*CapY+40)/40;
if(TileY >= (MapSizeY/40))
{
            if(*CapY%40 == 0)
            {
            *CapY = *CapY-1;
            }
            if(*CapY%40 == 1)
            {
            *CapY = *CapY-2;
            }
            if(*CapY%40 == 2)
            {
            *CapY = *CapY-3;
            }

}
if(*CapX%40 <= 30 && *CapX%40 >= 0 && TileType[TileY][(*CapX/40)] == 1 )
{
            if(*CapY%40 == 0)
            {
            *CapY = *CapY-1;
            }
            if(*CapY%40 == 1)
            {
            *CapY = *CapY-2;
            }
            if(*CapY%40 == 2)
            {
            *CapY = *CapY-3;
            }

//CollissionDetect = 1;
//TileX = (CapX+10)/40;
}
if(*CapX%40 <= 39 && *CapX%40 >= 10 && TileType[TileY][((*CapX/40)+1)] == 1 )
{
            if(*CapY%40 == 0)
            {
            *CapY = *CapY-1;
            }
            if(*CapY%40 == 1)
            {
            *CapY = *CapY-2;
            }
            if(*CapY%40 == 2)
            {
            *CapY = *CapY-3;
            }

//CollissionDetect = 1;
//TileX = (CapX+20)/40;
}
//if(TileType[TileY][TileX] == 1)
//{
//CollissionDetect = 1;
//}

}

if(FromWhere==2) //UP
{

TileY = (*CapY)/40;
if(TileY == 0)
{
            if(*CapY%40 == 39)
            {
            *CapY = *CapY+1;
            }
            if(*CapY%40 == 38)
            {
            *CapY = *CapY+2;
            }
            if(*CapY%40 == 37)
            {
            *CapY = *CapY+3;
            }
}
if(*CapX%40 <= 30 && *CapX%40 >= 0 && TileType[TileY][(*CapX/40)] == 1 )
{
            if(*CapY%40 == 39)
            {
            *CapY = *CapY+1;
            }
            if(*CapY%40 == 38)
            {
            *CapY = *CapY+2;
            }
            if(*CapY%40 == 37)
            {
            *CapY = *CapY+3;
            }
//CollissionDetect = 1;
//TileX = (CapX+10)/40;
}
if(*CapX%40 <= 39 && *CapX%40 >= 10 && TileType[TileY][((*CapX/40)+1)] == 1 )
{
            if(*CapY%40 == 39)
            {
            *CapY = *CapY+1;
            }
            if(*CapY%40 == 38)
            {
            *CapY = *CapY+2;
            }
            if(*CapY%40 == 37)
            {
            *CapY = *CapY+3;
            }
//CollissionDetect = 1;
//TileX = (CapX+20)/40;
}

/*
TileY = CapY/20;
TileX = (CapX+10)/20;

if(TileType[TileY][TileX] == 1)
{
CollissionDetect = 1;
}
*/
}

if(FromWhere==3) //RIGHT
{

TileX = (((*CapX+30)/40));
if(TileType[((*CapY/40)+1)][TileX] == 1 || TileType[*CapY/40][TileX] == 1 || TileX >= (MapSizeX/40))
{
            if(*CapX%40 == 10)
            {
            *CapX = *CapX-1;
            }
            if(*CapX%40 == 11)
            {
            *CapX = *CapX-2;
            }
            if(*CapX%40 == 12)
            {
            *CapX = *CapX-3;
            }

//CollissionDetect = 1;
//TileX = (CapX+10)/40;

}
/*
TileY = (CapY)/20;
TileX = (CapX+20)/20;
if(TileType[TileY][TileX] == 1)
{
CollissionDetect = 1;
}
*/
}


if(FromWhere==4) //LEFT
{

TileX = (((*CapX)/40));
if(TileType[((*CapY/40)+1)][TileX] == 1 || TileType[*CapY/40][TileX] == 1 )
{

            if(*CapX%40 == 30)
            {
            *CapX = *CapX+1;
            }
            if(*CapX%40 == 29)
            {
            *CapX = *CapX+2;
            }
            if(*CapX%40 == 28)
            {
            *CapX = *CapX+3;
            }
//TileX = (CapX+10)/40;

}
/*
TileY = (CapY)/20;
TileX = (CapX+20)/20;
if(TileType[TileY][TileX] == 1)
{
CollissionDetect = 1;
}
*/
}
else{
return(1);
}
}
