#pragma once
#include <SDL.h>
#include "Renderer.h"
#include <SDL_image.h>

using namespace std;
class Bullet
{
private:
	SDL_Rect* m_render_rect;
	SDL_Rect rect;
	SDL_Texture* m_texture = NULL;
	SDL_Surface* m_surface;
	SDL_Point m_position;
	int type;
	bool alive;
	void LoadAssets(Renderer &r);
	float directionAngle;

	float directionX;
	float directionY;

public:
	Bullet(SDL_Point pos, int width, int height, Renderer &r, int t, float directionAngle);
	~Bullet();
	void Update(float delta, float dirAngle);
	void Rotate(float angle);
	void CollisionResponse();
	bool CheckAlive();
	void Draw(Renderer &r);
	void Shoot();
	bool offScreen();
};
