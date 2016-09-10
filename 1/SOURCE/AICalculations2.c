
TemporaryAnimationID2 = -1;
AnimationValidityCheck2 = 0;


if(TimeSlotTicks2%TimeSlotLength2 == 0){

WhichAIPattern2 = 0;

srand( rtc_unix_secs()+TimerTicks);
RandomAINumber2 = (1+(rand()%10));

//printf("Random Number: %d!\n", RandomAINumber2);

if(GroundLevel2 == 1 && CrouchPosition2 == 0 && CharHitStatus2 == 0){

TemporaryAnimationID2 = 0;
TimeSlotLength2 = 60;
TimeSlotTicks2 = 0;

if(((DrawCharX2+256-CharOffset2-CharWidth2 > DrawCharX1+CharOffset1+CharWidth1+20 && CharIsLeft1 == 1) || (DrawCharX1+256-CharOffset1-CharWidth1 > DrawCharX2+CharOffset2+CharWidth2+20 && CharIsLeft1 == 0))&& RandomAINumber2 <= 1){
TemporaryAnimationID2 = 1;
WhichAIPattern2 = 1;
TimeSlotLength2 = 30;
TimeSlotTicks2 = 0;
}

if(CharHealth2 < 250 && RandomAINumber2 <= 1){
TemporaryAnimationID2 = 2;
WhichAIPattern2 = 4;
TimeSlotLength2 = 30;
TimeSlotTicks2 = 0;
}

if(RandomAINumber2 > 6){
WhichAIPattern2 = 2;
TimeSlotLength2 = 30000;
TimeSlotTicks2 = 0;
}

if(RandomAINumber2 == 6){

AnimationID2 = -4;
MovementReadCompulsory(3, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
//AnimationName2 = "CROU_PRE";
WhichAnimationFrame2 = 1;
AnimationTicks2 = 1;
DirectionalInputAllowed2 = 0;
CrouchPosition2 = 1;

WhichAIPattern2 = -1;
TimeSlotLength2 = 30000;
TimeSlotTicks2 = 0;
TemporaryAnimationID2 = -1;
}

if(RandomAINumber2 >= 3 && RandomAINumber2 <= 5){

WhichAIPattern2 = 3;
TimeSlotLength2 = 30000;
TimeSlotTicks2 = 0;
TemporaryAnimationID2 = -1;

GroundLevel2 = 0;
JumpBlock2 = 1;
if(RandomAINumber2 == 3){ 
JumpAnimationFlags2 = JumpBackFlags2; 
JumpType2 = 2; 
if(CharIsLeft2 == 0) JumpDirection2 = CharSpeed2;
else JumpDirection2 = -CharSpeed2;
}
else if(RandomAINumber2 == 4){ 
JumpAnimationFlags2 = JumpForwardFlags2; 
JumpType2 = 1;
if(CharIsLeft2 == 1) JumpDirection2 = CharSpeed2;
else JumpDirection2 = -CharSpeed2;
 }
else{ JumpAnimationFlags2 = JumpIdleUpFlags2; JumpType2 = 0; }
WhichJumpStage2 = 1;
JumpReadCompulsory(0, CharacterName2, JumpNameBuffer2, &JumpAnimationSpeed2, &JumpFrameAmount2, &JumpLoop2, JumpType2);
AnimationID2 = -100-WhichJumpStage2;
AnimationLoop2 = JumpLoop2;
FrameAmount2 = JumpFrameAmount2;
AnimationSpeed2 = JumpAnimationSpeed2;
for (i=0; i<8; i++) AnimationBuffer2[i] = JumpNameBuffer2[i];
WhichJumpFrame2 = 1;
JumpTicks2 = 1;	
JumpVelocity2 = JumpStrength2*JumpFrameAmount2+JumpFrameAmount2*JumpAnimationSpeed2;
WhichAnimationFrame2 = 1;
AnimationTicks2 = 1;
}

}
else if(CrouchPosition2 == 2 && CharHitStatus2 == 0){

TemporaryAnimationID2 = 4;
TimeSlotLength2 = 60;
TimeSlotTicks2 = 0;


if(RandomAINumber2 == 6){

AnimationID2 = -1;
MovementReadCompulsory(0, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
//AnimationName2 = "STANDING";
WhichAnimationFrame2 = 1;
AnimationTicks2 = 1;


DirectionalInputAllowed2 = 0;
CrouchPosition2 = 0;
WhichAIPattern2 = -1;
TimeSlotLength2 = 60;
TimeSlotTicks2 = 0;
TemporaryAnimationID2 = -1;
}
else if(RandomAINumber2 > 6){
AttackSelectCPU(&TemporaryAnimationID2, CharacterName2, DrawCharX2, PosCharY2, DrawCharX1, PosCharY1, GroundLevel2, GroundLevel1, CrouchPosition2, CrouchPosition1, 0, CharIsLeft2, CharIsLeft1, CharOffset2, CharOffset1, CharWidth2, CharWidth2); //Insert some Attack Here. Weak Punch?
//TemporaryAnimationID2 = 22;
WhichAIPattern2 = 0;
TimeSlotTicks2 = -1;
}
}
}

if (CrouchPosition2 == 1 && AnimationTicks2 >= AnimationSpeed2 && WhichAnimationFrame2 >= FrameAmount2 && AnimationType2 == 1) {

AnimationID2 = -5;
MovementReadCompulsory(4, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
//AnimationName2 = "CROU_DUR";
WhichAnimationFrame2 = 1;
AnimationTicks2 = 1;
CrouchPosition2 = 2;
TimeSlotLength2 = 10;
TimeSlotTicks2 = 0;
WhichAIPattern2 = 0;
}

if(WhichAIPattern2 == 1 && CharHitStatus2 == 0){ //Just Walking Forward
if(CharIsLeft2 == 0) PosCharX2 -= CharSpeed2;
else PosCharX2 += CharSpeed2;
}

if(WhichAIPattern2 == 4 && CharHitStatus2 == 0){ //Just Walking Backward
if(CharIsLeft2 == 0) PosCharX2 += CharSpeed2;
else PosCharX2 -= CharSpeed2;
}

if(WhichAIPattern2 == 2 && CharHitStatus2 == 0){ //Rush Attack!

if(CrouchPosition1 != 0 && GroundLevel2 == 1 && ((DrawCharX2+256-CharOffset2-CharWidth2-JumpLength2 < DrawCharX1+CharOffset1+CharWidth1+20 && CharIsLeft2 == 0) || (DrawCharX1+256-CharOffset1-CharWidth1-20 < DrawCharX2+CharOffset2+CharWidth2+JumpLength2 && CharIsLeft2 == 1))){

GroundLevel2 = 0;
JumpBlock2 = 1;

JumpAnimationFlags2 = JumpForwardFlags2; 
JumpType2 = 1;

if(CharIsLeft2 == 1) JumpDirection2 = CharSpeed2;
else JumpDirection2 = -CharSpeed2;

WhichJumpStage2 = 1;
JumpReadCompulsory(0, CharacterName2, JumpNameBuffer2, &JumpAnimationSpeed2, &JumpFrameAmount2, &JumpLoop2, JumpType2);
AnimationID2 = -100-WhichJumpStage2;
AnimationLoop2 = JumpLoop2;
FrameAmount2 = JumpFrameAmount2;
AnimationSpeed2 = JumpAnimationSpeed2;
for (i=0; i<8; i++) AnimationBuffer2[i] = JumpNameBuffer2[i];
WhichJumpFrame2 = 1;
JumpTicks2 = 1;	
JumpVelocity2 = JumpStrength2*JumpFrameAmount2+JumpFrameAmount2*JumpAnimationSpeed2;
WhichAnimationFrame2 = 1;
AnimationTicks2 = 1;

}
if((DrawCharX2+256-CharOffset2-CharWidth2 > DrawCharX1+CharOffset1+CharWidth1+20 && CharIsLeft2 == 0) || (DrawCharX1+256-CharOffset1-CharWidth1 > DrawCharX2+CharOffset2+CharWidth2+20 && CharIsLeft2 == 1)){
if(GroundLevel2 == 1){
TemporaryAnimationID2 = 1;
if(CharIsLeft2 == 0)PosCharX2 -= CharSpeed2;
else PosCharX2 += CharSpeed2;
}
}
else if(CrouchPosition1 == 0 || GroundLevel2 == 0){
AttackSelectCPU(&TemporaryAnimationID2, CharacterName2, DrawCharX2, PosCharY2, DrawCharX1, PosCharY1, GroundLevel2, GroundLevel1, CrouchPosition2, CrouchPosition1, 0, CharIsLeft2, CharIsLeft1, CharOffset2, CharOffset1, CharWidth2, CharWidth2); //Insert some Attack Here. Weak Punch?
//TemporaryAnimationID2 = 22;
WhichAIPattern2 = 0;
TimeSlotTicks2 = -1;
}
else{
AnimationID2 = -4;
MovementReadCompulsory(3, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
//AnimationName2 = "CROU_PRE";
WhichAnimationFrame2 = 1;
AnimationTicks2 = 1;
DirectionalInputAllowed2 = 0;
CrouchPosition2 = 1;

WhichAIPattern2 = -1;
TimeSlotLength2 = 30000;
TimeSlotTicks2 = 0;
TemporaryAnimationID2 = -1;
}
}

if(WhichAIPattern2 == 3 && GroundLevel2 == 1){ //Give AI control again after just jumping forward
TimeSlotLength2 = 10;
TimeSlotTicks2 = 0;
WhichAIPattern2 = 0;
}

if((AnimationType1 == 3 || AnimationType1 == 6) && AnimationType2 == 1 && GroundLevel2 == 1 && AnimationID2 != -10 && AnimationID2 != -11){ //Try'n block that, sucker!

srand( rtc_unix_secs()+TimerTicks);
RandomAINumber2 = (1+(rand()%10));
if(RandomAINumber2 < 9 ){
if(CrouchPosition2 != 0){
MovementReadCompulsory(10, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
//AnimationName2 = "CROUBLOC";
AnimationID2 = -11;

WhichAnimationFrame2 = 1;
AnimationTicks2 = 1;
AnimationLoop2 = 1;

CrouchPosition2 = 2;

TimeSlotLength2 = FrameAmount1*AnimationSpeed1; //-(WhichAnimationFrame1-1)*AnimationSpeed1;
TimeSlotTicks2 = 1;
WhichAIPattern2 = 0;
}
else if(CrouchPosition2 == 0 && CrouchPosition1 == 0){
MovementReadCompulsory(9, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
//AnimationName2 = "BLOCKING";
AnimationID2 = -10;

WhichAnimationFrame2 = 1;
AnimationTicks2 = 1;
AnimationLoop2 = 1;

TimeSlotLength2 = FrameAmount1*AnimationSpeed1; //-(WhichAnimationFrame1-1)*AnimationSpeed1;
TimeSlotTicks2 = 1;
WhichAIPattern2 = 0;
}

}
}

if(TemporaryAnimationID2 != -1){
AnimationValidityCheck2 = MovementReadCPU(TemporaryAnimationID2, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationEnemyAcceleration2, &AnimationType2, &AnimationStrength2, &WhichSpecial2, &WhichMissSoundEffect2, &WhichSoundEffectFrame2 ,&WhichHitSoundEffect2);
}
if(AnimationValidityCheck2 == 1 && AnimationID2 != TemporaryAnimationID2){
AnimationName2 = AnimationBuffer2;
WhichAnimationFrame2 = 1;
AnimationTicks2 = 1;
AnimationID2 = TemporaryAnimationID2;
if(TimeSlotTicks2 == -1) {
TimeSlotTicks2 = 0;
TimeSlotLength2 = FrameAmount2*AnimationSpeed2;
}
}
if(TimeSlotTicks2 < 65000) TimeSlotTicks2++;
else TimeSlotTicks2 = 0;