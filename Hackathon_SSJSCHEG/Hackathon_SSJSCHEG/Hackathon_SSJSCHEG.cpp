// Hackathon_SSJSCHEG.cpp : Defines the entry point for the console application.
//
#pragma comment(lib, "SDL2_image.lib")

#include "stdafx.h"
#include <SDL.h>
#include "Enemy.h"
#include "AudioManager.h"
#include "Menu.h"
#include "Level.h"
#include "Player.h"
#include "Timer.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

#include "SDL_thread.h"
#include "SDL_timer.h"

//Screen dimension constants
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;

const int MENU = 0, PLAY = 1;
int gameState;

SDL_Renderer* gRenderer = NULL;

//Set text color as black
SDL_Color textColor = { 0, 0, 0, 255 };

//The application timer
Timer timer;

//The frames per second timer
Timer fpsTimer;

//Start counting frames per second
int countedFrames = 0;

//In memory text stream
std::stringstream timeText;

float avgFPS = 0;
float highestAvgFPS = 0;

// THREADS \\

//Our test thread function
int renderThreadFunction(void* data);

// THREADS \\

void calculateFPS();

int wmain()
{
#pragma region Other Stuff
			// Hide cursor
	SDL_ShowCursor(0);

	gameState = PLAY;
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
	Enemy en = Enemy(200, 200, 62 / 3, 77 / 3, r, 0);
	Enemy en1 = Enemy(400, 100, 62 / 3, 77 / 3, r, 0);
	Level lvl = Level(r);

	// MENU
	SDL_Point bPos;
	bPos.x = 0;
	bPos.y = 0;
	Menu background = Menu(bPos, SCREEN_WIDTH, SCREEN_HEIGHT, r, 0, "background");

	SDL_Point pPos;
	pPos.x = SCREEN_WIDTH / 3;
	pPos.y = SCREEN_HEIGHT / 4;
	Menu playBtn = Menu(pPos, 263, 44, r, 0, "playBtn");

	SDL_Point e2Pos;
	e2Pos.x = (SCREEN_WIDTH / 2) - 50;
	e2Pos.y = (SCREEN_HEIGHT / 2) - 20;
	Menu exitBtn = Menu(e2Pos, 111, 45, r, 0, "exitBtn");
	// Player
	SDL_Point playerPos;
	playerPos.x = SCREEN_WIDTH / 2 - 25;
	playerPos.y = SCREEN_HEIGHT / 2 - 10;
	Player player = Player(playerPos, 44, 32, r, 0);


	// THREADS \\

	// Run the thread
	//Player * p = (); // pointer to object
	void * pv = &player;          // pointer to void
	Player * p2 = static_cast<Player *>(pv); // pointer to the same object

	int data;
	SDL_Thread* threadID = SDL_CreateThread(renderThreadFunction, "RenderThread", (void*)p2);

	// THREADS \\
#pragma endregion


#pragma region SDL STUFF

			bool quit = false;
			float oldTime = SDL_GetTicks();
			float delta = 0.f;
			float newTime = 0.f;
			SDL_Event e;
			fpsTimer.start();


			while (!quit) 
			{
				while (SDL_PollEvent(&e) != 0) 
				{
					InputManager::GetInstance()->UpdatePolledEvents(e);
				}

				if (e.button.button == SDL_SCANCODE_ESCAPE)
					quit = true;

					// THREADS \\

					// THREADS \\

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
					player.Update(r, delta);
					player.Draw(r);

					//calculateFPS();

					break;
					
				}
				InputManager::GetInstance()->UpdateState();
				
				r.End();
			}

			//Remove timer in case the call back was not called
			SDL_WaitThread(threadID, NULL);

	return EXIT_SUCCESS;
}

void calculateFPS()
{
	//Calculate and correct fps
	avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}
	//cout << avgFPS << endl;

	if (avgFPS > highestAvgFPS)
	{
		highestAvgFPS = avgFPS;
	}

	cout << avgFPS << endl;

	++countedFrames;
}

int renderThreadFunction(void* data)
{

	// Print incoming data
	printf("Running thread with value = %d\n", (int)data);

	return 0;
}

