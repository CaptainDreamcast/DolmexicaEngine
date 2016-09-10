typedef struct{

uint8 PaletteInUse;
char WhichCharPaletteUsed;
char WhichBufferPaletteUsed;
uint8 Separator1[13]; //16

uint8 ReservedSpace[16];
} PaletteData;

typedef struct{

uint16 ScreenPositionX;
uint16 ScreenPositionY;
uint16 SizeX;
uint16 SizeY;
int TextureSizeX;
int TextureSizeY;

uint8 ReservedSpace[16];

} WhoAgainstWhoTextureDataStruct;

typedef struct{

uint16 ScreenPositionX;
uint16 ScreenPositionY;
uint16 SizeX;
uint16 SizeY;
int TextureSizeX;
int TextureSizeY;

uint8 ReservedSpace[16];

} ShowWayToGoTextureDataStruct;

typedef struct{

uint16 SizeX; 
uint16 SizeY; 

short PositionDifferenceX; 
short PositionDifferenceY; 

short DesiredFinalPositionX;
short DesiredFinalPositionY;

uint8 Separator1[4]; //16

short PositionX[MaxArcadeLength];
short PositionY[MaxArcadeLength]; //48

uint8 ReservedSpace[16]; //64

} ShowWayToGoEnemyDataStruct;

typedef struct{

uint16 BigPortraitScreenPositionX;
uint16 BigPortraitScreenPositionY;
uint16 BigPortraitSizeX;
uint16 BigPortraitSizeY;

uint16 NameScreenPositionX;
uint16 NameScreenPositionY;
uint16 NameSizeX;
uint16 NameSizeY; //16

uint8 ReservedSpace[16];

} FighterSelectHeaderStruct;

typedef struct{
uint8 ThisBonusIsScrolling;
uint8 PositionLeft;
uint8 Separator1[2];

uint16 ScreenPositionX;
uint16 ScreenPositionY;

uint16 SizeX;
uint16 SizeY;

uint16 TextureSizeX;
uint16 TextureSizeY; //16

uint8 ReservedSpace[16];

} FighterSelectSpecialStruct;

typedef struct{

uint8 Separator1[4];

char CharacterName[8]; //12

uint16 CharGoUp;
uint16 CharGoDown;
uint16 CharGoLeft;
uint16 CharGoRight; //20

uint16 PositionX;
uint16 PositionY;
uint16 SizeX;
uint16 SizeY; //28

uint8 Separator2[4]; //32

char BackGroundName[8];

int TextureSizeX;
int TextureSizeY; //48

uint8 ReservedSpace[16];

} FighterSelectSmallPortraitStruct;

typedef struct{
char ArrayToBePrinted[100];
int PositionX;
int PositionY;
int FontSize;
} LargerArrayStruct;

typedef struct{
char ArrayToBePrinted[17];
int PositionX;
int PositionY;
int FontSize;
} FightMenuPointStruct;

typedef struct{
int PositionX;
int PositionY;
int SizeX;
int SizeY;
} FightMenuBoxStruct;

typedef struct{
uint16 OriginalTextureSize;
uint16 CharacterOffset;

uint16 CharacterWidth;
uint16 CharacterHeight;

uint8 Separator1[4];

uint16 CharacterSpeed;
uint16 JumpIdleUpStrength; //16

uint16 CharacterDefense;
uint8 JumpIdleUpFlags;
uint8 JumpForwardFlags;

uint8 JumpBackFlags;
uint8 BackBlocking;
uint8 PaletteInUse;
uint8 Separator2;

uint16 JumpForwardSpeed;
uint16 JumpForwardStrength;

uint16 JumpBackSpeed;
uint16 JumpBackStrength; //32

char RealCharName[16]; //48

char ReservedSpace[16];

} CharacterBaseValuesStruct;

typedef struct{
uint16 HitEffectID;
uint8 Separator[2];
uint8 HitEffectName[8];
uint8 HitEffectFrameAmount;
uint8 HitEffectSpeed;
uint8 Separator1[2]; //16

uint8 ReservedSpace[16]; 
} LoadHitEffectStruct;

typedef struct{
uint16 HitEffectSizeX;
uint16 HitEffectSizeY;
uint16 HitEffectTextureSizeX;
uint16 HitEffectTextureSizeY;

uint8 Separator1[8]; //16

uint8 ReservedSpace[16]; 
} UseHitEffectStruct;

