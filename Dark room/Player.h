#pragma once
#include <string>
#include <map>

class Player {
public:
	Player();

	void setPosition(int x, int y);

	void getPosition(int& x, int& y);

	void createLight(std::map<int, std::pair<int, int>>& ligth);

	void move(const char input);

private:
	int _x = 0;
	int _y = 0;
};

