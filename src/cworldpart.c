#include <stdbool.h>
#include "commonvars.h"
#include "cworldpart.h"
#include "sound.h"

CWorldPart* CWorldPart_create(const int PlayFieldXin, const int PlayFieldYin, const int Typein,  const int GroupIn)
{
	CWorldPart* Result = pd->system->realloc(NULL, sizeof(CWorldPart));
	if (Result)
	{
		Result->MoveQueFront = -1;
		Result->MoveQueBack = -1;
		Result->Player = NULL;
		Result->AttachedPart = NULL;
		Result->NeedToMoveLeft = false;
		Result->NeedToMoveRight = false;
		Result->PickupLeft = false;
		Result->PickupRight = false;
		Result->AnimCounter = 0;
		Result->AnimBase = 0;
		Result->AnimDelay = 0;
		Result->AnimDelayCounter = 0;
		Result->AnimPhases = 0;
		Result->Dirty = false;
		Result->PlayFieldX = PlayFieldXin;
		Result->PlayFieldY = PlayFieldYin;
		Result->Xi = 0;
		Result->Yi = 0;
		Result->X = PlayFieldXin * TileWidth;
		Result->Y = PlayFieldYin * TileHeight;
		Result->Type = Typein;
		Result->MoveDelay = 0;
		Result->MoveDelayCounter = 0;
		Result->IsMoving = false;
		Result->MoveSpeed = 0;
		Result->ParentList = 0;
		Result->AnimPhase = 0;
		Result->PrevDrawAnimPhase = 0;
		Result->Selected = false;
		Result->FirstArriveEventFired = false;
		Result->Group = GroupIn;
		Result->PrevDrawX = -TileWidth;
		Result->PrevDrawY = -TileHeight;
		Result->PrevDrawPlayFieldX = -1;
		Result->PrevDrawPlayFieldY = -1;


		if (Typein == IDPlayer)
		{
			Result->AnimBase = AnimBaseLeft;
			Result->AnimPhases = 4;
			Result->AnimCounter = 1;
			Result->AnimDelay = PlayerAnimDelay;
			Result->MoveSpeed = GameMoveSpeed;
			Result->AnimDelayCounter = 0;
		}

		if (Typein == IDBox)
		{
			Result->MoveSpeed = GameMoveSpeed;
		}
	}
	return Result;
}



void CWorldPart_MoveQueClear(CWorldPart* self)
{
	self->MoveQueBack = -1;
	self->MoveQueFront = -1;
}

void CWorldPart_MoveQuePopBack(CWorldPart* self)
{
	if (self->MoveQueBack > -1)
		self->MoveQueBack--;

	if (self->MoveQueBack == -1)
		self->MoveQueFront = -1;
}

void CWorldPart_MoveQuePushBack(CWorldPart* self, SPoint point)
{
	if (self->MoveQueBack < MOVEQUESIZE - 1)
	{
		if (self->MoveQueFront == -1)
			self->MoveQueFront = 0;
		self->MoveQueBack++;
		self->MoveQue[self->MoveQueBack] = point;
	}
}

void CWorldPart_MoveQueInsert(CWorldPart* self, int pos, SPoint point)
{
	if ((self->MoveQueBack < MOVEQUESIZE - 1) && (pos <= self->MoveQueBack))
	{
		if (self->MoveQueFront == -1)
			self->MoveQueFront = 0;
		self->MoveQueBack++;

		for (int i = self->MoveQueBack; i > pos; i--)
		{
			self->MoveQue[i] = self->MoveQue[i - 1];
		}

		self->MoveQue[pos] = point;
	}
}

void CWorldPart_AddToMoveQue(CWorldPart* self, int PlayFieldXIn, int PlayFieldYIn)
{
	SPoint Temp = { .X = PlayFieldXIn, .Y = PlayFieldYIn };

	if (self->MoveQueBack == -1)
		CWorldPart_MoveQuePushBack(self, Temp);
	else
		CWorldPart_MoveQueInsert(self, self->MoveQueFront, Temp);
}


bool CWorldPart_MovesInQue(CWorldPart* self)
{
	return (self->MoveQueBack > -1);
}

