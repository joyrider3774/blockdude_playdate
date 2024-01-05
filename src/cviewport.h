#ifndef CVIEWPORT_H
#define CVIEWPORT_H

#include <stdbool.h>

typedef struct CViewPort CViewPort;

struct CViewPort
{
	int VPMinX;
	int VPMinY;
	int VPMaxX;
	int VPMaxY;
	int MinScreenX;
	int MinScreenY;
	int MaxScreenX;
	int MaxScreenY;
	int Width;
	int Height;
	int VPLimitMinX;
	int VPLimitMaxX;
	int VPLimitMinY;
	int VPLimitMaxY;
	int BackgroundX;
	int BackgroundY;
};

CViewPort* CViewPort_Create(int MinX, int MinY, int MaxX, int MaxY, int MinX2, int MinY2, int MaxX2, int MaxY2);
void CViewPort_SetVPLimit(CViewPort* self, int MinX, int MinY, int MaxX, int MaxY);
bool CViewPort_Move(CViewPort* self, int Xi, int Yi);
void CViewPort_SetViewPort(CViewPort* self, int MinX, int MinY, int MaxX, int MaxY);
void CViewPort_deinit(CViewPort* self);

#endif
