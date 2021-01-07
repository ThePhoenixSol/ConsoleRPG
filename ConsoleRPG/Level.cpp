#include <fstream>
#include <iostream>
#include <cstdio>
#include "Level.h"


Level::Level()
{

}

void Level::load(std::string fileName, Player &player)
{
	std::ifstream file;

	file.open(fileName);
	if (file.fail())
	{
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}

	std::string line;

	while (getline(file, line))
	{
		_levelData.push_back(line);
	}
	
	file.close();

	//Process the level
	char tile;

	for (int i = 0; i < _levelData.size(); i++) //Loops through each row
	{
		for (int j = 0; j < _levelData[i].size(); j++) //Loops through each collumn in that row
		{
			tile = _levelData[i][j];
			switch (tile)
			{
			case '@':
				player.setPos(j, i);
				break;
			}
		}
	}
}

void Level::print()
{
	std::cout << std::string(100, '\n') << std::endl;

	for (int i = 0; i < _levelData.size(); i++)
	{
		printf("%s\n", _levelData[i].c_str());
	}
	printf("\n");
}

void Level::movePlayer(char input, Player &player)
{
	int playerX;
	int playerY;
	player.getPos(playerX, playerY);

	

	switch (input)
	{
	case 'w': //Up
	case 'W':
		processPlayerMove(player, playerX, playerY - 1);
		break;
	case 'a': //Left
	case 'A':
		processPlayerMove(player, playerX -1, playerY);
		break;
	case 's': //Down
	case 'S':
		processPlayerMove(player, playerX, playerY + 1);
		break;
	case 'd': //Right
	case 'D':
		processPlayerMove(player, playerX + 1, playerY);
		break;
	default:
		printf("Invalid Input!");
		system("PAUSE");
		break;
	}
}

char Level::getTile(int x, int y)
{
	return _levelData[y][x];
}

void Level::setTile(int x, int y, char tile)
{
	_levelData[y][x] = tile;
}

void Level::processPlayerMove(Player& player, int targetX, int targetY)
{
	int playerX;
	int playerY;
	player.getPos(playerX, playerY);
	
	char moveTile = getTile(targetX, targetY);
	switch (moveTile)
	{
	case '#':
		printf("You ran into a wall!\n");
		system("PAUSE");
		break;
	case '.':
		player.setPos(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	}
}