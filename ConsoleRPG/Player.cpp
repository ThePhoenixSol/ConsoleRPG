#include "Player.h"

//Constructor, initialize char pos to 0
Player::Player()
{
	_x = 0;
	_y = 0;
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

//Gets pos of player
void Player::getPos(int &x, int &y)
{
	x = _x;
	y = _y;
}