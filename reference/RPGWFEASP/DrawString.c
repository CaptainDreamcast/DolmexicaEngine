int DrawString(char* MessageContent, int MessageLength, int PositionX, int PositionY, int PieceWidth, int PieceHeight)
{
int WhichChar = 0;
char CurrentChar;
float TileSetPositionX = 0;
float TileSetPositionY = 0;
int Position = 0;
int StartPositionX = PositionX;
int StartPositionY = PositionY;
while (WhichChar <= MessageLength)
{
Position = 0;
TileSetPositionX = 0;
TileSetPositionY = 0;

Position = MessageContent[WhichChar] - 65 ;
if(MessageContent[WhichChar] == 0 || MessageContent[WhichChar] == 32){
Position = 26;
}

TileSetPositionX = Position * 0.078125;
while (TileSetPositionX >= 0.859375){
TileSetPositionX = TileSetPositionX - 0.859375;
TileSetPositionY = TileSetPositionY + 0.1171875;
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

    vert.x = PositionX+PieceWidth;
    vert.y = PositionY;
    vert.z = 5;
    vert.u = TileSetPositionX+0.07421875;
    vert.v = TileSetPositionY+0.00390625;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX;
    vert.y = PositionY+PieceHeight;
    vert.z = 5;
    vert.u = TileSetPositionX+0.00390625;
    vert.v = TileSetPositionY+0.11328125;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX+PieceWidth;
    vert.y = PositionY+PieceHeight;
    vert.z = 5;
    vert.u = TileSetPositionX+0.07421875;
    vert.v = TileSetPositionY+0.11328125;
    vert.flags = PVR_CMD_VERTEX_EOL;

    pvr_prim(&vert, sizeof(vert));

    PositionX = PositionX+PieceWidth;


    WhichChar++;
    }
    }
