uint8 CheckReturn(){

char FileDir[NormalFileDirSize];

sprintf(FileDir, "/cd/1ST_DOLM.BIN");
if(FileExists(FileDir)) return(BootMenuReturn);

//Not the prettiest solution, but I'm trying to weasel my way around a global filesystem flag here. Mission Accomplished.

return(BootLoaderReturn);
}