#ifndef CWORLDPARTS_H
#define CWORLDPARTS_H

#include "commonvars.h"
#include "cviewport.h"
#include "pd_api.h"

typedef struct CWorldPart CWorldPart;
typedef struct CWorldParts CWorldParts;

struct CWorldParts {
	LCDBitmap* LevelBitmap;
	bool DisableSorting;
	bool AllDirty;
	bool AttchedBoxQuedOrMoving;
	CViewPort* ViewPort;
	CWorldPart* Items[NrOfRows*NrOfCols];
	CWorldPart* PositionalItems[NrOfGroups][NrOfCols][NrOfRows];	
	CWorldPart* Player;
	CWorldPart* IgnorePart;
	CWorldPart* DirtyList[NrOfRows * NrOfCols];
	unsigned int PositionalItemsCount[NrOfGroups];
	unsigned int ItemCount;
	unsigned int DirtyCount;
	unsigned int AllDirtyCount;
	unsigned int DirtyClearedCount;
	unsigned int DrawCount;
	unsigned int NumPartsMoving;
	unsigned int NumPartsMovingQueued;
	unsigned int NumPartsAttachedToPlayer;
	unsigned int NumBoxesAttachedToPlayer;
};

CWorldParts* CWorldParts_Create(bool UseLevelBitmapMode);
void CWorldParts_ClearPositionalItems(CWorldParts* self);
void CWorldParts_CreateLevelBitmap(CWorldParts* self, bool BlackBackground);
void CWorldParts_CenterVPOnPlayer(CWorldParts* self);
void CWorldParts_LimitVPLevel(CWorldParts* self);
void CWorldParts_RemoveAll(CWorldParts* self);
void CWorldParts_Remove(CWorldParts* self, int PlayFieldXin, int PlayFieldYin);
void CWorldParts_RemoveType(CWorldParts* self, int Type);
void CWorldParts_Sort(CWorldParts* self);
void CWorldParts_Add(CWorldParts* self, CWorldPart* WorldPart);
void CWorldParts_Load(CWorldParts* self, char* Filename, bool FromData);
bool CWorldParts_SavePositional(CWorldParts* self, char* Filename);
bool CWorldParts_Save(CWorldParts* self, char* Filename);
bool CWorldParts_Move(CWorldParts* self);
int CWorldParts_ClearDirty(CWorldParts* self, bool BlackBackGround);
void CWorldParts_AddDirty(CWorldParts* self, CWorldPart* Part);
int CWorldParts_Draw(CWorldParts* self, bool BlackBackGround);
void CWorldParts_FindPlayer(CWorldParts* self);
void CWorldParts_deinit(CWorldParts* self);
int CWorldParts_GroupCount(CWorldParts* self, int GroupIn);
CWorldPart* CWorldParts_PartAtPosition(CWorldParts* self, int PlayFieldXin, int PlayFieldYin);
int CWorldParts_TypeAtPosition(CWorldParts* self, int PlayFieldXin, int PlayFieldYin);

#endif