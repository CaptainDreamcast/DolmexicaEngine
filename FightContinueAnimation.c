int FightContinueAnimationFunction(int FightStage, int LeftStageBorder, BackGroundHeaderStruct BackGroundHeaderData, BackGroundStruct BackGroundData[], BackGroundAnimationStruct BackGroundAnimationData[], pvr_ptr_t BackGroundTextures[], char CharacterName[][10], CharacterTextureStruct CharacterTexture[], char AnimationBuffer[][10], char WhichAnimationFrame[], int DrawCharX[], int PosCharY[], char CharIsLeft[], PaletteData CharPalette[], int StageGround, int ShadowPositionX, int ShadowPositionY, int CharacterTextureSizeDrawn, int CharacterTextureSizeReal[], sfxhnd_t FightAnimationSoundEffect[][MaxFightAnimationSoundEffect], int WhichCharLost, TimerStruct TimerHeaderData, FontSingleCharacterStruct TimerCharacterData[], pvr_ptr_t NewTimerTexture, int* Winner, char PointArray[][SurvivalModeBeatableEnemyArrayLength], uint16 FightAnimationFlags, uint8 DrawCharDifferently[]){

maple_device_t *cont;
cont_state_t *st;

pvr_ptr_t FightAnimationTexture;

char FirstTimerValue = 9;
int TimerTicks = 1;
int TimerSpeed = 60;

int CurrentChar;

int FightAnimationTicks = 1;
char FightAnimationSpeed = 60;
int WhichFightAnimationFrame = 1;
short FightAnimationSizeX = 256;
short FightAnimationSizeY = 256;
int FightAnimationTextureSizeX = 256;
int FightAnimationTextureSizeY = 256;
short FightAnimationScreenPositionX = 0;
short FightAnimationScreenPositionY = 0;
char FightAnimationID = 0;
char EndFightAnimation = 0;
char MountPoint[40];
short FightAnimationVoiceClipChecker = 0;
uint8 TextureType;

int ButtonInputAllowed1 = 0;

if(!(FightAnimationFlags & ContinueAnimationFlag)) return(FightShutDown);
sprintf(MountPoint, "CONTINUEANIMATION");

if(LoadPalette8(MountPoint, 0, AdditionalAnimationPalette)) TextureType = PaletteType;
else TextureType = RedGreenBlueType;

FightAnimationTexture = pvr_mem_malloc(FightAnimationTextureSizeX*FightAnimationTextureSizeY*2);

while(FightStage == FightContinueAnimation){

    ReadNormalAnimation(WhichFightAnimationFrame, &FightAnimationID, &FightAnimationSpeed, &FightAnimationTextureSizeX, &FightAnimationTextureSizeY, &FightAnimationSizeX, &FightAnimationSizeY, &FightAnimationScreenPositionX, &FightAnimationScreenPositionY, &FightAnimationVoiceClipChecker, &EndFightAnimation, MountPoint);
    if(FightAnimationVoiceClipChecker != 0) {snd_sfx_play(FightAnimationSoundEffect[ContinueAnimationSoundEffectIdentifier][FightAnimationVoiceClipChecker], VolumeSFX, 128); FightAnimationVoiceClipChecker = 0;}

    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);

    DrawCoolStage(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, BackGroundDrawAnimated);

    CurrentChar = CharacterOne;
    do{
    DrawCharLiteStandard();    
    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue); 

    DrawTransparentGreyBackGround(0.8);
    DrawSomeFunkyAnimation(FightAnimationID, FightAnimationSizeX, FightAnimationSizeY, FightAnimationScreenPositionX, FightAnimationScreenPositionY, MountPoint, FightAnimationTexture, TextureType);
    DrawContinueCountDown(FirstTimerValue, 200, 150, 200, TimerHeaderData, TimerCharacterData, NewTimerTexture, TextureType);

    pvr_list_finish();
    pvr_scene_finish();


    if((cont = maple_enum_dev(WhichCharLost, 0)) != NULL) {
    st = (cont_state_t *)maple_dev_status(cont);


    if ((st->buttons & CONT_START) && ButtonInputAllowed1 == 1) {
            FightFadingOut(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, CharacterName, CharacterTexture, AnimationBuffer, WhichAnimationFrame, DrawCharX, PosCharY, CharIsLeft, CharPalette, StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn, CharacterTextureSizeReal, DrawCharDifferently);

            sprintf(PointArray[WhichCharLost], "00000");

            FightStage = FightEntireReset;
            ButtonInputAllowed1 = 0;
			}

    if ((st->buttons & CONT_A) && ButtonInputAllowed1 == 1) {

            if(FirstTimerValue > 0 ){
            FirstTimerValue--;
            TimerTicks = 1;
            }

            ButtonInputAllowed1 = 0;
			}

    if (!(st->buttons & CONT_START) && !(st->buttons & CONT_A) && ButtonInputAllowed1 == 0) {

            ButtonInputAllowed1 = 1;

			}

    if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
    FightStage = FightShutDown;
    *Winner = StairWayToHeavenIdentifier;
    }

 }

    if(TimerTicks%TimerSpeed == 0){
    FirstTimerValue--;
    if(FirstTimerValue<0) FightStage = FightShutDown;
    }

    if(FightAnimationTicks%FightAnimationSpeed == 0){
    if(EndFightAnimation == 0) WhichFightAnimationFrame++;
    else{
    WhichFightAnimationFrame = EndFightAnimation;
    EndFightAnimation = 0;
    }
    }

    FightAnimationTicks++;
    if(FightAnimationTicks == 30000){
    FightAnimationTicks=1;
    }

    TimerTicks++;
    if(TimerTicks == 30000){
    TimerTicks=1;
    }
}

pvr_mem_free(FightAnimationTexture);
return(FightStage);
}