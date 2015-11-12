#include "stdafx.h"
#include "Player.h"
#include <cmath>
#pragma comment(lib, "SDL2_image.lib")

Player::Player(SDL_Point pos, int width, int height, Renderer& r, int t) :type(t)
{
	m_render_rect = new SDL_Rect{ pos.x, pos.y, width, height };

	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = width;
	rect.h = height;

	LoadAssets(r);

	directionAngle = 0;

	differenceX = 0;
	differenceY = 0;
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

void Player::Update(Renderer &r, float delta)
{
	// Mouse position
	float mouseX = InputManager::GetInstance()->GetMousePos().x;
	float mouseY = InputManager::GetInstance()->GetMousePos().y;

	differenceX = mouseX - rect.x;
	differenceY = mouseY - rect.y;

	// Face sprite in direction of cursor
	directionAngle = atan2(differenceY, differenceX) * 180 / 3.141;
	//directionAngle = atan2(differenceY, differenceX);

	// Update bullets
	for (std::vector<Bullet>::iterator it = bullets.begin(); it < bullets.end(); ++it)
		it._Ptr->Update(delta, directionAngle);

	// Destroy bullets
	for (std::vector<Bullet>::iterator it = bullets.begin(); it < bullets.end(); ++it)
	{
		if (it._Ptr->offScreen())
		{
			bullets.erase(it);
		}
	}

	if (InputManager::GetInstance()->IsKeyDown(SDLK_SPACE) || InputManager::GetInstance()->IsMouseButtonDown(SDL_BUTTON_LEFT))
	{
		Shoot(r);
	}
}// End update

void Player::Shoot(Renderer &r)
{
	// Bullet initial position
	SDL_Point bulletPoint;
	bulletPoint.x = rect.x;
	bulletPoint.y = rect.y;

	int x = (int)bulletPoint.x;
	int y = (int)bulletPoint.y;

	Bullet bullet = Bullet(x, y, 12, 12, r, 0, directionAngle);
	bullets.push_back(bullet);
}

void Player::Draw(Renderer &r)
{
	//SDL_RenderCopy(r.getRender(), m_texture, NULL, m_render_rect);

	//std::cout << directionAngle << std::endl;

	SDL_RenderCopyEx(r.getRender(), m_texture, NULL, m_render_rect, directionAngle, NULL, SDL_FLIP_NONE);

	for (std::vector<Bullet>::iterator it = bullets.begin(); it < bullets.end(); ++it)
		it._Ptr->Draw(r);
}