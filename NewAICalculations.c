
TemporaryAnimationID[CurrentChar] = -1;
AnimationValidityCheck[CurrentChar] = 0;


if(TimeSlotTicks[CurrentChar] >= TimeSlotLength[CurrentChar]){

WhichAIPattern[CurrentChar] = 0;
TimeSlotTicks[CurrentChar] = 0;

if(CharHitStatus[CurrentChar] == 0){
WhichAIPattern[CurrentChar] = AttackSelectCPU(
&TemporaryAnimationID[CurrentChar], CharacterName[CurrentChar], DrawCharX[CurrentChar], PosCharY[CurrentChar], 
DrawCharX[OtherChar], PosCharY[OtherChar], GroundLevel[CurrentChar], GroundLevel[OtherChar], 
CrouchPosition[CurrentChar], CrouchPosition[OtherChar], 0, CharIsLeft[CurrentChar], CharIsLeft[OtherChar], 
CharOffset[CurrentChar], CharOffset[OtherChar], CharWidth[CurrentChar], CharWidth[OtherChar], CharacterTextureSizeDrawn,
AnimationType[CurrentChar], AnimationType[OtherChar], CharHitStatus[CurrentChar], CharHitStatus[OtherChar], 
CharHealth[CurrentChar], CharHealth[OtherChar], SpecialEffectStage, 
TimerTicks, Difficulty, NeedsMoreCounters, CurrentChar, OtherChar
);}
else WhichAIPattern[CurrentChar] = ComputerAttackSelectNoAttackFound;

if(WhichAIPattern[CurrentChar] == ComputerAttackSelectSomethingMessedUp || WhichAIPattern[CurrentChar] == ComputerAttackSelectNoAttackFound){

if(GroundLevel[CurrentChar] && CharHitStatus[CurrentChar] == 0){ 
if(CrouchPosition[CurrentChar] == 0) TemporaryAnimationID[CurrentChar] = CompulsoryIdleIdentifier;
else if(CrouchPosition[CurrentChar] == 2) TemporaryAnimationID[CurrentChar] = CompulsoryCrouchIdentifier;
}

WhichAIPattern[CurrentChar] = 0;
TimeSlotLength[CurrentChar] = 1;
}//-------------------------------------------------------------------------------------------------------
else if(WhichAIPattern[CurrentChar] == ComputerAttackSelectAttackFound){
WhichAIPattern[CurrentChar] = 0;
TimeSlotLength[CurrentChar] = -1;

TimeSlotTicks[CurrentChar] = -1;
}//-------------------------------------------------------------------------------------------------------
else if(WhichAIPattern[CurrentChar] == ComputerAttackSelectMoveForward){

if(CharIsLeft[CurrentChar] == 0) PosCharX[CurrentChar] -= CharSpeed[CurrentChar];
else PosCharX[CurrentChar] += CharSpeed[CurrentChar];

TemporaryAnimationID[CurrentChar] = CompulsoryWalkingForwardIdentifier;

WhichAIPattern[CurrentChar] = 0;
TimeSlotLength[CurrentChar] = 1;
}//-------------------------------------------------------------------------------------------------------
else if(WhichAIPattern[CurrentChar] == ComputerAttackSelectMoveBack){

if(CharIsLeft[CurrentChar] == 1) PosCharX[CurrentChar] -= CharSpeed[CurrentChar];
else PosCharX[CurrentChar] += CharSpeed[CurrentChar];

TemporaryAnimationID[CurrentChar] = CompulsoryWalkingBackIdentifier;

WhichAIPattern[CurrentChar] = 0;
TimeSlotLength[CurrentChar] = 1;
}//-------------------------------------------------------------------------------------------------------
else if(WhichAIPattern[CurrentChar] == ComputerAttackSelectJumpIdleUp){

JumpDirection[CurrentChar] = 0;
JumpAnimationFlags[CurrentChar] = JumpIdleUpFlags[CurrentChar];
JumpStrength[CurrentChar] = JumpIdleUpStrength[CurrentChar];
JumpType[CurrentChar] = 0;

DirectionalInputAllowed[CurrentChar] = 0;
ButtonInputAllowed[CurrentChar] = 0;
GroundLevel[CurrentChar] = 0;
JumpBlock[CurrentChar] = 1;

WhichJumpStage[CurrentChar] = 1;
JumpReadCompulsory(0, CharacterName[CurrentChar], JumpNameBuffer[CurrentChar], &JumpAnimationSpeed[CurrentChar], &JumpFrameAmount[CurrentChar], &JumpLoop[CurrentChar], JumpType[CurrentChar]);
WhichJumpFrame[CurrentChar] = 1;
JumpTicks[CurrentChar] = 1;	
JumpVelocity[CurrentChar] = JumpStrength[CurrentChar]*JumpFrameAmount[CurrentChar]+JumpFrameAmount[CurrentChar]*JumpAnimationSpeed[CurrentChar];

WhichAIPattern[CurrentChar] = 0;
TimeSlotLength[CurrentChar] = -1;
}//-------------------------------------------------------------------------------------------------------
else if(WhichAIPattern[CurrentChar] == ComputerAttackSelectJumpForward){

if(CharIsLeft[CurrentChar] == 0) JumpDirection[CurrentChar] = -JumpForwardSpeed[CurrentChar];
else JumpDirection[CurrentChar] = JumpForwardSpeed[CurrentChar];

JumpAnimationFlags[CurrentChar] = JumpForwardFlags[CurrentChar];
JumpStrength[CurrentChar] = JumpForwardStrength[CurrentChar];
JumpType[CurrentChar] = 1;

DirectionalInputAllowed[CurrentChar] = 0;
ButtonInputAllowed[CurrentChar] = 0;
GroundLevel[CurrentChar] = 0;
JumpBlock[CurrentChar] = 1;

WhichJumpStage[CurrentChar] = 1;
JumpReadCompulsory(0, CharacterName[CurrentChar], JumpNameBuffer[CurrentChar], &JumpAnimationSpeed[CurrentChar], &JumpFrameAmount[CurrentChar], &JumpLoop[CurrentChar], JumpType[CurrentChar]);
WhichJumpFrame[CurrentChar] = 1;
JumpTicks[CurrentChar] = 1;	
JumpVelocity[CurrentChar] = JumpStrength[CurrentChar]*JumpFrameAmount[CurrentChar]+JumpFrameAmount[CurrentChar]*JumpAnimationSpeed[CurrentChar];

WhichAIPattern[CurrentChar] = 0;
TimeSlotLength[CurrentChar] = -1;
}//-------------------------------------------------------------------------------------------------------
else if(WhichAIPattern[CurrentChar] == ComputerAttackSelectJumpBack){

if(CharIsLeft[CurrentChar] == 1) JumpDirection[CurrentChar] = -JumpBackSpeed[CurrentChar];
else JumpDirection[CurrentChar] = JumpBackSpeed[CurrentChar];

JumpAnimationFlags[CurrentChar] = JumpBackFlags[CurrentChar];
JumpStrength[CurrentChar] = JumpBackStrength[CurrentChar];
JumpType[CurrentChar] = 2;

DirectionalInputAllowed[CurrentChar] = 0;
ButtonInputAllowed[CurrentChar] = 0;
GroundLevel[CurrentChar] = 0;
JumpBlock[CurrentChar] = 1;

WhichJumpStage[CurrentChar] = 1;
JumpReadCompulsory(0, CharacterName[CurrentChar], JumpNameBuffer[CurrentChar], &JumpAnimationSpeed[CurrentChar], &JumpFrameAmount[CurrentChar], &JumpLoop[CurrentChar], JumpType[CurrentChar]);
WhichJumpFrame[CurrentChar] = 1;
JumpTicks[CurrentChar] = 1;	
JumpVelocity[CurrentChar] = JumpStrength[CurrentChar]*JumpFrameAmount[CurrentChar]+JumpFrameAmount[CurrentChar]*JumpAnimationSpeed[CurrentChar];

WhichAIPattern[CurrentChar] = 0;
TimeSlotLength[CurrentChar] = -1;
}//-------------------------------------------------------------------------------------------------------
else if(WhichAIPattern[CurrentChar] == ComputerAttackSelectCrouchBlock){

TemporaryAnimationID[CurrentChar] = CompulsoryCrouchBlockIdentifier;

WhichAIPattern[CurrentChar] = 0;
TimeSlotLength[CurrentChar] = 1;
}//-------------------------------------------------------------------------------------------------------
else if(WhichAIPattern[CurrentChar] == ComputerAttackSelectBlock){

TemporaryAnimationID[CurrentChar] = CompulsoryBlockIdentifier;

WhichAIPattern[CurrentChar] = 0;
TimeSlotLength[CurrentChar] = 1;
}//-------------------------------------------------------------------------------------------------------
else if(WhichAIPattern[CurrentChar] == ComputerAttackSelectIntoCrouch){

TemporaryAnimationID[CurrentChar] = CompulsoryIntoCrouchIdentifier;

CrouchPosition[CurrentChar] = 1;

WhichAIPattern[CurrentChar] = ArtificialIntelligenceIntoCrouchPattern;
TimeSlotLength[CurrentChar] = ArtificialIntelligencePatternInfiniteLength;
}//-------------------------------------------------------------------------------------------------------
else if(WhichAIPattern[CurrentChar] == ComputerAttackSelectStandUp){

TemporaryAnimationID[CurrentChar] = CompulsoryIntoCrouchIdentifier;

CrouchPosition[CurrentChar] = 1;

WhichAIPattern[CurrentChar] = ArtificialIntelligenceStandUpPattern;
TimeSlotLength[CurrentChar] = ArtificialIntelligencePatternInfiniteLength;
}//-------------------------------------------------------------------------------------------------------


}

