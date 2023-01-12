#include <stdlib.h>
#include "commonvars.h"
#include "sound.h"
#include "savestate.h"
#include "crank.h"
#include "game.h"
#include "cviewport.h"
#include "cworldpart.h"
#include "cWorldParts.h"

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

bool StageDone(CWorldPart* Player)
{
	bool Temp = false;
	for (int Teller = 0; Teller < WorldParts->ItemCount; Teller++)
		if (WorldParts->Items[Teller]->Type == IDExit)
		{
			if ((WorldParts->Items[Teller]->PlayFieldX == Player->PlayFieldX) && (WorldParts->Items[Teller]->PlayFieldY == Player->PlayFieldY))
				Temp = true;
			break;
		}
	return Temp;
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
			playMenuSelectSound();
			return true;
		}

		if (!MustBeAButton && (currButtons & kButtonB) && (!(prevButtons & kButtonB)))
		{
			*Answer = false;
			AskingQuestion = false;
			NeedRedraw = true;
			AskingQuestionID = -1;
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

CWorldPart* FindPlayer()
{
	CWorldPart* Player = NULL;
	for (int teller = 0; teller < WorldParts->ItemCount; teller++)
	{
		if (WorldParts->Items[teller]->Type == IDPlayer)
		{
			Player = WorldParts->Items[teller];
			break;
		}
	}
	return Player;
}

void LoadSelectedLevel(void)
{
	char* Filename;
	if ((SelectedLevel > 0) && (SelectedLevel <= InstalledLevels))
	{
		pd->system->formatString(&Filename, "levels/level%d.lev", SelectedLevel);
		CWorldParts_Load(WorldParts, Filename);
		ThePlayer = FindPlayer();
		pd->system->realloc(Filename, 0);
	}
}

void OtherMenuItemCallback(void* userdata)
{
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
		NeedRedraw = true;
	}

	if (userdata == &menuItem3)
	{
		int tmp = pd->system->getMenuItemValue(menuItem3);
		setSkinSaveState(tmp);
		LoadGraphics();
		NeedRedraw = true;
	}
}

void CreateOtherMenuItems()
{
	const char* onOff[] = { "On", "Off" };
	if (menuItem1 == NULL)
	{
		menuItem1 = pd->system->addOptionsMenuItem("Music", onOff, 2, OtherMenuItemCallback, &menuItem1);
		if(isMusicOnSaveState())
			pd->system->setMenuItemValue(menuItem1, 0);
		else
			pd->system->setMenuItemValue(menuItem1, 1);
	}
	
	const char* normalInverted[] = { "Normal", "Inverted" };
	if (menuItem2 == NULL)
	{
		menuItem2 = pd->system->addOptionsMenuItem("Colors", normalInverted, 2, OtherMenuItemCallback, &menuItem2);
		if(isInvertedSaveState())
			pd->system->setMenuItemValue(menuItem2, 1);
		else
			pd->system->setMenuItemValue(menuItem2, 0);
	}
	
	if (menuItem3 == NULL)
	{
		menuItem3 = pd->system->addOptionsMenuItem("Skin", skins, 3, OtherMenuItemCallback, &menuItem3);
		pd->system->setMenuItemValue(menuItem3, skin);
	}
}

void GameMenuItemCallback(void* userdata)
{
	if (userdata == &menuItem1)
	{
		LoadSelectedLevel();
		NeedRedraw = true;
	}

	if (userdata == &menuItem2)
	{
		FreeView = true;
		NeedRedraw = true;
	}

	if (userdata == &menuItem3)
	{
		int tmp = pd->system->getMenuItemValue(menuItem3);
		setSkinSaveState(tmp);
		LoadGraphics();
		NeedRedraw = true;
	}
}

