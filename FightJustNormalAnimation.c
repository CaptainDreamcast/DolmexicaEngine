    void FightJustNormalAnimation(int FightStage, int LeftStageBorder, BackGroundHeaderStruct BackGroundHeaderData, BackGroundStruct BackGroundData[], BackGroundAnimationStruct BackGroundAnimationData[], pvr_ptr_t BackGroundTextures[], char CharacterName[][10], CharacterTextureStruct CharacterTexture[], char AnimationBuffer[][10], char WhichAnimationFrame[], int DrawCharX[], int PosCharY[], char CharIsLeft[], PaletteData CharPalette[], int StageGround, int ShadowPositionX, int ShadowPositionY, int CharacterTextureSizeDrawn, int CharacterTextureSizeReal[], int WhichRound, sfxhnd_t FightAnimationSoundEffect[][MaxFightAnimationSoundEffect], int WhichFightAnimation, int* Winner, uint16 FightAnimationFlags, uint8 DrawCharDifferently[]){

    pvr_ptr_t FightAnimationTexture;

    maple_device_t *cont;
    cont_state_t *st;

    int CurrentChar;

    uint8 SoundEffectIdentifier = 0;
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
    char MountPoint[NormalMountPointSize];
    short FightAnimationVoiceClipChecker = 0;
    uint8 TextureType;


    switch (WhichFightAnimation) {
	case FightRoundAnimation:
                if(!(FightAnimationFlags & RoundAnimationFlag)) return;
	        sprintf(MountPoint, "ROUNDANIMATION");
                SoundEffectIdentifier = RoundAnimationSoundEffectIdentifier;
                break;
	case FightFightAnimation:
                if(!(FightAnimationFlags & FightAnimationFlag)) return;
	        sprintf(MountPoint, "FIGHTANIMATION");
                SoundEffectIdentifier = FightAnimationSoundEffectIdentifier;
                break;
	case FightPerfectAnimation:
                if(!(FightAnimationFlags & PerfectAnimationFlag)) return;
	        sprintf(MountPoint, "PERFECTANIMATION");
                SoundEffectIdentifier = PerfectAnimationSoundEffectIdentifier;
                break;
	case FightNewRivalAnimation:
                if(!(FightAnimationFlags & NewRivalAnimationFlag)) return;
	        sprintf(MountPoint, "JOININANIMATION");
                SoundEffectIdentifier = NewRivalAnimationSoundEffectIdentifier;
                break;
	}

    if(LoadPalette8(MountPoint, 0, AdditionalAnimationPalette)) TextureType = PaletteType;
    else TextureType = RedGreenBlueType;


    if(WhichFightAnimation == FightRoundAnimation) ReadNewRoundAnimation(WhichRound, WhichFightAnimationFrame, &FightAnimationID, &FightAnimationSpeed, &FightAnimationTextureSizeX, &FightAnimationTextureSizeY, &FightAnimationSizeX, &FightAnimationSizeY, &FightAnimationScreenPositionX, &FightAnimationScreenPositionY, &FightAnimationVoiceClipChecker, &EndFightAnimation, MountPoint);
    else ReadNormalAnimation(WhichFightAnimationFrame, &FightAnimationID, &FightAnimationSpeed, &FightAnimationTextureSizeX, &FightAnimationTextureSizeY, &FightAnimationSizeX, &FightAnimationSizeY, &FightAnimationScreenPositionX, &FightAnimationScreenPositionY, &FightAnimationVoiceClipChecker, &EndFightAnimation, MountPoint);
    if(FightAnimationVoiceClipChecker != 0) {snd_sfx_play(FightAnimationSoundEffect[SoundEffectIdentifier][FightAnimationVoiceClipChecker], VolumeSFX, 128); FightAnimationVoiceClipChecker = 0;}

    FightAnimationTexture = pvr_mem_malloc(FightAnimationTextureSizeX*FightAnimationTextureSizeY*2);

    while(EndFightAnimation == 0 || FightAnimationTicks%FightAnimationSpeed != 0){

    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_TR_POLY);
 
    DrawCoolStage(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, BackGroundDrawAnimated);

    CurrentChar = CharacterOne;
    do{
    DrawCharLiteStandard();    
    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);    

    DrawSomeFunkyAnimation(FightAnimationID, FightAnimationSizeX, FightAnimationSizeY, FightAnimationScreenPositionX, FightAnimationScreenPositionY, MountPoint, FightAnimationTexture, TextureType);

    pvr_list_finish();
    pvr_scene_finish();

    if(FightAnimationTicks%FightAnimationSpeed == 0){
    WhichFightAnimationFrame++;
    FightAnimationTicks = 0;

    if(WhichFightAnimation == FightRoundAnimation) ReadNewRoundAnimation(WhichRound, WhichFightAnimationFrame, &FightAnimationID, &FightAnimationSpeed, &FightAnimationTextureSizeX, &FightAnimationTextureSizeY, &FightAnimationSizeX, &FightAnimationSizeY, &FightAnimationScreenPositionX, &FightAnimationScreenPositionY, &FightAnimationVoiceClipChecker, &EndFightAnimation, MountPoint);
    else ReadNormalAnimation(WhichFightAnimationFrame, &FightAnimationID, &FightAnimationSpeed, &FightAnimationTextureSizeX, &FightAnimationTextureSizeY, &FightAnimationSizeX, &FightAnimationSizeY, &FightAnimationScreenPositionX, &FightAnimationScreenPositionY, &FightAnimationVoiceClipChecker, &EndFightAnimation, MountPoint);
    if(FightAnimationVoiceClipChecker != 0) {snd_sfx_play(FightAnimationSoundEffect[SoundEffectIdentifier][FightAnimationVoiceClipChecker], VolumeSFX, 128); FightAnimationVoiceClipChecker = 0;}
    }

    FightAnimationTicks++;
    if(FightAnimationTicks == 0xFFFF){
    FightAnimationTicks=1;
    }

    if((cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER)) != NULL) {
    st = (cont_state_t *)maple_dev_status(cont);

    if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
    EndFightAnimation = 1;
    FightAnimationSpeed = 1;
    *Winner = StairWayToHeavenIdentifier;
    }
    }

    }

    pvr_mem_free(FightAnimationTexture);   
    #include "FightResettingTheScreen.c"
    }