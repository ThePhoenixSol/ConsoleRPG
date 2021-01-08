#include <random>
#include <ctime>
#include "Enemy.h"


Enemy::Enemy(std::string name, char tile, int level, int health, int attack, int defense, int xp)
{
	_name = name;
	_tile = tile;
	_level = level;
	_health = health;
	_attack = attack;
	_defense = defense;
	_experienceVal = xp;

}

int Enemy::attack()
{
	static std::default_random_engine randEngine(time(NULL));
	std::uniform_int_distribution <int> attackRoll(0, _attack);

	return attackRoll(randEngine);
}

int Enemy::takeDamage(int attack)
{
	attack -= _defense;
	//check if the attack does damage
	if (attack > 0)
	{
		_health -= attack;
		//check if player died
		if (_health <= 0)
		{
			return _experienceVal;
		}
	}
	return 0;
}

//Sets pos of enemy
void Enemy::setPos(int x, int y)
{
	_x = x;
	_y = y;
}

//Gets pos of enemy
void Enemy::getPos(int& x, int& y)
{
	x = _x;
	y = _y;
}

char Enemy::getMove(int playerX, int playerY)
{
	static std::default_random_engine randEngine(time(NULL));
	std::uniform_int_distribution <int> moveRoll(0, 6);

	int distance;
	int dx = _x - playerX;
	int dy = _y - playerY;
	int adx = abs(dx);
	int ady = abs(dy);
	distance = adx + ady;
	
	if (distance <= 4)
	{
		//Moving along the X axis
		if (adx > ady)
		{
			if (dx > 0)
			{
				return 'a';
			}
			else
			{
				return 'd';
			}
		}
		else //Move along the Y axis
		{
			if (dy > 0)
			{
				return 'w';
			}
			else
			{
				return 's';
			}
		}
	}

	int randomMove = moveRoll(randEngine);
	switch (randomMove)
	{
	case 0:
		return 'w';
	case 1:
		return 'a';
	case 2:
		return 's';
	case 3:
		return 'd';
	default:
		return '.';
	}

}

