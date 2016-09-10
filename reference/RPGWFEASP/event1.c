

int EventCheck(int EventType, int* FromWhere, int DrawCapX, int DrawCapY,  int* CapX, int* CapY, int* CurrentLocation )
{
int l, EventPhase, EventTicks;
int EventActive = 1;
maple_device_t	*addr;
cont_state_t	*st;
if(*CurrentLocation == 1)
{

if(EventType == 1) {


  l=0;
  		while ( (addr = maple_enum_type(l++, MAPLE_FUNC_CONTROLLER)) ) {
			// Check for input
			st = (cont_state_t *)maple_dev_status(addr);

			// Exit
			if (st->buttons & CONT_A) {
            *CapX = 0;
            return(-1);
			}

		}


return(-1);
}

if(EventType == 2) {

EventPhase = 2;
EventTicks = 0;

while(EventActive == 1){
  int RunningAnimation = 39;
  pvr_wait_ready();
  pvr_scene_begin();
  pvr_list_begin(PVR_LIST_OP_POLY);
  int BG_Layer = BGTileDraw(CapX, CapY);
  pvr_list_finish();
  pvr_list_begin(PVR_LIST_TR_POLY);
  int FG_Layer = FGTileDraw(CapX, CapY);
  int C_Layer = CaptainDraw(DrawCapX, DrawCapY, *FromWhere, *CurrentLocation, RunningAnimation);
  int MessageWindow = DrawMessageWindow();
  DrawMessage();
  pvr_list_finish();

  pvr_scene_finish();
if(EventPhase == 2 ){
  l=0;
  		while ( (addr = maple_enum_type(l++, MAPLE_FUNC_CONTROLLER)) ) {
			// Check for input
			st = (cont_state_t *)maple_dev_status(addr);

			// Exit
			if (st->buttons & CONT_A) {
            *CapY = 0;
            EventActive = 0;
            return(-1);
			}

		}

}

  //SDL_Flip(screen);
}
return(-1);
}

if(EventType == 3) {


  l=0;
  		while ( (addr = maple_enum_type(l++, MAPLE_FUNC_CONTROLLER)) ) {
			// Check for input
			st = (cont_state_t *)maple_dev_status(addr);

			// Exit
			if (st->buttons & CONT_A) {
            return(0);
			}

		}


return(-1);
}
if(EventType == 4) {


  l=0;
  		while ( (addr = maple_enum_type(l++, MAPLE_FUNC_CONTROLLER)) ) {
			// Check for input
			st = (cont_state_t *)maple_dev_status(addr);

			// Exit
			if (st->buttons & CONT_A) {
            *CurrentLocation = 2;
            return(-1);
			}

		}


return(-1);
}

}

}

int EventHandler(int DrawCapX, int DrawCapY, int* CapX, int* CapY, int* CurrentLocation, int* FromWhere)
{

int l;



if( *CurrentLocation == 1 ){

int EventTileset[24][32] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

int WhichTileX = -1;
int WhichTileY = -1;
if(*CapY%40 == 0 && *CapX%40 < 10) {
WhichTileX = *CapX/40;
WhichTileY = *CapY/40;
}
if(*CapY%40 == 0 && *CapX%40 > 30) {
WhichTileX = (*CapX/40)+1;
WhichTileY = *CapY/40;
}
if(WhichTileX != -1)
{
int CurrentType = EventTileset[WhichTileY][WhichTileX];
if(CurrentType != 0) {
int CheckEvents = EventCheck(CurrentType, FromWhere, DrawCapX, DrawCapY, CapX, CapY, CurrentLocation);
if(CheckEvents != -1){
return(CheckEvents);
}
if(CheckEvents == -1){
return(-1);
}
}
}

 }
return(-1);
 }

