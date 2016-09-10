void UpdateComputerCounters(
short NeedsMoreCounters[][ComputerCounterAmount], int CurrentChar, int OtherChar, char CharHitStatus[], 
int GroundLevel[], int CrouchPosition[], char CharIsHuman[], uint8* Difficulty){

uint8 WhichBeingHitCounter;
uint8 WhichHitCounter;

if(CrouchPosition[CurrentChar] != 0) WhichBeingHitCounter = CrouchBeingHitCounter;
else if(GroundLevel[CurrentChar] == 0) WhichBeingHitCounter = AirBeingHitCounter;
else WhichBeingHitCounter = GroundBeingHitCounter;

if(CrouchPosition[OtherChar] != 0) WhichHitCounter = CrouchHitCounter;
else if(GroundLevel[OtherChar] == 0) WhichHitCounter = AirHitCounter;
else WhichHitCounter = GroundHitCounter;

if(CharHitStatus[CurrentChar] == 3){
NeedsMoreCounters[CurrentChar][WhichBeingHitCounter]++;
NeedsMoreCounters[OtherChar][WhichHitCounter]++;
}

//else{
//NeedsMoreCounters[CurrentChar][WhichBeingHitCounter]--;
//NeedsMoreCounters[OtherChar][WhichHitCounter]--;
//}

if(CharIsHuman[CurrentChar]){ 
if(*Difficulty > 0) (*Difficulty)--;
}
else if(*Difficulty < MaximumDifficulty) (*Difficulty)++;

}