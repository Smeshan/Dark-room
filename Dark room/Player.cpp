#include "Player.h"

const int LIGTH_POW = 5;

Player::Player() {
	_x = 2;
	_y = 2;
}

void Player::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void Player::getPosition(int& x, int& y) {
	x = _x;
	y = _y;
}

void Player::move(const char input) {
	switch (input) {
	case 'w': _y -= 1; printf("You pressed 'W'.\n"); break;//up
	case 's': _y += 1; printf("You pressed 'S'.\n"); break;// down
	case 'a': _x -= 1; printf("You pressed 'A'.\n"); break; //left	
	case 'd': _x += 1; printf("You pressed 'D'.\n"); break;// right
	default: printf("Invalid input!\n"); break;
	}
}

void Player::createLight(std::map<int, std::pair<int, int>>& ligth) {
	std::map<int, std::pair<int, int>> _ligth;
	std::pair<int, int> currLigthPos;
	const int step = 2;
	int power = LIGTH_POW - 1;
	int spread = power - LIGTH_POW;
	for (int i = - LIGTH_POW; i <= LIGTH_POW; ++i) {
		if (i < 0) {
			power += step * 2;
			spread -= step;
		}
		else if (i > 1) {
			power -= step * 2;
			spread += step;
		}
		currLigthPos.first = _x + spread; // col
		currLigthPos.second = power; // pow
		_ligth[_y + i] = currLigthPos; // row
	}
	ligth = _ligth;
}
