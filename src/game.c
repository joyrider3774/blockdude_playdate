#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "commonvars.h"
#include "sound.h"
#include "savestate.h"
#include "crank.h"
#include "game.h"
#include "cviewport.h"
#include "cworldpart.h"
#include "cworldparts.h"
#include "cselector.h"
#include "pd_api.h"

LCDBitmap* loadImageAtPath(const char* path)
{
	const char* outErr = NULL;
	LCDBitmap* img = pd->graphics->loadBitmap(path, &outErr);
	if (outErr != NULL) {
		pd->system->error("Error loading image at path '%s': %s", path, outErr);
		pd->system->logToConsole("Error loading image at path '%s': %s", path, outErr);
	}
	return img;
}

LCDBitmapTable* loadBitmapTableAtPath(const char* path)
{
	const char* outErr = NULL;
	LCDBitmapTable* table = pd->graphics->loadBitmapTable(path, &outErr);
	if (outErr != NULL) {
		pd->system->error("Error loading image at path '%s': %s", path, outErr);
		pd->system->logToConsole("Error loading image at path '%s': %s", path, outErr);
	}
	return table;
}

LCDFont* loadFontAtPath(const char* path)
{
	const char* outErr = NULL;
	LCDFont* fnt = pd->graphics->loadFont(path, &outErr);
	if (outErr != NULL) {
		pd->system->error("Error loading font at path '%s': %s", path, outErr);
		pd->system->logToConsole("Error loading font at path '%s': %s", path, outErr);
	}
	return fnt;
}

void DrawBitmapSrcRec(LCDBitmap* Bitmap, int dstX, int dstY, int srcX, int srcY, int srcW, int srcH, LCDBitmapFlip FlipMode)
{
	pd->graphics->pushContext(Bitmap);
	pd->graphics->setClipRect(srcX, srcY, srcW, srcH);
	pd->graphics->pushContext(NULL);
	pd->graphics->setClipRect(dstX, dstY, srcW, srcH);
	pd->graphics->setDrawOffset(-srcX + dstX, -srcY + dstY);
	pd->graphics->drawBitmap(Bitmap, 0, 0, FlipMode);
	pd->graphics->setDrawOffset(0, 0);
	pd->graphics->clearClipRect();
	pd->graphics->popContext();
	pd->graphics->popContext();
}

void DrawBitmapScaledSrcRec(LCDBitmap* Bitmap, float xscale, float yscale, int dstX, int dstY, int srcX, int srcY, int srcW, int srcH)
{
	pd->graphics->setClipRect(dstX, dstY, (int)(srcW * xscale), (int)(srcH * yscale));
	pd->graphics->setDrawOffset((int)(-srcX * xscale) + dstX, (int)(-srcY * yscale) + dstY);
	pd->graphics->drawScaledBitmap(Bitmap, 0, 0, xscale, yscale);
	pd->graphics->setDrawOffset(0, 0);
	pd->graphics->clearClipRect();
}

void UnLoadGraphics()
{
	if (IMGExit)
		pd->graphics->freeBitmapTable(IMGExit);

	if (IMGFloor)
		pd->graphics->freeBitmapTable(IMGFloor);

	if (IMGPlayer)
		pd->graphics->freeBitmapTable(IMGPlayer);

	if (IMGBox)
		pd->graphics->freeBitmapTable(IMGBox);

	if (IMGEmpty)
		pd->graphics->freeBitmapTable(IMGEmpty);

	if (IMGFloorLeft)
		pd->graphics->freeBitmapTable(IMGFloorLeft);

	if (IMGFloorRight)
		pd->graphics->freeBitmapTable(IMGFloorRight);

	if (IMGEarthGrassRight)
		pd->graphics->freeBitmapTable(IMGEarthGrassRight);

	if (IMGEarthGrassLeft)
		pd->graphics->freeBitmapTable(IMGEarthGrassLeft);

	if (IMGEarthLeft)
		pd->graphics->freeBitmapTable(IMGEarthLeft);

	if (IMGEarthRight)
		pd->graphics->freeBitmapTable(IMGEarthRight);

	if (IMGEarthMiddle)
		pd->graphics->freeBitmapTable(IMGEarthMiddle);

	if (IMGFloatingFloor)
		pd->graphics->freeBitmapTable(IMGFloatingFloor);

	if (IMGFloatingFloorLeft)
		pd->graphics->freeBitmapTable(IMGFloatingFloorLeft);

	if (IMGFloatingFloorRight)
		pd->graphics->freeBitmapTable(IMGFloatingFloorRight);

	if (IMGFloatingFloorMiddle)
		pd->graphics->freeBitmapTable(IMGFloatingFloorMiddle);

	if (IMGTower)
		pd->graphics->freeBitmapTable(IMGTower);

	if (IMGStartTower)
		pd->graphics->freeBitmapTable(IMGStartTower);

	if (IMGTowerShaft)
		pd->graphics->freeBitmapTable(IMGTowerShaft);

	if (IMGRoof1)
		pd->graphics->freeBitmapTable(IMGRoof1);

	if (IMGRoof2)
		pd->graphics->freeBitmapTable(IMGRoof2);

	if (IMGRoofCornerLeft)
		pd->graphics->freeBitmapTable(IMGRoofCornerLeft);

	if (IMGRoofCornerRight)
		pd->graphics->freeBitmapTable(IMGRoofCornerRight);

	if (IMGRoofDownRight)
		pd->graphics->freeBitmapTable(IMGRoofDownRight);

	if (IMGRoofDownLeft)
		pd->graphics->freeBitmapTable(IMGRoofDownLeft);

	if (IMGRoofCornerBoth)
		pd->graphics->freeBitmapTable(IMGRoofCornerBoth);

	if (IMGSelection)
		pd->graphics->freeBitmap(IMGSelection);

	if (IMGGrid)
		pd->graphics->freeBitmap(IMGGrid);

	if (IMGBackground)
		pd->graphics->freeBitmap(IMGBackground);

	if (IMGIntro1)
		pd->graphics->freeBitmap(IMGIntro1);

	if (IMGIntro2)
		pd->graphics->freeBitmap(IMGIntro2);

	if (IMGIntro3)
		pd->graphics->freeBitmap(IMGIntro3);

	if (IMGTitleScreen)
		pd->graphics->freeBitmap(IMGTitleScreen);
}


void LoadGraphics(void)
{
	char *Filename;

	if (IMGExit)
		pd->graphics->freeBitmapTable(IMGExit);

	if (IMGFloor)
		pd->graphics->freeBitmapTable(IMGFloor);

	if (IMGPlayer)
		pd->graphics->freeBitmapTable(IMGPlayer);

	if (IMGBox)
		pd->graphics->freeBitmapTable(IMGBox);

	if (IMGEmpty)
		pd->graphics->freeBitmapTable(IMGEmpty);

	if (IMGFloorLeft)
		pd->graphics->freeBitmapTable(IMGFloorLeft);

	if (IMGFloorRight)
		pd->graphics->freeBitmapTable(IMGFloorRight);

	if (IMGEarthGrassRight)
		pd->graphics->freeBitmapTable(IMGEarthGrassRight);

	if (IMGEarthGrassLeft)
		pd->graphics->freeBitmapTable(IMGEarthGrassLeft);

	if (IMGEarthLeft)
		pd->graphics->freeBitmapTable(IMGEarthLeft);

	if (IMGEarthRight)
		pd->graphics->freeBitmapTable(IMGEarthRight);

	if (IMGEarthMiddle)
		pd->graphics->freeBitmapTable(IMGEarthMiddle);

	if (IMGFloatingFloor)
		pd->graphics->freeBitmapTable(IMGFloatingFloor);

	if (IMGFloatingFloorLeft)
		pd->graphics->freeBitmapTable(IMGFloatingFloorLeft);

	if (IMGFloatingFloorRight)
		pd->graphics->freeBitmapTable(IMGFloatingFloorRight);

	if (IMGFloatingFloorMiddle)
		pd->graphics->freeBitmapTable(IMGFloatingFloorMiddle);

	if (IMGTower)
		pd->graphics->freeBitmapTable(IMGTower);

	if (IMGStartTower)
		pd->graphics->freeBitmapTable(IMGStartTower);

	if (IMGTowerShaft)
		pd->graphics->freeBitmapTable(IMGTowerShaft);

	if (IMGRoof1)
		pd->graphics->freeBitmapTable(IMGRoof1);

	if (IMGRoof2)
		pd->graphics->freeBitmapTable(IMGRoof2);

	if (IMGRoofCornerLeft)
		pd->graphics->freeBitmapTable(IMGRoofCornerLeft);

	if (IMGRoofCornerRight)
		pd->graphics->freeBitmapTable(IMGRoofCornerRight);

	if (IMGRoofDownRight)
		pd->graphics->freeBitmapTable(IMGRoofDownRight);

	if (IMGRoofDownLeft)
		pd->graphics->freeBitmapTable(IMGRoofDownLeft);

	if (IMGRoofCornerBoth)
		pd->graphics->freeBitmapTable(IMGRoofCornerBoth);

	if (IMGGrid)
		pd->graphics->freeBitmap(IMGGrid);

	if (IMGSelection)
		pd->graphics->freeBitmap(IMGSelection);

	if (IMGBackground)
		pd->graphics->freeBitmap(IMGBackground);

	if (IMGIntro1)
		pd->graphics->freeBitmap(IMGIntro1);

	if (IMGIntro2)
		pd->graphics->freeBitmap(IMGIntro2);

	if (IMGIntro3)
		pd->graphics->freeBitmap(IMGIntro3);

	if (IMGTitleScreen)
		pd->graphics->freeBitmap(IMGTitleScreen);

	pd->system->formatString(&Filename, "skins/%s/selection", skins[skin]);
	IMGSelection = loadImageAtPath(Filename);
	pd->system->realloc(Filename, 0);


	pd->system->formatString(&Filename, "skins/%s/grid", skins[skin]);
	IMGGrid = loadImageAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/intro1", skins[skin]);
	IMGIntro1 = loadImageAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/intro2", skins[skin]);
	IMGIntro2 = loadImageAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/intro3", skins[skin]);
	IMGIntro3 = loadImageAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/titlescreen", skins[skin]);
	IMGTitleScreen = loadImageAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/background", skins[skin]);
	IMGBackground = loadImageAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/roof1", skins[skin]);
	IMGRoof1 = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/roof2", skins[skin]);
	IMGRoof2 = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/roofcornerleft", skins[skin]);
	IMGRoofCornerLeft = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/roofcornerright", skins[skin]);
	IMGRoofCornerRight = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/roofdownright", skins[skin]);
	IMGRoofDownRight = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/roofdownleft", skins[skin]);
	IMGRoofDownLeft = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/roofcornerboth", skins[skin]);
	IMGRoofCornerBoth = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/door", skins[skin]);
	IMGExit = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/floor", skins[skin]);
	IMGFloor = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/box", skins[skin]);
	IMGBox = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/player", skins[skin]);
	IMGPlayer = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/empty", skins[skin]);
	IMGEmpty = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/floorleft", skins[skin]);
	IMGFloorLeft = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/floorright", skins[skin]);
	IMGFloorRight = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/earthgrassright", skins[skin]);
	IMGEarthGrassRight = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/earthgrassleft", skins[skin]);
	IMGEarthGrassLeft = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/earthleft", skins[skin]);
	IMGEarthLeft = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/earthright", skins[skin]);
	IMGEarthRight = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/earthmiddle", skins[skin]);
	IMGEarthMiddle = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/floatingfloor", skins[skin]);
	IMGFloatingFloor = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/floatingfloorleft", skins[skin]);
	IMGFloatingFloorLeft = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/floatingfloorright", skins[skin]);
	IMGFloatingFloorRight = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/floatingfloormiddle", skins[skin]);
	IMGFloatingFloorMiddle = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/tower", skins[skin]);
	IMGTower = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/starttower", skins[skin]);
	IMGStartTower = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/towershaft", skins[skin]);
	IMGTowerShaft = loadBitmapTableAtPath(Filename);
	pd->system->realloc(Filename, 0);

}


