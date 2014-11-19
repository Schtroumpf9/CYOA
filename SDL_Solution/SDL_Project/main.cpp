#include "std.h"
#include "Game.h"
#include <vld.h>

int main(int argc, char* args[])
{
	CGame cGame;
	cGame.Initialize();
	while(cGame.Run()) {}
	cGame.Shutdown();
	return 0;
}