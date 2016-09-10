void LoadSoundEffect(sfxhnd_t* SFX, char SFXID, char CharacterName[], int SoundEffectVolume){
/*
file_t SFXArchive;

int Bluff;
char SFXFile[39];
long CurrentOffset;
long SFXOffset = SFXID*8;
char SFXName[9];
char WAVFile[20];

if(SFXID != 0){

Bluff = sprintf(SFXFile, "%s/%.8s.sfx", StreamingFileSystemUsed, CharacterName);

SFXArchive = fs_open(SFXFile, O_RDONLY);

CurrentOffset = fs_seek(SFXArchive, SFXOffset, 0);
fs_read(SFXArchive, SFXName, 8);

fs_close(SFXArchive);

Bluff = sprintf(WAVFile, "%s/%.8s.wav", StreamingFileSystemUsed, SFXName);

*SFX = snd_sfx_load(WAVFile);
snd_sfx_play(*SFX, SoundEffectVolume, 128);
snd_sfx_unload(*SFX);

}
*/
}

void LoadPreFightSoundEffects(sfxhnd_t* KnockDownSFX){

char SFXFile[NormalFileDirSize];

sprintf(SFXFile, "%s/FIGHTSFX/KNOKDOWN.wav", FileSystemUsed);

*KnockDownSFX = snd_sfx_load(SFXFile);

}

void LoadCharacterSoundEffects(sfxhnd_t CharacterSFX[][MaxSoundEffectsAllowed], char CharacterName[][10]){

file_t RomDiskFile;
size_t RomDiskSize;

uint8* RomDiskBuffer;

int Bluff;
int CurrentChar;
char FileDir[NormalFileDirSize];
char AlternateFileDir[NormalFileDirSize];
char SoundEffectName[10];
char MountPoint[NormalMountPointSize];

long CurrentOffset;

CurrentChar = CharacterOne;
Bluff = sprintf(MountPoint, "/TEMPORARYMOUNT");

do{

// ROMDISK START

Bluff = sprintf(FileDir, "%s/%.8s/%.8s.sfa", FileSystemUsed, CharacterName[CurrentChar], CharacterName[CurrentChar]);

RomDiskFile = fs_open(FileDir, O_RDONLY);

RomDiskSize = fs_total(RomDiskFile);

RomDiskBuffer = (uint8 *)malloc(RomDiskSize);

fs_read(RomDiskFile, RomDiskBuffer, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBuffer, 1);

fs_close(RomDiskFile);


// ROMDISK END

// REGISTER START

Bluff = sprintf(AlternateFileDir, "%s/%.8s/%.8s.sfx", FileSystemUsed, CharacterName[CurrentChar], CharacterName[CurrentChar]);
Bluff = sprintf(FileDir, "/ram/%.8s.sfx", CharacterName[CurrentChar]);

FileCopyToOtherFileSystem(AlternateFileDir, FileDir);

RomDiskFile = fs_open(FileDir, O_RDONLY);
RomDiskSize = fs_total(RomDiskFile);

CurrentOffset = HeaderSizeSFX+ActualNameSize;
Bluff = 1;

while(CurrentOffset < RomDiskSize){

fs_seek(RomDiskFile, CurrentOffset, 0);
fs_read(RomDiskFile, SoundEffectName, ActualNameSize);

sprintf(AlternateFileDir, "%s/%.8s.wav", MountPoint, SoundEffectName);

CharacterSFX[CurrentChar][Bluff] = snd_sfx_load(AlternateFileDir);

CurrentOffset+=ActualNameSize;
Bluff++;
}
fs_close(RomDiskFile);
fs_unlink(FileDir);
fs_romdisk_unmount(MountPoint);

CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);

}

void DeLoadCharacterSoundEffects(sfxhnd_t CharacterSFX[][MaxSoundEffectsAllowed], char CharacterName[][NormalNameSize]){

file_t RomDiskFile;
size_t RomDiskSize;

int Bluff;
int CurrentChar;
char FileDir[NormalFileDirSize];
long CurrentOffset;

CurrentChar = CharacterOne;

do{

Bluff = sprintf(FileDir, "%s/%.8s/%.8s.sfx", FileSystemUsed, CharacterName[CurrentChar], CharacterName[CurrentChar]);

RomDiskFile = fs_open(FileDir, O_RDONLY);

RomDiskSize = fs_total(RomDiskFile);

fs_close(RomDiskFile);

CurrentOffset = HeaderSizeSFX+ActualNameSize;
Bluff = 1;

while(CurrentOffset < RomDiskSize){

snd_sfx_unload(CharacterSFX[CurrentChar][Bluff]);

CurrentOffset+=ActualNameSize;
Bluff++;
}

CurrentChar++;
} while(CurrentChar <= MaxCharsLoopValue);

}