void CreateGameMenuItems()
{
	if (menuItem1 == NULL)
	{
		menuItem1 = pd->system->addMenuItem("Restart Level", GameMenuItemCallback, &menuItem1);
	}
	if (menuItem2 == NULL)
	{
		menuItem2 = pd->system->addMenuItem("Free View", GameMenuItemCallback, &menuItem2);
	}
	if (menuItem3 == NULL)
	{
		menuItem3 = pd->system->addOptionsMenuItem("Skin", skins, 3, GameMenuItemCallback, &menuItem3);
		pd->system->setMenuItemValue(menuItem3, skin);
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



void StageSelectInit()
{

	pd->graphics->setFont(Mini);
	LoadSelectedLevel();
	NeedRedraw = true;
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
		if (SelectedLevel <= lastUnlockedLevel())
			GameState = GSGameInit;
		else
		{
			char* Text;
			pd->system->formatString(&Text, "This Level Hasn't been unlocked yet!\nDo you want to play the last unlocked\nlevel %d/%d?\n\nPress (A) to Play (B) to cancel", lastUnlockedLevel(), InstalledLevels);
			AskQuestion(1, Text);
			pd->system->realloc(Text, 0);
			DestroyMenuItems();
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
	}

	if (!AskingQuestion && (currButtons & kButtonRight) && (!(prevButtons & kButtonRight)))
	{
		playMenuSound();
		NeedRedraw = true;
		SelectedLevel++;
		if (SelectedLevel > InstalledLevels)
			SelectedLevel = InstalledLevels;
		LoadSelectedLevel();
	}

	int id;
	bool answer;
	if (AskQuestionUpdate(&id, &answer, false))
	{
		if (id == 1)
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
			}
		}
	}
	

	if (NeedRedraw)
	{
		NeedRedraw = false;
		char* Text;
		pd->graphics->drawBitmap(IMGBackground, 0, 0, kBitmapUnflipped);
		CWorldParts_Draw(WorldParts);
		pd->graphics->fillRect(0, 0, WINDOW_WIDTH, 15, kColorWhite);
		pd->graphics->drawRect(0, 0, WINDOW_WIDTH, 15, kColorBlack);
		if (SelectedLevel <= lastUnlockedLevel())
			pd->system->formatString(&Text, "Level: %d/%d - (A) Play Level - (B) Titlescreen", SelectedLevel, InstalledLevels);
		else
			pd->system->formatString(&Text, "Level: %d/%d - Level is locked! - (B) Titlescreen", SelectedLevel, InstalledLevels);

		pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 4, 4);
		pd->system->realloc(Text, 0);
	}
}

void TitleScreenInit(void)
{
	CreateOtherMenuItems();
	SelectMusic(musTitle);
	NeedRedraw = true;
}

void TitleScreen()
{

	if (GameState == GSTitleScreenInit)
	{
		TitleScreenInit();
		GameState -= GSDiff;
	}

	if ((currButtons & kButtonDown) && (!(prevButtons & kButtonDown)))
	{
		switch (titleStep)
		{
		case tsMainMenu:
			if (titleSelection < mmCount -1)
			{
				titleSelection++;
				playMenuSound();
				NeedRedraw = true;
			}
			break;
		case tsOptions:
			if (titleSelection < opCount -1)
			{
				titleSelection++;
				playMenuSound();
				NeedRedraw = true;
			}
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
		}
	}

	if ((currButtons & kButtonA) && (!(prevButtons & kButtonA)))
	{
		switch (titleStep)
		{
		case tsMainMenu:
			switch (titleSelection)
			{
			case mmStartGame:
				if (InstalledLevels > 0)
				{
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
			pd->system->formatString(&Text, "Start Game\nOptions\nCredits\n");
			pd->graphics->setFont(Mini2X);
			pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 140, 90);
			pd->system->realloc(Text, 0);
			switch (titleSelection)
			{
			case mmStartGame:
				pd->system->formatString(&Text, ">>");
				break;
			case mmOptions:
				pd->system->formatString(&Text, "\n>>");
				break;
			case mmCredits:
				pd->system->formatString(&Text, "\n\n>>");
				break;
			}
			pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 115, 90);
			pd->system->realloc(Text, 0);
			break;
		case tsCredits:
			pd->graphics->setFont(Mini);
			pd->system->formatString(&Text, "Blockdude was created by\nWillems Davy. Fonts by\nDonald Hays. Tech skin by\nFusion Power. Default skin by\nKlas Kroon & Kris Katiesen,\nmodified by Fusion Power.\nMusic By DonSkeeto.\nLevels from blockman by\nSoleau Software.");
			pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 108, 74);
			pd->system->realloc(Text, 0);
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

			pd->system->formatString(&Text, "Skin: %s", skins[skinSaveState()]);
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
				pd->graphics->drawText(">>", strlen(">>"), kASCIIEncoding, 115, 80);
				break;
			case opSound:
				pd->graphics->drawText(">>", strlen(">>"), kASCIIEncoding, 115, 100);
				break;
			case opSkin:
				pd->graphics->drawText(">>", strlen(">>"), kASCIIEncoding, 115, 120);
				break;
			case opInverted:
				pd->graphics->drawText(">>", strlen(">>"), kASCIIEncoding, 115, 140);
				break;
			}
			break;

		}
		pd->graphics->setDrawMode(kDrawModeCopy);
	}
}

