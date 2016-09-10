int LoadStage(int WhichStage)
{
file_t BGArchive;
file_t BackBG1PNG;
kos_img_t* KMG_BUFFER;
short BGLayers[1];
long int BackBG1Offset[8];
int ForeBG1Offset;
int ForeBG2Offset;
int BGMusicOffset;
long int CurrentOffset;
long int BackBG1Size[8];
char StageName[8];
BGArchive = fs_open("/rd/background.bgr", O_RDONLY);
fs_read(BGArchive, StageName, 8);
int i;
for (i=0; i<8; i++) printf("%c", StageName[i]);
if(i == 8 ){
    printf("\n");
    }
CurrentOffset = fs_seek(BGArchive, 8, 0);
fs_read(BGArchive, BGLayers, 1);
printf("BackGroundLayers: %d\n", *BGLayers);


CurrentOffset = fs_seek(BGArchive, 16, 0);
fs_read(BGArchive, BackBG1Offset, 8);
printf("OffsetPosition: %d\n", *BackBG1Offset);

CurrentOffset = fs_seek(BGArchive, 24, 0);
fs_read(BGArchive, BackBG1Size, 8);
printf("Size: %d\n", *BackBG1Size);
char PNG_BUFFER[*BackBG1Size];

CurrentOffset = fs_seek(BGArchive, *BackBG1Offset, 0);
fs_read(BGArchive, PNG_BUFFER, *BackBG1Size);
BackBG1PNG = fs_open("/ram/BackBG1.png", O_WRONLY);
fs_write(BackBG1PNG, PNG_BUFFER, *BackBG1Size);
printf("Background loaded. \n");
fs_close(BackBG1PNG);
fs_close(BGArchive);
BackBG1Texture = pvr_mem_malloc(512*512*2);
png_to_texture("/ram/BackBG1.png", BackBG1Texture, PNG_FULL_ALPHA);

printf("Texture in memory. \n");
}
