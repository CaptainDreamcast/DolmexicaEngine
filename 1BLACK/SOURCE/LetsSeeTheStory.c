uint8 LetsSeeTheStory(char FileDir[]){

StoryBoardHeaderStruct HeaderBuffer;
StoryBoardTextureStruct TextureData[StoryBoardMaximumTextureAmount];
StoryBoardTextStruct TextData[StoryBoardMaximumTextAmount];
StoryBoardSoundEffectStruct SoundEffectData[StoryBoardMaximumSoundEffectAmount];

pvr_ptr_t Texture[StoryBoardMaximumTextureAmount];

sfxhnd_t SoundEffect[StoryBoardMaximumSoundEffectAmount];

file_t StoryBoardFile;

maple_device_t *cont;
cont_state_t *st;

int DirtyDeedsDoneDirtCheap;

int TextureActive[StoryBoardMaximumTextureAmount];
int TextureTicks[StoryBoardMaximumTextureAmount];

int TextActive[StoryBoardMaximumTextAmount];
int TextTicks[StoryBoardMaximumTextAmount];
int CurrentTextPosition[StoryBoardMaximumTextAmount];
char DrawnText[StoryBoardMaximumTextAmount][StoryBoardMaximumTextSize];

int SoundEffectActive[StoryBoardMaximumSoundEffectAmount];
int SoundEffectLoaded[StoryBoardMaximumSoundEffectAmount];

int HeaderTicks;
int ActionAmount;

uint32 CurrentOffset;

uint8 ButtonInputAllowed[MaxCharsOnScreen];
uint8 OffTo;

int ReadyToRock;

for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<StoryBoardMaximumTextureAmount; DirtyDeedsDoneDirtCheap++){
TextureActive[DirtyDeedsDoneDirtCheap] = 0;
TextureTicks[DirtyDeedsDoneDirtCheap] = 0;
Texture[DirtyDeedsDoneDirtCheap] = pvr_mem_malloc(512*512*2);
}

for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<StoryBoardMaximumTextAmount; DirtyDeedsDoneDirtCheap++){
TextActive[DirtyDeedsDoneDirtCheap] = 0;
TextTicks[DirtyDeedsDoneDirtCheap] = 0;
CurrentTextPosition[DirtyDeedsDoneDirtCheap] = 0;
}

for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<StoryBoardMaximumSoundEffectAmount; DirtyDeedsDoneDirtCheap++){
SoundEffectActive[DirtyDeedsDoneDirtCheap] = 0;
SoundEffectLoaded[DirtyDeedsDoneDirtCheap] = 0;
}

for(DirtyDeedsDoneDirtCheap=CharacterOne; DirtyDeedsDoneDirtCheap<MaxCharsOnScreen; DirtyDeedsDoneDirtCheap++) ButtonInputAllowed[DirtyDeedsDoneDirtCheap] = 0;

HeaderTicks = 1;
CurrentOffset = sizeof(StoryBoardUberHeaderStruct);

HeaderBuffer.WhichAction = 0;
HeaderBuffer.Duration = 1;
HeaderBuffer.WaitForButtonInput = 0;

ActionAmount = OpenStoryBoardAndFetchActionAmount(FileDir, &StoryBoardFile);

OffTo = 1;

ReadyToRock = 1;
while(ReadyToRock){

HeaderTicks++;
if(HeaderTicks >= HeaderBuffer.Duration){
HeaderBuffer.WhichAction++;
if(HeaderBuffer.WhichAction > ActionAmount) ReadyToRock = 0;
else ReadAllTheNewCoolStoryBoardStuff(&StoryBoardFile, &HeaderBuffer, TextureData, TextData, TextureActive, TextActive, TextureTicks, TextTicks, Texture, CurrentTextPosition, DrawnText, SoundEffectData, SoundEffectActive, SoundEffectLoaded, SoundEffect);
HeaderTicks = 0;
}

//DRAAAAAAAAWS

pvr_wait_ready();
pvr_scene_begin();
pvr_list_begin(PVR_LIST_TR_POLY);

for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<StoryBoardMaximumTextureAmount; DirtyDeedsDoneDirtCheap++){
if(TextureActive[DirtyDeedsDoneDirtCheap]) StoryBoardDrawTexture(Texture[DirtyDeedsDoneDirtCheap], TextureData[DirtyDeedsDoneDirtCheap]);
}

for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<StoryBoardMaximumTextAmount; DirtyDeedsDoneDirtCheap++){
if(TextActive[DirtyDeedsDoneDirtCheap]) StoryBoardDrawText(DrawnText[DirtyDeedsDoneDirtCheap], TextData[DirtyDeedsDoneDirtCheap]);
}

pvr_list_finish();
pvr_scene_finish();

//DRAAAAAAAAWS

//OTHER STUFF

