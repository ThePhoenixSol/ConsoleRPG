#pragma once
#include <vector>
#include <string>
#include "Player.h"


class Enemy
{
public:
	Enemy(std::string name, char tile, int level, int health, int attack, int defense, int xp);
	int attack();
	int takeDamage(int attack);

	//Setters
	void setPos(int x, int y);

	//Getters
	void getPos(int &x, int &y);
	std::string getName() { return _name;}
	char getMove(int playerX, int playerY);
	char getTile() { return _tile; }

private:
	//Properties
	std::string _name;
	char _tile;
	int _level;
	int _health;
	int _attack;
	int _defense;
	int _experienceVal;

	//Position
	int _x;
	int _y;

	std::vector <std::string> droppedItems;

};

