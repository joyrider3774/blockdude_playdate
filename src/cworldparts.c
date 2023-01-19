#include "cworldparts.h"
#include "cworldpart.h"
#include "commonvars.h"

CWorldParts* CWorldParts_Create()
{
	CWorldParts* Result = pd->system->realloc(NULL, sizeof(CWorldParts));
	if (Result)
	{
		CWorldParts_ClearPositionalItems(Result);
		Result->LevelBitmap = NULL;
		Result->AllDirty = false;
		Result->ItemCount = 0;
		Result->DirtyCount = 0;
		Result->Player = NULL;
		Result->IgnorePart = NULL;
		Result->DisableSorting = false;
		Result->AttchedBoxQuedOrMoving = false;
		Result->NumPartsMoving = 0;
		Result->DrawCount = 0;
		Result->DirtyClearedCount = 0;
		Result->AllDirtyCount = 0;
		Result->NumPartsMovingQueued = 0;
		Result->NumBoxesAttachedToPlayer = 0;
		Result->NumPartsAttachedToPlayer = 0;
		Result->ViewPort = CViewPort_Create(0, 0, 24, 14, 0, 0, NrOfCols - 1, NrOfRows - 1);
	}
	return Result;
}

void CWorldParts_FindPlayer(CWorldParts* self)
{
	for (unsigned int i = 0; i < self->ItemCount; i++)
	{
		if ((self->Items[i]->Group == GroupPlayer) && (self->Items[i] != self->IgnorePart))
		{
			self->Player = self->Items[i];
			break;
		}
	}
}

void CWorldParts_ClearPositionalItems(CWorldParts* self)
{
	for (int i = 0; i < NrOfGroups; i++)
	{
		self->PositionalItemsCount[i] = 0;
		for (int x = 0; x < NrOfCols; x++)
			for (int y = 0; y < NrOfRows; y++)
				self->PositionalItems[i][x][y] = NULL;
	}
}

void CWorldParts_CreateLevelBitmap(CWorldParts* self, bool BlackBackground)
{
	if (self->LevelBitmap)
	{
		pd->graphics->freeBitmap(self->LevelBitmap);
	}
	if (BlackBackground)
	{
		self->LevelBitmap = pd->graphics->newBitmap(NrOfCols * TileWidth, NrOfRows * TileHeight, kColorBlack);
	}
	else
	{
		self->LevelBitmap = pd->graphics->newBitmap(NrOfCols * TileWidth, NrOfRows * TileHeight, kColorWhite);
	}
}

void CWorldParts_CenterVPOnPlayer(CWorldParts* self)
{
	if (self->Player == NULL)
		CWorldParts_FindPlayer(self);

	if (self->Player)
	{
		CViewPort_SetViewPort(self->ViewPort, self->Player->PlayFieldX - 12, self->Player->PlayFieldY - 7, self->Player->PlayFieldX + 12, self->Player->PlayFieldY + 7);
		self->AllDirty = self->LevelBitmap == NULL;
	}
}

void CWorldParts_LimitVPLevel(CWorldParts* self)
{
	int MinX = NrOfCols, MinY = NrOfRows, MaxX = -1, MaxY = -1;
	for (unsigned int Teller = 0; Teller < self->ItemCount; Teller++)
	{
		if (self->Items[Teller]->PlayFieldX < MinX)
			MinX = self->Items[Teller]->PlayFieldX;
		if (self->Items[Teller]->PlayFieldY < MinY)
			MinY = self->Items[Teller]->PlayFieldY;
		if (self->Items[Teller]->PlayFieldX > MaxX)
			MaxX = self->Items[Teller]->PlayFieldX;
		if (self->Items[Teller]->PlayFieldY > MaxY)
			MaxY = self->Items[Teller]->PlayFieldY;
	}
	CViewPort_SetVPLimit(self->ViewPort, MinX, MinY, MaxX, MaxY);
	CWorldParts_CenterVPOnPlayer(self);
}

