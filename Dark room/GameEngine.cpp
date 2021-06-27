#include "GameEngine.h"
#include "conio.h"

GameEngine::GameEngine() {
	_level.load("level1.txt");
	_level.renderTiles();
}

void GameEngine::playGame() {

	bool gameOver = false;

	char input;
	int playerX = 1;
	int playerY = 1;
	int oldPosX = playerX;
	int oldPosY = playerY;
	std::map<int, std::pair<int, int>> playerLigth;

	while (!gameOver) {
		_player.getPosition(playerX, playerY);
		_level.updatePlayerPos(playerX, playerY, oldPosX, oldPosY);
		_player.setPosition(playerX, playerY);

		_player.createLight(playerLigth);
		_level.printLigth(playerLigth);

		//printf("Enter a move command (w/s/a/d): ");

		input = _getch();
		oldPosX = playerX;
		oldPosY = playerY;
		_player.move(input);
	}	
}
