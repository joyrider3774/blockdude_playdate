#include "pd_api.h"
#include "commonvars.h"
#include "cselector.h"
#include "cworldpart.h"


CSelector* CSelector_Create(CWorldParts* List)
{
	CSelector* Result = pd->system->realloc(NULL, sizeof(CSelector));
	Result->PList = List;
	Result->Selection = IDPlayer;
	Result->Part = CWorldPart_create(0, 0, IDPlayer, GroupPlayer);
	Result->Part->ParentList = Result->PList;
	Result->Part->ParentList->IgnorePart = Result->Part;
	Result->Part->Selected = true;
	return Result;
}

bool CSelector_SetPosition(CSelector* self, const int PlayFieldXin, const int PlayFieldYin)
{
	return CWorldPart_SetPosition(self->Part, PlayFieldXin, PlayFieldYin);
}

bool CSelector_MoveUp(CSelector* self)
{
	return CWorldPart_SetPosition(self->Part, self->Part->PlayFieldX, self->Part->PlayFieldY - 1);
}

bool CSelector_MoveDown(CSelector* self)
{
	return CWorldPart_SetPosition(self->Part, self->Part->PlayFieldX, self->Part->PlayFieldY + 1);
}

bool CSelector_MoveRight(CSelector* self)
{
	return CWorldPart_SetPosition(self->Part, self->Part->PlayFieldX + 1, self->Part->PlayFieldY);
}

bool CSelector_MoveLeft(CSelector* self)
{
	return CWorldPart_SetPosition(self->Part, self->Part->PlayFieldX - 1, self->Part->PlayFieldY);
}

void CSelector_IncSelection(CSelector* self)
{
	int X, Y;
	self->Selection++;
	if (self->Selection > 26)
		self->Selection = 1;
	X = self->Part->PlayFieldX;
	Y = self->Part->PlayFieldY;
	pd->system->realloc(self->Part, 0);
	switch (self->Selection)
	{
	case IDEmpty:
		self->Part = CWorldPart_create(X, Y, IDEmpty, GroupNone);
		break;
	case IDBox:
		self->Part = CWorldPart_create(X, Y, IDBox, GroupBox);
		break;
	case IDPlayer:
		self->Part = CWorldPart_create(X, Y, IDPlayer, GroupPlayer);
		break;
	case IDFloor:
		self->Part = CWorldPart_create(X, Y, IDFloor, GroupFloor);
		break;
	case IDExit:
		self->Part = CWorldPart_create(X, Y, IDExit, GroupExit);
		break;
	case IDEarthGrassLeft:
		self->Part = CWorldPart_create(X, Y, IDEarthGrassLeft, GroupFloor);
		break;
	case IDEarthGrassRight:
		self->Part = CWorldPart_create(X, Y, IDEarthGrassRight, GroupFloor);
		break;
	case IDEarthLeft:
		self->Part = CWorldPart_create(X, Y, IDEarthLeft, GroupFloor);
		break;
	case IDEarthMiddle:
		self->Part = CWorldPart_create(X, Y, IDEarthMiddle, GroupFloor);
		break;
	case IDEarthRight:
		self->Part = CWorldPart_create(X, Y, IDEarthRight, GroupFloor);
		break;
	case IDFloatingFloor:
		self->Part = CWorldPart_create(X, Y, IDFloatingFloor, GroupFloor);
		break;
	case IDFloatingFloorLeft:
		self->Part = CWorldPart_create(X, Y, IDFloatingFloorLeft, GroupFloor);
		break;
	case IDFloatingFloorMiddle:
		self->Part = CWorldPart_create(X, Y, IDFloatingFloorMiddle, GroupFloor);
		break;
	case IDFloatingFloorRight:
		self->Part = CWorldPart_create(X, Y, IDFloatingFloorRight, GroupFloor);
		break;
	case IDFloorLeft:
		self->Part = CWorldPart_create(X, Y, IDFloorLeft, GroupFloor);
		break;
	case IDFloorRight:
		self->Part = CWorldPart_create(X, Y, IDFloorRight, GroupFloor);
		break;
	case IDTower:
		self->Part = CWorldPart_create(X, Y, IDTower, GroupFloor);
		break;
	case IDStartTower:
		self->Part = CWorldPart_create(X, Y, IDStartTower, GroupFloor);
		break;
	case IDTowerShaft:
		self->Part = CWorldPart_create(X, Y, IDTowerShaft, GroupFloor);
		break;
	case IDRoof1:
		self->Part = CWorldPart_create(X, Y, IDRoof1, GroupFloor);
		break;
	case IDRoof2:
		self->Part = CWorldPart_create(X, Y, IDRoof2, GroupFloor);
		break;
	case IDRoofCornerLeft:
		self->Part = CWorldPart_create(X, Y, IDRoofCornerLeft, GroupFloor);
		break;
	case IDRoofCornerRight:
		self->Part = CWorldPart_create(X, Y, IDRoofCornerRight, GroupFloor);
		break;
	case IDRoofCornerBoth:
		self->Part = CWorldPart_create(X, Y, IDRoofCornerBoth, GroupFloor);
		break;
	case IDRoofDownRight:
		self->Part = CWorldPart_create(X, Y, IDRoofDownRight, GroupFloor);
		break;
	case IDRoofDownLeft:
		self->Part = CWorldPart_create(X, Y, IDRoofDownLeft, GroupFloor);
		break;

	}
	self->Part->ParentList = self->PList;
	self->Part->ParentList->IgnorePart = self->Part;
	self->Part->Selected = true;
}