void CWorldParts_RemoveAll(CWorldParts* self)
{
	for (unsigned int Teller = 0; Teller < self->ItemCount; Teller++)
	{
		if (self->Items[Teller])
		{
			pd->system->realloc(self->Items[Teller], 0);
			self->Items[Teller] = NULL;
		}
	}
	CWorldParts_ClearPositionalItems(self);
	self->Player = NULL;
	self->ItemCount = 0;
	self->DirtyCount = 0;
}

void CWorldParts_Remove(CWorldParts* self, int PlayFieldXin, int PlayFieldYin)
{
	for (unsigned int Teller1 = 0; Teller1 < self->ItemCount; Teller1++)
	{
		if (self->Items[Teller1] && (self->Items[Teller1] != self->IgnorePart))
		{
			if ((self->Items[Teller1]->PlayFieldX == PlayFieldXin) && (self->Items[Teller1]->PlayFieldY == PlayFieldYin))
			{

				if (self->Items[Teller1]->Group == GroupPlayer)
				{
					self->Player = NULL;
				}
				
				if (self->Items[Teller1]->Group != GroupNone)
				{
					self->PositionalItemsCount[self->Items[Teller1]->Group]--;
					self->PositionalItems[self->Items[Teller1]->Group][self->Items[Teller1]->PlayFieldX][self->Items[Teller1]->PlayFieldY] = NULL;
				}

				//remove from dirty list
				for (unsigned int i = 0; i < self->DirtyCount; i++)
				{
					if (self->DirtyList[i] == self->Items[Teller1])
					{
						for (unsigned int j = i; j < self->DirtyCount - 1; j++)
							self->DirtyList[j] = self->DirtyList[j + 1];
						self->DirtyCount--;
						break;
					}
				}
				
				//now clear memory & remove for item list
				pd->system->realloc(self->Items[Teller1], 0);
				self->Items[Teller1] = NULL;
				for (unsigned int Teller2 = Teller1; Teller2 < self->ItemCount - 1; Teller2++)
					self->Items[Teller2] = self->Items[Teller2 + 1];
				self->ItemCount--;
				Teller1--;
			}
		}
	}
	//self->AllDirty = true;
}

void CWorldParts_RemoveType(CWorldParts* self, int Type)
{
	for (unsigned int Teller1 = 0; Teller1 < self->ItemCount; Teller1++)
	{
		if (self->Items[Teller1] && (self->Items[Teller1] != self->IgnorePart))
		{
			if (self->Items[Teller1]->Type == Type)
			{
				if (Type == IDPlayer)
				{
					self->Items[Teller1]->Player = NULL;
					self->Player = NULL;
				}
				
				if (self->Items[Teller1]->Group != GroupNone)
				{
					self->PositionalItemsCount[self->Items[Teller1]->Group]--;
					self->PositionalItems[self->Items[Teller1]->Group][self->Items[Teller1]->PlayFieldX][self->Items[Teller1]->PlayFieldY] = NULL;
				}

				//remove from dirty list
				for (unsigned int i = 0; i < self->DirtyCount; i++)
				{
					if (self->DirtyList[i] == self->Items[Teller1])
					{
						for (unsigned int j = i; j < self->DirtyCount - 1; j++)
							self->DirtyList[j] = self->DirtyList[j + 1];
						self->DirtyCount--;
						break;
					}
				}

				//now clear memory & remove for item list
				pd->system->realloc(self->Items[Teller1], 0);
				self->Items[Teller1] = NULL;
				for (unsigned int Teller2 = Teller1; Teller2 < self->ItemCount - 1; Teller2++)
					self->Items[Teller2] = self->Items[Teller2 + 1];
				self->ItemCount--;
				Teller1--;
			}
		}
	}
	self->AllDirty = true;
}



