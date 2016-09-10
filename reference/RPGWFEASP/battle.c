void BattleBGDraw(){
   pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_OP_POLY, PVR_TXRFMT_RGB565, 512, 512, BattleBG, PVR_FILTER_BILINEAR);
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

int NormalBattle()
{
maple_device_t	*addr;
cont_state_t	*st;
int health = 999;
int hattari = 99;
int BattlePart = 1;
int Ticks = 0;
int BattleLoop = 1;
if(BattleBG == 0)
{
BattleBG = pvr_mem_malloc(512*512*2);
png_to_texture("/rd/battlebackground.png", BattleBG, PNG_NO_ALPHA);
}
if(BattleEnemySprite == 0){
BattleEnemySprite = pvr_mem_malloc(256*256*2);
png_to_texture("/rd/enemy.png", BattleEnemySprite, PNG_FULL_ALPHA);
}
if(BattlePlayerSprite == 0){
BattlePlayerSprite = pvr_mem_malloc(256*256*2);
png_to_texture("/rd/player.png", BattlePlayerSprite, PNG_FULL_ALPHA);
}
if(UI_TileSet == 0){
UI_TileSet = pvr_mem_malloc(256*256*2);
png_to_texture("/rd/UI.png", UI_TileSet, PNG_FULL_ALPHA);
}
if(FontSet == 0){
FontSet = pvr_mem_malloc(256*256*2);
png_to_texture("/rd/font.png", FontSet, PNG_FULL_ALPHA);
}
while (BattleLoop == 1){
pvr_wait_ready();
if(BattlePart == 1){ //SELECT PRIMARY ACTION
MAPLE_FOREACH_BEGIN(MAPLE_FUNC_CONTROLLER, cont_state_t, st)
if ((st->buttons & CONT_B)) {
                pvr_mem_reset();
                BattlePlayerSprite = 0;
                BattleEnemySprite = 0;
                BattleBG = 0;
                FontSet = 0;
                UI_TileSet = 0;
				BattleLoop = 0;
				pvr_wait_ready();
				return;
				}
if ((st->buttons & CONT_A)) {
                BattlePart = 2;
				}
MAPLE_FOREACH_END()

pvr_scene_begin();
pvr_list_begin(PVR_LIST_OP_POLY);
BattleBGDraw();
pvr_list_finish();
pvr_list_begin(PVR_LIST_TR_POLY);
BattleCaptainDraw();
BattleEnemyDraw();
BattleHealthDraw(987,98);
BattleInputInterfaceDraw();
pvr_list_finish();

pvr_scene_finish();
}

if(BattlePart == 2){ // NORMAL ATTACK
pvr_wait_ready();
pvr_scene_begin();
pvr_list_begin(PVR_LIST_OP_POLY);
BattleBGDraw();
pvr_list_finish();
pvr_list_begin(PVR_LIST_TR_POLY);
BattleCaptainDraw();
BattleEnemyDraw();
BattleHealthDraw(987,98);
BattleInputInterfaceDraw();
pvr_list_finish();

pvr_scene_finish();
BattlePart = 1;
}


}

}
