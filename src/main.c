#include "pd_api.h"
#include "commonvars.h"
#include "maingameloop.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif

int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, uint32_t arg)
{
	if ( event == kEventInit )
	{
		setPDPtr(playdate);
		playdate->display->setRefreshRate(FRAMERATE);
		playdate->system->setUpdateCallback(mainLoop, NULL);
		setupGame();
	}
	
	return 0;
}
