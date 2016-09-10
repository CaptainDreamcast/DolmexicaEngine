  //MAPLE_FOREACH_BEGIN(MAPLE_FUNC_CONTROLLER, cont_state_t, st)
		

    //if((cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER)) != NULL) {
    
    //if((cont = DolmexicaFetchCont(0, MAPLE_FUNC_CONTROLLER)) != NULL) {

    if((cont = maple_enum_dev(0, 0)) != NULL) {

    st = (cont_state_t *)maple_dev_status(cont);


    if ((st->buttons & CONT_START) && ButtonInputAllowed1 == 1) {
            FightStage+=1;
			}

    if (((st->buttons & CONT_DPAD_UP)  || (st->joyy <= -64)) && DirectionalInputAllowed1 == 1 && GroundLevel1 == 1 && JumpVelocity1 == -480 && JumpBlock1 == 0) {


      
            //AnimationName1 = "JUMPING1";
            WhichAnimationFrame1 = 1;
            //AnimationSpeed1 = 4;
            //FrameAmount1 = 1;
            //AnimationLoop1 =1;
            AnimationTicks1 = 1;

            if (((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64))){
             if(CharIsLeft1 == 1){
              JumpAnimationFlags1 = JumpForwardFlags1;
              JumpType1 = 1;
              }
             else{
             JumpAnimationFlags1 = JumpBackFlags1;
             JumpType1 = 2;
              }
             JumpDirection1 = CharSpeed1;
             }
            else if (((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64))){
             if(CharIsLeft1 == 0){
              JumpAnimationFlags1 = JumpForwardFlags1;
              JumpType1 = 1;
              }
             else{
             JumpAnimationFlags1 = JumpBackFlags1;
             JumpType1 = 2;
              }
             JumpDirection1 = -CharSpeed1;
             }
            else{
             JumpAnimationFlags1 = JumpIdleUpFlags1;
             JumpType1 = 0;
             }

            DirectionalInputAllowed1 = 0;
            ButtonInputAllowed1 = 0;

            GroundLevel1 = 0;
            JumpBlock1 = 1;

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
	}

   if (!(st->buttons & CONT_DPAD_UP)  && (st->joyy > -64) && GroundLevel1 == 1 && JumpBlock1 == 1) {

    JumpBlock1 = 0;
   }

if((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)){


            if(CrouchPosition1 != 0 && AnimationType1 == 1 && (AnimationType2 == 3 || AnimationType2 == 6) && ((CharIsLeft1 == 0 && (st->buttons & CONT_DPAD_RIGHT)) || (CharIsLeft1 == 1 && (st->buttons & CONT_DPAD_LEFT)))){
            if(AnimationID1 != -11){
            MovementReadCompulsory(10, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
            //AnimationName1 = "CROUBLOC";
            WhichAnimationFrame1 = 1; 
            AnimationTicks1 = 1;
            AnimationID1 = -11;

            CrouchPosition1 = 2;
           
            }
            }

   else if (AnimationType1 == 1 && DirectionalInputAllowed1 == 1 && GroundLevel1 == 1 && JumpVelocity1 == -480 && CrouchPosition1 != 2) {


            if(AnimationID1 != -4){
            AnimationID1 = -4;
            MovementReadCompulsory(3, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
            //AnimationName1 = "CROU_PRE";
            WhichAnimationFrame1 = 1;
            AnimationTicks1 = 1;
            }
            DirectionalInputAllowed1 = 0;
            CrouchPosition1 = 1;
			}


    else if (CrouchPosition1 == 1 && AnimationTicks1 >= AnimationSpeed1 && WhichAnimationFrame1 >= FrameAmount1) {

            if(AnimationType1 == 1){
            AnimationID1 = -5;
            MovementReadCompulsory(4, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
            //AnimationName1 = "CROU_DUR";
            WhichAnimationFrame1 = 1;
            AnimationTicks1 = 1;


            CrouchPosition1 = 2;
            }

            }

    


    if(DirectionalComboChecker1 == 0 && !(st->buttons & CONT_DPAD_RIGHT)  && (st->joyx < 64) && !(st->buttons & CONT_DPAD_LEFT)  && (st->joyx > -64)) DirectionalComboChecker1 += 1;
    else if(DirectionalComboChecker1 == 1 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && CharIsLeft1 == 1) DirectionalComboChecker1+= 1;
    else if(DirectionalComboChecker1 == 1 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && CharIsLeft1 == 0) DirectionalComboChecker1+= 1;
    else if(DirectionalComboChecker1 == 1 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && CharIsLeft1 == 0) DirectionalComboChecker1+= 3;
    else if(DirectionalComboChecker1 == 1 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && CharIsLeft1 == 1) DirectionalComboChecker1+= 3;
    else if(DirectionalComboChecker1 == 1 && !(st->buttons & CONT_DPAD_RIGHT)  && (st->joyx < 64) && !(st->buttons & CONT_DPAD_LEFT)  && (st->joyx > -64)){ }
    else if(DirectionalComboChecker1 == 2 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && CharIsLeft1 == 1){ }  
    else if(DirectionalComboChecker1 == 2 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && CharIsLeft1 == 0){ }  
    else if(DirectionalComboChecker1 == 4 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) && CharIsLeft1 == 0){ }  
    else if(DirectionalComboChecker1 == 4 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) && CharIsLeft1 == 1){ }  
    else if(DirectionalComboChecker1 == 7 && !(st->buttons & CONT_DPAD_LEFT & CONT_DPAD_RIGHT)  && (st->joyx < 64 && st->joyx > -64)) DirectionalComboChecker1++;  
    else if(DirectionalComboChecker1 == 8 && !(st->buttons & CONT_DPAD_LEFT & CONT_DPAD_RIGHT)  && (st->joyx < 64 && st->joyx > -64)) {}
    else if(DirectionalComboChecker1 == 8 && CharIsLeft1 == 1 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64))) DirectionalComboChecker1 += 1;                        
    else if(DirectionalComboChecker1 == 9 && CharIsLeft1 == 1 && ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64))) {} 
    else if(DirectionalComboChecker1 == 8 && CharIsLeft1 == 0 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64))) DirectionalComboChecker1 += 1;                        
    else if(DirectionalComboChecker1 == 9 && CharIsLeft1 == 0 && ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64))) {}   
    else DirectionalComboChecker1 = 0;


}

    if (!(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64) && AnimationType1 == 1) {

            if(CrouchPosition1 == 1 && AnimationTicks1 >= AnimationSpeed1 && WhichAnimationFrame1 >= FrameAmount1){
            AnimationID1 = -1;
            MovementReadCompulsory(0, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
            //AnimationName1 = "STANDING";
            WhichAnimationFrame1 = 1;
            AnimationTicks1 = 1;

            CrouchPosition1 = 0;
            DirectionalInputAllowed1 = 1;

            }

            if(CrouchPosition1 == 2){
          
            AnimationID1 = -4;
            MovementReadCompulsory(3, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
            //AnimationName1 = "CROU_PRE";
            WhichAnimationFrame1 = 1;
            AnimationTicks1 = 1;

            CrouchPosition1 = 1;

                }
			}

    if ((st->buttons & CONT_DPAD_RIGHT)  || (st->joyx >= 64)) {

            if(DirectionalInputAllowed1 == 1 && CrouchPosition1 != 0 && AnimationType1 == 1 && (AnimationType2 == 3 || AnimationType2 == 6) && CharIsLeft1 == 0){
            if(AnimationID1 != -11){
            MovementReadCompulsory(10, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
            //AnimationName1 = "CROUBLOC";
            WhichAnimationFrame1 = 1; 

            CrouchPosition1 = 2;

            AnimationTicks1 = 1;
            AnimationID1 = -11;
            }
            }
            else if(DirectionalInputAllowed1 == 1 && GroundLevel1 == 1){
            if(AnimationType1 == 1 && (AnimationType2 == 3 || AnimationType2 == 6) && CharIsLeft1 == 0){
            if(AnimationID1 != -10){
            MovementReadCompulsory(9, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
            //AnimationName1 = "BLOCKING";
            WhichAnimationFrame1 = 1; 
            AnimationTicks1 = 1;
            AnimationID1 = -10;
            }            
            }
            else{
            if(CharIsLeft1 == 1){
            if(AnimationID1 != -2){
            MovementReadCompulsory(1, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
            //AnimationName1 = "WALKINGF";
            WhichAnimationFrame1 = 1; 
            AnimationTicks1 = 1;
            AnimationID1 = -2;
            }
            }
            else{
            if(AnimationID1 != -3){
            MovementReadCompulsory(2, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
            //AnimationName1 = "WALKINGB";
            WhichAnimationFrame1 = 1; 
            AnimationTicks1 = 1;
            AnimationID1 = -3;
            }
            }
            if(DrawCharX1+CharOffset1+CharWidth1 >= DrawCharX2+256-CharOffset2-(CharWidth2/2) && CharIsLeft1 == 1 && GroundLevel2 == 1){
            PosCharX1 = PosCharX1+(CharSpeed1/2);
            PosCharX2 = PosCharX2+(CharSpeed1/2);
            }
            else{
            PosCharX1 = PosCharX1+CharSpeed1;
            }
	    }
            }

            if(DirectionalComboChecker1 == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft1 == 1) DirectionalComboChecker1+= 1;       
            else if(DirectionalComboChecker1 == 2 && CharIsLeft1 == 1 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)) DirectionalComboChecker1+= 1;
            else if(DirectionalComboChecker1 == 2 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft1 == 1) { } 
            else if(DirectionalComboChecker1 == 3 && CharIsLeft1 == 1 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)){ } //D,DF,F
            else if(DirectionalComboChecker1 == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft1 == 0) DirectionalComboChecker1+= 3;       
            else if(DirectionalComboChecker1 == 4 && CharIsLeft1 == 0 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)) DirectionalComboChecker1+= 1;
            else if(DirectionalComboChecker1 == 4 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft1 == 0) { } 
            else if(DirectionalComboChecker1 == 5 && CharIsLeft1 == 0 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)){ }// D,DB, B
            else if(DirectionalComboChecker1 == 0 && CharIsLeft1 == 1 && !(st->buttons & CONT_DPAD_DOWN)  && !(st->buttons & CONT_DPAD_UP) && (st->joyy < 64) && (st->joyy > -64)) DirectionalComboChecker1 = 7;                        
            else if(DirectionalComboChecker1 == 7 && CharIsLeft1 == 1 && !(st->buttons & CONT_DPAD_DOWN)  && !(st->buttons & CONT_DPAD_UP) && (st->joyy < 64) && (st->joyy > -64)) {}
            else if(DirectionalComboChecker1 == 8 && CharIsLeft1 == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64))) DirectionalComboChecker1 += 1;                        
            else if(DirectionalComboChecker1 == 9 && CharIsLeft1 == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64))) {}  
            else DirectionalComboChecker1 = 0;

                        }

    if ((st->buttons & CONT_DPAD_LEFT)  || (st->joyx <= -64)) {

            if(DirectionalInputAllowed1 == 1 && CrouchPosition1 != 0 && AnimationType1 == 1 && (AnimationType2 == 3 || AnimationType2 == 6) && CharIsLeft1 == 1){
            if(AnimationID1 != -11){
            MovementReadCompulsory(10, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
            //AnimationName1 = "CROUBLOC";
            WhichAnimationFrame1 = 1; 

            CrouchPosition1 = 2;

            AnimationTicks1 = 1;
            AnimationID1 = -11;
            }
            }
            else if(DirectionalInputAllowed1 == 1 && GroundLevel1 == 1){
            if(AnimationType1 == 1 && (AnimationType2 == 3 || AnimationType2 == 6) && CharIsLeft1 == 1){
            if(AnimationID1 != -10){
            MovementReadCompulsory(9, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
            //AnimationName1 = "BLOCKING";
            WhichAnimationFrame1 = 1; 
            AnimationTicks1 = 1;
            AnimationID1 = -10;
            }            
            }
            else{
            if(CharIsLeft1 == 0){
            if(AnimationID1 != -2){
            MovementReadCompulsory(1, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
            //AnimationName1 = "WALKINGF";
            WhichAnimationFrame1 = 1; 
            AnimationTicks1 = 1;
            AnimationID1 = -2;
            }
            }
            else{
            if(AnimationID1 != -3){
            MovementReadCompulsory(2, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);
            //AnimationName1 = "WALKINGB";
            WhichAnimationFrame1 = 1; 
            AnimationTicks1 = 1;
            AnimationID1 = -3;
            }
            }
            if(DrawCharX2+CharOffset2+(CharWidth2/2) >= DrawCharX1+256-CharOffset1-CharWidth1 && CharIsLeft1 == 0 && GroundLevel2 == 1){
            PosCharX1 = PosCharX1-(CharSpeed1/2);
            PosCharX2 = PosCharX2-(CharSpeed1/2);
            }
            else{
            PosCharX1 = PosCharX1-CharSpeed1;
            }
            }
            }


            if(DirectionalComboChecker1 == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft1 == 0) DirectionalComboChecker1+= 1;       
            else if(DirectionalComboChecker1 == 2 && CharIsLeft1 == 0 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)) DirectionalComboChecker1+= 1;
            else if(DirectionalComboChecker1 == 2 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft1 == 0) { } 
            else if(DirectionalComboChecker1 == 3 && CharIsLeft1 == 0 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)){ }// D,DF,F
            else if(DirectionalComboChecker1 == 1 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft1 == 1) DirectionalComboChecker1+= 3;       
            else if(DirectionalComboChecker1 == 4 && CharIsLeft1 == 1 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)) DirectionalComboChecker1+= 1;   
            else if(DirectionalComboChecker1 == 4 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64)) && CharIsLeft1 == 1) { } 
            else if(DirectionalComboChecker1 == 5 && CharIsLeft1 == 1 && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64)){ }// D,DB,B
            else if(DirectionalComboChecker1 == 0 && CharIsLeft1 == 0 && !(st->buttons & CONT_DPAD_DOWN & CONT_DPAD_UP)  && (st->joyy < 64 && st->joyy > -64)) DirectionalComboChecker1 = 7;                        
            else if(DirectionalComboChecker1 == 7 && CharIsLeft1 == 0 && !(st->buttons & CONT_DPAD_DOWN & CONT_DPAD_UP)  && (st->joyy < 64 && st->joyy > -64)) {}  
            else if(DirectionalComboChecker1 == 8 && CharIsLeft1 == 0 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64))) DirectionalComboChecker1 += 1;                        
            else if(DirectionalComboChecker1 == 9 && CharIsLeft1 == 0 && ((st->buttons & CONT_DPAD_DOWN)  || (st->joyy >= 64))) {}  
            else DirectionalComboChecker1 = 0;

			}
 //   if (!(st->buttons & CONT_START) && !(st->buttons & CONT_A) && !(st->buttons & CONT_B) && !(st->buttons & CONT_X) && !(st->buttons & CONT_Y) && !(st->buttons & CONT_DPAD_RIGHT) && !(st->buttons & CONT_DPAD_UP) && !(st->buttons & CONT_DPAD_DOWN) && !(st->buttons & CONT_DPAD_LEFT) && InputAllowed1 == 1) {
    if ( !(st->buttons & CONT_DPAD_RIGHT)  && (st->joyx < 64) && !(st->buttons & CONT_DPAD_UP)  && (st->joyy > -64) && !(st->buttons & CONT_DPAD_DOWN)  && (st->joyy < 64) && !(st->buttons & CONT_DPAD_LEFT)  && (st->joyx > -64) && DirectionalInputAllowed1 == 1 && GroundLevel1 == 1) {

                  
            if(AnimationID1 != -1){
            AnimationID1 = -1;
            MovementReadCompulsory(0, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationType1);

            WhichAnimationFrame1 = 1;
            AnimationTicks1 = 1;
            }

			}

    if (st->buttons & CONT_X) {


            
            if(ButtonInputAllowed1 == 1){

            if(AnimationType1 == 1){
            TemporaryAnimationID1 = 21;
            if(DirectionalComboChecker1 == 3) TemporaryAnimationID1+=3;
            else if(DirectionalComboChecker1 == 5) TemporaryAnimationID1+=4;
            else if(DirectionalComboChecker1 == 9) TemporaryAnimationID1+=5;
            else if(st->buttons & CONT_A) TemporaryAnimationID1+=2;

            AnimationValidityCheck1 = MovementReadHuman(TemporaryAnimationID1, GroundLevel1, CrouchPosition1, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationEnemyAcceleration1, &AnimationType1, &AnimationStrength1, &WhichSpecial1, &WhichMissSoundEffect1, &WhichSoundEffectFrame1 ,&WhichHitSoundEffect1);
            if(AnimationValidityCheck1 == 1 && AnimationID1 != TemporaryAnimationID1){
            WhichAnimationFrame1 = 1;
            DirectionalInputAllowed1 = 0;
            AnimationID1 = TemporaryAnimationID1;
            AnimationTicks1 = 1;
            SpecialAnimationFrame1 = 0;
            //AnimationName1 = AnimationBuffer1;
            ButtonInputAllowed1 = 0;
            }
            }

            if(ComboID1 == 3 && ComboChecker1 == 0){
            ComboChecker1 = 1;
            ButtonInputAllowed1 = 0;
            }
            }

            DirectionalComboChecker1 = 0;

			}




