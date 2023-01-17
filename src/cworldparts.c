#include "cworldparts.h"
#include "cworldpart.h"
#include "commonvars.h"

CWorldParts* CWorldParts_Create()
{
	CWorldParts* Result = pd->system->realloc(NULL, sizeof(CWorldParts));
	if (Result)
	{
		Result->LevelBitmap = NULL;
		Result->AllDirty = false;
		Result->ItemCount = 0;
		Result->DirtyCount = 0;
		Result->DisableSorting = false;
		Result->ViewPort = CViewPort_Create(0, 0, 24, 14, 0, 0, NrOfCols - 1, NrOfRows - 1);
	}
	return Result;
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
	for (int Teller = 0; Teller < self->ItemCount; Teller++)
		if (self->Items[Teller]->Type == IDPlayer)
		{
			CViewPort_SetViewPort(self->ViewPort, self->Items[Teller]->PlayFieldX - 12, self->Items[Teller]->PlayFieldY - 7, self->Items[Teller]->PlayFieldX + 12, self->Items[Teller]->PlayFieldY + 7);
			self->AllDirty = self->LevelBitmap == NULL;
			break;
		}
}

void CWorldParts_LimitVPLevel(CWorldParts* self)
{
	int MinX = NrOfCols, MinY = NrOfRows, MaxX = -1, MaxY = -1;
	for (int Teller = 0; Teller < self->ItemCount; Teller++)
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
	for (int Teller = 0; Teller < self->ItemCount; Teller++)
	{
		if (self->Items[Teller])
		{
			pd->system->realloc(self->Items[Teller], 0);
			self->Items[Teller] = NULL;
		}
	}
	self->ItemCount = 0;
	self->DirtyCount = 0;
}

void CWorldParts_Remove(CWorldParts* self, int PlayFieldXin, int PlayFieldYin)
{
	for (int Teller1 = 0; Teller1 < self->ItemCount; Teller1++)
	{
		if (self->Items[Teller1])
		{
			if ((self->Items[Teller1]->PlayFieldX == PlayFieldXin) && (self->Items[Teller1]->PlayFieldY == PlayFieldYin))
			{
				//remove from dirty list
				for (int i = 0; i < self->DirtyCount; i++)
				{
					if (self->DirtyList[i] == self->Items[Teller1])
					{
						for (int j = i; j < self->DirtyCount - 1; j++)
							self->DirtyList[j] = self->DirtyList[j + 1];
						self->DirtyCount--;
						break;
					}
				}
				
				//now clear memory & remove for item list
				pd->system->realloc(self->Items[Teller1], 0);
				self->Items[Teller1] = NULL;
				for (int Teller2 = Teller1; Teller2 < self->ItemCount - 1; Teller2++)
					self->Items[Teller2] = self->Items[Teller2 + 1];
				self->ItemCount--;
				Teller1--;
			}
		}
	}
	//self->AllDirty = true;
}

