void CheckFileSystem(){

char FileDir[NormalFileDirSize];
uint8 ReadyToRock;

ReadyToRock = 0;

#ifdef DOLMEXICA_SD
f_mount(0, &SuperCardFileSystemObject);
#endif

sprintf(FileDir, "/sd/DOLMEXICA/WHITE.pkg");
if(FileExists(FileDir)){
sprintf(FileSystemUsed, "/sd/DOLMEXICA");
ReadyToRock = 1;
}

sprintf(FileDir, "/cd/WHITE.pkg"); 
if(!ReadyToRock && FileExists(FileDir)){
sprintf(FileSystemUsed, "/cd");
ReadyToRock = 1;
}

sprintf(FileDir, "/rd/WHITE.pkg"); 
if(!ReadyToRock && FileExists(FileDir)){
sprintf(FileSystemUsed, "/rd");
ReadyToRock = 1;
}

if(!ReadyToRock) sprintf(FileSystemUsed, "/pc");


sprintf(StreamingFileSystemUsed, "%s", FileSystemUsed); //It was practical for Debugging, but now it seems to have outlived its usefulness.

}