void CWorldPart_AttachToPlayer(CWorldPart* self, CWorldPart* PlayerIn)
{
	PlayerIn->AttachedPart = self;
	self->Player = PlayerIn;
}

void CWorldPart_DeattachFromPlayer(CWorldPart* self, CWorldPart* PlayerIn)
{
	PlayerIn->AttachedPart = NULL;
	self->Player = NULL;
}

void CWorldPart_SetAnimPhase(CWorldPart* self, int AnimPhaseIn)
{
	self->AnimPhase = AnimPhaseIn;
}


bool CWorldPart_MoveTo(CWorldPart* self, const int PlayFieldXin, const int PlayFieldYin)
{
	bool Result = false;
	if (!self->IsMoving && ((PlayFieldXin != self->PlayFieldX) || (PlayFieldYin != self->PlayFieldY)))
	{
		if (self->Type == IDPlayer)
		{
			if (CWorldPart_CanMoveTo(self, PlayFieldXin, PlayFieldYin))
			{
				Result = true;
				if (self->ParentList && (self != self->ParentList->IgnorePart) && (self->Group != GroupNone))
				{
					if ((self->PlayFieldX >= 0) && (self->PlayFieldY >= 0))
					{
						self->ParentList->PositionalItems[self->Group][self->PlayFieldX][self->PlayFieldY] = NULL;
					}
					self->ParentList->PositionalItems[self->Group][PlayFieldXin][PlayFieldYin] = self;
				}

				self->PlayFieldX = PlayFieldXin;
				self->PlayFieldY = PlayFieldYin;
				self->IsMoving = true;
				//Right
				if (self->X < self->PlayFieldX * TileWidth)
				{
					//this comes from a jump and falling down
					if (!self->NeedToMoveRight)
					{
						CWorldPart* Tmp = CWorldParts_PartAtPosition(self->ParentList, PlayFieldXin, PlayFieldYin + 1);
						if (Tmp != NULL)
						{
							if ((Tmp->Group == GroupFloor) || (Tmp->Group == GroupBox))
								playWalkSound();
						}
					}

					self->Xi = self->MoveSpeed;
					if (self->AnimBase != AnimBaseRight)
					{
						self->AnimBase = AnimBaseRight;
						CWorldParts_AddDirty(self->ParentList, self);
					}

					if (self->ParentList)
					{
						//check for a box on top of the player.
						CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX - 1, self->PlayFieldY - 1);
						if(Part)
						{
							if (Part->Group == GroupBox)
							{
								//if one is found move it to the players X position
								CWorldPart_MoveTo(Part, self->PlayFieldX, self->PlayFieldY - 1);
								//AnimBase = 6;
							}
						}
					}
				}
				//left
				if (self->X > self->PlayFieldX * TileWidth)
				{
					if (!self->NeedToMoveLeft)
					{
						CWorldPart* Tmp = CWorldParts_PartAtPosition(self->ParentList, PlayFieldXin, PlayFieldYin + 1);
						if (Tmp)
						{
							if ((Tmp->Group == GroupFloor) || (Tmp->Group == GroupBox))
								playWalkSound();
						}
					}

					self->Xi = -self->MoveSpeed;
					if (self->AnimBase != AnimBaseLeft)
					{
						self->AnimBase = AnimBaseLeft;
						CWorldParts_AddDirty(self->ParentList, self);
					}

					if (self->ParentList)
					{
						//check for a box on top of the player.
						CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX + 1, self->PlayFieldY - 1);
						if (Part)
						{
							if (Part->Group == GroupBox)
							{
								//if one is found move it to the players X position
								CWorldPart_MoveTo(Part, self->PlayFieldX, self->PlayFieldY - 1);
								//AnimBase = 6;
							}
						}
					}
				}

				//up
				if (self->Y > self->PlayFieldY * TileHeight)
				{
					playJumpSound();
					self->Yi = -self->MoveSpeed;
					//animbase = 0 is start of animation for going left, 2 is start for going right
					if (self->AnimBase == AnimBaseLeft)
					{
						self->NeedToMoveLeft = true;
						self->AnimBase = AnimBaseLeftJump;
						CWorldParts_AddDirty(self->ParentList, self);
					}
					else
						if (self->AnimBase == AnimBaseRight)
						{
							self->AnimBase = AnimBaseRightJump;
							self->NeedToMoveRight = true;
							CWorldParts_AddDirty(self->ParentList, self);
						}

					if (self->ParentList)
					{
						//check for a box on top of the player.
						CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX, self->PlayFieldY);
						if (Part)
						{
							if (Part->Group == GroupBox)
							{
								//if one is found move it to the players X position
								CWorldPart_MoveTo(Part, self->PlayFieldX, self->PlayFieldY - 1);
								//AnimBase = 6;
							}
						}
					}
				}
				//down
				if (self->Y < self->PlayFieldY * TileHeight)
				{
					playFallSound();
					self->Yi = self->MoveSpeed;
					if (self->ParentList)
					{

						//check for a box on top of the player.
						CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX, self->PlayFieldY - 2);
						if (Part)
						{
							if (Part->Group == GroupBox)
							{
								//if one is found move it to the players X position
								CWorldPart_MoveTo(Part, self->PlayFieldX, self->PlayFieldY - 1);
								//AnimBase = 6;
							}
						}
					}
				}
			}
			else
			{
				//Right
				if ((self->AnimBase != AnimBaseRight) && (PlayFieldXin > self->PlayFieldX))
				{
					self->MoveDelayCounter = -TileWidth / self->MoveSpeed;
					self->IsMoving = true;
					Result = true;
					self->AnimBase = AnimBaseRight;
					self->AnimCounter = 0;
				}
				//Left
				if ((self->AnimBase != AnimBaseLeft) && (PlayFieldXin < self->PlayFieldX))
				{
					self->MoveDelayCounter = -TileWidth / self->MoveSpeed;
					self->IsMoving = true;
					Result = true;
					self->AnimBase = AnimBaseLeft;
					self->AnimCounter = 0;
				}
				if (self->AnimPhase != self->AnimBase)
				{
					Result = true;
					CWorldParts_AddDirty(self->ParentList, self);
					self->AnimPhase = self->AnimBase;
				}
			}

		}
		else
		{
			if (self->Group == GroupBox)
				if (CWorldPart_CanMoveTo(self, PlayFieldXin, PlayFieldYin))
				{
					Result = true;
					if (self->ParentList && (self != self->ParentList->IgnorePart) && (self->Group != GroupNone))
					{
						if ((self->PlayFieldX >= 0) && (self->PlayFieldY >= 0))
						{
							self->ParentList->PositionalItems[self->Group][self->PlayFieldX][self->PlayFieldY] = NULL;
						}
						self->ParentList->PositionalItems[self->Group][PlayFieldXin][PlayFieldYin] = self;
					}
					self->PlayFieldX = PlayFieldXin;
					self->PlayFieldY = PlayFieldYin;
					if (self->X < self->PlayFieldX * TileWidth)
						self->Xi = self->MoveSpeed;
					if (self->X > self->PlayFieldX * TileWidth)
						self->Xi = -self->MoveSpeed;
					if (self->Y > self->PlayFieldY * TileHeight)
						self->Yi = -self->MoveSpeed;
					if (self->Y < self->PlayFieldY * TileHeight)
						self->Yi = self->MoveSpeed;
					self->IsMoving = true;
				}
		}
	}
	return Result;
}

