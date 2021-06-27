#include "Level.h"

#define CLRSCR system("cls"); // windows
//#define CLRSCR system("clear"); // linux

const int LEVEL_SIZE = 70;
const int MAX_BRIGHTNESS = 246;
const int ZERO_BRIGHTNESS = 232;

const char WALL = char(219);
const char FLOOR = char(176); 
const char PLAYER = char(153);
const char GOLD = 'o';
const char GOLD_CHEST = char(220);

//for now
int gold = 0;
std::string lastNotification;

Level::Level() {

}

void Level::load(std::string fileName) {
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open()) {
		printf("Error loading the file.\n");
		return;
	}
	std::string line;
	while (getline(file, line)) {
		std::vector<char> currTilesLine(LEVEL_SIZE);
		for (int i = 0; i < LEVEL_SIZE; ++i) {
			currTilesLine[i] = line[i];
		}
		_tiles.push_back(currTilesLine);
	}
	_size = _tiles.size();
	file.close();
}

char renderSingleTile(char currTile) {
	switch (currTile) {
	case 'w': return WALL; break;
	case '.': return FLOOR; break;
	case 'g': return GOLD; break;
	case 'c': return GOLD_CHEST; break;
	}
}

void Level::renderTiles() {
	for (int i = 0; i < _size; ++i) {
		for (int j = 0; j < LEVEL_SIZE; ++j) {
			_tiles[i][j] = renderSingleTile(_tiles[i][j]);
		}
	}
}

void Level::updatePlayerPos(int& playerX, int& playerY, const int oldPosX, const int oldPosY) {
	_tiles[oldPosY][oldPosX] = FLOOR; // old position
	char playerPos = _tiles[playerY][playerX]; // new position

	switch (playerPos) {
	case WALL: //s tay on old position
		playerX = oldPosX;
		playerY = oldPosY;
		_tiles[playerY][playerX] = PLAYER;
		lastNotification = "";
		break;
	case FLOOR: // move to new position
		_tiles[playerY][playerX] = PLAYER;
		lastNotification = "";
		break;
	case GOLD:
		_tiles[playerY][playerX] = PLAYER;
		lastNotification = "You found gold coin.";
		gold++;
		break;
	case GOLD_CHEST:
		_tiles[playerY][playerX] = PLAYER;
		lastNotification = "You found gold chest.";
		gold += 100;
		break;
	}
	_playerX = playerX;
	_playerY = playerY;
}

double Level::distFromPlayer(const int tileX, const int tileY, double& maxDist) {
	double dX = (tileX - 0.5 - _playerX) / 2;
	double dY = tileY - _playerY;
	double distance = sqrt((dX * dX) + (dY * dY));
	if (maxDist < distance) {
		maxDist = distance;
	}
	return distance;
}

int pickColor(char currTile, int& brightness) {
	switch (currTile) {
	case WALL: 
	case FLOOR:
		return brightness;
		break;
	case GOLD: return 220; break;
	case GOLD_CHEST: return 130; break;
	}
}

void Level::printLigth(std::map<int, std::pair<int, int>>& ligth) {

	CLRSCR; // clear screen
	printf(" Level: 1   Exp: 0 / 100   Gold: %d   %s\n", gold, lastNotification.c_str());

	int lightSpread = 0;
	bool hitWall = false;
	double maxDist = 0.0;
	int dBrightness = MAX_BRIGHTNESS - ZERO_BRIGHTNESS;

	for (int i = 0; i < _size; ++i) {
		for (int j = 0; j < LEVEL_SIZE; ++j) {
			if (ligth.find(i) != ligth.end()) {
				if (ligth[i].first == j) {
					lightSpread = ligth[i].second;
				} else if (ligth[i].first < 0 && !hitWall) {
					lightSpread = ligth[i].second + ligth[i].first;
					hitWall = true;
				}
			}
			if (lightSpread > 0) {
				double currDistPercent = distFromPlayer(j, i, maxDist) / maxDist;
				int brightness = MAX_BRIGHTNESS - round(dBrightness * currDistPercent);

				printf("\033[38;5;%dm%c\033[m", pickColor(_tiles[i][j], brightness), _tiles[i][j]);
				lightSpread--;
				continue;
			}
			printf("\033[38;5;%dm%c\033[m", 0, _tiles[i][j]); // print darkness
		}
		lightSpread = 0;
		hitWall = false;
		printf("\n");
	}
}

//void Level::print() {
//
//	CLRSCR; // clear screen
//
//	for (int i = 0; i < _size; ++i) {
//		for (int j = 0; j < LEVEL_SIZE; ++j) {
//			printf("%c", _tiles[i][j]);
//		}
//		printf("\n");
//	}
//}



