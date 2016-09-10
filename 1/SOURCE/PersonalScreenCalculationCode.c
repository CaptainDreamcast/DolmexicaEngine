    if(PosCharX[CurrentChar] < LeftStageBorder)
    {
    PosCharX[CurrentChar] = LeftStageBorder;
    }
    if(PosCharX[CurrentChar]+CharWidth[CurrentChar] > LeftStageBorder+ScreenSizeX)
    {
    PosCharX[CurrentChar] = LeftStageBorder-CharWidth[CurrentChar]+ScreenSizeX;
    }

    if(CharIsLeft[CurrentChar] == 1){
    DrawCharX[CurrentChar] = PosCharX[CurrentChar] - LeftStageBorder-CharOffset[CurrentChar];
    }
    else{
    DrawCharX[CurrentChar] = PosCharX[CurrentChar]-LeftStageBorder-CharacterTextureSizeDrawn+CharWidth[CurrentChar]+CharOffset[CurrentChar];    
    }
    

    if(PosCharX[CurrentChar]+(CharWidth[CurrentChar]/2) > PosCharX[OtherChar]+(CharWidth[OtherChar]/2)){
    if(CharIsLeft[CurrentChar] == 1 && GroundLevel[CurrentChar] == 1 && AnimationType[CurrentChar] == 1){
    CharIsLeft[CurrentChar] = 0;
    DrawCharX[CurrentChar] = PosCharX[CurrentChar]-LeftStageBorder-CharacterTextureSizeDrawn+CharWidth[CurrentChar]+CharOffset[CurrentChar];
    }
    if(CharIsLeft[OtherChar] == 0 && GroundLevel[OtherChar] == 1 && AnimationType[OtherChar] == 1){
    CharIsLeft[OtherChar] = 1;
    DrawCharX[OtherChar] = PosCharX[OtherChar] - LeftStageBorder-CharOffset[OtherChar];
    }
    }


    SpecialEffectDrawX[CurrentChar] = SpecialEffectPosX[CurrentChar] - LeftStageBorder;
    SpecialEffectDrawY[CurrentChar] = SpecialEffectPosY[CurrentChar];