void CWorldPart_Event_ArrivedOnNewSpot(CWorldPart* self)
{
	switch (self->Type)
	{
	case IDPlayer:
		//check for floor so we can drop down if not found
		bool FloorFound = false;

		//in case the block was attached to a player but blocked by wall the player moved under
		if (self->AttachedPart) 
		{
			if(self->AttachedPart->Group == GroupBox)
			{
				CWorldPart_Event_ArrivedOnNewSpot(self->AttachedPart);
			}
		}

		if (self->PlayFieldY == NrOfRows - 1)
		{
			self->AnimPhases = 4;
			FloorFound = true;
		}

		if (!FloorFound)
		{
			CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX, self->PlayFieldY + 1);
			if (Part)
			{
				if ((Part->Group == GroupFloor) || (Part->Group == GroupBox))
				{
					self->AnimPhases = 4;
					FloorFound = true;
				}
			}
		}

		if (!FloorFound)
		{
			CWorldPart* Part2 = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX, self->PlayFieldY);
			if (Part2)
			{
				//to catch floating exits
				if (Part2->Group == GroupExit)
				{
					self->AnimPhases = 4;
					FloorFound = true;
				}
			}
		}

		if (self->NeedToMoveLeft)
		{
			CWorldPart_MoveTo(self, self->PlayFieldX - 1, self->PlayFieldY);
			self->NeedToMoveLeft = false;
		}

		if (self->NeedToMoveRight)
		{
			CWorldPart_MoveTo(self, self->PlayFieldX + 1, self->PlayFieldY);
			self->NeedToMoveRight = false;
		}

		if (!FloorFound && self->ParentList)
		{
			self->AnimCounter = 0;
			self->AnimPhases = 1;
			CWorldPart_MoveTo(self, self->PlayFieldX, self->PlayFieldY + 1);
		}

		break;
	case IDBox:
		bool PlayerBelow = false;
		bool SomethingBelow = (self->PlayFieldY == NrOfRows - 1);

		CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX, self->PlayFieldY + 1);
		if (Part)
		{
			if (Part->Type == IDPlayer)
			{
				SomethingBelow = true;
				PlayerBelow = true;
			}

			if ((Part->Group == GroupFloor) || (Part->Group == GroupBox) || (Part->Group == GroupPlayer) || (Part->Group == GroupExit))
			{
				SomethingBelow = true;
			}
		}
		
		if (PlayerBelow)
			CWorldPart_AttachToPlayer(self, self->ParentList->Player);
		else
			if ((self->Player) && !CWorldPart_MovesInQue(self))
				CWorldPart_DeattachFromPlayer(self, self->Player);

		//if nothing is below and there are no moves in the queue move it down
		if ((!SomethingBelow) && (!CWorldPart_MovesInQue(self)))
		{
			if (self->Player)
			{
				/*if (!self->Player->IsMoving)
				{
					self->AttachedToPlayer = false;
					self->Player = NULL;
				}*/
				//CWorldPart_Event_ArrivedOnNewSpot(self);
			}
			/*if ((!CWorldPart_CanMoveTo(self, self->PlayFieldX, self->PlayFieldY + 2)) && (self->PlayFieldY < NrOfRows - 1))
			{
				playDropSound();
			}*/
			CWorldPart_MoveTo(self, self->PlayFieldX, self->PlayFieldY + 1);
		}

		
		break;
	}
}