typedef struct{
uint8 PositionID;
uint8 WhichAttackID;
uint8 AvailabilityCheck;
uint8 Separator1;
char AnimationNameBuffer[8]; // or uint8
uint8 FrameAmount;
uint8 AnimationSpeed;
uint8 AnimationType;
uint8 AnimationLoop;
uint8 EnemyAccelerationX;
uint8 EnemyAccelerationY;
uint16 AnimationStrength;
uint16 RangeX;
uint16 RangeY;
uint8 WhichMissSoundEffect;
uint8 WhichSoundEffectFrame;
uint8 WhichHitSoundEffect;
uint8 WhichSpecial;

uint8 AnimationAddOn;
uint8 Separator2;

uint16 SpecialNeeded; //32

uint8 ReservedSpace[16]; 
} NormalAttackStruct;

typedef struct{
uint8 ThrowIdentifier;
uint8 WhichSpecial;
char AnimationName[8]; // or uint8
uint8 FrameAmount;
uint8 Separator1;
uint32 SpecialOffset;
uint8 Separator2[16]; 

uint8 ReservedSpace[16]; 
} ThrowHeaderStruct;

typedef struct __attribute__((packed)){
uint8 ThrowIdentifier; 
uint8 ThrowStage; 
uint8 EnemyAlignment; 
uint8 AnimationSpeed; 
uint8 Minus1;
uint16 CharPositionChangeX;
uint8 Minus2;
uint16 CharPositionChangeY;
uint8 Minus3;
uint16 EnemyPositionChangeX;
uint8 Minus4;
uint16 EnemyPositionChangeY; //16
uint8 MinusEnemyAccelerationX; 
uint8 EnemyAccelerationX; 
uint8 MinusEnemyAccelerationY; 
uint8 EnemyAccelerationY; 
uint16 AnimationStrength; 
uint8 Separator1[10]; //32

uint8 ReservedSpace[16]; 

} ThrowAttackStruct;

typedef struct{
uint8 CoolnessIdentifier;
uint8 WhichSpecial;
char AnimationName[8]; // or uint8
uint8 FrameAmount;
uint8 Separator1;
uint32 SpecialOffset;
uint8 Separator2[16];

uint8 ReservedSpace[16]; 

} CoolerAttackHeaderStruct;

typedef struct __attribute__((packed)){
uint8 CoolnessIdentifier; 
uint8 WhichCoolerAttack; 
uint8 EnemyAlignment; 
uint8 AnimationSpeed; 
uint8 Minus1;
uint16 CharPositionChangeX;
uint8 Minus2;
uint16 CharPositionChangeY;
uint8 Minus3;
uint16 CharComboMovementX;
uint8 Minus4;
uint16 CharComboMovementY;
uint8 MinusEnemyAccelerationX; 
uint8 EnemyAccelerationX; 
uint8 MinusEnemyAccelerationY; 
uint8 EnemyAccelerationY; 
uint16 AnimationStrength; 
uint8 Separator1[10];

uint8 ReservedSpace[16]; 

} CoolerAttackStruct;

typedef struct __attribute__((packed)){
uint8 SpecialEffectIdentifier;
uint8 WhichSpecial;

uint32 SpecialOffset;

uint16 SpecialEffectSizeX;
uint16 SpecialEffectSizeY;

uint8 SpecialEffectPosCharRelativity;
uint8 Minus1;
uint16 SpecialEffectPosX;

uint8 Minus2;
uint16 SpecialEffectPosY;
uint8 SpecialEffectWhichFrame;

uint16 SpecialEffectRange;
uint8 Minus3;

uint16 SpecialEffectSpeedX;
uint8 Minus4;
uint16 SpecialEffectSpeedY;

uint8 SpecialEffectSideEffect;

uint16 SpecialEffectSideEffectDuration;

uint8 HitSoundEffect;

uint8 Separator1[2]; 


uint16 SpecialEffectCollisionOffsetX;
uint16 SpecialEffectCollisionOffsetY;
uint8 Separator2[12];


uint8 ReservedSpace[16]; 

} SpecialEffectHeaderStruct;


typedef struct{
uint8 SpecialEffectIdentifier;
uint8 WhichSpecial;
char SpecialEffectNameBuffer[8]; // or uint8

uint8 SpecialEffectAnimationSpeed;
uint8 SpecialEffectFrameAmount;

uint8 Separator2[4];

uint8 ReservedSpace[16]; 

} SpecialEffectStruct;

