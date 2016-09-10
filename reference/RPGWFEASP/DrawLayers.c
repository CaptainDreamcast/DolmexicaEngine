int DrawLayers(int DrawCapX, int DrawCapY, int* PosCapX, int* PosCapY, int FromWhere, int CurrentLocation, int RunningAnimation){


  pvr_list_begin(PVR_LIST_OP_POLY);
  int BG_Layer = BGTileDraw(PosCapX, PosCapY);
  pvr_list_finish();
  pvr_list_begin(PVR_LIST_TR_POLY);
  int FG_Layer = FGTileDraw(PosCapX, PosCapY);
  int C_Layer = CaptainDraw(DrawCapX, DrawCapY, FromWhere, CurrentLocation, RunningAnimation);
  pvr_list_finish();
}
