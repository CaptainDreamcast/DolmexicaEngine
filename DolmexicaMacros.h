#define DrawCharStandard() DrawChar(CharacterName[CurrentChar], &CharacterTexture[CurrentChar], AnimationBuffer[CurrentChar], WhichAnimationFrame[CurrentChar], DrawCharX[CurrentChar], PosCharY[CurrentChar], CharIsLeft[CurrentChar], CharPalette[CurrentChar], StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn, DrawCharDifferently[CurrentChar])
#define DrawCharLiteStandard() DrawCharLite(&CharacterTexture[CurrentChar], DrawCharX[CurrentChar], PosCharY[CurrentChar], CharIsLeft[CurrentChar], CharPalette[CurrentChar], StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn, CharacterTextureSizeReal[CurrentChar], DrawCharDifferently[CurrentChar])

#define CheckColor(Color, Red, Green, Blue, Max, Min) { \
if(Color == BlackColor) Red = Green = Blue = Min; \
else if(Color == RedColor){ Red = Max; Green = Blue = Min;} \
else if(Color == GreenColor){ Green = Max; Red = Blue = Min;} \
else if(Color == BlueColor){ Blue = Max; Green = Red = Min;} \
else if(Color == YellowColor){ Green = Red = Max; Blue = Min;} \
else Red = Green = Blue = 1.0f; \
}

