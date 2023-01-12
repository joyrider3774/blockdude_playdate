#include "commonvars.h"
#include <stdbool.h>
#include "pd_api.h"


int debugMode;

PDMenuItem* menuItem1 = NULL, *menuItem2 = NULL, *menuItem3 = NULL;
PlaydateAPI* pd;
PDButtons currButtons, prevButtons;

LCDBitmapTable* IMGFloor = NULL, * IMGPlayer = NULL, * IMGBox = NULL, * IMGEmpty = NULL, * IMGExit = NULL, * IMGFloorLeft = NULL, * IMGFloorRight = NULL,
    * IMGEarthGrassRight = NULL, * IMGEarthGrassLeft = NULL, * IMGEarthLeft = NULL, * IMGEarthRight = NULL, * IMGEarthMiddle = NULL, * IMGFloatingFloor = NULL,
    * IMGFloatingFloorLeft = NULL, * IMGFloatingFloorRight = NULL, * IMGFloatingFloorMiddle = NULL, * IMGTower = NULL, * IMGStartTower = NULL, * IMGTowerShaft = NULL,
    * IMGRoof1 = NULL, * IMGRoof2 = NULL, * IMGRoofCornerLeft = NULL,* IMGRoofCornerRight = NULL, * IMGRoofDownRight = NULL, * IMGRoofDownLeft = NULL, * IMGRoofCornerBoth = NULL;

const char* skins[] = { "Default", "Tech", "Ti-83" };

LCDBitmap * IMGIntro1 = NULL, *IMGIntro2 = NULL, *IMGIntro3 = NULL, *IMGBackground = NULL, *IMGTitleScreen = NULL;

LCDFont* Nano, * Mini, * Mini2X;

int GameState = GSIntroInit;
int SelectedLevel = 0, NeedRedraw = 1, AskingQuestionID = -1, titleStep = tsMainMenu, titleSelection = 0, Option = opMusic;
bool AskingQuestion = false, FreeView = false;
int IntroScreenNr = 1;
int framecounter = 0;

CWorldParts* WorldParts;
CWorldPart* ThePlayer;

void setPDPtr(PlaydateAPI* p) {
    pd = p;
}
