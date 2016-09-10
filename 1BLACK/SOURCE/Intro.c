int Intro(uint8 PlayOrCheck){

char FileDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];

uint8 IntroAmount;
uint8 WhichIntro;

WhichIntro = MaximumIntroAmount;


sprintf(MountPoint, "INTRO");

while(WhichIntro > 0){
sprintf(FileDir, "%s/INTRO/BOARDS/%d.sbd", FileSystemUsed, WhichIntro);
if(FileExists(FileDir)){
IntroAmount = WhichIntro;
WhichIntro = 0;
}
else{
WhichIntro--;
if(WhichIntro == 0) return(0);
}
}

srand(rtc_unix_secs());
WhichIntro = ((rand()%IntroAmount)+1);



if(PlayOrCheck == PlayIntro){
sprintf(FileDir, "%s/INTRO/BOARDS/%d.sbd", FileSystemUsed, WhichIntro);
LetsSeeTheStory(FileDir);
}


return(1);
}