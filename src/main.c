#include "main.h"
#include "pd_api.h"
#include "maingameloop.h"
#include "commonvars.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif

int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, uint32_t arg)
{
	if ( event == kEventInit )
	{
		setPDPtr(playdate);
		playdate->system->logToConsole("app.uuid=664315b417744969aa93577f23e9879e");
		playdate->display->setRefreshRate(FRAMERATE);
		playdate->system->setUpdateCallback(mainLoop, NULL);
		setupGame();
	}
	
	return 0;
}
