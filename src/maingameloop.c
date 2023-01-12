#include "pd_api.h"
#include "crank.h"
#include "maingameloop.h"
#include "commonvars.h"
#include "sound.h"
#include "game.h"
#include "savestate.h"

// game initialization
void setupGame(void)
{  
    GameState = GSIntroInit;
    setCrankMoveThreshold(70);
    initSaveState();    
    initSaveState();
    initSound();
    initMusic();
    setMusicOn(isMusicOnSaveState());
    setSoundOn(isSoundOnSaveState());
    pd->display->setInverted(isInvertedSaveState());
    LoadGraphics();
    LoadFonts();
    WorldParts = CWorldParts_Create();
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
        default:
            break;
    }

    if (debugMode)
    {
        pd->system->drawFPS(0, 0);
    }

	return result;
}
