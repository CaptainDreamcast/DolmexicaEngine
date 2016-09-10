if(CharHealth[CharacterOne] == CharHealth[CharacterTwo]){

CurrentChar = CharacterOne;
do{

AnimationID[CurrentChar] = -6;
MovementReadCompulsory(5, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &CharHitAnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
WhichAnimationFrame[CurrentChar] = 1;
AnimationTicks[CurrentChar] = 1;

CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);

FightStage = FightLetsSeeWhatHappens;
}
else{

CurrentChar = CharacterOne;
OtherChar = CharacterTwo;
do{

if(CharHealth[CurrentChar] < CharHealth[OtherChar]){

WhichCharWon = OtherChar;
WhichCharLost = CurrentChar;

AnimationID[CurrentChar] = -6;
MovementReadCompulsory(5, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &CharHitAnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
WhichAnimationFrame[CurrentChar] = 1;
AnimationTicks[CurrentChar] = 1;
}

CurrentChar++;
OtherChar--;
} while(CurrentChar <= MaxCharsLoopValue);

FightStage = FightVictoryPose;
}