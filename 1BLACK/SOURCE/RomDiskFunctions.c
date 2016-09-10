void FileDirToRomDisk(char RomDiskDir[], char MountPoint[]){

file_t RomDiskFile;
uint8* RomDiskBuffer;
long RomDiskSize;


RomDiskFile = fs_open(RomDiskDir, O_RDONLY);

RomDiskSize = fs_total(RomDiskFile);

RomDiskBuffer = (uint8 *)malloc(RomDiskSize);

fs_read(RomDiskFile, RomDiskBuffer, RomDiskSize);

fs_romdisk_mount(MountPoint, RomDiskBuffer, 1);

fs_close(RomDiskFile);
}