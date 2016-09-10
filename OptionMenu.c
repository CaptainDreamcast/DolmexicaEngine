

uint8 LoadOptionMenu(OptionMenuStruct* OptionMenuData){

file_t InputFile;
char FileDir[NormalFileDirSize];
char MountPoint[NormalMountPointSize];
uint8 DirtyDeedsDoneDirtCheap;

sprintf(FileDir, "%s/MENU/OPTIONMENU.ogg", FileSystemUsed);
SoundLoad(FileDir);

sprintf(FileDir, "%s/MENU/OPTIONMENU.img", FileSystemUsed);
if(!FileExists(FileDir)) return(0);

sprintf(MountPoint, "/MENU");
FileDirToRomDisk(FileDir, MountPoint);

sprintf(FileDir, "%s/OPTIONMENU.hdr", MountPoint);
InputFile = FileOpen(FileDir, O_RDONLY);

FileRead(InputFile, &OptionMenuData->OptionMenuHeaderData, sizeof(OptionMenuHeaderStruct));
for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<OptionMenuOptionAmount*2; DirtyDeedsDoneDirtCheap++) FileRead(InputFile, &OptionMenuData->SingleOptionMenuData[DirtyDeedsDoneDirtCheap], sizeof(SingleOptionMenuStruct));

FileClose(InputFile);
fs_romdisk_unmount(MountPoint);

sprintf(FileDir, "%s/MENU/OPTIONMENU.ogg", FileSystemUsed);
SoundPlay(FileDir, -1);

return(1);
}

int OptionMenu(int* WhichPlayerActive, ModifiableOptionStruct* ModifiableOptionData){

maple_device_t *cont;
cont_state_t *st;

OptionMenuStruct OptionMenuData;
uint8 ReadyToRock, ReturnValue, DrawIntro, DirtyDeedsDoneDirtCheap, PressingTicks, SelectedOption;
uint8 ButtonInputAllowed[ButtonAmount];

int SuperCoolIntroTicks, SuperCoolOutroTicks;


if(!(ReadyToRock = LoadOptionMenu(&OptionMenuData))) ReturnValue = GameStageMusicMode;
else ReturnValue = GameStageModeMenu;

sprintf(OptionMenuData.SingleOptionMenuData[OptionMenuOptionAmount+OptionMenuDifficultyOption].Array, "%d%c/100%c", ModifiableOptionData->Difficulty, '%', '%');
if(ModifiableOptionData->FirstTimerStartValue == 10) sprintf(OptionMenuData.SingleOptionMenuData[OptionMenuOptionAmount+OptionMenuTimerOption].Array, "INFINITE");
else if(ModifiableOptionData->FirstTimerStartValue == 0 && ModifiableOptionData->SecondTimerStartValue == 1) sprintf(OptionMenuData.SingleOptionMenuData[OptionMenuOptionAmount+OptionMenuTimerOption].Array, "%d%d SECOND", ModifiableOptionData->FirstTimerStartValue, ModifiableOptionData->SecondTimerStartValue);
else sprintf(OptionMenuData.SingleOptionMenuData[OptionMenuOptionAmount+OptionMenuTimerOption].Array, "%d%d SECONDS", ModifiableOptionData->FirstTimerStartValue, ModifiableOptionData->SecondTimerStartValue);
OptionMenuData.SingleOptionMenuData[OptionMenuOptionAmount+OptionMenuSoundOption].Array[0] = '\0';
OptionMenuData.SingleOptionMenuData[OptionMenuOptionAmount+OptionMenuReturnOption].Array[0] = '\0';

for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<ButtonAmount; DirtyDeedsDoneDirtCheap++) ButtonInputAllowed[DirtyDeedsDoneDirtCheap] = 0;
SuperCoolIntroTicks = SuperCoolOutroTicks = 0;
PressingTicks = OptionMenuData.OptionMenuHeaderData.HoldingSpeedThreshold;
SelectedOption = 0;
DrawIntro = 1;

