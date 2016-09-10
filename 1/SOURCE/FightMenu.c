

    int FightMenuFunction(int FightStage, int LeftStageBorder, BackGroundHeaderStruct BackGroundHeaderData, BackGroundStruct BackGroundData[], BackGroundAnimationStruct BackGroundAnimationData[], pvr_ptr_t BackGroundTextures[], char CharacterName[][10], pvr_ptr_t CharacterTexture[], char AnimationBuffer[][10], char WhichAnimationFrame[], int DrawCharX[], int PosCharY[], char CharIsLeft[], int CharHealth[], short SpecialLeft[], char RealCharName[][20], char PointArray[][9], PaletteData CharPalette[], int StageGround, int ShadowPositionX, int ShadowPositionY, int CharacterTextureSizeDrawn, int CharacterTextureSizeReal[], char FirstTimerValue, char SecondTimerValue, pvr_ptr_t NewTimerTexture, TimerStruct TimerHeaderData, FontSingleCharacterStruct TimerCharacterData[], char CharWins[], SingleLifeBarStruct LifeBarData[], pvr_ptr_t LifeBarTexture[], pvr_ptr_t VictoryTexture[], OtherGuiStruct OtherGuiData[], char CharIsHuman[], int* Winner){

    maple_device_t *cont;
    cont_state_t *st;

    int Bluff;
    int CurrentChar;
    uint8 ButtonInputAllowed[MaxCharsOnScreen];
    uint8 OriginalButtonInputAllowed[MaxCharsOnScreen];

    int FightMenuStage;

    int WhichMenuPointSelected = 0;
    int MenuSelectedOption = -1;

    FightMenuPointStruct FightMenuPoint[FightMenuPointAmount];
    FightMenuBoxStruct FightMenuBox;


    ButtonInputAllowed[CharacterOne] = 0;
    ButtonInputAllowed[CharacterTwo] = 0;

    OriginalButtonInputAllowed[CharacterOne] = 0;
    OriginalButtonInputAllowed[CharacterTwo] = 0;

    sprintf(FightMenuPoint[0].ArrayToBePrinted, "CONTINUE");
    sprintf(FightMenuPoint[1].ArrayToBePrinted, "RESTART");
    sprintf(FightMenuPoint[2].ArrayToBePrinted, "CHAR SELECT");
    sprintf(FightMenuPoint[3].ArrayToBePrinted, "OPTIONS");
    sprintf(FightMenuPoint[4].ArrayToBePrinted, "EXIT");

    sprintf(FightMenuPoint[5].ArrayToBePrinted, "YES");
    sprintf(FightMenuPoint[6].ArrayToBePrinted, "NO");
    sprintf(FightMenuPoint[7].ArrayToBePrinted, "REALLY?");

    sprintf(FightMenuPoint[8].ArrayToBePrinted, "BGM: %d/15", VolumeCDDA);
    sprintf(FightMenuPoint[9].ArrayToBePrinted, "SFX: %d/255", VolumeSFX);
    sprintf(FightMenuPoint[10].ArrayToBePrinted, "BACK");

    for(Bluff = FightMenuMainArrayOffset; Bluff < FightMenuMainArrayUpperOffset; Bluff++) FightMenuPoint[Bluff].PositionX = 157;
    FightMenuPoint[5].PositionX = 157;
    FightMenuPoint[6].PositionX = 407;
    FightMenuPoint[7].PositionX = 205;

    FightMenuPoint[8].PositionX = 157;
    FightMenuPoint[9].PositionX = 157;
    FightMenuPoint[10].PositionX = 157;


    FightMenuPoint[0].PositionY = 141;
    FightMenuPoint[1].PositionY = 187;
    FightMenuPoint[2].PositionY = 231;
    FightMenuPoint[3].PositionY = 273;
    FightMenuPoint[4].PositionY = 314;
    for(Bluff = FightMenuCheckArrayOffset; Bluff < FightMenuCheckArrayUpperOffset-1; Bluff++) FightMenuPoint[Bluff].PositionY = 231;
    FightMenuPoint[7].PositionY = 141;
    FightMenuPoint[8].PositionY = 141;
    FightMenuPoint[9].PositionY = 187;
    FightMenuPoint[10].PositionY = 314;


    for(Bluff = 0; Bluff < FightMenuPointAmount; Bluff++) FightMenuPoint[Bluff].FontSize = 30;
    FightMenuPoint[8].FontSize = 25;
    FightMenuPoint[9].FontSize = 25;

    FightMenuBox.PositionX = 137;
    FightMenuBox.PositionY = 128;
    FightMenuBox.SizeX = 350;
    FightMenuBox.SizeY = 250;

    FightMenuStage = FightMenuMainIdentifier;

    while(FightStage == FightMenu){

    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
    
    DrawTransparentGreyBackGround(0.9);

    DrawTimer(NewTimerTexture, TimerHeaderData, TimerCharacterData, FirstTimerValue, SecondTimerValue);

    //DrawPoints(PointArray[CharacterOne], PointArray[CharacterTwo]);

    DrawColorBox(FightMenuBox.PositionX, FightMenuBox.PositionY, UpperGuiPositionZ1, FightMenuBox.SizeX, FightMenuBox.SizeY, BlackColor);

    if(FightMenuStage == FightMenuMainIdentifier){
    for(Bluff = FightMenuMainArrayOffset; Bluff < FightMenuMainArrayUpperOffset; Bluff++) DrawArray(FightMenuPoint[Bluff].ArrayToBePrinted, FightMenuPoint[Bluff].PositionX, FightMenuPoint[Bluff].PositionY, UpperGuiPositionZ2, FightMenuPoint[Bluff].FontSize, WhiteColor);
    DrawArray(FightMenuPoint[WhichMenuPointSelected].ArrayToBePrinted, FightMenuPoint[WhichMenuPointSelected].PositionX, FightMenuPoint[WhichMenuPointSelected].PositionY, UpperGuiPositionZ2, FightMenuPoint[WhichMenuPointSelected].FontSize, YellowColor);
    }
    else if(FightMenuStage == FightMenuCheckIdentifier){
    for(Bluff = FightMenuCheckArrayOffset; Bluff < FightMenuCheckArrayUpperOffset; Bluff++) DrawArray(FightMenuPoint[Bluff].ArrayToBePrinted, FightMenuPoint[Bluff].PositionX, FightMenuPoint[Bluff].PositionY, UpperGuiPositionZ2, FightMenuPoint[Bluff].FontSize, WhiteColor);
    DrawArray(FightMenuPoint[WhichMenuPointSelected].ArrayToBePrinted, FightMenuPoint[WhichMenuPointSelected].PositionX, FightMenuPoint[WhichMenuPointSelected].PositionY, UpperGuiPositionZ2, FightMenuPoint[WhichMenuPointSelected].FontSize, YellowColor);
    }
    else if(FightMenuStage == FightMenuOptionsIdentifier){
    for(Bluff = FightMenuOptionsArrayOffset; Bluff < FightMenuOptionsArrayUpperOffset; Bluff++) DrawArray(FightMenuPoint[Bluff].ArrayToBePrinted, FightMenuPoint[Bluff].PositionX, FightMenuPoint[Bluff].PositionY, UpperGuiPositionZ2, FightMenuPoint[Bluff].FontSize, WhiteColor);
    DrawArray(FightMenuPoint[WhichMenuPointSelected].ArrayToBePrinted, FightMenuPoint[WhichMenuPointSelected].PositionX, FightMenuPoint[WhichMenuPointSelected].PositionY, UpperGuiPositionZ2, FightMenuPoint[WhichMenuPointSelected].FontSize, YellowColor);
    }

    DrawCoolStage(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, BackGroundNoDrawAnimated);

    CurrentChar = CharacterOne;
    do{

    DrawArray(RealCharName[CurrentChar], OtherGuiData[CurrentChar].NamePositionX, OtherGuiData[CurrentChar].NamePositionY, LowerGuiPositionZ, OtherGuiData[CurrentChar].NameSizeX, 1);
    if(CharIsHuman[CurrentChar]) DrawArray(PointArray[CurrentChar], OtherGuiData[CurrentChar].ArrayPositionX, OtherGuiData[CurrentChar].ArrayPositionY, LowerGuiPositionZ, OtherGuiData[CurrentChar].ArraySizeX, YellowColor);
    else DrawArray("PRESS START", OtherGuiData[CurrentChar].ArrayPositionX, OtherGuiData[CurrentChar].ArrayPositionY, LowerGuiPositionZ, OtherGuiData[CurrentChar].ArraySizeX, YellowColor);
    DrawLifeBar(CharHealth[CurrentChar], SpecialLeft[CurrentChar], CharWins[CurrentChar], LifeBarData[CurrentChar], LifeBarTexture[CurrentChar], VictoryTexture[CurrentChar]);
    DrawCharLite(CharacterTexture[CurrentChar], DrawCharX[CurrentChar], PosCharY[CurrentChar], CharIsLeft[CurrentChar], CharPalette[CurrentChar], StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn, CharacterTextureSizeReal[CurrentChar]);

    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);    

    pvr_list_finish();
    pvr_scene_finish();

    CurrentChar = CharacterOne;
    do{
    if((cont = maple_enum_dev(CurrentChar, 0)) != NULL) {
    st = (cont_state_t *)maple_dev_status(cont);

    if(FightMenuStage == FightMenuMainIdentifier){

    if (((st->buttons & CONT_DPAD_UP)  || (st->joyy <= -64)) && ButtonInputAllowed[CurrentChar] == 1) {
            WhichMenuPointSelected --;
            if(WhichMenuPointSelected < 0) WhichMenuPointSelected = 0;
            ButtonInputAllowed[CurrentChar] = 0;
    }

    if(((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && ButtonInputAllowed[CurrentChar] == 1){

            WhichMenuPointSelected++;
            if(WhichMenuPointSelected > 4) WhichMenuPointSelected = 4;
            ButtonInputAllowed[CurrentChar] = 0;


    }

    if((st->buttons & CONT_A) && OriginalButtonInputAllowed[CurrentChar] == 1) {

            MenuSelectedOption = WhichMenuPointSelected;
            if(WhichMenuPointSelected == 0) FightMenuStage = FightMenuItsOverIdentifier;
            else if(WhichMenuPointSelected == 3){
            FightMenuStage = FightMenuOptionsIdentifier;
            WhichMenuPointSelected = FightMenuOptionsArrayOffset;
            }
            else{
            FightMenuStage = FightMenuCheckIdentifier;          
            WhichMenuPointSelected = FightMenuCheckArrayOffset;
            }
            OriginalButtonInputAllowed[CurrentChar] = 0;
			}


    }
    else if(FightMenuStage == FightMenuCheckIdentifier){


    if (((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && ButtonInputAllowed[CurrentChar] == 1) {
            WhichMenuPointSelected --;
            if(WhichMenuPointSelected < FightMenuCheckArrayOffset) WhichMenuPointSelected = FightMenuCheckArrayOffset;
            ButtonInputAllowed[CurrentChar] = 0;
    }

    if(((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && ButtonInputAllowed[CurrentChar] == 1){

            WhichMenuPointSelected++;
            if(WhichMenuPointSelected == (FightMenuCheckArrayUpperOffset-1)) WhichMenuPointSelected--;
            ButtonInputAllowed[CurrentChar] = 0;


    }

    if((st->buttons & CONT_A) && OriginalButtonInputAllowed[CurrentChar] == 1) {

            if(WhichMenuPointSelected == FightMenuCheckArrayOffset) FightMenuStage = FightMenuItsOverIdentifier;
            else{ 
            FightMenuStage = FightMenuMainIdentifier;          
            WhichMenuPointSelected = MenuSelectedOption;
            MenuSelectedOption = -1;
            }

            OriginalButtonInputAllowed[CurrentChar] = 0;
			}

    if((st->buttons & CONT_B) && OriginalButtonInputAllowed[CurrentChar] == 1) {

            FightMenuStage = FightMenuMainIdentifier;          
            WhichMenuPointSelected = MenuSelectedOption;
            MenuSelectedOption = -1;
            OriginalButtonInputAllowed[CurrentChar] = 0;
			}

    }
    else if(FightMenuStage == FightMenuOptionsIdentifier){

    if (((st->buttons & CONT_DPAD_UP)  || (st->joyy <= -64)) && ButtonInputAllowed[CurrentChar] == 1) {
            WhichMenuPointSelected --;
            if(WhichMenuPointSelected < FightMenuOptionsArrayOffset) WhichMenuPointSelected = FightMenuOptionsArrayOffset;
            ButtonInputAllowed[CurrentChar] = 0;
    }

    if(((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && ButtonInputAllowed[CurrentChar] == 1){

            WhichMenuPointSelected++;
            if(WhichMenuPointSelected == FightMenuOptionsArrayUpperOffset) WhichMenuPointSelected = FightMenuOptionsArrayUpperOffset;
            ButtonInputAllowed[CurrentChar] = 0;
    }

    if (((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && ButtonInputAllowed[CurrentChar] == 1) {

            if(WhichMenuPointSelected == FightMenuMusicOption){
            if(VolumeCDDA > 0){ 
            VolumeCDDA--;
            spu_cdda_volume(VolumeCDDA, VolumeCDDA);
            sprintf(FightMenuPoint[8].ArrayToBePrinted, "BGM: %d/15", VolumeCDDA);
            }
            ButtonInputAllowed[CurrentChar] = 0;
            }
            else if(WhichMenuPointSelected == FightMenuSoundEffectOption){
            if(VolumeSFX > 0){ 
            VolumeSFX--;
            sprintf(FightMenuPoint[9].ArrayToBePrinted, "SFX: %d/255", VolumeSFX);
            }
            }
    }

    if(((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && ButtonInputAllowed[CurrentChar] == 1){

            if(WhichMenuPointSelected == FightMenuMusicOption){
            if(VolumeCDDA < 15){ 
            VolumeCDDA++;
            spu_cdda_volume(VolumeCDDA, VolumeCDDA);
            sprintf(FightMenuPoint[8].ArrayToBePrinted, "BGM: %d/15", VolumeCDDA);
            }
            ButtonInputAllowed[CurrentChar] = 0;
            }
            else if(WhichMenuPointSelected == FightMenuSoundEffectOption){
            if(VolumeSFX < 255){ 
            VolumeSFX++;
            sprintf(FightMenuPoint[9].ArrayToBePrinted, "SFX: %d/255", VolumeSFX);
            }
            }
    }

    if((st->buttons & CONT_A) && OriginalButtonInputAllowed[CurrentChar] == 1) {

            if(WhichMenuPointSelected == (FightMenuOptionsArrayUpperOffset-1)) { 
            FightMenuStage = FightMenuMainIdentifier;          
            WhichMenuPointSelected = MenuSelectedOption;
            MenuSelectedOption = -1;
            }

            OriginalButtonInputAllowed[CurrentChar] = 0;
			}

    if((st->buttons & CONT_B) && OriginalButtonInputAllowed[CurrentChar] == 1) {

            FightMenuStage = FightMenuMainIdentifier;          
            WhichMenuPointSelected = MenuSelectedOption;
            MenuSelectedOption = -1;

            OriginalButtonInputAllowed[CurrentChar] = 0;
			}

    }



    if ((st->buttons & CONT_START) && OriginalButtonInputAllowed[CurrentChar] == 1) {
            FightStage = FightActualFight;
            OriginalButtonInputAllowed[CurrentChar] = 0;
			}


    if (!((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && !((st->buttons & CONT_DPAD_UP)  || (st->joyy <= -64)) && !((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && !((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && ButtonInputAllowed[CurrentChar] == 0) {
            ButtonInputAllowed[CurrentChar] = 1;
			}

    if (!(st->buttons & CONT_START) && !(st->buttons & CONT_X) && !(st->buttons & CONT_B) && !(st->buttons & CONT_A) && !(st->buttons & CONT_Y) && OriginalButtonInputAllowed[CurrentChar] == 0) {
            OriginalButtonInputAllowed[CurrentChar] = 1;
			}


    if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
    FightStage = FightShutDown;
    *Winner = StairWayToHeavenIdentifier;
    }
  
    }

    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);      

    if(FightMenuStage == FightMenuItsOverIdentifier){

    if(MenuSelectedOption == 0){
    FightStage = FightActualFight;
    }
    else if(MenuSelectedOption == 1){
    FightStage = FightEntireReset;
    }
    else if(MenuSelectedOption == 2){
    *Winner = SelectNewCharacterIdentifier;
    FightStage = FightShutDown;
    }
    else if(MenuSelectedOption == 3){
    WhichMenuPointSelected = FightMenuOptionsArrayOffset;
    FightMenuStage = FightMenuOptionsIdentifier;
    }
    else if(MenuSelectedOption == 4){
    FightStage = FightShutDown;
    }
    else MenuSelectedOption = -1;

    }


    }  
    return(FightStage);
    }