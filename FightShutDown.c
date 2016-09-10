    //pvr_stats_t stats;
    //pvr_get_stats(&stats);
    //printf("VBL Count: %d, last_time: %f, frame rate: %f fps\n",
    //stats.vbl_count, stats.frame_last_time, stats.frame_rate);

    FightFadingOut(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, CharacterName, CharacterTexture, AnimationBuffer, WhichAnimationFrame, DrawCharX, PosCharY, CharIsLeft, CharPalette, StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn, CharacterTextureSizeReal, DrawCharDifferently);

    while(HitEffectAmount > 0){
    HitEffectAmount--;  
    while(HitEffectFrameAmount[HitEffectAmount] > 0){
    pvr_mem_free(HitEffectTextures[HitEffectAmount][HitEffectFrameAmount[HitEffectAmount]]);
    HitEffectFrameAmount[HitEffectAmount]--;
    }
    }

    for(CurrentChar=0; CurrentChar<BackGroundHeaderData.BackGroundAmount; CurrentChar++){ 

    if(BackGroundData[CurrentChar].BackGroundAnimated != 0){
    Bluff = BackGroundData[CurrentChar].BackGroundAnimated-1;
    for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<BackGroundAnimationData[Bluff].Data.FrameAmount; DirtyDeedsDoneDirtCheap++) pvr_mem_free(BackGroundAnimationData[Bluff].Texture[DirtyDeedsDoneDirtCheap]);  
    }
    else pvr_mem_free(BackGroundTextures[CurrentChar]);

    }
    pvr_mem_free(NewTimerTexture);

    DeLoadCharacterSoundEffects(CharacterSFX, OriginalCharacterName);
    DeLoadAllKindsOfAnimations(FightAnimationSoundEffect, FightAnimationFlags);
    
    CurrentChar = CharacterOne;
    do{

    DeLoadCharRomDisk(CharacterName[CurrentChar], CharsAreIdentical, CurrentChar);

    for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<CharacterTextureBufferAmount; DirtyDeedsDoneDirtCheap++) pvr_mem_free(CharacterTexture[CurrentChar].Texture[DirtyDeedsDoneDirtCheap]);

    pvr_mem_free(LifeBarTexture[CurrentChar]);
    pvr_mem_free(VictoryTexture[CurrentChar]);
    if(SpecialEffect[CurrentChar]) pvr_mem_free(SpecialEffectTexture[CurrentChar]);


    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);
    snd_sfx_unload(KnockDownSFX);

    if(WhichMode == StoryModeIdentifier && CharIsHuman[CharacterOne] && CharIsHuman[CharacterTwo]){
    Winner = SelectNewCharacterIdentifier;
    CharIsHuman[WhichCharLost] = 0;
    PlayerID[WhichCharLost] = -1;
    }

    cdfs_test(); // Prints content of the RAMDISK. For Debugging.
    FightStage = 99;
    FightLoop = 0;
    SoundStop();