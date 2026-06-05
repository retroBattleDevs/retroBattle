#pragma once

#include <vector>
#include "Entity.h"
#include "headers/terrain/Terrain.h"

class Player : public Entity {
public:
	Player();
	Player(int id, const int width, const int height, Vec2d position, Animator* animation);
	~Player();

	void displayStats();
	void hideStats();
	virtual void drawSelf() const override;
	void roomCheck(Terrain *terrain, Vec2d &pos);

	EntityTypes::Type getType() const override;

	WINDOW *statsWindow;
	int showStats;
	int terrain_room_x, terrain_room_y;
private:
	std::shared_ptr<Animator> animation;
	//int heigth, width = 3;
};