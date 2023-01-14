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
void CSelector_MoveUp(CSelector* self);
void CSelector_MoveDown(CSelector* self);
void CSelector_MoveLeft(CSelector* self);
void CSelector_MoveRight(CSelector* self);
void CSelector_IncSelection(CSelector* self);
void CSelector_DecSelection(CSelector* self);
void CSelector_SetPosition(CSelector* self, const int PlayFieldXin, const int PlayFieldYin);
void CSelector_Draw(CSelector* self);
void CSelector_deinit(CSelector* self);

#endif