    if(PosCharX1 < LeftStageBorder)
    {
    PosCharX1 = LeftStageBorder;
    }
    if(PosCharX1 > LeftStageBorder+640)
    {
    PosCharX1 = LeftStageBorder+640;
    }


    if(CharIsLeft1 == 1){
    DrawCharX1 = PosCharX1 - LeftStageBorder-CharOffset1;
    }
    else{
    DrawCharX1 = PosCharX1-LeftStageBorder-256+CharWidth1+CharOffset1;    
    }
    
    if(CharIsLeft2 == 1){
    DrawCharX2 = PosCharX2 - LeftStageBorder-CharOffset2;
    }
    else{
    DrawCharX2 = PosCharX2-LeftStageBorder-256+CharWidth2+CharOffset2;
    }

    if(PosCharX1+(CharWidth1/2) > PosCharX2+(CharWidth2/2)){
    if(CharIsLeft1 == 1 && GroundLevel1 == 1){
    CharIsLeft1 = 0;
    DrawCharX1 = PosCharX1-LeftStageBorder-256+CharWidth1+CharOffset1;
    }
    if(CharIsLeft2 == 0 && GroundLevel2 == 1){
    CharIsLeft2 = 1;
    DrawCharX2 = PosCharX2 - LeftStageBorder-CharOffset2;
    }
    }

    if(PosCharX2+(CharWidth2/2) > PosCharX1+(CharWidth1/2)){
    if(CharIsLeft1 == 0 && GroundLevel1 == 1){
    CharIsLeft1 = 1;
    DrawCharX1 = PosCharX1-LeftStageBorder-CharOffset1;
    }
    if(CharIsLeft2 == 1 && GroundLevel2 == 1){
    CharIsLeft2 = 0;
    DrawCharX2 = PosCharX2-LeftStageBorder-256+CharWidth2+CharOffset2;
    }
    }


    

    if(PosCharX1-LeftStageBorder < 190 && PosCharX2-LeftStageBorder < 190 && LeftStageBorder > 0){
    LeftStageBorder -= 2;
    DrawCharX1 += 2;
    DrawCharX2 += 2;
    if(WhichEffect2 != 0)    {
    HitPositionX2+= 2;
    }
    }
    if(PosCharX1-LeftStageBorder > 380 && PosCharX2-LeftStageBorder > 380 && LeftStageBorder <= 640){
    LeftStageBorder += 2;
    DrawCharX1 -= 2;
    DrawCharX2 -= 2;
    if(WhichEffect2 != 0)    {
    HitPositionX2-= 2;
    }
    }
    /*if(SpecialEffectStage1 != 0){
    SpecialEffectPosX1 += SpecialEffectSpeedX1;
    SpecialEffectPosY1 += SpecialEffectSpeedY1;
    SpecialEffectRange1 -= SpecialEffectSpeedX1;
    if(SpecialEffectRange1 <= 0 && SpecialEffectStage1 == 2){
    SpecialEffectReadHuman(CharacterName1, SpecialEffectNameBuffer1, SpecialEffectOffset1+16, &SpecialEffectAnimationSpeed1, &SpecialEffectFrameAmount1);   
    SpecialEffectStage1 = 3;
    SpecialEffectWhichFrame1 = 1;    
    }
    SpecialEffectDrawX1 = SpecialEffectPosX1 - LeftStageBorder;
    SpecialEffectDrawY1 = SpecialEffectPosY1;
    }  */

    SpecialEffectDrawX1 = SpecialEffectPosX1 - LeftStageBorder;
    SpecialEffectDrawY1 = SpecialEffectPosY1;

    /*
    LeftStageBorder = PosCharX1-200;
    if(LeftStageBorder < 0){
    DrawCharX1 = 200 + LeftStageBorder;
    LeftStageBorder = 0;
    }
    if(LeftStageBorder > 640){
    DrawCharX1 = PosCharX1-640;
    LeftStageBorder = 640;
    }

    */
