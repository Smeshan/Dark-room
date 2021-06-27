#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <map>

class Level {
public:
	Level();

	void load(std::string fileName);

	void renderTiles();

	void updatePlayerPos(int& playerX, int& playerY, const int oldPosX, const int oldPosY);


	// print tools
	void printLigth(std::map<int, std::pair<int, int>>& ligth);
	double distFromPlayer(const int tileX, const int tileY, double& maxDist);

	//void print();
	

private:
	size_t _size = 0;
	std::vector <std::vector<char>> _tiles;
	int _playerX = 0;
	int _playerY = 0;
};

