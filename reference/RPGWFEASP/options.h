
int MainOptions(SDL_Surface *screen)
{
    int l;
	int SelectedOption = 1;

 FPSmanager fpsm;

 /* Initialize variables */
 srand(SDL_GetTicks());
 maple_device_t	*addr;
 cont_state_t	*st;

 ClearEvents();
 SDL_initFramerate(&fpsm);
 SDL_setFramerate(&fpsm,8);
 while (1) {

//  HandleEvent();
  SDL_FillRect(screen,NULL,0);
  l=0;
  		while ( (addr = maple_enum_type(l++, MAPLE_FUNC_CONTROLLER)) ) {
			/* Check for input */
			st = (cont_state_t *)maple_dev_status(addr);

			/* Exit */
			if (st->buttons & CONT_START) {
				int_mode = 99;
				return(1);
			}
            if (st->buttons & CONT_B) {
				int_mode=2;
				return(1);
			}
            if (st->buttons & CONT_DPAD_DOWN) {
				if(SelectedOption <= 3)
				{
				SelectedOption++;
				}
			}
            if (st->buttons & CONT_DPAD_UP) {
				if(SelectedOption >= 2)
				{
				SelectedOption = SelectedOption-1;
				}
			}
		}

  SDL_FillRect(screen,NULL,0);
  char option1[]= "New Game";
  char option2[]= "Load Game";
  char option3[]= "Options";
  char option4[]= "LOLFAIL";
  {
  }
 gfxPrimitivesSetFont(&SDL_gfx_font_9x18B_fnt,9,18);
 if (SelectedOption == 1)
 {
 stringRGBA(screen,screen->w/4,(screen->h*1/5),option1,255,0,0,255);
 }
  if (SelectedOption != 1)
 {
 stringRGBA(screen,screen->w/4,(screen->h*1/5),option1,255,255,255,255);
 }
  if (SelectedOption == 2)
 {
 stringRGBA(screen,screen->w/4,(screen->h*2/5),option2,255,0,0,255);
 }
  if (SelectedOption != 2)
 {
 stringRGBA(screen,screen->w/4,(screen->h*2/5),option2,255,255,255,255);
 }
  if (SelectedOption == 3)
 {
 stringRGBA(screen,screen->w/4,(screen->h*3/5),option3,255,0,0,255);
 }
  if (SelectedOption != 3)
 {
 stringRGBA(screen,screen->w/4,(screen->h*3/5),option3,255,255,255,255);
 }
  if (SelectedOption == 4)
 {
 stringRGBA(screen,screen->w/4,(screen->h*4/5),option4,255,0,0,255);
 }
  if (SelectedOption != 4)
 {
 stringRGBA(screen,screen->w/4,(screen->h*4/5),option4,255,255,255,100);
 }

  SDL_Flip(screen);
  SDL_framerateDelay(&fpsm);

 }
 }