void LoadFonts(void)
{
	Nano = loadFontAtPath("fonts/Nano Sans/Nano Sans");
	Mini = loadFontAtPath("fonts/Mini Sans/Mini Sans");
	Mini2X = loadFontAtPath("fonts/Mini Sans 2X/Mini Sans 2X");
}

void FindLevelPacksCallBack(const char* path, void* userdata)
{
	//its a directory with a name not longer than the maximum + 1 (from '/')
	size_t len = strlen(path);
	if ((len <= MaxLenLevelPackName + 1) && (path[len - 1] == '/'))
	{
		pd->system->formatString(&(LevelPacks[FoundLevelPacks]), "%s", path);
		//remove slash
		LevelPacks[FoundLevelPacks][len - 1] = '\0';
		FoundLevelPacks++;
	}
}

void FindLevelPacks(void)
{
	FoundLevelPacks = 0;
	//clear memory first
	for (int i = 0; i < MaxLevelPacks; i++)
		if (LevelPacks[i])
		{
			pd->system->realloc(LevelPacks[i], 0);
			LevelPacks[i] = NULL;
		}

	pd->file->mkdir("levels");
	pd->file->listfiles("levels", FindLevelPacksCallBack, NULL, 0);
}

void FindLevelsCallBack(const char* path, void* userdata)
{
	size_t pathlen = strlen(path);
	//see if it's a level file
	if ((pathlen == 10) || (pathlen == 11))
	{
		//if it ends with "lev"
		if (strcmp(path + (pathlen - 3), levelext) == 0)
		{
			char *level = pd->system->realloc(NULL, 6);
			memset(level, 0, 6);
			strncpy(level, path, 5);
			level[5] = '\0';
			//starts with "level"
			if (strcmp(level, levelprefix) == 0)
			{
				//check filename
				//levelx.lev
				if (pathlen == 10)
				{
					char *levelNr = pd->system->realloc(NULL, 3);
					memset(levelNr, 0, 3);
					strncpy(levelNr, path + 5, 1);
					levelNr[2] = '\0';
					int tmp = atoi(levelNr);
					if ((tmp > 0) && (tmp <= InstalledLevelsLevelEditor))
					{
						if (tmp > InstalledLevels)
							InstalledLevels = tmp;
					}
					pd->system->realloc(levelNr, 0);
				}

				//levelxx.lev
				if (pathlen == 11)
				{
					char* levelNr = pd->system->realloc(NULL, 3);
					memset(levelNr, 0, 3);
					strncpy(levelNr, path + 5, 2);
					levelNr[2] = '\0';
					int tmp = atoi(levelNr);
					if ((tmp > 0) && (tmp <= InstalledLevelsLevelEditor))
					{
						if (tmp > InstalledLevels)
							InstalledLevels = tmp;
					}
					pd->system->realloc(levelNr, 0);
				}
			}
			
			pd->system->realloc(level, 0);
		}
	}
}

void FindLevels(void)
{
	InstalledLevels = 0;
	char* path;
	if ((FoundLevelPacks > 0) && (CurrentLevelPackIndex >= 0) && (CurrentLevelPackIndex < FoundLevelPacks))
	{		
		pd->system->formatString(&path, "levels/%s", LevelPacks[CurrentLevelPackIndex]);
		pd->file->mkdir("levels");
		pd->file->mkdir(path);
		pd->file->listfiles(path, FindLevelsCallBack, NULL, 0);
		pd->system->realloc(path, 0);
		pd->system->logToConsole("%s:%d", LevelPacks[CurrentLevelPackIndex], InstalledLevels);
	}
	
}

bool StageDone(CWorldPart* Player)
{
	//this works because player is on a higher group (it is handled & found last so the exit is found first if we are at that position)
	CWorldPart* Part = CWorldParts_PartAtPosition(WorldParts, Player->PlayFieldX, Player->PlayFieldY);
	if(Part)
	{
		if(Part->Type == IDExit)
		{
			return true;
		}
	}
	return false;
}

bool AskQuestionUpdate(int* Id, bool* Answer, bool MustBeAButton)
{
	*Answer = false;
	*Id = AskingQuestionID;

	if (AskingQuestionID > -1)
	{
		if ((currButtons & kButtonA) && (!(prevButtons & kButtonA)))
		{
			*Answer = true;
			AskingQuestion = false;
			NeedRedraw = true;
			AskingQuestionID = -1;
			prevButtons = currButtons;
			playMenuSelectSound();
			return true;
		}

		if (!MustBeAButton && (currButtons & kButtonB) && (!(prevButtons & kButtonB)))
		{
			*Answer = false;
			AskingQuestion = false;
			NeedRedraw = true;
			AskingQuestionID = -1;
			prevButtons = currButtons;
			playMenuBackSound();
			return true;
		}
	}
	return false;
}

void AskQuestion(int Id, char* Msg)
{
	pd->graphics->fillRect(80, 80, 240, 80,kColorWhite);
	pd->graphics->drawRect(80, 80, 240, 80, kColorBlack);
	pd->graphics->drawRect(82, 82, 236, 76, kColorBlack);
	pd->graphics->drawText(Msg, strlen(Msg), kASCIIEncoding, 85, 85);
	prevButtons = currButtons;
	AskingQuestionID = Id;
	AskingQuestion = true;
}

void SaveSelectedLevel(void)
{
	char* Filename;
	if ((SelectedLevel > 0) && (SelectedLevel <= InstalledLevels))
	{
		if (LevelEditorMode)
		{
			pd->system->formatString(&Filename, "levels/%s/%s%d.%s", LevelPacks[CurrentLevelPackIndex], levelprefix, SelectedLevel, levelext);
			pd->system->logToConsole("%s", Filename);
		}
		else
		{
			pd->system->formatString(&Filename, "levels/%s%d.%s", levelprefix, SelectedLevel, levelext);
		}
		CWorldParts_Save(WorldParts, Filename);
		pd->system->realloc(Filename, 0);
	}
}

void SaveSelectedLevelPositional(void)
{
	char* Filename;
	if ((SelectedLevel > 0) && (SelectedLevel <= InstalledLevels))
	{
		if (LevelEditorMode)
		{
			pd->system->formatString(&Filename, "levels/%s/%s%d.%s", LevelPacks[CurrentLevelPackIndex], levelprefix, SelectedLevel, levelext);
			pd->system->logToConsole("%s", Filename);
		}
		else
		{
			pd->system->formatString(&Filename, "levels/%s%d.%s", levelprefix, SelectedLevel, levelext);
			CWorldParts_SavePositional(WorldParts, Filename);
			pd->system->realloc(Filename, 0);
		}
	}
}

