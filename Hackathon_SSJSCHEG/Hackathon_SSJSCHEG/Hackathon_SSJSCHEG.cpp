// Hackathon_SSJSCHEG.cpp : Defines the entry point for the console application.
//
#pragma comment(lib, "SDL2_image.lib")

#include "stdafx.h"
#include <SDL.h>
#include "Enemy.h"
#include "AudioManager.h"
#include "Menu.h"
#include "Level.h"

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
	Enemy en = Enemy(200,200, 62/3, 77/3, r, 0);
	Enemy en1 = Enemy(400, 100, 62 / 3, 77 / 3, r, 0);
	Level lvl = Level(r);


	// MENU
	SDL_Point bPos;
	bPos.x = 0;
	bPos.y = 0;
	Menu background = Menu(bPos, SCREEN_WIDTH, SCREEN_HEIGHT, r, 0, "background");

	SDL_Point pPos;
	pPos.x = SCREEN_WIDTH/3;
	pPos.y = SCREEN_HEIGHT/4;
	Menu playBtn = Menu(pPos, 263, 44, r, 0, "playBtn");

	SDL_Point e2Pos;
	e2Pos.x = (SCREEN_WIDTH / 2) - 50;
	e2Pos.y = (SCREEN_HEIGHT / 2) -20;
	Menu exitBtn = Menu(e2Pos, 111, 45, r, 0, "exitBtn");

#pragma region SDL STUFF

			bool quit = false;
			float oldTime = SDL_GetTicks();
			float delta = 0.f;
			float newTime = 0.f;
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

					//detect button click
					if (e.type == SDL_MOUSEBUTTONDOWN) 
					{
						//If the left mouse button was pressed
						if (e.button.button == SDL_BUTTON_LEFT) 
						{
							//Get the mouse offsets
							int mouse_x = e.button.x;
							int mouse_y = e.button.y;

							if (playBtn.IsClicked(mouse_x, mouse_y)) 
							{
								gameState = PLAY;
							}
							else if (exitBtn.IsClicked(mouse_x, mouse_y))
							{
								quit = true;
							}
						}
					}// End detect button click


					background.Draw(r);
					playBtn.Draw(r);
					exitBtn.Draw(r);
					break;
				case PLAY:
					newTime = SDL_GetTicks();
					delta = newTime - oldTime;
					oldTime = newTime;

					en.Update(delta);
					lvl.Draw(r);
					en.Draw(r);
					en1.Update(delta);
					en1.Draw(r);
					en.Draw(r);
					break;
					
				}
				
				r.End();
			}

	return EXIT_SUCCESS;
}

