/*

    SDL_framerate - test program for framerate manager

    Copyright (C) A. Schiffler, August 2001

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/
#ifdef DREAMCAST
#include <kos.h>
KOS_INIT_FLAGS(INIT_DEFAULT);
#endif

#ifdef GP32
#include <x_gp32.h>
#endif


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "SDL.h"

#include "SDL_framerate.h"
#include "SDL_gfxPrimitives.h"
#include "SDL_gfx_9x18B_fnt.h"

#include <png/png.h>

void ClearEvents()
{
	SDL_Event event;
	SDL_Delay(333);
	while(SDL_PollEvent(&event))
		SDL_Delay(50);
}

/*void HandleEvent()
{
	SDL_Event event;
*/
	/* Check for events */
/*        while ( SDL_PollEvent(&event) ) {
                        switch (event.type) {
			 case SDL_JOYBUTTONDOWN:
			 case SDL_KEYDOWN:
			 case SDL_QUIT:
                                        exit(0);
                                        break;

			}
	}
}*/
//GLOBAL VARIABLES. OR SOMETHING LIKE THAT.

int int_mode = 0; // Selects which mode is used
int location = 1; // Current Location.

// the different game modes. Dont ask me why.

#include "event1.c"
#include "MapSizeStore.c"
#include "startmenu.h"
#include "test.h"
#include "options.h"
#include "worldmap.h"
#include "BG_Layer.h"
#include "FG_Layer.h"
#include "C_Layer.h"
#include "Collission.c"

/* romdisk */
extern uint8 romdisk_boot[];
KOS_INIT_ROMDISK(romdisk_boot);

int main ( int argc, char *argv[] )
{
	SDL_Surface *screen;
	Uint32 video_flags = SDL_HWSURFACE | SDL_HWPALETTE | SDL_DOUBLEBUF;
	Uint32 video_bits=0;

#if defined(DREAMCAST) || defined(GP32)
	video_flags |= SDL_FULLSCREEN;
#ifdef GP32
	x_gp32_SetCPUSpeed_133();
	video_bits=8;
#else
	video_bits=16;
#endif
#endif

	if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK) < 0 ) {
		fprintf(stderr,
			"Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	screen = SDL_SetVideoMode(640, 480, video_bits, video_flags);
	if ( screen == NULL ) {
    fprintf(stderr, "Couldn't set %dx%dx%d video mode: %s\n",
					320, 240, video_bits, SDL_GetError());
		exit(1);
	}

	SDL_JoystickEventState(SDL_ENABLE);
	SDL_JoystickOpen(0);
	int game_loop = 1;
    int l,t;

while (game_loop == 1)
{
	if(int_mode == 0)
	{
	startmenu (screen); // 0 = Title screen
	}
	if(int_mode == 1)
	{
	MainOptions (screen); // 1 = Main Options
	}
	if(int_mode == 2)
	{
	WorldMap (screen); // 2 = World Map
	}
    if (int_mode == 99)
    {
    game_loop = 0; // 99 = END
    }
}
	return(0);
}
