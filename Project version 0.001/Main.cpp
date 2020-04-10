#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_image.h"
#include "SDL/include/SDL_mixer.h"

#pragma comment(lib,"SDL/libx86/SDL2.lib")
#pragma comment(lib,"SDL/libx86/SDL2main.lib")

enum class main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};


int main(int argc, char* argv[]) {

	Game game;



	system("pause");
	return 0;
	
}