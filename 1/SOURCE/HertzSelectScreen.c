uint8 HertzSelectScreen(){

maple_device_t *cont;
cont_state_t *st;

FightMenuPointStruct SelectableArray[HertzVariationAmount];
LargerArrayStruct CurrentOptionArray;
LargerArrayStruct WarningArray[HertzWarningArrayAmount];

uint8 DirtyDeedsDoneDirtCheap;
uint8 WhichArraySelected = NtscHertz;
uint8 OriginalButtonInputAllowed[MaxCharsOnScreen];
uint8 ButtonInputAllowed[MaxCharsOnScreen];
uint8 ReadyToRock;


ButtonInputAllowed[CharacterOne] = 0;
ButtonInputAllowed[CharacterTwo] = 0;
OriginalButtonInputAllowed[CharacterOne] = 0;
OriginalButtonInputAllowed[CharacterTwo] = 0;

sprintf(SelectableArray[0].ArrayToBePrinted, "50HZ");
sprintf(SelectableArray[1].ArrayToBePrinted, "60HZ");
sprintf(CurrentOptionArray.ArrayToBePrinted, "CURRENT SELECTED OPTION: %s", SelectableArray[WhichArraySelected].ArrayToBePrinted);
sprintf(WarningArray[0].ArrayToBePrinted, "WARNING: 50HZ MODE WILL RESULT IN SLOWER GAMEPLAY!!");
sprintf(WarningArray[1].ArrayToBePrinted, "USE 60HZ IF POSSIBLE!");

for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<HertzVariationAmount; DirtyDeedsDoneDirtCheap++){
SelectableArray[DirtyDeedsDoneDirtCheap].FontSize = 50;
SelectableArray[DirtyDeedsDoneDirtCheap].PositionY = 150;
}

SelectableArray[0].PositionX = 80;
SelectableArray[1].PositionX = 360;

CurrentOptionArray.PositionX = 40;
CurrentOptionArray.PositionY = 335;
CurrentOptionArray.FontSize = 20;


for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<HertzWarningArrayAmount; DirtyDeedsDoneDirtCheap++){
WarningArray[DirtyDeedsDoneDirtCheap].FontSize = 11;
}

WarningArray[0].PositionX = 40;
WarningArray[0].PositionY = 375;

WarningArray[1].PositionX = 205;
WarningArray[1].PositionY = 390;

vid_set_mode(DM_640x480_PAL_IL, PM_RGB565);
ReadyToRock = 1;
while(ReadyToRock){


pvr_wait_ready();
pvr_scene_begin();
pvr_list_begin(PVR_LIST_TR_POLY);

for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<HertzVariationAmount; DirtyDeedsDoneDirtCheap++){
DrawArray(SelectableArray[DirtyDeedsDoneDirtCheap].ArrayToBePrinted, SelectableArray[DirtyDeedsDoneDirtCheap].PositionX, SelectableArray[DirtyDeedsDoneDirtCheap].PositionY, 1, SelectableArray[DirtyDeedsDoneDirtCheap].FontSize, WhiteColor);
}
DrawArray(SelectableArray[WhichArraySelected].ArrayToBePrinted, SelectableArray[WhichArraySelected].PositionX, SelectableArray[WhichArraySelected].PositionY, 2, SelectableArray[WhichArraySelected].FontSize, GreenColor);
DrawArray(CurrentOptionArray.ArrayToBePrinted, CurrentOptionArray.PositionX, CurrentOptionArray.PositionY, 1, CurrentOptionArray.FontSize, WhiteColor);

if(WhichArraySelected == PalHertz){
for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<HertzWarningArrayAmount; DirtyDeedsDoneDirtCheap++) DrawArray(WarningArray[DirtyDeedsDoneDirtCheap].ArrayToBePrinted, WarningArray[DirtyDeedsDoneDirtCheap].PositionX, WarningArray[DirtyDeedsDoneDirtCheap].PositionY, 1, WarningArray[DirtyDeedsDoneDirtCheap].FontSize, RedColor);
}

pvr_list_finish();
pvr_scene_finish();



for(DirtyDeedsDoneDirtCheap=CharacterOne; DirtyDeedsDoneDirtCheap<MaxCharsOnScreen; DirtyDeedsDoneDirtCheap++){


    if((cont = maple_enum_dev(DirtyDeedsDoneDirtCheap, 0)) != NULL) {
    st = (cont_state_t *)maple_dev_status(cont);


    if (((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && ButtonInputAllowed[DirtyDeedsDoneDirtCheap] == 1) {
    if(WhichArraySelected > 0){
    WhichArraySelected--;
    sprintf(CurrentOptionArray.ArrayToBePrinted, "CURRENT SELECTED OPTION: %s", SelectableArray[WhichArraySelected].ArrayToBePrinted);
    }
    ButtonInputAllowed[DirtyDeedsDoneDirtCheap] = 0;
    }

    if(((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && ButtonInputAllowed[DirtyDeedsDoneDirtCheap] == 1){
    if(WhichArraySelected < HertzVariationAmount-1){
    WhichArraySelected++;
    sprintf(CurrentOptionArray.ArrayToBePrinted, "CURRENT SELECTED OPTION: %s", SelectableArray[WhichArraySelected].ArrayToBePrinted);
    }
    ButtonInputAllowed[DirtyDeedsDoneDirtCheap] = 0;
    }


    if (((st->buttons & CONT_START) || (st->buttons & CONT_A)) && OriginalButtonInputAllowed[DirtyDeedsDoneDirtCheap] == 1) {
            if(WhichArraySelected == PalHertz) vid_set_mode(DM_640x480_PAL_IL, PM_RGB565);
            else vid_set_mode(DM_640x480_NTSC_IL, PM_RGB565);
            ReadyToRock = 0;
			}


    if (!((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && !((st->buttons & CONT_DPAD_UP)  || (st->joyy <= -64)) && !((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && !((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && ButtonInputAllowed[DirtyDeedsDoneDirtCheap] == 0) {
            ButtonInputAllowed[DirtyDeedsDoneDirtCheap] = 1;
			}

    if (!(st->buttons & CONT_START) && !(st->buttons & CONT_A) && OriginalButtonInputAllowed[DirtyDeedsDoneDirtCheap] == 0) {
           OriginalButtonInputAllowed[DirtyDeedsDoneDirtCheap] = 1;
			}


    if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
    return(0);
    }
  
}
}

}

return(1);
}