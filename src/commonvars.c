#include "commonvars.h"
#include <stdbool.h>
#include "pd_api.h"


int showFps = ShowFpsDefault;
bool showDebugInfo = DebugInfoDefault;
unsigned int FrameTime =0, Frames=0;
float CurrentMs=0.0f;

PDMenuItem* menuItem1 = NULL, *menuItem2 = NULL, *menuItem3 = NULL;
PlaydateAPI* pd;
PDButtons currButtons, prevButtons;

LCDBitmapTable* IMGFloor = NULL, * IMGPlayer = NULL, * IMGBox = NULL, * IMGEmpty = NULL, * IMGExit = NULL, * IMGFloorLeft = NULL, * IMGFloorRight = NULL,
    * IMGEarthGrassRight = NULL, * IMGEarthGrassLeft = NULL, * IMGEarthLeft = NULL, * IMGEarthRight = NULL, * IMGEarthMiddle = NULL, * IMGFloatingFloor = NULL,
    * IMGFloatingFloorLeft = NULL, * IMGFloatingFloorRight = NULL, * IMGFloatingFloorMiddle = NULL, * IMGTower = NULL, * IMGStartTower = NULL, * IMGTowerShaft = NULL,
    * IMGRoof1 = NULL, * IMGRoof2 = NULL, * IMGRoofCornerLeft = NULL,* IMGRoofCornerRight = NULL, * IMGRoofDownRight = NULL, * IMGRoofDownLeft = NULL,
    * IMGRoofCornerBoth = NULL;

//ID's start counting from 1
const char* blockNames[] = {"None", "Eraser", "Player", "Box", "Middle Earth Grass", "Exit", "Right Earth Grass", "Left Earth Grass", "Right Earth", "Middle Earth", "Left Earth",
    "Float Floor", "Left Float Floor", "Middle Float Floor", "Right Float Floor", "Left Floor", "Right Floor", "Tower", "Start Tower",
    "Tower Shaft", "Roof 1", "Roof 2", "Left Roof Corner", "Right Roof Corner", "Both Roof Corner", "Right Roof Down", "Left Roof Down" };

const char* skins[] = { "Default", "Tech", "Flat", "Ti-83", "Kenney"};
char* LevelPacks[MaxLevelPacks];
const char* InternalLevelPacks[InternalLevelPackCount] = { "davy" };
LCDBitmap * IMGIntro1 = NULL, *IMGIntro2 = NULL, *IMGIntro3 = NULL, * IMGIntro4 = NULL, *IMGTitleScreen = NULL, * IMGGrid = NULL, *IMGSelection = NULL;

LCDFont* Nano, * Mini, * Mini2X;

char* levelext = "lev";
char* levelprefix = "level";
char* GetStringResult;
int GameState = GSIntroInit;
int SelectedLevel = 0, NeedRedraw = 1, AskingQuestionID = -1, titleStep = tsMainMenu, titleSelection = 0, Option = opMusicSound, InstalledLevels = 0, CurrentLevelPackIndex = 0, FoundLevelPacks = 0, GetStringId = -1, GetStringX = 0, GetStringY = 0 ;
bool AskingQuestion = false, FreeView = false, LevelEditorMode = false, LevelEditorPlayMode = false, NeedToReloadGraphics = false, AskingGetString = false;
int IntroScreenNr = 1;
int framecounter = 0;
size_t MaxLenGetString = 0;
CWorldParts* WorldParts;
CSelector* Selector;

void setPDPtr(PlaydateAPI* p) {
    pd = p;
}
