#define MaxCharsOnScreen 				2
#define CharacterOne 					0
#define CharacterTwo 					1
#define MaxCharsLoopValue 				1

#define BootMenuReturn					1
#define BootLoaderReturn				0

#define PalHertz					0
#define NtscHertz					1
#define HertzVariationAmount				2

#define HertzWarningArrayAmount				2

#define ScreenSizeX 					640
#define ScreenSizeY 					480

#define FileSystemAmount				4

#define XAxisIdentifier 				0
#define YAxisIdentifier 				1
#define AxisAmount 					2

#define FontCharacterAmount 				91
#define DefaultFontIdentifier 				1

#define ModeNotAvailableDuration	 		600

#define WhoAgainstWhoBigPortraitIdentifier 		0
#define WhoAgainstWhoNameIdentifier 			1
#define WhoAgainstWhoLogoIdentifier 			2
#define WhoAgainstWhoTextureAmount 			3

#define ShowWayToGoShowTheScreen 			0
#define ShowWayToGoFindTheEnemy 			1
#define ShowWayToGoReadyToReveal 			2
#define ShowWayToGoFlashyStuff 				3
#define ShowWayToGoOhMyGodItIsHim 			4
#define ShowWayToGoFinishIt 				5

#define MysteryOpponentTextureIdentifier 		0 
#define MysteryOppenentBigPortraitTextureIdentifier 	1

#define MysteryOpponentDataIdentifier 			0 
#define MysteryOpponentBigPortraitDataIdentifier 	1
#define ConnectionDataIdentifier 			2
#define ShowWayToGoAdditionalTextureDataAmount 		3

#define ConnectionConquered 				0
#define ConnectionNotConquered 				1

#define NoDrawDefeated 					0 
#define DrawDefeated 					1

#define ShowWayToGoEnemyDisplayDuration  		200

#define ShowWayToGoConnectionTextureAmount 		2
#define ShowWayToGoBonusTextureAmount 			2
#define ShowWayToGoAdditionalTextureAmount 		ShowWayToGoBonusTextureAmount+ShowWayToGoConnectionTextureAmount

#define MaxArcadeLength 				8

#define MaxHitEffectAmount 				10
#define MaxHitEffectFrames 				10

#define WhiteColor 					0
#define BlackColor 					1
#define RedColor 					2
#define GreenColor 					3
#define BlueColor 					4
#define YellowColor 					5

#define FightEntireReset 				-2
#define FightPreRoundReset 				-1
#define FightFadeInEffect 				1
#define FightIntroAnimation 				2
#define FightRoundAnimation 				3
#define FightFightAnimation 				4
#define FightActualFight 				5
#define FightMenu 					6
#define FightKnockOutEffect 				7 
#define FightPreKnockOutAnimation 			8
#define FightKnockOutAnimation 				9
#define FightVictoryPose 				10
#define FightCheckingStuff 				11
#define FightWinningAnimation 				12
#define FightShutDown 					13
#define FightWinQuote 					14
#define FightContinueAnimation 				15
#define FightFadeOutEffect 				16
#define FightPerfectAnimation 				17
#define FightLetsSeeWhatHappens 			18
#define FightPreContinueAnimation 			19
#define FightTimeOut 					20
#define FightSurvivalCalculateNextFight 		21
#define FightNewRivalAnimation 				22

#define GameStageIntro 					-1
#define GameStageTitleScreen 				1
#define GameStageModeMenu 				2
#define GameStageArcadeMode 				3
#define GameStageStoryMode 				4
#define GameStageSurvivalMode 				5
#define GameStageOptionMenu 				6
#define GameStageMusicMode 				7
#define GameStageDeath 					13

#define FighterSelectStage 				1
#define InbetweenStage 					2
#define WhoAgainstWhoStage 				3
#define ActualFightStage 				4
#define FirstTimeCharacterSelectedStage 		5
#define CreditStage 					11
#define GameOverStage 					12
#define FinalExitStage 					13

#define SurvivalModeBeatableEnemyArrayLength 		9

#define ArcadeModeIdentifier 				1
#define SurvivalModeIdentifier 				2
#define StoryModeIdentifier 				3

