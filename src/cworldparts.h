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
	CViewPort* ViewPort;
	CWorldPart* Items[NrOfRows * NrOfCols];
	CWorldPart* DirtyList[NrOfRows * NrOfCols];
	int ItemCount;
	int DirtyCount;
};

CWorldParts* CWorldParts_Create();
void CWorldParts_CreateLevelBitmap(CWorldParts* self, bool BlackBackground);
void CWorldParts_CenterVPOnPlayer(CWorldParts* self);
void CWorldParts_LimitVPLevel(CWorldParts* self);
void CWorldParts_RemoveAll(CWorldParts* self);
void CWorldParts_Remove(CWorldParts* self, int PlayFieldXin, int PlayFieldYin);
void CWorldParts_RemoveType(CWorldParts* self, int PlayFieldXin, int PlayFieldYin, int Type);
void CWorldParts_Sort(CWorldParts* self);
void CWorldParts_Add(CWorldParts* self, CWorldPart* WorldPart);
void CWorldParts_Load(CWorldParts* self, char* Filename, bool FromData);
bool CWorldParts_Save(CWorldParts* self, char* Filename);
void CWorldParts_Move(CWorldParts* self);
int CWorldParts_ClearDirty(CWorldParts* self, bool BlackBackGround);
void CWorldParts_AddDirty(CWorldParts* self, CWorldPart* Part);
int CWorldParts_Draw(CWorldParts* self, bool BlackBackGround);
void CWorldParts_deinit(CWorldParts* self);
int CWorldParts_GroupCount(CWorldParts* self, int GroupIn);
CWorldPart* CWorldParts_PartAtPosition(CWorldParts* self, int PlayFieldXin, int PlayFieldYin);
int CWorldParts_TypeAtPosition(CWorldParts* self, int PlayFieldXin, int PlayFieldYin);

#endif