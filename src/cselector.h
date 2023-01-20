#ifndef CSELECTOR_H
#define CSELECTOR_H

#include "commonvars.h"

typedef struct CSelector CSelector;

struct CSelector {
	CWorldParts* PList;
	CWorldPart* Part;
	int Selection;
};

CSelector* CSelector_Create(CWorldParts* List);
bool CSelector_MoveUp(CSelector* self);
bool CSelector_MoveDown(CSelector* self);
bool CSelector_MoveLeft(CSelector* self);
bool CSelector_MoveRight(CSelector* self);
void CSelector_IncSelection(CSelector* self);
void CSelector_DecSelection(CSelector* self);
bool CSelector_SetPosition(CSelector* self, const int PlayFieldXin, const int PlayFieldYin);
void CSelector_Draw(CSelector* self);
void CSelector_deinit(CSelector* self);

#endif