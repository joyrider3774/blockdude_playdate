#include "pd_api.h"
#include "commonvars.h"
#include "cselector.h"
#include "cworldpart.h"


CSelector* CSelector_Create(CWorldParts* List)
{
	CSelector* Result = pd->system->realloc(NULL, sizeof(CSelector));
	Result->PList = List;
	Result->Selection = IDPlayer;
	Result->Part = CWorldPart_create(0, 0, IDPlayer, ZPlayer, GroupPlayer);
	Result->Part->ParentList = Result->PList;
	Result->Part->Selected = true;
	return Result;
}

void CSelector_SetPosition(CSelector* self, const int PlayFieldXin, const int PlayFieldYin)
{
	CWorldPart_SetPosition(self->Part, PlayFieldXin, PlayFieldYin);
}

void CSelector_MoveUp(CSelector* self)
{
	CWorldPart_SetPosition(self->Part, self->Part->PlayFieldX, self->Part->PlayFieldY - 1);
}

void CSelector_MoveDown(CSelector* self)
{
	CWorldPart_SetPosition(self->Part, self->Part->PlayFieldX, self->Part->PlayFieldY + 1);
}

void CSelector_MoveRight(CSelector* self)
{
	CWorldPart_SetPosition(self->Part, self->Part->PlayFieldX + 1, self->Part->PlayFieldY);
}

