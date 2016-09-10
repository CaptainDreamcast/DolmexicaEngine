/* png example for KOS 1.1.x
 * Jeffrey McBeth / Morphogenesis
 * <mcbeth@morphogenesis.2y.net>
 *
 * Heavily borrowed from from 2-D example
 * AndrewK / Napalm 2001
 * <andrewk@napalm-x.com>
 */

#include <kos.h>
#include <png/png.h>
#include <zlib/zlib.h>

/* font data */
extern char wfont[];

/* textures */
pvr_ptr_t font_tex;
pvr_ptr_t back_tex;
char *data;

/* init background */
void back_init()
{
    back_tex = pvr_mem_malloc(512*512*2);
    png_to_texture("/rd/background.png", back_tex, PNG_NO_ALPHA);
}


/* draw background */
void draw_back(void)
{
    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_OP_POLY, PVR_TXRFMT_RGB565, 512, 512, back_tex, PVR_FILTER_BILINEAR);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = 1;
    vert.y = 1;
    vert.z = 1;
    vert.u = 0.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 640;
    vert.y = 1;
    vert.z = 1;
    vert.u = 1.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 1;
    vert.y = 480;
    vert.z = 1;
    vert.u = 0.0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 640;
    vert.y = 480;
    vert.z = 1;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));
}


/* base y coordinate */
int y = 0;

/* draw one frame */
void draw_frame(void)
{
    pvr_wait_ready();
    pvr_scene_begin();

    pvr_list_begin(PVR_LIST_OP_POLY);
    draw_back();
    pvr_list_finish();
    pvr_scene_finish();

    y--;
}

/* romdisk */
extern uint8 romdisk_boot[];
KOS_INIT_ROMDISK(romdisk_boot);

int main(void)
{
    int done = 0;

    /* init kos  */
    pvr_init_defaults();

    /* init background */
    back_init();


    /* keep drawing frames until start is pressed */
    while(!done) {
        MAPLE_FOREACH_BEGIN(MAPLE_FUNC_CONTROLLER, cont_state_t, st)
            if (st->buttons & CONT_START)
                done = 1;
        MAPLE_FOREACH_END()

	draw_frame();
    }

    return 0;
}

