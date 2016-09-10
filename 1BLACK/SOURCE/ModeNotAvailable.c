uint8 ModeNotAvailable(){

maple_device_t *cont;
cont_state_t *st;

uint8 ReadyToRock;
uint8 DurationTicks;
uint8 CurrentChar;
uint8 ButtonInputAllowed[MaxCharsOnScreen];

for(CurrentChar=CharacterOne; CurrentChar<MaxCharsOnScreen; CurrentChar++) ButtonInputAllowed[CurrentChar] = 0;

DurationTicks = 0;
ReadyToRock = 1;
while(ReadyToRock){


pvr_wait_ready();
pvr_scene_begin();
pvr_list_begin(PVR_LIST_TR_POLY);

DrawArray("MODE NOT AVAILABLE", 23, 224, LowerGuiPositionZ, 33, RedColor);

pvr_list_finish();
pvr_scene_finish();


for(CurrentChar=CharacterOne; CurrentChar<MaxCharsOnScreen; CurrentChar++){
if((cont = maple_enum_dev(CurrentChar, 0)) != NULL) {
st = (cont_state_t *)maple_dev_status(cont);

if(((st->buttons & CONT_START) || (st->buttons & CONT_A)) && ButtonInputAllowed[CurrentChar]){
ReadyToRock = 0;
}
if(!(st->buttons & CONT_START) && !(st->buttons & CONT_A) && !ButtonInputAllowed[CurrentChar]){
ButtonInputAllowed[CurrentChar] = 1;
}

}
}

DurationTicks++;
if(DurationTicks >= ModeNotAvailableDuration) ReadyToRock = 0;

}

return(FinalExitStage);
}