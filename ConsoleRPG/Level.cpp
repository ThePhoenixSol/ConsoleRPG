#include <fstream>
#include <iostream>
#include <cstdio>
#include <conio.h>
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
			case '@': //Player
				player.setPos(j, i);
				break;
			case 'M': //Monster
				_enemies.push_back(Enemy("Monster", tile, 1, 20, 1, 1, 10));
				_enemies.back().setPos(j, i);
				break;
			case 'm': //Monster
				_enemies.push_back(Enemy("monster", tile, 1, 10, 10, 10, 10));
				_enemies.back().setPos(j, i);
				break;
			}
		}
	}
}

void Level::print()
{
	system("cls");
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

void Level::updateEnemies(Player& player)
{
	char aimove;
	int playerX;
	int playerY;
	player.getPos(playerX, playerY);

	int enemyX;
	int enemyY;

	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i].getPos(enemyX, enemyY);
		aimove = _enemies[i].getMove(playerX, playerY);

		switch (aimove)
		{
		case 'w': //Up
			processEnemyMove(player, i, enemyX, enemyY - 1);
			break;
		case 'a': //Left
			processEnemyMove(player, i, enemyX - 1, enemyY);
			break;
		case 's': //Down
			processEnemyMove(player, i, enemyX, enemyY + 1);
			break;
		case 'd': //Right
			processEnemyMove(player, i, enemyX + 1, enemyY);
			break;
		}
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
	case '.': //Open Space
		player.setPos(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case '#': //Wall
		break;
	case 'P': //Person
		break;
	case 'D': //Door
		break;
	case 'C': //Chest
		break;
	case '^': //Move map up
		break;
	case 'v': //Move map down
		break;
	case '<': //Move map left
		break;
	case '>': //Move map right
		break;
	default:
		battleMonster(player, targetX, targetY);
		break;
	}
}

void Level::processEnemyMove(Player& player, int enemyIndex, int targetX, int targetY)
{
	int playerX;
	int playerY;
	player.getPos(playerX, playerY);

	int enemyX;
	int enemyY;
	_enemies[enemyIndex].getPos(enemyX, enemyY);

	char moveTile = getTile(targetX, targetY);
	switch (moveTile)
	{
	case '.': //Open Space
		_enemies[enemyIndex].setPos(targetX, targetY);
		setTile(enemyX, enemyY, '.');
		setTile(targetX, targetY, _enemies[enemyIndex].getTile());
		break;
	case '@': //player
		battleMonster(player, enemyX, enemyY);
		break;
	default:
		break;
	}
}

void Level::battleMonster(Player& player, int targetX, int targetY)
{
	int enemyX;
	int enemyY;
	int playerX;
	int playerY;
	int attackRoll;
	int attackResult;
	std::string enemyName;

	player.getPos(playerX, playerY);

	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i].getPos(enemyX, enemyY);
		enemyName == _enemies[i].getName();
		if (targetX == enemyX && targetY == enemyY)
		{
			//Battle!

			//Player turn
			attackRoll = player.attack();
			printf("\n%s attacked the %s with a chance of %d \n", player.getName().c_str(), enemyName.c_str(), attackRoll);
			attackResult = _enemies[i].takeDamage(attackRoll);
			printf("\n%s attacked the %s with a damage of %d \n", player.getName().c_str(), enemyName.c_str(), attackResult);
			system("PAUSE");
			if (attackResult != 0)
			{
				setTile(targetX, targetY, '.');
				print();
				printf("\nPlayer killed the monster!\n");
				//removes the enemies
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;
				system("PAUSE");
				player.addExperience(attackResult);

				return;
			}
			//Monster Turn
			attackRoll = _enemies[i].attack();
			printf("\n%s attacked the %s with a chance of %d \n", enemyName.c_str(), player.getName().c_str(), attackRoll);
			attackResult = player.takeDamage(attackRoll);
			printf("\n%s attacked the %s with a damage of %d \n", enemyName.c_str(), player.getName().c_str(), attackResult);
			system("PAUSE");
			if (attackResult != 0)
			{
				setTile(playerX, playerY, 'x');
				print();
				printf("\nThe Monster killed the Player!\n");
				exit(0);
			}

			return;
		}

	}
}