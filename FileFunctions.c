#define StandardFileSystemFlag 0x80000000

file_t FileOpen(char* FileDir, uint32 Flags){

int ReturnValue;
int Result;

if(FileDir[0] == '/' && FileDir[1] == 's' && FileDir[2] == 'd' && FileDir[3] == '/'){

FileDir += 3;
ReturnValue = (int)malloc(sizeof(FIL));

if(Flags == O_RDONLY) Flags = FA_READ;
else if(Flags == O_WRONLY) Flags = FA_WRITE;
else Flags = (FA_READ | FA_WRITE);

Result = f_open((FIL*)ReturnValue, FileDir, Flags);
if(Result) {free((void*)ReturnValue); return(FILEHND_INVALID);}

}
else{

ReturnValue = fs_open(FileDir, Flags);
if(ReturnValue == FILEHND_INVALID) return(FILEHND_INVALID);
else ReturnValue |= StandardFileSystemFlag;

}


return((file_t)ReturnValue);
}

void FileClose(file_t FileHandler){

if(FileHandler & StandardFileSystemFlag){
fs_close((FileHandler & (~StandardFileSystemFlag)));
}
else{
f_close((FIL*)FileHandler);
free((void*)FileHandler);
}

}

uint32 FileRead(file_t FileHandler, void* Buffer, uint32 Size){

uint32 ReturnValue;

if(FileHandler & StandardFileSystemFlag) ReturnValue = fs_read((FileHandler & (~StandardFileSystemFlag)), Buffer, Size);
else f_read((FIL*) FileHandler, Buffer, Size, (UINT*)&ReturnValue);

return(ReturnValue);
}

uint32 FileWrite(file_t FileHandler, void* Buffer, uint32 Size){

uint32 ReturnValue;

if(FileHandler & StandardFileSystemFlag) ReturnValue = fs_write((FileHandler & (~StandardFileSystemFlag)), Buffer, Size);
else f_write((FIL*) FileHandler, Buffer, Size, (UINT*)&ReturnValue);

return(ReturnValue);
}

uint32 FileSeek(file_t FileHandler, uint32 Offset, int Flags){

uint32 ReturnValue;

if(FileHandler & StandardFileSystemFlag) ReturnValue = fs_seek((FileHandler & (~StandardFileSystemFlag)), Offset, Flags);
else{

if(Flags == SEEK_SET) ReturnValue = Offset;
else if(Flags == SEEK_CUR) ReturnValue = (f_tell((FIL*)FileHandler))+Offset;
else if(Flags == SEEK_END) ReturnValue = (f_size((FIL*)FileHandler))-Offset;
else ReturnValue = (f_tell((FIL*)FileHandler));

ReturnValue = f_lseek((FIL*)FileHandler, ReturnValue);

}

return(ReturnValue);
}

uint8 FileUnlink(char* FileDir){

uint8 ReturnValue;

if(FileDir[0] == '/' && FileDir[1] == 's' && FileDir[2] == 'd' && FileDir[3] == '/') ReturnValue = f_unlink((FileDir+3));
else ReturnValue = fs_unlink(FileDir);

return(ReturnValue);
}

char* FileMemoryMap(file_t FileHandler){

char* ReturnBuffer;

if(FileHandler & StandardFileSystemFlag) ReturnBuffer = fs_mmap((FileHandler & (~StandardFileSystemFlag)));
else return(NULL);

return(ReturnBuffer);
}

uint32 FileTotal(file_t FileHandler){

uint32 ReturnValue;

if(FileHandler & StandardFileSystemFlag) ReturnValue = fs_total((FileHandler & (~StandardFileSystemFlag)));
else ReturnValue = (f_size((FIL*)FileHandler));

return(ReturnValue);
}

uint32 FileTell(file_t FileHandler){

uint32 ReturnValue;

if(FileHandler & StandardFileSystemFlag) ReturnValue = fs_tell((FileHandler & (~StandardFileSystemFlag)));
else ReturnValue = (f_tell((FIL*)FileHandler));

return(ReturnValue);
}
