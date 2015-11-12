#pragma once
#include <SDL.h>
#include "Renderer.h"
#include <SDL_image.h>
using namespace std;
class Enemy
{
private:
	SDL_Rect* m_render_rect;
	SDL_Texture* m_texture = NULL;
	SDL_Surface* m_surface;
	SDL_Point position;
	int type;
	bool alive;
	void LoadAssets(Renderer &r);
	float direction;
	
public:
	Enemy(SDL_Point pos, int width, int height, Renderer &r, int t);
	~Enemy();
	void Update();
	void Movement();
	void CollisionResponse();
	bool CheckAlive();
	void Draw(Renderer &r);
};

