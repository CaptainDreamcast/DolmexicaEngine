void SoundLoad(char FileDir[]){

char RamDiskFileDir[NormalFileDirSize];

if(FileExists(FileDir) && FileSystemUsed[1] != 'c'){
sprintf(RamDiskFileDir, "/ram/BGM.ogg");
FileCopyToOtherFileSystem(FileDir, RamDiskFileDir);
}

}

void SoundPlay(char FileDir[], char FallBackSoundTrack){

char RamDiskFileDir[NormalFileDirSize];
sprintf(RamDiskFileDir, "/ram/BGM.ogg");

sndoggvorbis_stop();
if(FileExists(RamDiskFileDir)) sndoggvorbis_start(RamDiskFileDir, MaximumSoundLoopValue);
else if(FileExists(FileDir)) sndoggvorbis_start(FileDir, MaximumSoundLoopValue);
else if(FallBackSoundTrack > 0) cdrom_cdda_play(FallBackSoundTrack, FallBackSoundTrack, 16, CDDA_TRACKS);

}

void SoundStopNew(uint8 Unlink){

char RamDiskFileDir[NormalFileDirSize];

sndoggvorbis_stop();
sprintf(RamDiskFileDir, "/ram/BGM.ogg");
if(Unlink && FileExists(RamDiskFileDir)) fs_unlink(RamDiskFileDir);

cdrom_cdda_pause();
}

#define SoundStop() SoundStopNew(1)

void SoundResume(char FileDir[]){

char RamDiskFileDir[NormalFileDirSize];
sprintf(RamDiskFileDir, "/ram/BGM.ogg");

sndoggvorbis_stop();
if(FileExists(RamDiskFileDir)) sndoggvorbis_start(RamDiskFileDir, MaximumSoundLoopValue);
else if(FileExists(FileDir)) sndoggvorbis_start(FileDir, MaximumSoundLoopValue);
else cdrom_cdda_resume();

}

void StartSoundFight(char StageName[], uint8 FallBackSoundTrack){

char FileDir[NormalFileDirSize];

sprintf(FileDir, "%s/STAGES/%s.ogg", FileSystemUsed, StageName);
SoundPlay(FileDir, FallBackSoundTrack);
}


void ResumeMenuSound(char StageName[]){
char FileDir[NormalFileDirSize];
sprintf(FileDir, "%s/STAGES/%s.ogg", FileSystemUsed, StageName);
SoundResume(FileDir);
}

void WhoAgainstWhoSoundPlay(int WhichMode){

char MountPoint[NormalMountPointSize];
char FileDir[NormalFileDirSize];


switch(WhichMode){
case ArcadeModeIdentifier:
sprintf(MountPoint, "/ARCADE");
break;
}

sprintf(FileDir, "%s%s/WHOAGAINSTWHO.ogg", FileSystemUsed, MountPoint);
SoundPlay(FileDir, WhoAgainstWhoTrack);
}
