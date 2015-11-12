#include "stdafx.h"
#include "Enemy.h"
#pragma comment(lib, "SDL2_image.lib")

Enemy::Enemy(SDL_Point pos, int width, int height, Renderer& r, int t):type(t)
{
	m_render_rect = new SDL_Rect{ position.x + width / 2, position.y + height / 2,width,height };

	LoadAssets(r);
}

Enemy::~Enemy()
{
}

void Enemy::LoadAssets(Renderer& r)
{
	std::string path = "enemy.png";
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

void Enemy::Update()
{
	m_render_rect->x = position.x;
	m_render_rect->y = position.y;
}

void Enemy::Movement()
{
}

void Enemy::CollisionResponse()
{
}

bool Enemy::CheckAlive()
{
	return alive;
}

void Enemy::Draw(Renderer &r)
{
	SDL_RenderCopy(r.getRender(), m_texture, NULL, m_render_rect);
}

int Enemy::GetType()
{
	return type;
}