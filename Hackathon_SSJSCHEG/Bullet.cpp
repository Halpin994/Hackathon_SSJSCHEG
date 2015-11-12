#include "stdafx.h"
#include "Bullet.h"
#include <cmath>
#pragma comment(lib, "SDL2_image.lib")

Bullet::Bullet(SDL_Point pos, int width, int height, Renderer& r, int t, float dirAngle) :type(t)
{
	directionAngle = dirAngle;

	m_render_rect = new SDL_Rect{ pos.x, pos.y, width, height };

	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = width;
	rect.h = height;

	LoadAssets(r);
}

Bullet::~Bullet()
{
}

void Bullet::LoadAssets(Renderer& r)
{
	std::string path = "Bullet.png";
	m_surface = IMG_Load(path.c_str());

	if (m_surface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		m_texture = SDL_CreateTextureFromSurface(r.getRender(), m_surface);
		if (m_texture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(m_surface);
	}
}

void Bullet::Update(float delta, float dirAngle)
{
	//directionAngle = dirAngle;

	m_render_rect->x += (cos(directionAngle *3.14159 / 180.0) * 1 / 10);
	m_render_rect->y += (sin(directionAngle *3.14159 / 180.0) * 1 / 10);

	//m_render_rect->x += directionAngle;
	//m_render_rect->y += directionAngle;
}

bool Bullet::offScreen()
{
	//Screen dimension constants
	const int SCREEN_WIDTH = 900;
	const int SCREEN_HEIGHT = 600;

	/*if ((m_render_rect->x + m_render_rect->w) > SCREEN_WIDTH
		|| (m_render_rect->x + m_render_rect->w) < 0
		|| (m_render_rect->y + m_render_rect->h) > SCREEN_HEIGHT
		|| (m_render_rect->y + m_render_rect->h) < 0)
	{
		return true;
	}*/
	return false;
}

void Bullet::CollisionResponse()
{
}

bool Bullet::CheckAlive()
{
	return alive;
}

void Bullet::Draw(Renderer &r)
{
	//SDL_RenderCopy(r.getRender(), m_texture, NULL, m_render_rect);

	//std::cout << directionAngle << std::endl;

	SDL_RenderCopyEx(r.getRender(), m_texture, NULL, m_render_rect, directionAngle, NULL, SDL_FLIP_NONE);
}