while(ReadyToRock){

pvr_wait_ready();
pvr_scene_begin();
pvr_list_begin(PVR_LIST_TR_POLY);

DrawColorBackGround(OptionMenuData.OptionMenuHeaderData.BackGroundColor);
DrawArray(OptionMenuData.OptionMenuHeaderData.TitleArray, OptionMenuData.OptionMenuHeaderData.TitlePositionX, OptionMenuData.OptionMenuHeaderData.TitlePositionY, OptionMenuData.OptionMenuHeaderData.TitlePositionZ, OptionMenuData.OptionMenuHeaderData.TitleFontSize, OptionMenuData.OptionMenuHeaderData.NonSelectedOptionColor);
for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<OptionMenuOptionAmount*2; DirtyDeedsDoneDirtCheap++){
if(DirtyDeedsDoneDirtCheap%OptionMenuOptionAmount == SelectedOption) DrawArray(OptionMenuData.SingleOptionMenuData[DirtyDeedsDoneDirtCheap].Array, OptionMenuData.SingleOptionMenuData[DirtyDeedsDoneDirtCheap].PositionX, OptionMenuData.SingleOptionMenuData[DirtyDeedsDoneDirtCheap].PositionY, OptionMenuData.SingleOptionMenuData[DirtyDeedsDoneDirtCheap].PositionZ, OptionMenuData.SingleOptionMenuData[DirtyDeedsDoneDirtCheap].FontSize, OptionMenuData.OptionMenuHeaderData.SelectedOptionColor);
else DrawArray(OptionMenuData.SingleOptionMenuData[DirtyDeedsDoneDirtCheap].Array, OptionMenuData.SingleOptionMenuData[DirtyDeedsDoneDirtCheap].PositionX, OptionMenuData.SingleOptionMenuData[DirtyDeedsDoneDirtCheap].PositionY, OptionMenuData.SingleOptionMenuData[DirtyDeedsDoneDirtCheap].PositionZ, OptionMenuData.SingleOptionMenuData[DirtyDeedsDoneDirtCheap].FontSize, OptionMenuData.OptionMenuHeaderData.NonSelectedOptionColor);
}

if(DrawIntro){ 
DrawIntro = DrawSuperCoolEffect(SuperCoolIntroTicks);
SuperCoolIntroTicks++;
}
if(ReadyToRock == FadeToBlackIdentifier){
if(FadeToBlack(SuperCoolOutroTicks)) ReadyToRock = 0;
SuperCoolOutroTicks++;
}

pvr_list_finish();
pvr_scene_finish();