void GameInit(void)
{
	CWorldParts_LimitVPLevel(WorldParts);
	ThePlayer = FindPlayer();
	NeedRedraw = true;
	DestroyMenuItems();
	CreateGameMenuItems();
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
		pd->system->formatString(&Text, "Do you want to quit playing the\ncurrent level and return to the level\nselector?\n\nPress (A) to quit, (B) to keep playing", SelectedLevel, InstalledLevels);
		AskQuestion(4, Text);
		pd->system->realloc(Text, 0);
	}

	bool BoxMoving = false;
	//find out if a box is moving or if a box is being carried by the player
	bool CarryingBox = false;
	bool Que = false;
	bool Moving = false;
	for (int teller = 0; teller < WorldParts->ItemCount; teller++)
	{
		if (WorldParts->Items[teller]->IsMoving)
		{
			Moving = true;

			if (WorldParts->Items[teller]->Type == IDBox)
			{
				BoxMoving = true;
			}
		}

		if (WorldParts->Items[teller]->Type == IDBox)
		{
			if (WorldParts->Items[teller]->AttachedToPlayer)
			{
				CarryingBox = true;
			}		
		}

		if (CWorldPart_MovesInQue(WorldParts->Items[teller]))
			Que = true;
	}

	if (FreeView)
	{
		if ((currButtons & kButtonB) && (!(prevButtons & kButtonB)) || 
			(currButtons & kButtonA) && (!(prevButtons & kButtonA)))
		{
			FreeView = false;
			CWorldParts_CenterVPOnPlayer(WorldParts);
			NeedRedraw = true;
		}

		if (currButtons & kButtonLeft)
		{
			CViewPort_Move(WorldParts->ViewPort, -2, 0);
			NeedRedraw = true;
		}
		if (currButtons & kButtonRight)
		{
			CViewPort_Move(WorldParts->ViewPort, 2, 0);
			NeedRedraw = true;
		}
		if (currButtons & kButtonUp)
		{
			CViewPort_Move(WorldParts->ViewPort, 0, -2);
			NeedRedraw = true;
		}
		if (currButtons & kButtonDown)
		{
			CViewPort_Move(WorldParts->ViewPort, 0, 2);
			NeedRedraw = true;
		}
	}
	else
	if (!AskingQuestion && !ThePlayer->IsMoving && !BoxMoving && !Que)
	{

		//move up
		if (currButtons & kButtonUp)
		{
			CWorldPart_MoveTo(ThePlayer, ThePlayer->PlayFieldX, ThePlayer->PlayFieldY - 1, false);
			NeedRedraw = true;
		}
		//pickup 
		if (((currButtons & kButtonA) && (!(prevButtons & kButtonA))))
		{
			for (int teller = 0; teller < WorldParts->ItemCount; teller++)
				//dropping a block
			{   //if there is a block on top of the player and were facing left
				if (CarryingBox)
				{
					if ((WorldParts->Items[teller]->PlayFieldX == ThePlayer->PlayFieldX) &&
						(WorldParts->Items[teller]->PlayFieldY == ThePlayer->PlayFieldY - 1) &&
						(WorldParts->Items[teller]->Type == IDBox) && (ThePlayer->AnimBase == AnimBaseLeft))
					{  
						// and it can move to the left
						if ((CWorldPart_CanMoveTo(WorldParts->Items[teller], WorldParts->Items[teller]->PlayFieldX - 1, WorldParts->Items[teller]->PlayFieldY)))
						{
							//move it to the left
							CWorldPart_AddToMoveQue(WorldParts->Items[teller], WorldParts->Items[teller]->PlayFieldX - 1, WorldParts->Items[teller]->PlayFieldY);
							CWorldPart_AddToMoveQue(WorldParts->Items[teller], WorldParts->Items[teller]->PlayFieldX - 1, WorldParts->Items[teller]->PlayFieldY + 1);
							CWorldPart_DeattachFromPlayer(WorldParts->Items[teller]);
							NeedRedraw = true;
						}
					}
					else // if there is block on top of theplayer were facing right
						if ((WorldParts->Items[teller]->PlayFieldX == ThePlayer->PlayFieldX) &&
							(WorldParts->Items[teller]->PlayFieldY == ThePlayer->PlayFieldY - 1) &&
							(WorldParts->Items[teller]->Type == IDBox) && (ThePlayer->AnimBase == AnimBaseRight))
						{   //and it can be moved to the right
							if ((CWorldPart_CanMoveTo(WorldParts->Items[teller], WorldParts->Items[teller]->PlayFieldX + 1, WorldParts->Items[teller]->PlayFieldY)))
							{
								//move it to right
								CWorldPart_AddToMoveQue(WorldParts->Items[teller], WorldParts->Items[teller]->PlayFieldX + 1, WorldParts->Items[teller]->PlayFieldY);
								CWorldPart_AddToMoveQue(WorldParts->Items[teller], WorldParts->Items[teller]->PlayFieldX + 1, WorldParts->Items[teller]->PlayFieldY + 1);
								CWorldPart_DeattachFromPlayer(WorldParts->Items[teller]);
								NeedRedraw = true;
							}

						}
				}
				else
					if (!CarryingBox)
					{
						bool FloorFound = false;
						//picking up a block
						//if there is a block left to the player and were facing left
						if ((WorldParts->Items[teller]->PlayFieldX == ThePlayer->PlayFieldX - 1) &&
							(WorldParts->Items[teller]->PlayFieldY == ThePlayer->PlayFieldY) &&
							(WorldParts->Items[teller]->Type == IDBox) && (ThePlayer->AnimBase == AnimBaseLeft))
						{
							//see if there is a floor or block beneath the block
							for (int teller2 = 0; teller2 < WorldParts->ItemCount; teller2++)
							{
								if ((WorldParts->Items[teller2]->PlayFieldX == ThePlayer->PlayFieldX - 1) && (WorldParts->Items[teller2]->PlayFieldY == ThePlayer->PlayFieldY + 1) &&
									((WorldParts->Items[teller2]->Group == GroupFloor) || (WorldParts->Items[teller2]->Group == GroupBox)))
								{
									FloorFound = true;
									break;
								}
							}
							if (FloorFound)
								//if there was see if there is space above the block and above the player
								if ((CWorldPart_CanMoveTo(WorldParts->Items[teller], WorldParts->Items[teller]->PlayFieldX, WorldParts->Items[teller]->PlayFieldY - 1)) &&
									(CWorldPart_CanMoveTo(WorldParts->Items[teller], WorldParts->Items[teller]->PlayFieldX + 1, WorldParts->Items[teller]->PlayFieldY - 1)))
								{
									//Attach the block to the player & move the block
									CWorldPart_AttachToPlayer(WorldParts->Items[teller], ThePlayer);
									CWorldPart_AddToMoveQue(WorldParts->Items[teller], WorldParts->Items[teller]->PlayFieldX, WorldParts->Items[teller]->PlayFieldY - 1);
									CWorldPart_AddToMoveQue(WorldParts->Items[teller], WorldParts->Items[teller]->PlayFieldX + 1, WorldParts->Items[teller]->PlayFieldY - 1);
									NeedRedraw = true;
								}
						}
						else
							//if there is a block right to the player and were facing right
							if ((WorldParts->Items[teller]->PlayFieldX == ThePlayer->PlayFieldX + 1) &&
								(WorldParts->Items[teller]->PlayFieldY == ThePlayer->PlayFieldY) &&
								(WorldParts->Items[teller]->Type == IDBox) && (ThePlayer->AnimBase == AnimBaseRight))
							{
								//see if there is a floor or block beneath the block
								for (int teller2 = 0; teller2 < WorldParts->ItemCount; teller2++)
								{
									if ((WorldParts->Items[teller2]->PlayFieldX == ThePlayer->PlayFieldX + 1) && (WorldParts->Items[teller2]->PlayFieldY == ThePlayer->PlayFieldY + 1) &&
										((WorldParts->Items[teller2]->Group == GroupFloor) || (WorldParts->Items[teller2]->Group == GroupBox)))
									{
										FloorFound = true;
										break;
									}
								}
								if (FloorFound)
									//if there was see if there is space above the block and above the player
									if (CWorldPart_CanMoveTo(WorldParts->Items[teller], WorldParts->Items[teller]->PlayFieldX, WorldParts->Items[teller]->PlayFieldY - 1) &&
										CWorldPart_CanMoveTo(WorldParts->Items[teller], WorldParts->Items[teller]->PlayFieldX - 1, WorldParts->Items[teller]->PlayFieldY - 1))
									{
										//Attach the block to the player & move the block
										CWorldPart_AttachToPlayer(WorldParts->Items[teller], ThePlayer);
										CWorldPart_AddToMoveQue(WorldParts->Items[teller], WorldParts->Items[teller]->PlayFieldX, WorldParts->Items[teller]->PlayFieldY - 1);
										CWorldPart_AddToMoveQue(WorldParts->Items[teller], WorldParts->Items[teller]->PlayFieldX - 1, WorldParts->Items[teller]->PlayFieldY - 1);
										NeedRedraw = true;
									}
							}
					}
			}
		}
		if (currButtons & kButtonLeft)
		{
			CWorldPart_MoveTo(ThePlayer, ThePlayer->PlayFieldX - 1, ThePlayer->PlayFieldY, false);
			NeedRedraw = true;
		}
		if (currButtons & kButtonRight)
		{
			CWorldPart_MoveTo(ThePlayer, ThePlayer->PlayFieldX + 1, ThePlayer->PlayFieldY, false);
			NeedRedraw = true;
		}

	}

	NeedRedraw = NeedRedraw || Moving || Que;

	//need to draw and move one more time to draw final state and make boxes drop down further
	//otherwise there is a hickup while keeping moving with the player in the animation
	//or boxes not being fully on the ground or dropping further
	if (!AskingQuestion && !NeedRedraw && (framecounter > 0))
	{
		framecounter--;
		pd->graphics->drawBitmap(IMGBackground, 0, 0, kBitmapUnflipped);
		CWorldParts_Draw(WorldParts);
		CWorldParts_Move(WorldParts);
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

	
	if (!AskingQuestion && NeedRedraw)
	{
		NeedRedraw = false;
		framecounter = 1;
		pd->graphics->drawBitmap(IMGBackground, 0, 0, kBitmapUnflipped);
		CWorldParts_Draw(WorldParts);
		CWorldParts_Move(WorldParts);
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
	


	if (!AskingQuestion && !ThePlayer->IsMoving && StageDone(ThePlayer))
	{
		playLevelDoneSound();

		if (SelectedLevel == lastUnlockedLevel())
		{
			if (lastUnlockedLevel() < InstalledLevels)
			{
				char* Text;
				pd->system->formatString(&Text, "Congratulations !\n\nYou Succesfully Solved Level %d/%d\nThe next level has now been unlocked!\n\nPress (A) to continue", SelectedLevel, InstalledLevels);
				AskQuestion(1, Text);
				pd->system->realloc(Text, 0);
				DestroyMenuItems();
			}
			else
			{
				char* Text;
				pd->system->formatString(&Text, "Congratulations !\n\nYou Succesfully Solved Level %d/%d\nAll levels are now finished!\n\nPress (A) to continue", SelectedLevel, InstalledLevels);
				AskQuestion(2, Text);
				pd->system->realloc(Text, 0);
				DestroyMenuItems();
			}
		}
		else
		{
			char* Text;
			pd->system->formatString(&Text, "Congratulations !\n\nYou Succesfully Solved Level %d/%d\n\nPress (A) to continue", SelectedLevel, InstalledLevels);
			AskQuestion(3, Text);
			pd->system->realloc(Text, 0);
			DestroyMenuItems();
		}

	}

	int id;
	bool answer;
	//simple confirm messages
	if ((AskingQuestionID >= 1) && (AskingQuestionID <= 3))
	{
		if (AskQuestionUpdate(&id, &answer, true))
		{
			if ((id == 1) && answer)
			{
				SelectedLevel++;
				unlockLevel(SelectedLevel);
				GameState = GSStageSelectInit;
			}

			if ((id == 2) && answer)
			{
				GameState = GSTitleScreenInit;
			}

			if ((id == 3) && answer)
			{
				GameState = GSStageSelectInit;
			}
		}
	}

	//Yes / No Questions
	if (AskingQuestionID == 4)
	{
		if (AskQuestionUpdate(&id, &answer, false))
		{
			if (id == 4)
			{
				if (answer)
				{
					GameState = GSStageSelectInit;
				}
				else
				{
					CreateGameMenuItems();
				}
			}
		}
	}



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
