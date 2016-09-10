
    if((cont = maple_enum_dev(CurrentChar, 0)) != NULL) {

    st = (cont_state_t *)maple_dev_status(cont);



    if ((st->buttons & CONT_START) && ButtonInputAllowed[CurrentChar] == 1) {
            FightStage = FightMenu;
			}

    if (((st->buttons & CONT_DPAD_UP)  || (st->joyy <= -64)) && DirectionalInputAllowed[CurrentChar] == 1 && GroundLevel[CurrentChar] == 1 && JumpVelocity[CurrentChar] == -480 && JumpBlock[CurrentChar] == 0) {

            //WhichAnimationFrame[CurrentChar] = 1;
            //AnimationTicks[CurrentChar] = 1;

            if (((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64))){
             if(CharIsLeft[CurrentChar] == 1){
              JumpAnimationFlags[CurrentChar] = JumpForwardFlags[CurrentChar];
              JumpStrength[CurrentChar] = JumpForwardStrength[CurrentChar];
              JumpDirection[CurrentChar] = JumpForwardSpeed[CurrentChar];
              JumpType[CurrentChar] = 1;
              }
             else{
             JumpAnimationFlags[CurrentChar] = JumpBackFlags[CurrentChar];
             JumpStrength[CurrentChar] = JumpBackStrength[CurrentChar];
             JumpDirection[CurrentChar] = JumpBackSpeed[CurrentChar];
             JumpType[CurrentChar] = 2;
              }
             }
            else if (((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64))){
             if(CharIsLeft[CurrentChar] == 0){
              JumpAnimationFlags[CurrentChar] = JumpForwardFlags[CurrentChar];
             JumpStrength[CurrentChar] = JumpForwardStrength[CurrentChar];
             JumpDirection[CurrentChar] = -JumpForwardSpeed[CurrentChar];
              JumpType[CurrentChar] = 1;
              }
             else{
             JumpAnimationFlags[CurrentChar] = JumpBackFlags[CurrentChar];
             JumpStrength[CurrentChar] = JumpBackStrength[CurrentChar];
             JumpDirection[CurrentChar] = -JumpBackSpeed[CurrentChar];
             JumpType[CurrentChar] = 2;
              }
             }
            else{
             JumpAnimationFlags[CurrentChar] = JumpIdleUpFlags[CurrentChar];
             JumpStrength[CurrentChar] = JumpIdleUpStrength[CurrentChar];
             JumpType[CurrentChar] = 0;
             }

            DirectionalInputAllowed[CurrentChar] = 0;
            ButtonInputAllowed[CurrentChar] = 0;

            GroundLevel[CurrentChar] = 0;
            JumpBlock[CurrentChar] = 1;

            WhichJumpStage[CurrentChar] = 1;
            JumpReadCompulsory(0, CharacterName[CurrentChar], JumpNameBuffer[CurrentChar], &JumpAnimationSpeed[CurrentChar], &JumpFrameAmount[CurrentChar], &JumpLoop[CurrentChar], JumpType[CurrentChar]);

            WhichJumpFrame[CurrentChar] = 1;
            JumpTicks[CurrentChar] = 1;	
            JumpVelocity[CurrentChar] = JumpStrength[CurrentChar]*JumpFrameAmount[CurrentChar]+JumpFrameAmount[CurrentChar]*JumpAnimationSpeed[CurrentChar];
	}

   if (!(st->buttons & CONT_DPAD_UP)  && (st->joyy > -64) && GroundLevel[CurrentChar] == 1 && JumpBlock[CurrentChar] == 1) {

    JumpBlock[CurrentChar] = 0;
   }

if((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)){


            if(BackBlocking[CurrentChar] && CrouchPosition[CurrentChar] != 0 && AnimationType[CurrentChar] == 1 && (AnimationType[OtherChar] == 3 || AnimationType[OtherChar] == 6) && ((CharIsLeft[CurrentChar] == 0 && (st->buttons & CONT_DPAD_RIGHT)) || (CharIsLeft[CurrentChar] == 1 && (st->buttons & CONT_DPAD_LEFT)))){
            if(AnimationID[CurrentChar] != -11){
            MovementReadCompulsory(10, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
            //AnimationName[CurrentChar] = "CROUBLOC";
            WhichAnimationFrame[CurrentChar] = 1; 
            AnimationTicks[CurrentChar] = 1;
            AnimationID[CurrentChar] = -11;

            CrouchPosition[CurrentChar] = 2;
           
            }
            }

   else if (AnimationType[CurrentChar] == 1 && DirectionalInputAllowed[CurrentChar] == 1 && GroundLevel[CurrentChar] == 1 && JumpVelocity[CurrentChar] == -480 && CrouchPosition[CurrentChar] != 2) {


            if(AnimationID[CurrentChar] != -4){
            AnimationID[CurrentChar] = -4;
            MovementReadCompulsory(3, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
            //AnimationName[CurrentChar] = "CROU_PRE";
            WhichAnimationFrame[CurrentChar] = 1;
            AnimationTicks[CurrentChar] = 1;
            }
            DirectionalInputAllowed[CurrentChar] = 0;
            CrouchPosition[CurrentChar] = 1;
			}


    else if (CrouchPosition[CurrentChar] == 1 && AnimationTicks[CurrentChar] >= AnimationSpeed[CurrentChar] && WhichAnimationFrame[CurrentChar] >= FrameAmount[CurrentChar]) {

            if(AnimationType[CurrentChar] == 1){
            AnimationID[CurrentChar] = -5;
            MovementReadCompulsory(4, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
            //AnimationName[CurrentChar] = "CROU_DUR";
            WhichAnimationFrame[CurrentChar] = 1;
            AnimationTicks[CurrentChar] = 1;


            CrouchPosition[CurrentChar] = 2;
            }

            }

    


    if(DirectionalComboChecker[CurrentChar] == 0 && !(st->buttons & CONT_DPAD_RIGHT)  && (st->joyx < 64) && !(st->buttons & CONT_DPAD_LEFT)  && (st->joyx > -64)) DirectionalComboChecker[CurrentChar] += 1;
    else if(DirectionalComboChecker[CurrentChar] == 1 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && CharIsLeft[CurrentChar] == 1) DirectionalComboChecker[CurrentChar]+= 1;
    else if(DirectionalComboChecker[CurrentChar] == 1 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && CharIsLeft[CurrentChar] == 0) DirectionalComboChecker[CurrentChar]+= 1;
    else if(DirectionalComboChecker[CurrentChar] == 1 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && CharIsLeft[CurrentChar] == 0) DirectionalComboChecker[CurrentChar]+= 3;
    else if(DirectionalComboChecker[CurrentChar] == 1 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && CharIsLeft[CurrentChar] == 1) DirectionalComboChecker[CurrentChar]+= 3;
    else if(DirectionalComboChecker[CurrentChar] == 1 && !(st->buttons & CONT_DPAD_RIGHT)  && (st->joyx < 64) && !(st->buttons & CONT_DPAD_LEFT)  && (st->joyx > -64)){ }
    else if(DirectionalComboChecker[CurrentChar] == 2 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && CharIsLeft[CurrentChar] == 1){ }  
    else if(DirectionalComboChecker[CurrentChar] == 2 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && CharIsLeft[CurrentChar] == 0){ }  
    else if(DirectionalComboChecker[CurrentChar] == 4 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && CharIsLeft[CurrentChar] == 0){ }  
    else if(DirectionalComboChecker[CurrentChar] == 4 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && CharIsLeft[CurrentChar] == 1){ }  
    else if(DirectionalComboChecker[CurrentChar] == 7 && !(st->buttons & CONT_DPAD_LEFT & CONT_DPAD_RIGHT)  && (st->joyx < 64 && st->joyx > -64)) DirectionalComboChecker[CurrentChar]++;  
    else if(DirectionalComboChecker[CurrentChar] == 8 && !(st->buttons & CONT_DPAD_LEFT & CONT_DPAD_RIGHT)  && (st->joyx < 64 && st->joyx > -64)) {}
    else if(DirectionalComboChecker[CurrentChar] == 8 && CharIsLeft[CurrentChar] == 1 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64))) DirectionalComboChecker[CurrentChar] += 1;                        
    else if(DirectionalComboChecker[CurrentChar] == 9 && CharIsLeft[CurrentChar] == 1 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64))) {} 
    else if(DirectionalComboChecker[CurrentChar] == 8 && CharIsLeft[CurrentChar] == 0 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64))) DirectionalComboChecker[CurrentChar] += 1;                        
    else if(DirectionalComboChecker[CurrentChar] == 9 && CharIsLeft[CurrentChar] == 0 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64))) {}   
    else DirectionalComboChecker[CurrentChar] = 0;


}

    if (!(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64) && AnimationType[CurrentChar] == 1 && CharHitStatus[CurrentChar] == 0) {

            if(CrouchPosition[CurrentChar] == 1 && AnimationTicks[CurrentChar] >= AnimationSpeed[CurrentChar] && WhichAnimationFrame[CurrentChar] >= FrameAmount[CurrentChar]){
            AnimationID[CurrentChar] = -1;
            MovementReadCompulsory(0, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
            //AnimationName[CurrentChar] = "STANDING";
            WhichAnimationFrame[CurrentChar] = 1;
            AnimationTicks[CurrentChar] = 1;

            CrouchPosition[CurrentChar] = 0;
            DirectionalInputAllowed[CurrentChar] = 1;

            }

            if(CrouchPosition[CurrentChar] == 2){
          
            AnimationID[CurrentChar] = -4;
            MovementReadCompulsory(3, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
            //AnimationName[CurrentChar] = "CROU_PRE";
            WhichAnimationFrame[CurrentChar] = 1;
            AnimationTicks[CurrentChar] = 1;

            CrouchPosition[CurrentChar] = 1;

                }
			}

    if ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) {

            if(BackBlocking[CurrentChar] == 1 && DirectionalInputAllowed[CurrentChar] == 1 && CrouchPosition[CurrentChar] != 0 && CharHitStatus[CurrentChar] == 0 && AnimationType[CurrentChar] == 1 && (AnimationType[OtherChar] == 3 || AnimationType[OtherChar] == 6) && CharIsLeft[CurrentChar] == 0){
            if(AnimationID[CurrentChar] != -11){
            MovementReadCompulsory(10, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
            //AnimationName[CurrentChar] = "CROUBLOC";
            WhichAnimationFrame[CurrentChar] = 1; 

            CrouchPosition[CurrentChar] = 2;

            AnimationTicks[CurrentChar] = 1;
            AnimationID[CurrentChar] = -11;
            }
            }
            else if(DirectionalInputAllowed[CurrentChar] == 1 && GroundLevel[CurrentChar] == 1 && CharHitStatus[CurrentChar] == 0){
            if(BackBlocking[CurrentChar] && AnimationType[CurrentChar] == 1 && (AnimationType[OtherChar] == 3 || AnimationType[OtherChar] == 6) && CharIsLeft[CurrentChar] == 0){
            if(AnimationID[CurrentChar] != -10){
            MovementReadCompulsory(9, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
            //AnimationName[CurrentChar] = "BLOCKING";
            WhichAnimationFrame[CurrentChar] = 1; 
            AnimationTicks[CurrentChar] = 1;
            AnimationID[CurrentChar] = -10;
            }            
            }
            else{
            if(CharIsLeft[CurrentChar] == 1){
            if(AnimationID[CurrentChar] != -2){
            MovementReadCompulsory(1, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
            //AnimationName[CurrentChar] = "WALKINGF";
            WhichAnimationFrame[CurrentChar] = 1; 
            AnimationTicks[CurrentChar] = 1;
            AnimationID[CurrentChar] = -2;
            }
            }
            else{
            if(AnimationID[CurrentChar] != -3){
            MovementReadCompulsory(2, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
            //AnimationName[CurrentChar] = "WALKINGB";
            WhichAnimationFrame[CurrentChar] = 1; 
            AnimationTicks[CurrentChar] = 1;
            AnimationID[CurrentChar] = -3;
            }
            }
            if(DrawCharX[CurrentChar]+CharOffset[CurrentChar]+CharWidth[CurrentChar] >= DrawCharX[OtherChar]+CharacterTextureSizeDrawn-CharOffset[OtherChar]-(CharWidth[OtherChar]/2) && CharIsLeft[CurrentChar] == 1 && GroundLevel[OtherChar] == 1){
            PosCharX[CurrentChar] = PosCharX[CurrentChar]+(CharSpeed[CurrentChar]/2);
            PosCharX[OtherChar] = PosCharX[OtherChar]+(CharSpeed[CurrentChar]/2);
            }
            else{
            PosCharX[CurrentChar] = PosCharX[CurrentChar]+CharSpeed[CurrentChar];
            }
	    }
            }

            if(DirectionalComboChecker[CurrentChar] == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft[CurrentChar] == 1) DirectionalComboChecker[CurrentChar]+= 1;       
            else if(DirectionalComboChecker[CurrentChar] == 2 && CharIsLeft[CurrentChar] == 1 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)) DirectionalComboChecker[CurrentChar]+= 1;
            else if(DirectionalComboChecker[CurrentChar] == 2 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft[CurrentChar] == 1) { } 
            else if(DirectionalComboChecker[CurrentChar] == 3 && CharIsLeft[CurrentChar] == 1 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)){ } //D,DF,F
            else if(DirectionalComboChecker[CurrentChar] == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft[CurrentChar] == 0) DirectionalComboChecker[CurrentChar]+= 3;       
            else if(DirectionalComboChecker[CurrentChar] == 4 && CharIsLeft[CurrentChar] == 0 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)) DirectionalComboChecker[CurrentChar]+= 1;
            else if(DirectionalComboChecker[CurrentChar] == 4 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft[CurrentChar] == 0) { } 
            else if(DirectionalComboChecker[CurrentChar] == 5 && CharIsLeft[CurrentChar] == 0 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)){ }// D,DB, B
            else if(DirectionalComboChecker[CurrentChar] == 0 && CharIsLeft[CurrentChar] == 1 && !(st->buttons & CONT_DPAD_DOWN)  && !(st->buttons & CONT_DPAD_UP) && (st->joyy < 64) && (st->joyy > -64)) DirectionalComboChecker[CurrentChar] = 7;                        
            else if(DirectionalComboChecker[CurrentChar] == 7 && CharIsLeft[CurrentChar] == 1 && !(st->buttons & CONT_DPAD_DOWN)  && !(st->buttons & CONT_DPAD_UP) && (st->joyy < 64) && (st->joyy > -64)) {}
            else if(DirectionalComboChecker[CurrentChar] == 8 && CharIsLeft[CurrentChar] == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64))) DirectionalComboChecker[CurrentChar] += 1;                        
            else if(DirectionalComboChecker[CurrentChar] == 9 && CharIsLeft[CurrentChar] == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64))) {}  
            else DirectionalComboChecker[CurrentChar] = 0;

                        }

    if ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) {

            if(BackBlocking[CurrentChar] == 1 && DirectionalInputAllowed[CurrentChar] == 1 && CrouchPosition[CurrentChar] != 0 && CharHitStatus[CurrentChar] == 0 && AnimationType[CurrentChar] == 1 && (AnimationType[OtherChar] == 3 || AnimationType[OtherChar] == 6) && CharIsLeft[CurrentChar] == 1){
            if(AnimationID[CurrentChar] != -11){
            MovementReadCompulsory(10, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
            //AnimationName[CurrentChar] = "CROUBLOC";
            WhichAnimationFrame[CurrentChar] = 1; 

            CrouchPosition[CurrentChar] = 2;

            AnimationTicks[CurrentChar] = 1;
            AnimationID[CurrentChar] = -11;
            }
            }
            else if(DirectionalInputAllowed[CurrentChar] == 1 && GroundLevel[CurrentChar] == 1 && CharHitStatus[CurrentChar] == 0){
            if(BackBlocking[CurrentChar] && AnimationType[CurrentChar] == 1 && (AnimationType[OtherChar] == 3 || AnimationType[OtherChar] == 6) && CharIsLeft[CurrentChar] == 1){
            if(AnimationID[CurrentChar] != -10){
            MovementReadCompulsory(9, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
            //AnimationName[CurrentChar] = "BLOCKING";
            WhichAnimationFrame[CurrentChar] = 1; 
            AnimationTicks[CurrentChar] = 1;
            AnimationID[CurrentChar] = -10;
            }            
            }
            else{
            if(CharIsLeft[CurrentChar] == 0){
            if(AnimationID[CurrentChar] != -2){
            MovementReadCompulsory(1, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
            //AnimationName[CurrentChar] = "WALKINGF";
            WhichAnimationFrame[CurrentChar] = 1; 
            AnimationTicks[CurrentChar] = 1;
            AnimationID[CurrentChar] = -2;
            }
            }
            else{
            if(AnimationID[CurrentChar] != -3){
            MovementReadCompulsory(2, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
            //AnimationName[CurrentChar] = "WALKINGB";
            WhichAnimationFrame[CurrentChar] = 1; 
            AnimationTicks[CurrentChar] = 1;
            AnimationID[CurrentChar] = -3;
            }
            }
            if(DrawCharX[OtherChar]+CharOffset[OtherChar]+(CharWidth[OtherChar]/2) >= DrawCharX[CurrentChar]+CharacterTextureSizeDrawn-CharOffset[CurrentChar]-CharWidth[CurrentChar] && CharIsLeft[CurrentChar] == 0 && GroundLevel[OtherChar] == 1){
            PosCharX[CurrentChar] = PosCharX[CurrentChar]-(CharSpeed[CurrentChar]/2);
            PosCharX[OtherChar] = PosCharX[OtherChar]-(CharSpeed[CurrentChar]/2);
            }
            else{
            PosCharX[CurrentChar] = PosCharX[CurrentChar]-CharSpeed[CurrentChar];
            }
            }
            }


            if(DirectionalComboChecker[CurrentChar] == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft[CurrentChar] == 0) DirectionalComboChecker[CurrentChar]+= 1;       
            else if(DirectionalComboChecker[CurrentChar] == 2 && CharIsLeft[CurrentChar] == 0 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)) DirectionalComboChecker[CurrentChar]+= 1;
            else if(DirectionalComboChecker[CurrentChar] == 2 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft[CurrentChar] == 0) { } 
            else if(DirectionalComboChecker[CurrentChar] == 3 && CharIsLeft[CurrentChar] == 0 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)){ }// D,DF,F
            else if(DirectionalComboChecker[CurrentChar] == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft[CurrentChar] == 1) DirectionalComboChecker[CurrentChar]+= 3;       
            else if(DirectionalComboChecker[CurrentChar] == 4 && CharIsLeft[CurrentChar] == 1 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)) DirectionalComboChecker[CurrentChar]+= 1;   
            else if(DirectionalComboChecker[CurrentChar] == 4 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft[CurrentChar] == 1) { } 
            else if(DirectionalComboChecker[CurrentChar] == 5 && CharIsLeft[CurrentChar] == 1 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)){ }// D,DB,B
            else if(DirectionalComboChecker[CurrentChar] == 0 && CharIsLeft[CurrentChar] == 0 && !(st->buttons & CONT_DPAD_DOWN & CONT_DPAD_UP)  && (st->joyy < 64 && st->joyy > -64)) DirectionalComboChecker[CurrentChar] = 7;                        
            else if(DirectionalComboChecker[CurrentChar] == 7 && CharIsLeft[CurrentChar] == 0 && !(st->buttons & CONT_DPAD_DOWN & CONT_DPAD_UP)  && (st->joyy < 64 && st->joyy > -64)) {}  
            else if(DirectionalComboChecker[CurrentChar] == 8 && CharIsLeft[CurrentChar] == 0 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64))) DirectionalComboChecker[CurrentChar] += 1;                        
            else if(DirectionalComboChecker[CurrentChar] == 9 && CharIsLeft[CurrentChar] == 0 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64))) {}  
            else DirectionalComboChecker[CurrentChar] = 0;

			}
 //   if (!(st->buttons & CONT_START) && !(st->buttons & CONT_A) && !(st->buttons & CONT_B) && !(st->buttons & CONT_X) && !(st->buttons & CONT_Y) && !(st->buttons & CONT_DPAD_RIGHT) && !(st->buttons & CONT_DPAD_UP) && !(st->buttons & CONT_DPAD_DOWN) && !(st->buttons & CONT_DPAD_LEFT) && InputAllowed[CurrentChar] == 1) {
    if (  !(st->buttons & CONT_DPAD_RIGHT)  && (st->joyx < 64) && !(st->buttons & CONT_DPAD_UP)  && (st->joyy > -64) && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64) && !(st->buttons & CONT_DPAD_LEFT)  && (st->joyx > -64) && DirectionalInputAllowed[CurrentChar] == 1 && GroundLevel[CurrentChar] == 1 && CrouchPosition[CurrentChar] == 0) {

            
            //printf("AnimationName: %s\n", AnimationName[CurrentChar]);
            //printf("Frame Amount: %d\n", FrameAmount[CurrentChar]);
            //printf("Loop: %d\n", AnimationLoop[CurrentChar]);
            //printf("Animation Type: %d\n", AnimationType[CurrentChar]);
            //printf("Animation Speed: %d\n", AnimationSpeed[CurrentChar]);          
            if(AnimationID[CurrentChar] != -1){
            AnimationID[CurrentChar] = -1;
            MovementReadCompulsory(0, CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationType[CurrentChar]);
            //AnimationName[CurrentChar] = "STANDING";
            WhichAnimationFrame[CurrentChar] = 1;
            AnimationTicks[CurrentChar] = 1;
             
            DirectionalInputAllowed[CurrentChar] = 1;
            ResetToStance[CurrentChar] = 0;
            }

			}

    if (st->buttons & CONT_X) {


            
            if(ButtonInputAllowed[CurrentChar] == 1){

            if(AnimationType[CurrentChar] == 1 && CharHitStatus[CurrentChar] == 0){
            TemporaryAnimationID[CurrentChar] = 21;
            if(DirectionalComboChecker[CurrentChar] == 3) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetDownDownForwardForward;
            else if(DirectionalComboChecker[CurrentChar] == 5) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetDownDownBackBack;
            else if(DirectionalComboChecker[CurrentChar] == 9) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetForwardDownDownForward;
            else if(st->buttons & CONT_A) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetSameStrengthButtons;

            else if(st->buttons & CONT_DPAD_LEFT){
            if(CharIsLeft[CurrentChar] == 1) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingBack;
            else TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingForward;
            }  
            else if(st->buttons & CONT_DPAD_RIGHT){
            if(CharIsLeft[CurrentChar] == 1) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingForward;
            else TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingBack;
            }              

            AnimationValidityCheck[CurrentChar] = MovementReadHuman(TemporaryAnimationID[CurrentChar], GroundLevel[CurrentChar], CrouchPosition[CurrentChar], CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationEnemyAccelerationX[CurrentChar], &AnimationEnemyAccelerationY[CurrentChar], &AnimationType[CurrentChar], &AnimationStrength[CurrentChar], &WhichSpecial[CurrentChar], &WhichMissSoundEffect[CurrentChar], &WhichSoundEffectFrame[CurrentChar] ,&WhichHitSoundEffect[CurrentChar], &AnimationAddOn[CurrentChar], &SpecialLeft[CurrentChar]);
            if(AnimationValidityCheck[CurrentChar] == 1 && AnimationID[CurrentChar] != TemporaryAnimationID[CurrentChar]){
            WhichAnimationFrame[CurrentChar] = 1;
            DirectionalInputAllowed[CurrentChar] = 0;
            AnimationID[CurrentChar] = TemporaryAnimationID[CurrentChar];
            AnimationTicks[CurrentChar] = 1;
            SpecialAnimationFrame[CurrentChar] = 0;
            //AnimationName[CurrentChar] = AnimationBuffer[CurrentChar];
            if(AnimationLoop[CurrentChar] == 1){ ResetToStance[CurrentChar] = 1; }
            ButtonInputAllowed[CurrentChar] = 0; 
            }
            }

            if(ComboID[CurrentChar] == 3 && ComboChecker[CurrentChar] == 0){
            ComboChecker[CurrentChar] = 1;
            ButtonInputAllowed[CurrentChar] = 0;
            }
            }

            DirectionalComboChecker[CurrentChar] = 0;

			}