if((cont = maple_enum_dev((*WhichPlayerActive), 0)) != NULL) {
st = (cont_state_t *)maple_dev_status(cont);

if((st->buttons & CONT_A) && ReadyToRock != FadeToBlackIdentifier && ButtonInputAllowed[ButtonA]){

if(SelectedOption == OptionMenuSoundOption){
ReturnValue = GameStageOptionMenu; //Tells The Sound Menu we're calling from this menu.
ReadyToRock = FadeToBlackIdentifier;
}
else if(SelectedOption == OptionMenuReturnOption){
ReturnValue = GameStageModeMenu;
ReadyToRock = FadeToBlackIdentifier;
}

ButtonInputAllowed[ButtonA] = 0;
}
if(!(st->buttons & CONT_A) && !ButtonInputAllowed[ButtonA]) ButtonInputAllowed[ButtonA] = 1;


if((st->buttons & CONT_B) && ReadyToRock != FadeToBlackIdentifier && ButtonInputAllowed[ButtonB]){

ReturnValue = GameStageModeMenu;
ReadyToRock = FadeToBlackIdentifier;
ButtonInputAllowed[ButtonB] = 0;

}
if(!(st->buttons & CONT_B) && !ButtonInputAllowed[ButtonB]) ButtonInputAllowed[ButtonB] = 1;


if((st->buttons & CONT_DPAD_DOWN) && ReadyToRock != FadeToBlackIdentifier && ButtonInputAllowed[ButtonDown]){
SelectedOption = (SelectedOption+1)%OptionMenuOptionAmount;
PressingTicks = 0;
ButtonInputAllowed[ButtonDown] = 0;
}
if(!(st->buttons & CONT_DPAD_DOWN) && !ButtonInputAllowed[ButtonDown]) ButtonInputAllowed[ButtonDown] = 1;


if((st->buttons & CONT_DPAD_UP) && ReadyToRock != FadeToBlackIdentifier && ButtonInputAllowed[ButtonUp]){
if(SelectedOption == 0) SelectedOption += OptionMenuOptionAmount;
SelectedOption--;
PressingTicks = 0;
ButtonInputAllowed[ButtonUp] = 0;
}
if(!(st->buttons & CONT_DPAD_UP) && !ButtonInputAllowed[ButtonUp]) ButtonInputAllowed[ButtonUp] = 1;


if((st->buttons & CONT_DPAD_LEFT) && ReadyToRock != FadeToBlackIdentifier && ButtonInputAllowed[ButtonLeft]){

if(SelectedOption == OptionMenuDifficultyOption){
PressingTicks++;
if(PressingTicks >= OptionMenuData.OptionMenuHeaderData.HoldingSpeedThreshold){
if(ModifiableOptionData->Difficulty > 0) ModifiableOptionData->Difficulty--;
sprintf(OptionMenuData.SingleOptionMenuData[OptionMenuOptionAmount+OptionMenuDifficultyOption].Array, "%d%c/100%c", ModifiableOptionData->Difficulty, '%', '%');
PressingTicks = 0;
}
}
else if(SelectedOption == OptionMenuTimerOption){

PressingTicks++;
if(PressingTicks >= OptionMenuData.OptionMenuHeaderData.HoldingSpeedThreshold){
if(ModifiableOptionData->FirstTimerStartValue == 10) ModifiableOptionData->FirstTimerStartValue = ModifiableOptionData->SecondTimerStartValue = 9;
else if(ModifiableOptionData->SecondTimerStartValue > 0) ModifiableOptionData->SecondTimerStartValue--;
else{
ModifiableOptionData->SecondTimerStartValue = 9;
if(ModifiableOptionData->FirstTimerStartValue > 0) ModifiableOptionData->FirstTimerStartValue--;
else ModifiableOptionData->FirstTimerStartValue = ModifiableOptionData->SecondTimerStartValue = 0;
}
if(ModifiableOptionData->FirstTimerStartValue == 0 && ModifiableOptionData->SecondTimerStartValue == 1) sprintf(OptionMenuData.SingleOptionMenuData[OptionMenuOptionAmount+OptionMenuTimerOption].Array, "%d%d SECOND", ModifiableOptionData->FirstTimerStartValue, ModifiableOptionData->SecondTimerStartValue);
else sprintf(OptionMenuData.SingleOptionMenuData[OptionMenuOptionAmount+OptionMenuTimerOption].Array, "%d%d SECONDS", ModifiableOptionData->FirstTimerStartValue, ModifiableOptionData->SecondTimerStartValue);
PressingTicks = 0;
}
}

}
if(!(st->buttons & CONT_DPAD_LEFT) && !ButtonInputAllowed[ButtonLeft]) ButtonInputAllowed[ButtonLeft] = 1;

if((st->buttons & CONT_DPAD_RIGHT) && ReadyToRock != FadeToBlackIdentifier && ButtonInputAllowed[ButtonRight]){

if(SelectedOption == OptionMenuDifficultyOption){
PressingTicks++;
if(PressingTicks >= OptionMenuData.OptionMenuHeaderData.HoldingSpeedThreshold){
if(ModifiableOptionData->Difficulty < MaximumDifficulty) ModifiableOptionData->Difficulty++;
sprintf(OptionMenuData.SingleOptionMenuData[OptionMenuOptionAmount+OptionMenuDifficultyOption].Array, "%d%c/100%c", ModifiableOptionData->Difficulty, '%', '%');
PressingTicks = 0;
}
}
else if(SelectedOption == OptionMenuTimerOption){

PressingTicks++;
if(PressingTicks >= OptionMenuData.OptionMenuHeaderData.HoldingSpeedThreshold){
if(ModifiableOptionData->SecondTimerStartValue < 9) ModifiableOptionData->SecondTimerStartValue++;
else{
ModifiableOptionData->SecondTimerStartValue = 0;
if(ModifiableOptionData->FirstTimerStartValue < 9) ModifiableOptionData->FirstTimerStartValue++;
else{ 
ModifiableOptionData->FirstTimerStartValue = 10;
ModifiableOptionData->SecondTimerStartValue = -1;
}
}

if(ModifiableOptionData->FirstTimerStartValue == 10) sprintf(OptionMenuData.SingleOptionMenuData[OptionMenuOptionAmount+OptionMenuTimerOption].Array, "INFINITE");
else if(ModifiableOptionData->FirstTimerStartValue == 0 && ModifiableOptionData->SecondTimerStartValue == 1) sprintf(OptionMenuData.SingleOptionMenuData[OptionMenuOptionAmount+OptionMenuTimerOption].Array, "%d%d SECOND", ModifiableOptionData->FirstTimerStartValue, ModifiableOptionData->SecondTimerStartValue);
else sprintf(OptionMenuData.SingleOptionMenuData[OptionMenuOptionAmount+OptionMenuTimerOption].Array, "%d%d SECONDS", ModifiableOptionData->FirstTimerStartValue, ModifiableOptionData->SecondTimerStartValue);

PressingTicks = 0;
}
}

}
if(!(st->buttons & CONT_DPAD_RIGHT) && !ButtonInputAllowed[ButtonRight]) ButtonInputAllowed[ButtonRight] = 1;
if(!(st->buttons & CONT_DPAD_RIGHT) && !(st->buttons & CONT_DPAD_LEFT) && PressingTicks != OptionMenuData.OptionMenuHeaderData.HoldingSpeedThreshold) PressingTicks = OptionMenuData.OptionMenuHeaderData.HoldingSpeedThreshold;

if((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)){
ReturnValue = GameStageTitleScreen;
ReadyToRock = 0;
}

}



}

SoundStop();
return(ReturnValue);
}