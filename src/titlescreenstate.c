#include <stdint.h>
#include <string.h>
#include "titlescreenstate.h"
#include "commonvars.h"
#include "sound.h"
#include "gamefuncs.h"
#include "menus.h"
#include "savestate.h"
#include "pd_helperfuncs.h"
#include "pd_api.h"
#include "crank.h"

void TitleScreenInit(void)
{
	setCrankMoveThreshold(90);
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

	if (!AskingGetString && !AskingQuestion)
	{
		unsigned int crankResult = crankUpdate();
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
				break;
			case tsOptions:
				switch (titleSelection)
				{
				case opMusicSound:
					if (isMusicOn() && isSoundOn())
					{
						setMusicOn(false);
						setMusicOnSaveState(false);
						setSoundOn(true);
						setSoundOnSaveState(true);
					}
					else
					{
						if (!isMusicOn() && !isSoundOn())
						{
							setMusicOn(true);
							setMusicOnSaveState(true);
							setSoundOn(true);
							setSoundOnSaveState(true);
						}
						else
						{
							if (isMusicOn() && !isSoundOn())
							{
								setMusicOn(false);
								setMusicOnSaveState(false);
								setSoundOn(false);
								setSoundOnSaveState(false);
							}
							else
							{
								setMusicOn(true);
								setMusicOnSaveState(true);
								setSoundOn(false);
								setSoundOnSaveState(false);
							}
						}
					}

					if (menuItem1)
					{
						if (isMusicOnSaveState())
							pd->system->setMenuItemValue(menuItem1, 0);
						else
							pd->system->setMenuItemValue(menuItem1, 1);
					}
					NeedRedraw = true;
    				break;
				case opFontSize:
					playMenuSelectSound();
					float tmp = fontScaleSaveState();
					tmp -= 0.25f;
					if (tmp < 1.0f)
						tmp = 1.5f;
					setFontScaleSaveState(tmp);
					NeedRedraw = true;
					break;
				case opSkin:
					playMenuSelectSound();
					int i = skinSaveState();
					i--;
					if (i == -1)
						i = MAXSKINS - 1;
					setSkinSaveState(i);
					LoadGraphics();
					if (menuItem3)
					{
						pd->system->setMenuItemValue(menuItem3, i);
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
				break;
			case tsOptions:
				switch (titleSelection)
				{
				case opMusicSound:
					if (isMusicOn() && isSoundOn())
					{
						setMusicOn(false);
						setMusicOnSaveState(false);
						setSoundOn(false);
						setSoundOnSaveState(false);
					}
					else
					{
						if (!isMusicOn() && !isSoundOn())
						{
							setMusicOn(true);
							setMusicOnSaveState(true);
							setSoundOn(false);
							setSoundOnSaveState(false);
						}
						else
						{
							if (isMusicOn() && !isSoundOn())
							{
								setMusicOn(false);
								setMusicOnSaveState(false);
								setSoundOn(true);
								setSoundOnSaveState(true);
							}
							else
							{
								setMusicOn(true);
								setMusicOnSaveState(true);
								setSoundOn(true);
								setSoundOnSaveState(true);
							}
						}
					}

					if (menuItem1)
					{
						if (isMusicOnSaveState())
							pd->system->setMenuItemValue(menuItem1, 0);
						else
							pd->system->setMenuItemValue(menuItem1, 1);
					}
					NeedRedraw = true;
					break;
				case opFontSize:
					playMenuSelectSound();
					float tmp = fontScaleSaveState();
					tmp += 0.25f;
					if (tmp > 1.5f)
						tmp = 1.0f;
					setFontScaleSaveState(tmp);
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
						pd->system->setMenuItemValue(menuItem3, i);
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
			default:
				break;
			}
		}


		if (((currButtons & kButtonDown) && (!(prevButtons & kButtonDown))) || (crankResult == CRANKMOVERIGHT))
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

		if (((currButtons & kButtonUp) && (!(prevButtons & kButtonUp))) || (crankResult == CRANKMOVELEFT))
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
					playMenuSelectSound();
					pd->graphics->setFont(Mini);
					AskQuestion(qsCredits, "Blockdude was created by Willems\nDavy. Fonts by Donald Hays. Tech skin\nand Default skin by Fusion Power. Flat\nskin by Klas Kroon & Kris Katiesen.\nKenney's skin by Kenney. Music By\nDonSkeeto. Levels from blockman by\nSoleau Software.");
					DestroyMenuItems();
					break;
				case mmOptions:
					titleStep = tsOptions;
					titleSelection = opMusicSound;
					playMenuSelectSound();
					NeedRedraw = true;
					break;
				}
				break;
			case tsOptions:
				switch (titleSelection)
				{
				case opMusicSound:
					playMenuSelectSound();
					if (isMusicOn() && isSoundOn())
					{
						setMusicOn(false);
						setMusicOnSaveState(false);
						setSoundOn(false);
						setSoundOnSaveState(false);
					}
					else
					{
						if (!isMusicOn() && !isSoundOn())
						{
							setMusicOn(true);
							setMusicOnSaveState(true);
							setSoundOn(false);
							setSoundOnSaveState(false);
						}
						else
						{
							if (isMusicOn() && !isSoundOn())
							{
								setMusicOn(false);
								setMusicOnSaveState(false);
								setSoundOn(true);
								setSoundOnSaveState(true);
							}
							else
							{
								setMusicOn(true);
								setMusicOnSaveState(true);
								setSoundOn(true);
								setSoundOnSaveState(true);
							}
						}
					}

					if (menuItem1)
					{
						if (isMusicOnSaveState())
							pd->system->setMenuItemValue(menuItem1, 0);
						else
							pd->system->setMenuItemValue(menuItem1, 1);
					}
					NeedRedraw = true;
					break;
				case opFontSize:
					playMenuSelectSound();
					float tmp = fontScaleSaveState();
					tmp += 0.25f;
					if (tmp > 1.5f)
						tmp = 1.0f;
					setFontScaleSaveState(tmp);
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
						pd->system->setMenuItemValue(menuItem3, i);
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
					pd->graphics->setFont(Mini);
					AskQuestion(qsDelPack, "Deleting a level pack will remove all\nlevels and the pack!\nThere is no undo!\n\nDo you want todo this?\n\nPress (A) to Continue (B) to cancel");
					DestroyMenuItems();
					break;
				case spOptimize:
					pd->graphics->setFont(Mini);
					AskQuestion(qsOptimizePack, "Optimizing a level pack will remove\nall empty levels, and remove gaps\nbetween level numbering.\n\nDo you want todo this ?\n\nPress (A) to Continue (B) to cancel");
					DestroyMenuItems();
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
		pd->graphics->setFont(Mini2X);
		pd->graphics->drawBitmap(IMGTitleScreen, 0, 0, kBitmapUnflipped);
		pd->graphics->fillRect(97, 67, 206, 101, kColorXOR);
		pd->graphics->drawRect(100, 70, 200, 95, kColorXOR);
		pd->graphics->setDrawMode(kDrawModeNXOR);
		char* Text = NULL;
		switch (titleStep)
		{
		case tsMainMenu:
			pd->system->formatString(&Text, "Start Game\nLevel Editor\nOptions\nCredits\n");
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
			break;
		case tsLevelEditorMode:
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
				char* text;
				bool isInternal = false;
				for (int i = 0; i < InternalLevelPackCount; i++)
				{
					if (strcmp(InternalLevelPacks[i], LevelPacks[CurrentLevelPackIndex]) == 0)
					{
						isInternal = true;
						break;
					}
				}
				if (isInternal)
				{
					pd->system->formatString(&text, "Cur*:%s", LevelPacks[CurrentLevelPackIndex]);
				}
				else
				{
					pd->system->formatString(&text, "Cur:%s", LevelPacks[CurrentLevelPackIndex]);
				}
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
			
			pd->system->formatString(&Text, "Audio %s %s", isMusicOn() ? "M":" ", isSoundOn() ? "S":" ");
			pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 140, 80);
			pd->system->realloc(Text, 0);
			
			pd->system->formatString(&Text, "Text %d%%", (int)(fontScaleSaveState()*100));
			pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 140, 100);
			pd->system->realloc(Text, 0);

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
			case opMusicSound:
				pd->graphics->drawText(">", 1, kASCIIEncoding, 125, 80);
				break;
			case opFontSize:
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

	int id = -1;
	bool answered = false;

	if (getStringUpdate(&id, &answered, GetStringResult))
	{
		if (answered)
		{
			char* path;
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

	id = -1;
	answered = false;
	if ((AskingQuestionID == qsOptimizePack) || (AskingQuestionID == qsDelPack)) 
	{

		if (AskQuestionUpdate(&id, &answered, false))
		{

			if (answered)
			{
				NeedRedraw = false; //need to reset this as were asking another question immediatly
				
				if (id == qsOptimizePack)
				{
					OptimizeLevelPack(LevelPacks[CurrentLevelPackIndex]);
				}

				if (id == qsDelPack)
				{
					char* path;
					pd->system->formatString(&path, "levels/%s", LevelPacks[CurrentLevelPackIndex]);
					pd->file->unlink(path, 1);
					pd->system->realloc(path, 0);
					FindLevelPacks();
					if (FoundLevelPacks == 0)
						titleSelection = spCreate;
					CurrentLevelPackIndex = 0;
				}

				AskQuestion(qsAllDone, "All Done!\n\nPress (A) to continue.");
			}
			else
			{
				CreateOtherMenuItems();
			}
		}
	}
	else
	{
		if (AskQuestionUpdate(&id, &answered, AskingQuestionID != qsCredits))
		{
			//only confirmation questions
			CreateOtherMenuItems();
		}
	}
}