if(CrouchPosition[CurrentChar] == 1 && AnimationTicks[CurrentChar] >= AnimationSpeed[CurrentChar] && WhichAnimationFrame[CurrentChar] >= FrameAmount[CurrentChar]){
if(WhichAIPattern[CurrentChar] == ArtificialIntelligenceIntoCrouchPattern){

TemporaryAnimationID[CurrentChar] = CompulsoryCrouchIdentifier;
CrouchPosition[CurrentChar] = 2;
}
else if(WhichAIPattern[CurrentChar] == ArtificialIntelligenceStandUpPattern){

TemporaryAnimationID[CurrentChar] = CompulsoryIdleIdentifier;
CrouchPosition[CurrentChar] = 0;
}

WhichAIPattern[CurrentChar] = 0;
TimeSlotLength[CurrentChar] = 1;
TimeSlotTicks[CurrentChar] = 0;

}


if(TemporaryAnimationID[CurrentChar] != -1){
AnimationValidityCheck[CurrentChar] = MovementReadCPU(TemporaryAnimationID[CurrentChar], CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationEnemyAccelerationX[CurrentChar], &AnimationEnemyAccelerationY[CurrentChar], &AnimationType[CurrentChar], &AnimationStrength[CurrentChar], &WhichSpecial[CurrentChar], &WhichMissSoundEffect[CurrentChar], &WhichSoundEffectFrame[CurrentChar] ,&WhichHitSoundEffect[CurrentChar], &AnimationAddOn[CurrentChar]);
}
if(AnimationValidityCheck[CurrentChar] == 1 && AnimationID[CurrentChar] != TemporaryAnimationID[CurrentChar]){
WhichAnimationFrame[CurrentChar] = 1;
AnimationTicks[CurrentChar] = 1;
AnimationID[CurrentChar] = TemporaryAnimationID[CurrentChar];
if(TimeSlotTicks[CurrentChar] == -1) {
TimeSlotTicks[CurrentChar] = 0;
TimeSlotLength[CurrentChar] = FrameAmount[CurrentChar]*AnimationSpeed[CurrentChar];
}
}
if(TimeSlotTicks[CurrentChar] < 65000) TimeSlotTicks[CurrentChar]++;
else TimeSlotTicks[CurrentChar] = 0;