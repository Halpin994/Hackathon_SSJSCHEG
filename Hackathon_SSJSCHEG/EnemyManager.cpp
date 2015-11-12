#include "stdafx.h"
#include "Renderer.h"

float random()
{
	return rand() / (float)RAND_MAX;
}

int randomRange(int low, int high)
{
	int range = high - low;
	return (int)(random() * range) + low;
}


bool EnemyManager::instanceFlag = false;
EnemyManager* EnemyManager::instance = NULL;

EnemyManager* EnemyManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new EnemyManager();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}


void EnemyManager::Spawn(int wave, Renderer& r)
{
	//Need a better way to decide max enemies
	int maxEnemies = MINIMUM_ENEMIES * wave;

	for (int i = 0; i < maxEnemies; i++)
	{
		int newRand = randomRange(0, 3);
		SpawnEnemy(newRand, r);
	}
}


void EnemyManager::SpawnEnemy(int type, Renderer& r)
{
	switch (type)
	{
	case 0:
		typeOneEnemies.push_back(Enemy(40, 40, 20, 20, r, type));
		break;
	case 1:
		typeTwoEnemies.push_back(Enemy(40, 40, 20, 20, r, type));
		break;
	case 2:
		typeThreeEnemies.push_back(Enemy(40, 40, 20, 20, r, type));
		break;
	}
}

void EnemyManager::RemoveEnemyFromList(Enemy* enemy)
{
	switch (enemy->GetType())
	{
	case 0:
		typeOneEnemies.remove(*enemy);
		break;
	case 1:
		typeTwoEnemies.remove(*enemy);
		break;
	case 2:
		typeThreeEnemies.remove(*enemy);
		break;
	}
}


void EnemyManager::Update(float delta)
{
	for each (Enemy enemy in typeOneEnemies)
	{
		std::list<Enemy>::iterator iter = std::find(typeOneEnemies.begin(), typeOneEnemies.end(), enemy);
		iter->Update(delta);
	}

	for each (Enemy enemy in typeTwoEnemies)
	{
		std::list<Enemy>::iterator iter = std::find(typeTwoEnemies.begin(), typeTwoEnemies.end(), enemy);
		iter->Update(delta);
	}

	for each (Enemy enemy in typeThreeEnemies)
	{
		std::list<Enemy>::iterator iter = std::find(typeThreeEnemies.begin(), typeThreeEnemies.end(), enemy);
		iter->Update(delta);
	}
}

void EnemyManager::Draw(Renderer& r)
{
	for each (Enemy enemy in typeOneEnemies)
	{
		enemy.Draw(r);
	}

	for each (Enemy enemy in typeTwoEnemies)
	{
		enemy.Draw(r);
	}

	for each (Enemy enemy in typeThreeEnemies)
	{
		enemy.Draw(r);
	}
}