void CSelector_MoveLeft(CSelector* self)
{
	CWorldPart_SetPosition(self->Part, self->Part->PlayFieldX - 1, self->Part->PlayFieldY);
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
		self->Part = CWorldPart_create(X, Y, IDEmpty, 1000, 0);
		break;
	case IDBox:
		self->Part = CWorldPart_create(X, Y, IDBox, ZBox, GroupBox);
		break;
	case IDPlayer:
		self->Part = CWorldPart_create(X, Y, IDPlayer, ZPlayer, GroupPlayer);
		break;
	case IDFloor:
		self->Part = CWorldPart_create(X, Y, IDFloor, ZFloor, GroupFloor);
		break;
	case IDExit:
		self->Part = CWorldPart_create(X, Y, IDExit, ZExit, GroupExit);
		break;
	case IDEarthGrassLeft:
		self->Part = CWorldPart_create(X, Y, IDEarthGrassLeft, ZFloor, GroupFloor);
		break;
	case IDEarthGrassRight:
		self->Part = CWorldPart_create(X, Y, IDEarthGrassRight, ZFloor, GroupFloor);
		break;
	case IDEarthLeft:
		self->Part = CWorldPart_create(X, Y, IDEarthLeft, ZFloor, GroupFloor);
		break;
	case IDEarthMiddle:
		self->Part = CWorldPart_create(X, Y, IDEarthMiddle, ZFloor, GroupFloor);
		break;
	case IDEarthRight:
		self->Part = CWorldPart_create(X, Y, IDEarthRight, ZFloor, GroupFloor);
		break;
	case IDFloatingFloor:
		self->Part = CWorldPart_create(X, Y, IDFloatingFloor, ZFloor, GroupFloor);
		break;
	case IDFloatingFloorLeft:
		self->Part = CWorldPart_create(X, Y, IDFloatingFloorLeft, ZFloor, GroupFloor);
		break;
	case IDFloatingFloorMiddle:
		self->Part = CWorldPart_create(X, Y, IDFloatingFloorMiddle, ZFloor, GroupFloor);
		break;
	case IDFloatingFloorRight:
		self->Part = CWorldPart_create(X, Y, IDFloatingFloorRight, ZFloor, GroupFloor);
		break;
	case IDFloorLeft:
		self->Part = CWorldPart_create(X, Y, IDFloorLeft, ZFloor, GroupFloor);
		break;
	case IDFloorRight:
		self->Part = CWorldPart_create(X, Y, IDFloorRight, ZFloor, GroupFloor);
		break;
	case IDTower:
		self->Part = CWorldPart_create(X, Y, IDTower, ZFloor, GroupFloor);
		break;
	case IDStartTower:
		self->Part = CWorldPart_create(X, Y, IDStartTower, ZFloor, GroupFloor);
		break;
	case IDTowerShaft:
		self->Part = CWorldPart_create(X, Y, IDTowerShaft, ZFloor, GroupFloor);
		break;
	case IDRoof1:
		self->Part = CWorldPart_create(X, Y, IDRoof1, ZFloor, GroupFloor);
		break;
	case IDRoof2:
		self->Part = CWorldPart_create(X, Y, IDRoof2, ZFloor, GroupFloor);
		break;
	case IDRoofCornerLeft:
		self->Part = CWorldPart_create(X, Y, IDRoofCornerLeft, ZFloor, GroupFloor);
		break;
	case IDRoofCornerRight:
		self->Part = CWorldPart_create(X, Y, IDRoofCornerRight, ZFloor, GroupFloor);
		break;
	case IDRoofCornerBoth:
		self->Part = CWorldPart_create(X, Y, IDRoofCornerBoth, ZFloor, GroupFloor);
		break;
	case IDRoofDownRight:
		self->Part = CWorldPart_create(X, Y, IDRoofDownRight, ZFloor, GroupFloor);
		break;
	case IDRoofDownLeft:
		self->Part = CWorldPart_create(X, Y, IDRoofDownLeft, ZFloor, GroupFloor);
		break;

	}
	self->Part->ParentList = self->PList;
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
		self->Part = CWorldPart_create(X, Y, IDEmpty, 1000, 0);
		break;
	case IDBox:
		self->Part = CWorldPart_create(X, Y, IDBox, ZBox, GroupBox);
		break;
	case IDPlayer:
		self->Part = CWorldPart_create(X, Y, IDPlayer, ZPlayer, GroupPlayer);
		break;
	case IDFloor:
		self->Part = CWorldPart_create(X, Y, IDFloor, ZFloor, GroupFloor);
		break;
	case IDExit:
		self->Part = CWorldPart_create(X, Y, IDExit, ZExit, GroupExit);
		break;
	case IDEarthGrassLeft:
		self->Part = CWorldPart_create(X, Y, IDEarthGrassLeft, ZFloor, GroupFloor);
		break;
	case IDEarthGrassRight:
		self->Part = CWorldPart_create(X, Y, IDEarthGrassRight, ZFloor, GroupFloor);
		break;
	case IDEarthLeft:
		self->Part = CWorldPart_create(X, Y, IDEarthLeft, ZFloor, GroupFloor);
		break;
	case IDEarthMiddle:
		self->Part = CWorldPart_create(X, Y, IDEarthMiddle, ZFloor, GroupFloor);
		break;
	case IDEarthRight:
		self->Part = CWorldPart_create(X, Y, IDEarthRight, ZFloor, GroupFloor);
		break;
	case IDFloatingFloor:
		self->Part = CWorldPart_create(X, Y, IDFloatingFloor, ZFloor, GroupFloor);
		break;
	case IDFloatingFloorLeft:
		self->Part = CWorldPart_create(X, Y, IDFloatingFloorLeft, ZFloor, GroupFloor);
		break;
	case IDFloatingFloorMiddle:
		self->Part = CWorldPart_create(X, Y, IDFloatingFloorMiddle, ZFloor, GroupFloor);
		break;
	case IDFloatingFloorRight:
		self->Part = CWorldPart_create(X, Y, IDFloatingFloorRight, ZFloor, GroupFloor);
		break;
	case IDFloorLeft:
		self->Part = CWorldPart_create(X, Y, IDFloorLeft, ZFloor, GroupFloor);
		break;
	case IDFloorRight:
		self->Part = CWorldPart_create(X, Y, IDFloorRight, ZFloor, GroupFloor);
		break;
	case IDTower:
		self->Part = CWorldPart_create(X, Y, IDTower, ZFloor, GroupFloor);
		break;
	case IDStartTower:
		self->Part = CWorldPart_create(X, Y, IDStartTower, ZFloor, GroupFloor);
		break;
	case IDTowerShaft:
		self->Part = CWorldPart_create(X, Y, IDTowerShaft, ZFloor, GroupFloor);
		break;
	case IDRoof1:
		self->Part = CWorldPart_create(X, Y, IDRoof1, ZFloor, GroupFloor);
		break;
	case IDRoof2:
		self->Part = CWorldPart_create(X, Y, IDRoof2, ZFloor, GroupFloor);
		break;
	case IDRoofCornerLeft:
		self->Part = CWorldPart_create(X, Y, IDRoofCornerLeft, ZFloor, GroupFloor);
		break;
	case IDRoofCornerRight:
		self->Part = CWorldPart_create(X, Y, IDRoofCornerRight, ZFloor, GroupFloor);
		break;
	case IDRoofCornerBoth:
		self->Part = CWorldPart_create(X, Y, IDRoofCornerBoth, ZFloor, GroupFloor);
		break;
	case IDRoofDownRight:
		self->Part = CWorldPart_create(X, Y, IDRoofDownRight, ZFloor, GroupFloor);
		break;
	case IDRoofDownLeft:
		self->Part = CWorldPart_create(X, Y, IDRoofDownLeft, ZFloor, GroupFloor);
		break;

	}
	self->Part->ParentList = self->PList;
	self->Part->Selected = true;

}

void CSelector_Draw(CSelector* self)
{
	CWorldPart_Draw(self->Part, false, false, NULL);
}

void CSelector_deinit(CSelector* self)
{
	pd->system->realloc(self->Part, 0);
}