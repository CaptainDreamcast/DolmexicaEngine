    //printf("Main Loop Restart.\n");

    #ifdef DOLMEXICA_DEBUG_BORDERCOLOR
    vid_border_color(0, 0, 255);
    #endif

    #include "GeneralScreenCalculationCode.c"    

    CurrentChar = CharacterOne;
    OtherChar = CharacterTwo;
    do{
    if(CharIsHuman[CurrentChar] == 0){

    if((cont = maple_enum_dev(CurrentChar, 0)) != NULL) {
    st = (cont_state_t *)maple_dev_status(cont);

    if (st->buttons & CONT_START) {

   Winner = CurrentChar+NewPlayerJoinsInIdentifier;
   FightStage = FightNewRivalAnimation;
   }
   }

    #include "NewAICalculations.c"
    }
    else{
    #include "NewControlCode.c"
    }

    #include "SpecialAttackCode.c"

    #include "StatusAilmentCode.c"

    #include "PersonalScreenCalculationCode.c"

    #include "NewJumpingCode.c"


    if(WhichMissSoundEffect[CurrentChar] != 0 && WhichAnimationFrame[CurrentChar] == WhichSoundEffectFrame[CurrentChar]){


    snd_sfx_play(CharacterSFX[CurrentChar][WhichMissSoundEffect[CurrentChar]], VolumeSFX, 128);
    WhichMissSoundEffect[CurrentChar] = 0;
    WhichSoundEffectFrame[CurrentChar] = 0;
    
    }

    CurrentChar++;
    OtherChar--;
    } while(CurrentChar <= MaxCharsLoopValue);


    //if(AnimationType[CharacterOne] == 5 && (WhichAnimationFrame[CharacterOne] == 3 || WhichAnimationFrame[CharacterOne] == 4)  && CharHitStatus[CharacterOne] == 0){ 
    //printf("PosCharX[CharacterOne]: (%d)\n", PosCharX[CharacterOne]);
    //printf("DrawCharX[CharacterOne]: (%d)\n", DrawCharX[CharacterOne]);
    //}  


    #include "NewDrawingCode.c"

    if(AnimationType[CharacterOne] != OmniAttackAnimationIdentifier && AnimationType[CharacterTwo] != OmniAttackAnimationIdentifier){
    //CollisionDetect(CharacterName[CharacterOne], AnimationBuffer[CharacterOne], WhichAnimationFrame[CharacterOne], CharacterName[CharacterTwo], AnimationBuffer[CharacterTwo], WhichAnimationFrame[CharacterTwo], DrawCharX[CharacterOne], DrawCharX[CharacterTwo], PosCharY[CharacterOne], PosCharY[CharacterTwo], CharIsLeft[CharacterOne], CharIsLeft[CharacterTwo], &CharHitStatus[CharacterOne], &CharHitStatus[CharacterTwo], &HitPositionX[CharacterOne], &HitPositionY[CharacterOne], &HitPositionX[CharacterTwo], &HitPositionY[CharacterTwo], CharacterStretchFactor, CharacterTextureSizeDrawn, SpecialEffectStage[CharacterOne], SpecialEffectSizeX[CharacterOne], SpecialEffectSizeY[CharacterOne], SpecialEffectDrawX[CharacterOne], SpecialEffectDrawY[CharacterOne], SpecialEffectWhichFrame[CharacterOne], SpecialEffectNameBuffer[CharacterOne]);
    NewCollisionDetect(
    CharacterName, AnimationBuffer, WhichAnimationFrame, DrawCharX, PosCharY, CharIsLeft, CharHitStatus, 
    HitPositionX, HitPositionY, CharacterStretchFactor, CharacterTextureSizeDrawn, SpecialEffectStage, 
    SpecialEffectSizeX, SpecialEffectSizeY, SpecialEffectDrawX, SpecialEffectDrawY, SpecialEffectWhichFrame, 
    SpecialEffectNameBuffer);


    #include "NewCollisionCode.c"
    //printf("Collision Calculated!\n");
    }
    CurrentChar = CharacterOne;
    OtherChar = CharacterTwo;
    do{
    #include "FightSmallTimeShenanigans.c"
    CurrentChar++;
    OtherChar--;
    } while(CurrentChar <= MaxCharsLoopValue);

    #ifdef DOLMEXICA_DEBUG_BORDERCOLOR
    vid_border_color(255, 0, 255);
    #endif