void CWorldPart_Event_BeforeDraw(CWorldPart* self)
{
	if (self->IsMoving)
	{
		self->AnimPhase = self->AnimBase + self->AnimCounter;
		self->AnimDelayCounter++;
		if (self->AnimDelayCounter == self->AnimDelay)
		{
			self->AnimDelayCounter = 0;
			self->AnimCounter++;
			if (self->AnimCounter == self->AnimPhases)
				self->AnimCounter = 0;
		}
	}
	else
	{
		//i commented it normally we should go to animbase
		//	but the walking animation shows weird if do this
		// because there is a single frame where ismoving is false
		// when the player arrived on a new spot and this made the animation look weird
		// side effect is that walking animation remain visible but thats not a big issue
		// people could think it's as designed
		//if (self->AnimPhase != self->AnimBase)
		//{
		//	//self->AnimPhase = self->AnimBase;
		//	self->AnimDelayCounter = 0;
		//}
	}
}

void CWorldPart_Event_Moving(CWorldPart* self, int ScreenPosX, int ScreenPosY)
{
	if (self->Type == IDPlayer)
	{
		if (self->ParentList)
		{
			if ((ScreenPosX > (self->ParentList->ViewPort->MaxScreenX) - HALFWINDOWWIDTH) && (self->Xi > 0))
			{
				if (CViewPort_Move(self->ParentList->ViewPort, self->Xi, self->Yi))
					self->ParentList->AllDirty = self->ParentList->LevelBitmap == NULL;
			}
			if ((ScreenPosX < (self->ParentList->ViewPort->MaxScreenX) - HALFWINDOWWIDTH) && (self->Xi < 0))
			{
				if (CViewPort_Move(self->ParentList->ViewPort, self->Xi, self->Yi))
					self->ParentList->AllDirty = self->ParentList->LevelBitmap == NULL;
			}
			if ((ScreenPosY > (self->ParentList->ViewPort->MaxScreenY) - HALFWINDOWHEIGHT) && (self->Yi > 0))
			{
				if (CViewPort_Move(self->ParentList->ViewPort, self->Xi, self->Yi))
					self->ParentList->AllDirty = self->ParentList->LevelBitmap == NULL;
			}
			if ((ScreenPosY < (self->ParentList->ViewPort->MaxScreenY) - HALFWINDOWHEIGHT) && (self->Yi < 0))
			{
				if (CViewPort_Move(self->ParentList->ViewPort, self->Xi, self->Yi))
					self->ParentList->AllDirty = self->ParentList->LevelBitmap == NULL;
			}
		}
	}
}

