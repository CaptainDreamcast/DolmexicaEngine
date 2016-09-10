int FetchCharData(char WhatInput, int GroundLevel){

file_t CharMoveInfo;

char CharToSearchFor[20];
sprintf(CharToSearchFor, "INITIATIONBUTTONS=[%c", WhatInput);
CharMoveInfo = fs_open("/rd/sagat.nfo", O_RDONLY);
int FileSize = fs_total(CharMoveInfo);
char FileContentArray[FileSize];
char* FileContent = FileContentArray;
int CurrentOffset;
fs_read(CharMoveInfo, FileContentArray, FileSize);
int i = 0;
int CheckLoopInner = 1;
int CheckLoopOuter = 1;
//while (*FileContent != CharToSearchFor[0] || *(FileContent+1) != CharToSearchFor[1] || *(FileContent+2) != CharToSearchFor[2] || *(FileContent+3) != CharToSearchFor[3]) {
while(CurrentOffset <= FileSize && CheckLoopOuter ==1){
//printf("CheckLoopOuter Start!\n");
i=0;
while( i <= 20 && CheckLoopInner == 1) {
    //printf("CheckLoopInner Start!\n");
if(*(FileContent+i) != CharToSearchFor[i]){
    CheckLoopInner = 0;
    }
    //printf("CheckLoopInner End! I is: %d\n", i);
    i++;
}
if(CheckLoopInner == 1)
{
CheckLoopOuter == 0;
}
CheckLoopInner = 1;
CurrentOffset++;
FileContent++;
//printf("CheckLoopOuter End! CurrentContent:%c\n", *FileContent);
}
//boogaloooga;

if(CheckLoopOuter == 0)
{
printf("String Found!\n");
}
if(CheckLoopOuter == 1  ){
printf("String Not Found!\n");
}
fs_close(CharMoveInfo);

return(1);
//}



}
