int FightWinQuoteFunction(int FightStage, int LeftStageBorder, BackGroundHeaderStruct BackGroundHeaderData, BackGroundStruct BackGroundData[], BackGroundAnimationStruct BackGroundAnimationData[], pvr_ptr_t BackGroundTextures[], char CharacterName[][10], CharacterTextureStruct CharacterTexture[], char AnimationBuffer[][10], char WhichAnimationFrame[], int DrawCharX[], int PosCharY[], char CharIsLeft[], PaletteData CharPalette[], int StageGround, int ShadowPositionX, int ShadowPositionY, int CharacterTextureSizeDrawn, int CharacterTextureSizeReal[], int* Winner, char WinnerName[], char CharIsHuman[], int WhichMode, uint8 DrawCharDifferently[]){


    pvr_ptr_t WinPortraitTexture;

    maple_device_t *cont;
    cont_state_t *st;

    int CurrentChar;

    char ButtonInputAllowed[MaxCharsOnScreen];

    int EndFightAnimation = 0;
    int FightAnimationTicks = 1;  

    WinQuoteStruct WinQuoteData;
    char* ActualQuote;
   
    for(CurrentChar=CharacterOne; CurrentChar<MaxCharsOnScreen; CurrentChar++) ButtonInputAllowed[CurrentChar] = 0;

    WinPortraitTexture = pvr_mem_malloc(512*512*2);
    ActualQuote = (char*) malloc(ProllyMaximumWinQuoteSize);

    if((WhichMode == StoryModeIdentifier && CharIsHuman[*Winner]) || !ReadNewWinStuff(WinnerName, &WinQuoteData, ActualQuote, &WinPortraitTexture)) EndFightAnimation = 1;

while(EndFightAnimation == 0){ 
 
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);

    DrawCoolStage(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, BackGroundNoDrawAnimated);

    CurrentChar = CharacterOne;
    do{
    DrawCharLiteStandard();    
    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);

    DrawNewWinPortrait(WinQuoteData, WinPortraitTexture);
    DrawNewWinQuote(WinQuoteData, ActualQuote);
    DrawTransparentGreyBackGround(0.8);

    pvr_list_finish();
    pvr_scene_finish();


for(CurrentChar=CharacterOne; CurrentChar<MaxCharsOnScreen; CurrentChar++){

    if((cont = maple_enum_dev(CurrentChar, 0)) != NULL) {
    st = (cont_state_t *)maple_dev_status(cont);

    if((st->buttons & CONT_START) && ButtonInputAllowed[CurrentChar]){
    EndFightAnimation = 1;
    }

    if(!(st->buttons & CONT_START) && !ButtonInputAllowed[CurrentChar]){
    ButtonInputAllowed[CurrentChar] = 1;    
    }

    if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
    EndFightAnimation = 1;
    *Winner = StairWayToHeavenIdentifier;
    }
    }

}

    
    if(FightAnimationTicks%WinQuoteDuration == 0){
    EndFightAnimation = 1;
    FightAnimationTicks = 0;
    }

    FightAnimationTicks++;
    if(FightAnimationTicks == 30000){
    FightAnimationTicks=1;
    }

}

if(*Winner == StairWayToHeavenIdentifier) FightStage = FightShutDown;
else FightStage = FightPreContinueAnimation;

pvr_mem_free(WinPortraitTexture);
free(ActualQuote);

return(FightStage);

}