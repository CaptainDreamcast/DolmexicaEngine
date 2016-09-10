int FightWinningAnimationFunction(int FightStage, int LeftStageBorder, BackGroundHeaderStruct BackGroundHeaderData, BackGroundStruct BackGroundData[], BackGroundAnimationStruct BackGroundAnimationData[], pvr_ptr_t BackGroundTextures[], char CharacterName[][10], CharacterTextureStruct CharacterTexture[], char AnimationBuffer[][10], char WhichAnimationFrame[], int DrawCharX[], int PosCharY[], char CharIsLeft[], PaletteData CharPalette[], int StageGround, int ShadowPositionX, int ShadowPositionY, int CharacterTextureSizeDrawn, int CharacterTextureSizeReal[], char CharIsHuman[], int WhichCharLost, int* Winner, int WhichMode, uint8 DrawCharDifferently[]){

pvr_ptr_t WinningAnimationTexture;
WinningAnimationStruct WinningAnimationData;

maple_device_t *cont;
cont_state_t *st;

sfxhnd_t WinningSoundEffect;

SoundStopNew(0);

WinningAnimationTexture = LoadNewWinningAnimation(&WinningAnimationData, CharIsHuman[(*Winner)], &WinningSoundEffect);

int CurrentChar;
int EndFightAnimation = 0;
int FightAnimationTicks = 1;  


while(EndFightAnimation == 0){ 
   
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);

    DrawCoolStage(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, BackGroundDrawAnimated);

    CurrentChar = CharacterOne;
    do{
    DrawCharLiteStandard();    
    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);

    DrawNewWinningAnimation(WinningAnimationData, WinningAnimationTexture);

    pvr_list_finish();
    pvr_scene_finish();

    if((cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER)) != NULL) {
    st = (cont_state_t *)maple_dev_status(cont);

    if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
    EndFightAnimation = 1;
    *Winner = StairWayToHeavenIdentifier;
    }
    }

    if(FightAnimationTicks%WinningAnimationData.Duration == 0){
    EndFightAnimation = 1;
    FightAnimationTicks = 0;
    }

    FightAnimationTicks++;
    if(FightAnimationTicks == 30000){
    FightAnimationTicks=1;
    }

}
pvr_mem_free(WinningAnimationTexture);
if(WinningSoundEffect != 0) snd_sfx_unload(WinningSoundEffect);

if(*Winner == StairWayToHeavenIdentifier) FightStage = FightShutDown;
else if(WhichMode == SurvivalModeIdentifier){ 
if(CharIsHuman[WhichCharLost] && !CharIsHuman[*Winner]) FightStage = FightShutDown;
else if(CharIsHuman[*Winner]){
CharIsHuman[WhichCharLost] = 0;
FightStage = FightSurvivalCalculateNextFight;
}
else FightStage = FightSurvivalCalculateNextFight;
}
else FightStage = FightWinQuote;

return(FightStage);

}