void LoadSelectedLevel(void)
{
	char* Filename;
	if ((SelectedLevel > 0) && (SelectedLevel <= InstalledLevels))
	{
		if (LevelEditorMode)
		{
			pd->system->formatString(&Filename, "levels/%s/%s%d.%s", LevelPacks[CurrentLevelPackIndex], levelprefix, SelectedLevel, levelext);
			pd->system->logToConsole("%s", Filename);
			//we read from both data and file system, this way i can include people's created levelpacks in updates of the game
			//and supply my own created level pack. When saving the level is always saved to data folder and it would seem
			//the data folder also takes preference for reading the files. So this is really handy.
			CWorldParts_Load(WorldParts, Filename, kFileRead | kFileReadData);
		}
		else
		{
			pd->system->formatString(&Filename, "levels/%s%d.%s", levelprefix, SelectedLevel, levelext);
			CWorldParts_Load(WorldParts, Filename, kFileRead);
		}
		
		pd->system->realloc(Filename, 0);
	}
}


void DestroyMenuItems(void)
{
	if (menuItem1)
	{
		pd->system->removeMenuItem(menuItem1);
		menuItem1 = NULL;
	}
	if (menuItem2)
	{
		pd->system->removeMenuItem(menuItem2);
		menuItem2 = NULL;
	}
	if (menuItem3)
	{
		pd->system->removeMenuItem(menuItem3);
		menuItem3 = NULL;
	}
}


void OtherMenuItemCallback(void* userdata)
{
	//music
	if (userdata == &menuItem1)
	{
		int tmp = pd->system->getMenuItemValue(menuItem1);
		if (tmp == 0)
		{
			setMusicOnSaveState(true);
			setMusicOn(isMusicOnSaveState());
		}
		else
		{
			setMusicOnSaveState(false);
			setMusicOn(isMusicOnSaveState());
		}
		NeedRedraw = true;
	}

	//inverted colors
	if (userdata == &menuItem2)
	{
		int tmp = pd->system->getMenuItemValue(menuItem2);
		if (tmp == 0)
		{
			setInvertedSaveState(false);
			pd->display->setInverted(isInvertedSaveState());
		}
		else
		{
			setInvertedSaveState(true);
			pd->display->setInverted(isInvertedSaveState());
		}
		WorldParts->AllDirty = true;
		NeedRedraw = true;
	}

	//skin
	if (userdata == &menuItem3)
	{
		int tmp = pd->system->getMenuItemValue(menuItem3);
		setSkinSaveState(tmp);
		LoadGraphics();
		WorldParts->AllDirty = true;
		NeedRedraw = true;
	}
}

void PlayLevelIfNoErrorsFound()
{
	int errType;
	if (!LevelErrorsFound(&errType))
	{
		if(LevelEditorMode && !LevelEditorPlayMode)
			SaveSelectedLevel();
		GameState = GSGameInit;
	}
	else
	{
		if (errType == errNoPlayer)
		{
			AskQuestion(qsErrPlayer, "Can not play this level because there\nis no player in the level! Please add\na Player and try again.\n\nPress '(A)' to continue");
			DestroyMenuItems();
		}
		else if (errType == errNoExit)
		{
			AskQuestion(qsErrExit, "Can not play this level because there\nis no exit in the level! Please add an\nexit and try again.\n\nPress '(A)' to continue");
			DestroyMenuItems();
		}
		else if (errType == errBlocksPlayerNotOnAFloor)
		{
			AskQuestion(qsErrBlocksOrPlayerNotOnAFloor, "Can not play this level because there\nare boxes, players or exits not on a\nfloor!\nPlease correct this and and try again.\n\nPress '(A)' to continue");
			DestroyMenuItems();
		}
		else if (errType == errBlocksOnPlayerNotOne)
		{
			AskQuestion(qsErrBlocksOrPlayerNotOnAFloor, "Can not play this level because the\nplayer is carrying more than one box!\nPlease correct this and and try again.\n\nPress '(A)' to continue");
			DestroyMenuItems();
		}
	}
}

void LevelEditorMenuItemCallback(void* userdata)
{
	//play level
	if (userdata == &menuItem1)
	{
		PlayLevelIfNoErrorsFound();
	}

	//clear
	if (userdata == &menuItem2)
	{
		CWorldParts_RemoveAll(WorldParts);
		NeedRedraw = true;
	}

	//show info
	if (userdata == &menuItem3)
	{
		int tmp = pd->system->getMenuItemValue(menuItem3);
		if (tmp == 0)
		{
			setShowPositionSaveState(false);
			setShowGridSaveState(false);
		}

		if (tmp == 1)
		{
			setShowPositionSaveState(true);
			setShowGridSaveState(false);
		}

		if (tmp == 2)
		{
			setShowPositionSaveState(false);
			setShowGridSaveState(true);
		}

		if (tmp == 3)
		{
			setShowPositionSaveState(true);
			setShowGridSaveState(true);
		}
		WorldParts->AllDirty = true;
		NeedRedraw = true;
	}
}

void CreateLevelEditorMenuItems()
{
	//play level
	if (menuItem1 == NULL)
	{
		menuItem1 = pd->system->addMenuItem("Play", LevelEditorMenuItemCallback, &menuItem1);
	}
	
	//clear
	if (menuItem2 == NULL)
	{
		menuItem2 = pd->system->addMenuItem("Clear", LevelEditorMenuItemCallback, &menuItem2);
	}

	//show info
	if (menuItem3 == NULL)
	{
		const char* Views[] = { "None", "Info", "Grid", "Info + Grid" };
		menuItem3 = pd->system->addOptionsMenuItem("View", Views, 4, LevelEditorMenuItemCallback, &menuItem3);
		if (!ShowPositionSaveState() && !ShowGridSaveState())
		{
			pd->system->setMenuItemValue(menuItem3, 0);
		}

		if (ShowPositionSaveState() && !ShowGridSaveState())
		{
			pd->system->setMenuItemValue(menuItem3, 1);
		}

		if (!ShowPositionSaveState() && ShowGridSaveState())
		{
			pd->system->setMenuItemValue(menuItem3, 2);
		}

		if(ShowPositionSaveState() && ShowGridSaveState())
		{
			pd->system->setMenuItemValue(menuItem3, 3);
		}

	}
}



void CreateOtherMenuItems()
{	
	//music
	if (menuItem1 == NULL)
	{
		const char* onOff[] = { "On", "Off" };
		menuItem1 = pd->system->addOptionsMenuItem("Music", onOff, 2, OtherMenuItemCallback, &menuItem1);
		if(isMusicOnSaveState())
			pd->system->setMenuItemValue(menuItem1, 0);
		else
			pd->system->setMenuItemValue(menuItem1, 1);
	}	
	
	//colors 
	if (menuItem2 == NULL)
	{
		const char* normalInverted[] = { "Normal", "Inverted" };
		menuItem2 = pd->system->addOptionsMenuItem("Colors", normalInverted, 2, OtherMenuItemCallback, &menuItem2);
		if(isInvertedSaveState())
			pd->system->setMenuItemValue(menuItem2, 1);
		else
			pd->system->setMenuItemValue(menuItem2, 0);
	}
	
	//skins
	if (menuItem3 == NULL)
	{
		menuItem3 = pd->system->addOptionsMenuItem("Skin", skins, MAXSKINS, OtherMenuItemCallback, &menuItem3);
		pd->system->setMenuItemValue(menuItem3, skin);
	}
}

void GameMenuItemCallback(void* userdata)
{
	//restart
	if (userdata == &menuItem1)
	{
		LoadSelectedLevel();
		WorldParts->AllDirty = true;
		FreeView = false;
		NeedRedraw = true;
	}

	//freeview
	if (userdata == &menuItem2)
	{
		FreeView = true;
		NeedRedraw = true;
	}

	//level editor / skins
	if (userdata == &menuItem3)
	{
		if (LevelEditorMode && !LevelEditorPlayMode)
		{
			GameState = GSLevelEditorInit;
		}
		else
		{
			int tmp = pd->system->getMenuItemValue(menuItem3);
			setSkinSaveState(tmp);
			//can't reload immediatly, the callback could have
			//happened during draw commands and it would
			//make the graphics be mixed so need todo it 
			//during the gameloop itself before starting drawing
			NeedToReloadGraphics = true;
		}
		
	}
}

void CreateGameMenuItems()
{
	//restart
	if (menuItem1 == NULL)
	{
		menuItem1 = pd->system->addMenuItem("Restart Level", GameMenuItemCallback, &menuItem1);
	}

	//Free view
	if (menuItem2 == NULL)
	{
		menuItem2 = pd->system->addMenuItem("Free View", GameMenuItemCallback, &menuItem2);
	}

	//level editor / skins
	if (menuItem3 == NULL)
	{
		if (LevelEditorMode && !LevelEditorPlayMode)
		{
			menuItem3 = pd->system->addMenuItem("Level Editor", GameMenuItemCallback, &menuItem3);
		}
		else
		{
			menuItem3 = pd->system->addOptionsMenuItem("Skin", skins, MAXSKINS, GameMenuItemCallback, &menuItem3);
			pd->system->setMenuItemValue(menuItem3, skin);
		}
	}
}

