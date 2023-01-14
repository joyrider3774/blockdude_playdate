#ifndef CWOLRDPART_H
#define CWOLRDPART_H

#include "commonvars.h"
#include "cworldparts.h"

#define MOVEQUESIZE 100



typedef struct SPoint SPoint;
struct SPoint {
    int X, Y;
};

typedef struct CWorldParts CWorldParts;
typedef struct CWorldPart CWorldPart;
struct CWorldPart {
	int MoveDelayCounter;
	bool FirstArriveEventFired;
	int Type, MoveSpeed, MoveDelay, Xi, Yi, X, Y, AnimPhase, PlayFieldX, PlayFieldY, Z, Group;
	int MoveQueBack;
	int MoveQueFront;
	SPoint MoveQue[MOVEQUESIZE];
	bool PickupLeft, PickupRight;
	CWorldPart *Player;
	bool AttachedToPlayer;
	bool isAttaching;
	bool isDetaching;
	int AtOrDetachingMoveCounter;
	CWorldParts *ParentList;
	bool IsMoving;
	bool Selected;
	bool NeedToMoveLeft;
	bool ItemAttached;
	bool NeedToMoveRight;
	int AnimCounter, AnimBase, AnimDelay, AnimDelayCounter, AnimPhases;
};

CWorldPart* CWorldPart_create(const int PlayFieldXin, const int PlayFieldYin, const int Typein, const int Zin, const int GroupIn);
void CWorldPart_MoveQueClear(CWorldPart* self);
void CWorldPart_MoveQuePopBack(CWorldPart* self);
void CWorldPart_MoveQuePushBack(CWorldPart* self, SPoint point);
void CWorldPart_MoveQueInsert(CWorldPart* self, int pos, SPoint point);
void CWorldPart_AddToMoveQue(CWorldPart* self, int PlayFieldXIn, int PlayFieldYIn);
bool CWorldPart_MovesInQue(CWorldPart* self);
void CWorldPart_AttachToPlayer(CWorldPart* self, CWorldPart* PlayerIn);
void CWorldPart_DeattachFromPlayer(CWorldPart* self);
void CWorldPart_SetAnimPhase(CWorldPart* self, int AnimPhaseIn);
void CWorldPart_MoveTo(CWorldPart* self, const int PlayFieldXin, const int PlayFieldYin);
void CWorldPart_Event_ArrivedOnNewSpot(CWorldPart* self);
void CWorldPart_Event_BeforeDraw(CWorldPart* self);
void CWorldPart_Event_Moving(CWorldPart* self, int ScreenPosX, int ScreenPosY);
void CWorldPart_SetPosition(CWorldPart* self, const int PlayFieldXin, const int PlayFieldYin);
bool CWorldPart_CanMoveTo(CWorldPart* self, const int PlayFieldXin, const int PlayFieldYin);
void CWorldPart_Move(CWorldPart* self);
void CWorldPart_Draw(CWorldPart* self);

#endif