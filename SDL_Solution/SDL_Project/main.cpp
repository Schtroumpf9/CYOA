#include "std.h"
#include "Game.h"

int main(int argc, char* args[])
{
	// Memory Leak Detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	CGame cGame;
	cGame.Initialize();
	while(cGame.Run()) {}
	cGame.Shutdown();
	return 0;
}