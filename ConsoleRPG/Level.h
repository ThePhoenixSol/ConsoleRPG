#pragma once
#include <vector>
#include <string>
#include "Player.h"

class Level
{
public:
	Level();

	void load(std::string fileName, Player &player);
	void print();
	void movePlayer(char input, Player& player);

	//Getters
	char getTile(int x, int y);

	//Setters
	void setTile(int x, int y, char tile);

private:
	std::vector <std::string> _levelData;
	void processPlayerMove(Player &player, int targetX, int targetY);

};

