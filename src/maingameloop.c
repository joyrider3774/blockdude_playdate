#include <string.h>
#include "maingameloop.h"
#include "crank.h"
#include "commonvars.h"
#include "sound.h"
#include "gamefuncs.h"
#include "savestate.h"
#include "cselector.h"
#include "stageselectstate.h"
#include "titlescreenstate.h"
#include "gamestate.h"
#include "stageselectstate.h"
#include "leveleditorstate.h"
#include "introstate.h"
#include "pd_api.h"
#include "pd_helperfuncs.h"

void resetGlobals()
{
	GameState = GSIntroInit;
	SelectedLevel = 0;
	NeedRedraw = 1;
	AskingQuestionID = -1;
	titleStep = tsMainMenu;
	titleSelection = 0;
	Option = opMusicSound;
	InstalledLevels = 0;
	CurrentLevelPackIndex = 0;
	FoundLevelPacks = 0;
	GetStringId = -1;
	GetStringX = 0;
	GetStringY = 0;
	AskingQuestion = false;
	FreeView = false;
	LevelEditorMode = false;
	LevelEditorPlayMode = false;
	NeedToReloadGraphics = false;
	AskingGetString = false;
	IntroScreenNr = 1;
	framecounter = 0;
	MaxLenGetString = 0;
	prevLogTime = 0u;
}

// game initialization
void setupGame(void)
{  
	resetGlobals();
    GameState = GSIntroInit;
    initSaveState();
    initSound();
    initMusic();
    setMusicOn(isMusicOnSaveState());
    setSoundOn(isSoundOnSaveState());
    pd->display->setInverted(isInvertedSaveState());
    LoadGraphics();
    LoadFonts();
    WorldParts = CWorldParts_Create(true);
    Selector = CSelector_Create(WorldParts);
}

void terminateGame(void)
{
	deInitSound();
	deInitMusic();
	UnLoadGraphics();
	CWorldParts_deinit(WorldParts);
	CSelector_deinit(Selector);
}

// main update function
int mainLoop(void* ud)
{
    int result = 1;
    prevButtons = currButtons;
    pd->system->getButtonState(&currButtons, NULL, NULL);

    //gamestate handling   
    switch (GameState)
    {
        case GSIntro:
        case GSIntroInit:
            Intro();
            break;
        case GSTitleScreen:
        case GSTitleScreenInit:
            TitleScreen();
            break;
        case GSStageSelect:
        case GSStageSelectInit:
            StageSelect();
            break;
        case GSGame:
        case GSGameInit:
            Game();
            break;
        case GSLevelEditor:
        case GSLevelEditorInit:
            LevelEditor();
            break;
        default:
            break;
    }

    DoShowDebugInfo();

    if (showFps)
    {
        Frames++;
        if (pd->system->getCurrentTimeMilliseconds() - FrameTime >= 1000) 
		{
            CurrentMs = (float) (1000.0f / Frames);
            Frames = 0;
            FrameTime += 1000;
        }
        char* Text;
        pd->system->formatString(&Text, "%f %f", CurrentMs, 1000.0f / CurrentMs);
        pd->graphics->pushContext(NULL);
        pd->graphics->setFont(Mini2X);
        pd->graphics->fillRect(0, 0, pd->graphics->getTextWidth(Mini2X, Text, strlen(Text), kASCIIEncoding, 0), 16, kColorWhite);
        pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 0, 0);
        pd->system->realloc(Text, 0);
        pd->graphics->popContext();
    }
    if (BatteryMonitoring)
    {
        pd->system->setAutoLockDisabled(true);
        prevLogTime = logPower("power.csv", 60u, prevLogTime);
    }
    return result;
}
