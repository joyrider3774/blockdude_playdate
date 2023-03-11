#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "commonvars.h"
#include "sound.h"
#include "savestate.h"
#include "crank.h"
#include "gamefuncs.h"
#include "cviewport.h"
#include "cworldpart.h"
#include "cworldparts.h"
#include "cselector.h"
#include "menus.h"
#include "pd_api.h"
#include "pd_helperfuncs.h"
#include "crank.h"

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

	if (IMGIntro1)
		pd->graphics->freeBitmap(IMGIntro1);

	if (IMGIntro2)
		pd->graphics->freeBitmap(IMGIntro2);

	if (IMGIntro3)
		pd->graphics->freeBitmap(IMGIntro3);
	
	if (IMGIntro4)
		pd->graphics->freeBitmap(IMGIntro4);

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

	if (IMGIntro1)
		pd->graphics->freeBitmap(IMGIntro1);

	if (IMGIntro2)
		pd->graphics->freeBitmap(IMGIntro2);

	if (IMGIntro3)
		pd->graphics->freeBitmap(IMGIntro3);
	
	if (IMGIntro4)
		pd->graphics->freeBitmap(IMGIntro4);

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

	pd->system->formatString(&Filename, "skins/%s/intro4", skins[skin]);
	IMGIntro4 = loadImageAtPath(Filename);
	pd->system->realloc(Filename, 0);

	pd->system->formatString(&Filename, "skins/%s/titlescreen", skins[skin]);
	IMGTitleScreen = loadImageAtPath(Filename);
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
	}
	
}

bool AskQuestionUpdate(int* Id, bool* Answer, bool MustBeAButton)
{
	*Answer = false;
	*Id = AskingQuestionID;

	if (AskingQuestionID > -1)
	{
		unsigned int crankResult = crankUpdate();
		if (((currButtons & kButtonA) && (!(prevButtons & kButtonA))) || (crankResult == CRANKMOVERIGHT))
		{
			*Answer = true;
			AskingQuestion = false;
			NeedRedraw = true;
			AskingQuestionID = -1;
			prevButtons = currButtons;
			playMenuSelectSound();
			return true;
		}

		if (!MustBeAButton && (((currButtons & kButtonB) && (!(prevButtons & kButtonB))) || (crankResult == CRANKMOVELEFT)))
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
	pd->graphics->fillRect(80, 80, 240, 80, kColorWhite);
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
			AskQuestion(qsErrPlayer, "Can not play this level because there\nis no player in the level! Please add\na Player and try again.\n\nPress (A) to continue");
			DestroyMenuItems();
		}
		else if (errType == errNoExit)
		{
			AskQuestion(qsErrExit, "Can not play this level because there\nis no exit in the level! Please add an\nexit and try again.\n\nPress (A) to continue");
			DestroyMenuItems();
		}
		else if (errType == errBlocksPlayerNotOnAFloor)
		{
			AskQuestion(qsErrBlocksOrPlayerNotOnAFloor, "Can not play this level because there\nare boxes, players or exits not on a\nfloor!\nPlease correct this and and try again.\n\nPress (A) to continue");
			DestroyMenuItems();
		}
		else if (errType == errBlocksOnPlayerNotOne)
		{
			AskQuestion(qsErrBlocksOrPlayerNotOnAFloor, "Can not play this level because the\nplayer is carrying more than one box!\nPlease correct this and and try again.\n\nPress (A) to continue");
			DestroyMenuItems();
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

//will fill up level gaps and remove empty levels so all levels are increasing by 1 with no gaps
void OptimizeLevelPack(char* Pack)
{
	int SavedLevel = 1;
	char* CurrentFilename, *SavedFilename;
	FileStat stat;
	for (int CurrentLevel = 1; CurrentLevel <= InstalledLevelsLevelEditor; CurrentLevel++)
	{
		pd->system->formatString(&CurrentFilename, "levels/%s/%s%d.%s", Pack, levelprefix, CurrentLevel, levelext);
		pd->system->formatString(&SavedFilename, "levels/%s/%s%d.%s", Pack, levelprefix, SavedLevel, levelext);
		int ret = pd->file->stat(CurrentFilename, &stat);
		//no error so file is found
		if (ret == 0)
		{
			if (!stat.isdir && (stat.size > 0))
			{
				if (SavedLevel < CurrentLevel)
					pd->file->rename(CurrentFilename, SavedFilename);
				SavedLevel++;
			}
			//empty level has 0 size so delete it but don't increase savedLevel
			else if (stat.size == 0)
			{
				pd->file->unlink(CurrentFilename, 0);
				//check if it is not a level in the included level pack if so need to inc SavedLevel As well
				if (pd->file->stat(CurrentFilename, &stat) == 0)
				{
					SavedLevel++;
				}
			}
		}
		pd->system->realloc(CurrentFilename, 0);
		pd->system->realloc(SavedFilename, 0);
	}
}

void DoShowDebugInfo()
{
	if (showDebugInfo)
	{
		pd->graphics->pushContext(NULL);
		pd->graphics->fillRect(0, 0, WINDOW_WIDTH, 15, kColorWhite);
		pd->graphics->drawRect(0, 0, WINDOW_WIDTH, 15, kColorBlack);
		pd->graphics->drawRect(0, 0, WINDOW_WIDTH, 15, kColorBlack);
		pd->graphics->setFont(Mini);
		char* Text;
		pd->system->formatString(&Text, "vmin:%d,%d vmax:%d,%d C:%d B:%d F:%d D:%d D2:%d M:%d A:%d A2:%d", WorldParts->ViewPort->VPMinX, WorldParts->ViewPort->VPMinY, WorldParts->ViewPort->VPMaxX, WorldParts->ViewPort->VPMaxY, WorldParts->ItemCount, CWorldParts_GroupCount(WorldParts, GroupBox), CWorldParts_GroupCount(WorldParts, GroupFloor), WorldParts->DrawCount, WorldParts->DirtyClearedCount, WorldParts->NumPartsMoving, WorldParts->NumPartsAttachedToPlayer, WorldParts->AllDirtyCount);
		pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 4, 4);
		pd->system->realloc(Text, 0);
		pd->graphics->popContext();
	}
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
	
	unsigned int crankResult = crankUpdate();
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

	if (((currButtons & kButtonUp) && (!(prevButtons & kButtonUp))) || (crankResult == CRANKMOVELEFT))
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

	if (((currButtons & kButtonDown) && (!(prevButtons & kButtonDown))) || (crankResult == CRANKMOVERIGHT))
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
