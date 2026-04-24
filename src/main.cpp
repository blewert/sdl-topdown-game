#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"

int main(int argc, char** argv)
{
	Game game = Game(800, 600, false);
	
	bool running = false;

	while (!game.NeedsExit())
	{
		game.Update();
		game.Render();
	}

	return 0;
}