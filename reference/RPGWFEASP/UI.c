int DrawMessageWindow()
{
    int StartPositionX = 40;
    int StartPositionY = 280;
    int PositionX = 40;
    int PositionY = 280;
    int PieceWidth = 80;
    int PieceHeight = 40;
    float TileSetPositionX = 0;
    float TileSetPositionY = 0;

    while(PositionY <= 480){

    if((PositionX == StartPositionX) && (PositionY == StartPositionY)){
    TileSetPositionX = 0.0;
    TileSetPositionY = 0.0;
    }
    if((PositionX != StartPositionX) && (PositionY == StartPositionY)){
    TileSetPositionX = 0.5;
    TileSetPositionY = 0.25;
    }
    if((PositionX == 520) && (PositionY == StartPositionY)){
    TileSetPositionX = 0.25;
    TileSetPositionY = 0.0;
    }
    if((PositionX == StartPositionX) && (PositionY != StartPositionY)){
    TileSetPositionX = 0.75;
    TileSetPositionY = 0.0;
    }
    if((PositionX != StartPositionX) && (PositionY != StartPositionY)){
    TileSetPositionX = 0.5;
    TileSetPositionY = 0.0;
    }
    if((PositionX == 520) && (PositionY != StartPositionY)){
    TileSetPositionX = 0.0;
    TileSetPositionY = 0.5;
    }
    if((PositionX == StartPositionX) && (PositionY == 440)){
    TileSetPositionX = 0.0;
    TileSetPositionY = 0.25;
    }
    if((PositionX != StartPositionX) && (PositionY == 440)){
    TileSetPositionX = 0.75;
    TileSetPositionY = 0.25;
    }
    if((PositionX == 520) && (PositionY == 440)){
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
    vert.z = 4;
    vert.u = TileSetPositionX+0.00390625;
    vert.v = TileSetPositionY+0.00390625;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX+PieceWidth;
    vert.y = PositionY;
    vert.z = 4;
    vert.u = TileSetPositionX+0.24609375;
    vert.v = TileSetPositionY+0.00390625;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX;
    vert.y = PositionY+PieceHeight;
    vert.z = 4;
    vert.u = TileSetPositionX+0.00390625;
    vert.v = TileSetPositionY+0.24609375;
    pvr_prim(&vert, sizeof(vert));

    vert.x = PositionX+PieceWidth;
    vert.y = PositionY+PieceHeight;
    vert.z = 4;
    vert.u = TileSetPositionX+0.24609375;
    vert.v = TileSetPositionY+0.24609375;
    vert.flags = PVR_CMD_VERTEX_EOL;

    pvr_prim(&vert, sizeof(vert));

    PositionX = PositionX+PieceWidth;
    if(PositionX > 520){
    PositionX = StartPositionX;
    PositionY = PositionY+PieceHeight;
    }

    }

}

int DrawMessage() {
	/* file_t fd;
	int amt;
    size_t FileSize;
    printf("Print Something, faggot!\n");
	/* Read and print a file called README.TXT (if any)
	fd = fs_open("/rd/MessageString.txt", O_RDONLY);
	if (fd == 0) {
		printf("Can't open file README.TXT for reading.\r\n");
		return;
	}

    FileSize = fs_total(fd);


char* buffer;

amt = fs_read(fd, buffer, FileSize);


fs_close(fd); */
char MessageContent[] = "HOW ARE YOU| GENTLEMEN";
int MessageLength = 21;
int WhichChar = 0;
char CurrentChar;
float TileSetPositionX = 0;
float TileSetPositionY = 0;
int Position = 0;
int StartPositionX = 60;
int StartPositionY = 290;
int PositionX = 60;
int PositionY = 290;
int PieceWidth = 20;
int PieceHeight = 30;
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
    if(PositionX > 540){
    PositionX = StartPositionX;
    PositionY = PositionY+PieceHeight;
    }
    WhichChar++;
    if(MessageContent[WhichChar] == 124){
    PositionX = StartPositionX;
    PositionY = PositionY+PieceHeight;
    WhichChar++;
    }
    }

}
