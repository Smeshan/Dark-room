#pragma once
#include "Level.h"
#include "Player.h"

class GameEngine {
public:
	GameEngine();
	
	void playGame();

private:
	Level _level;
	Player _player;
};

