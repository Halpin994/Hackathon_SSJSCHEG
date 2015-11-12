// Hackathon_SSJSCHEG.cpp : Defines the entry point for the console application.
//
#pragma comment(lib, "SDL2_image.lib")

#include "stdafx.h"
#include <SDL.h>
#include "Enemy.h"

//Screen dimension constants
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;

const int MENU = 0, PLAY = 1;
int gameState;

SDL_Renderer* gRenderer = NULL;

int wmain()
{
	gameState = MENU;
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;
	//SDL
	Renderer r = Renderer(SCREEN_WIDTH, SCREEN_HEIGHT);

	Enemy en = Enemy(200,200, 62/3, 77/3, r, 0);
	Enemy en1 = Enemy(400, 100, 62 / 3, 77 / 3, r, 0);

#pragma region SDL STUFF

			bool quit = false;
			float oldTime = SDL_GetTicks();
			float delta = 0.f;
			float newTime = 0.f;
			SDL_Event e;

			while (!quit) {
				while (SDL_PollEvent(&e) != 0) 
				{
				}
				//controls gameState added in game menu feature
				r.Begin();
				switch (gameState) 
				{
					
					
				case MENU:
					//en.Movement();
					newTime = SDL_GetTicks();
					delta = newTime - oldTime;
					oldTime = newTime;

					en.Update(delta);
					en.Draw(r);
					en1.Update(delta);
					en1.Draw(r);

					break;
				case PLAY:
					break;
					
				}
				
				r.End();
			}

	return EXIT_SUCCESS;
}

