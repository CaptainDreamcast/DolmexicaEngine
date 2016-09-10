int GameOver(char PointsArray[], int DrawPoints, int* WhichPlayerActive){

float r, g, b;
r = g = b = 0;

pvr_poly_cxt_t cxt;
pvr_poly_hdr_t hdr;
pvr_vertex_t vert;

maple_device_t *cont;
cont_state_t *st;

char OffTo = FinalExitStage;

int GameOverDuration = 300;
int GameOverDurationTicks = 1;

char DrawIntro = 1;
char ReadyToRock = 0;
char TimeToGoOn = 0;

int SuperCoolEffectTicks = 1;

char ButtonInputAllowed = 0;

while(TimeToGoOn == 0){



    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    
     if(DrawIntro == 1)
      { 
      DrawIntro = DrawSuperCoolEffect(SuperCoolEffectTicks);
      SuperCoolEffectTicks++;
      }
    
     if(ReadyToRock == 1)
      {
      TimeToGoOn = FadeToBlack(SuperCoolEffectTicks);
      SuperCoolEffectTicks++;
      }


    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 16, 16, LoadingBackGroundTexture, PVR_FILTER_BILINEAR);

    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, r, g, b);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = 0;
    vert.y = 0;
    vert.z = 1;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 640;
    vert.y = 0;
    vert.z = 1;
    vert.u = 1.0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 0;
    vert.y = 480;
    vert.z = 1;
    vert.u = 0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 640;
    vert.y = 480;
    vert.z = 1;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));

    DrawArray("GAME OVER", 50, 213, LowerGuiPositionZ, 55, RedColor);

    if(DrawPoints){
    DrawArray("FINAL SCORE: ", 50, 300, LowerGuiPositionZ, 30, YellowColor);
    DrawArray(PointsArray, 440, 300, LowerGuiPositionZ, 30, YellowColor);
    }

    pvr_list_finish();
    pvr_scene_finish();
    
    if(GameOverDurationTicks < GameOverDuration) GameOverDurationTicks++;
    else if(GameOverDurationTicks == GameOverDuration){
     SuperCoolEffectTicks = 1;
     ReadyToRock = 1;
     GameOverDurationTicks++;
     }


 if((cont = maple_enum_dev((*WhichPlayerActive), 0)) != NULL) {
  st = (cont_state_t *)maple_dev_status(cont);

  if ((st->buttons & CONT_START) && ButtonInputAllowed == 1) {
   TimeToGoOn = 1;
   }

  if(!(st->buttons & CONT_DPAD_DOWN) && !(st->buttons & CONT_DPAD_UP) && !(st->buttons & CONT_DPAD_RIGHT) && !(st->buttons & CONT_DPAD_LEFT) && !(st->buttons & CONT_START) && !(st->buttons & CONT_A) && !(st->buttons & CONT_B) && !(st->buttons & CONT_X) && !(st->buttons & CONT_Y) && ButtonInputAllowed == 0){
  ButtonInputAllowed = 1;
  }

  if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
   TimeToGoOn = 1;
  }

 }



}

return(OffTo);
}