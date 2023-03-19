#include "leveleditorstate.h"
#include "savestate.h"
#include "menus.h"
#include "crank.h"
#include "gamefuncs.h"
#include "commonvars.h"
#include "cworldparts.h"
#include "cworldpart.h"
#include "cselector.h"
#include "pd_api.h"
#include "pd_helperfuncs.h"

void LevelEditorInit(void)
{
	setCrankMoveThreshold(90);
	framecounter = 0;
	NeedRedraw = true;
	DestroyMenuItems();
	CreateLevelEditorMenuItems();
	LoadSelectedLevel();
	WorldParts->AllDirty = true;

	if (WorldParts->Player)
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
			LCDBitmap* tmp = pd->graphics->newBitmap(WINDOW_WIDTH, 16, kColorWhite);
			pd->graphics->pushContext(tmp);
			pd->graphics->fillRect(0, 0, WINDOW_WIDTH, 16, kColorWhite);
			pd->graphics->fillRect(0, 15, WINDOW_WIDTH, 1, kColorBlack);
			pd->graphics->setFont(Mini);
			int BlockBelowSelector = CWorldParts_TypeAtPosition(WorldParts, Selector->Part->PlayFieldX, Selector->Part->PlayFieldY);
			char* Text;
			pd->system->formatString(&Text, "Pos: %d,%d - Selector: %s / %s", Selector->Part->PlayFieldX, Selector->Part->PlayFieldY, blockNames[Selector->Part->Type], blockNames[BlockBelowSelector]);
			pd->graphics->drawText(Text, strlen(Text), kASCIIEncoding, 4, 4);
			pd->system->realloc(Text, 0);
			pd->graphics->popContext();
			pd->graphics->drawScaledBitmap(tmp, 0, 0, fontScaleSaveState(), fontScaleSaveState());
			pd->graphics->freeBitmap(tmp);
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
			NeedRedraw |= CSelector_MoveLeft(Selector);
			if (Selector->Part->PlayFieldX < WorldParts->ViewPort->VPMinX + 3)
				if (CViewPort_Move(WorldParts->ViewPort, -TileWidth, 0))
				{
					WorldParts->AllDirty = WorldParts->LevelBitmap == NULL;
					NeedRedraw = true;
				}

		}

		if (currButtons & kButtonRight)
		{
			NeedRedraw |= CSelector_MoveRight(Selector);
			if (Selector->Part->PlayFieldX > WorldParts->ViewPort->VPMaxX - 3)
				if (CViewPort_Move(WorldParts->ViewPort, TileWidth, 0))
				{
					WorldParts->AllDirty = WorldParts->LevelBitmap == NULL;
					NeedRedraw = true;
				}
		}

		if (currButtons & kButtonUp)
		{
			NeedRedraw |= CSelector_MoveUp(Selector);
			if (Selector->Part->PlayFieldY < WorldParts->ViewPort->VPMinY + 3)
				if (CViewPort_Move(WorldParts->ViewPort, 0, -TileWidth))
				{
					WorldParts->AllDirty = WorldParts->LevelBitmap == NULL;
					NeedRedraw = true;
				}
		}

		if (currButtons & kButtonDown)
		{
			NeedRedraw |= CSelector_MoveDown(Selector);
			if (Selector->Part->PlayFieldY > WorldParts->ViewPort->VPMaxY - 3)
				if (CViewPort_Move(WorldParts->ViewPort, 0, TileWidth))
				{
					WorldParts->AllDirty = WorldParts->LevelBitmap == NULL;
					NeedRedraw = true;
				}
		}
	}

	if (!AskingQuestion && (currButtons & kButtonB) && (!(prevButtons & kButtonB)))
	{
		SaveSelectedLevel();
		GameState = GSStageSelectInit;
	}

	int id;
	bool answer;
	if (AskingQuestionID == qsClearLevel)
	{
		if (AskQuestionUpdate(&id, &answer, false))
		{
			if (answer)
			{
				CWorldParts_RemoveAll(WorldParts);
				WorldParts->AllDirty = true;
			}
			CreateLevelEditorMenuItems();
		}
	}
	else
	{
		if (AskQuestionUpdate(&id, &answer, true))
		{
			if (answer)
			{
				CreateLevelEditorMenuItems();
				WorldParts->AllDirty = true;
			}

		}
	}
}