typedef struct __attribute__((packed)){
uint8 ComboIdentifier;
uint8 ComboID;
uint8 Separator1[2];
char AnimationNameBuffer[8]; // or uint8
uint8 FrameAmount;
uint8 AnimationSpeed;
uint8 AnimationType;
uint8 AnimationLoop;
uint8 EnemyAccelerationX;
uint8 EnemyAccelerationY;
uint16 AnimationStrength;
uint16 WhichSpecial;
uint8 Minus1;
uint16 CharPositionChangeX;
uint8 Minus2;
uint16 CharPositionChangeY;

uint8 WhichMissSoundEffect;
uint8 WhichSoundEffectFrame;
uint8 WhichHitSoundEffect;
uint8 Separator2;

uint8 ReservedSpace[16]; 
} ComboAttackStruct;

typedef struct{
uint8 OmniIdentifier;
uint8 WhichSpecial;
uint8 ActionAmount;
uint8 Separator1;
uint32 SpecialOffset;

uint8 Separator2[8];

uint8 ReservedSpace[16]; 
} OmniHeaderStruct;

typedef struct __attribute__((packed)){
uint8 OmniIdentifier; 
uint8 WhichAction; 
uint8 EnemyAlignment; 
uint8 NewCharacterAnimation;

char CharacterAnimationName[8]; // or uint8

uint8 CharacterFrameAmount;
uint8 CharacterAnimationSpeed;
uint8 CharacterWhichFrame;
uint8 NewSpecialEffectAnimation;

char SpecialEffectAnimationName[8]; // or uint8

uint8 SpecialEffectAnimationSpeed;
uint8 SpecialEffectFrameAmount;
uint8 SpecialEffectWhichFrame;

uint16 SpecialEffectSizeX;
uint16 SpecialEffectSizeY;

uint8 SpecialEffectPosCharRelativity;
uint8 MinusSpecialEffectPosX;
uint16 SpecialEffectPosX;

uint8 MinusSpecialEffectPosY;
uint16 SpecialEffectPosY;

uint16 SpecialEffectRange;

uint8 MinusSpecialEffectSpeedX;
uint16 SpecialEffectSpeedX;
uint8 MinusSpecialEffectSpeedY;
uint16 SpecialEffectSpeedY;
 
uint8 MinusCharPositionChangeX;
uint16 CharPositionChangeX;
uint8 MinusCharPositionChangeY;
uint16 CharPositionChangeY;

uint8 MinusEnemyPositionChangeX;
uint16 EnemyPositionChangeX;
uint8 MinusEnemyPositionChangeY;
uint16 EnemyPositionChangeY;

uint8 MinusCharComboMovementX;
uint16 CharComboMovementX;
uint8 MinusCharComboMovementY;
uint16 CharComboMovementY;

uint8 MinusEnemyComboMovementX;
uint16 EnemyComboMovementX;
uint8 MinusEnemyComboMovementY;
uint16 EnemyComboMovementY;

uint8 PosCharRelativity;

uint8 MinusCharPositionFixedX;
uint16 CharPositionFixedX;
uint8 MinusCharPositionFixedY;
uint16 CharPositionFixedY;

uint8 PosEnemyRelativity; 

uint8 MinusEnemyPositionFixedX;
uint16 EnemyPositionFixedX;
uint8 MinusEnemyPositionFixedY;
uint16 EnemyPositionFixedY; 

uint8 MinusEnemyAccelerationX; 
uint8 EnemyAccelerationX; 
uint8 MinusEnemyAccelerationY; 
uint8 EnemyAccelerationY; 

uint16 AnimationStrength; 
uint16 ActionDuration; 

uint8 Separator1[4]; 

uint8 ReservedSpace[16]; 

} OmniAttackStruct;

typedef struct __attribute__((packed)){

uint16 ActionAmount;
uint8 Separator1[14]; //16

uint8 ReservedSpace[16]; 
} StoryBoardUberHeaderStruct;

typedef struct __attribute__((packed)){

uint8 WhichAction;
uint8 WaitForButtonInput;
uint8 SoundTrack;
uint8 Separator1;

uint16 Duration;
uint8 Separator2[2];

uint8 TextureStructAmount;
uint8 TextStructAmount;
uint8 SoundEffectStructAmount;
uint8 Separator3;

uint8 Separator4[4]; //16

uint8 ReservedSpace[16]; 

} StoryBoardHeaderStruct;