bool CWorldPart_SetPosition(CWorldPart* self, const int PlayFieldXin, const int PlayFieldYin)
{
	bool Result = false;
	if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
	{
		if ((self->PlayFieldX != PlayFieldXin) || (self->PlayFieldY != PlayFieldYin))
		{
			if (self->ParentList && (self != self->ParentList->IgnorePart) && (self->Group != GroupNone))
			{
				if ((self->PlayFieldX >= 0) && (self->PlayFieldY >= 0))
				{
					self->ParentList->PositionalItems[self->Group][self->PlayFieldX][self->PlayFieldY] = NULL;
				}
				self->ParentList->PositionalItems[self->Group][PlayFieldXin][PlayFieldYin] = self;
			}
			self->PlayFieldX = PlayFieldXin;
			self->PlayFieldY = PlayFieldYin;
			self->X = PlayFieldXin * TileWidth;
			self->Y = PlayFieldYin * TileHeight;
			//Event_ArrivedOnNewSpot();
			//self->Dirty = true;
			Result = true;
		}
	}
	return Result;
}

bool CWorldPart_CanMoveTo(CWorldPart* self, const int PlayFieldXin, const int PlayFieldYin)
{
	switch (self->Type)
	{
	case IDPlayer:
		if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
		{
			if (self->ParentList)
			{
				//if we move up
				if (PlayFieldYin - self->PlayFieldY < 0)
				{
					//we're facing left
					if (self->AnimBase == AnimBaseLeft)
					{
						//part left from player
						CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX - 1, self->PlayFieldY);
						if (Part)
						{
							//its an exit (can't jump onto it)
							if (Part->Group == GroupExit)
								return false;

							//it's a box
							if (Part->Group == GroupBox)
							{
								//check part below it
								CWorldPart* Part2 = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX - 1, self->PlayFieldY + 1);
								if (Part2)
								{
									//it's not a floor kind so can't jump onto it
									if (!((Part2->Group == GroupFloor) || (Part2->Group == GroupBox) || (Part2->Group == GroupExit)))
									{
										return false;
									}
								}
								else
									return false;

							}

							//check part on final position
							CWorldPart* Part3 = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX - 1, PlayFieldYin);
							if (Part3)
							{
								//it's something else than exit
								if (Part3->Group != GroupExit)
								{
									return false;
								}
							}
						}
						else
							//nothing on the left
							return false;
					}
					else
					{
						//we're facing right
						if (self->AnimBase == AnimBaseRight)
						{
							//check part on right of player
							CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX + 1, self->PlayFieldY);
							if (Part)
							{
								//its an exit can't jump onto that
								if (Part->Group == GroupExit)
									return false;

								//it's a box
								if (Part->Group == GroupBox)
								{
									//check part below it
									CWorldPart* Part2 = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX + 1, self->PlayFieldY + 1);
									if (Part2)
									{
										//it's not a floor kind so can't jump onto it
										if (!((Part2->Group == GroupFloor) || (Part2->Group == GroupBox) || (Part2->Group == GroupExit)))
										{
											return false;
										}

									}
									else
										return false;
								}

								//check part on final position
								CWorldPart* Part3 = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX + 1, PlayFieldYin);
								if (Part3)
								{
									//anything but exit and we can't jump onto it
									if (Part3->Group != GroupExit)
									{
										return false;
									}
								}
							}
							else
								//nothing on the right
								return false;
						}
					}
				}

				CWorldPart* Part4 = CWorldParts_PartAtPosition(self->ParentList, PlayFieldXin, PlayFieldYin);
				if (Part4)
				{
					if (Part4->Group == GroupFloor)
					{
						return false;
					}
					else
					{
						if (Part4->Group == GroupBox)
						{
							//we're moving horizontal or falling down so we can't move into the box
							if (PlayFieldYin - self->PlayFieldY >= 0)
							{
								return false;
							}
							//were moving up
							//check to see if there are no stackboxes or other things on top of the player blocking the jump
							else
							{
								if ((self->AnimBase == AnimBaseLeft) || (self->AnimBase == AnimBaseRight))
								{
									CWorldPart* Part5 = CWorldParts_PartAtPosition(self->ParentList, PlayFieldXin, PlayFieldYin - 1);
									if (Part5)
									{
										if ((Part5->Group == GroupFloor) || (Part5->Group == GroupBox) || (Part5->Group == GroupExit))
										{
											return false;
										}
									}
								}
							}
						}
					}
				}

				//check to see if our attached box has a queue if so we can't move either
				if (self->AttachedPart)
				{
					if (self->AttachedPart->Group == GroupBox)
					{
						if (self->AttachedPart->MoveQueBack > -1)
						{
							return false;
						}
					}
				}
			}
			else
				return false;
		}
		else
			return false;

		//if we want to move up
		if (PlayFieldYin - self->PlayFieldY < 0)
			//only allow jump if we are not on top position
			return self->PlayFieldY - 1 > 0;
		return true;
		break;
	case IDBox:
		if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
		{
			if (self->ParentList)
			{
				CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, PlayFieldXin, PlayFieldYin);
				if (Part)
				{
					if ((Part->Group == GroupFloor) || (Part->Group == GroupBox) || (Part->Group == GroupExit))
					{
						return false;
					}
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
		break;
	default:
		return false;
		break;
	}
}

