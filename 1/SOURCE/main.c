//Copyright 2012 - Josh Tari

//This file is part of the Dolmexica Engine.

//The Dolmexica Engine is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//The Dolmexica Engine is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with the Dolmexica Engine.  If not, see <http://www.gnu.org/licenses/>.


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

#include "DolmexicaDefinitions.h"
#include "ImplicitDeclarations.h"
#include "MyStructs.h"

//DC stuff
#include "DreamCastOnlyDefinitions.h"
#include "DreamCastOnlyStructs.h"

// Music Thingies

// Everything related to fonts

pvr_ptr_t FontTexture;

FontHeaderStruct FontHeaderData;
FontSingleCharacterStruct FontCharacterData[FontCharacterAmount];

//Global Power VR Texture Declarations. Maybe they should be "localized" later on?

//pvr_ptr_t GuiTexture;
//pvr_ptr_t TimerTexture;

pvr_ptr_t LoadingBackGroundTexture;

//IMG placeholder
kos_img_t IMGFilePlaceholder;

//Sound Effect Thingies

int VolumeSFX = 255;
int VolumeCDDA = 15;



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
#include "ModeMenu.c"
#include "SurvivalMode.c"
#include "StoryMode.c"


#include "Intro.c"
#include "TitleScreen.c"



//extern uint8 romdisk_boot[];
//KOS_INIT_ROMDISK(romdisk_boot);

//Main Function.

int main(){

char GameLoop = 1;
int GameStage = GameStageIntro;
int WhichPlayerActive = CharacterOne;


InitiatePowerVR();
CheckFileSystem();
LoadGui();
//DrawWarningScreen(); //PUT IT BACK IN BRO, IT'S COMEDY GOLD!!!
if(!SetVideoMode()) GameLoop = 0;
fs_romdisk_init();
InitiatePalette();
snd_init();
spu_cdda_volume(VolumeCDDA, VolumeCDDA);
spu_cdda_pan(0, 31);

//Debugging Zone START!



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
GameStage = ArcadeMode(&WhichPlayerActive);
//Arcade Mode!
}
if(GameStage == 4){
GameStage = StoryMode(&WhichPlayerActive);
//Story Mode!
}
if(GameStage == 5){
GameStage = SurvivalMode(&WhichPlayerActive);
//Survival Mode!
}
if(GameStage == 6){
GameStage = MusicMenu(&WhichPlayerActive);
//Option Mode!
}
if(GameStage == 13){
GameLoop = 0;
}
}
if(CheckReturn()) arch_menu();
return(1);
}