void CWorldParts_Sort(CWorldParts* self)
{
	int Teller2, Group, Y;
	CWorldPart* Part;
	if (!self->DisableSorting)
	{
		for (unsigned int Teller1 = 1; Teller1 < self->ItemCount; Teller1++)
		{
			Group = self->Items[Teller1]->Group;
			Y = self->Items[Teller1]->PlayFieldY;
			Part = self->Items[Teller1];
			Teller2 = Teller1;
			//need to sort on group for drawing but also on playfieldY for same Z so that 1st item is the highest one, otherwise blocks don't fall at same time
			while ((Teller2 > 0) && ((self->Items[Teller2 - 1]->Group > Group) || ((self->Items[Teller2 - 1]->Group == Group) && (self->Items[Teller2-1]->PlayFieldY < Y))))
			{
				self->Items[Teller2] = self->Items[Teller2 - 1];
				Teller2--;
			}
			self->Items[Teller2] = Part;
		}
	}

}

void CWorldParts_Add(CWorldParts* self, CWorldPart* WorldPart)
{
	if (self->ItemCount < NrOfRows * NrOfCols)
	{
		if (WorldPart->Type == IDPlayer)
			self->Player = WorldPart;
		WorldPart->ParentList = self;
		CWorldParts_AddDirty(self, WorldPart);
		self->Items[self->ItemCount] = WorldPart;
		if (WorldPart->Group != GroupNone)
		{
			self->PositionalItems[WorldPart->Group][WorldPart->PlayFieldX][WorldPart->PlayFieldY] = WorldPart;
			self->PositionalItemsCount[WorldPart->Group]++;
		}
		self->ItemCount++;
		CWorldParts_Sort(self);
	}
}

bool CWorldParts_SavePositional(CWorldParts* self, char* Filename)
{
	char Buffer[3] = "   ";
	int ret;
	SDFile* Fp = pd->file->open(Filename, kFileWrite);
	if (Fp)
	{
		for (int i = 0; i < NrOfGroups; i++)
		{
			for (int y = 0; y < NrOfRows; y++)
			{
				for (int x = 0; x < NrOfCols; x++)
				{

					if (self->PositionalItems[i][x][y] != self->IgnorePart)
					{
						Buffer[0] = (char)self->PositionalItems[i][x][y]->Type;
						Buffer[1] = (char)x;
						Buffer[2] = (char)y;
						ret = pd->file->write(Fp, Buffer, 3);
						if (ret == -1)
						{
							pd->system->error("Error writing level file!");
							pd->system->logToConsole(pd->file->geterr());
							return false;
						}
					}
				}
			}
		}
		//crashes the simulator ???
#ifndef _WIN32
		ret = pd->file->flush(Fp);
		if (ret == -1)
		{
			pd->system->error("Error flushing savesate file!");
			pd->system->logToConsole(pd->file->geterr());
			return false;
		}
#endif
		ret = pd->file->close(Fp);
		if (ret == -1)
		{
			pd->system->error("Error closing level file!");
			pd->system->logToConsole(pd->file->geterr());
			return false;
		}
	}
	return true;
}


bool CWorldParts_Save(CWorldParts* self, char* Filename)
{
	char Buffer[3] = "   ";
	int ret;
	SDFile* Fp = pd->file->open(Filename, kFileWrite);
	if(Fp)
	{
		for (unsigned int Teller = 0; Teller < self->ItemCount; Teller++)
		{
			if (self->Items[Teller] != self->IgnorePart)
			{
				Buffer[0] = (char)self->Items[Teller]->Type;
				Buffer[1] = (char)self->Items[Teller]->PlayFieldX;
				Buffer[2] = (char)self->Items[Teller]->PlayFieldY;
				ret = pd->file->write(Fp, Buffer, 3);
				if (ret == -1)
				{
					pd->system->error("Error writing level file!");
					pd->system->logToConsole(pd->file->geterr());
					return false;
				}
			}
		}
		//crashes the simulator ???
#ifndef _WIN32
		ret = pd->file->flush(Fp);
		if (ret == -1)
		{
			pd->system->error("Error flushing savesate file!");
			pd->system->logToConsole(pd->file->geterr());
			return false;
		}
#endif
		ret = pd->file->close(Fp);
		if (ret == -1)
		{
			pd->system->error("Error closing level file!");
			pd->system->logToConsole(pd->file->geterr());
			return false;
		}
	}
	return true;
}


