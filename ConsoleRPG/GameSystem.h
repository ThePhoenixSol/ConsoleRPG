#pragma once
#include <string>
#include <conio.h>
#include <iostream>
#include "Player.h"
#include "Level.h"

class GameSystem
{
public:
	GameSystem(std::string levelFile);

	void playGame();
	void playerMove();

private:
	Player _player;
	Level _level;
};

