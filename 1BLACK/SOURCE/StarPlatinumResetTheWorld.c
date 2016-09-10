

    FightStage = FightPreRoundReset;
    if(WhichMode == ArcadeModeIdentifier) WhichRound = 1;
    else if(WhichMode == SurvivalModeIdentifier) WhichRound = 3;
    else WhichRound = 1;

    Winner = -1;
    if(MusicWorks == 1) cdrom_cdda_play(BackGroundHeaderData.BackGroundSoundTrack, BackGroundHeaderData.BackGroundSoundTrack, 16, CDDA_TRACKS);
    CurrentChar = CharacterOne;    

    do{

    if(WhichMode == ArcadeModeIdentifier) CharWins[CurrentChar] = 0;
    else if(WhichMode == SurvivalModeIdentifier) CharWins[CurrentChar] = 1;
    else CharWins[CurrentChar] = 0;
    SpecialLeft[CurrentChar] = SpecialStartValue;

    for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<ComputerCounterAmount; DirtyDeedsDoneDirtCheap++) NeedsMoreCounters[CurrentChar][DirtyDeedsDoneDirtCheap] = 0;

    CurrentChar++;
    } while(CurrentChar <= MaxCharsLoopValue);