pvr_ptr_t background_tileset;
pvr_ptr_t foreground_tileset;
pvr_ptr_t captaindc;
pvr_ptr_t UI_TileSet;
pvr_ptr_t FontSet;
pvr_ptr_t BattleBG;
pvr_ptr_t BattlePlayerSprite;
pvr_ptr_t BattleEnemySprite;

int WorldMap(SDL_Surface *screen)
{

int l;
 maple_device_t	*addr;
 cont_state_t	*st;
int MapSizeX, MapSizeY;
int DrawCapX = 40;
int DrawCapY = 40;
int PosCapX = 40;
int PosCapY = 40;
int FromWhere = 1;
int RunningAnimation = 39;


 while (1) {
 pvr_wait_ready();



GetMapSize(&MapSizeX, &MapSizeY, location);
//  HandleEvent();

  l=0;
      MAPLE_FOREACH_BEGIN(MAPLE_FUNC_CONTROLLER, cont_state_t, st)

			/* Exit */
			if ((st->buttons & CONT_START)) {
				int_mode = 99;
				pvr_mem_reset();
				return(1);
			}

            if ((st->buttons & CONT_Y)) {
				pvr_mem_reset();
				background_tileset = 0;
				foreground_tileset = 0;
				captaindc = 0;
				UI_TileSet = 0;
				FontSet = 0;
				NormalBattle();
			}

            if (st->buttons & CONT_DPAD_RIGHT) {

            if (st->buttons & CONT_B) {
				PosCapX = PosCapX+3;
			}

			else{
			PosCapX = PosCapX+1;
			}
            FromWhere =3;
            if ( (PosCapX)%40 == 10 || (PosCapX)%40 == 11 || (PosCapX)%40 == 12 ) {

            //#include "Collission.c"
            int CollisionDetect = CollissionDetect(&PosCapX, &PosCapY, FromWhere, location, MapSizeX, MapSizeY);
            }

			}
            if (st->buttons & CONT_DPAD_LEFT) {

            if (st->buttons & CONT_B) {
				PosCapX = PosCapX-3;
			}

			else{
			PosCapX = PosCapX-1;
			}
            if(PosCapX < -10)
            {
            PosCapX = -10;
            }
            FromWhere =4;
            if ( (PosCapX)%40 == 30 || (PosCapX)%40 == 29 || (PosCapX)%40 == 28 ) {

            //#include "Collission.c"
            int CollisionDetect = CollissionDetect(&PosCapX, &PosCapY, FromWhere, location, MapSizeX, MapSizeY);

            }


			}


            if (st->buttons & CONT_DPAD_DOWN) {


            if (st->buttons & CONT_B) {
				PosCapY = PosCapY+3;
			}

			else{
			PosCapY = PosCapY+1;
			}
            FromWhere =1;
            if ( (PosCapY-40)%40 == 0 || (PosCapY-40)%40 == 1 || (PosCapY-40)%40 == 2 ) {

            //#include "Collission.c"
            int CollisionDetect = CollissionDetect(&PosCapX, &PosCapY, FromWhere, location, MapSizeX, MapSizeY);

            }

			}
            if (st->buttons & CONT_DPAD_UP) {

            if (st->buttons & CONT_B) {
				PosCapY = PosCapY-3;
			}

			else{
			PosCapY = PosCapY-1;
			}
			if(PosCapY < 0)
			{
            PosCapY = 0;
			}
            FromWhere =2;
            if ( (PosCapY-40)%40 == 39 || (PosCapY-40)%40 == 38 || (PosCapY-40)%40 == 37 ) {

            //#include "Collission.c"
            int CollisionDetect = CollissionDetect(&PosCapX, &PosCapY, FromWhere, location, MapSizeX, MapSizeY);

            }

			}

            RunningAnimation++;
            if(RunningAnimation == 80){
                RunningAnimation = 0;
                }

            if (!(st->buttons & CONT_DPAD_RIGHT) && !(st->buttons & CONT_DPAD_LEFT) && !(st->buttons & CONT_DPAD_UP) && !(st->buttons & CONT_DPAD_DOWN)) {
            RunningAnimation = 39;
            }


        if(PosCapX <= 320) {
        DrawCapX = PosCapX;
        }
        if(PosCapX >= (MapSizeX-320) ) {
        DrawCapX = 640-(MapSizeX-PosCapX);
        }
        if(PosCapY <= 240) {
        DrawCapY = PosCapY;
        }
        if(PosCapY > (MapSizeY-240) ) {
        DrawCapY = 480-(MapSizeY-PosCapY);
        }
        MAPLE_FOREACH_END()

        if(background_tileset == 0)
        {
        background_tileset = pvr_mem_malloc(512*512*2);
        png_to_texture("/rd/background.png", background_tileset, PNG_FULL_ALPHA);
        }
        if(foreground_tileset == 0){
        foreground_tileset = pvr_mem_malloc(512*512*2);
        png_to_texture("/rd/foreground.png", foreground_tileset, PNG_FULL_ALPHA);
        }
        if(captaindc == 0){
        captaindc = pvr_mem_malloc(128*128*2);
        png_to_texture("/rd/captaindc.png", captaindc, PNG_FULL_ALPHA);
        }
        if(UI_TileSet == 0){
        UI_TileSet = pvr_mem_malloc(256*256*2);
        png_to_texture("/rd/UI.png", UI_TileSet, PNG_FULL_ALPHA);
        }
        if(FontSet == 0){
        FontSet = pvr_mem_malloc(256*256*2);
        png_to_texture("/rd/font.png", FontSet, PNG_FULL_ALPHA);
        }
        pvr_scene_begin();
        DrawLayers(DrawCapX, DrawCapY, &PosCapX, &PosCapY, FromWhere, location, RunningAnimation);
        pvr_scene_finish();
  int events = EventHandler(DrawCapX, DrawCapY, &PosCapX, &PosCapY, &location, &FromWhere);
  //int events = EventHandler(screen, &PosCapX, &PosCapY, &location, &FromWhere);
  if(events != -1){
  pvr_mem_reset();
  int_mode = events;
  return(1);
  }


 }
 }

