#include "cviewport.h"
#include "commonvars.h"

void CViewPort_SetVPLimit(CViewPort* self, int MinX, int MinY, int MaxX, int MaxY)
{
	if ((MinX < NrOfCols) && (MinX >= 0) && (MaxX < NrOfCols) && (MaxX >= 0) &&
		(MinY < NrOfRows) && (MinY >= 0) && (MaxY < NrOfRows) && (MaxY >= 0))
	{
		//printf("Limit Success\n");
		self->VPLimitMinX = MinX;
		self->VPLimitMinY = MinY;
		self->VPLimitMaxX = MaxX;
		self->VPLimitMaxY = MaxY;
	}
	else
	{
		// printf("Limit Failed\n");
		self->VPLimitMinX = 0;
		self->VPLimitMinY = 0;
		self->VPLimitMaxX = NrOfCols - 1;
		self->VPLimitMaxY = NrOfRows - 1;
	}
	if (self->VPLimitMaxX - self->VPLimitMinX < self->Width - 1)
	{
		if (self->VPLimitMaxX - self->Width - 1 >= 0)
			self->VPLimitMinX = self->VPLimitMaxX - (self->Width - 1);
		else
		{
			self->VPLimitMinX = 0;
			self->VPLimitMaxX = self->VPLimitMinX + (self->Width - 1);
		}
	}
	if (self->VPLimitMaxY - self->VPLimitMinY < self->Height - 1)
	{
		if (self->VPLimitMaxY - self->Height - 1 >= 0)
			self->VPLimitMinY = self->VPLimitMaxY - (self->Height - 1);
		else
		{
			self->VPLimitMinY = 0;
			self->VPLimitMaxY = self->VPLimitMinY + (self->Height - 1);
		}
	}

}


void CViewPort_Move(CViewPort* self, int Xi, int Yi)
{
	if ((self->MinScreenX + Xi <= TileWidth * (self->VPLimitMaxX)) && (self->MinScreenX + Xi >= self->VPLimitMinX * TileWidth) && (self->MaxScreenX + Xi <= TileWidth * (self->VPLimitMaxX)) && (self->MaxScreenX + Xi >= self->VPLimitMinX * TileWidth) &&
		(self->MinScreenY + Yi <= TileHeight * (self->VPLimitMaxY)) && (self->MinScreenY + Yi >= self->VPLimitMinY * TileHeight) && (self->MaxScreenY + Yi <= TileHeight * (self->VPLimitMaxY)) && (self->MaxScreenY + Yi >= self->VPLimitMinY * TileHeight))
	{

		self->MinScreenX += Xi;
		self->MaxScreenX += Xi;
		self->MinScreenY += Yi;
		self->MaxScreenY += Yi;
		self->VPMinX = self->MinScreenX / TileWidth;
		self->VPMinY = self->MinScreenY / TileHeight;
		self->VPMaxX = self->MaxScreenX / TileHeight;
		self->VPMaxY = self->MaxScreenY / TileWidth;
		self->BackgroundX += (Xi / 2);
		self->BackgroundY += (Yi / 2);
	}
}

