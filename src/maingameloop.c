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

// game initialization
void setupGame(void)
{  
    GameState = GSIntroInit;
    setCrankMoveThreshold(90);
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

    if (debugMode)
    {
        pd->system->drawFPS(0, 0);
    }

    

    return result;
}
