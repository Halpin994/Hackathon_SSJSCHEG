#include "Enemy.h"

#ifndef ENEMYMANAGER 
#define ENEMYMANAGER

class EnemyManager
{
public:
	//Functions
	static EnemyManager* GetInstance();
	~EnemyManager()
	{
		instanceFlag = false;
	}

	void Spawn(int wave);
	void RemoveEnemyFromList(Enemy enemy);

	//Variables

private:
	//Functions
	EnemyManager()
	{
		//private constructor
	}

	//Variables
	const int MINIMUM_ENEMIES = 1;

	std::list<Enemy>  typeOneEnemies;
	std::list<Enemy>  typeTwoEnemies;
	std::list<Enemy>  typeThreeEnemies;

	static bool instanceFlag;
	static EnemyManager *instance;
};

#endif
