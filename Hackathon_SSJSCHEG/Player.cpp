#include "stdafx.h"
#include "Player.h"
#pragma comment(lib, "SDL2_image.lib")

Player::Player(SDL_Point pos, int width, int height, Renderer& r, int t) :type(t)
{
	m_render_rect = new SDL_Rect{ pos.x, pos.y, width, height };

	LoadAssets(r);
}

Player::~Player()
{
}

void Player::LoadAssets(Renderer& r)
{
	std::string path = "cowboy.png";
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

void Player::Update()
{

}

void Player::Movement()
{
}

void Player::CollisionResponse()
{
}

bool Player::CheckAlive()
{
	return alive;
}

void Player::Draw(Renderer &r)
{
	SDL_RenderCopy(r.getRender(), m_texture, NULL, m_render_rect);
}