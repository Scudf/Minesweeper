#include "stdafx.h"
#include <Windows.h>
#include <GL/glew.h>
#include <ctime>
#include <random>

#include "stdio.h"
#include "Game.h"


int main()
{
#ifndef _DEBUG
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	srand((unsigned int)time(0));

	Game* game = new Game();
	game->initialize();

	while (game->update())
	{

	}

	delete game;

	return 0;
}

