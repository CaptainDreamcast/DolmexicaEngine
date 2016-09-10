CharWins[WhichCharWon] += 1;
if(CharWins[WhichCharWon] == 2) Winner = WhichCharWon;

WhichRound++;

if(CharHealth[WhichCharWon] == 1000){
FightStage = FightPerfectAnimation;
}
else FightStage = FightLetsSeeWhatHappens;