void CWorldParts_RemoveType(CWorldParts* self, int PlayFieldXin, int PlayFieldYin, int Type)
{
	for (int Teller1 = 0; Teller1 < self->ItemCount; Teller1++)
	{
		if (self->Items[Teller1])
		{
			if ((self->Items[Teller1]->PlayFieldX == PlayFieldXin) && (self->Items[Teller1]->PlayFieldY == PlayFieldYin) && (self->Items[Teller1]->Type == Type))
			{
				//remove from dirty list
				for (int i = 0; i < self->DirtyCount; i++)
				{
					if (self->DirtyList[i] == self->Items[Teller1])
					{
						for (int j = i; j < self->DirtyCount - 1; j++)
							self->DirtyList[j] = self->DirtyList[j + 1];
						self->DirtyCount--;
						break;
					}
				}

				//now clear memory & remove for item list
				pd->system->realloc(self->Items[Teller1], 0);
				self->Items[Teller1] = NULL;
				for (int Teller2 = Teller1; Teller2 < self->ItemCount - 1; Teller2++)
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
	int Teller2, Z, Y;
	CWorldPart* Part;
	if (!self->DisableSorting)
	{
		for (int Teller1 = 1; Teller1 < self->ItemCount; Teller1++)
		{
			Z = self->Items[Teller1]->Z;
			Y = self->Items[Teller1]->PlayFieldY;
			Part = self->Items[Teller1];
			Teller2 = Teller1;
			//need to sort on Z for drawing but also on playfieldY for same Z so that 1st item is the highest one, otherwise blocks don't fall at same time
			while ((Teller2 > 0) && ((self->Items[Teller2 - 1]->Z > Z) || ((self->Items[Teller2 - 1]->Z == Z) && (self->Items[Teller2-1]->PlayFieldY < Y))))
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
		WorldPart->ParentList = self;
		CWorldParts_AddDirty(self, WorldPart);
		self->Items[self->ItemCount] = WorldPart;
		self->ItemCount++;
		CWorldParts_Sort(self);
	}
}

bool CWorldParts_Save(CWorldParts* self, char* Filename)
{
	char Buffer[3] = "   ";
	int ret;
	SDFile* Fp = pd->file->open(Filename, kFileWrite);
	if(Fp)
	{
		for (int Teller = 0; Teller < self->ItemCount; Teller++)
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
				CWorldParts_Add(self, CWorldPart_create(X, Y, Type, 0, 0));
				break;
			case IDBox:
				CWorldParts_Add(self, CWorldPart_create(X, Y, Type, ZBox, GroupBox));
				break;
			case IDPlayer:
				CWorldParts_Add(self, CWorldPart_create(X, Y, Type, ZPlayer, GroupPlayer));
				break;
			case IDExit:
				CWorldParts_Add(self, CWorldPart_create(X, Y, Type, ZExit, GroupExit));
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
				CWorldParts_Add(self, CWorldPart_create(X, Y, Type, ZFloor, GroupFloor));
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

void CWorldParts_Move(CWorldParts* self)
{
	for (int Teller = 0; Teller < self->ItemCount; Teller++)
		CWorldPart_Move(self->Items[Teller]);
}

int CWorldParts_ClearDirty(CWorldParts* self, bool BlackBackGround)
{
	int Result = 0;

	if ((self->LevelBitmap == NULL) && self->AllDirty)
		return Result;

	for (int Teller = 0; Teller < self->DirtyCount; Teller++)
	{
		if ((self->LevelBitmap != NULL) || ((self->DirtyList[Teller]->PrevDrawPlayFieldX >= self->ViewPort->VPMinX) && (self->DirtyList[Teller]->PrevDrawPlayFieldX - 1 <= self->ViewPort->VPMaxX) &&
			(self->DirtyList[Teller]->PrevDrawPlayFieldY >= self->ViewPort->VPMinY) && (self->DirtyList[Teller]->PrevDrawPlayFieldY - 1 <= self->ViewPort->VPMaxY)))
		{
			CWorldPart_Draw(self->DirtyList[Teller], true, BlackBackGround, self->LevelBitmap);
			Result++;
		}
	}
	return Result;
}
void CWorldParts_AddDirty(CWorldParts* self, CWorldPart* Part)
{
	if (!Part->Dirty)
	{
		Part->Dirty = true;
		self->DirtyList[self->DirtyCount] = Part;
		self->DirtyCount++;
	}
}

int CWorldParts_Draw(CWorldParts* self, bool BlackBackGround)
{
	int Result = 0;
	//fullscreen update
	if (self->AllDirty)
	{
		for (int Teller = 0; Teller < self->ItemCount; Teller++)
		{
			if ((self->LevelBitmap != NULL) || ((self->Items[Teller]->PlayFieldX >= self->ViewPort->VPMinX) && (self->Items[Teller]->PlayFieldX - 1 <= self->ViewPort->VPMaxX) &&
				(self->Items[Teller]->PlayFieldY >= self->ViewPort->VPMinY) && (self->Items[Teller]->PlayFieldY - 1 <= self->ViewPort->VPMaxY)))
			{
				CWorldPart_Draw(self->Items[Teller], false, BlackBackGround, self->LevelBitmap);
				Result++;
			}
			self->Items[Teller]->Dirty = false;
			self->Items[Teller]->PrevDrawPlayFieldX = self->Items[Teller]->PlayFieldX;
			self->Items[Teller]->PrevDrawPlayFieldY = self->Items[Teller]->PlayFieldY;
		}
		self->AllDirty = false;
		self->DirtyCount = 0;
	}
	//smaller list with only dirty items to draw (smaller loop)
	else
	{
		for (int Teller = 0; Teller < self->DirtyCount; Teller++)
		{
			if ((self->LevelBitmap != NULL) || ((self->DirtyList[Teller]->PlayFieldX >= self->ViewPort->VPMinX) && (self->DirtyList[Teller]->PlayFieldX - 1 <= self->ViewPort->VPMaxX) &&
				(self->DirtyList[Teller]->PlayFieldY >= self->ViewPort->VPMinY) && (self->DirtyList[Teller]->PlayFieldY - 1 <= self->ViewPort->VPMaxY)))
			{
				CWorldPart_Draw(self->DirtyList[Teller], false, BlackBackGround, self->LevelBitmap);
				Result++;
			}
			self->DirtyList[Teller]->PrevDrawPlayFieldX = self->DirtyList[Teller]->PlayFieldX;
			self->DirtyList[Teller]->PrevDrawPlayFieldY = self->DirtyList[Teller]->PlayFieldY;
			self->DirtyList[Teller]->Dirty = false;
		}
		self->AllDirty = false;
		self->DirtyCount = 0;
	}

	return Result;
}

CWorldPart* CWorldParts_PartAtPosition(CWorldParts* self, int PlayFieldXin, int PlayFieldYin)
{
	if ((PlayFieldYin < 0) || (PlayFieldYin >= NrOfRows) || (PlayFieldXin < 0) || (PlayFieldXin >= NrOfCols))
		return NULL;

	for (int Teller = 0; Teller < self->ItemCount; Teller++)
	{
		if ((self->Items[Teller]->PlayFieldX == PlayFieldXin) && (self->Items[Teller]->PlayFieldY == PlayFieldYin))
		{
			return self->Items[Teller];
		}
	}
	return NULL;
}

int CWorldParts_GroupCount(CWorldParts* self, int GroupIn)
{
	int Result = 0;
	for (int Teller = 0; Teller < self->ItemCount; Teller++)
	{
		if ((self->Items[Teller]->Group == GroupIn))
		{
			Result++;
		}
	}
	return Result;
}


int CWorldParts_TypeAtPosition(CWorldParts* self, int PlayFieldXin, int PlayFieldYin)
{
	if ((PlayFieldYin < 0) || (PlayFieldYin >= NrOfRows) || (PlayFieldXin < 0) || (PlayFieldXin >= NrOfCols))
		return 0;

	for (int Teller = 0; Teller < self->ItemCount; Teller++)
	{
		if ((self->Items[Teller]->PlayFieldX == PlayFieldXin) && (self->Items[Teller]->PlayFieldY == PlayFieldYin))
		{
			return self->Items[Teller]->Type;
		}
	}
	return 0;
}

void CWorldParts_deinit(CWorldParts* self)
{
	CWorldParts_RemoveAll(self);
	pd->system->realloc(self->ViewPort, 0);
}