if (st->buttons & CONT_B) {

            if(ButtonInputAllowed[CurrentChar] == 1){
            if(AnimationType[CurrentChar] == 1 && CharHitStatus[CurrentChar] == 0){
            TemporaryAnimationID[CurrentChar] = 11;
            if(DirectionalComboChecker[CurrentChar] == 3) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetDownDownForwardForward;
            else if(DirectionalComboChecker[CurrentChar] == 5) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetDownDownBackBack;
            else if(DirectionalComboChecker[CurrentChar] == 9) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetForwardDownDownForward;
            else if(st->buttons & CONT_Y) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetSameStrengthButtons;

            else if(st->buttons & CONT_DPAD_LEFT){
            if(CharIsLeft[CurrentChar] == 1) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingBack;
            else TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingForward;
            }  
            else if(st->buttons & CONT_DPAD_RIGHT){
            if(CharIsLeft[CurrentChar] == 1) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingForward;
            else TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingBack;
            }              

            AnimationValidityCheck[CurrentChar] = MovementReadHuman(TemporaryAnimationID[CurrentChar], GroundLevel[CurrentChar], CrouchPosition[CurrentChar], CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationEnemyAccelerationX[CurrentChar], &AnimationEnemyAccelerationY[CurrentChar], &AnimationType[CurrentChar], &AnimationStrength[CurrentChar], &WhichSpecial[CurrentChar], &WhichMissSoundEffect[CurrentChar], &WhichSoundEffectFrame[CurrentChar] ,&WhichHitSoundEffect[CurrentChar], &AnimationAddOn[CurrentChar], &SpecialLeft[CurrentChar]);
            if(AnimationValidityCheck[CurrentChar] == 1 && AnimationID[CurrentChar] != TemporaryAnimationID[CurrentChar]){
            WhichAnimationFrame[CurrentChar] = 1;

            DirectionalInputAllowed[CurrentChar] = 0;
            SpecialAnimationFrame[CurrentChar] = 0;
            AnimationID[CurrentChar] = TemporaryAnimationID[CurrentChar];
            AnimationTicks[CurrentChar] = 1;
            //AnimationName[CurrentChar] = AnimationBuffer[CurrentChar];
            if(AnimationLoop[CurrentChar] == 1){ ResetToStance[CurrentChar] = 1; }
            ButtonInputAllowed[CurrentChar] = 0; 
            }
            }

            if(ComboID[CurrentChar] == 2 && ComboChecker[CurrentChar] == 0){
            ComboChecker[CurrentChar] = 1;
            ButtonInputAllowed[CurrentChar] = 0;
            }
            }

            DirectionalComboChecker[CurrentChar] = 0;
			}


