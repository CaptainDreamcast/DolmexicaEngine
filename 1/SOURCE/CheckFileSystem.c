void CheckFileSystem(){

char FileDir[NormalFileDirSize];
uint8 ReadyToRock;

ReadyToRock = 0;

sprintf(FileDir, "/cd/1ST_DOLM.BIN"); 
if(FileExists(FileDir)){
sprintf(FileSystemUsed, "/cd");
ReadyToRock = 1;
}

sprintf(FileDir, "/sd/1ST_DOLM.BIN"); //I have no clue how SD stuff works. It's more of a placeholder, really.
if(!ReadyToRock && FileExists(FileDir)){
sprintf(FileSystemUsed, "/sd");
ReadyToRock = 1;
}

sprintf(FileDir, "/rd/1ST_DOLM.BIN"); //This doesn't make much sense, does it? ;P
if(!ReadyToRock && FileExists(FileDir)){
sprintf(FileSystemUsed, "/rd");
ReadyToRock = 1;
}

if(!ReadyToRock) sprintf(FileSystemUsed, "/pc");


sprintf(StreamingFileSystemUsed, "%s", FileSystemUsed); //It was practical for Debugging, but now it seems to have outlived its usefulness.

}