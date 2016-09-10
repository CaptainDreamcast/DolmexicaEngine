/* 

Finally coming to a C-source file near you: The Dolmexica Engine Debugging Mode!
*/

if(DebuggingMode == 1){


AnimationSpeed1 = DebuggingAnimationSpeed;
AnimationStrength1 = DebuggingAnimationStrength;

if((cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER)) != NULL) {
 st = (cont_state_t *)maple_dev_status(cont);

    if ((st->buttons & CONT_DPAD_LEFT) && DebugButtonInputAllowed == 1) {
            if(DebuggingSelection == 1) DebuggingAnimationSpeed--;
            else if(DebuggingSelection == 2) DebuggingAnimationStrength--;
            DebugButtonInputAllowed = 0;
     }

    if ((st->buttons & CONT_DPAD_RIGHT) && DebugButtonInputAllowed == 1) {
            if(DebuggingSelection == 1) DebuggingAnimationSpeed++;
            else if(DebuggingSelection == 2) DebuggingAnimationStrength++;
            DebugButtonInputAllowed = 0;
     }
    if ((st->buttons & CONT_DPAD_UP) && DebugButtonInputAllowed == 1) {
            DebuggingSelection--;
            if(DebuggingSelection <= 0 ) DebuggingSelection = 2;
            DebugButtonInputAllowed = 0;
     }

    if ((st->buttons & CONT_DPAD_DOWN) && DebugButtonInputAllowed == 1) {
            DebuggingSelection++;
            if(DebuggingSelection > 2 ) DebuggingSelection = 1;
            DebugButtonInputAllowed = 0;
     }

    if (!(st->buttons & CONT_DPAD_DOWN) && !(st->buttons & CONT_DPAD_UP) && !(st->buttons & CONT_DPAD_LEFT) && !(st->buttons & CONT_DPAD_RIGHT) && DebugButtonInputAllowed == 0) {

            DebugButtonInputAllowed = 1;
     }


 }

            if(DebuggingSelection == 1) {
            DrawArray("ANIMATIONSPEED ", 0, 0, LowerGuiPositionZ, 30, 2);
            DrawNumber(DebuggingAnimationSpeed, 0, 30, 30, LowerGuiPositionZ);
            }            
            else if(DebuggingSelection == 2) {
            DrawArray("ANIMATIONSTRENGTH ", 0, 0, LowerGuiPositionZ, 30, 2);
            DrawNumber(DebuggingAnimationStrength, 0, 30, 30, LowerGuiPositionZ);
            }           


}