bool LevelErrorsFound(int* ErrorType)
{
	int NumPlayer = 0, NumExit = 0, NumBlocksNotFloor = 0, NumExitsNotFloor = 0, NumPlayerNotFloor = 0, NumBlocksOnPlayerNotOne = 0;
	CWorldPart* Part;

	*ErrorType = errNoError;

	if(WorldParts->Player)
	{
		NumPlayer++;
		Part = CWorldParts_PartAtPosition(WorldParts, WorldParts->Player->PlayFieldX, WorldParts->Player->PlayFieldY + 1);
		if (Part == NULL)
			NumPlayerNotFloor++;

		Part = CWorldParts_PartAtPosition(WorldParts, WorldParts->Player->PlayFieldX, WorldParts->Player->PlayFieldY - 1);
		if (Part != NULL)
		{
			if (Part->Group == GroupBox)
			{
				Part = CWorldParts_PartAtPosition(WorldParts, WorldParts->Player->PlayFieldX, WorldParts->Player->PlayFieldY - 2);
				if (Part != NULL)
				{
					if (Part->Group == GroupBox)
						NumBlocksOnPlayerNotOne++;
				}
			}
		}
	}
	
	for (unsigned Teller = 0; Teller < WorldParts->ItemCount; Teller++)
	{

		if (WorldParts->Items[Teller]->Type == IDExit)
			NumExit++;

		if (WorldParts->Items[Teller]->Group == GroupBox)
		{
			Part = CWorldParts_PartAtPosition(WorldParts, WorldParts->Items[Teller]->PlayFieldX, WorldParts->Items[Teller]->PlayFieldY + 1);
			if (Part == NULL)
				NumBlocksNotFloor++;
		}
		
		if (WorldParts->Items[Teller]->Group == GroupExit)
		{
			Part = CWorldParts_PartAtPosition(WorldParts, WorldParts->Items[Teller]->PlayFieldX, WorldParts->Items[Teller]->PlayFieldY + 1);
			if (Part == NULL)
				NumExitsNotFloor++;
		}
	}

	if (NumPlayer == 0)
	{

		*ErrorType = errNoPlayer;
		return true;
	}

	else if (NumExit == 0)
	{
		*ErrorType = errNoExit;
		return true;
	}

	else if ((NumBlocksNotFloor > 0) || (NumPlayerNotFloor > 0) || (NumExitsNotFloor > 0))
	{
		*ErrorType = errBlocksPlayerNotOnAFloor;
		return true;
	}

	else if (NumBlocksOnPlayerNotOne > 0)
	{
		*ErrorType = errBlocksOnPlayerNotOne;
		return true;
	}

	return false;
}

void DoShowDebugInfo()
{
	if (showDebugInfo)
	{
		pd->graphics->fillRect(0, 0, WINDOW_WIDTH, 15, kColorWhite);
		pd->graphics->drawRect(0, 0, WINDOW_WIDTH, 15, kColorBlack);
		pd->graphics->drawRect(0, 0, WINDOW_WIDTH, 15, kColorBlack);
		pd->graphics->setFont(Mini);
		char* Text;
		pd->system->formatString(&Text, "vmin:%d,%d vmax:%d,%d C:%d B:%d F:%d D:%d D2:%d M:%d A:%d A2:%d", WorldParts->ViewPort->VPMinX, WorldParts->ViewPort->VPMinY, WorldParts->ViewPort->VPMaxX, WorldParts->ViewPort->VPMaxY, WorldParts->ItemCount, CWorldParts_GroupCount(WorldParts, GroupBox), CWorldParts_GroupCount(WorldParts, GroupFloor), WorldParts->DrawCount, WorldParts->DirtyClearedCount, WorldParts->NumPartsMoving, WorldParts->NumPartsAttachedToPlayer, WorldParts->AllDirtyCount);
		pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 4, 4);
		pd->system->realloc(Text, 0);
	}
}

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
			if(!LevelEditorPlayMode)
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

	int id;
	bool answer;
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

char* GetString(int Id, int x, int y,char* Msg, size_t MaxLen)
{
	char* Result = NULL;
	if (MaxLen > 0)
	{
		GetStringX = x;
		GetStringY = y;
		AskingGetString = true;
		GetStringId = Id;
		pd->graphics->drawText(Msg, strlen(Msg), kASCIIEncoding, x, y);
		prevButtons = currButtons;
		MaxLenGetString = MaxLen;
		Result = pd->system->realloc(NULL, MaxLen+1);
		if(Result)
			memset(Result, 0, MaxLen + 1);
	}
	else
	{
		GetStringId = -1;
		AskingGetString = false;
		GetStringX = 0;
		GetStringY = 0;
		MaxLenGetString = 0;
	}
	return Result;
}

void getStringDraw(char* StringBuffer, bool ErasingPrevious)
{
	char* Buffer;
	char* text;
	size_t len = strlen(StringBuffer);
	Buffer = pd->system->realloc(NULL, len + 2);
	memset(Buffer, 0, len + 2);
	strcpy(Buffer, StringBuffer);
	Buffer[len - 1] = '[';
	Buffer[len] = StringBuffer[len - 1];
	Buffer[len + 1] = ']';
	Buffer[len + 2] = '\0';

	if (ErasingPrevious)
	{
		pd->graphics->pushContext(NULL);
		pd->graphics->setDrawMode(kDrawModeNXOR);
	}
	pd->system->formatString(&text, "\n%s\n(DPad):Select\n(A):Ok (B):Cancel", Buffer);
	pd->graphics->drawText(text, strlen(text), kASCIIEncoding, GetStringX, GetStringY);
	pd->system->realloc(text, 0);
	if (ErasingPrevious)
	{
		pd->graphics->popContext();
	}
	pd->system->realloc(Buffer, 0);
}

bool getStringUpdate(int *Id, bool* Answered, char* StringBuffer)
{
	*Id = GetStringId;
	*Answered = false;

	if (GetStringId == -1)
		return false;

	if (StringBuffer == NULL)
		return false;
	
	size_t len = strlen(StringBuffer);
	if (len == 0)
	{
		StringBuffer[0] = 'a';
		getStringDraw(StringBuffer, false);
		DestroyMenuItems();
	}
	

	if ((currButtons & kButtonB) && (!(prevButtons & kButtonB)))
	{
		memset(StringBuffer, 0, len);
		*Answered = false;
		NeedRedraw = true;
		GetStringId = -1;
		AskingGetString = false;
		playMenuBackSound();
		return true;
	}

	if ((currButtons & kButtonA) && (!(prevButtons & kButtonA)))
	{
		*Answered = true;
		NeedRedraw = true;
		GetStringId = -1;
		AskingGetString = false;
		playMenuSelectSound();
		return true;
	}

	if ((currButtons & kButtonUp) && (!(prevButtons & kButtonUp)))
	{
		getStringDraw(StringBuffer, true);
		char val = StringBuffer[len - 1];
		if ((val < 'z'))
			val++;
		else
			val = 'a';
		StringBuffer[len - 1] = val;
		getStringDraw(StringBuffer, false);
		playMenuSound();
	}

	if ((currButtons & kButtonDown) && (!(prevButtons & kButtonDown)))
	{
		getStringDraw(StringBuffer, true);
		char val = StringBuffer[len - 1];
		if ((val > 'a'))
			val--;
		else
			if (val == 'a')
				val = 'z';
		StringBuffer[len - 1] = val;
		getStringDraw(StringBuffer, false);
		playMenuSound();
	}

	if ((currButtons & kButtonLeft) && (!(prevButtons & kButtonLeft)))
	{
		if (len > 1)
		{
			getStringDraw(StringBuffer, true);
			StringBuffer[len - 1] = '\0';
			getStringDraw(StringBuffer, false);
			playMenuSound();
		}
	}

	if ((currButtons & kButtonRight) && (!(prevButtons & kButtonRight)))
	{
		if ((len < MaxLenGetString))
		{
			getStringDraw(StringBuffer, true);
			StringBuffer[len] = 'a';
			getStringDraw(StringBuffer, false);
			playMenuSound();
		}
	}

	return false;
}

void TitleScreenInit(void)
{
	CreateOtherMenuItems();
	SelectMusic(musTitle);
	NeedRedraw = true;
	//in case we come back from the level editor and had created
	//a new level in a new pack we need to refind those levels.
	if (titleStep == tsLevelEditorMode)
	{
		FindLevels();
		if (InstalledLevels > 0)
			titleSelection = lmPlayMode;
		else
			titleSelection = lmEditMode;
	}
}