#define FightAnimationSoundEffectIdentifier		0
#define RoundAnimationSoundEffectIdentifier		1
#define PerfectAnimationSoundEffectIdentifier 		2
#define ContinueAnimationSoundEffectIdentifier 		3
#define NewRivalAnimationSoundEffectIdentifier 		4
#define SoundEffectIdentifierArraySize 			5

#define FightAnimationFlag				(1 << 0)
#define RoundAnimationFlag				(1 << 1)
#define PerfectAnimationFlag				(1 << 2)
#define ContinueAnimationFlag				(1 << 2)
#define NewRivalAnimationFlag				(1 << 2)

#define ShadowPositionZ 				6
#define LowerGuiPositionZ 				7
#define LifeBarPositionZ 				8
#define CharacterPositionZMin 				9
#define CharacterPositionZMax 				10
#define EffectPositionZ 				11
#define TransparencyPositionZ 				12
#define UpperGuiPositionZ1 				13
#define UpperGuiPositionZ2 				14
#define AboveAllPositionZ 				15

#define WarningTrack 					2
//#define TitleTrack 					3
#define ModeMenuTrack 					3
#define MusicMenuTrack 					4
#define FighterSelectTrack 				5
#define WhoAgainstWhoTrack 				6
#define FightTrack 					7

#define NormalFileDirSize 				50
#define NormalMountPointSize 				50

#define NoAllocateTextureMemory 			0
#define ReAllocateTextureMemory 			1
#define PreAllocateTextureMemory 			1

#define WinQuoteDuration 				1000 

#define CharHealthMax 					1000
#define SpecialBarValueMax 				1000

#define SpecialStartValue 				0

#define SpecialMultiplicationFactor 			5

#define DrawnNameAlignedLeft 				0
#define DrawnNameAlignedRight 				1

#define MaximumTimerLength 				2
#define TimerCharacterAmount 				11

#define PushBackFactor 					3

#define OverHeadAddOnIdentifier 			1
#define SweepAddOnIdentifier 				2
#define OmniAddOnIdentifier 				3

#define CharHitDeAccelerationSpeedGround 		2
#define CharHitDeAccelerationSpeedAir 			1

#define CreditLinesOnScreenMax 				100

#define NormalNameSize 					9
#define ActualNameSize 					8

#define BackGroundAmountMaxIdentifier 			5
#define BackGroundAnimationAmountMaxIdentifier 		10
#define BackGroundFrameAmountMax 			70

#define BackGroundNoDrawAnimated			0
#define BackGroundDrawAnimated				1

#define HexNumberValueOffset 				48

#define HeaderSizeSFX					0
#define HeaderSizeKMG					64

#define HeaderSizeHumanMVT 				0x90 
#define HeaderSizeComputerMVT 				HeaderSizeHumanMVT
#define HeaderSizeCharacterArchive			0x30 
#define UniversalHeaderSize 				0x30 
#define HeaderSizeHitEffects				0x20

#define UniversalHeaderMagicPosition			0x0
#define UniversalHeaderMagicSize			0x10
#define UniversalHeaderVersionPosition			0x10
#define UniversalHeaderVersionSize			0x10

#define SpecialAttackHeaderSize 			0x20 

#define NormalAttackRegisterSize 			sizeof(NormalAttackStruct)

#define HeaderOffsetSize		 		0x4

#define SpecialOffsetsPosition				0x60
#define SpecialOffsetsSize				0x30

#define NormalAttackOffsetPositionHuman 		0x60
#define ThrowAttackOffsetPositionHuman 			0x64
#define CoolerAttackOffsetPositionHuman 		0x68
#define SpecialEffectOffsetPositionHuman 		0x6C
#define ComboAttackOffsetPositionHuman 			0x70
#define OmniAttackOffsetPositionHuman 			0x74
#define OriginalTextureSizePositionHuman 		0x7E



#define AttackAmountPositionComputer 			0x30
#define OriginalTextureSizePositionComputer 		0x4E

#define StandardCompulsoryAttackAmountComputer		0x22

#define GroundHitCounter				0
#define CrouchHitCounter				1
#define AirHitCounter					2
#define GroundBeingHitCounter				3
#define CrouchBeingHitCounter				4
#define AirBeingHitCounter				5
#define ComputerCounterAmount				6

#define LowerCounterLimit				-3
#define UpperCounterLimit				3

