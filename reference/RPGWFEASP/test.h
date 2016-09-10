
void works(SDL_Surface *screen)
{

	int l,t,int_mode;
 FPSmanager fpsm;

 /* Initialize variables */
 srand(SDL_GetTicks());
 maple_device_t	*addr;
 cont_state_t	*st;

 ClearEvents();
 SDL_initFramerate(&fpsm);
 SDL_setFramerate(&fpsm,60);

 while (1) {

//  HandleEvent();
  SDL_FillRect(screen,NULL,0);
  l=0;
  		while ( (addr = maple_enum_type(l++, MAPLE_FUNC_CONTROLLER)) ) {
			/* Check for input */
			st = (cont_state_t *)maple_dev_status(addr);

			/* Exit */
			if (st->buttons & CONT_START) {
				int_mode=2;
				exit(0);
				break;
			}

		}

  SDL_FillRect(screen,NULL,0);
  char char_title[] = "IT";
  char char_pressstart[]= "WORKS";
 gfxPrimitivesSetFont(&SDL_gfx_font_9x18B_fnt,9,18);
 stringRGBA(screen,screen->w/4,(screen->h*1/3),char_title,255,255,255,255);
 gfxPrimitivesSetFont(&SDL_gfx_font_9x18B_fnt,9,18);
 stringRGBA(screen,screen->w/3,(screen->h*2/3),char_pressstart,255,255,255,255);


  SDL_Flip(screen);
  SDL_framerateDelay(&fpsm);

 }
}