void CWorldParts_Load(CWorldParts* self, char* Filename, bool FromData)
{
	char Buffer[3];
	int X, Y, Type;
	FileOptions opt;
	if (FromData)
		opt = kFileReadData;
	else
		opt = kFileRead;

	CWorldParts_RemoveAll(self);

	SDFile* Fp = pd->file->open(Filename, opt);
	if (Fp)
	{
		self->DisableSorting = true;
		while (pd->file->read(Fp, Buffer, sizeof(Buffer)) == 3)
		{
			Type = (int)Buffer[0];
			X = (int)Buffer[1];
			Y = (int)Buffer[2];
			switch (Type)
			{
			case IDEmpty:
				CWorldParts_Add(self, CWorldPart_create(X, Y, Type, GroupNone));
				break;
			case IDBox:
				CWorldParts_Add(self, CWorldPart_create(X, Y, Type, GroupBox));
				break;
			case IDPlayer:
				CWorldParts_Add(self, CWorldPart_create(X, Y, Type, GroupPlayer));
				break;
			case IDExit:
				CWorldParts_Add(self, CWorldPart_create(X, Y, Type, GroupExit));
				break;
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
			case IDFloor:
				CWorldParts_Add(self, CWorldPart_create(X, Y, Type, GroupFloor));
				break;

			}
		}
		pd->file->close(Fp);
		self->DisableSorting = false;
		CWorldParts_Sort(self);
		CWorldParts_LimitVPLevel(self);
		CWorldParts_CenterVPOnPlayer(self);
	}

}

bool CWorldParts_Move(CWorldParts* self)
{
	bool result = false;
	self->NumPartsMoving = 0;
	self->NumPartsMovingQueued = 0;
	self->NumPartsAttachedToPlayer = 0 ;
	self->NumBoxesAttachedToPlayer = 0;
	self->AttchedBoxQuedOrMoving = false;
	for (unsigned int Teller = 0; Teller < self->ItemCount; Teller++)
	{
		result |= CWorldPart_Move(self->Items[Teller]);

		if (WorldParts->Items[Teller]->IsMoving)
		{
			self->NumPartsMoving++;
		}
		
		if (WorldParts->Items[Teller]->Player)
		{
			self->NumPartsAttachedToPlayer++;

			if (WorldParts->Items[Teller]->Type == IDBox)
			{			
				self->NumBoxesAttachedToPlayer++;
				self->AttchedBoxQuedOrMoving = (WorldParts->Items[Teller]->MoveQueBack > -1) || WorldParts->Items[Teller]->IsMoving;
			}
		}

		if (WorldParts->Items[Teller]->MoveQueBack > -1)
			self->NumPartsMovingQueued++;
			
	}
	return result;
}