if (st->buttons & CONT_B) {

            if(ButtonInputAllowed1 == 1){
            if(AnimationType1 == 1){
            TemporaryAnimationID1 = 11;
            if(DirectionalComboChecker1 == 3) TemporaryAnimationID1+=3;
            else if(DirectionalComboChecker1 == 5) TemporaryAnimationID1+=4;
            else if(DirectionalComboChecker1 == 9) TemporaryAnimationID1+=5;
            AnimationValidityCheck1 = MovementReadHuman(TemporaryAnimationID1, GroundLevel1, CrouchPosition1, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationEnemyAcceleration1, &AnimationType1, &AnimationStrength1, &WhichSpecial1, &WhichMissSoundEffect1, &WhichSoundEffectFrame1 ,&WhichHitSoundEffect1);
            if(AnimationValidityCheck1 == 1 && AnimationID1 != TemporaryAnimationID1){
            WhichAnimationFrame1 = 1;

            DirectionalInputAllowed1 = 0;
            SpecialAnimationFrame1 = 0;
            AnimationID1 = TemporaryAnimationID1;
            AnimationTicks1 = 1;
            //AnimationName1 = AnimationBuffer1;
            ButtonInputAllowed1 = 0;
            }
            }

            if(ComboID1 == 2 && ComboChecker1 == 0){
            ComboChecker1 = 1;
            ButtonInputAllowed1 = 0;
            }
            }

            DirectionalComboChecker1 = 0;
			}


