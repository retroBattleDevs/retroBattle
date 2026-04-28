#pragma once

#include <vector>
#include "Entity.h"

class Player : public Entity {
public:
	Player();
	Player(int id, const int width, const int height, Vec2d position);
	~Player();

	void displayStats();
	void hideStats();
	virtual void drawSelf() const override;

	EntityTypes::Type getType() const override;
	/*
	two options determining heigth and width of character:
	- 1: Vec2d Min, Max values, width = Max.x - Min.x, heigth = Max.y - Min.y
	- 2: heigth, width member variables (Chose this options: to keep possibility to increase/decrease Min/Max-Values without changing player appearance)
	void drawSelf(std::vector<std::vector<char*>> texture);
	int getHeigth() const;
	int getWidth() const;
	*/

	WINDOW *statsWindow;
	int showStats;
private:
	//int heigth, width = 3;
};