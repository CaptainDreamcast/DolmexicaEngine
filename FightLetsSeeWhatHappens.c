if(Winner == -1){
FightFadingOut(LeftStageBorder, BackGroundHeaderData, BackGroundData, BackGroundAnimationData, BackGroundTextures, CharacterName, CharacterTexture, AnimationBuffer, WhichAnimationFrame, DrawCharX, PosCharY, CharIsLeft, CharPalette, StageGround, ShadowPositionX, ShadowPositionY, CharacterTextureSizeDrawn, CharacterTextureSizeReal, DrawCharDifferently);
FightStage = FightPreRoundReset;
}
else{
FightStage = FightWinningAnimation;
}