if (st->buttons & CONT_A) {


            if(ButtonInputAllowed1 == 1){
            if(AnimationType1 == 1){  
            TemporaryAnimationID1 = 1;
            if(DirectionalComboChecker1 == 3) TemporaryAnimationID1+=3;
            else if(DirectionalComboChecker1 == 5) TemporaryAnimationID1+=4;
            else if(DirectionalComboChecker1 == 9) TemporaryAnimationID1+=5;  
            else if(st->buttons & CONT_X) TemporaryAnimationID1+=2;   
            AnimationValidityCheck1 = MovementReadHuman(TemporaryAnimationID1, GroundLevel1, CrouchPosition1, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationEnemyAcceleration1, &AnimationType1, &AnimationStrength1, &WhichSpecial1, &WhichMissSoundEffect1, &WhichSoundEffectFrame1 ,&WhichHitSoundEffect1);
            if(AnimationValidityCheck1 == 1 && AnimationID1 != TemporaryAnimationID1){
            WhichAnimationFrame1 = 1;

            DirectionalInputAllowed1 = 0;
            AnimationID1 = TemporaryAnimationID1;
            AnimationTicks1 = 1;
            SpecialAnimationFrame1 = 0;
            //AnimationName1 = AnimationBuffer1;
            ButtonInputAllowed1 = 0;
            }
            }

            if(ComboID1 == 1 && ComboChecker1 == 0){
            ComboChecker1 = 1;
            ButtonInputAllowed1 = 0;
            }
            }

            DirectionalComboChecker1 = 0;

			}