void TitleScreen()
{

	if (GameState == GSTitleScreenInit)
	{
		TitleScreenInit();
		GameState -= GSDiff;
	}
	
	if (!AskingGetString)
	{
		if ((currButtons & kButtonLeft) && (!(prevButtons & kButtonLeft)))
		{
			switch (titleStep)
			{
			case tsSelectPack:
				switch (titleSelection)
				{
				case spPack:
					CurrentLevelPackIndex--;
					if (CurrentLevelPackIndex < 0)
						CurrentLevelPackIndex = FoundLevelPacks - 1;
					playMenuSelectSound();
					NeedRedraw = true;
					break;
				default:
					break;
				}
			default:
				break;
			}
		}

		if ((currButtons & kButtonRight) && (!(prevButtons & kButtonRight)))
		{
			switch (titleStep)
			{
			case tsSelectPack:
				switch (titleSelection)
				{
				case spPack:
					CurrentLevelPackIndex++;
					if (CurrentLevelPackIndex == FoundLevelPacks)
						CurrentLevelPackIndex = 0;
					playMenuSelectSound();
					NeedRedraw = true;
					break;
				default:
					break;
				}
			default:
				break;
			}
		}


		if ((currButtons & kButtonDown) && (!(prevButtons & kButtonDown)))
		{
			switch (titleStep)
			{
			case tsMainMenu:
				if (titleSelection < mmCount - 1)
				{
					titleSelection++;
					playMenuSound();
					NeedRedraw = true;
				}
				break;
			case tsOptions:
				if (titleSelection < opCount - 1)
				{
					titleSelection++;
					playMenuSound();
					NeedRedraw = true;
				}
				break;
			case tsLevelEditorMode:
				if (InstalledLevels > 0)
				{
					if (titleSelection < lmCount - 1)
					{
						titleSelection++;
						playMenuSound();
						NeedRedraw = true;
					}
				}
				else
					titleSelection = lmEditMode;
				break;
			case tsSelectPack:
				if (FoundLevelPacks > 0)
				{
					if (titleSelection < spCount - 1)
					{
						titleSelection++;
						playMenuSound();
						NeedRedraw = true;
					}
				}
				else
					titleSelection = spCreate;
				break;
			}
		}

		if ((currButtons & kButtonUp) && (!(prevButtons & kButtonUp)))
		{
			switch (titleStep)
			{
			case tsMainMenu:
			case tsOptions:
				if (titleSelection > 0)
				{
					titleSelection--;
					playMenuSound();
					NeedRedraw = true;
				}
				break;
			case tsLevelEditorMode:
				if (InstalledLevels > 0)
				{
					if (titleSelection > 0)
					{
						titleSelection--;
						playMenuSound();
						NeedRedraw = true;
					}
				}
				else
					titleSelection = lmEditMode;
				break;			
			case tsSelectPack:
				if (FoundLevelPacks > 0)
				{
					if (titleSelection > 0)
					{
						titleSelection--;
						playMenuSound();
						NeedRedraw = true;
					}
				}
				else
					titleSelection = spCreate;
				break;
			}
		}

		if ((currButtons & kButtonB) && (!(prevButtons & kButtonB)))
		{
			switch (titleStep)
			{
			case tsOptions:
				titleStep = tsMainMenu;
				titleSelection = mmOptions;
				playMenuBackSound();
				NeedRedraw = true;
				break;
			case tsCredits:
				titleStep = tsMainMenu;
				titleSelection = mmCredits;
				playMenuBackSound();
				NeedRedraw = true;
				break;
			case tsLevelEditorMode:
				titleStep = tsSelectPack;
				titleSelection = spPack;
				playMenuBackSound();
				NeedRedraw = true;
				break;
			case tsSelectPack:
				titleStep = tsMainMenu;
				titleSelection = mmLevelEditor;
				playMenuBackSound();
				NeedRedraw = true;
			}
		}

		if ((currButtons & kButtonA) && (!(prevButtons & kButtonA)))
		{
			switch (titleStep)
			{
			case tsMainMenu:
				switch (titleSelection)
				{
				case mmLevelEditor:
					LevelEditorMode = true;
					FindLevelPacks();
					titleStep = tsSelectPack;
					if (FoundLevelPacks > 0)
					{
						titleSelection = spPack;
					}
					else
					{
						titleSelection = spCreate;
					}
					playMenuSelectSound();
					NeedRedraw = true;
					break;
				case mmStartGame:
					InstalledLevels = InstalledLevelsDefaultGame;
					if (InstalledLevels > 0)
					{
						LevelEditorMode = false;
						SelectedLevel = lastUnlockedLevel();
						GameState = GSStageSelectInit;
						playMenuSelectSound();
					}
					break;
				case mmCredits:
					titleStep = tsCredits;
					playMenuSelectSound();
					NeedRedraw = true;
					break;
				case mmOptions:
					titleStep = tsOptions;
					titleSelection = opMusic;
					playMenuSelectSound();
					NeedRedraw = true;
					break;
				}
				break;
			case tsOptions:
				switch (titleSelection)
				{
				case opMusic:
					playMenuSelectSound();
					setMusicOn(!isMusicOn());
					setMusicOnSaveState(isMusicOn());
					if (menuItem1)
					{
						if (isMusicOnSaveState())
							pd->system->setMenuItemValue(menuItem1, 0);
						else
							pd->system->setMenuItemValue(menuItem1, 1);
					}
					NeedRedraw = true;
					break;
				case opSound:
					playMenuSelectSound();
					setSoundOn(!isSoundOn());
					setSoundOnSaveState(isSoundOn());
					NeedRedraw = true;
					break;
				case opSkin:
					playMenuSelectSound();
					int i = skinSaveState();
					i++;
					if (i == MAXSKINS)
						i = 0;
					setSkinSaveState(i);
					LoadGraphics();
					if (menuItem3)
					{
						if (isMusicOnSaveState())
							pd->system->setMenuItemValue(menuItem3, 0);
						else
							pd->system->setMenuItemValue(menuItem3, 1);
					}
					NeedRedraw = true;
					break;
				case opInverted:
					playMenuSelectSound();
					setInvertedSaveState(!isInvertedSaveState());
					pd->display->setInverted(isInvertedSaveState());
					if (menuItem2)
					{
						if (isInvertedSaveState())
							pd->system->setMenuItemValue(menuItem2, 1);
						else
							pd->system->setMenuItemValue(menuItem2, 0);
					}
					NeedRedraw = true;
					break;
				}
				break;
			case tsCredits:
				titleStep = tsMainMenu;
				titleSelection = mmCredits;
				playMenuSelectSound();
				NeedRedraw = true;
				break;
			case tsLevelEditorMode:
				LevelEditorPlayMode = titleSelection == lmPlayMode;
				if (!LevelEditorPlayMode)
				{
					InstalledLevels = InstalledLevelsLevelEditor;
				}
				SelectedLevel = 1;
				GameState = GSStageSelectInit;
				playMenuSelectSound();
				break;
			case tsSelectPack:
				switch (titleSelection)
				{
				case spCreate:
					DrawBitmapSrcRec(IMGTitleScreen, 101, 71, 101, 71, 198, 93, kBitmapUnflipped);
					pd->graphics->fillRect(101, 71, 198, 93, kColorXOR);
					pd->graphics->setDrawMode(kDrawModeNXOR);
					char text[] = "Pack Name:";
					GetStringResult = GetString(1, 105, 80, text, MaxLenLevelPackName);
					break;
				case spDelete:
					char* path;
					pd->system->formatString(&path, "levels/%s", LevelPacks[CurrentLevelPackIndex]);
					pd->file->unlink(path, 1);
					pd->system->realloc(path, 0);
					FindLevelPacks();
					if (FoundLevelPacks == 0)
						titleSelection = spCreate;
					CurrentLevelPackIndex = 0;
					NeedRedraw = 1;
					break;
				case spOptimize:
					break;
				case spPack:
					FindLevels();
					if (InstalledLevels > 0)
						titleSelection = lmPlayMode;
					else
						titleSelection = lmEditMode;
					titleStep = tsLevelEditorMode;
					playMenuSelectSound();
					NeedRedraw = true;
					break;
				}
				break;
			}
		}
	}
	
	if (NeedRedraw)
	{
		NeedRedraw = false;
		pd->graphics->drawBitmap(IMGTitleScreen, 0, 0, kBitmapUnflipped);
		pd->graphics->fillRect(97, 67, 206, 101, kColorXOR);
		pd->graphics->drawRect(100, 70, 200, 95, kColorXOR);
		pd->graphics->setDrawMode(kDrawModeNXOR);
		char* Text = NULL;
		switch (titleStep)
		{
		case tsMainMenu:
			pd->system->formatString(&Text, "Start Game\nLevel Editor\nOptions\nCredits\n");
			pd->graphics->setFont(Mini2X);
			pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 140, 80);
			pd->system->realloc(Text, 0);
			switch (titleSelection)
			{
			case mmStartGame:
				pd->system->formatString(&Text, ">");
				break;
			case mmLevelEditor:
				pd->system->formatString(&Text, "\n>");
				break;
			case mmOptions:
				pd->system->formatString(&Text, "\n\n>");
				break;
			case mmCredits:
				pd->system->formatString(&Text, "\n\n\n>");
				break;
			}
			pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 125, 80);
			pd->system->realloc(Text, 0);
			break;
		case tsCredits:
			pd->graphics->setFont(Mini);
			pd->system->formatString(&Text, "Blockdude was created by\nWillems Davy. Fonts by\nDonald Hays. Tech skin and\nDefault skin by Fusion Power.\nFlat skin by Klas Kroon & Kris\nKatiesen,\nMusic By DonSkeeto.\nLevels from blockman by\nSoleau Software.");
			pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 108, 74);
			pd->system->realloc(Text, 0);
			break;
		case tsLevelEditorMode:
			pd->graphics->setFont(Mini2X);
			if (InstalledLevels > 0)
				pd->graphics->drawText("Play Mode", strlen("Play Mode"), kASCIIEncoding, 140, 80);
			pd->graphics->drawText("Edit Mode", strlen("Edit Mode"), kASCIIEncoding, 140, 100);
			switch (titleSelection)
			{
			case lmPlayMode:
				pd->graphics->drawText(">", 1, kASCIIEncoding, 125, 80);
				break;
			case lmEditMode:
				pd->graphics->drawText(">", 1, kASCIIEncoding, 125, 100);
				break;
			default:
				break;
			}
			break;
		case tsSelectPack:
			if (FoundLevelPacks > 0)
			{
				pd->graphics->setFont(Mini2X);
				char* text;
				pd->system->formatString(&text, "Pack:%s", LevelPacks[CurrentLevelPackIndex]);
				pd->graphics->drawText(text, strlen(text), kASCIIEncoding, 120, 80);
				pd->system->realloc(text, 0);
			}
			
			pd->graphics->drawText("Create Pack", strlen("Create Pack"), kASCIIEncoding, 120, 100);
		
			if (FoundLevelPacks > 0)
			{
				pd->graphics->drawText("Del Pack", strlen("Del Pack"), kASCIIEncoding, 120, 120);
			}
			
			if (FoundLevelPacks > 0)
			{
				pd->graphics->drawText("Optimize Pack", strlen("Optimize Pack"), kASCIIEncoding, 120, 140);
			}

			switch (titleSelection)
			{
			case spPack:
				pd->graphics->drawText(">", 1, kASCIIEncoding, 105, 80);
				break;
			case spCreate:
				pd->graphics->drawText(">", 1, kASCIIEncoding, 105, 100);
				break;
			case spDelete:
				pd->graphics->drawText(">", 1, kASCIIEncoding, 105, 120);
				break;
			case spOptimize:
				pd->graphics->drawText(">", 1, kASCIIEncoding, 105, 140);
				break;
			}
			break;
		case tsOptions:
			pd->graphics->setFont(Mini2X);
			if (isMusicOn())
			{
				pd->graphics->drawText("Music On", strlen("music On"), kASCIIEncoding, 140, 80);
			}
			else
			{
				pd->graphics->drawText("Music Off", strlen("Music Off"), kASCIIEncoding, 140, 80);
			}

			if (isSoundOn())
			{
				pd->graphics->drawText("Sound On", strlen("Sound On"), kASCIIEncoding, 140, 100);
			}
			else
			{
				pd->graphics->drawText("Sound Off", strlen("Sound Off"), kASCIIEncoding, 140, 100);
			}

			pd->system->formatString(&Text, "%s skin", skins[skinSaveState()]);
			pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 140, 120);
			pd->system->realloc(Text, 0);

			if (isInvertedSaveState())
			{
				pd->graphics->drawText("Inverted", strlen("Inverted"), kASCIIEncoding, 140, 140);
			}
			else
			{
				pd->graphics->drawText("Normal", strlen("Normal"), kASCIIEncoding, 140, 140);
			}
			switch (titleSelection)
			{
			case opMusic:
				pd->graphics->drawText(">", 1, kASCIIEncoding, 125, 80);
				break;
			case opSound:
				pd->graphics->drawText(">", 1, kASCIIEncoding, 125, 100);
				break;
			case opSkin:
				pd->graphics->drawText(">", 1, kASCIIEncoding, 125, 120);
				break;
			case opInverted:
				pd->graphics->drawText(">", 1, kASCIIEncoding, 125, 140);
				break;
			}
			break;

		}
		pd->graphics->setDrawMode(kDrawModeCopy);
	}
	int id;
	bool answered;
	if (getStringUpdate(&id, &answered, GetStringResult))
	{
		if(answered)
		{ 
			char* path;
			pd->system->logToConsole("%s", GetStringResult);
			pd->file->mkdir("levels");
			pd->system->formatString(&path, "levels/%s", GetStringResult);
			pd->file->mkdir(path);
			pd->system->realloc(path, 0);
			FindLevelPacks();
			if (FoundLevelPacks > 0)
			{
				for (int i = 0; i < FoundLevelPacks; i++)
				{
					if (strcmp(LevelPacks[i], GetStringResult) == 0)
					{
						CurrentLevelPackIndex = i;
						titleSelection = spPack;
						break;
					}
				}
			}			
		}
		pd->system->realloc(GetStringResult, 0);
		GetStringResult = NULL;
		pd->graphics->setDrawMode(kDrawModeCopy);
		CreateOtherMenuItems();
	}
}

