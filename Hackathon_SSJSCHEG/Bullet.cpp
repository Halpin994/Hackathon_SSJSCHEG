#include "stdafx.h"
#include "Bullet.h"
#include <cmath>
#pragma comment(lib, "SDL2_image.lib")

Bullet::Bullet(int posX, int posY, int width, int height, Renderer& r, float angle)
{
	/*directionAngle = 0;
	directionAngle = dirAngle;
	*/
	m_render_rect = new SDL_Rect{ posX, posY, width, height };

	//delta2X = InputManager::GetInstance()->GetMousePos().x - m_render_rect->x;
	//delta2Y = InputManager::GetInstance()->GetMousePos().y - m_render_rect->y;

	//float vectorLength = sqrt(delta2X*delta2X + delta2Y*delta2Y);

	//dx = delta2X / vectorLength;
	//dy = delta2Y / vectorLength;
	
	dx = angle;
	//angle = atan2f(delta2Y, delta2X);

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
	/*float delta2X = InputManager::GetInstance()->GetMousePos().x - m_render_rect->x;
	float delta2Y = InputManager::GetInstance()->GetMousePos().y - m_render_rect->y;

	float vectorLength = sqrt(delta2X*delta2X + delta2Y*delta2Y);

	float dx = delta2X / vectorLength;
	float dy = delta2Y / vectorLength;*/

	float SpeedX = cos(dx *3.14159 / 180.0);
	float SpeedY = sin(dx *3.14159 / 180.0);

	m_render_rect->x += SpeedX;
	m_render_rect->y += SpeedY;

	//m_render_rect->x += (cos(angle *3.14159 / 180.0) * 1 / 10)*2;
	//m_render_rect->y += (sin(angle *3.14159 / 180.0) * 1 / 10)*2;

	//float x = cos(angle);
	//float y = sin(angle);

	//m_render_rect->x += (cos(angle *3.14159 / 180.0) * 1 / 10);
	//m_render_rect->y += (sin(angle *3.14159 / 180.0) * 1 / 10);

	//m_render_rect->x += x;
	//m_render_rect->y += y;

	//directionAngle = atan2f(delta2Y, delta2X) * 180 / 3.14159;
	//m_render_rect->x += (cos(directionAngle *3.14159 / 180.0) * 1 / 10);
	//m_render_rect->y += (sin(directionAngle *3.14159 / 180.0) * 1 / 10);

	////////////////////////////////////

	//directionAngle = dirAngle;

	//int x = (cos(directionAngle *3.14159 / 180.0) / 10);
	//int y = (sin(directionAngle *3.14159 / 180.0) / 10);

	//m_render_rect->x += (cos(directionAngle *3.14159 / 180.0) * 1 / 10);
	//m_render_rect->y += (sin(directionAngle *3.14159 / 180.0) * 1 / 10);

	//std::cout << m_render_rect->x << std::endl;
	//std::cout << m_render_rect->y << std::endl;

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