if (st->buttons & CONT_Y) {

            if(ButtonInputAllowed1 == 1){
            if(AnimationType1 == 1){
            TemporaryAnimationID1 = 31;
            if(DirectionalComboChecker1 == 3) TemporaryAnimationID1+=3;
            else if(DirectionalComboChecker1 == 5) TemporaryAnimationID1+=4;
            else if(DirectionalComboChecker1 == 9) TemporaryAnimationID1+=5;
            AnimationValidityCheck1 = MovementReadHuman(TemporaryAnimationID1, GroundLevel1, CrouchPosition1, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationEnemyAcceleration1, &AnimationType1, &AnimationStrength1, &WhichSpecial1, &WhichMissSoundEffect1, &WhichSoundEffectFrame1 ,&WhichHitSoundEffect1);
            if(AnimationValidityCheck1 == 1 && AnimationID1 != TemporaryAnimationID1){
            WhichAnimationFrame1 = 1;

            DirectionalInputAllowed1 = 0;
            SpecialAnimationFrame1 = 0;
            AnimationID1 = TemporaryAnimationID1;
            AnimationTicks1 = 1;
            //AnimationName1 = AnimationBuffer1;
            ButtonInputAllowed1 = 0;
            }
            }

            if(ComboID1 == 4 && ComboChecker1 == 0){
            ButtonInputAllowed1 = 0;
            ComboChecker1 = 1;
            }
            }

            DirectionalComboChecker1 = 0;

			}

    if ((st->ltrig) > 0) {


            
            if(ButtonInputAllowed1 == 1){

            if(AnimationType1 == 1){
            TemporaryAnimationID1 = 41;
            if(DirectionalComboChecker1 == 3) TemporaryAnimationID1+=3;
            else if(DirectionalComboChecker1 == 5) TemporaryAnimationID1+=4;
            else if(DirectionalComboChecker1 == 9) TemporaryAnimationID1+=5;

            AnimationValidityCheck1 = MovementReadHuman(TemporaryAnimationID1, GroundLevel1, CrouchPosition1, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationEnemyAcceleration1, &AnimationType1, &AnimationStrength1, &WhichSpecial1, &WhichMissSoundEffect1, &WhichSoundEffectFrame1 ,&WhichHitSoundEffect1);
            if(AnimationValidityCheck1 == 1 && AnimationID1 != TemporaryAnimationID1){
            WhichAnimationFrame1 = 1;
            DirectionalInputAllowed1 = 0;
            AnimationID1 = TemporaryAnimationID1;
            AnimationTicks1 = 1;
            SpecialAnimationFrame1 = 0;
            //AnimationName1 = AnimationBuffer1;
            ButtonInputAllowed1 = 0;
            }
            }

            if(ComboID1 == 5 && ComboChecker1 == 0){
            ButtonInputAllowed1 = 0;
            ComboChecker1 = 1;
            }
             if ((st->rtrig) > 0) {    
             if(DebuggingMode == 1) DebuggingMode = 0;
             else DebuggingMode = 1;
             }        
            }

            DirectionalComboChecker1 = 0;

			}

    if ((st->rtrig) > 0) {


            
            if(ButtonInputAllowed1 == 1){

            if(AnimationType1 == 1){
            TemporaryAnimationID1 = 51;
            if(DirectionalComboChecker1 == 3) TemporaryAnimationID1+=3;
            else if(DirectionalComboChecker1 == 5) TemporaryAnimationID1+=4;
            else if(DirectionalComboChecker1 == 9) TemporaryAnimationID1+=5;

            AnimationValidityCheck1 = MovementReadHuman(TemporaryAnimationID1, GroundLevel1, CrouchPosition1, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationEnemyAcceleration1, &AnimationType1, &AnimationStrength1, &WhichSpecial1, &WhichMissSoundEffect1, &WhichSoundEffectFrame1 ,&WhichHitSoundEffect1);
            if(AnimationValidityCheck1 == 1 && AnimationID1 != TemporaryAnimationID1){
            WhichAnimationFrame1 = 1;
            DirectionalInputAllowed1 = 0;
            AnimationID1 = TemporaryAnimationID1;
            AnimationTicks1 = 1;
            SpecialAnimationFrame1 = 0;
            //AnimationName1 = AnimationBuffer1;
            ButtonInputAllowed1 = 0;
            }
            }

            if(ComboID1 == 6 && ComboChecker1 == 0){
            ComboChecker1 = 1;
            ButtonInputAllowed1 = 0;
            }
            }

            DirectionalComboChecker1 = 0;

			}


    if ( !(st->buttons & CONT_X) && !(st->buttons & CONT_B) && !(st->buttons & CONT_A) && !(st->buttons & CONT_Y) && !(st->buttons & CONT_START) && (st->rtrig) == 0 && (st->ltrig) == 0 && AnimationID1 != -10 && ButtonInputAllowed1 == 0) {
            ButtonInputAllowed1 = 1;
            //printf("INPUT ALLOWED AGAIN!\n");
            //printf("STATUS: %d!\n", ButtonInputAllowed1);
			}
    //MAPLE_FOREACH_END()
 }


    if(AnimationType1 == 5 && CharHitStatus2 == 6){
	if(WhichAnimationFrame1 != SpecialAnimationFrame1){
            FrameSpecialReadHuman(CharacterName1, SpecialOffset1, &AnimationSpeed1, &AnimationEnemyAcceleration1, AnimationType1, &AnimationStrength1, &SpecialCharChangeX1, &SpecialCharChangeY1, &SpecialCharChangeX2, &SpecialCharChangeY2, &SpecialCharAlignment2, &JumpVelocity2, &ComboMovementX1, &ComboMovementY1);
    
/*
    if(WhichCharLeft == 1){
    PosCharX1 += SpecialCharChangeX1;
    PosCharX2 += SpecialCharChangeX2;
    }
    if(WhichCharLeft == 2){
    PosCharX1 -= SpecialCharChangeX1;
    PosCharX2 -= SpecialCharChangeX2;
    }
*/
    if(CharIsLeft1 == 1){
    PosCharX1 += SpecialCharChangeX1;
    }
    else{
    PosCharX1 -= SpecialCharChangeX1;
    }

    if(CharIsLeft2 == 0){
    PosCharX2 += SpecialCharChangeX2;
    }
    else{
    PosCharX2 -= SpecialCharChangeX2;
    }

    PosCharY1 += SpecialCharChangeY1;
    PosCharY2 += SpecialCharChangeY2;
    SpecialCharChangeX1 = 0;
    SpecialCharChangeY1 = 0;
    SpecialCharChangeX2 = 0;
    SpecialCharChangeY2 = 0;
    if(PosCharY1 < StageGround){
    GroundLevel1 = 0;
    }
    if(PosCharY2 < StageGround){
    GroundLevel2 = 0;
    }

    SpecialOffset1+=32;
    SpecialAnimationFrame1 = WhichAnimationFrame1;
    if(SpecialCharAlignment2 == 1){
    AnimationID2 = -6;
    MovementReadCompulsory(5, CharacterName2, AnimationBuffer2, &CharHitAnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "HITHIGH0";
    WhichAnimationFrame2 = 1;
    AnimationSpeed2 = 61;
    AnimationTicks2 = 1;
    CharHitStatus2 = 6;

    }
    if(SpecialCharAlignment2 == 2){

    MovementReadCompulsory(7, CharacterName2, AnimationBuffer2, &CharHitAnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "KNOKDOWN";
    WhichAnimationFrame2 = FrameAmount2;
    AnimationSpeed2 = 61;
    AnimationTicks2 = 1;
    CharHitStatus2 = 6;
    AnimationType2 = 5;
    }
    if(AnimationEnemyAcceleration1 != 0 && (PosCharY2 < StageGround || JumpVelocity2 != -480)){
    JumpAnimationSpeed2 = 61;
    JumpDirection2 = AnimationEnemyAcceleration1;
    if(CharIsLeft2 == 1){
    JumpDirection2 = -JumpDirection2; 
    }
    MovementReadCompulsory(7, CharacterName2, AnimationBuffer2, &CharHitAnimationSpeed2, &FrameAmount2, &AnimationLoop2, &AnimationType2);
    AnimationName2 = "KNOKDOWN";
    WhichAnimationFrame2 = FrameAmount2;
    AnimationSpeed2 = 61;
    AnimationTicks2 = 1;
    CharHitStatus2 = 4;
    AnimationType2 = 4;
    AnimationEnemyAcceleration1 = 0;
    CharHealth2 = CharHealth2-AnimationStrength1;
    //printf("Direction: %d\n", JumpDirection2);
    //printf("Velocity: %d\n", JumpVelocity2);
    }
    
    
	}

       }
    if(AnimationType1 == 6 && WhichSpecial1 != 0){
    if(SpecialAnimationFrame1 == 0){
    FirstSpecialReadHuman(CharacterName1, AnimationBuffer1, &FrameAmount1,  &AnimationEnemyAcceleration1, &AnimationType1, &AnimationStrength1, WhichSpecial1, &SpecialOffset1);
    WhichAnimationFrame1 = 1;
    SpecialAnimationFrame1 = 0;
    DirectionalInputAllowed1 = 0;
    AnimationLoop1 = 0;
    AnimationName1 = AnimationBuffer1;
    }
    if(SpecialAnimationFrame1 < WhichAnimationFrame1){
    FrameSpecialReadHuman(CharacterName1, SpecialOffset1, &AnimationSpeed1, &AnimationEnemyAcceleration1, AnimationType1, &AnimationStrength1, &SpecialCharChangeX1, &SpecialCharChangeY1, &SpecialCharChangeX2, &SpecialCharChangeY2, &SpecialCharAlignment2, &JumpVelocity2, &ComboMovementX1, &ComboMovementY1);
        
    if(CharIsLeft1 == 1){
    PosCharX1 += SpecialCharChangeX1;
    }
    else{
    PosCharX1 -= SpecialCharChangeX1;
    }
    PosCharY1 += SpecialCharChangeY1;
    SpecialCharChangeX1 = 0;
    SpecialCharChangeY1 = 0;

    if(PosCharY1 < StageGround && GroundLevel1 != 0){
    GroundLevel1 = 0;
    JumpVelocity1 = 0;
    WhichJumpStage1 = 4;
    JumpAnimationFlags1 = JumpIdleUpFlags1;
    JumpType1 = 0;
    WhichJumpFrame1 = 1;
    JumpTicks1 = 1;
    JumpAnimationSpeed1 = 1;
    }
    SpecialOffset1+=32;
    SpecialAnimationFrame1 = WhichAnimationFrame1;    
    } 
    if(CharIsLeft1 == 1){
    PosCharX1 += ComboMovementX1;
    }
    else{
    PosCharX1 -= ComboMovementX1;
    }  
    PosCharY1 += ComboMovementY1;
    }

    if(SpecialEffectStage1 != 0){
    SpecialEffectPosX1 += SpecialEffectSpeedX1;
    SpecialEffectPosY1 += SpecialEffectSpeedY1;
    SpecialEffectRange1 -= SpecialEffectSpeedX1;
    if(SpecialEffectStage1 == 2 && ((SpecialEffectRange1 <= 0 && SpecialEffectSpeedX1 >= 0) ||(SpecialEffectRange1 >= 0 && SpecialEffectSpeedX1 <= 0))){
    SpecialEffectReadHuman(CharacterName1, SpecialEffectNameBuffer1, SpecialEffectOffset1+32, &SpecialEffectAnimationSpeed1, &SpecialEffectFrameAmount1);   
    SpecialEffectStage1 = 3;
    SpecialEffectWhichFrame1 = 1;
    SpecialEffectTicks1 = 1;    
    }

    }
    if(AnimationType1 == 7){

    if(SpecialEffect1 == 0){
    FirstSpecialEffectReadHuman(CharacterName1, WhichSpecial1, &SpecialEffectOffset1, &SpecialEffectSizeX1, &SpecialEffectSizeY1, &SpecialEffectPosX1, &SpecialEffectPosY1, &SpecialEffectPosCharRelativity, &SpecialEffectWhichFrame1, &SpecialEffectRange1, &SpecialEffectSpeedX1, &SpecialEffectSpeedY1);
    SpecialEffect1 = 1;
    SpecialEffectStage1 = 0;
    SpecialEffectStrength1 = AnimationStrength1;
    SpecialEffectAcceleration1 = AnimationEnemyAcceleration1;

    if((SpecialEffectSpeedX1 < 0 && CharIsLeft1 == 1) || (SpecialEffectSpeedX1 > 0 && CharIsLeft1 == 0)){
    SpecialEffectRange1 = -SpecialEffectRange1;
    }
    if(CharIsLeft1 == 0){
    SpecialEffectSpeedX1 = -SpecialEffectSpeedX1;
    }
    printf("Special Effect Position: %d/%d\n", SpecialEffectPosX1, SpecialEffectPosY1);
    if((SpecialEffectSizeX1 <= 256 || SpecialEffectSizeX1 <= 256) && !(SpecialEffectSizeX1 > 256 || SpecialEffectSizeY1 > 256)){
    SpecialEffectTextureSizeX1 = 256;
    SpecialEffectTextureSizeY1 = 256;
    }
    if((SpecialEffectSizeX1 <= 128 || SpecialEffectSizeX1 <= 128) && !(SpecialEffectSizeX1 > 128 || SpecialEffectSizeY1 > 128)){
    SpecialEffectTextureSizeX1 = 128;
    SpecialEffectTextureSizeY1 = 128;
    }
    if((SpecialEffectSizeX1 <= 64 || SpecialEffectSizeX1 <= 64) && !(SpecialEffectSizeX1 > 64 || SpecialEffectSizeY1 > 64)){
    SpecialEffectTextureSizeX1 = 64;
    SpecialEffectTextureSizeY1 = 64;
    }
    if((SpecialEffectSizeX1 <= 32 || SpecialEffectSizeX1 <= 32) && !(SpecialEffectSizeX1 > 32 || SpecialEffectSizeY1 > 32)){
    SpecialEffectTextureSizeX1 = 32;
    SpecialEffectTextureSizeY1 = 32;
    }
    if((SpecialEffectSizeX1 <= 16 || SpecialEffectSizeX1 <= 16) && !(SpecialEffectSizeX1 > 16 || SpecialEffectSizeY1 > 16)){
    SpecialEffectTextureSizeX1 = 16;
    SpecialEffectTextureSizeY1 = 16;
    }
    if(SpecialEffectPosCharRelativity == 1 && CharIsLeft1 == 1){
    SpecialEffectPosX1 = DrawCharX1+LeftStageBorder+SpecialEffectPosX1;
    SpecialEffectPosY1 = PosCharY1+SpecialEffectPosY1;
    }
    if(SpecialEffectPosCharRelativity == 1 && CharIsLeft1 == 0){
    SpecialEffectPosX1 = DrawCharX1+LeftStageBorder+256-SpecialEffectPosX1-(SpecialEffectTextureSizeX1*2);
    SpecialEffectPosY1 = PosCharY1+SpecialEffectPosY1;
    }
    if(SpecialEffectPosCharRelativity == 0){
    SpecialEffectPosX1 = LeftStageBorder+SpecialEffectPosX1;
    }
    SpecialEffectSizeX1 *= 2;
    SpecialEffectSizeY1 *= 2;
    //printf("Real Size: %d/%d\n", SpecialEffectTextureSizeX1, SpecialEffectTextureSizeY1);
    SpecialEffectTexture1 = pvr_mem_malloc(SpecialEffectTextureSizeX1*SpecialEffectTextureSizeY1*2);
    
    }
    //printf("AnimationFrame: %d\n", WhichAnimationFrame1);
    //printf("SpecialEffect1: %d\n", SpecialEffect1);
    //printf("SpecialEffectWhichFrame1: %d\n", SpecialEffectWhichFrame1);
    //printf("SpecialEffectStage1: %d\n", SpecialEffectStage1);
    if(SpecialEffect1 == 1 && WhichAnimationFrame1 == SpecialEffectWhichFrame1 && SpecialEffectStage1 == 0){
    //printf("Loading Special Effect\n");
    SpecialEffectReadHuman(CharacterName1, SpecialEffectNameBuffer1, SpecialEffectOffset1, &SpecialEffectAnimationSpeed1, &SpecialEffectFrameAmount1);
    //SpecialEffectReadHuman(CharacterName1, SpecialEffectNameBuffer1, SpecialEffectOffset1, &SpecialEffectAnimationSpeed1, &SpecialEffectFrameAmount1);
    SpecialEffectStage1 = 1;
    SpecialEffectWhichFrame1 = 1;
    SpecialEffectTicks1 = 1;
    //printf("Name: %.8s\nSpeed: %d\nAmount: %d\n", SpecialEffectNameBuffer1, SpecialEffectAnimationSpeed1, SpecialEffectFrameAmount1);
    //printf("Done Reading Effect\n");
    }      
    }
    if(AnimationType1 == 8 && WhichSpecial1 != 0){

    if((SpecialAnimationFrame1 == 0) || (ComboChecker1 == 1 && WhichAnimationFrame1 >= FrameAmount1 && AnimationTicks1%AnimationSpeed1 == 0)){
    ComboReadHuman(AnimationID1, CharacterName1, AnimationBuffer1, &AnimationSpeed1, &FrameAmount1, &AnimationLoop1, &AnimationEnemyAcceleration1, &AnimationType1, &AnimationStrength1, &WhichSpecial1, &ComboID1, &SpecialCharChangeX1, &SpecialCharChangeY1);
    WhichAnimationFrame1 = 1;
    AnimationTicks1 = 1;
    ComboChecker1 = 0;
    SpecialAnimationFrame1++;
    
    if(CharIsLeft1 == 1){
    PosCharX1 += SpecialCharChangeX1;
    }
    else{
    PosCharX1 -= SpecialCharChangeX1;
    }
    PosCharY1 += SpecialCharChangeY1;
    SpecialCharChangeX1 = 0;
    SpecialCharChangeY1 = 0;
    if(PosCharY1 < StageGround){
    GroundLevel1 = 0;
    }
    
    }
    }

