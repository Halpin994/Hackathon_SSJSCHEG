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

	void Spawn(int wave, Renderer& r);
	void RemoveEnemyFromList(Enemy* enemy);
	void Update(float delta);
	void Draw(Renderer& r);

	//Variables

private:
	//Functions
	EnemyManager()
	{
		//private constructor
		typeOneEnemies = std::list<Enemy>();
		typeTwoEnemies = std::list<Enemy>();
		typeThreeEnemies = std::list<Enemy>();
	}

	void SpawnEnemy(int type, Renderer& r);

	//Variables
	const int MINIMUM_ENEMIES = 1;

	std::list<Enemy>  typeOneEnemies;
	std::list<Enemy>  typeTwoEnemies;
	std::list<Enemy>  typeThreeEnemies;

	static bool instanceFlag;
	static EnemyManager *instance;
};

#endif
