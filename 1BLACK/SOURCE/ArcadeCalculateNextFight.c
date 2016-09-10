   (*WhichCharacterFight)++;

   if(CharIsHuman[CharacterOne] == 1){CurrentChar = CharacterTwo; OtherChar = CharacterOne;}
   else{CurrentChar = CharacterOne; OtherChar = CharacterTwo;}

   srand(rtc_unix_secs());
   PlayerID[CurrentChar] = ((rand()%CharacterAmount));

   ReadyToRock = 1;
   DirtyDeedsDoneDirtCheap = 0;   

   if((*WhichCharacterFight) >= ArcadeLength){DoNotShowTheScreen = 1; ReadyToRock = 0; OffTo = CreditStage;}

   while(ReadyToRock){
   ReadyToRock = 0;

    if(PlayerID[CurrentChar] == PlayerID[OtherChar]) ReadyToRock = 1;
    for(Bluff = 0; Bluff < *WhichCharacterFight; Bluff++) {
    if(PlayerID[CurrentChar] == CharIDCPU[Bluff]) ReadyToRock = 1;
    }

    if(ReadyToRock) PlayerID[CurrentChar]++;
    if(PlayerID[CurrentChar] == CharacterAmount){
    if(!DirtyDeedsDoneDirtCheap){ PlayerID[CurrentChar] = 0; DirtyDeedsDoneDirtCheap = 1;}
    else{printf("No Character found!\n"); DoNotShowTheScreen = 1; ReadyToRock = 0; OffTo = CreditStage;}
    }
    }

    CharIDCPU[*WhichCharacterFight] = PlayerID[CurrentChar];
    sprintf(CharacterName[CurrentChar], "%.8s", SmallPortraitData[PlayerID[CurrentChar]].CharacterName);
    sprintf(BackGroundName, "%.8s", SmallPortraitData[PlayerID[CurrentChar]].BackGroundName);
    printf("PlayerID: (%d)\n", PlayerID[CurrentChar]);
    printf("CharacterName: (%s)\n", CharacterName[CurrentChar]);
    printf("Stage: (%s)\n", BackGroundName);