int CWorldParts_ClearDirty(CWorldParts* self, bool BlackBackGround)
{
	self->DirtyClearedCount = 0;

	if (self->AllDirty)
		self->AllDirtyCount++;

	//in case of all Dirty and not bitmap level mode we don't need clear it as we will have blanked the screen
	if ((self->LevelBitmap == NULL) && self->AllDirty)
		return self->DirtyClearedCount;

	if (self->LevelBitmap)
	{
		pd->graphics->pushContext(self->LevelBitmap);
	}

	for (unsigned int Teller = 0; Teller < self->DirtyCount; Teller++)
	{
		//in case of bitmap mode we always need to draw and in non bitmap mode only if they fall inside the viewport
		if ((self->LevelBitmap != NULL) || ((self->DirtyList[Teller]->PrevDrawPlayFieldX >= self->ViewPort->VPMinX) && (self->DirtyList[Teller]->PrevDrawPlayFieldX -1 <= self->ViewPort->VPMaxX) &&
			(self->DirtyList[Teller]->PrevDrawPlayFieldY >= self->ViewPort->VPMinY) && (self->DirtyList[Teller]->PrevDrawPlayFieldY -1 <= self->ViewPort->VPMaxY)))
		{
			//CWorldPart_Draw(self->DirtyList[Teller], true, BlackBackGround, self->LevelBitmap);
			pd->graphics->fillRect(self->DirtyList[Teller]->PrevDrawX, self->DirtyList[Teller]->PrevDrawY, TileWidth, TileHeight, BlackBackGround ? kColorBlack: kColorWhite);
			self->DirtyClearedCount++;
		}
	}
	if (self->LevelBitmap)
	{
		pd->graphics->popContext();
	}

	return self->DirtyClearedCount;
}
void CWorldParts_AddDirty(CWorldParts* self, CWorldPart* Part)
{
	if ((Part != self->IgnorePart) && !Part->Dirty)
	{
		Part->Dirty = true;
		self->DirtyList[self->DirtyCount] = Part;
		self->DirtyCount++;
	}
}

int CWorldParts_Draw(CWorldParts* self, bool BlackBackGround)
{
	self->DrawCount = 0;
	//fullscreen update
	if (self->LevelBitmap)
	{
		pd->graphics->pushContext(self->LevelBitmap);
	}
	if (self->AllDirty)
	{
		unsigned int startx, starty, endx, endy, numitems;
		if (self->LevelBitmap != NULL)
		{
			startx = 0;
			starty = 0;
			endx = NrOfCols - 1;
			endy = NrOfRows - 1;
			numitems = (endx - startx) * (endy - starty) * (NrOfGroups-1); //there is only 1 player

		}
		else
		{
			startx = self->ViewPort->VPMinX;
			starty = self->ViewPort->VPMinY;
			endx = self->ViewPort->VPMaxX + 1;
			endy = self->ViewPort->VPMaxY + 1;
			//just a safety
			if (startx < 0)
				startx = 0;
			if (starty < 0)
				starty = 0;
			if (endx > NrOfCols - 1)
				endx = NrOfCols - 1;
			if (endy > NrOfRows - 1)
				endy = NrOfRows - 1;
			numitems = (endx - startx) * (endy - starty) * (NrOfGroups-1); //there is only 1 player
		}

		if (self->ItemCount < numitems)
		{
			for (unsigned int Teller = 0; Teller < self->ItemCount; Teller++)
			{
				if ((self->LevelBitmap != NULL) || ((self->Items[Teller]->PlayFieldX >= self->ViewPort->VPMinX) && (self->Items[Teller]->PlayFieldX - 1 <= self->ViewPort->VPMaxX) &&
					(self->Items[Teller]->PlayFieldY >= self->ViewPort->VPMinY) && (self->Items[Teller]->PlayFieldY - 1 <= self->ViewPort->VPMaxY)))
				{
					CWorldPart_Draw(self->Items[Teller], false, BlackBackGround, self->LevelBitmap);
					self->DrawCount++;
				}
				self->Items[Teller]->Dirty = false;
				self->Items[Teller]->PrevDrawPlayFieldX = self->Items[Teller]->PlayFieldX;
				self->Items[Teller]->PrevDrawPlayFieldY = self->Items[Teller]->PlayFieldY;
			}
		}
		else
		{
			for (int i = 0; i < NrOfGroups; i++)
			{
				//there is only one player no need to loop over the list we can draw it directly
				if (i == GroupPlayer)
				{
					if (self->Player)
					{
						CWorldPart_Draw(self->Player, false, BlackBackGround, self->LevelBitmap);
						self->DrawCount++;
						self->Player->Dirty = false;
						self->Player->PrevDrawPlayFieldX = self->Player->PlayFieldX;
						self->Player->PrevDrawPlayFieldY = self->Player->PlayFieldY;
					}
					continue;
				}

				for (unsigned int y = starty; y <= endy; y++)
				{
					for (unsigned int x = startx; x <= endx; x++)
					{
						if (self->PositionalItems[i][x][y] && (self->PositionalItems[i][x][y] != self->IgnorePart))
						{
							CWorldPart_Draw(self->PositionalItems[i][x][y], false, BlackBackGround, self->LevelBitmap);
							self->DrawCount++;
							self->PositionalItems[i][x][y]->Dirty = false;
							self->PositionalItems[i][x][y]->PrevDrawPlayFieldX = self->PositionalItems[i][x][y]->PlayFieldX;
							self->PositionalItems[i][x][y]->PrevDrawPlayFieldY = self->PositionalItems[i][x][y]->PlayFieldY;
						}
					}
				}
			}
		}
	}
	//smaller list with only dirty items to draw (smaller loop)
	else
	{
		for (unsigned int Teller = 0; Teller < self->DirtyCount; Teller++)
		{
			if ((self->LevelBitmap != NULL) || ((self->DirtyList[Teller]->PlayFieldX >= self->ViewPort->VPMinX) && (self->DirtyList[Teller]->PlayFieldX - 1 <= self->ViewPort->VPMaxX) &&
				(self->DirtyList[Teller]->PlayFieldY >= self->ViewPort->VPMinY) && (self->DirtyList[Teller]->PlayFieldY - 1 <= self->ViewPort->VPMaxY)))
			{
				CWorldPart_Draw(self->DirtyList[Teller], false, BlackBackGround, self->LevelBitmap);
				self->DrawCount++;
			}
			self->DirtyList[Teller]->PrevDrawPlayFieldX = self->DirtyList[Teller]->PlayFieldX;
			self->DirtyList[Teller]->PrevDrawPlayFieldY = self->DirtyList[Teller]->PlayFieldY;
			self->DirtyList[Teller]->Dirty = false;
		}
	}
	if (self->LevelBitmap)
	{
		pd->graphics->popContext();
	}
	self->AllDirty = false;
	self->DirtyCount = 0;
	return self->DrawCount;
}

