//StatusAilmentCode

switch(CharacterStatusAilment[CurrentChar]){

case CharacterIsBurning:
printf("CharacterBurns!\n");
break;

case CharacterIsFrozen:
StatusAilmentDuration[CurrentChar]--;
if(StatusAilmentDuration[CurrentChar] > 0){ 

DirectionalInputAllowed[CurrentChar] = 0; ButtonInputAllowed[CurrentChar] = 0; 

}
else{
CharacterStatusAilment[CurrentChar] = CharacterIsNormal;
TimeSlotTicks[CurrentChar] = 0;
CharHitStatus[CurrentChar] = 0;

if(CrouchPosition[CurrentChar] == 0){
AnimationID[CurrentChar] = -1;
MovementReadCompulsory(0, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
//AnimationName[CurrentChar] = "STANDING";
WhichAnimationFrame[CurrentChar] = 1;
AnimationTicks[CurrentChar] = 1;
}
else{
CrouchPosition[CurrentChar] = 2;

AnimationID[CurrentChar] = -5;
MovementReadCompulsory(4, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
//AnimationName[CurrentChar] = "CROU_DUR";
WhichAnimationFrame[CurrentChar] = 1;
AnimationTicks[CurrentChar] = 1;

}

DirectionalInputAllowed[CurrentChar] = 1;
}
break;

case CharacterIsProtected:
printf("CharacterIsProtected!\n");
break;

default: break;
}