void GameInit(void)
{
	FreeView = false;
	NeedRedraw = true;
	DestroyMenuItems();
	CreateGameMenuItems();
	CWorldParts_FindPlayer(WorldParts);
	CWorldParts_LimitVPLevel(WorldParts);
	WorldParts->AllDirty = true;
}

void Game(void)
{
	if (GameState == GSGameInit)
	{
		GameInit();
		GameState -= GSDiff;
	}

	if (!FreeView && !AskingQuestion && ((currButtons & kButtonB) && (!(prevButtons & kButtonB)))) 
	{
		DestroyMenuItems();
		playMenuBackSound();
		char* Text;
		if (LevelEditorMode && !LevelEditorPlayMode)
			pd->system->formatString(&Text, "Do you want to quit playing the\ncurrent level and return to the level\neditor?\n\nPress (A) to quit, (B) to keep playing", SelectedLevel, InstalledLevels);
		else
			pd->system->formatString(&Text, "Do you want to quit playing the\ncurrent level and return to the level\nselector?\n\nPress (A) to quit, (B) to keep playing", SelectedLevel, InstalledLevels);
		AskQuestion(qsQuitPlaying, Text);
		pd->system->realloc(Text, 0);
	}

	if (FreeView)
	{
		if (((currButtons & kButtonB) && (!(prevButtons & kButtonB))) ||
			((currButtons & kButtonA) && (!(prevButtons & kButtonA))))
		{
			FreeView = false;
			CWorldParts_CenterVPOnPlayer(WorldParts);
			NeedRedraw = true;
		}
	}
	else
	{
		if (!AskingQuestion && !WorldParts->Player->IsMoving && !WorldParts->AttchedBoxQuedOrMoving)
		{
			//pickup 
			if ((currButtons & kButtonA) && (!(prevButtons & kButtonA)))
			{
				//dropping a block
				//if there is a block on top of the player and were facing left				
				if (WorldParts->NumBoxesAttachedToPlayer > 0)
				{
					CWorldPart* Part = CWorldParts_PartAtPosition(WorldParts, WorldParts->Player->PlayFieldX, WorldParts->Player->PlayFieldY - 1);
					if (Part)
					{
						if (Part->Group == GroupBox)
						{
							if (WorldParts->Player->AnimBase == AnimBaseLeft)
							{
								// and it can move to the left
								if ((CWorldPart_CanMoveTo(Part, Part->PlayFieldX - 1, Part->PlayFieldY)))
								{
									//move it to the left
									CWorldPart_AddToMoveQue(Part, Part->PlayFieldX - 1, Part->PlayFieldY);
									CWorldPart_AddToMoveQue(Part, Part->PlayFieldX - 1, Part->PlayFieldY + 1);
									//detaching is set automatically otherwise it would be set too early while the block is still detaching
									//CWorldPart_DeattachFromPlayer(WorldParts->Items[teller]);
									//NeedRedraw = true;
									playDropSound();
								}
							}
							else
							{
								// if there is block on top of theplayer were facing right
								if (WorldParts->Player->AnimBase == AnimBaseRight)
								{
									// and it can move to the left
									if ((CWorldPart_CanMoveTo(Part, Part->PlayFieldX + 1, Part->PlayFieldY)))
									{
										//move it to right
										CWorldPart_AddToMoveQue(Part, Part->PlayFieldX + 1, Part->PlayFieldY);
										CWorldPart_AddToMoveQue(Part, Part->PlayFieldX + 1, Part->PlayFieldY + 1);
										//detaching is set automatically otherwise it would be set too early while the block is still detaching
										//CWorldPart_DeattachFromPlayer(WorldParts->Items[teller]);
										//NeedRedraw = true;
										playDropSound();
									}

								}
							}
						}
					}
				}
				else
				{
					if (WorldParts->NumBoxesAttachedToPlayer == 0)
					{
						bool FloorFound = false;
						//picking up a block
						//if there is a block left to the player and were facing left
						if (WorldParts->Player->AnimBase == AnimBaseLeft)
						{
							CWorldPart* Part = CWorldParts_PartAtPosition(WorldParts, WorldParts->Player->PlayFieldX - 1, WorldParts->Player->PlayFieldY);
							if (Part)
							{
								if (Part->Group == GroupBox)
								{
									//see if there is a floor or block beneath the block
									CWorldPart* Part2 = CWorldParts_PartAtPosition(WorldParts, WorldParts->Player->PlayFieldX - 1, WorldParts->Player->PlayFieldY + 1);
									if (Part2)
									{
										if ((Part2->Group == GroupFloor) || (Part2->Group == GroupBox) || (Part2->Group == GroupExit))
										{
											FloorFound = true;
										}
									}

									if (Part->PlayFieldY == NrOfRows - 1)
									{
										FloorFound = true;
									}

									if (FloorFound)
									{
										//if there was see if there is space above the block and above the player
										if ((CWorldPart_CanMoveTo(Part, Part->PlayFieldX, Part->PlayFieldY - 1)) &&
											(CWorldPart_CanMoveTo(Part, Part->PlayFieldX + 1, Part->PlayFieldY - 1)))
										{
											//Attach the block to the player & move the block
											CWorldPart_AttachToPlayer(Part, WorldParts->Player);
											CWorldPart_AddToMoveQue(Part, Part->PlayFieldX, Part->PlayFieldY - 1);
											CWorldPart_AddToMoveQue(Part, Part->PlayFieldX + 1, Part->PlayFieldY - 1);
											//NeedRedraw = true;
											playPickupSound();
										}
									}
								}
							}
						}
						else
						{
							if (WorldParts->Player->AnimBase == AnimBaseRight)
							{
								CWorldPart* Part = CWorldParts_PartAtPosition(WorldParts, WorldParts->Player->PlayFieldX + 1, WorldParts->Player->PlayFieldY);
								if (Part)
								{
									if (Part->Group == GroupBox)
									{
										//see if there is a floor or block beneath the block
										CWorldPart* Part2 = CWorldParts_PartAtPosition(WorldParts, WorldParts->Player->PlayFieldX + 1, WorldParts->Player->PlayFieldY + 1);
										if (Part2)
										{
											if ((Part2->Group == GroupFloor) || (Part2->Group == GroupBox) || (Part2->Group == GroupExit))
											{
												FloorFound = true;
											}
										}


										if (Part->PlayFieldY == NrOfRows - 1)
										{
											FloorFound = true;
										}

										if (FloorFound)
										{
											//if there was see if there is space above the block and above the player
											if (CWorldPart_CanMoveTo(Part, Part->PlayFieldX, Part->PlayFieldY - 1) &&
												CWorldPart_CanMoveTo(Part, Part->PlayFieldX - 1, Part->PlayFieldY - 1))
											{
												//Attach the block to the player & move the block
												CWorldPart_AttachToPlayer(Part, WorldParts->Player);
												CWorldPart_AddToMoveQue(Part, Part->PlayFieldX, Part->PlayFieldY - 1);
												CWorldPart_AddToMoveQue(Part, Part->PlayFieldX - 1, Part->PlayFieldY - 1);
												//NeedRedraw = true;
												playPickupSound();
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	if (FreeView)
	{
		if (currButtons & kButtonLeft)
		{
			if (CViewPort_Move(WorldParts->ViewPort, -ViewportMove, 0))
			{
				WorldParts->AllDirty = WorldParts->LevelBitmap == NULL;
				NeedRedraw = true;
			}
		}
		if (currButtons & kButtonRight)
		{
			if (CViewPort_Move(WorldParts->ViewPort, ViewportMove, 0))
			{
				WorldParts->AllDirty = WorldParts->LevelBitmap == NULL;
				NeedRedraw = true;
			}
		}
		if (currButtons & kButtonUp)
		{
			if (CViewPort_Move(WorldParts->ViewPort, 0, -ViewportMove))
			{
				WorldParts->AllDirty = WorldParts->LevelBitmap == NULL;
				NeedRedraw = true;
			}
		}
		if (currButtons & kButtonDown)
		{
			if (CViewPort_Move(WorldParts->ViewPort, 0, ViewportMove))
			{
				WorldParts->AllDirty = WorldParts->LevelBitmap == NULL;
				NeedRedraw = true;
			}
		}
	}
	else
	{
		//need to have a input delay, its too taxing otherwise
		framecounter++;
		if (framecounter >= FrameDelayInput)
		{
			framecounter = 0;

			if (!AskingQuestion && !WorldParts->Player->IsMoving && !WorldParts->AttchedBoxQuedOrMoving)
			{

				//move up
				if (currButtons & kButtonUp)
				{
					NeedRedraw |= CWorldPart_MoveTo(WorldParts->Player, WorldParts->Player->PlayFieldX, WorldParts->Player->PlayFieldY - 1);
				}

				if (currButtons & kButtonLeft)
				{
					NeedRedraw |= CWorldPart_MoveTo(WorldParts->Player, WorldParts->Player->PlayFieldX - 1, WorldParts->Player->PlayFieldY);
				}

				if (currButtons & kButtonRight)
				{
					NeedRedraw |= CWorldPart_MoveTo(WorldParts->Player, WorldParts->Player->PlayFieldX + 1, WorldParts->Player->PlayFieldY);
				}
			}
		}
	}
	

	if (!AskingQuestion)
	{
		NeedRedraw |=  CWorldParts_Move(WorldParts) || NeedToReloadGraphics;
		if (NeedRedraw)
		{
			NeedRedraw = false;

			//need to happen here just before drawing & clearing everything
			//otherwise alldirty could have been reset depending on when 
			//the menu callback fired
			if (NeedToReloadGraphics)
			{
				LoadGraphics();
				NeedToReloadGraphics = false;
				WorldParts->AllDirty = true;
			}
			if (WorldParts->AllDirty)
			{
				if (WorldParts->LevelBitmap)
				{
					pd->graphics->pushContext(WorldParts->LevelBitmap);
				}
				if ((skinSaveState() == 1) || (skinSaveState() == 4))
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
			}
			CWorldParts_ClearDirty(WorldParts, ((skinSaveState() == 1) || (skinSaveState() == 4)));
			CWorldParts_Draw(WorldParts, ((skinSaveState() == 1) || (skinSaveState() == 4)));
			if (WorldParts->LevelBitmap)
			{
				DrawBitmapSrcRec(WorldParts->LevelBitmap, 0, 0, WorldParts->ViewPort->MinScreenX, WorldParts->ViewPort->MinScreenY, WINDOW_WIDTH, WINDOW_HEIGHT, kBitmapUnflipped);
			}
			if (FreeView)
			{
				pd->graphics->fillRect(0, 0, WINDOW_WIDTH, 15, kColorWhite);
				pd->graphics->drawRect(0, 0, WINDOW_WIDTH, 15, kColorBlack);
				pd->graphics->drawRect(0, 0, WINDOW_WIDTH, 15, kColorBlack);
				pd->graphics->setFont(Mini);
				char* Text;
				pd->system->formatString(&Text, "Freeview mode: Use dpad to move around (A) or (B) to exit", SelectedLevel, InstalledLevels);
				pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 4, 4);
				pd->system->realloc(Text, 0);
			}
		}
	}

	if (!AskingQuestion && !WorldParts->Player->IsMoving && StageDone(WorldParts->Player))
	{
		//to one extra move & draw to make sure boxes are on final spot
		CWorldParts_Move(WorldParts);
		if (WorldParts->AllDirty)
		{
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

		}
		CWorldParts_ClearDirty(WorldParts, ((skinSaveState() == 1) || (skinSaveState() == 4)));
		CWorldParts_Draw(WorldParts, ((skinSaveState() == 1) || (skinSaveState() == 4)));
		if (WorldParts->LevelBitmap)
		{
			DrawBitmapSrcRec(WorldParts->LevelBitmap, 0, 0, WorldParts->ViewPort->MinScreenX, WorldParts->ViewPort->MinScreenY, WINDOW_WIDTH, WINDOW_HEIGHT, kBitmapUnflipped);
		}

		playLevelDoneSound();

		if (!LevelEditorMode && (SelectedLevel == lastUnlockedLevel()))
		{
			if (lastUnlockedLevel() < InstalledLevels)
			{
				char* Text;
				pd->system->formatString(&Text, "Congratulations !\n\nYou Succesfully Solved Level %d/%d\nThe next level has now been unlocked!\n\nPress (A) to continue", SelectedLevel, InstalledLevels);
				AskQuestion(qsSolvedNotLastLevel, Text);
				pd->system->realloc(Text, 0);
				DestroyMenuItems();
			}
			else
			{
				char* Text;
				pd->system->formatString(&Text, "Congratulations !\n\nYou Succesfully Solved Level %d/%d\nAll levels are now finished!\n\nPress (A) to continue", SelectedLevel, InstalledLevels);
				AskQuestion(qsSolvedLastLevel, Text);
				pd->system->realloc(Text, 0);
				DestroyMenuItems();
			}
		}
		else
		{
			char* Text;
			pd->system->formatString(&Text, "Congratulations !\n\nYou Succesfully Solved Level %d/%d\n\nPress (A) to continue", SelectedLevel, InstalledLevels);
			AskQuestion(qsSolvedLevel, Text);
			pd->system->realloc(Text, 0);
			DestroyMenuItems();
		}

	}

	int id;
	bool answer;
	//simple confirm messages
	if ((AskingQuestionID == qsSolvedNotLastLevel) || (AskingQuestionID == qsSolvedLastLevel) || (AskingQuestionID == qsSolvedLevel))
	{
		if (AskQuestionUpdate(&id, &answer, true))
		{
			if ((id == qsSolvedNotLastLevel) && answer)
			{
				SelectedLevel++;
				unlockLevel(SelectedLevel);
				GameState = GSStageSelectInit;
			}

			if ((id == qsSolvedLastLevel) && answer)
			{
				GameState = GSTitleScreenInit;
			}

			if ((id == qsSolvedLevel) && answer)
			{
				if (LevelEditorMode && !LevelEditorPlayMode)
				{
					GameState = GSLevelEditorInit;
				}
				else
				{
					GameState = GSStageSelectInit;
				}
			}
		}
	}

	//Yes / No Questions
	if (AskingQuestionID == qsQuitPlaying)
	{
		if (AskQuestionUpdate(&id, &answer, false))
		{
			if (id == qsQuitPlaying)
			{
				if (answer)
				{
					if (LevelEditorMode && !LevelEditorPlayMode)
					{
						GameState = GSLevelEditorInit;
					}
					else
					{
						GameState = GSStageSelectInit;
					}
				}
				else
				{
					CreateGameMenuItems();
					WorldParts->AllDirty = true;
				}
			}
		}
	}


	DoShowDebugInfo();
}

void LevelEditorInit(void)
{
	framecounter = 0;
	NeedRedraw = true;	
	DestroyMenuItems();
	CreateLevelEditorMenuItems();
	LoadSelectedLevel();
	WorldParts->AllDirty = true;
	
	if(WorldParts->Player)
	{
		CSelector_SetPosition(Selector, WorldParts->Player->PlayFieldX, WorldParts->Player->PlayFieldY);
	}

	CViewPort_SetVPLimit(WorldParts->ViewPort, 0, 0, NrOfCols - 1, NrOfRows - 1);
	if (WorldParts->Player == NULL)
	{
		CSelector_SetPosition(Selector, WorldParts->ViewPort->VPMinX + ((NrOfColsVisible) >> 1), WorldParts->ViewPort->VPMinY + ((NrOfRowsVisible) >> 1));
	}
	
	
}

void LevelEditor(void)
{	
	if (GameState == GSLevelEditorInit)
	{
		LevelEditorInit();
		GameState -= GSDiff;
	}

	if (NeedRedraw)
	{
		NeedRedraw = false;
		//always redraw everything in case of none levelbitmap mode
		WorldParts->AllDirty |= WorldParts->LevelBitmap == NULL;
		if (WorldParts->AllDirty)
		{
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
		}

		CWorldParts_ClearDirty(WorldParts, ((skinSaveState() == 1) || (skinSaveState() == 4)));
		CWorldParts_Draw(WorldParts, ((skinSaveState() == 1) || (skinSaveState() == 4)));
		if (WorldParts->LevelBitmap)
		{
			DrawBitmapSrcRec(WorldParts->LevelBitmap, 0, 0, WorldParts->ViewPort->MinScreenX, WorldParts->ViewPort->MinScreenY, WINDOW_WIDTH, WINDOW_HEIGHT, kBitmapUnflipped);
		}
		CSelector_Draw(Selector);
		//in case of bitmap mode always redraw the tile at the selector
		if (WorldParts->LevelBitmap)
		{
			CWorldPart* Part = CWorldParts_PartAtPosition(WorldParts, Selector->Part->PlayFieldX, Selector->Part->PlayFieldY);
			if (Part)
			{
				CWorldParts_AddDirty(WorldParts, Part);
			}
		}

		if (ShowGridSaveState())
			pd->graphics->drawBitmap(IMGGrid, 0, 0, kBitmapUnflipped);

		if (ShowPositionSaveState())
		{
			pd->graphics->fillRect(0, 0, WINDOW_WIDTH, 15, kColorWhite);
			pd->graphics->drawRect(0, 0, WINDOW_WIDTH, 15, kColorBlack);
			pd->graphics->drawRect(0, 0, WINDOW_WIDTH, 15, kColorBlack);
			pd->graphics->setFont(Mini);
			int BlockBelowSelector = CWorldParts_TypeAtPosition(WorldParts, Selector->Part->PlayFieldX, Selector->Part->PlayFieldY);
			char* Text;
			pd->system->formatString(&Text, "Pos: %d,%d - Selector: %s / %s", Selector->Part->PlayFieldX, Selector->Part->PlayFieldY, blockNames[Selector->Part->Type], blockNames[BlockBelowSelector]);
			pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 4, 4);
			pd->system->realloc(Text, 0);
		}
	}

	unsigned int crankResult = crankUpdate();
	if (!AskingQuestion && (crankResult == CRANKMOVELEFT))
	{
		CSelector_DecSelection(Selector);
		NeedRedraw = true;
		WorldParts->AllDirty = WorldParts->LevelBitmap == NULL;
	}

	if (!AskingQuestion && (crankResult == CRANKMOVERIGHT))
	{
		CSelector_IncSelection(Selector);
		NeedRedraw = true;
		WorldParts->AllDirty = WorldParts->LevelBitmap == NULL;
	}

	if (!AskingQuestion && (currButtons & kButtonA) && (!(prevButtons & kButtonA)))
	{
		switch (Selector->Selection)
		{
		case IDEmpty:
			CWorldParts_Remove(WorldParts, Selector->Part->PlayFieldX, Selector->Part->PlayFieldY);
			//clear graphics at selector in case of bitmap mode
			if (WorldParts->LevelBitmap)
			{
				if (WorldParts->LevelBitmap)
				{
					pd->graphics->pushContext(WorldParts->LevelBitmap);
				}
				if (((skinSaveState() == 1) || (skinSaveState() == 4)))
				{
					pd->graphics->fillRect(Selector->Part->PlayFieldX * TileWidth, Selector->Part->PlayFieldY * TileHeight, TileWidth, TileHeight, kColorBlack);
				}
				else
				{
					pd->graphics->fillRect(Selector->Part->PlayFieldX * TileWidth, Selector->Part->PlayFieldY * TileHeight, TileWidth, TileHeight, kColorWhite);
				}

				if (WorldParts->LevelBitmap)
				{
					pd->graphics->popContext();
				}
			}
			else
			{
				//need to redraw everything in this case to clear the erased part
				WorldParts->AllDirty = WorldParts->LevelBitmap == NULL;
			}
			break;
		case IDPlayer:
			CWorldParts_Remove(WorldParts, Selector->Part->PlayFieldX, Selector->Part->PlayFieldY);
			CWorldParts_RemoveType(WorldParts, Selector->Part->Type);
			CWorldParts_Add(WorldParts, CWorldPart_create(Selector->Part->PlayFieldX, Selector->Part->PlayFieldY, Selector->Part->Type, Selector->Part->Group));
			//need to redraw everything in this case to clear previous player position
			WorldParts->AllDirty = true;
			break;
		case IDBox:
		case IDFloor:
		case IDExit:
		case IDEarthGrassLeft:
		case IDEarthGrassRight:
		case IDEarthLeft:
		case IDEarthMiddle:
		case IDEarthRight:
		case IDFloatingFloor:
		case IDFloatingFloorLeft:
		case IDFloatingFloorMiddle:
		case IDFloatingFloorRight:
		case IDFloorLeft:
		case IDFloorRight:
		case IDTower:
		case IDStartTower:
		case IDTowerShaft:
		case IDRoof1:
		case IDRoof2:
		case IDRoofCornerLeft:
		case IDRoofCornerRight:
		case IDRoofCornerBoth:
		case IDRoofDownRight:
		case IDRoofDownLeft:
			CWorldParts_Remove(WorldParts, Selector->Part->PlayFieldX, Selector->Part->PlayFieldY);
			CWorldParts_Add(WorldParts, CWorldPart_create(Selector->Part->PlayFieldX, Selector->Part->PlayFieldY, Selector->Part->Type, Selector->Part->Group));
			break;
		}
		//in case of bitmap mode always redraw the tile at the selector
		if (WorldParts->LevelBitmap)
		{
			CWorldPart* Part = CWorldParts_PartAtPosition(WorldParts, Selector->Part->PlayFieldX, Selector->Part->PlayFieldY);
			if (Part)
			{
				CWorldParts_AddDirty(WorldParts, Part);
			}
		}
		NeedRedraw = true;
	}

	framecounter++;
	if (!AskingQuestion && (framecounter >= FrameDelayInputLevelEditor))
	{
		framecounter = 0;
		if (currButtons & kButtonLeft)
		{
			NeedRedraw = CSelector_MoveLeft(Selector);
			if (Selector->Part->PlayFieldX < WorldParts->ViewPort->VPMinX + 3)
				if (CViewPort_Move(WorldParts->ViewPort, -TileWidth, 0))
				{
					WorldParts->AllDirty = WorldParts->LevelBitmap == NULL;
					NeedRedraw = true;
				}
			
		}

		if (currButtons & kButtonRight)
		{
			NeedRedraw = CSelector_MoveRight(Selector);			
			if (Selector->Part->PlayFieldX > WorldParts->ViewPort->VPMaxX - 3)
				if (CViewPort_Move(WorldParts->ViewPort, TileWidth, 0))
				{
					WorldParts->AllDirty = WorldParts->LevelBitmap == NULL;
					NeedRedraw = true;
				}
		}

		if (currButtons & kButtonUp)
		{
			NeedRedraw = CSelector_MoveUp(Selector);
			if (Selector->Part->PlayFieldY < WorldParts->ViewPort->VPMinY + 3)
				if (CViewPort_Move(WorldParts->ViewPort, 0, -TileWidth))
				{
					WorldParts->AllDirty = WorldParts->LevelBitmap == NULL;
					NeedRedraw = true;
				}
		}

		if (currButtons & kButtonDown)
		{
			NeedRedraw = CSelector_MoveDown(Selector);
			if (Selector->Part->PlayFieldY > WorldParts->ViewPort->VPMaxY - 3)
				if (CViewPort_Move(WorldParts->ViewPort, 0, TileWidth))
				{
					WorldParts->AllDirty = WorldParts->LevelBitmap == NULL;
					NeedRedraw = true;
				}
		}
	}

	if (!AskingQuestion && (currButtons & kButtonB))
	{
		SaveSelectedLevel();
		GameState = GSStageSelectInit;
	}

	int id;
	bool answer;
	if (AskQuestionUpdate(&id, &answer, true))
	{
		if (answer)
		{
			CreateLevelEditorMenuItems();
			WorldParts->AllDirty = true;
		}
	
	}

	DoShowDebugInfo();
}


void IntroInit(void)
{
	NeedRedraw = true;
}

void Intro(void)
{
	if (GameState == GSIntroInit)
	{
		IntroInit();
		GameState -= GSDiff;
	}
	framecounter++;

	if (((currButtons & kButtonA) && (!(prevButtons & kButtonA))) || 
		((currButtons & kButtonB) && (!(prevButtons & kButtonB))))
	{
		GameState = GSTitleScreenInit;
	}

	if (currButtons & kButtonUp)
	{
		debugMode = true;
	}

	if (currButtons & kButtonDown)
	{
		showDebugInfo = true;
	}

	if (NeedRedraw)
	{
		NeedRedraw = false;
		switch (IntroScreenNr)
		{
		case 1:
			pd->graphics->drawBitmap(IMGIntro1, 0, 0, kBitmapUnflipped);
			break;
		case 2:
			pd->graphics->drawBitmap(IMGIntro2, 0, 0, kBitmapUnflipped);
			break;
		case 3:
			pd->graphics->drawBitmap(IMGIntro3, 0, 0, kBitmapUnflipped);
			break;
		}
	}

	if (framecounter > FRAMERATE * 3)
	{
		framecounter = 0;
		IntroScreenNr++;
		NeedRedraw = true;
		if (IntroScreenNr > 3)
			GameState = GSTitleScreenInit;
	}
}