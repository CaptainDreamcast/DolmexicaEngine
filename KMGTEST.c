#include <kos.h>
KOS_INIT_FLAGS(INIT_DEFAULT);


//Standard Stuff
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


//For Texture stuff
#include <png/png.h>
#include <kmg/kmg.h>
#include <kos/img.h>
//Global Power VR Texture Declarations.
pvr_ptr_t BackBG1Texture;
kos_img_t img;
pvr_ptr_t dest;
//Debugging stuff. Can be remov

//The various game source files. Should get ordered.

//#include "FetchCharData.c"
/* romdisk */
extern uint8 romdisk_boot[];
KOS_INIT_ROMDISK(romdisk_boot);


void DrawStage(){


    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 128, 128, dest, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = 0;
    vert.y = 0;
    vert.z = 1;
    vert.u = 0.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 256;
    vert.y = 0;
    vert.z = 1;
    vert.u = 1.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 0;
    vert.y = 480;
    vert.z = 1;
    vert.u = 0.0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 256;
    vert.y = 256;
    vert.z = 1;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));
}

//Main Function. Duh.
int main ( int argc, char *argv[] )
{

    pvr_init_defaults();
    kmg_to_img("/rd/TEST.kmg", &img);


dest = pvr_mem_malloc(img.byte_count);
pvr_txr_load_kimg(&img, dest, 0);
while(1){
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    DrawStage();
    pvr_list_finish();
    pvr_scene_finish();
    }
   // Char1Texture = pvr_mem_malloc(128*128*2);


    //printf("Main Loop Restart.\n");

    pvr_mem_stats();
	return(0);
}
