#include "introstate.h"
#include "commonvars.h"
#include "pd_api.h"

void IntroInit(void)
{
	NeedRedraw = true;
}

void Intro(void)
{
	if (GameState == GSIntroInit)
	{
		IntroInit();
		GameState -= GSDiff;
	}
	framecounter++;

	if (((currButtons & kButtonA) && (!(prevButtons & kButtonA))) ||
		((currButtons & kButtonB) && (!(prevButtons & kButtonB))))
	{
		GameState = GSTitleScreenInit;
	}

	if (currButtons & kButtonUp)
	{
		showFps = true;
	}

	if (currButtons & kButtonDown)
	{
		showDebugInfo = true;
	}

	if (NeedRedraw)
	{
		NeedRedraw = false;
		switch (IntroScreenNr)
		{
		case 1:
			pd->graphics->drawBitmap(IMGIntro1, 0, 0, kBitmapUnflipped);
			break;
		case 2:
			pd->graphics->drawBitmap(IMGIntro2, 0, 0, kBitmapUnflipped);
			break;
		case 3:
			pd->graphics->drawBitmap(IMGIntro3, 0, 0, kBitmapUnflipped);
			break;
		case 4:
			pd->graphics->drawBitmap(IMGIntro4, 0, 0, kBitmapUnflipped);
			break;
		}
	}

	if (framecounter > FRAMERATE * 3)
	{
		framecounter = 0;
		IntroScreenNr++;
		NeedRedraw = true;
		if (IntroScreenNr > 4)
			GameState = GSTitleScreenInit;
	}
}