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
	CWorldPart* AttachedPart;
	int MoveDelayCounter;
	bool FirstArriveEventFired;
	int Type, MoveSpeed, MoveDelay, Xi, Yi, X, Y, AnimPhase, PlayFieldX, PlayFieldY, Z, Group;
	int MoveQueBack;
	int MoveQueFront;
	SPoint MoveQue[MOVEQUESIZE];
	bool PickupLeft, PickupRight;
	CWorldPart *Player;
	CWorldParts *ParentList;
	bool IsMoving;
	bool Selected;
	bool NeedToMoveLeft;
	bool ItemAttached;
	bool NeedToMoveRight;
	bool Dirty;
	int PrevDrawPlayFieldX;
	int PrevDrawPlayFieldY;
	int PrevDrawX;
	int PrevDrawY;
	int PrevDrawAnimPhase;
	int AnimCounter, AnimBase, AnimDelay, AnimDelayCounter, AnimPhases;
};

CWorldPart* CWorldPart_create(const int PlayFieldXin, const int PlayFieldYin, const int Typein, const int GroupIn);
void CWorldPart_MoveQueClear(CWorldPart* self);
void CWorldPart_MoveQuePopBack(CWorldPart* self);
void CWorldPart_MoveQuePushBack(CWorldPart* self, SPoint point);
void CWorldPart_MoveQueInsert(CWorldPart* self, int pos, SPoint point);
void CWorldPart_AddToMoveQue(CWorldPart* self, int PlayFieldXIn, int PlayFieldYIn);
bool CWorldPart_MovesInQue(CWorldPart* self);
void CWorldPart_AttachToPlayer(CWorldPart* self, CWorldPart* PlayerIn);
void CWorldPart_DeattachFromPlayer(CWorldPart* self, CWorldPart* PlayerIn);
void CWorldPart_SetAnimPhase(CWorldPart* self, int AnimPhaseIn);
bool CWorldPart_MoveTo(CWorldPart* self, const int PlayFieldXin, const int PlayFieldYin);
void CWorldPart_Event_ArrivedOnNewSpot(CWorldPart* self);
void CWorldPart_Event_BeforeDraw(CWorldPart* self);
void CWorldPart_Event_Moving(CWorldPart* self, int ScreenPosX, int ScreenPosY);
bool CWorldPart_SetPosition(CWorldPart* self, const int PlayFieldXin, const int PlayFieldYin);
bool CWorldPart_CanMoveTo(CWorldPart* self, const int PlayFieldXin, const int PlayFieldYin);
bool CWorldPart_Move(CWorldPart* self);
void CWorldPart_Draw(CWorldPart* self, bool ClearPrevDrawPosition, bool BlackBackGround, bool UseRealPosition);

#endif