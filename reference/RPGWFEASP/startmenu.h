
int startmenu(SDL_Surface *screen)
{

	int l,t,test;

 FPSmanager fpsm;

 /* Initialize variables */
 srand(SDL_GetTicks());
 maple_device_t	*addr;
 cont_state_t	*st;

 ClearEvents();
 SDL_initFramerate(&fpsm);
 SDL_setFramerate(&fpsm,60);
 test = 0;
 while (test ==0) {

//  HandleEvent();
  SDL_FillRect(screen,NULL,0);
  l=0;



		while ( (addr = maple_enum_type(l++, MAPLE_FUNC_CONTROLLER)) ) {
			/* Check for input */
			st = (cont_state_t *)maple_dev_status(addr);

			/* Exit */
			if (st->buttons & CONT_START) {
				test=1;
				return(int_mode=1);
			}

		}

  SDL_FillRect(screen,NULL,0);
  char char_title[] = "Generic Platformer";
  char char_pressstart[]= "Press Start";
 gfxPrimitivesSetFont(&SDL_gfx_font_9x18B_fnt,9,18);
 stringRGBA(screen,screen->w/4,(screen->h*1/3),char_title,255,255,255,255);
 gfxPrimitivesSetFont(&SDL_gfx_font_9x18B_fnt,9,18);
 stringRGBA(screen,screen->w/3,(screen->h*2/3),char_pressstart,255,255,255,255);


  SDL_Flip(screen);
  SDL_framerateDelay(&fpsm);

 }
 }