bool CWorldPart_Move(CWorldPart* self)
{
	bool Result = false;
	//floors & exits don't move
	if ((self->Group == GroupFloor) || (self->Group == GroupExit))
	{
		if (!self->FirstArriveEventFired)
		{
			self->FirstArriveEventFired = true;
			CWorldParts_AddDirty(self->ParentList, self);
			Result = true;
		}
	}
	else
	{
		if (!self->FirstArriveEventFired)
		{
			CWorldPart_Event_ArrivedOnNewSpot(self);
			self->FirstArriveEventFired = true;
			CWorldParts_AddDirty(self->ParentList, self);
			Result = true;
		}

		if (self->IsMoving)
		{
			if (self->MoveDelayCounter == self->MoveDelay)
			{
				Result = true;
				CWorldParts_AddDirty(self->ParentList, self);
				self->X += self->Xi;
				self->Y += self->Yi;
				CWorldPart_Event_Moving(self, self->X, self->Y);
				if ((abs(self->X - (self->PlayFieldX * TileWidth)) < GameMoveSpeed) && (abs(self->Y - (self->PlayFieldY * TileHeight)) < GameMoveSpeed))
				{
					self->IsMoving = false;
					self->Xi = 0;
					self->Yi = 0;
					self->X = self->PlayFieldX * TileWidth;
					self->Y = self->PlayFieldY * TileHeight;
					CWorldPart_Event_ArrivedOnNewSpot(self);
				}

				self->MoveDelayCounter = -1;
			}
			self->MoveDelayCounter++;
		}
		else
		{
			if (self->MoveQueBack > -1)
			{
				if (CWorldPart_CanMoveTo(self, self->MoveQue[self->MoveQueBack].X, self->MoveQue[self->MoveQueBack].Y))
				{
					CWorldPart_MoveTo(self, self->MoveQue[self->MoveQueBack].X, self->MoveQue[self->MoveQueBack].Y);
					CWorldPart_MoveQuePopBack(self);
					Result = true;
				}
				else
				{
					if (self->Player)
					{
						CWorldPart_DeattachFromPlayer(self, self->Player);
					}
					CWorldPart_MoveQueClear(self);
				}
			}
		}
	}
	return Result;
}

