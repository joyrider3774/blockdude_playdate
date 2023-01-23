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

void StageSelectInit()
{
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


	if (!AskingQuestion && (currButtons & kButtonLeft) && (!(prevButtons & kButtonLeft)))
	{
		playMenuSound();
		NeedRedraw = true;
		SelectedLevel--;
		if (SelectedLevel < 1)
			SelectedLevel = 1;
		LoadSelectedLevel();
		WorldParts->AllDirty = true;
	}

	if (!AskingQuestion && (currButtons & kButtonRight) && (!(prevButtons & kButtonRight)))
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
		pd->graphics->fillRect(0, 0, WINDOW_WIDTH, 15, kColorWhite);
		pd->graphics->drawRect(0, 0, WINDOW_WIDTH, 15, kColorBlack);
		if (LevelEditorMode)
		{
			if (!LevelEditorPlayMode)
				pd->system->formatString(&Text, "Level: %d/%d - (A) Edit Level - (B) Titlescreen", SelectedLevel, InstalledLevels);
			else
				pd->system->formatString(&Text, "Level: %d/%d - (A) Play Level - (B) Titlescreen", SelectedLevel, InstalledLevels);
		}
		else if (SelectedLevel <= lastUnlockedLevel())
			pd->system->formatString(&Text, "Level: %d/%d - (A) Play Level - (B) Titlescreen", SelectedLevel, InstalledLevels);
		else
			pd->system->formatString(&Text, "Level: %d/%d - Level is locked! - (B) Titlescreen", SelectedLevel, InstalledLevels);

		pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 4, 4);
		pd->system->realloc(Text, 0);
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
	DoShowDebugInfo();
}
