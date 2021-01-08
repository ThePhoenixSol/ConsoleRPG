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

