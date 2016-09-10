#include <kos.h> 

KOS_INIT_FLAGS(INIT_DEFAULT);


//Standard Stuff
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/*
QuickLZ Compression Format.

In order to use this format for free, the engine has to be released under the GPL. Fair trade if you ask me.
*/
#include "quicklz.h"
#include "quicklz.c"

//For Texture stuff
#include <kmg/kmg.h> //The KallistiOS image format. This image format loads ten times faster than PNGs since it's pre-twiddled and is thus AWESOME! :3
// It's basically just a .PVR file with a different header...


//Definitions. They define.


#include "CONFIG.h"

#include "DolmexicaMacros.h"
#include "DolmexicaDefinitions.h"
#include "ImplicitDeclarations.h"
#include "DolmexicaStructs.h"

//DC stuff
#include "DreamCastOnlyDefinitions.h"
#include "DreamCastOnlyStructs.h"


//File junk
#ifdef DOLMEXICA_SD

#include "/home/captaindc/dc/kos-ports/libsd/sample/generic/ff.h"
#include "FileFunctions.c"
FATFS SuperCardFileSystemObject;

#else

#define FileOpen(x,y) fs_open(x,y)
#define FileRead(x,y,z) fs_read(x,y,z)
#define FileWrite(x,y,z) fs_write(x,y,z)
#define FileSeek(x,y,z) fs_seek(x,y,z)
#define FileTell(x) fs_tell(x)
#define FileTotal(x) fs_total(x)
#define FileClose(x) fs_close(x)
#define FileUnlink(x) fs_unlink(x)
#define FileMemoryMap(x) fs_mmap(x)

#endif

// Music Thingies

// Everything related to fonts

pvr_ptr_t FontTexture;

FontHeaderStruct FontHeaderData;
FontSingleCharacterStruct FontCharacterData[FontCharacterAmount];

//Global Power VR Texture Declarations. Maybe they should be "localized" later on?

pvr_ptr_t LoadingBackGroundTexture;

//IMG placeholder
kos_img_t IMGFilePlaceholder;

//Sound Effect Thingies

#include <oggvorbis/sndoggvorbis.h>

int VolumeSFX = 255;
int VolumeCDDA = 15;


//Lua

#ifdef LUA_VERSION_KOS
#include <lua/lua.h>
#endif

#ifdef LUA_VERSION_502
#include LUA_HEADER_PATH
#include LUA_HEADER_LIB_PATH
#include LUA_HEADER_AUX_PATH
#endif


#ifndef LUA_VERSION_NONE

static lua_State* LuaState = NULL;
#endif

#include "PrepareScriptLanguage.c"

//Debugging stuff. Can be removed after finishing the game. Maybe. Probably not though.
#include "FileSystemTest.c"
//#include "TestDraw.c"
char FileSystemUsed[NormalFileDirSize] = "/pc";
char StreamingFileSystemUsed[NormalFileDirSize] = "/pc";
int MusicWorks = 1;

//The various game source files. Should get ordered.





#include "InitiatePowerVR.c"
#include "ControllerInputFunctions.c"


#include "FileExists.c"
#include "CheckFileSystem.c"
#include "RomDiskFunctions.c"
#include "FileCopyToOtherFileSystem.c"
#include "SoundFunctions.c"
#include "NewStreamPulseCodeModulationFile.c"
#include "CrashLayerDecompress.c"
#include "TextureLoadPKG.h"
#include "FontFunctions.c"
#include "LoadPalette.c"
#include "CheckReturn.c"