#define DummyAnimationValue				1
#define PositionAmountValue				3
#define ButtonAmountValue				6
#define AttackVariationValue				10

#define SizeOfLongLong					64

#define MaxSoundEffectsSustainable 			100
#define InternalSoundEffects 				1
#define MaxSoundEffectsAllowed 				MaxSoundEffectsSustainable-InternalSoundEffects

#define AnimationIDOffsetSameStrengthButtons	 	2
#define AnimationIDOffsetDownDownForwardForward 	3
#define AnimationIDOffsetDownDownBackBack	 	4
#define AnimationIDOffsetForwardDownDownForward		5
#define AnimationIDOffsetHoldingForward			6
#define AnimationIDOffsetHoldingBack			7

#define CompulsoryJumpValue				19
#define JumpVariationAmount				5
#define JumpTypeAmount					3

#define StandardNormalAttackOffset  			HeaderSizeHumanMVT+(CompulsoryJumpValue+(JumpVariationAmount*JumpTypeAmount))*sizeof(NormalAttackStruct)
#define StandardThrowAttackOffset  			StandardNormalAttackOffset+(PositionAmountValue*(ButtonAmountValue*AttackVariationValue+DummyAnimationValue)*sizeof(NormalAttackStruct))

#define JumpRecoveryExists				1
#define JumpPeakExists					8
#define JumpStageLoopsToFour				4
#define JumpPeakUnLoopsToFour				2

#define JumpIdleUpExists				128
#define JumpIdleUpUnLoopsToFour				64
#define JumpIdleUpUnLoopsToThree			32
#define JumpIdleUpLoopsToThree				16

#define SoundEffectNameLength				8

#define MoveAmount 					61

#define IdleExistenceIdentifier				1
#define NoIdeaWhatItsForIdentifier			2
#define NormalAttackAnimationIdentifier			3
#define GettingHitIdentifier				4
#define RecoveryIdentifier				5
#define ThrowAttackIdentifier				5 // See the problem?
#define CoolerAttackIdentifier				6
#define SpecialEffectAnimationIdentifier		7
#define ComboAttackAnimationIdentifier			8
#define OmniAttackAnimationIdentifier			9

#define SpecialEffectStageAmount			4

#define SpecialEffectStagePreLoop			1
#define SpecialEffectStageLoop				2
#define SpecialEffectStageVanish			3
#define SpecialEffectStageHit				4
#define SpecialEffectStageOutOfBounds			5

#define CharacterIsNormal				0
#define CharacterIsBurning				1
#define CharacterIsFrozen				2
#define CharacterIsProtected				3
#define CharacterIsGoingBerserk				OmniAttackAnimationIdentifier

#define MaxFightAnimationSoundEffect			3
#define FightAnimationSoundEffectAmountOffset		0x10
#define HeaderSizeRoundAnimationRegister		0x30
#define HeaderSizeFightAnimation			0x30

#define MoveBorderCrouchAntiIdleOffset			0x31
#define MoveBorderIdleAntiCrouchOffset			0x33
#define MoveBorderIdleStrongOffset			0x35
#define MoveBorderIdleAntiJumpOffset			0x37
#define MoveBorderJumpAntiGroundOffset			0x39
#define MoveBorderThrowOffset				0x3B
#define MoveBorderCoolerOffset				0x3D
#define MoveBorderUnidentifiedSpecialOffset		0x3F
#define MoveBorderSpecialEffectOffset			0x41
#define MoveBorderCrouchAntiJumpOffset			0x43
#define MoveBorderIdleInterceptorOffset                 0x45

#define ComputerAttackSelectNoAttackFound		-2
#define ComputerAttackSelectSomethingMessedUp		0
#define ComputerAttackSelectAttackFound			1
#define ComputerAttackSelectMoveForward			2
#define ComputerAttackSelectMoveBack			3
#define ComputerAttackSelectJumpIdleUp			4
#define ComputerAttackSelectJumpForward			5
#define ComputerAttackSelectJumpBack			6
#define ComputerAttackSelectCrouchBlock			7
#define ComputerAttackSelectBlock			8
#define ComputerAttackSelectIntoCrouch			9
#define ComputerAttackSelectStandUp			10

#define ArtificialIntelligenceIntoCrouchPattern		1
#define ArtificialIntelligenceStandUpPattern		2

#define ArtificialIntelligencePatternInfiniteLength	30000

