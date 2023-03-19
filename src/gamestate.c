#include <stdbool.h>
#include "gamestate.h"
#include "menus.h"
#include "savestate.h"
#include "commonvars.h"
#include "cworldparts.h"
#include "cworldpart.h"
#include "sound.h"
#include "gamefuncs.h"
#include "pd_api.h"
#include "pd_helperfuncs.h"
#include "crank.h"


bool StageDone(CWorldPart* Player)
{
	//this works because player is on a higher group (it is handled & found last so the exit is found first if we are at that position)
	CWorldPart* Part = CWorldParts_PartAtPosition(WorldParts, Player->PlayFieldX, Player->PlayFieldY);
	if (Part)
	{
		if (Part->Type == IDExit)
		{
			return true;
		}
	}
	return false;
}


void GameInit(void)
{
	setCrankMoveThreshold(35);
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
			if (((currButtons & kButtonA) && (!(prevButtons & kButtonA))) || ((currButtons & kButtonUp) && (!(prevButtons & kButtonUp))))
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
				unsigned int crankResult = crankUpdate(); 
				if ((currButtons & kButtonLeft) || (crankResult == CRANKMOVELEFT))
				{
					if (CWorldPart_MoveTo(WorldParts->Player, WorldParts->Player->PlayFieldX - 1, WorldParts->Player->PlayFieldY))
					{
						NeedRedraw = true;
					}
					else
					{
						//move up
						NeedRedraw |= CWorldPart_MoveTo(WorldParts->Player, WorldParts->Player->PlayFieldX, WorldParts->Player->PlayFieldY - 1);
					}
				}

				if ((currButtons & kButtonRight) || (crankResult == CRANKMOVERIGHT))
				{
					if (CWorldPart_MoveTo(WorldParts->Player, WorldParts->Player->PlayFieldX + 1, WorldParts->Player->PlayFieldY))
					{
						NeedRedraw = true;
					}
					else
					{
						//move up
						NeedRedraw |= CWorldPart_MoveTo(WorldParts->Player, WorldParts->Player->PlayFieldX, WorldParts->Player->PlayFieldY - 1);
					}
				}
			}
		}
	}


	if (!AskingQuestion)
	{
		NeedRedraw |= CWorldParts_Move(WorldParts) || NeedToReloadGraphics;
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
			CWorldParts_ClearDirty(WorldParts, ((skinSaveState() == 1) || (skinSaveState() == 4)));
			CWorldParts_Draw(WorldParts, ((skinSaveState() == 1) || (skinSaveState() == 4)));
			if (WorldParts->LevelBitmap)
			{
				DrawBitmapSrcRec(WorldParts->LevelBitmap, 0, 0, WorldParts->ViewPort->MinScreenX, WorldParts->ViewPort->MinScreenY, WINDOW_WIDTH, WINDOW_HEIGHT, kBitmapUnflipped);
			}
			if (FreeView)
			{
				LCDBitmap* tmp = pd->graphics->newBitmap(WINDOW_WIDTH, 16, kColorWhite);
				pd->graphics->pushContext(tmp);
				pd->graphics->fillRect(0, 0, WINDOW_WIDTH, 16, kColorWhite);
				pd->graphics->drawRect(0, 15, WINDOW_WIDTH, 1, kColorBlack);
				pd->graphics->setFont(Mini);
				char* Text;
				pd->system->formatString(&Text, "Freeview Mode - dpad: Move A/B: exit", SelectedLevel, InstalledLevels);
				pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 4, 4);
				pd->system->realloc(Text, 0);
				pd->graphics->popContext();
				pd->graphics->drawScaledBitmap(tmp, 0, 0, fontScaleSaveState(), fontScaleSaveState());
				pd->graphics->freeBitmap(tmp);
			}
		}
	}

	if (!AskingQuestion && !WorldParts->Player->IsMoving && StageDone(WorldParts->Player))
	{
		//to one extra move & draw to make sure boxes are on final spot
		CWorldParts_Move(WorldParts);
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
}