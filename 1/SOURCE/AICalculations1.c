
TemporaryAnimationID1 = -1;
AnimationValidityCheck1 = 0;


if(TimeSlotTicks1%TimeSlotLength1 == 0){

WhichAIPattern1 = 0;

srand( rtc_unix_secs()+TimerTicks);
RandomAINumber1 = (1+(rand()%10));

//printf("Random Number: %d!\n", RandomAINumber1);

if(GroundLevel1 == 1 && CrouchPosition1 == 0 && CharHitStatus1 == 0){

TemporaryAnimationID1 = 0;
TimeSlotLength1 = 60;
TimeSlotTicks1 = 0;

if(((DrawCharX1+256-CharOffset1-CharWidth1 > DrawCharX2+CharOffset2+CharWidth2+20 && CharIsLeft2 == 1) || (DrawCharX2+256-CharOffset2-CharWidth2 > DrawCharX1+CharOffset1+CharWidth1+20 && CharIsLeft2 == 0))&& RandomAINumber1 <= 1){
TemporaryAnimationID1 = 1;
WhichAIPattern1 = 1;
TimeSlotLength1 = 30;
TimeSlotTicks1 = 0;
}

if(CharHealth1 < 250 && RandomAINumber1 <= 1){
TemporaryAnimationID1 = 2;
WhichAIPattern1 = 4;
TimeSlotLength1 = 30;
TimeSlotTicks1 = 0;
}

if(RandomAINumber1 > 5){
WhichAIPattern1 = 2;
TimeSlotLength1 = 30000;
TimeSlotTicks1 = 0;
}

if(RandomAINumber1 >= 3 && RandomAINumber1 <= 5){

WhichAIPattern1 = 3;
TimeSlotLength1 = 30000;
TimeSlotTicks1 = 0;
TemporaryAnimationID1 = -1;

GroundLevel1 = 0;
JumpBlock1 = 1;
if(RandomAINumber1 == 3){ 
JumpAnimationFlags1 = JumpBackFlags1; 
JumpType1 = 2; 
if(CharIsLeft1 == 0) JumpDirection1 = CharSpeed1;
else JumpDirection1 = -CharSpeed1;
}
else if(RandomAINumber1 == 4){ 
JumpAnimationFlags1 = JumpForwardFlags1; 
JumpType1 = 1;
if(CharIsLeft1 == 1) JumpDirection1 = CharSpeed1;
else JumpDirection1 = -CharSpeed1;
 }
else{ JumpAnimationFlags1 = JumpIdleUpFlags1; JumpType1 = 0; }
WhichJumpStage1 = 1;
JumpReadCompulsory(0, CharacterName1, JumpNameBuffer1, &JumpAnimationSpeed1, &JumpFrameAmount1, &JumpLoop1, JumpType1);
AnimationID1 = -100-WhichJumpStage1;
AnimationLoop1 = JumpLoop1;
FrameAmount1 = JumpFrameAmount1;
AnimationSpeed1 = JumpAnimationSpeed1;
for (i=0; i<8; i++) AnimationBuffer1[i] = JumpNameBuffer1[i];
WhichJumpFrame1 = 1;
JumpTicks1 = 1;	
JumpVelocity1 = JumpStrength1*JumpFrameAmount1+JumpFrameAmount1*JumpAnimationSpeed1;
WhichAnimationFrame1 = 1;
AnimationTicks1 = 1;
}

}
}

if(WhichAIPattern1 == 1 && CharHitStatus1 == 0){ //Just Walking Forward
if(CharIsLeft1 == 0) PosCharX1 -= CharSpeed1;
else PosCharX1 += CharSpeed1;
}

if(WhichAIPattern1 == 4 && CharHitStatus1 == 0){ //Just Walking Backward
if(CharIsLeft1 == 0) PosCharX1 += CharSpeed1;
else PosCharX1 -= CharSpeed1;
}

if(WhichAIPattern1 == 2 && CharHitStatus1 == 0){ //Rush Attack!

if((DrawCharX1+256-CharOffset1-CharWidth1 > DrawCharX2+CharOffset2+CharWidth2+20 && CharIsLeft1 == 0) || (DrawCharX2+256-CharOffset2-CharWidth2 > DrawCharX1+CharOffset1+CharWidth1+20 && CharIsLeft1 == 1)){
TemporaryAnimationID1 = 1;
if(CharIsLeft1 == 0)PosCharX1 -= CharSpeed1;
else PosCharX1 += CharSpeed1;
}
else{
AttackSelectCPU(&TemporaryAnimationID1, CharacterName1, DrawCharX1, PosCharY1, DrawCharX2, PosCharY2, GroundLevel1, GroundLevel2, CrouchPosition1, CrouchPosition2, 0, CharIsLeft1, CharIsLeft2, CharOffset1, CharOffset2, CharWidth1, CharWidth2); //Insert some Attack Here. Weak Punch?
//TemporaryAnimationID1 = 22;
WhichAIPattern1 = 0;
TimeSlotTicks1 = -1;
}
}

if(WhichAIPattern1 == 3 && GroundLevel1 == 1){ //Give AI control again after just jumping forward
TimeSlotLength1 = 10;
TimeSlotTicks1 = 0;
WhichAIPattern1 = 0;
}

if((AnimationType2 == 3 || AnimationType2 == 6) && AnimationType1 == 1 && GroundLevel1 == 1 && AnimationID1 != -10){ //Try'n block that, sucker!

srand( rtc_unix_secs()+TimerTicks);
RandomAINumber1 = (1+(rand()%10));
if(RandomAINumber1 < 9 ){
if(CrouchPosition1 != 0){
MovementReadCompulsory(10, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
//AnimationName1 = "CROUBLOC";
AnimationID1 = -11;

WhichAnimationFrame1 = 1;
AnimationTicks1 = 1;
AnimationLoop1 = 1;

TimeSlotLength1 = FrameAmount2*AnimationSpeed2; //-(WhichAnimationFrame2-1)*AnimationSpeed2;
TimeSlotTicks1 = 1;
WhichAIPattern1 = 0;
}
else if(CrouchPosition1 == 0 && CrouchPosition2 == 0){
MovementReadCompulsory(9, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
//AnimationName1 = "BLOCKING";
AnimationID1 = -10;

WhichAnimationFrame1 = 1;
AnimationTicks1 = 1;
AnimationLoop1 = 1;

TimeSlotLength1 = FrameAmount2*AnimationSpeed2; //-(WhichAnimationFrame2-1)*AnimationSpeed2;
TimeSlotTicks1 = 1;
WhichAIPattern1 = 0;
}

}
}

if(TemporaryAnimationID1 != -1){
AnimationValidityCheck1 = MovementReadCPU(TemporaryAnimationID1, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationEnemyAcceleration1, &AnimationType1, &AnimationStrength1, &WhichSpecial1, &WhichMissSoundEffect1, &WhichSoundEffectFrame1 ,&WhichHitSoundEffect1);
}
if(AnimationValidityCheck1 == 1 && AnimationID1 != TemporaryAnimationID1){
AnimationName1 = AnimationBuffer1;
WhichAnimationFrame1 = 1;
AnimationTicks1 = 1;
AnimationID1 = TemporaryAnimationID1;
if(TimeSlotTicks1 == -1) {
TimeSlotTicks1 = 0;
TimeSlotLength1 = FrameAmount1*AnimationSpeed1;
}
}
if(TimeSlotTicks1 < 65000) TimeSlotTicks1++;
else TimeSlotTicks1 = 0;