#include "DeLoadTextures.c"
#include "FightAnimation.c"
//#include "DrawShadow.c"
#include "UpdateComputerCounters.c"
#include "NewCollisionDetect.c"
//#include "CollisionDetect.c"
#include "LoadEffects.c"
#include "DrawEffect.c"
#include "LoadChar.c"
#include "DrawChar.c"
//#include "LoadStage.c"
#include "NewLoadStageTotally.c"
#include "DrawStage.c"
#include "LoadGui.c"
#include "LoadGraphicalUserInterface.c"
#include "DrawGui.c"
#include "NewDrawGraphicalUserInterface.c"
#include "DrawSingleLifeBar.c"
#include "MovementReadHuman.c"
#include "NewMovementReadCPU.c"
//#include "FighterSelection.c" //OUT-DATED!!
#include "CharStatsLoad.c"
#include "LoadSoundEffect.c" 
#include "Loading.c"
//#include "NormalFight.c"
#include "NewFighterSelect.c"
#include "FetchNewSurvivalModeEnemy.c"
#include "SurvivalCalculateNextFight.c"

#include "HertzSelectScreen.c"
#include "VideoMode.c"

#include "NewmalFight.c"

#include "CreditFunction.c"

#include "StoryModePreFetchTheStory.c"
#include "StoryBoardFunctions.c"
#include "LetsSeeTheStory.c"
#include "UnfoldTheTragedy.c"

#include "ModeNotAvailable.c"
#include "WhoAgainstWho.c"
#include "GameOver.c"
#include "ArcadePlayEnding.c"
#include "ShowArcadeWayToGo.c"
#include "ArcadeMode.c"
//#include "WarningScreen.c"
#include "MusicMenu.c"
#include "OptionMenu.c"
#include "ModeMenu.c"
#include "SurvivalMode.c"
#include "StoryMode.c"


#include "Intro.c"
#include "TitleScreen.c"



//extern uint8 romdisk_boot[];
//KOS_INIT_ROMDISK(romdisk_boot);

//Main Function.

int main(){

ModifiableOptionStruct ModifiableOptionData;
char GameLoop = 1;
int GameStage = GameStageIntro;
int WhichPlayerActive = CharacterOne;

ModifiableOptionData.Difficulty = StandardArcadeDifficulty;
ModifiableOptionData.FirstTimerStartValue = 10;
ModifiableOptionData.SecondTimerStartValue = -1;

InitiatePowerVR();
CheckFileSystem();
PrepareScriptLanguage();
LoadGui();
//DrawWarningScreen(); //PUT IT BACK IN BRO, IT'S COMEDY GOLD!!!
if(!SetVideoMode()) GameLoop = 0;
fs_romdisk_init();
InitiatePalette();
snd_init();
spu_cdda_volume(VolumeCDDA, VolumeCDDA);
spu_cdda_pan(0, 31);
sndoggvorbis_init();
sndoggvorbis_volume((VolumeCDDA/(float)VolumeMaxCDDA)*VolumeMaxOGG);


//Debugging Zone START!

//malloc_stats();

//Debugging Zone END!

while(GameLoop){
if(GameStage == GameStageIntro){
Intro(PlayIntro);
GameStage = GameStageTitleScreen;
}
if(GameStage == GameStageTitleScreen){
GameStage = DrawTitleScreen(&WhichPlayerActive);
}
if(GameStage == 2){
GameStage = DrawModeMenu(&WhichPlayerActive);
} 
if(GameStage == 3){
GameStage = ArcadeMode(&WhichPlayerActive, &ModifiableOptionData);
//Arcade Mode!
}
if(GameStage == 4){
GameStage = StoryMode(&WhichPlayerActive, &ModifiableOptionData);
//Story Mode!
}
if(GameStage == 5){
GameStage = SurvivalMode(&WhichPlayerActive, &ModifiableOptionData);
//Survival Mode!
}
if(GameStage == GameStageMusicMode){

//Option Mode!
}
if(GameStage == GameStageOptionMenu){
GameStage = OptionMenu(&WhichPlayerActive, &ModifiableOptionData);
GameStage = MusicMenu(&WhichPlayerActive, &GameStage);
//Option Mode!
}
if(GameStage == 13){
GameLoop = 0;
}
}

#ifndef LUA_VERSION_NONE
lua_close(LuaState);
#endif

sndoggvorbis_shutdown();

cdfs_test();
if(CheckReturn()) arch_menu();
return(1);
}