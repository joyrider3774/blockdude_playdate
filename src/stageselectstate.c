#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "stageselectstate.h"
#include "commonvars.h"
#include "gamefuncs.h"
#include "menus.h"
#include "cworldparts.h"
#include "sound.h"
#include "savestate.h"
#include "pd_api.h"
#include "pd_helperfuncs.h"
#include "crank.h"

void StageSelectInit()
{
	setCrankMoveThreshold(90);
	pd->graphics->setFont(Mini);
	LoadSelectedLevel();
	NeedRedraw = true;
	DestroyMenuItems();
	CreateOtherMenuItems();
}

void StageSelect()
{
	if (GameState == GSStageSelectInit)
	{
		StageSelectInit();
		GameState -= GSDiff;
	}


	if (!AskingQuestion && (currButtons & kButtonB) && (!(prevButtons & kButtonB)))
	{
		GameState = GSTitleScreenInit;
		CWorldParts_RemoveAll(WorldParts);
		playMenuBackSound();
	}

	if (!AskingQuestion && (currButtons & kButtonA) && (!(prevButtons & kButtonA)))
	{
		playMenuSelectSound();
		if (LevelEditorMode)
		{
			if (SelectedLevel <= InstalledLevels)
			{
				if (LevelEditorPlayMode)
					PlayLevelIfNoErrorsFound();
				else
					GameState = GSLevelEditorInit;
			}
		}
		else
		{
			if (SelectedLevel <= lastUnlockedLevel())
				GameState = GSGameInit;
			else
			{
				char* Text;
				pd->system->formatString(&Text, "This Level Hasn't been unlocked yet!\nDo you want to play the last unlocked\nlevel %d/%d?\n\nPress (A) to Play (B) to cancel", lastUnlockedLevel(), InstalledLevels);
				AskQuestion(qsNotUnlocked, Text);
				pd->system->realloc(Text, 0);
				DestroyMenuItems();
			}
		}
	}

	unsigned int crankResult = crankUpdate();
	if (!AskingQuestion && (((currButtons & kButtonLeft) && (!(prevButtons & kButtonLeft))) || (crankResult == CRANKMOVELEFT)))
	{
		playMenuSound();
		NeedRedraw = true;
		SelectedLevel--;
		if (SelectedLevel < 1)
			SelectedLevel = 1;
		LoadSelectedLevel();
		WorldParts->AllDirty = true;
	}

	if (!AskingQuestion && (((currButtons & kButtonRight) && (!(prevButtons & kButtonRight))) || (crankResult == CRANKMOVERIGHT)))
	{
		playMenuSound();
		NeedRedraw = true;
		SelectedLevel++;
		if (SelectedLevel > InstalledLevels)
			SelectedLevel = InstalledLevels;
		LoadSelectedLevel();
		WorldParts->AllDirty = true;
	}

	if (NeedRedraw)
	{
		NeedRedraw = false;
		char* Text;
		if (WorldParts->LevelBitmap)
		{
			pd->graphics->pushContext(WorldParts->LevelBitmap);
		}

		if (((skinSaveState() == 1) || (skinSaveState() == 4)))
		{
			pd->graphics->clear(kColorBlack);
		}
		else
		{
			pd->graphics->clear(kColorWhite);
		}

		if (WorldParts->LevelBitmap)
		{
			pd->graphics->popContext();
		}
		//pd->graphics->drawBitmap(IMGBackground, 0, 0, kBitmapUnflipped);
		CWorldParts_Draw(WorldParts, ((skinSaveState() == 1) || (skinSaveState() == 4)));
		if (WorldParts->LevelBitmap)
		{
			DrawBitmapSrcRec(WorldParts->LevelBitmap, 0, 0, WorldParts->ViewPort->MinScreenX, WorldParts->ViewPort->MinScreenY, WINDOW_WIDTH, WINDOW_HEIGHT, kBitmapUnflipped);
		}
		LCDBitmap* tmp = pd->graphics->newBitmap(WINDOW_WIDTH, 16, kColorWhite);
		pd->graphics->pushContext(tmp);
		pd->graphics->fillRect(0, 0, WINDOW_WIDTH, 16, kColorWhite);
		pd->graphics->fillRect(0, 15, WINDOW_WIDTH, 1, kColorBlack);
		if (LevelEditorMode)
		{
			if (!LevelEditorPlayMode)
				pd->system->formatString(&Text, "Level: %d/%d A:Edit Level B:Titlescreen", SelectedLevel, InstalledLevels);
			else
				pd->system->formatString(&Text, "Level: %d/%d A:Play Level B:Titlescreen", SelectedLevel, InstalledLevels);
		}
		else if (SelectedLevel <= lastUnlockedLevel())
			pd->system->formatString(&Text, "Level: %d/%d A:Play Level B:Titlescreen", SelectedLevel, InstalledLevels);
		else
			pd->system->formatString(&Text, "Level: %d/%d is locked! B:Titlescreen", SelectedLevel, InstalledLevels);

		pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 4, 4);
		pd->system->realloc(Text, 0);
		pd->graphics->popContext();
		pd->graphics->drawScaledBitmap(tmp, 0, 0, fontScaleSaveState(), fontScaleSaveState());
		pd->graphics->freeBitmap(tmp);
	}

	int id = -1;
	bool answer = false;
	if (AskQuestionUpdate(&id, &answer, false))
	{
		if (id == qsNotUnlocked)
		{
			if (answer)
			{
				SelectedLevel = lastUnlockedLevel();
				LoadSelectedLevel();
				GameState = GSGameInit;
			}
			else
			{
				CreateOtherMenuItems();
				//we asked question so need to redraw everything
				WorldParts->AllDirty = true;
			}
		}
		else
		{
			//level play / validation error confirmations
			if (answer)
			{
				CreateOtherMenuItems();
				//we asked question so need to redraw everything
				WorldParts->AllDirty = true;
			}
		}
	}
}
