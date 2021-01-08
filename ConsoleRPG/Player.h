#pragma once
class Player
{
public:

	Player();
	void init(int level, int health, int attack, int defense, int experience);

	int attack();
	int takeDamage(int attack);
	
	//Setters
	void setPos(int x, int y);
	void addExperience(int experience);

	//Getters
	void getPos(int &x, int &y);
	std::string getName() { return _playerName; }

private:
	//Properties
	std::string _playerName = "Phoenix";
	int _level = 1;
	int _health;
	int _attack;
	int _defense;
	int _experience;
	int _nextLevel = 50;

	//postion
	int _x;
	int _y;

};