void CWorldPart_Draw(CWorldPart* self, bool ClearPrevDrawPosition, bool BlackBackGround, bool UseRealPosition)
{
	LCDBitmapTable* Img = NULL;

	switch (self->Type)
	{
	case IDEmpty:
		Img = IMGEmpty;
		break;
	case IDBox:
		Img = IMGBox;
		break;
	case IDPlayer:
		Img = IMGPlayer;
		break;
	case IDFloor:
		Img = IMGFloor;
		break;
	case IDExit:
		Img = IMGExit;
		break;
	case IDEarthGrassLeft:
		Img = IMGEarthGrassLeft;
		break;
	case IDEarthGrassRight:
		Img = IMGEarthGrassRight;
		break;
	case IDEarthLeft:
		Img = IMGEarthLeft;
		break;
	case IDEarthMiddle:
		Img = IMGEarthMiddle;
		break;
	case IDEarthRight:
		Img = IMGEarthRight;
		break;
	case IDFloatingFloor:
		Img = IMGFloatingFloor;
		break;
	case IDFloatingFloorLeft:
		Img = IMGFloatingFloorLeft;
		break;
	case IDFloatingFloorMiddle:
		Img = IMGFloatingFloorMiddle;
		break;
	case IDFloatingFloorRight:
		Img = IMGFloatingFloorRight;
		break;
	case IDFloorLeft:
		Img = IMGFloorLeft;
		break;
	case IDFloorRight:
		Img = IMGFloorRight;
		break;
	case IDTower:
		Img = IMGTower;
		break;
	case IDStartTower:
		Img = IMGStartTower;
		break;
	case IDTowerShaft:
		Img = IMGTowerShaft;
		break;
	case IDRoof1:
		Img = IMGRoof1;
		break;
	case IDRoof2:
		Img = IMGRoof2;
		break;
	case IDRoofCornerLeft:
		Img = IMGRoofCornerLeft;
		break;
	case IDRoofCornerRight:
		Img = IMGRoofCornerRight;
		break;
	case IDRoofCornerBoth:
		Img = IMGRoofCornerBoth;
		break;
	case IDRoofDownRight:
		Img = IMGRoofDownRight;
		break;
	case IDRoofDownLeft:
		Img = IMGRoofDownLeft;
		break;
	}

	int x, y;
	LCDBitmap* Bitmap;
	if (Img)
	{
		if (ClearPrevDrawPosition)
		{
			Bitmap = pd->graphics->getTableBitmap(Img, self->PrevDrawAnimPhase);

			if (BlackBackGround)
				pd->graphics->setDrawMode(kDrawModeFillBlack);
			else
				pd->graphics->setDrawMode(kDrawModeFillWhite);

			pd->graphics->drawBitmap(Bitmap, self->PrevDrawX, self->PrevDrawY, kBitmapUnflipped);

			pd->graphics->setDrawMode(kDrawModeCopy);
		}
		else
		{
			CWorldPart_Event_BeforeDraw(self);

			Bitmap = pd->graphics->getTableBitmap(Img, self->AnimPhase);

			if (!UseRealPosition && self->ParentList)
			{
				x = self->X - self->ParentList->ViewPort->MinScreenX;
				y = self->Y - self->ParentList->ViewPort->MinScreenY;
			}
			else
			{
				x = self->X;
				y = self->Y;
			}

			self->PrevDrawPlayFieldX = self->PlayFieldX;
			self->PrevDrawPlayFieldY = self->PlayFieldY;
			self->PrevDrawX = x;
			self->PrevDrawY = y;
			self->PrevDrawAnimPhase = self->AnimPhase;

			pd->graphics->drawBitmap(Bitmap, x, y, kBitmapUnflipped);

			if (self->Selected && (self->Type != IDEmpty))
			{
				pd->graphics->drawBitmap(IMGSelection, x, y, kBitmapUnflipped);
			}
		}
	}
}
