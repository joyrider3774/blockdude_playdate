#include "commonvars.h"
#include "cworldpart.h"
#include "sound.h"

CWorldPart* CWorldPart_create(const int PlayFieldXin, const int PlayFieldYin, const int Typein, const int Zin, const int GroupIn)
{
	CWorldPart* Result = pd->system->realloc(NULL, sizeof(CWorldPart));
	if (Result)
	{
		Result->MoveQueFront = -1;
		Result->MoveQueBack = -1;
		Result->Player = NULL;
		Result->AttachedToPlayer = false;
		Result->NeedToMoveLeft = false;
		Result->ItemAttached = false;
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
		Result->Z = Zin;
		Result->Group = GroupIn;
		Result->PrevDrawX = -1;
		Result->PrevDrawY = -1;

		if (Typein == IDPlayer)
		{
			Result->AnimBase = AnimBaseLeft;
			Result->AnimPhases = 4;
			Result->AnimCounter = 1;
			Result->AnimDelay = PlayerAnimDelay; //als er eerst gedrawed wordt en dan gemoved, als het andersom is gebeurd er 1 tje
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
	self->Player = PlayerIn;
	self->AttachedToPlayer = true;
}

void CWorldPart_DeattachFromPlayer(CWorldPart* self)
{
	self->Player = NULL;
	self->AttachedToPlayer = false;
}

void CWorldPart_SetAnimPhase(CWorldPart* self, int AnimPhaseIn)
{
	self->AnimPhase = AnimPhaseIn;
}


bool CWorldPart_MoveTo(CWorldPart* self, const int PlayFieldXin, const int PlayFieldYin)
{
	bool Result = false;
	if (!self->IsMoving)
	{
		if (self->Type == IDPlayer)
		{
			if (CWorldPart_CanMoveTo(self, PlayFieldXin, PlayFieldYin))
			{
				Result = true;
				self->PlayFieldX = PlayFieldXin;
				self->PlayFieldY = PlayFieldYin;
				self->IsMoving = true;
				//Right
				if (self->X < self->PlayFieldX * TileWidth)
				{
					//this comes from a jump and falling down
					if (!self->NeedToMoveRight)
					{
						//if(!CWorldPart_CanMoveTo(self, PlayFieldXin, PlayFieldYin + 1))
						//	playWalkSound();

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
						for (int Teller = 0; Teller < self->ParentList->ItemCount; Teller++)
						{
							//check for a box on top of the player.
							if (((self->ParentList->Items[Teller]->Group == GroupBox)) && ((self->ParentList->Items[Teller]->PlayFieldX == self->PlayFieldX - 1) && (self->ParentList->Items[Teller]->PlayFieldY == self->PlayFieldY - 1)))
							{
								//if one is found move it to the players X position
								CWorldPart_MoveTo(self->ParentList->Items[Teller], self->PlayFieldX, self->PlayFieldY - 1);
								//AnimBase = 6;
								break;
							}
						}
					}
				}
				//left
				if (self->X > self->PlayFieldX * TileWidth)
				{
					//this comes from a jump and from falling down
					if (!self->NeedToMoveLeft)
					{
						//if(!CWorldPart_CanMoveTo(self, PlayFieldXin, PlayFieldYin + 1))
						//	playWalkSound();

						CWorldPart* Tmp = CWorldParts_PartAtPosition(self->ParentList, PlayFieldXin, PlayFieldYin + 1);
						if (Tmp != NULL)
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
						for (int Teller = 0; Teller < self->ParentList->ItemCount; Teller++)
						{
							//check for a box on top of the player
							if (((self->ParentList->Items[Teller]->Group == GroupBox)) && ((self->ParentList->Items[Teller]->PlayFieldX == self->PlayFieldX + 1) && (self->ParentList->Items[Teller]->PlayFieldY == self->PlayFieldY - 1)))
							{
								CWorldPart_MoveTo(self->ParentList->Items[Teller], self->PlayFieldX, self->PlayFieldY - 1);
								break;
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
						for (int Teller = 0; Teller < self->ParentList->ItemCount; Teller++)
						{
							if (((self->ParentList->Items[Teller]->Group == GroupBox)) && ((self->ParentList->Items[Teller]->PlayFieldY == self->PlayFieldY) && (self->ParentList->Items[Teller]->PlayFieldX == self->PlayFieldX)))
							{
								CWorldPart_MoveTo(self->ParentList->Items[Teller], self->PlayFieldX, self->PlayFieldY - 1);
								break;
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
						for (int Teller = 0; Teller < self->ParentList->ItemCount; Teller++)
						{
							if (((self->ParentList->Items[Teller]->Group == GroupBox)) && ((self->ParentList->Items[Teller]->PlayFieldY == self->PlayFieldY-2) && (self->ParentList->Items[Teller]->PlayFieldX == self->PlayFieldX)))
							{
								CWorldPart_MoveTo(self->ParentList->Items[Teller], self->PlayFieldX, self->PlayFieldY -1);
								break;
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
					Result = true;
					self->AnimBase = AnimBaseRight;
					CWorldParts_AddDirty(self->ParentList, self);
				}
				//Left
				if ((self->AnimBase != AnimBaseLeft) && (PlayFieldXin < self->PlayFieldX))
				{
					Result = true;
					self->AnimBase = AnimBaseLeft;
					CWorldParts_AddDirty(self->ParentList, self);
				}
				self->AnimPhase = self->AnimBase + self->AnimCounter;
			}

		}
		else
		{
			if (self->Group == GroupBox)
				if ((PlayFieldXin != self->PlayFieldX) || (PlayFieldYin != self->PlayFieldY))
					if (CWorldPart_CanMoveTo(self, PlayFieldXin, PlayFieldYin))
					{
						Result = true;
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
	{
		//floorfound check moet hier gebeuren zodat wanneer men van een "blok springt" naar benede valt en niet blijft voortschuiven
		bool FloorFound = false;
		if (self->ParentList)
		{
			for (int Teller = 0; Teller < self->ParentList->ItemCount; Teller++)
			{
				if ((self->ParentList->Items[Teller]->PlayFieldX == self->PlayFieldX) && (self->ParentList->Items[Teller]->PlayFieldY == self->PlayFieldY + 1) &&
					((self->ParentList->Items[Teller]->Group == GroupFloor) || (self->ParentList->Items[Teller]->Group == GroupBox)))
				{
					self->AnimPhases = 4;
					FloorFound = true;
					break;
				}

				//to catch floating exits
				if ((self->ParentList->Items[Teller]->PlayFieldX == self->PlayFieldX) && (self->ParentList->Items[Teller]->PlayFieldY == self->PlayFieldY) &&
					(self->ParentList->Items[Teller]->Group == GroupExit))
				{
					self->AnimPhases = 4;
					FloorFound = true;
					break;
				}

			}
		}

		if (self->PlayFieldY == NrOfRows - 1)
		{
			self->AnimPhases = 4;
			FloorFound = true;
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
	}
	case IDBox:
		if (self->ParentList)
		{
			int PlayerID = 0;
			bool PlayerBelow = false;
			//see if there is a Player below the block
			for (int Teller = 0; Teller < self->ParentList->ItemCount; Teller++)
			{
				if ((self->ParentList->Items[Teller]->PlayFieldX == self->PlayFieldX) && (self->ParentList->Items[Teller]->PlayFieldY == self->PlayFieldY + 1) &&
					(self->ParentList->Items[Teller]->Type == IDPlayer))
				{

					PlayerBelow = true;
					PlayerID = Teller;
					break;

				}
			}
			if (PlayerBelow)
				CWorldPart_AttachToPlayer(self, self->ParentList->Items[PlayerID]);
			else
				if (self->AttachedToPlayer && !CWorldPart_MovesInQue(self))
					CWorldPart_DeattachFromPlayer(self);

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
		self->AnimPhase = self->AnimBase;
}

void CWorldPart_Event_Moving(CWorldPart* self, int ScreenPosX, int ScreenPosY)
{
	if (self->Type == IDPlayer)
	{
		if ((ScreenPosX > (self->ParentList->ViewPort->MaxScreenX) - HALFWINDOWWIDTH) && (self->Xi > 0))
		{
			if (CViewPort_Move(self->ParentList->ViewPort, self->Xi, self->Yi))
				self->ParentList->AllDirty = true;
		}
		if ((ScreenPosX < (self->ParentList->ViewPort->MaxScreenX) - HALFWINDOWWIDTH) && (self->Xi < 0))
		{
			if (CViewPort_Move(self->ParentList->ViewPort, self->Xi, self->Yi))
				self->ParentList->AllDirty = true;
		}
		if ((ScreenPosY > (self->ParentList->ViewPort->MaxScreenY) - HALFWINDOWHEIGHT) && (self->Yi > 0))
		{
			if (CViewPort_Move(self->ParentList->ViewPort, self->Xi, self->Yi))
				self->ParentList->AllDirty = true;
		}
		if ((ScreenPosY < (self->ParentList->ViewPort->MaxScreenY) - HALFWINDOWHEIGHT) && (self->Yi < 0))
		{
			if (CViewPort_Move(self->ParentList->ViewPort, self->Xi, self->Yi))
				self->ParentList->AllDirty = true;
		}
	}
}

void CWorldPart_SetPosition(CWorldPart* self, const int PlayFieldXin, const int PlayFieldYin)
{
	if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
	{
		self->PlayFieldX = PlayFieldXin;
		self->PlayFieldY = PlayFieldYin;
		self->X = PlayFieldXin * TileWidth;
		self->Y = PlayFieldYin * TileHeight;
		//Event_ArrivedOnNewSpot();
	}
}

bool CWorldPart_CanMoveTo(CWorldPart* self, const int PlayFieldXin, const int PlayFieldYin)
{
	bool Result = true, CanJump = false, FloorFound = false;

	if (!self->FirstArriveEventFired)
		return false;

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
					//check to see
					for (int Teller = 0; Teller < self->ParentList->ItemCount; Teller++)
					{						
						//if a block is left or right besides the player to jump onto,
						if ((((self->ParentList->Items[Teller]->PlayFieldX == self->PlayFieldX - 1) && (self->AnimBase == AnimBaseLeft)) ||
							((self->ParentList->Items[Teller]->PlayFieldX == self->PlayFieldX + 1) && (self->AnimBase == AnimBaseRight))) &&
							(self->ParentList->Items[Teller]->PlayFieldY == self->PlayFieldY) && (self->ParentList->Items[Teller]->Type != IDExit))
						{
							CanJump = self->PlayFieldY-1 > 0;
							//if it is a box check if the box has another box or a floor below it (io check if it's not falling down)
							if (self->ParentList->Items[Teller]->Type == IDBox)
							{
								for (int Teller2 = 0; Teller2 < self->ParentList->ItemCount; Teller2++)
								{
									if ((((self->ParentList->Items[Teller2]->PlayFieldX == self->PlayFieldX - 1) && (self->AnimBase == AnimBaseLeft)) ||
										((self->ParentList->Items[Teller2]->PlayFieldX == self->PlayFieldX + 1) && (self->AnimBase == AnimBaseRight))) &&
										(self->ParentList->Items[Teller2]->PlayFieldY == self->PlayFieldY + 1) &&
										((self->ParentList->Items[Teller2]->Group == GroupFloor) || (self->ParentList->Items[Teller2]->Group == GroupBox) ||
											(self->ParentList->Items[Teller2]->Group == GroupExit)))
									{
										FloorFound = true;
										break;
									}
								}

								if (self->PlayFieldY == NrOfRows - 1)
								{
									FloorFound = true;
								}

								if (!FloorFound)
									CanJump = false;
							}
						}
						//if the place on top the block is not empty
						if (((((self->ParentList->Items[Teller]->PlayFieldX == self->PlayFieldX - 1) && (self->AnimBase == AnimBaseLeft)) ||
							(((self->ParentList->Items[Teller]->PlayFieldX == self->PlayFieldX + 1)) && (self->AnimBase == AnimBaseRight))) &&
							(self->ParentList->Items[Teller]->PlayFieldY == PlayFieldYin)))
						{
							//it's not so we can't move / jump on it
							if (self->ParentList->Items[Teller]->Type != IDExit)
							{
								Result = false;
								break;
							}
						}
					}
				}

				// if the result is always true we will have checked all boxes to see if they are attached or not
				//check for an attached box
				if (Result)
				{
					for (int Teller = 0; Teller < self->ParentList->ItemCount; Teller++)
					{
						if (self->ParentList->Items[Teller]->Group == GroupBox)
						{
							if (self->ParentList->Items[Teller]->AttachedToPlayer)
							{
								if (CWorldPart_MovesInQue(self->ParentList->Items[Teller]))
								{
									Result = false;
									break;
								}
							}
						}

						//if we can still move to it after the jump check
						//if there is an item on the new position
						if (Result)
						{
							if ((self->ParentList->Items[Teller]->PlayFieldX == PlayFieldXin) && (self->ParentList->Items[Teller]->PlayFieldY == PlayFieldYin))
							{
								//and it's a wall or floor, we can't move to it
								if ((self->ParentList->Items[Teller]->Group == GroupFloor))
								{
									Result = false;
									break;
								}
								else
								{
									// it's a box
									if (self->ParentList->Items[Teller]->Group == GroupBox)
									{
										//we're moving horizontal or falling down so we can't move into the box
										if (PlayFieldYin - self->PlayFieldY >= 0)
										{
											Result = false;
											break;
										}
										//were moving up
										//check to see if there are no stackboxes or other things on top of the player blocking the jump
										else
										{
											for (int Teller2 = 0; Teller2 < self->ParentList->ItemCount; Teller2++)
											{
												if ((((self->ParentList->Items[Teller2]->PlayFieldX == self->PlayFieldX) && (self->AnimBase == AnimBaseLeft)) ||
													((self->ParentList->Items[Teller2]->PlayFieldX == self->PlayFieldX) && (self->AnimBase == AnimBaseRight))) &&
													(self->ParentList->Items[Teller2]->PlayFieldY == PlayFieldYin - 1) &&
													((self->ParentList->Items[Teller2]->Group == GroupFloor) || (self->ParentList->Items[Teller2]->Group == GroupBox) ||
														(self->ParentList->Items[Teller2]->Group == GroupExit)))
												{
													Result = false;
													break;
												}
											}
											if (!Result)
											{
												break;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
			Result = false;
		//if we want to move up
		if (PlayFieldYin - self->PlayFieldY < 0)
			return (CanJump && Result);
		else
			return Result;
		break;

	case IDBox:
		if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
		{
			if (self->ParentList)
			{
				for (int Teller = 0; Teller < self->ParentList->ItemCount; Teller++)
				{
					if (((self->ParentList->Items[Teller]->PlayFieldX == PlayFieldXin) && (self->ParentList->Items[Teller]->PlayFieldY == PlayFieldYin)))
						if ((self->ParentList->Items[Teller]->Group == GroupFloor) || (self->ParentList->Items[Teller]->Group == GroupBox) ||
							(self->ParentList->Items[Teller]->Group == GroupExit))
						{
							Result = false;
							break;
						}
				}
			}
			else
			{
				Result = false;
			}
		}
		else
		{
			Result = false;
		}
		return Result;
		break;
	default:
		return false;
	}
}

void CWorldPart_Move(CWorldPart* self)
{
	bool FloorFound = false;
	bool SomethingBelow = false;
	
	switch (self->Type)
	{
	case IDPlayer:
		if (!self->FirstArriveEventFired)
		{
			CWorldPart_Event_ArrivedOnNewSpot(self);
			self->FirstArriveEventFired = true;
			CWorldParts_AddDirty(self->ParentList, self);
		}

		if (self->ParentList)
		{
			for (int Teller = 0; Teller < self->ParentList->ItemCount; Teller++)
			{
				if ((self->ParentList->Items[Teller]->PlayFieldX == self->PlayFieldX) && (self->ParentList->Items[Teller]->PlayFieldY == self->PlayFieldY + 1) &&
					((self->ParentList->Items[Teller]->Group == GroupFloor) || (self->ParentList->Items[Teller]->Group == GroupBox)))
				{
					self->AnimPhases = 4;
					FloorFound = true;
					break;
				}
			}
		}

		if (self->PlayFieldY == NrOfRows - 1)
		{
			self->AnimPhases = 4;
			FloorFound = true;
		}

		if (!FloorFound && self->ParentList)
		{
			self->AnimPhases = 1;
			self->AnimCounter = 0;

			CWorldPart_MoveTo(self, self->PlayFieldX, self->PlayFieldY + 1);
		}


		if (self->IsMoving)
		{
			if (self->MoveDelayCounter == self->MoveDelay)
			{
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
			if (self->MoveQueBack > -1)
			{
				if (CWorldPart_CanMoveTo(self, self->MoveQue[self->MoveQueBack].X, self->MoveQue[self->MoveQueBack].Y))
				{
					CWorldPart_MoveTo(self, self->MoveQue[self->MoveQueBack].X, self->MoveQue[self->MoveQueBack].Y);
					CWorldPart_MoveQuePopBack(self);
				}
				else
					CWorldPart_MoveQueClear(self);
			}
		break;
	case IDBox:
		if (!self->FirstArriveEventFired)
		{
			CWorldPart_Event_ArrivedOnNewSpot(self);
			self->FirstArriveEventFired = true;
			CWorldParts_AddDirty(self->ParentList, self);
		}
		//move moet hergedaan worden zodat de player als er op z'n start positie geen block onder hem zit toch naar beneden valt en niet blijft staan

		if (self->ParentList)
		{
			//see if there is something below the block
			for (int Teller = 0; Teller < self->ParentList->ItemCount; Teller++)
			{
				if ((self->ParentList->Items[Teller]->PlayFieldX == self->PlayFieldX) && (self->ParentList->Items[Teller]->PlayFieldY == self->PlayFieldY + 1) &&
					((self->ParentList->Items[Teller]->Group == GroupFloor) ||
						(self->ParentList->Items[Teller]->Group == GroupBox) || (self->ParentList->Items[Teller]->Group == GroupPlayer) ||
						(self->ParentList->Items[Teller]->Group == GroupExit)))
				{
					SomethingBelow = true;
					break;
				}
			}
		}

		//assume ground on edges
		if (self->PlayFieldY == NrOfRows - 1)
		{
			SomethingBelow = true;
		}

		//if nothing is below and there are no moves in the queue move it down
		if ((!SomethingBelow) && (!CWorldPart_MovesInQue(self)))
		{
			if (self->AttachedToPlayer)
			{
				if (!self->Player->IsMoving)
				{
					self->AttachedToPlayer = false;
					self->Player = NULL;
				}
			}
			if ((!CWorldPart_CanMoveTo(self, self->PlayFieldX, self->PlayFieldY + 2)) && (self->PlayFieldY < NrOfRows - 1))
			{
				playDropSound();
			}
			CWorldPart_MoveTo(self, self->PlayFieldX, self->PlayFieldY + 1);
		}

		if (self->IsMoving)
		{
			if (self->MoveDelayCounter == self->MoveDelay)
			{
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
				}
				else
					CWorldPart_MoveQueClear(self);
			}
		}
		break;
	default:
		//floors & exits don't move
		if ((self->Group == GroupFloor) || (self->Group == GroupExit))
		{
			if (!self->FirstArriveEventFired)
				self->FirstArriveEventFired = true;
		}
		else
		{
			if (!self->FirstArriveEventFired)
			{
				CWorldPart_Event_ArrivedOnNewSpot(self);
				self->FirstArriveEventFired = true;
				CWorldParts_AddDirty(self->ParentList, self);
			}

			if (self->IsMoving)
			{
				if (self->MoveDelayCounter == self->MoveDelay)
				{
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
					}
					else
						CWorldPart_MoveQueClear(self);
				}
			}
		}
		break;
	}
}

void CWorldPart_Draw(CWorldPart* self, bool ClearPrevDrawPosition, bool BlackBackGround)
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

	if (ClearPrevDrawPosition)
	{
		if (BlackBackGround)
			pd->graphics->setDrawMode(kDrawModeFillBlack);
		else
			pd->graphics->setDrawMode(kDrawModeFillWhite);
		Bitmap = pd->graphics->getTableBitmap(Img, self->PrevDrawAnimPhase);
		pd->graphics->drawBitmap(Bitmap, self->PrevDrawX, self->PrevDrawY, kBitmapUnflipped);
		pd->graphics->setDrawMode(kDrawModeCopy);
	}
	else
	{

		CWorldPart_Event_BeforeDraw(self);


		Bitmap = pd->graphics->getTableBitmap(Img, self->AnimPhase);
		if (self->ParentList)
		{
			x = self->X - self->ParentList->ViewPort->MinScreenX;
			y = self->Y - self->ParentList->ViewPort->MinScreenY;
		}
		else
		{
			x = self->X;
			y = self->Y;
		}
		self->PrevDrawX = x;
		self->PrevDrawY = y;
		self->PrevDrawAnimPhase = self->AnimPhase;
		pd->graphics->drawBitmap(Bitmap, x, y, kBitmapUnflipped);

		if (self->Selected && (self->Type != IDEmpty))
		{
			if (self->ParentList)
			{
				pd->graphics->drawBitmap(IMGSelection, self->X - self->ParentList->ViewPort->MinScreenX, self->Y - self->ParentList->ViewPort->MinScreenY, kBitmapUnflipped);
			}
			else
			{
				pd->graphics->drawBitmap(IMGSelection, self->X, self->Y, kBitmapUnflipped);
			}
		}
	}
}
