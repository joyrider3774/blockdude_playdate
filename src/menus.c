#include <stdint.h>
#include <stddef.h>
#include "menus.h"
#include "gamefuncs.h"
#include "commonvars.h"
#include "savestate.h"
#include "cworldparts.h"
#include "pd_api.h"
#include "sound.h"


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
		AskQuestion(qsClearLevel, "This will erase the complete level,\nthere is no undo!\n\nAre you sure you want to continue?\n\nPress (A) to continue (B) to cancel");
		DestroyMenuItems();
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

		if (ShowPositionSaveState() && ShowGridSaveState())
		{
			pd->system->setMenuItemValue(menuItem3, 3);
		}

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

void CreateOtherMenuItems()
{
	//music
	if (menuItem1 == NULL)
	{
		const char* onOff[] = { "On", "Off" };
		menuItem1 = pd->system->addOptionsMenuItem("Music", onOff, 2, OtherMenuItemCallback, &menuItem1);
		if (isMusicOnSaveState())
			pd->system->setMenuItemValue(menuItem1, 0);
		else
			pd->system->setMenuItemValue(menuItem1, 1);
	}

	//colors 
	if (menuItem2 == NULL)
	{
		const char* normalInverted[] = { "Normal", "Inverted" };
		menuItem2 = pd->system->addOptionsMenuItem("Colors", normalInverted, 2, OtherMenuItemCallback, &menuItem2);
		if (isInvertedSaveState())
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

