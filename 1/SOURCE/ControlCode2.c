    if((cont = maple_enum_dev(1, 0)) != NULL) {

    st = (cont_state_t *)maple_dev_status(cont);


    if ((st->buttons & CONT_START) && ButtonInputAllowed2 == 1) {
            FightStage+=1;
			}

    if (((st->buttons & CONT_DPAD_UP)  || (st->joyy <= -64)) && DirectionalInputAllowed2 == 1 && GroundLevel2 == 1 && JumpVelocity2 == -480 && JumpBlock2 == 0) {


      
            //AnimationName2 = "JUMPING1";
            WhichAnimationFrame2 = 1;
            //AnimationSpeed2 = 4;
            //FrameAmount2 = 1;
            //AnimationLoop2 =1;
            AnimationTicks2 = 1;

            if (((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64))){
             if(CharIsLeft2 == 1){
              JumpAnimationFlags2 = JumpForwardFlags2;
              JumpType2 = 1;
              }
             else{
             JumpAnimationFlags2 = JumpBackFlags2;
             JumpType2 = 2;
              }
             JumpDirection2 = CharSpeed2;
             }
            else if (((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64))){
             if(CharIsLeft2 == 0){
              JumpAnimationFlags2 = JumpForwardFlags2;
              JumpType2 = 1;
              }
             else{
             JumpAnimationFlags2 = JumpBackFlags2;
             JumpType2 = 2;
              }
             JumpDirection2 = -CharSpeed2;
             }
            else{
             JumpAnimationFlags2 = JumpIdleUpFlags2;
             JumpType2 = 0;
             }

            DirectionalInputAllowed2 = 0;
            ButtonInputAllowed2 = 0;

            GroundLevel2 = 0;
            JumpBlock2 = 1;

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
	}

   if (!(st->buttons & CONT_DPAD_UP)  && (st->joyy > -64) && GroundLevel2 == 1 && JumpBlock2 == 1) {

    JumpBlock2 = 0;
   }

if((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)){


            if(CrouchPosition2 != 0 && AnimationType2 == 1 && (AnimationType1 == 3 || AnimationType1 == 6) && ((CharIsLeft2 == 0 && (st->buttons & CONT_DPAD_RIGHT)) || (CharIsLeft2 == 1 && (st->buttons & CONT_DPAD_LEFT)))){
            if(AnimationID2 != -11){
            MovementReadCompulsory(10, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
            //AnimationName2 = "CROUBLOC";
            WhichAnimationFrame2 = 1; 
            AnimationTicks2 = 1;
            AnimationID2 = -11;

            CrouchPosition2 = 2;
           
            }
            }

   else if (AnimationType2 == 1 && DirectionalInputAllowed2 == 1 && GroundLevel2 == 1 && JumpVelocity2 == -480 && CrouchPosition2 != 2) {


            if(AnimationID2 != -4){
            AnimationID2 = -4;
            MovementReadCompulsory(3, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
            //AnimationName2 = "CROU_PRE";
            WhichAnimationFrame2 = 1;
            AnimationTicks2 = 1;
            }
            DirectionalInputAllowed2 = 0;
            CrouchPosition2 = 1;
			}


    else if (CrouchPosition2 == 1 && AnimationTicks2 >= AnimationSpeed2 && WhichAnimationFrame2 >= FrameAmount2) {

            if(AnimationType2 == 1){
            AnimationID2 = -5;
            MovementReadCompulsory(4, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
            //AnimationName2 = "CROU_DUR";
            WhichAnimationFrame2 = 1;
            AnimationTicks2 = 1;


            CrouchPosition2 = 2;
            }

            }

    


    if(DirectionalComboChecker2 == 0 && !(st->buttons & CONT_DPAD_RIGHT)  && (st->joyx < 64) && !(st->buttons & CONT_DPAD_LEFT)  && (st->joyx > -64)) DirectionalComboChecker2 += 1;
    else if(DirectionalComboChecker2 == 1 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && CharIsLeft2 == 1) DirectionalComboChecker2+= 1;
    else if(DirectionalComboChecker2 == 1 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && CharIsLeft2 == 0) DirectionalComboChecker2+= 1;
    else if(DirectionalComboChecker2 == 1 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && CharIsLeft2 == 0) DirectionalComboChecker2+= 3;
    else if(DirectionalComboChecker2 == 1 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && CharIsLeft2 == 1) DirectionalComboChecker2+= 3;
    else if(DirectionalComboChecker2 == 1 && !(st->buttons & CONT_DPAD_RIGHT)  && (st->joyx < 64) && !(st->buttons & CONT_DPAD_LEFT)  && (st->joyx > -64)){ }
    else if(DirectionalComboChecker2 == 2 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && CharIsLeft2 == 1){ }  
    else if(DirectionalComboChecker2 == 2 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && CharIsLeft2 == 0){ }  
    else if(DirectionalComboChecker2 == 4 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && CharIsLeft2 == 0){ }  
    else if(DirectionalComboChecker2 == 4 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && CharIsLeft2 == 1){ }  
    else if(DirectionalComboChecker2 == 7 && !(st->buttons & CONT_DPAD_LEFT & CONT_DPAD_RIGHT)  && (st->joyx < 64 && st->joyx > -64)) DirectionalComboChecker2++;  
    else if(DirectionalComboChecker2 == 8 && !(st->buttons & CONT_DPAD_LEFT & CONT_DPAD_RIGHT)  && (st->joyx < 64 && st->joyx > -64)) {}
    else if(DirectionalComboChecker2 == 8 && CharIsLeft2 == 1 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64))) DirectionalComboChecker2 += 1;                        
    else if(DirectionalComboChecker2 == 9 && CharIsLeft2 == 1 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64))) {} 
    else if(DirectionalComboChecker2 == 8 && CharIsLeft2 == 0 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64))) DirectionalComboChecker2 += 1;                        
    else if(DirectionalComboChecker2 == 9 && CharIsLeft2 == 0 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64))) {}   
    else DirectionalComboChecker2 = 0;


}

    if (!(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64) && AnimationType2 == 1) {

            if(CrouchPosition2 == 1 && AnimationTicks2 >= AnimationSpeed2 && WhichAnimationFrame2 >= FrameAmount2){
            AnimationID2 = -1;
            MovementReadCompulsory(0, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
            //AnimationName2 = "STANDING";
            WhichAnimationFrame2 = 1;
            AnimationTicks2 = 1;

            CrouchPosition2 = 0;
            DirectionalInputAllowed2 = 1;

            }

            if(CrouchPosition2 == 2){
          
            AnimationID2 = -4;
            MovementReadCompulsory(3, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
            //AnimationName2 = "CROU_PRE";
            WhichAnimationFrame2 = 1;
            AnimationTicks2 = 1;

            CrouchPosition2 = 1;

                }
			}

    if ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) {

            if(DirectionalInputAllowed2 == 1 && CrouchPosition2 != 0 && AnimationType2 == 1 && (AnimationType1 == 3 || AnimationType1 == 6) && CharIsLeft2 == 0){
            if(AnimationID2 != -11){
            MovementReadCompulsory(10, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
            //AnimationName2 = "CROUBLOC";
            WhichAnimationFrame2 = 1; 

            CrouchPosition2 = 2;

            AnimationTicks2 = 1;
            AnimationID2 = -11;
            }
            }
            else if(DirectionalInputAllowed2 == 1 && GroundLevel2 == 1){
            if(AnimationType2 == 1 && (AnimationType1 == 3 || AnimationType1 == 6) && CharIsLeft2 == 0){
            if(AnimationID2 != -10){
            MovementReadCompulsory(9, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
            //AnimationName2 = "BLOCKING";
            WhichAnimationFrame2 = 1; 
            AnimationTicks2 = 1;
            AnimationID2 = -10;
            }            
            }
            else{
            if(CharIsLeft2 == 1){
            if(AnimationID2 != -2){
            MovementReadCompulsory(1, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
            //AnimationName2 = "WALKINGF";
            WhichAnimationFrame2 = 1; 
            AnimationTicks2 = 1;
            AnimationID2 = -2;
            }
            }
            else{
            if(AnimationID2 != -3){
            MovementReadCompulsory(2, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
            //AnimationName2 = "WALKINGB";
            WhichAnimationFrame2 = 1; 
            AnimationTicks2 = 1;
            AnimationID2 = -3;
            }
            }
            if(DrawCharX2+CharOffset2+CharWidth2 >= DrawCharX1+256-CharOffset1-(CharWidth1/2) && CharIsLeft2 == 1 && GroundLevel1 == 1){
            PosCharX2 = PosCharX2+(CharSpeed2/2);
            PosCharX1 = PosCharX1+(CharSpeed2/2);
            }
            else{
            PosCharX2 = PosCharX2+CharSpeed2;
            }
	    }
            }

            if(DirectionalComboChecker2 == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft2 == 1) DirectionalComboChecker2+= 1;       
            else if(DirectionalComboChecker2 == 2 && CharIsLeft2 == 1 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)) DirectionalComboChecker2+= 1;
            else if(DirectionalComboChecker2 == 2 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft2 == 1) { } 
            else if(DirectionalComboChecker2 == 3 && CharIsLeft2 == 1 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)){ } //D,DF,F
            else if(DirectionalComboChecker2 == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft2 == 0) DirectionalComboChecker2+= 3;       
            else if(DirectionalComboChecker2 == 4 && CharIsLeft2 == 0 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)) DirectionalComboChecker2+= 1;
            else if(DirectionalComboChecker2 == 4 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft2 == 0) { } 
            else if(DirectionalComboChecker2 == 5 && CharIsLeft2 == 0 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)){ }// D,DB, B
            else if(DirectionalComboChecker2 == 0 && CharIsLeft2 == 1 && !(st->buttons & CONT_DPAD_DOWN)  && !(st->buttons & CONT_DPAD_UP) && (st->joyy < 64) && (st->joyy > -64)) DirectionalComboChecker2 = 7;                        
            else if(DirectionalComboChecker2 == 7 && CharIsLeft2 == 1 && !(st->buttons & CONT_DPAD_DOWN)  && !(st->buttons & CONT_DPAD_UP) && (st->joyy < 64) && (st->joyy > -64)) {}
            else if(DirectionalComboChecker2 == 8 && CharIsLeft2 == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64))) DirectionalComboChecker2 += 1;                        
            else if(DirectionalComboChecker2 == 9 && CharIsLeft2 == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64))) {}  
            else DirectionalComboChecker2 = 0;

                        }

    if ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) {

            if(DirectionalInputAllowed2 == 1 && CrouchPosition2 != 0 && AnimationType2 == 1 && (AnimationType1 == 3 || AnimationType1 == 6) && CharIsLeft2 == 1){
            if(AnimationID2 != -11){
            MovementReadCompulsory(10, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
            //AnimationName2 = "CROUBLOC";
            WhichAnimationFrame2 = 1; 

            CrouchPosition2 = 2;

            AnimationTicks2 = 1;
            AnimationID2 = -11;
            }
            }
            else if(DirectionalInputAllowed2 == 1 && GroundLevel2 == 1){
            if(AnimationType2 == 1 && (AnimationType1 == 3 || AnimationType1 == 6) && CharIsLeft2 == 1){
            if(AnimationID2 != -10){
            MovementReadCompulsory(9, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
            //AnimationName2 = "BLOCKING";
            WhichAnimationFrame2 = 1; 
            AnimationTicks2 = 1;
            AnimationID2 = -10;
            }            
            }
            else{
            if(CharIsLeft2 == 0){
            if(AnimationID2 != -2){
            MovementReadCompulsory(1, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
            //AnimationName2 = "WALKINGF";
            WhichAnimationFrame2 = 1; 
            AnimationTicks2 = 1;
            AnimationID2 = -2;
            }
            }
            else{
            if(AnimationID2 != -3){
            MovementReadCompulsory(2, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
            //AnimationName2 = "WALKINGB";
            WhichAnimationFrame2 = 1; 
            AnimationTicks2 = 1;
            AnimationID2 = -3;
            }
            }
            if(DrawCharX1+CharOffset1+(CharWidth1/2) >= DrawCharX2+256-CharOffset2-CharWidth2 && CharIsLeft2 == 0 && GroundLevel1 == 1){
            PosCharX2 = PosCharX2-(CharSpeed1/2);
            PosCharX1 = PosCharX1-(CharSpeed2/2);
            }
            else{
            PosCharX2 = PosCharX2-CharSpeed2;
            }
            }
            }


            if(DirectionalComboChecker2 == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft1 == 0) DirectionalComboChecker2+= 1;       
            else if(DirectionalComboChecker2 == 2 && CharIsLeft2 == 0 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)) DirectionalComboChecker2+= 1;
            else if(DirectionalComboChecker2 == 2 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft2 == 0) { } 
            else if(DirectionalComboChecker2 == 3 && CharIsLeft2 == 0 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)){ }// D,DF,F
            else if(DirectionalComboChecker2 == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft2 == 1) DirectionalComboChecker2+= 3;       
            else if(DirectionalComboChecker2 == 4 && CharIsLeft2 == 1 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)) DirectionalComboChecker2+= 1;   
            else if(DirectionalComboChecker2 == 4 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft2 == 1) { } 
            else if(DirectionalComboChecker2 == 5 && CharIsLeft2 == 1 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)){ }// D,DB,B
            else if(DirectionalComboChecker2 == 0 && CharIsLeft2 == 0 && !(st->buttons & CONT_DPAD_DOWN & CONT_DPAD_UP)  && (st->joyy < 64 && st->joyy > -64)) DirectionalComboChecker2 = 7;                        
            else if(DirectionalComboChecker2 == 7 && CharIsLeft2 == 0 && !(st->buttons & CONT_DPAD_DOWN & CONT_DPAD_UP)  && (st->joyy < 64 && st->joyy > -64)) {}  
            else if(DirectionalComboChecker2 == 8 && CharIsLeft2 == 0 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64))) DirectionalComboChecker2 += 1;                        
            else if(DirectionalComboChecker2 == 9 && CharIsLeft2 == 0 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64))) {}  
            else DirectionalComboChecker2 = 0;

			}
 //   if (!(st->buttons & CONT_START) && !(st->buttons & CONT_A) && !(st->buttons & CONT_B) && !(st->buttons & CONT_X) && !(st->buttons & CONT_Y) && !(st->buttons & CONT_DPAD_RIGHT) && !(st->buttons & CONT_DPAD_UP) && !(st->buttons & CONT_DPAD_DOWN) && !(st->buttons & CONT_DPAD_LEFT) && InputAllowed2 == 1) {
    if ( !(st->buttons & CONT_DPAD_RIGHT)  && (st->joyx < 64) && !(st->buttons & CONT_DPAD_UP)  && (st->joyy > -64) && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64) && !(st->buttons & CONT_DPAD_LEFT)  && (st->joyx > -64) && DirectionalInputAllowed2 == 1 && GroundLevel2 == 1) {

            
            //printf("AnimationName: %s\n", AnimationName2);
            //printf("Frame Amount: %d\n", FrameAmount2);
            //printf("Loop: %d\n", AnimationLoop2);
            //printf("Animation Type: %d\n", AnimationType2);
            //printf("Animation Speed: %d\n", AnimationSpeed2);          
            if(AnimationID2 != -1){
            AnimationID2 = -1;
            MovementReadCompulsory(0, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
            //AnimationName2 = "STANDING";
            WhichAnimationFrame2 = 1;
            AnimationTicks2 = 1;
            }

			}

    if (st->buttons & CONT_X) {


            
            if(ButtonInputAllowed2 == 1){

            if(AnimationType2 == 1){
            TemporaryAnimationID2 = 21;
            if(DirectionalComboChecker2 == 3) TemporaryAnimationID2+=3;
            else if(DirectionalComboChecker2 == 5) TemporaryAnimationID2+=4;
            else if(DirectionalComboChecker2 == 9) TemporaryAnimationID2+=5;
            else if(st->buttons & CONT_A) TemporaryAnimationID2+=2;

            AnimationValidityCheck2 = MovementReadHuman(TemporaryAnimationID2, GroundLevel2, CrouchPosition2, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationEnemyAcceleration2, &AnimationType2, &AnimationStrength2, &WhichSpecial2, &WhichMissSoundEffect2, &WhichSoundEffectFrame2 ,&WhichHitSoundEffect2);
            if(AnimationValidityCheck2 == 1 && AnimationID2 != TemporaryAnimationID2){
            WhichAnimationFrame2 = 1;
            DirectionalInputAllowed2 = 0;
            AnimationID2 = TemporaryAnimationID2;
            AnimationTicks2 = 1;
            SpecialAnimationFrame2 = 0;
            //AnimationName2 = AnimationBuffer2;
            ButtonInputAllowed2 = 0;
            }
            }

            if(ComboID2 == 3 && ComboChecker2 == 0){
            ComboChecker2 = 1;
            ButtonInputAllowed2 = 0;
            }
            }

            DirectionalComboChecker2 = 0;

			}




if (st->buttons & CONT_B) {

            if(ButtonInputAllowed2 == 1){
            if(AnimationType2 == 1){
            TemporaryAnimationID2 = 11;
            if(DirectionalComboChecker2 == 3) TemporaryAnimationID2+=3;
            else if(DirectionalComboChecker2 == 5) TemporaryAnimationID2+=4;
            else if(DirectionalComboChecker2 == 9) TemporaryAnimationID2+=5;

            AnimationValidityCheck2 = MovementReadHuman(TemporaryAnimationID2, GroundLevel2, CrouchPosition2, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationEnemyAcceleration2, &AnimationType2, &AnimationStrength2, &WhichSpecial2, &WhichMissSoundEffect2, &WhichSoundEffectFrame2 ,&WhichHitSoundEffect2);
            if(AnimationValidityCheck2 == 1 && AnimationID2 != TemporaryAnimationID2){
            WhichAnimationFrame2 = 1;
            DirectionalInputAllowed2 = 0;
            AnimationID2 = TemporaryAnimationID2;
            AnimationTicks2 = 1;
            SpecialAnimationFrame2 = 0;
            //AnimationName2 = AnimationBuffer2;
            ButtonInputAllowed2 = 0;
            }
            }
            if(ComboID2 == 2 && ComboChecker2 == 0){
            ComboChecker2 = 1;
            ButtonInputAllowed2 = 0;
            }
            }

            DirectionalComboChecker2 = 0;
			}


if (st->buttons & CONT_A) {


            if(ButtonInputAllowed2 == 1){
            if(AnimationType2 == 1){
            TemporaryAnimationID2 = 1;
            if(DirectionalComboChecker2 == 3) TemporaryAnimationID2+=3;
            else if(DirectionalComboChecker2 == 5) TemporaryAnimationID2+=4;
            else if(DirectionalComboChecker2 == 9) TemporaryAnimationID2+=5;
            else if(st->buttons & CONT_X) TemporaryAnimationID2+=2;

            AnimationValidityCheck2 = MovementReadHuman(TemporaryAnimationID2, GroundLevel2, CrouchPosition2, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationEnemyAcceleration2, &AnimationType2, &AnimationStrength2, &WhichSpecial2, &WhichMissSoundEffect2, &WhichSoundEffectFrame2 ,&WhichHitSoundEffect2);
            if(AnimationValidityCheck2 == 1 && AnimationID2 != TemporaryAnimationID2){
            WhichAnimationFrame2 = 1;
            DirectionalInputAllowed2 = 0;
            AnimationID2 = TemporaryAnimationID2;
            AnimationTicks2 = 1;
            SpecialAnimationFrame2 = 0;
            //AnimationName2 = AnimationBuffer2;
            ButtonInputAllowed2 = 0;
            }
            }

            if(ComboID2 == 1 && ComboChecker2 == 0){
            ComboChecker2 = 1;
            ButtonInputAllowed2 = 0;
            }
            }

            DirectionalComboChecker2 = 0;

			}

if (st->buttons & CONT_Y) {

            if(ButtonInputAllowed2 == 1){
            if(AnimationType2 == 1){
            TemporaryAnimationID2 = 31;
            if(DirectionalComboChecker2 == 3) TemporaryAnimationID2+=3;
            else if(DirectionalComboChecker2 == 5) TemporaryAnimationID2+=4;
            else if(DirectionalComboChecker2 == 9) TemporaryAnimationID2+=5;
            AnimationValidityCheck2 = MovementReadHuman(TemporaryAnimationID2, GroundLevel2, CrouchPosition2, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationEnemyAcceleration2, &AnimationType2, &AnimationStrength2, &WhichSpecial2, &WhichMissSoundEffect2, &WhichSoundEffectFrame2 ,&WhichHitSoundEffect2);
            if(AnimationValidityCheck2 == 1 && AnimationID2 != TemporaryAnimationID2){
            WhichAnimationFrame2 = 1;
            DirectionalInputAllowed2 = 0;
            AnimationID2 = TemporaryAnimationID2;
            AnimationTicks2 = 1;
            SpecialAnimationFrame2 = 0;
            //AnimationName2 = AnimationBuffer2;
            ButtonInputAllowed2 = 0;
            }
            }

            if(ComboID2 == 4 && ComboChecker2 == 0){
            ButtonInputAllowed2 = 0;
            ComboChecker2 = 1;
            }
            }

            DirectionalComboChecker2 = 0;

			}

    if ((st->ltrig) > 0) {


            
            if(ButtonInputAllowed2 == 1){

            if(AnimationType2 == 1){
            TemporaryAnimationID2 = 41;
            if(DirectionalComboChecker2 == 3) TemporaryAnimationID2+=3;
            else if(DirectionalComboChecker2 == 5) TemporaryAnimationID2+=4;
            else if(DirectionalComboChecker2 == 9) TemporaryAnimationID2+=5;

            AnimationValidityCheck2 = MovementReadHuman(TemporaryAnimationID2, GroundLevel2, CrouchPosition2, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationEnemyAcceleration2, &AnimationType2, &AnimationStrength2, &WhichSpecial2, &WhichMissSoundEffect2, &WhichSoundEffectFrame2 ,&WhichHitSoundEffect2);
            if(AnimationValidityCheck2 == 1 && AnimationID2 != TemporaryAnimationID2){
            WhichAnimationFrame2 = 1;
            DirectionalInputAllowed2 = 0;
            AnimationID2 = TemporaryAnimationID2;
            AnimationTicks2 = 1;
            SpecialAnimationFrame2 = 0;
            //AnimationName2 = AnimationBuffer2;
            ButtonInputAllowed2 = 0;
            }
            }

            if(ComboID2 == 5 && ComboChecker2 == 0){
            ButtonInputAllowed2 = 0;
            ComboChecker2 = 1;
            }
             if ((st->rtrig) > 0) {    
             if(DebuggingMode == 1) DebuggingMode = 0;
             else DebuggingMode = 1;
             }        
            }

            DirectionalComboChecker2 = 0;

			}

    if ((st->rtrig) > 0) {


            
            if(ButtonInputAllowed2 == 1){

            if(AnimationType2 == 1){
            TemporaryAnimationID2 = 51;
            if(DirectionalComboChecker2 == 3) TemporaryAnimationID2+=3;
            else if(DirectionalComboChecker2 == 5) TemporaryAnimationID2+=4;
            else if(DirectionalComboChecker2 == 9) TemporaryAnimationID2+=5;

            AnimationValidityCheck2 = MovementReadHuman(TemporaryAnimationID2, GroundLevel2, CrouchPosition2, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationEnemyAcceleration2, &AnimationType2, &AnimationStrength2, &WhichSpecial2, &WhichMissSoundEffect2, &WhichSoundEffectFrame2 ,&WhichHitSoundEffect2);
            if(AnimationValidityCheck2 == 1 && AnimationID2 != TemporaryAnimationID2){
            WhichAnimationFrame2 = 1;
            DirectionalInputAllowed2 = 0;
            AnimationID2 = TemporaryAnimationID2;
            AnimationTicks2 = 1;
            SpecialAnimationFrame2 = 0;
            //AnimationName2 = AnimationBuffer2;
            ButtonInputAllowed2 = 0;
            }
            }

            if(ComboID2 == 6 && ComboChecker2 == 0){
            ComboChecker2 = 1;
            ButtonInputAllowed2 = 0;
            }
            }

            DirectionalComboChecker2 = 0;

			}


    if ( !(st->buttons & CONT_X) && !(st->buttons & CONT_B) && !(st->buttons & CONT_A) && !(st->buttons & CONT_Y) && !(st->buttons & CONT_START) && (st->rtrig) == 0 && (st->ltrig) == 0 && AnimationID2 != -10 && ButtonInputAllowed2 == 0) {
            ButtonInputAllowed2 = 1;
            //printf("INPUT ALLOWED AGAIN!\n");
            //printf("STATUS: %d!\n", ButtonInputAllowed1);
			}
    //MAPLE_FOREACH_END()
 }


    if(AnimationType2 == 5 && CharHitStatus1 == 6){
	if(WhichAnimationFrame2 != SpecialAnimationFrame2){
            FrameSpecialReadHuman(CharacterName2, SpecialOffset2, &AnimationSpeed2, &AnimationEnemyAcceleration2, AnimationType2, &AnimationStrength2, &SpecialCharChangeX2, &SpecialCharChangeY2, &SpecialCharChangeX1, &SpecialCharChangeY1, &SpecialCharAlignment1, &JumpVelocity1, &ComboMovementX2, &ComboMovementY2);
    

    if(CharIsLeft2 == 1){
    PosCharX2 += SpecialCharChangeX2;
    }
    else{
    PosCharX2 -= SpecialCharChangeX2;
    }

    if(CharIsLeft1 == 0){
    PosCharX1 += SpecialCharChangeX1;
    }
    else{
    PosCharX1 -= SpecialCharChangeX1;
    }

    PosCharY2 += SpecialCharChangeY2;
    PosCharY1 += SpecialCharChangeY1;
    SpecialCharChangeX2 = 0;
    SpecialCharChangeY2 = 0;
    SpecialCharChangeX1 = 0;
    SpecialCharChangeY1 = 0;
    if(PosCharY2 < StageGround){
    GroundLevel2 = 0;
    }
    if(PosCharY1 < StageGround){
    GroundLevel1 = 0;
    }

    SpecialOffset2+=32;
    SpecialAnimationFrame2 = WhichAnimationFrame2;
    if(SpecialCharAlignment1 == 1){
    AnimationID1 = -6;
    MovementReadCompulsory(5, CharacterName1, AnimationBuffer1, &CharHitAnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    AnimationName1 = "HITHIGH0";
    WhichAnimationFrame1 = 1;
    AnimationSpeed1 = 61;
    AnimationTicks1 = 1;
    CharHitStatus1 = 6;

    }
    if(SpecialCharAlignment1 == 2){

    MovementReadCompulsory(7, CharacterName1, AnimationBuffer1, &CharHitAnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    AnimationName1 = "KNOKDOWN";
    WhichAnimationFrame1 = FrameAmount1;
    AnimationSpeed1 = 61;
    AnimationTicks1 = 1;
    CharHitStatus1 = 6;
    AnimationType1 = 5;
    }
    if(AnimationEnemyAcceleration2 != 0 && (PosCharY1 < StageGround || JumpVelocity1 != -480)){
    JumpAnimationSpeed1 = 61;
    JumpDirection1 = AnimationEnemyAcceleration2;
    if(CharIsLeft1 == 1){
    JumpDirection1 = -JumpDirection1; 
    }
    MovementReadCompulsory(7, CharacterName1, AnimationBuffer1, &CharHitAnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
    AnimationName1 = "KNOKDOWN";
    WhichAnimationFrame1 = FrameAmount1;
    AnimationSpeed1 = 61;
    AnimationTicks1 = 1;
    CharHitStatus1 = 4;
    AnimationType1 = 4;
    AnimationEnemyAcceleration2 = 0;
    CharHealth1 = CharHealth1-AnimationStrength2;
    //printf("Direction: %d\n", JumpDirection1);
    //printf("Velocity: %d\n", JumpVelocity1);
    }
    
    
	}

       }
    if(AnimationType2 == 6 && WhichSpecial2 != 0){
    if(SpecialAnimationFrame2 == 0){
    FirstSpecialReadHuman(CharacterName2, AnimationBuffer2, &FrameAmount2,  &AnimationEnemyAcceleration2, &AnimationType2, &AnimationStrength2, WhichSpecial2, &SpecialOffset2);
    WhichAnimationFrame2 = 1;
    SpecialAnimationFrame2 = 0;
    DirectionalInputAllowed2 = 0;
    AnimationLoop2 = 0;
    AnimationName2 = AnimationBuffer2;
    }
    if(SpecialAnimationFrame2 < WhichAnimationFrame2){
    FrameSpecialReadHuman(CharacterName2, SpecialOffset2, &AnimationSpeed2, &AnimationEnemyAcceleration2, AnimationType2, &AnimationStrength2, &SpecialCharChangeX2, &SpecialCharChangeY2, &SpecialCharChangeX1, &SpecialCharChangeY1, &SpecialCharAlignment1, &JumpVelocity1, &ComboMovementX2, &ComboMovementY2);
        
    if(CharIsLeft2 == 1){
    PosCharX2 += SpecialCharChangeX2;
    }
    else{
    PosCharX2 -= SpecialCharChangeX2;
    }
    PosCharY2 += SpecialCharChangeY2;
    SpecialCharChangeX2 = 0;
    SpecialCharChangeY2 = 0;

    if(PosCharY2 < StageGround && GroundLevel2 != 0){
    GroundLevel2 = 0;
    JumpVelocity2 = 0;
    WhichJumpStage2 = 4;
    JumpAnimationFlags2 = JumpIdleUpFlags2;
    JumpType2 = 0;
    WhichJumpFrame2 = 1;
    JumpTicks2 = 1;
    JumpAnimationSpeed2 = 1;
    }
    SpecialOffset2+=32;
    SpecialAnimationFrame2 = WhichAnimationFrame2;    
    } 
    if(CharIsLeft2 == 1){
    PosCharX2 += ComboMovementX2;
    }
    else{
    PosCharX2 -= ComboMovementX2;
    }  
    PosCharY2 += ComboMovementY2;
    }

    if(SpecialEffectStage2 != 0){
    SpecialEffectPosX2 += SpecialEffectSpeedX2;
    SpecialEffectPosY2 += SpecialEffectSpeedY2;
    SpecialEffectRange2 -= SpecialEffectSpeedX2;
    if(SpecialEffectStage2 == 2 && ((SpecialEffectRange2 <= 0 && SpecialEffectSpeedX2 >= 0) ||(SpecialEffectRange2 >= 0 && SpecialEffectSpeedX2 <= 0))){
    SpecialEffectReadHuman(CharacterName2, SpecialEffectNameBuffer2, SpecialEffectOffset2+32, &SpecialEffectAnimationSpeed2, &SpecialEffectFrameAmount2);   
    SpecialEffectStage2 = 3;
    SpecialEffectWhichFrame2 = 1;
    SpecialEffectTicks2 = 1;    
    }

    }
    if(AnimationType2 == 7){

    if(SpecialEffect2 == 0){
    FirstSpecialEffectReadHuman(CharacterName2, WhichSpecial2, &SpecialEffectOffset2, &SpecialEffectSizeX2, &SpecialEffectSizeY2, &SpecialEffectPosX2, &SpecialEffectPosY2, &SpecialEffectPosCharRelativity, &SpecialEffectWhichFrame2, &SpecialEffectRange2, &SpecialEffectSpeedX2, &SpecialEffectSpeedY2);
    SpecialEffect2 = 1;
    SpecialEffectStage2 = 0;
    SpecialEffectStrength2 = AnimationStrength2;
    SpecialEffectAcceleration2 = AnimationEnemyAcceleration2;

    if((SpecialEffectSpeedX2 < 0 && CharIsLeft2 == 1) || (SpecialEffectSpeedX2 > 0 && CharIsLeft2 == 0)){
    SpecialEffectRange2 = -SpecialEffectRange2;
    }
    if(CharIsLeft2 == 0){
    SpecialEffectSpeedX2 = -SpecialEffectSpeedX2;
    }
    printf("Special Effect Position: %d/%d\n", SpecialEffectPosX2, SpecialEffectPosY2);
    if((SpecialEffectSizeX2 <= 256 || SpecialEffectSizeX2 <= 256) && !(SpecialEffectSizeX2 > 256 || SpecialEffectSizeY2 > 256)){
    SpecialEffectTextureSizeX2 = 256;
    SpecialEffectTextureSizeY2 = 256;
    }
    if((SpecialEffectSizeX2 <= 128 || SpecialEffectSizeX2 <= 128) && !(SpecialEffectSizeX2 > 128 || SpecialEffectSizeY2 > 128)){
    SpecialEffectTextureSizeX2 = 128;
    SpecialEffectTextureSizeY2 = 128;
    }
    if((SpecialEffectSizeX2 <= 64 || SpecialEffectSizeX2 <= 64) && !(SpecialEffectSizeX2 > 64 || SpecialEffectSizeY2 > 64)){
    SpecialEffectTextureSizeX2 = 64;
    SpecialEffectTextureSizeY2 = 64;
    }
    if((SpecialEffectSizeX2 <= 32 || SpecialEffectSizeX2 <= 32) && !(SpecialEffectSizeX2 > 32 || SpecialEffectSizeY2 > 32)){
    SpecialEffectTextureSizeX2 = 32;
    SpecialEffectTextureSizeY2 = 32;
    }
    if((SpecialEffectSizeX2 <= 16 || SpecialEffectSizeX2 <= 16) && !(SpecialEffectSizeX2 > 16 || SpecialEffectSizeY2 > 16)){
    SpecialEffectTextureSizeX2 = 16;
    SpecialEffectTextureSizeY2 = 16;
    }
    if(SpecialEffectPosCharRelativity == 1 && CharIsLeft2 == 1){
    SpecialEffectPosX2 = DrawCharX2+LeftStageBorder+SpecialEffectPosX2;
    SpecialEffectPosY2 = PosCharY2+SpecialEffectPosY2;
    }
    if(SpecialEffectPosCharRelativity == 1 && CharIsLeft2 == 0){
    SpecialEffectPosX2 = DrawCharX2+LeftStageBorder+256-SpecialEffectPosX2-(SpecialEffectTextureSizeX2*2);
    SpecialEffectPosY2 = PosCharY2+SpecialEffectPosY2;
    }
    if(SpecialEffectPosCharRelativity == 0){
    SpecialEffectPosX2 = LeftStageBorder+SpecialEffectPosX2;
    }
    SpecialEffectSizeX2 *= 2;
    SpecialEffectSizeY2 *= 2;
    //printf("Real Size: %d/%d\n", SpecialEffectTextureSizeX2, SpecialEffectTextureSizeY2);
    SpecialEffectTexture2 = pvr_mem_malloc(SpecialEffectTextureSizeX2*SpecialEffectTextureSizeY2*2);
    
    }
    //printf("AnimationFrame: %d\n", WhichAnimationFrame2);
    //printf("SpecialEffect2: %d\n", SpecialEffect2);
    //printf("SpecialEffectWhichFrame2: %d\n", SpecialEffectWhichFrame2);
    //printf("SpecialEffectStage2: %d\n", SpecialEffectStage2);
    if(SpecialEffect2 == 1 && WhichAnimationFrame2 == SpecialEffectWhichFrame2 && SpecialEffectStage2 == 0){
    //printf("Loading Special Effect\n");
    SpecialEffectReadHuman(CharacterName2, SpecialEffectNameBuffer2, SpecialEffectOffset2, &SpecialEffectAnimationSpeed2, &SpecialEffectFrameAmount2);
    //SpecialEffectReadHuman(CharacterName2, SpecialEffectNameBuffer2, SpecialEffectOffset2, &SpecialEffectAnimationSpeed2, &SpecialEffectFrameAmount2);
    SpecialEffectStage2 = 1;
    SpecialEffectWhichFrame2 = 1;
    SpecialEffectTicks2 = 1;
    //printf("Name: %.8s\nSpeed: %d\nAmount: %d\n", SpecialEffectNameBuffer2, SpecialEffectAnimationSpeed2, SpecialEffectFrameAmount2);
    //printf("Done Reading Effect\n");
    }      
    }
    if(AnimationType2 == 8 && WhichSpecial2 != 0){

    if((SpecialAnimationFrame2 == 0) || (ComboChecker2 == 1 && WhichAnimationFrame2 >= FrameAmount2 && AnimationTicks2%AnimationSpeed2 == 0)){
    ComboReadHuman(AnimationID2, CharacterName2, AnimationBuffer2, &AnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationEnemyAcceleration2, &AnimationType2, &AnimationStrength2, &WhichSpecial2, &ComboID2, &SpecialCharChangeX2, &SpecialCharChangeY2);
    WhichAnimationFrame2 = 1;
    AnimationTicks2 = 1;
    ComboChecker2 = 0;
    SpecialAnimationFrame2++;
    
    if(CharIsLeft2 == 1){
    PosCharX2 += SpecialCharChangeX2;
    }
    else{
    PosCharX2 -= SpecialCharChangeX2;
    }
    PosCharY2 += SpecialCharChangeY2;
    SpecialCharChangeX2 = 0;
    SpecialCharChangeY2 = 0;
    if(PosCharY2 < StageGround){
    GroundLevel2 = 0;
    }
    
    }
    }