void FileDirToRomDisk(char RomDiskDir[], char MountPoint[]){

file_t RomDiskFile;
uint8* RomDiskBuffer;
long RomDiskSize;


RomDiskFile = FileOpen(RomDiskDir, O_RDONLY);

RomDiskSize = FileTotal(RomDiskFile);

RomDiskBuffer = (uint8 *)malloc(RomDiskSize);

FileRead(RomDiskFile, RomDiskBuffer, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBuffer, 1);

FileClose(RomDiskFile);
}