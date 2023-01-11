#include "cworldparts.h"
#include "cworldpart.h"
#include "commonvars.h"

CWorldParts* CWorldParts_Create()
{
	CWorldParts* Result = pd->system->realloc(NULL, sizeof(CWorldParts));
	if (Result)
	{
		Result->ItemCount = 0;
		Result->DisableSorting = false;
		Result->ViewPort = CViewPort_Create(0, 0, 24, 14, 0, 0, NrOfCols - 1, NrOfRows - 1);
	}
	return Result;
}

void CWorldParts_CenterVPOnPlayer(CWorldParts* self)
{
	for (int Teller = 0; Teller < self->ItemCount; Teller++)
		if (self->Items[Teller]->Type == IDPlayer)
		{
			CViewPort_SetViewPort(self->ViewPort, self->Items[Teller]->PlayFieldX - 12, self->Items[Teller]->PlayFieldY - 7, self->Items[Teller]->PlayFieldX + 12, self->Items[Teller]->PlayFieldY + 7);
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
}

void CWorldParts_Remove(CWorldParts* self, int PlayFieldXin, int PlayFieldYin)
{
	for (int Teller1 = 0; Teller1 < self->ItemCount; Teller1++)
	{
		if (self->Items[Teller1])
		{
			if ((self->Items[Teller1]->PlayFieldX == PlayFieldXin) && (self->Items[Teller1]->PlayFieldY == PlayFieldYin))
			{
				pd->system->realloc(self->Items[Teller1], 0);
				self->Items[Teller1] = NULL;
				for (int Teller2 = Teller1; Teller2 < self->ItemCount - 1; Teller2++)
					self->Items[Teller2] = self->Items[Teller2 + 1];
				self->ItemCount--;
				Teller1--;
			}
		}
	}
}

void CWorldParts_RemoveType(CWorldParts* self, int PlayFieldXin, int PlayFieldYin, int Type)
{
	for (int Teller1 = 0; Teller1 < self->ItemCount; Teller1++)
	{
		if (self->Items[Teller1])
		{
			if ((self->Items[Teller1]->PlayFieldX == PlayFieldXin) && (self->Items[Teller1]->PlayFieldY == PlayFieldYin) && (self->Items[Teller1]->Type == Type))
			{
				pd->system->realloc(self->Items[Teller1], 0);
				self->Items[Teller1] = NULL;
				for (int Teller2 = Teller1; Teller2 < self->ItemCount - 1; Teller2++)
					self->Items[Teller2] = self->Items[Teller2 + 1];
				self->ItemCount--;
				Teller1--;
			}
		}
	}
}



void CWorldParts_Sort(CWorldParts* self)
{
	int Teller2, Index;
	CWorldPart* Part;
	if (!self->DisableSorting)
	{
		for (int Teller1 = 1; Teller1 < self->ItemCount; Teller1++)
		{
			Index = self->Items[Teller1]->Z;
			Part = self->Items[Teller1];
			Teller2 = Teller1;
			while ((Teller2 > 0) && (self->Items[Teller2 - 1]->Z > Index))
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
		self->Items[self->ItemCount] = WorldPart;
		self->ItemCount++;
		CWorldParts_Sort(self);
	}
}


void CWorldParts_Load(CWorldParts* self, char* Filename)
{
	char Buffer[3];
	int X, Y, Type;
	SDFile* Fp = pd->file->open(Filename, kFileRead);
	if (Fp)
	{
		CWorldParts_RemoveAll(self);
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

void CWorldParts_Draw(CWorldParts* self)
{

	for (int Teller = 0; Teller < self->ItemCount; Teller++)
	{
		if ((self->Items[Teller]->PlayFieldX >= self->ViewPort->VPMinX) && (self->Items[Teller]->PlayFieldX - 1 <= self->ViewPort->VPMaxX) &&
			(self->Items[Teller]->PlayFieldY >= self->ViewPort->VPMinY) && (self->Items[Teller]->PlayFieldY - 1 <= self->ViewPort->VPMaxY))
		{
			CWorldPart_Draw(self->Items[Teller]);
		}
	}
}

void CWorldParts_deinit(CWorldParts* self)
{
	CWorldParts_RemoveAll(self);
	pd->system->realloc(self->ViewPort, 0);
}