for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<StoryBoardMaximumTextureAmount; DirtyDeedsDoneDirtCheap++){
if(TextureActive[DirtyDeedsDoneDirtCheap]){

if(TextureData[DirtyDeedsDoneDirtCheap].WhichFrame != 0){
TextureTicks[DirtyDeedsDoneDirtCheap]++;

if(TextureTicks[DirtyDeedsDoneDirtCheap] >= TextureData[DirtyDeedsDoneDirtCheap].Speed){
TextureData[DirtyDeedsDoneDirtCheap].WhichFrame++;
TextureTicks[DirtyDeedsDoneDirtCheap] = 0;

if(TextureData[DirtyDeedsDoneDirtCheap].WhichFrame > TextureData[DirtyDeedsDoneDirtCheap].FrameAmount){
if(TextureData[DirtyDeedsDoneDirtCheap].Loop){ 
TextureData[DirtyDeedsDoneDirtCheap].WhichFrame = 1;
StoryBoardLoadTexture(Texture[DirtyDeedsDoneDirtCheap], &TextureData[DirtyDeedsDoneDirtCheap]);
}
else TextureData[DirtyDeedsDoneDirtCheap].WhichFrame = TextureData[DirtyDeedsDoneDirtCheap].FrameAmount;
}
else StoryBoardLoadTexture(Texture[DirtyDeedsDoneDirtCheap], &TextureData[DirtyDeedsDoneDirtCheap]);

}
}

if(TextureData[DirtyDeedsDoneDirtCheap].MovementX != 0) TextureData[DirtyDeedsDoneDirtCheap].PositionX+=TextureData[DirtyDeedsDoneDirtCheap].MovementX;
if(TextureData[DirtyDeedsDoneDirtCheap].MovementY != 0) TextureData[DirtyDeedsDoneDirtCheap].PositionY+=TextureData[DirtyDeedsDoneDirtCheap].MovementY;

}

}
//TEXTURE STUFF OVER

for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<StoryBoardMaximumTextAmount; DirtyDeedsDoneDirtCheap++){
if(TextActive[DirtyDeedsDoneDirtCheap]){
if(TextData[DirtyDeedsDoneDirtCheap].BuildUp != 0){
TextTicks[DirtyDeedsDoneDirtCheap]++;

if(TextTicks[DirtyDeedsDoneDirtCheap] >= TextData[DirtyDeedsDoneDirtCheap].BuildUpSpeed){

CurrentTextPosition[DirtyDeedsDoneDirtCheap]++;
if(TextData[DirtyDeedsDoneDirtCheap].ActualText[CurrentTextPosition[DirtyDeedsDoneDirtCheap]] != '\0'){
DrawnText[DirtyDeedsDoneDirtCheap][CurrentTextPosition[DirtyDeedsDoneDirtCheap]] = TextData[DirtyDeedsDoneDirtCheap].ActualText[CurrentTextPosition[DirtyDeedsDoneDirtCheap]];
DrawnText[DirtyDeedsDoneDirtCheap][CurrentTextPosition[DirtyDeedsDoneDirtCheap]+1] = '\0';
TextTicks[DirtyDeedsDoneDirtCheap]=0;

//printf("\n");
//printf("Added a character\n");
//printf("ActualText: (%s)\n", TextData[DirtyDeedsDoneDirtCheap].ActualText);
//printf("DrawnText: (%s)\n", DrawnText[DirtyDeedsDoneDirtCheap]);

}
else TextData[DirtyDeedsDoneDirtCheap].BuildUp = 0;
}

}
}
}

for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<StoryBoardMaximumSoundEffectAmount; DirtyDeedsDoneDirtCheap++){
if(SoundEffectActive[DirtyDeedsDoneDirtCheap] && HeaderTicks >= SoundEffectData[DirtyDeedsDoneDirtCheap].SoundEffectPlayTime){
snd_sfx_play(SoundEffect[DirtyDeedsDoneDirtCheap], VolumeSFX, 128);
SoundEffectActive[DirtyDeedsDoneDirtCheap] = 0;
}
}

//OTHER STUFF

//INPUT

for(DirtyDeedsDoneDirtCheap=CharacterOne; DirtyDeedsDoneDirtCheap<MaxCharsOnScreen; DirtyDeedsDoneDirtCheap++){

  if((cont = maple_enum_dev(DirtyDeedsDoneDirtCheap, 0)) != NULL) {

  st = (cont_state_t *)maple_dev_status(cont);


  if ((st->buttons & CONT_START) && ButtonInputAllowed[DirtyDeedsDoneDirtCheap] == 1){
  ReadyToRock = 0;
  ButtonInputAllowed[DirtyDeedsDoneDirtCheap] = 0;
  }

  if ((st->buttons & CONT_A) && ButtonInputAllowed[DirtyDeedsDoneDirtCheap] == 1){
  HeaderTicks = HeaderBuffer.Duration;
  ButtonInputAllowed[DirtyDeedsDoneDirtCheap] = 0;
  }

  if ((st->buttons == 0) && ButtonInputAllowed[DirtyDeedsDoneDirtCheap] == 0) {
   ButtonInputAllowed[DirtyDeedsDoneDirtCheap] = 1;
  }

  if ((st->buttons & (StairWayToHeaven)) == (StairWayToHeaven)) {
   OffTo = StairWayToHeavenIdentifier;
   ReadyToRock = 0;
  }

 }

}

//INPUT


}

CloseStoryBoardAndCleanUp(&StoryBoardFile);
for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<StoryBoardMaximumTextureAmount; DirtyDeedsDoneDirtCheap++) pvr_mem_free(Texture[DirtyDeedsDoneDirtCheap]);
for(DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<StoryBoardMaximumSoundEffectAmount; DirtyDeedsDoneDirtCheap++) {
if(SoundEffectLoaded[DirtyDeedsDoneDirtCheap]) snd_sfx_unload(SoundEffect[DirtyDeedsDoneDirtCheap]);
}
return(OffTo);
}