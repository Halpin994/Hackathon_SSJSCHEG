// Hackathon_SSJSCHEG.cpp : Defines the entry point for the console application.
//
#pragma comment(lib, "SDL2_image.lib")

#include "stdafx.h"
#include <SDL.h>
#include "Enemy.h"
#include "AudioManager.h"

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

	AudioManager::GetInstance()->Init();
	AudioManager::GetInstance()->LoadMedia();
	AudioManager::GetInstance()->PlaySoundEffect(1);

	SDL_Point ePos;
	ePos.x = 100;
	ePos.y = 100;
	Enemy en = Enemy(ePos, 77, 62, r, 0);
#pragma region SDL STUFF

			bool quit = false;

			SDL_Event e;

			//AudioManager::GetInstance()->PlaySoundEffect(1);

			while (!quit) {
				while (SDL_PollEvent(&e) != 0) 
				{
				}
				//controls gameState added in game menu feature
				r.Begin();
				switch (gameState) 
				{
					
					
				case MENU:
					en.Draw(r);
					break;
				case PLAY:
					break;
					
				}
				r.End();
			}

	return EXIT_SUCCESS;
}