typedef struct __attribute__((packed)){

uint8 TextureID;
uint8 TextureAction;
uint8 TextureNameID;
uint8 Separator1;

uint8 WhichFrame;
uint8 FrameAmount;
uint8 Speed;
uint8 Loop;

uint16 PositionX;
uint16 PositionY;

uint16 SizeX;
uint16 SizeY; //16

float TexturePositionX1;
float TexturePositionY1;
float TexturePositionX2;
float TexturePositionY2; //32

short MovementX;
short MovementY;

uint16 PositionZ;
uint8 Separator2[2];

int TextureSizeX;
int TextureSizeY; //48

uint8 ReservedSpace[16]; 

} StoryBoardTextureStruct;

typedef struct __attribute__((packed)){

uint8 TextID;
uint8 TextAction;
uint8 BuildUp;
uint8 BuildUpSpeed;

uint16 PositionX;
uint16 PositionY;

uint16 SizeX;
uint16 SizeY;

uint16 FontSizeX;
uint16 FontSizeY; //16

uint8 WhichFont;
uint8 Length;
uint16 Duration;

uint16 PositionZ;
uint8 BreakSizeX;
uint8 BreakSizeY;

uint8 FontColor;
uint8 Separator1[7]; //32

uint8 ReservedSpace[16]; 

char ActualText[StoryBoardMaximumTextSize];

} StoryBoardTextStruct;

typedef struct __attribute__((packed)){

uint8 SoundEffectID;
uint8 SoundEffectAction;
uint8 SoundEffectNameID;
uint8 Separator1;

uint16 SoundEffectPlayTime;


uint8 Separator2[10];

uint8 ReservedSpace[16]; 

} StoryBoardSoundEffectStruct;


typedef struct __attribute__((packed)){

uint16 FightAmount;
uint8 Separator1[14];
uint8 ReservedSpace[16]; 

} StoryModeHeaderStruct;

typedef struct {

uint8 WhichFont;
uint8 Separator1[3];

int TextureSizeX;
int TextureSizeY;

} FontHeaderStruct;

typedef struct {

float FilePositionX1;
float FilePositionY1;
float FilePositionX2;
float FilePositionY2;

} FontSingleCharacterStruct;

typedef struct{

uint16 LifeBarScreenPositionX;
uint16 LifeBarScreenPositionY;

uint16 LifeBarSizeX;
uint16 LifeBarSizeY;

uint16 VictoryScreenPositionX;
uint16 VictoryScreenPositionY;

uint16 VictorySizeX;
uint16 VictorySizeY; //16


uint16 LifeStartPositionX;
uint16 LifeStartPositionY;

short LifeFullSizeX;
short LifeFullSizeY;

uint8 FirstColor;
uint8 SecondColor;
uint8 ThirdColor;
uint8 Separator1;

uint16 FirstColorChange;
uint16 SecondColorChange; //32


uint16 SpecialStartPositionX;
uint16 SpecialStartPositionY;

uint16 SpecialFullSizeX;
uint16 SpecialFullSizeY;

uint8 FirstSpecialColor;
uint8 SecondSpecialColor;
uint8 ThirdSpecialColor;
uint8 Separator2;

uint16 FirstSpecialColorChange;
uint16 SecondSpecialColorChange; //48


int VictoryTextureSizeX;
int VictoryTextureSizeY;
int LifeBarTextureSizeX;
int LifeBarTextureSizeY; //64

uint8 ReservedSpace[16]; 

} SingleLifeBarStruct;

typedef struct{

uint16 PositionX[2];
uint16 PositionY[2];

uint16 SizeX[2];
uint16 SizeY[2]; //16


int TextureSizeX;
int TextureSizeY;
 
char Separator1[8]; //32

uint8 ReservedSpace[16]; 
} TimerStruct;

typedef struct{

uint8 WhichNameAlignmentType;
uint8 Separator1[3];

uint16 NamePositionX;
uint16 NamePositionY;

uint16 NameSizeX;
uint16 NameSizeY;

uint8 Separator2[4]; //16

uint8 WhichArrayAlignmentType;
uint8 Separator3[3];

uint16 ArrayPositionX;
uint16 ArrayPositionY;

uint16 ArraySizeX;
uint16 ArraySizeY;

uint8 Separator4[4]; //32

uint8 ReservedSpace[16]; 

} OtherGuiStruct;

