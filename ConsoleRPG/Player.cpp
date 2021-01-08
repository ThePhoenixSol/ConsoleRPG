#include <random>
#include <ctime>
#include "Player.h"

//Constructor, initialize char pos to 0
Player::Player()
{
	_x = 0;
	_y = 0;
}

int Player::attack()
{
	static std::default_random_engine randEngine(time(NULL));
	std::uniform_int_distribution <int> attackRoll(0, _attack);

	return attackRoll(randEngine);
}

int Player::takeDamage(int attack)
{
	attack -= _defense;
	//check if the attack does damage
	if (attack > 0)
	{
		_health -= attack;
		//check if player died
		if (_health <= 0)
		{
			return 1;
		}
	}
	return 0;
}

//Initialize the player with properties
void Player::init(int level, int health, int attack, int defense, int experience)
{
	_level = level;
	_health = health;
	_attack = attack;
	_defense = defense;
	_experience = experience;
}

//Sets pos of player
void Player::setPos(int x, int y)
{
	_x = x;
	_y = y;
}

void Player::addExperience(int experience)
{
	_experience += experience;
	
	//Level Up
	while (_experience >= _nextLevel)
	{
		printf("Level Up!!!\n");
		_health += 10;
		_attack += 10;
		_defense += 10;
		_experience -= _nextLevel;
		_nextLevel *= 3;
		_level++;
		system("PAUSE");
	}
}

//Gets pos of player
void Player::getPos(int &x, int &y)
{
	x = _x;
	y = _y;
}