if (st->buttons & CONT_A) {


            if(ButtonInputAllowed[CurrentChar] == 1){
            if(AnimationType[CurrentChar] == 1 && CharHitStatus[CurrentChar] == 0){  
            TemporaryAnimationID[CurrentChar] = 1;
            if(DirectionalComboChecker[CurrentChar] == 3) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetDownDownForwardForward;
            else if(DirectionalComboChecker[CurrentChar] == 5) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetDownDownBackBack;
            else if(DirectionalComboChecker[CurrentChar] == 9) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetForwardDownDownForward;
            else if(st->buttons & CONT_X) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetSameStrengthButtons;   

            else if(st->buttons & CONT_DPAD_LEFT){
            if(CharIsLeft[CurrentChar] == 1) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingBack;
            else TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingForward;
            }  
            else if(st->buttons & CONT_DPAD_RIGHT){
            if(CharIsLeft[CurrentChar] == 1) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingForward;
            else TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingBack;
            }              

            AnimationValidityCheck[CurrentChar] = MovementReadHuman(TemporaryAnimationID[CurrentChar], GroundLevel[CurrentChar], CrouchPosition[CurrentChar], CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationEnemyAccelerationX[CurrentChar], &AnimationEnemyAccelerationY[CurrentChar], &AnimationType[CurrentChar], &AnimationStrength[CurrentChar], &WhichSpecial[CurrentChar], &WhichMissSoundEffect[CurrentChar], &WhichSoundEffectFrame[CurrentChar] ,&WhichHitSoundEffect[CurrentChar], &AnimationAddOn[CurrentChar], &SpecialLeft[CurrentChar]);
            if(AnimationValidityCheck[CurrentChar] == 1 && AnimationID[CurrentChar] != TemporaryAnimationID[CurrentChar]){
            WhichAnimationFrame[CurrentChar] = 1;

            DirectionalInputAllowed[CurrentChar] = 0;
            //ButtonInputAllowed[CurrentChar] = 0;
            AnimationID[CurrentChar] = TemporaryAnimationID[CurrentChar];
            AnimationTicks[CurrentChar] = 1;
            SpecialAnimationFrame[CurrentChar] = 0;
            //AnimationName[CurrentChar] = AnimationBuffer[CurrentChar];
            if(AnimationLoop[CurrentChar] == 1){ ResetToStance[CurrentChar] = 1; }
            ButtonInputAllowed[CurrentChar] = 0; 
            }
            }

            if(ComboID[CurrentChar] == 1 && ComboChecker[CurrentChar] == 0){
            ComboChecker[CurrentChar] = 1;
            ButtonInputAllowed[CurrentChar] = 0;
            }
            }

            DirectionalComboChecker[CurrentChar] = 0;

			}

