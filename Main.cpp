#include "Core\Application.h"

BLA

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE prevInst, PSTR cmdLine, int cmdShow)
{

#if defined(DEBUG) || defined(_DEBUG)
	FIND_MEMORY_LEAKS;
#endif

	Application app;

	if(!app.Initialize(hInst))
		return cmdShow;

	app.Run();

	app.Shutdown();

	return cmdShow;
}