void CSelector_DecSelection(CSelector* self)
{
	int X, Y;
	self->Selection--;
	if (self->Selection < 1)
		self->Selection = 26;
	X = self->Part->PlayFieldX;
	Y = self->Part->PlayFieldY;
	pd->system->realloc(self->Part, 0);
	switch (self->Selection)
	{
	case IDEmpty:
		self->Part = CWorldPart_create(X, Y, IDEmpty, GroupNone);
		break;
	case IDBox:
		self->Part = CWorldPart_create(X, Y, IDBox, GroupBox);
		break;
	case IDPlayer:
		self->Part = CWorldPart_create(X, Y, IDPlayer, GroupPlayer);
		break;
	case IDFloor:
		self->Part = CWorldPart_create(X, Y, IDFloor, GroupFloor);
		break;
	case IDExit:
		self->Part = CWorldPart_create(X, Y, IDExit, GroupExit);
		break;
	case IDEarthGrassLeft:
		self->Part = CWorldPart_create(X, Y, IDEarthGrassLeft, GroupFloor);
		break;
	case IDEarthGrassRight:
		self->Part = CWorldPart_create(X, Y, IDEarthGrassRight, GroupFloor);
		break;
	case IDEarthLeft:
		self->Part = CWorldPart_create(X, Y, IDEarthLeft, GroupFloor);
		break;
	case IDEarthMiddle:
		self->Part = CWorldPart_create(X, Y, IDEarthMiddle, GroupFloor);
		break;
	case IDEarthRight:
		self->Part = CWorldPart_create(X, Y, IDEarthRight, GroupFloor);
		break;
	case IDFloatingFloor:
		self->Part = CWorldPart_create(X, Y, IDFloatingFloor, GroupFloor);
		break;
	case IDFloatingFloorLeft:
		self->Part = CWorldPart_create(X, Y, IDFloatingFloorLeft, GroupFloor);
		break;
	case IDFloatingFloorMiddle:
		self->Part = CWorldPart_create(X, Y, IDFloatingFloorMiddle, GroupFloor);
		break;
	case IDFloatingFloorRight:
		self->Part = CWorldPart_create(X, Y, IDFloatingFloorRight, GroupFloor);
		break;
	case IDFloorLeft:
		self->Part = CWorldPart_create(X, Y, IDFloorLeft, GroupFloor);
		break;
	case IDFloorRight:
		self->Part = CWorldPart_create(X, Y, IDFloorRight, GroupFloor);
		break;
	case IDTower:
		self->Part = CWorldPart_create(X, Y, IDTower, GroupFloor);
		break;
	case IDStartTower:
		self->Part = CWorldPart_create(X, Y, IDStartTower, GroupFloor);
		break;
	case IDTowerShaft:
		self->Part = CWorldPart_create(X, Y, IDTowerShaft, GroupFloor);
		break;
	case IDRoof1:
		self->Part = CWorldPart_create(X, Y, IDRoof1, GroupFloor);
		break;
	case IDRoof2:
		self->Part = CWorldPart_create(X, Y, IDRoof2, GroupFloor);
		break;
	case IDRoofCornerLeft:
		self->Part = CWorldPart_create(X, Y, IDRoofCornerLeft, GroupFloor);
		break;
	case IDRoofCornerRight:
		self->Part = CWorldPart_create(X, Y, IDRoofCornerRight, GroupFloor);
		break;
	case IDRoofCornerBoth:
		self->Part = CWorldPart_create(X, Y, IDRoofCornerBoth, GroupFloor);
		break;
	case IDRoofDownRight:
		self->Part = CWorldPart_create(X, Y, IDRoofDownRight, GroupFloor);
		break;
	case IDRoofDownLeft:
		self->Part = CWorldPart_create(X, Y, IDRoofDownLeft, GroupFloor);
		break;

	}
	self->Part->ParentList = self->PList;
	self->Part->ParentList->IgnorePart = self->Part;
	self->Part->Selected = true;

}

void CSelector_Draw(CSelector* self)
{
	CWorldPart_Draw(self->Part, false, false, false);
}

void CSelector_deinit(CSelector* self)
{
	pd->system->realloc(self->Part, 0);
}