if (st->buttons & CONT_Y) {

            if(ButtonInputAllowed[CurrentChar] == 1){
            if(AnimationType[CurrentChar] == 1 && CharHitStatus[CurrentChar] == 0){
            TemporaryAnimationID[CurrentChar] = 31;
            if(DirectionalComboChecker[CurrentChar] == 3) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetDownDownForwardForward;
            else if(DirectionalComboChecker[CurrentChar] == 5) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetDownDownBackBack;
            else if(DirectionalComboChecker[CurrentChar] == 9) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetForwardDownDownForward;
            else if(st->buttons & CONT_B) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetSameStrengthButtons;

            else if(st->buttons & CONT_DPAD_LEFT){
            if(CharIsLeft[CurrentChar] == 1) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingBack;
            else TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingForward;
            }  
            else if(st->buttons & CONT_DPAD_RIGHT){
            if(CharIsLeft[CurrentChar] == 1) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingForward;
            else TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingBack;
            }              

            AnimationValidityCheck[CurrentChar] = MovementReadHuman(TemporaryAnimationID[CurrentChar], GroundLevel[CurrentChar], CrouchPosition[CurrentChar], CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationEnemyAccelerationX[CurrentChar], &AnimationEnemyAccelerationY[CurrentChar], &AnimationType[CurrentChar], &AnimationStrength[CurrentChar], &WhichSpecial[CurrentChar], &WhichMissSoundEffect[CurrentChar], &WhichSoundEffectFrame[CurrentChar] ,&WhichHitSoundEffect[CurrentChar], &AnimationAddOn[CurrentChar], &SpecialLeft[CurrentChar]);
            if(AnimationValidityCheck[CurrentChar] == 1 && AnimationID[CurrentChar] != TemporaryAnimationID[CurrentChar]){
            WhichAnimationFrame[CurrentChar] = 1;

            DirectionalInputAllowed[CurrentChar] = 0;
            SpecialAnimationFrame[CurrentChar] = 0;
            AnimationID[CurrentChar] = TemporaryAnimationID[CurrentChar];
            AnimationTicks[CurrentChar] = 1;
            //AnimationName[CurrentChar] = AnimationBuffer[CurrentChar];
            if(AnimationLoop[CurrentChar] == 1){ ResetToStance[CurrentChar] = 1; }
            ButtonInputAllowed[CurrentChar] = 0; 
            }
            }

            if(ComboID[CurrentChar] == 4 && ComboChecker[CurrentChar] == 0){
            ButtonInputAllowed[CurrentChar] = 0;
            ComboChecker[CurrentChar] = 1;
            }
            }

            DirectionalComboChecker[CurrentChar] = 0;

			}

    if ((st->ltrig) > 0) {


            
            if(ButtonInputAllowed[CurrentChar] == 1){

            if(AnimationType[CurrentChar] == 1 && CharHitStatus[CurrentChar] == 0){
            TemporaryAnimationID[CurrentChar] = 41;
            if(DirectionalComboChecker[CurrentChar] == 3) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetDownDownForwardForward;
            else if(DirectionalComboChecker[CurrentChar] == 5) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetDownDownBackBack;
            else if(DirectionalComboChecker[CurrentChar] == 9) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetForwardDownDownForward;
            else if((st->rtrig) > 0) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetSameStrengthButtons;

            else if(st->buttons & CONT_DPAD_LEFT){
            if(CharIsLeft[CurrentChar] == 1) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingBack;
            else TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingForward;
            }  
            else if(st->buttons & CONT_DPAD_RIGHT){
            if(CharIsLeft[CurrentChar] == 1) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingForward;
            else TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingBack;
            }              

            AnimationValidityCheck[CurrentChar] = MovementReadHuman(TemporaryAnimationID[CurrentChar], GroundLevel[CurrentChar], CrouchPosition[CurrentChar], CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationEnemyAccelerationX[CurrentChar], &AnimationEnemyAccelerationY[CurrentChar], &AnimationType[CurrentChar], &AnimationStrength[CurrentChar], &WhichSpecial[CurrentChar], &WhichMissSoundEffect[CurrentChar], &WhichSoundEffectFrame[CurrentChar] ,&WhichHitSoundEffect[CurrentChar], &AnimationAddOn[CurrentChar], &SpecialLeft[CurrentChar]);
            if(AnimationValidityCheck[CurrentChar] == 1 && AnimationID[CurrentChar] != TemporaryAnimationID[CurrentChar]){
            WhichAnimationFrame[CurrentChar] = 1;
            DirectionalInputAllowed[CurrentChar] = 0;
            AnimationID[CurrentChar] = TemporaryAnimationID[CurrentChar];
            AnimationTicks[CurrentChar] = 1;
            SpecialAnimationFrame[CurrentChar] = 0;
            //AnimationName[CurrentChar] = AnimationBuffer[CurrentChar];
            if(AnimationLoop[CurrentChar] == 1){ ResetToStance[CurrentChar] = 1; }
            ButtonInputAllowed[CurrentChar] = 0; 
            }
            }

            if(ComboID[CurrentChar] == 5 && ComboChecker[CurrentChar] == 0){
            ButtonInputAllowed[CurrentChar] = 0;
            ComboChecker[CurrentChar] = 1;
            }   
            }

            DirectionalComboChecker[CurrentChar] = 0;

			}

    if ((st->rtrig) > 0) {


            
            if(ButtonInputAllowed[CurrentChar] == 1){

            if(AnimationType[CurrentChar] == 1 && CharHitStatus[CurrentChar] == 0){
            TemporaryAnimationID[CurrentChar] = 51;
            if(DirectionalComboChecker[CurrentChar] == 3) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetDownDownForwardForward;
            else if(DirectionalComboChecker[CurrentChar] == 5) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetDownDownBackBack;
            else if(DirectionalComboChecker[CurrentChar] == 9) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetForwardDownDownForward;
            else if((st->ltrig) > 0) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetSameStrengthButtons;

            else if(st->buttons & CONT_DPAD_LEFT){
            if(CharIsLeft[CurrentChar] == 1) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingBack;
            else TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingForward;
            }  
            else if(st->buttons & CONT_DPAD_RIGHT){
            if(CharIsLeft[CurrentChar] == 1) TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingForward;
            else TemporaryAnimationID[CurrentChar]+=AnimationIDOffsetHoldingBack;
            }              

            AnimationValidityCheck[CurrentChar] = MovementReadHuman(TemporaryAnimationID[CurrentChar], GroundLevel[CurrentChar], CrouchPosition[CurrentChar], CharacterName[CurrentChar], AnimationBuffer[CurrentChar], &AnimationSpeed[CurrentChar], &FrameAmount[CurrentChar], &AnimationLoop[CurrentChar], &AnimationEnemyAccelerationX[CurrentChar], &AnimationEnemyAccelerationY[CurrentChar], &AnimationType[CurrentChar], &AnimationStrength[CurrentChar], &WhichSpecial[CurrentChar], &WhichMissSoundEffect[CurrentChar], &WhichSoundEffectFrame[CurrentChar] ,&WhichHitSoundEffect[CurrentChar], &AnimationAddOn[CurrentChar], &SpecialLeft[CurrentChar]);
            if(AnimationValidityCheck[CurrentChar] == 1 && AnimationID[CurrentChar] != TemporaryAnimationID[CurrentChar]){
            WhichAnimationFrame[CurrentChar] = 1;
            DirectionalInputAllowed[CurrentChar] = 0;
            AnimationID[CurrentChar] = TemporaryAnimationID[CurrentChar];
            AnimationTicks[CurrentChar] = 1;
            SpecialAnimationFrame[CurrentChar] = 0;
            //AnimationName[CurrentChar] = AnimationBuffer[CurrentChar];
            if(AnimationLoop[CurrentChar] == 1){ ResetToStance[CurrentChar] = 1; }
            ButtonInputAllowed[CurrentChar] = 0; 
            }
            }

            if(ComboID[CurrentChar] == 6 && ComboChecker[CurrentChar] == 0){
            ComboChecker[CurrentChar] = 1;
            ButtonInputAllowed[CurrentChar] = 0;
            }
            }

            DirectionalComboChecker[CurrentChar] = 0;

			}


    if ( !(st->buttons & CONT_X) && !(st->buttons & CONT_B) && !(st->buttons & CONT_A) && !(st->buttons & CONT_Y) && !(st->buttons & CONT_START) && (st->rtrig) == 0 && (st->ltrig) == 0 && AnimationID[CurrentChar] != -10 && ButtonInputAllowed[CurrentChar] == 0) {
            ButtonInputAllowed[CurrentChar] = 1;
            if(ResetToStance[CurrentChar] == 1) {AnimationLoop[CurrentChar] = 0; ResetToStance[CurrentChar] = 0;}
            //printf("INPUT ALLOWED AGAIN!\n");
            //printf("STATUS: %d!\n", ButtonInputAllowed[CurrentChar]);
			}

    if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
            Winner = StairWayToHeavenIdentifier;
            FightStage = FightShutDown;
			}

    //MAPLE_FOREACH_END()
 }


