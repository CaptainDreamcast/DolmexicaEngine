if(KnockOutAnimationFlag[WhichCharLost] == 1){
printf("Uhhhh\n");
}
else{
    AnimationID[WhichCharLost] = -8;
    MovementReadCompulsory(7, CharacterName[WhichCharLost], AnimationBuffer[WhichCharLost], &CharHitAnimationSpeed[WhichCharLost], &FrameAmount[WhichCharLost], &AnimationLoop[WhichCharLost], &AnimationType[WhichCharLost]);
    WhichAnimationFrame[WhichCharLost] = 1;
    AnimationTicks[WhichCharLost] = 1;
    AnimationSpeed[WhichCharLost] = 61;
}
if(AnimationType[WhichCharWon] != 3) AnimationSpeed[WhichCharWon] = 10;

FightStage = FightKnockOutAnimation;