CWorldPart* CWorldParts_PartAtPosition(CWorldParts* self, int PlayFieldXin, int PlayFieldYin)
{
	if ((PlayFieldYin < 0) || (PlayFieldYin >= NrOfRows) || (PlayFieldXin < 0) || (PlayFieldXin >= NrOfCols))
		return NULL;

	for (int Teller = 0; Teller < NrOfGroups; Teller++)
	{
		if (self->PositionalItems[Teller][PlayFieldXin][PlayFieldYin])
		{
			if (self->PositionalItems[Teller][PlayFieldXin][PlayFieldYin] != self->IgnorePart)
			{
				return self->PositionalItems[Teller][PlayFieldXin][PlayFieldYin];
			}
		}
	}

	return NULL;
}

int CWorldParts_GroupCount(CWorldParts* self, int GroupIn)
{
	if (GroupIn == GroupNone)
		return 0;

	return (self->PositionalItemsCount[GroupIn]);
}


int CWorldParts_TypeAtPosition(CWorldParts* self, int PlayFieldXin, int PlayFieldYin)
{
	if ((PlayFieldYin < 0) || (PlayFieldYin >= NrOfRows) || (PlayFieldXin < 0) || (PlayFieldXin >= NrOfCols))
		return 0;

	for(int Teller = 0; Teller < NrOfGroups; Teller++)
	{
		if (self->PositionalItems[Teller][PlayFieldXin][PlayFieldYin])
		{
			if (self->PositionalItems[Teller][PlayFieldXin][PlayFieldYin] != self->IgnorePart)
			{
				return self->PositionalItems[Teller][PlayFieldXin][PlayFieldYin]->Type;
			}
		}
	}

	return 0;
}

void CWorldParts_deinit(CWorldParts* self)
{
	CWorldParts_RemoveAll(self);
	pd->system->realloc(self->ViewPort, 0);
}