void CViewPort_SetViewPort(CViewPort* self, int MinX, int MinY, int MaxX, int MaxY)
{
	if ((MinX <= self->VPLimitMaxX) && (MinX >= self->VPLimitMinX) && (MaxX <= self->VPLimitMaxX) && (MaxX >= self->VPLimitMinX) &&
		(MinY <= self->VPLimitMaxY) && (MinY >= self->VPLimitMinY) && (MaxY <= self->VPLimitMaxY) && (MaxY >= self->VPLimitMinY))
	{
		self->VPMinX = MinX;
		self->VPMinY = MinY;
		self->VPMaxX = MaxX;
		self->VPMaxY = MaxY;
		self->MinScreenX = self->VPMinX * TileWidth;
		self->MinScreenY = self->VPMinY * TileHeight;
		self->MaxScreenX = self->VPMaxX * TileHeight;
		self->MaxScreenY = self->VPMaxY * TileWidth;
	}
	else
	{
		self->VPMinX = MinX;
		self->VPMinY = MinY;
		self->VPMaxX = MaxX;
		self->VPMaxY = MaxY;
		if (self->VPMinX < self->VPLimitMinX)
		{
			self->VPMinX = self->VPLimitMinX;
			self->VPMaxX = self->VPLimitMinX + (WINDOW_WIDTH / TileWidth) - 1;

		}
		if (self->VPMaxX > self->VPLimitMaxX)
		{
			self->VPMinX = self->VPLimitMaxX - (WINDOW_WIDTH / TileWidth) + 1;
			self->VPMaxX = self->VPLimitMaxX;
		}
		if (self->VPMinY < self->VPLimitMinY)
		{
			self->VPMaxY = self->VPLimitMinY + (WINDOW_HEIGHT / TileHeight) - 1;
			self->VPMinY = self->VPLimitMinY;
		}
		if (self->VPMaxY > self->VPLimitMaxY)
		{
			self->VPMinY = self->VPLimitMaxY - (WINDOW_HEIGHT / TileHeight) + 1;
			self->VPMaxY = self->VPLimitMaxY;
		}
		self->MinScreenX = self->VPMinX * TileWidth;
		self->MinScreenY = self->VPMinY * TileHeight;
		self->MaxScreenX = self->VPMaxX * TileHeight;
		self->MaxScreenY = self->VPMaxY * TileWidth;
	}
	self->Width = self->VPMaxX - self->VPMinX + 1;
	self->Height = self->VPMaxY - self->VPMinY + 1;
}

CViewPort* CViewPort_Create(int MinX, int MinY, int MaxX, int MaxY, int MinX2, int MinY2, int MaxX2, int MaxY2)
{
	CViewPort* Result = pd->system->realloc(NULL, sizeof(CViewPort));
	if (Result)
	{
		if ((MinX < NrOfCols) && (MinX >= 0) && (MaxX < NrOfCols) && (MaxX >= 0) &&
			(MinY < NrOfRows) && (MinY >= 0) && (MaxY < NrOfRows) && (MaxY >= 0))
		{
			Result->VPMinX = MinX;
			Result->VPMinY = MinY;
			Result->VPMaxX = MaxX;
			Result->VPMaxY = MaxY;
			Result->MinScreenX = Result->VPMinX * TileWidth;
			Result->MinScreenY = Result->VPMinY * TileHeight;
			Result->MaxScreenX = Result->VPMaxX * TileHeight;
			Result->MaxScreenY = Result->VPMaxY * TileWidth;
		}
		else
		{
			Result->VPMinX = 0;
			Result->VPMinY = 0;
			Result->VPMaxX = (WINDOW_WIDTH / TileWidth) - 1;
			Result->VPMaxY = (WINDOW_HEIGHT / TileHeight) - 1;
			Result->MinScreenX = 0;
			Result->MinScreenY = 0;
			Result->MaxScreenX = WINDOW_WIDTH;
			Result->MaxScreenY = WINDOW_HEIGHT;
		}
		if ((MinX2 < NrOfCols) && (MinX2 >= 0) && (MaxX2 < NrOfCols) && (MaxX2 >= 0) &&
			(MinY2 < NrOfRows) && (MinY2 >= 0) && (MaxY2 < NrOfRows) && (MaxY2 >= 0))
		{
			Result->VPLimitMinX = MinX2;
			Result->VPLimitMinY = MinY2;
			Result->VPLimitMaxX = MaxX2;
			Result->VPLimitMaxY = MaxY2;
		}
		else
		{
			Result->VPLimitMinX = 0;
			Result->VPLimitMinY = 0;
			Result->VPLimitMaxX = NrOfCols - 1;
			Result->VPLimitMaxY = NrOfRows - 1;
		}
		Result->BackgroundX = 0;
		Result->BackgroundY = 0;
		Result->Width = Result->VPMaxX - Result->VPMinX + 1;
		Result->Height = Result->VPMaxY - Result->VPMinY + 1;
	}
	return Result;
}
