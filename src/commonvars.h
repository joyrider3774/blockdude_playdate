#ifndef commonvars_h
#define commonvars_h

#include <stdio.h>
#include <stdbool.h>
#include "pd_api.h"

#define FRAMERATE 40
#define MAXSKINS 3
#define SMOOTHING 0
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 240
#define TileWidth 16
#define TileHeight 16
#define HALFWINDOWWIDTH (WINDOW_WIDTH >> 1)
#define HALFWINDOWHEIGHT (WINDOW_HEIGHT >> 1)
#define InstalledLevels 21
#define AlphaInc 20
#define NrOfRows 50
#define NrOfCols 50
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
#define GroupFloor 1
#define GroupPlayer 2
#define GroupBox 3
#define GroupExit 4
#define ZPlayer 10 //has to be drawn last + It has to be moved as last also for the logic to work. (otherwise a box can fall down when a player jumps)
#define ZWall 5
#define ZBox 5
#define ZFloor 5
#define ZExit 1
#define InputDelay 13
#define MaxMusicFiles 1
#define NrOfSounds 4
#define SND_MENU 0
#define SND_SELECT 1
#define SND_ERROR 2
#define SND_STAGEEND 3
#define MaxAlpha 150
#define AnimBaseLeft 0
#define AnimBaseRight 4
#define AnimBaseLeftJump 8
#define AnimBaseRightJump 12

#define mmStartGame 0
#define mmOptions 1
#define mmCredits 2
#define mmCount 3

#define opMusic 0
#define opSound 1
#define opSkin 2
#define opInverted 3
#define opCount 4

#define tsMainMenu 0
#define tsOptions 1
#define tsCredits 2

#define GSDiff 50

#define GSTitleScreen 0
#define GSIntro 1
#define GSGame 2
#define GSStageClear 3
#define GSStageSelect 4

#define GSIntroInit GSIntro + GSDiff
#define GSGameInit GSGame + GSDiff
#define GSStageClearInit GSStageClear + GSDiff
#define GSTitleScreenInit GSTitleScreen + GSDiff
#define GSStageSelectInit GSStageSelect + GSDiff

typedef struct CWorldPart CWorldPart;
typedef struct CWorldParts CWorldParts;

extern const char* const skins[3];

extern int gameState, debugMode;
extern PlaydateAPI *pd;
extern PDButtons currButtons, prevButtons;

extern LCDBitmapTable* IMGFloor, * IMGPlayer, * IMGBox, * IMGEmpty, * IMGExit, * IMGFloorLeft, * IMGFloorRight,
* IMGEarthGrassRight, * IMGEarthGrassLeft, * IMGEarthLeft, * IMGEarthRight, * IMGEarthMiddle, * IMGFloatingFloor, * IMGFloatingFloorLeft,
* IMGFloatingFloorRight, * IMGFloatingFloorMiddle, * IMGTower, * IMGStartTower, * IMGTowerShaft, * IMGRoof1, * IMGRoof2, * IMGRoofCornerLeft,
* IMGRoofCornerRight, * IMGRoofDownRight, * IMGRoofDownLeft, * IMGRoofCornerBoth;

extern LCDBitmap* IMGIntro1, * IMGIntro2, * IMGIntro3, * IMGBackground, * IMGTitleScreen;

extern LCDFont *Nano, *Mini, *Mini2X;

extern const char* const skins[];
extern int skin;
extern int GameState;
extern int SelectedLevel, NeedRedraw, AskingQuestionID, titleStep, titleSelection, Option;
extern bool AskingQuestion;
extern CWorldParts* WorldParts;
extern int IntroScreenNr;
extern int framecounter;
extern CWorldPart* ThePlayer;

void setPDPtr(PlaydateAPI* p);

#endif