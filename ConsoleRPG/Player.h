#pragma once
class Player
{
public:
	Player();
	void init(int level, int health, int attack, int defense, int experience);

	//Setters
	void setPos(int x, int y);

	//Getters
	void getPos(int &x, int &y);

private:
	//Properties
	int _level;
	int _health;
	int _attack;
	int _defense;
	int _experience;

	//postion
	int _x;
	int _y;

};