#define CompulsoryIdleIdentifier			0
#define CompulsoryWalkingForwardIdentifier		1
#define CompulsoryWalkingBackIdentifier			2
#define CompulsoryIntoCrouchIdentifier			3
#define CompulsoryCrouchIdentifier			4
#define CompulsoryGettingUpIdentifier			8
#define CompulsoryBlockIdentifier			9
#define CompulsoryCrouchBlockIdentifier			10

#define MaximumStoryModeLength				30

#define StoryBoardMaximumTextSize			0x100
#define StoryBoardMaximumTextureAmount			5
#define StoryBoardMaximumTextAmount			3
#define StoryBoardMaximumSoundEffectAmount		2

#define StoryBoardDestroyTextureIdentifier		0
#define StoryBoardLoadTextureIdentifier			1
#define StoryBoardChangeTextureIdentifier		2

#define StoryBoardTextureStructIdentifier		0
#define StoryBoardTextStructIdentifier			1
#define StoryBoardSoundEffectStructIdentifier		2
#define StoryBoardStructAmount				3

#define StoryBoardDestroyTextIdentifier			0

#define StoryBoardDestroySoundEffectIdentifier		0

#define ModeAmount					4

#define CharacterOnePalette				CharacterOne
#define CharacterTwoPalette				CharacterTwo
#define BackGroundPalette				2
#define AdditionalAnimationPalette			3

#define RedGreenBlueType				0
#define PaletteType					1

#define StairWayToHeavenIdentifier			0xff

#define CharsAreIdenticalNot				0
#define CharsAreIdenticalBasic				1

#define GameOverNoDrawPoints				0
#define GameOverDrawPoints				1

#define SelectNewCharacterIdentifier			0xFE

#define MaximumDifficulty				100
#define StandardArcadeDifficulty			100
#define StandardSurvivalDifficulty			100
#define StandardStoryDifficulty				100

#define ProllyMaximumWinQuoteSize			255

#define NewPlayerJoinsInIdentifier			0x2

#define BasicCharacterTextureSizeDrawn			64

#define CrashLayerExistenceExistenceOffset		0
#define CrashLayerAttackExistenceOffset			1
#define CrashLayerBlockExistenceOffset			2
#define CrashLayerExistenceTypeAmount			3

#define FightMenuMainIdentifier				0
#define FightMenuCheckIdentifier			1
#define FightMenuOptionsIdentifier			2
#define FightMenuItsOverIdentifier			3

#define FightMenuMainArrayOffset			0
#define FightMenuMainArrayUpperOffset			5

#define FightMenuCheckArrayOffset			5
#define FightMenuCheckArrayUpperOffset			8

#define FightMenuOptionsArrayOffset			8
#define FightMenuMusicOption				8
#define FightMenuSoundEffectOption			9
#define FightMenuOptionsArrayUpperOffset		11

#define FightMenuPointAmount 				11

#define MaximumIntroAmount				3

#define MenuSelectSoundEffectIdentifier			0
#define MenuSelectedSoundEffectIdentifier		1
#define MenuDeniedSoundEffectIdentifier			2
#define MenuSoundEffectAmount				3

#define CheckIntro					0
#define PlayIntro					1

#define FormatNormal					1
#define FormatADPCM					20

#define StreamingInActive				0
#define StreamingActive					1
#define StreamingCleanUp				2
#define StreamingLoad					3

#define StreamingPollInterval				50

#define MaximumSoundLoopValue				0x7D00

#define VolumeMaxCDDA					15
#define VolumeMaxOGG					255

#define CharacterTextureBufferAmount			2

#define DrawCharDifferentlyGreyTintValue		0.4f

#define ButtonA						0
#define ButtonB						1
#define ButtonX						2
#define ButtonY						3
#define ButtonL						4
#define ButtonR						5
#define ButtonUp					6
#define ButtonDown					7
#define ButtonLeft					8
#define ButtonRight					9
#define ButtonStart					10
#define ButtonAmount					11

#define OptionMenuDifficultyOption	0
#define OptionMenuTimerOption		1
#define OptionMenuSoundOption		2
#define OptionMenuReturnOption		3
#define OptionMenuOptionAmount		4

#define FadeToBlackIdentifier		2

#define SingleOptionMenuArraySize	0x10