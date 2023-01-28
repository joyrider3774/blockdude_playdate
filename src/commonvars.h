#ifndef commonvars_h
#define commonvars_h

#include <stdio.h>
#include <stdbool.h>
#include "pd_api.h"

#define FRAMERATE 30
#define GameMoveSpeed 3					//dec if fps increases
#define PlayerAnimDelay 5				//inc if fps increases
#define FrameDelayInput 1				
#define FrameDelayInputLevelEditor 3
#define ViewportMove 3					//dec if fps increases


#define MAXSKINS 5
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 240
#define HALFWINDOWWIDTH 200
#define HALFWINDOWHEIGHT 120
#define TileWidth 16
#define TileHeight 16
#define NrOfRowsVisible (WINDOW_HEIGHT / TileHeight)
#define NrOfColsVisible (WINDOW_WIDTH / TileWidth) 
#define InstalledLevelsDefaultGame 21
#define InstalledLevelsLevelEditor 50
#define NrOfRows 50
#define NrOfCols 50
#define MaxLevelPacks 25
#define MaxLenLevelPackName 6

#define IDEmpty 1
#define IDPlayer 2
#define IDBox 3
#define IDFloor 4
#define IDExit 5

#define IDEarthGrassLeft 6
#define IDEarthGrassRight 7
#define IDEarthLeft 8
#define IDEarthMiddle 9
#define IDEarthRight 10
#define IDFloatingFloor 11
#define IDFloatingFloorLeft 12
#define IDFloatingFloorMiddle 13
#define IDFloatingFloorRight 14
#define IDFloorLeft 15
#define IDFloorRight 16
#define IDTower 17
#define IDStartTower 18
#define IDTowerShaft 19
#define IDRoof1 20
#define IDRoof2 21
#define IDRoofCornerLeft 22
#define IDRoofCornerRight 23
#define IDRoofCornerBoth 24
#define IDRoofDownRight 25
#define IDRoofDownLeft 26

//these groups also define drawing order for all dirty items as well as logic
#define GroupNone 10 //special used in level editor
#define GroupExit 0
#define GroupFloor 1
#define GroupBox 2
#define GroupPlayer 3 //has to be drawn and moved last for logic to work
#define NrOfGroups 4 //group none is ignored



#define AnimBaseLeft 0
#define AnimBaseRight 4
#define AnimBaseLeftJump 8
#define AnimBaseRightJump 12

#define errNoError 0
#define errNoPlayer 1
#define errNoExit 2
#define errBlocksPlayerNotOnAFloor 3
#define errBlocksOnPlayerNotOne 4

#define mmStartGame 0
#define mmLevelEditor 1
#define mmOptions 2
#define mmCredits 3
#define mmCount 4

#define opMusic 0
#define opSound 1
#define opSkin 2
#define opInverted 3
#define opCount 4

#define lmPlayMode 0
#define lmEditMode 1
#define lmCount 2

#define spPack 0
#define spCreate 1
#define spDelete 2
#define spOptimize 3
#define spCount 4

#define tsMainMenu 0
#define tsOptions 1
#define tsCredits 2
#define tsLevelEditorMode 3
#define tsSelectPack 4

#define GSDiff 50

#define GSTitleScreen 0
#define GSIntro 1
#define GSGame 2
#define GSStageClear 3
#define GSStageSelect 4
#define GSLevelEditor 5

#define GSLevelEditorInit GSLevelEditor + GSDiff
#define GSIntroInit GSIntro + GSDiff
#define GSGameInit GSGame + GSDiff
#define GSStageClearInit GSStageClear + GSDiff
#define GSTitleScreenInit GSTitleScreen + GSDiff
#define GSStageSelectInit GSStageSelect + GSDiff

#define qsErrPlayer 1
#define qsErrExit 2
#define qsErrBlocksOrPlayerNotOnAFloor 3
#define qsErrBlocksOnPlayerNotOne 4
#define qsNotSaved 5
#define qsNotUnlocked 6
#define qsSolvedNotLastLevel 7
#define qsSolvedLastLevel 8
#define qsSolvedLevel 9
#define qsQuitPlaying 10
#define qsOptimizePack 11
#define qsAllDone 12
#define qsDelPack 13
#define qsClearLevel 14

typedef struct CWorldPart CWorldPart;
typedef struct CWorldParts CWorldParts;
typedef struct CSelector CSelector;

extern int gameState, debugMode;
extern PlaydateAPI *pd;
extern PDButtons currButtons, prevButtons;
extern PDMenuItem* menuItem1, * menuItem2, * menuItem3;

extern LCDBitmapTable* IMGFloor, * IMGPlayer, * IMGBox, * IMGEmpty, * IMGExit, * IMGFloorLeft, * IMGFloorRight,
* IMGEarthGrassRight, * IMGEarthGrassLeft, * IMGEarthLeft, * IMGEarthRight, * IMGEarthMiddle, * IMGFloatingFloor, * IMGFloatingFloorLeft,
* IMGFloatingFloorRight, * IMGFloatingFloorMiddle, * IMGTower, * IMGStartTower, * IMGTowerShaft, * IMGRoof1, * IMGRoof2, * IMGRoofCornerLeft,
* IMGRoofCornerRight, * IMGRoofDownRight, * IMGRoofDownLeft, * IMGRoofCornerBoth;

extern LCDBitmap* IMGIntro1, * IMGIntro2, * IMGIntro3, * IMGIntro4, * IMGTitleScreen,* IMGGrid, * IMGSelection, * ScreenLevel;

extern char* levelprefix;
extern char* levelext;
extern char* GetStringResult;
extern LCDFont *Nano, *Mini, *Mini2X;
extern char* LevelPacks[MaxLevelPacks];
extern const char* blockNames[];
extern const char* skins[];
extern int skin;
extern int GameState;
extern int SelectedLevel, NeedRedraw, AskingQuestionID, titleStep, titleSelection, Option, InstalledLevels, CurrentLevelPackIndex, FoundLevelPacks, GetStringId, GetStringX, GetStringY;
extern bool AskingQuestion, FreeView, LevelEditorMode, LevelEditorPlayMode, showDebugInfo, NeedToReloadGraphics, AskingGetString;
extern CWorldParts* WorldParts;
extern int IntroScreenNr;
extern int framecounter;
extern CSelector* Selector;
extern size_t MaxLenGetString;

void setPDPtr(PlaydateAPI* p);

#endif