typedef struct{

uint8  WhichBackGround;
uint8  BackGroundActive;
uint8  BackGroundAnimated;
uint8  Separator1;

uint8 Separator2[4];

int TextureSizeX;
int TextureSizeY; //16


uint16 PositionX;
uint16 PositionY;

uint16 SizeX;
uint16 SizeY;

uint16 PositionZ;
uint16 LayerSizeX;

uint8 Separator3[4]; //32

uint8 ReservedSpace[16]; 

} BackGroundStruct;

typedef struct{

char Magic[8];
char Version[8]; //16

uint8 BackGroundAmount;
uint8 BackGroundSoundTrack;
uint16 RealStageSize;

uint16 StartPositionX[MaxCharsOnScreen];
uint16 StageGround;
uint16 StartLeftStageBorder;

short ShadowPositionX;
short ShadowPositionY; //32

uint8 TextureType;
uint8 CharacterStretchFactor;
uint8 Separator1[2]; 

uint16 ScrollSpeedX;
uint16 ScrollSpeedY;

uint16 ScrollingLeftPositionX;
uint16 ScrollingRightPositionX;

uint8 Separator2[4];//48

uint8 ReservedSpace[16]; 

} BackGroundHeaderStruct;

typedef struct{

uint8 Speed;
uint8 FrameAmount;
uint8 WhichFrame;
uint8 Loop;

short MovementX;
short MovementY;

short MovementBorderX;
short MovementBorderY;

uint8 Tingle;
uint8 Separator1[3]; //16

uint8 Ticks;
uint8 SpecialPauseFrame; // DERP?
uint8 SpecialPauseDuration; // DERP DERP?
uint8 Separator2;

uint8 Separator3[12]; //32

uint8 ReservedSpace[16]; 

} BackGroundInnerAnimationStruct;

typedef struct{

uint8 LineActive;

short PositionX;
short PositionY;

char* Text;

} CreditSingleLineStruct;

typedef struct{

uint8 FinalLine;
uint8 ScrollSpeedY;
uint16 FreeSpaceY;

uint16 LineStartPositionX;
uint16 LineStartPositionY;

uint16 SizeX;
uint16 SizeY;

uint8 Separator1[4];

uint8 ReservedSpace[16]; 

} CreditHeaderStruct;

typedef struct{

uint16 ScreenReloadDuration;
uint16 PressStartDuration;

uint16 PressStartPositionX;
uint16 PressStartPositionY;

uint16 PressStartSizeX;
uint16 PressStartSizeY;

char Separator1[4]; //16

uint8 ReservedSpace[16]; 

} TitleScreenStruct;

typedef struct{

uint16 PositionX;
uint16 PositionY;

} InnerModeMenuStruct;

typedef struct{

uint16 AfterInputDuration;
uint8 Separator1[14];

InnerModeMenuStruct SingleMode[4];

uint8 ReservedSpace[16]; 

} ModeMenuStruct;

typedef struct{

uint8 WhichAction;
uint8 Separator1[1];
uint16 VoiceClipChecker;

uint16 SizeX;
uint16 SizeY;

uint16 PositionX;
uint16 PositionY;

uint8 FrameID;
uint8 Speed;
uint8 EndIt;
uint8 Separator2; //16

int TextureSizeX;
int TextureSizeY; 

uint8 Separator3[8]; //32

uint8 ReservedSpace[16];

} FightAnimationStruct;

typedef struct{

char Magic[8];
char Version[8];

uint16 SoundEffectAmount;

uint8 Separator2[14]; //32

uint8 ReservedSpace[16];

} FightAnimationHeaderStruct;


typedef struct{

uint32 QuoteOffset;

uint16 QuoteLength;
uint16 FontSize;

int TextureSizeX;
int TextureSizeY; //16

uint16 PortraitPositionX;
uint16 PortraitPositionY;

uint16 PortraitSizeX;
uint16 PortraitSizeY;

uint16 QuotePositionX;
uint16 QuotePositionY;

uint16 QuoteSizeX;
uint16 QuoteSizeY; //32

uint16 Duration;
uint16 BreakSizeY;
uint8 Separator1[12]; //48

uint8 ReservedSpace[16];

} WinQuoteStruct;


typedef struct{

uint16 PositionX;
uint16 PositionY;

uint16 SizeX;
uint16 SizeY;

int TextureSizeX;
int TextureSizeY; //16

uint16 Duration;
uint8 Separator1[14]; //32

uint8 ReservedSpace[16]; 

} WinningAnimationStruct;





