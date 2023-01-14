#ifndef CWORLDPARTS_H
#define CWORLDPARTS_H

#include "commonvars.h"
#include "cviewport.h"

typedef struct CWorldPart CWorldPart;
typedef struct CWorldParts CWorldParts;

struct CWorldParts {
	bool DisableSorting;
	CViewPort* ViewPort;
	CWorldPart* Items[NrOfRows * NrOfCols];
	int ItemCount;
};

CWorldParts* CWorldParts_Create();
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
void CWorldParts_Draw(CWorldParts* self);
void CWorldParts_deinit(CWorldParts* self);
int CWorldParts_TypeAtPosition(CWorldParts* self, int PlayFieldXin, int PlayFieldYin);

#endif