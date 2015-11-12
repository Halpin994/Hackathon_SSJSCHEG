#include "stdafx.h"

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


void EnemyManager::Spawn(int wave)
{
	//Need a better way to decide max enemies
	int maxEnemies = MINIMUM_ENEMIES * wave;

	for (int i = 0; i < maxEnemies; i++)
	{
		int newRand = randomRange(0, 3);

		/*
		switch (newRand)
		{
		case 0:
			Enemy enemy;
			typeOneEnemies.push_back(enemy);
			break;
		case 1:
			typeTwoEnemies.push_back(enemy);
			break;
		case 2:
			typeThreeEnemies.push_back(enemy);
			break;
		}
		*/

	}
}

void EnemyManager::RemoveEnemyFromList(Enemy enemy)
{
	switch (enemy.GetType())
	{
	case 0:
		typeOneEnemies.remove(enemy);
		break;
	case 1:
		typeTwoEnemies.remove(enemy);
		break;
	case 2:
		typeThreeEnemies.remove(enemy);
		break;
	}
}


float random()
{
	return rand() / (float)RAND_MAX;
}

int randomRange(int low, int high)
{
	int range = high - low;
	return (int)(random() * range) + low;
}


