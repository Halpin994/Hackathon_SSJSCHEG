// Hackathon_SSJSCHEG.cpp : Defines the entry point for the console application.
//
#pragma comment(lib, "SDL2_image.lib")

#include "stdafx.h"
#include <SDL.h>
#include "Enemy.h"
#include "Menu.h"
#include "Player.h"
#include "InputManager.h"

//Screen dimension constants
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;

const int MENU = 0, PLAY = 1;
int gameState;

SDL_Renderer* gRenderer = NULL;

int wmain()
{
	// Hide cursor
	SDL_ShowCursor(0);

	gameState = PLAY;
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;
	//SDL
	Renderer r = Renderer(SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Point ePos;
	ePos.x = 100;
	ePos.y = 100;
	Enemy en = Enemy(ePos, 77, 62, r, 0);

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

	// Player
	SDL_Point playerPos;
	playerPos.x = SCREEN_WIDTH / 2;
	playerPos.y = SCREEN_HEIGHT / 2;
	Player player = Player(playerPos, 44, 32, r, 0);

#pragma region SDL STUFF

			bool quit = false;
			float oldTime = SDL_GetTicks();
			float delta = 0.f;
			float newTime = 0.f;
			SDL_Event e;

			while (!quit) {
				while (SDL_PollEvent(&e) != 0) 
				{
					InputManager::GetInstance()->UpdatePolledEvents(e);
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

					en.Draw(r);
					player.Draw(r);
					player.Update(r, delta);
					break;
					
				}

				// Exit application
				if (InputManager::GetInstance()->IsKeyDown(SDLK_ESCAPE))
				{
					quit = true;
				}

				//// Hide cursor
				//SDL_ShowCursor(0);// Hide

				InputManager::GetInstance()->UpdateState();

				r.End();
			}

	return EXIT_SUCCESS;
}

