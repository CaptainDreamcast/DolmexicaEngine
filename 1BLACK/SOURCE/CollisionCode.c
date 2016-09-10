    //if(AnimationName1 == "PUNCHWEK" && WhichAnimationFrame1 == 2 && AnimationName2 == "STANDIN1" && DrawCharX2-DrawCharX1 < 256){
    CollisionDetect(CharacterName1, AnimationBuffer1, WhichAnimationFrame1, CharacterName2, AnimationBuffer2, WhichAnimationFrame2, DrawCharX1, DrawCharX2, PosCharY1, PosCharY2, CharIsLeft1, CharIsLeft2, &CharHitStatus1, &CharHitStatus2, &HitPositionX1, &HitPositionY1, &HitPositionX2, &HitPositionY2, SpecialEffectStage1, SpecialEffectTextureSizeX1, SpecialEffectTextureSizeY1, SpecialEffectDrawX1, SpecialEffectDrawY1, SpecialEffectNameBuffer1);
    //}
    //printf("Animation Type: %d.\n", AnimationType1);

    if((CharHitStatus2 == 3 || CharHitStatus2 == 2) && (AnimationType1 == 3 || AnimationType1 == 6 || AnimationType1 == 8)){


    if(CharHitStatus2 == 2){
    if(GroundLevel2 == 1 && CrouchPosition2 == 0 && CrouchPosition1 != 0) CharHitStatus2 = 3;
    else if(CrouchPosition2 != 0 && GroundLevel1 == 0) CharHitStatus2 = 3;
    else{
    if(CrouchPosition2 == 0){
    AnimationID2 = -10;
    MovementReadCompulsory(9, CharacterName2, AnimationBuffer2, &CharHitAnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "BLOCKING";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;
    WhichEffect2 = 4;
    WhichEffectFrame2 = 1;
    EffectFrameAmount2 = 10;
    EffectTicks2 = 0;
    }
    else{

    AnimationID2 = -11;
    MovementReadCompulsory(10, CharacterName2, AnimationBuffer2, &CharHitAnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "CROUBLOC";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;

    CrouchPosition2 = 2;

    WhichEffect2 = 4;
    WhichEffectFrame2 = 1;
    EffectFrameAmount2 = 10;
    EffectTicks2 = 0;

    }
    }
    }


    if(CharHitStatus2 == 3 && GroundLevel2 == 0){
    CharHealth2 = CharHealth2-AnimationStrength1;
    PointsAdd(PointArray1, AnimationStrength1, CrouchPosition1, CrouchPosition2, GroundLevel1, GroundLevel2);
    LoadSoundEffect(&HitSFX1, WhichHitSoundEffect1, CharacterName1, SoundEffectVolume);

    AnimationID2 = -8;
    MovementReadCompulsory(7, CharacterName2, AnimationBuffer2, &CharHitAnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "KNOKDOWN";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;
    WhichEffect2 = 1;
    WhichEffectFrame2 = 1;
    EffectFrameAmount2 = 10;
    EffectTicks2 = 0;
    }
    else if(CharHitStatus2 == 3 && CrouchPosition2 != 0){
    CharHealth2 = CharHealth2-AnimationStrength1;
    PointsAdd(PointArray1, AnimationStrength1, CrouchPosition1, CrouchPosition2, GroundLevel1, GroundLevel2);
    LoadSoundEffect(&HitSFX1, WhichHitSoundEffect1, CharacterName1, SoundEffectVolume);

    AnimationID2 = -13;
    MovementReadCompulsory(12, CharacterName2, AnimationBuffer2, &CharHitAnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "CROU_HIT";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;
    
    CrouchPosition2 = 2;  

    WhichEffect2 = 1;
    WhichEffectFrame2 = 1;
    EffectFrameAmount2 = 10;
    EffectTicks2 = 0;
 

    }
    else if(CharHitStatus2 == 3 && HitPositionY2 < PosCharY2+256-CharHeight2/3){
    LoadSoundEffect(&HitSFX1, WhichHitSoundEffect1, CharacterName1, SoundEffectVolume);
    CharHealth2 = CharHealth2-AnimationStrength1;
    PointsAdd(PointArray1, AnimationStrength1, CrouchPosition1, CrouchPosition2, GroundLevel1, GroundLevel2);
    AnimationID2 = -6;
    MovementReadCompulsory(5, CharacterName2, AnimationBuffer2, &CharHitAnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "HITHIGH0";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;

    WhichEffect2 = 1;
    WhichEffectFrame2 = 1;
    EffectFrameAmount2 = 10;
    EffectTicks2 = 0;


    }
    else if(CharHitStatus2 == 3 && HitPositionY2 >= PosCharY2+256-CharHeight2/3){

    LoadSoundEffect(&HitSFX1, WhichHitSoundEffect1, CharacterName1, SoundEffectVolume); 
    CharHealth2 = CharHealth2-AnimationStrength1;
    PointsAdd(PointArray1, AnimationStrength1, CrouchPosition1, CrouchPosition2, GroundLevel1, GroundLevel2);

    AnimationID2 = -8;
    MovementReadCompulsory(7, CharacterName2, AnimationBuffer2, &CharHitAnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "KNOKDOWN";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;

    WhichEffect2 = 1;
    WhichEffectFrame2 = 1;
    EffectFrameAmount2 = 10;
    EffectTicks2 = 0;
 

    }



    if (CharHealth2 < 0){
      CharHealth2 = 0;
     printf("DEAD!\n");
     FightStage = 6;
     SuperCoolEffectTicks = 0;
     WhichCharLost = 2;
    }

    if(AnimationEnemyAcceleration1 != 0){
     if(GroundLevel2 == 1){
      AnimationSpeed2 = 61;
      if(CharIsLeft1 == 1){
       CharHitAcceleration2 = AnimationEnemyAcceleration1;
       }
      if(CharIsLeft1 == 0){
       CharHitAcceleration2 = -AnimationEnemyAcceleration1;
       }
      CharHitDuration2 = (AnimationEnemyAcceleration1/10)+1;
      }
     else{
      AnimationSpeed2 = CharHitAnimationSpeed2;
      CharHitAnimationSpeed2 = 61;
      CharHitDuration2 = 0;
      //CharHitAcceleration2 = 0;
      
      if(CharIsLeft1 == 1){
       JumpDirection2 = 0;
       CharHitAcceleration2 = AnimationEnemyAcceleration1;

       }
      if(CharIsLeft1 == 0){
       JumpDirection2 = 0;
       CharHitAcceleration2 = -AnimationEnemyAcceleration1;
       } 
      }
    }

    if(AnimationEnemyAcceleration1 == 0){
    AnimationSpeed2 = CharHitAnimationSpeed2;
    }
    AnimationLoop2 =0;
    AnimationTicks2 = 1;

    CharHitStatus2 = 4;
    }

    if((CharHitStatus2 == 3) && (SpecialEffectStage1 == 2)){

    LoadSoundEffect(&HitSFX1, WhichHitSoundEffect1, CharacterName1, SoundEffectVolume);
    CharHealth2 = CharHealth2-SpecialEffectStrength1;
    PointsAdd(PointArray1, SpecialEffectStrength1, CrouchPosition1, CrouchPosition2, GroundLevel1, GroundLevel2);
    AnimationID2 = -6;
    MovementReadCompulsory(5, CharacterName2, AnimationBuffer2, &CharHitAnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "HITHIGH0";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;

    WhichEffect2 = 1;
    WhichEffectFrame2 = 1;
    EffectFrameAmount2 = 10;
    EffectTicks2 = 0;

/*
    if(CharHitStatus2 == 3 && GroundLevel2 == 0){
    CharHealth2 = CharHealth2-SpecialEffectStrength1;
    PointsAdd(PointArray1, SpecialEffectStrength1, CrouchPosition1, CrouchPosition2, GroundLevel1, GroundLevel2);
    LoadSoundEffect(&HitSFX1, WhichHitSoundEffect1, CharacterName1, SoundEffectVolume);

    AnimationID2 = -8;
    MovementReadCompulsory(7, CharacterName2, AnimationBuffer2, &CharHitAnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "KNOKDOWN";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;
    AnimationLoop2 = -1;
    WhichEffect2 = 1;
    WhichEffectFrame2 = 1;
    EffectFrameAmount2 = 10;
    EffectTicks2 = 0;
 

    }
*/

    if (CharHealth2 < 0){
      CharHealth2 = 0;
     printf("DEAD!\n");
    }

    if(SpecialEffectAcceleration1 != 0){
    AnimationSpeed2 = 61;
    if(CharIsLeft1 == 1){
    CharHitAcceleration2 = SpecialEffectAcceleration1;
    }
    if(CharIsLeft1 == 0){
    CharHitAcceleration2 = -SpecialEffectAcceleration1;
    }
    CharHitDuration2 = (SpecialEffectAcceleration1/10)+1;
    }
    if(SpecialEffectAcceleration1 == 0){
    AnimationSpeed2 = CharHitAnimationSpeed2;
    }
    AnimationLoop2 =0;
    AnimationTicks2 = 1;

    CharHitStatus2 = 4;
    }

    if((CharHitStatus2 == 3 || CharHitStatus2 == 2) && AnimationType1 == 5){ //Throwing is fun.

    //printf("Attempting Throw!\n");
    //printf("Now Loading: Special #%d.\n", WhichSpecial1);
    FirstSpecialReadHuman(CharacterName1, AnimationBuffer1, &FrameAmount1,  &AnimationEnemyAcceleration1, &AnimationType1, &AnimationStrength1, WhichSpecial1, &SpecialOffset1);
    //printf("First Offset: %ld.\n", SpecialOffset1);
    WhichAnimationFrame1 = 1;
    SpecialAnimationFrame1 = 1;
    DirectionalInputAllowed1 = 0;
    AnimationLoop1 = 0;
    AnimationName1 = AnimationBuffer1;
    
    FrameSpecialReadHuman(CharacterName1, SpecialOffset1, &AnimationSpeed1, &AnimationEnemyAcceleration1, AnimationType1, &AnimationStrength1, &SpecialCharChangeX1, &SpecialCharChangeY1, &SpecialCharChangeX2, &SpecialCharChangeY2, &SpecialCharAlignment2, &JumpVelocity2, &ComboMovementX1, &ComboMovementY1);
    
    if(CharIsLeft1 == 1){
    PosCharX1 += SpecialCharChangeX1;
    PosCharY1 += SpecialCharChangeY1;
    }
    else{
    PosCharX1 -= SpecialCharChangeX1;
    PosCharY1 -= SpecialCharChangeY1;
    }
    if(CharIsLeft2 == 0){
    PosCharX2 += SpecialCharChangeX2;
    PosCharY2 += SpecialCharChangeY2;
    }
    else{
    PosCharX2 -= SpecialCharChangeX2;
    PosCharY2 -= SpecialCharChangeY2;
    }


    SpecialOffset1+=32;

    if(SpecialCharAlignment2 == 1){
    AnimationID2 = -6;
    MovementReadCompulsory(5, CharacterName2, AnimationBuffer2, &CharHitAnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "HITHIGH0";
    WhichAnimationFrame2 = 1;
    AnimationSpeed2 = 61;
    AnimationTicks2 = 1;
    CharHitStatus2 = 6;
    }
    if(SpecialCharAlignment2 == 2){
    AnimationID2 = -8;
    MovementReadCompulsory(7, CharacterName2, AnimationBuffer2, &CharHitAnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "KNOKDOWN";
    WhichAnimationFrame2 = FrameAmount2;
    AnimationSpeed2 = 61;
    AnimationTicks2 = 1;
    CharHitStatus2 = 6;

    }
    }

    if(CharHitStatus2 == 7){ //SHOOTING is fun.

    CharHealth2 = CharHealth2-SpecialEffectStrength1;
    PointsAdd(PointArray1, SpecialEffectStrength1, CrouchPosition1, CrouchPosition2, GroundLevel1, GroundLevel2);
    AnimationID2 = -6;
    MovementReadCompulsory(5, CharacterName2, AnimationBuffer2, &CharHitAnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "HITHIGH0";
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;

    /*WhichEffect2 = 1;
    WhichEffectFrame2 = 1;
    EffectFrameAmount2 = 10;
    EffectTicks2 = 0;

    if(SpecialEffectAcceleration1 != 0){
    AnimationSpeed2 = 61;
    if(CharIsLeft1 == 1){
    CharHitAcceleration2 = SpecialEffectAcceleration1;
    }
    if(CharIsLeft1 == 0){
    CharHitAcceleration2 = -SpecialEffectAcceleration1;
    }
    CharHitDuration2 = (SpecialEffectAcceleration1/10)+1;
    }
    if(SpecialEffectAcceleration1 == 0){
    AnimationSpeed2 = CharHitAnimationSpeed2;
    }*/

    SpecialEffectReadHuman(CharacterName1, SpecialEffectNameBuffer1, SpecialEffectOffset1+48, &SpecialEffectAnimationSpeed1, &SpecialEffectFrameAmount1);   
    //printf("Done Reading the 2nd stage!\n");
    SpecialEffectStage1 = 4;
    SpecialEffectTicks1 = 1;
    
    AnimationLoop2 =0;
    AnimationTicks2 = 1;

    CharHitStatus2 = 4; 
    }

    if((CharHitStatus1 == 3 || CharHitStatus1 == 2) && (AnimationType2 == 3 || AnimationType2 == 6 || AnimationType2 == 8)){

    if(CharHitStatus1 == 2){
    if(GroundLevel1 == 1 && CrouchPosition1 == 0 && CrouchPosition2 != 0) CharHitStatus1 = 3;
    else if(CrouchPosition1 != 0 && GroundLevel2 == 0) CharHitStatus1 = 3;
    else{
    if(CrouchPosition1 == 0){
    MovementReadCompulsory(9, CharacterName1, AnimationBuffer1, &CharHitAnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    AnimationName1 = "BLOCKING";
    WhichAnimationFrame1 = 1; 
    AnimationTicks1 = 1;
    AnimationID1 = -10;       

    WhichEffect1 = 4;
    WhichEffectFrame1 = 1;
    EffectFrameAmount1 = 10;
    EffectTicks1 = 0;
    }
    else{

    AnimationID1 = -11;
    MovementReadCompulsory(10, CharacterName1, AnimationBuffer1, &CharHitAnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    AnimationName1 = "CROUBLOC";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;

    CrouchPosition1 = 2;

    WhichEffect1 = 4;
    WhichEffectFrame1 = 1;
    EffectFrameAmount1 = 10;
    EffectTicks1 = 0;

    }
    }
    }
    
    if(CharHitStatus1 == 3 && GroundLevel1 == 0){
    LoadSoundEffect(&HitSFX2, WhichHitSoundEffect2, CharacterName2, SoundEffectVolume);
    CharHealth1 = CharHealth1-AnimationStrength2;

    AnimationID1 = -8;
    MovementReadCompulsory(7, CharacterName1, AnimationBuffer1, &CharHitAnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    AnimationName1 = "KNOKDOWN";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;
    AnimationLoop1 = -1;
    WhichEffect1 = 1;
    WhichEffectFrame1 = 1;
    EffectFrameAmount1 = 10;
    EffectTicks1 = 0;
 

    }

    else if(CharHitStatus1 == 3 && CrouchPosition1 != 0){
    LoadSoundEffect(&HitSFX2, WhichHitSoundEffect2, CharacterName2, SoundEffectVolume);
    CharHealth1 = CharHealth1-AnimationStrength2;
    PointsAdd(PointArray2, AnimationStrength2, CrouchPosition2, CrouchPosition1, GroundLevel2, GroundLevel1);
    LoadSoundEffect(&HitSFX2, WhichHitSoundEffect2, CharacterName2, SoundEffectVolume);

    AnimationID1 = -13;
    MovementReadCompulsory(12, CharacterName1, AnimationBuffer1, &CharHitAnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    AnimationName1 = "CROU_HIT";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;
    
    CrouchPosition1 = 2;  

    WhichEffect1 = 1;
    WhichEffectFrame1 = 1;
    EffectFrameAmount1 = 10;
    EffectTicks1 = 0;
 

    }

    else if(CharHitStatus1 == 3 && HitPositionY1 < PosCharY1+256-CharHeight1/3){
    LoadSoundEffect(&HitSFX2, WhichHitSoundEffect2, CharacterName2, SoundEffectVolume);
    CharHealth1 = CharHealth1-AnimationStrength2;

    AnimationID1 = -6;
    MovementReadCompulsory(5, CharacterName1, AnimationBuffer1, &CharHitAnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    AnimationName1 = "HITHIGH0";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;

    WhichEffect1 = 1;
    WhichEffectFrame1 = 1;
    EffectFrameAmount1 = 10;
    EffectTicks1 = 0;


    }
    else if(CharHitStatus1 == 3 && HitPositionY1 >= PosCharY1+256-CharHeight1/3){
    LoadSoundEffect(&HitSFX2, WhichHitSoundEffect2, CharacterName2, SoundEffectVolume);
    CharHealth1 = CharHealth1-AnimationStrength2;

    AnimationID1 = -8;
    MovementReadCompulsory(7, CharacterName1, AnimationBuffer1, &CharHitAnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    AnimationName1 = "KNOKDOWN";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;

    WhichEffect1 = 1;
    WhichEffectFrame1 = 1;
    EffectFrameAmount1 = 10;
    EffectTicks1 = 0;
 

    }



    if (CharHealth1 < 0){
      CharHealth1 = 0;
     printf("DEAD!\n");
     FightStage = 6;
     SuperCoolEffectTicks = 1;
     WhichCharLost = 1;
    }

    if(AnimationEnemyAcceleration2 != 0){
     if(GroundLevel1 == 1){
      AnimationSpeed1 = 61;
      if(CharIsLeft2 == 1){
       CharHitAcceleration1 = AnimationEnemyAcceleration2;
       }
      if(CharIsLeft2 == 0){
       CharHitAcceleration1 = -AnimationEnemyAcceleration2;
       }
      CharHitDuration1 = (AnimationEnemyAcceleration2/10)+1;
      }
     else{
      AnimationSpeed1 = CharHitAnimationSpeed1;
      CharHitAnimationSpeed1 = 61;
      CharHitDuration1 = 0;
      //CharHitAcceleration1 = 0;
      
      if(CharIsLeft2 == 1){
       JumpDirection1 = 0;
       CharHitAcceleration1 = AnimationEnemyAcceleration2;
       }
      if(CharIsLeft2 == 0){
       JumpDirection1 = 0;
       CharHitAcceleration1 = -AnimationEnemyAcceleration2;
       } 
      }
    }
    if(AnimationEnemyAcceleration2 == 0){
    AnimationSpeed1 = CharHitAnimationSpeed1;
    }

    AnimationLoop1 =0;
    AnimationTicks1 = 1;
    DirectionalInputAllowed1 = 0;

    CharHitStatus1 = 4;
    }


    if((CharHitStatus1 == 3 || CharHitStatus1 == 2) && AnimationType2 == 5){ //Throwing is fun.

    //printf("Attempting Throw!\n");
    //printf("Now Loading: Special #%d.\n", WhichSpecial2);
    FirstSpecialReadHuman(CharacterName2, AnimationBuffer2, &FrameAmount2,  &AnimationEnemyAcceleration2, &AnimationType2, &AnimationStrength2, WhichSpecial2, &SpecialOffset2);
    //printf("First Offset: %ld.\n", SpecialOffset2);
    WhichAnimationFrame2 = 1;
    SpecialAnimationFrame2 = 1;
    DirectionalInputAllowed2 = 0;
    AnimationLoop2 = 0;
    AnimationName2 = AnimationBuffer2;
    
    FrameSpecialReadHuman(CharacterName2, SpecialOffset2, &AnimationSpeed2, &AnimationEnemyAcceleration2, AnimationType2, &AnimationStrength2, &SpecialCharChangeX2, &SpecialCharChangeY2, &SpecialCharChangeX1, &SpecialCharChangeY1, &SpecialCharAlignment1, &JumpVelocity1, &ComboMovementX2, &ComboMovementY2);
    
    if(CharIsLeft2 == 1){
    PosCharX2 += SpecialCharChangeX2;
    PosCharY2 += SpecialCharChangeY2;
    }
    else{
    PosCharX2 -= SpecialCharChangeX2;
    PosCharY2 -= SpecialCharChangeY2;
    }
    if(CharIsLeft1 == 0){
    PosCharX1 += SpecialCharChangeX1;
    PosCharY1 += SpecialCharChangeY1;
    }
    else{
    PosCharX1 -= SpecialCharChangeX1;
    PosCharY1 -= SpecialCharChangeY1;
    }


    SpecialOffset2+=32;

    if(SpecialCharAlignment1 == 1){
    AnimationID1 = -6;
    MovementReadCompulsory(5, CharacterName1, AnimationBuffer1, &CharHitAnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    AnimationName1 = "HITHIGH0";
    WhichAnimationFrame1 = 1;
    AnimationSpeed1 = 61;
    AnimationTicks1 = 1;
    CharHitStatus1 = 6;
    }
    if(SpecialCharAlignment1 == 2){
    AnimationID1 = -8;
    MovementReadCompulsory(7, CharacterName1, AnimationBuffer1, &CharHitAnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    AnimationName1 = "KNOKDOWN";
    WhichAnimationFrame1 = FrameAmount1;
    AnimationSpeed1 = 61;
    AnimationTicks1 = 1;
    CharHitStatus1 = 6;

    }
    }

    if(CharHitStatus1 == 7){ //SHOOTING is fun.

    CharHealth1 = CharHealth1-SpecialEffectStrength2;
    PointsAdd(PointArray2, SpecialEffectStrength2, CrouchPosition2, CrouchPosition1, GroundLevel2, GroundLevel1);
    AnimationID1 = -6;
    MovementReadCompulsory(5, CharacterName1, AnimationBuffer1, &CharHitAnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    AnimationName1 = "HITHIGH0";
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;



    SpecialEffectReadHuman(CharacterName2, SpecialEffectNameBuffer2, SpecialEffectOffset2+48, &SpecialEffectAnimationSpeed2, &SpecialEffectFrameAmount2);   
    //printf("Done Reading the 2nd stage!\n");
    SpecialEffectStage2 = 4;
    SpecialEffectTicks2 = 1;
    
    AnimationLoop1 =0;
    AnimationTicks1 = 1;

    CharHitStatus1 = 4; 
    }