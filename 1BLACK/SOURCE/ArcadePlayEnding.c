uint8 ArcadePlayEnding(char CharacterName[]){

char FileDir[NormalFileDirSize];

sprintf(FileDir, "%s/%.8s/BOARDS/ARCADE.sbd", FileSystemUsed, CharacterName);

if(FileExists(FileDir)){ 
if(LetsSeeTheStory(FileDir) == StairWayToHeavenIdentifier) return(0);
}

return(1);
}