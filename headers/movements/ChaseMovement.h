#pragma once

#include "Movement.h"
#include "headers/Entity.h"
#include "headers/Player.h"
#include <functional>

enum MovementState {
	IDLE,
	AGGRESSIVE,
	CONFUSED
};

class ChaseMovement : public Movement {
public:
	/*
		Recommendation for speed and aggressionRadius:
		speed = 3-4 (the higher the slower the enemy)
		aggressionRadius = 15-20 (the higher the bigger the Radius)
	*/
	ChaseMovement(Entity* playerTarget, Entity* self, int speed, int aggressionRadius);
	virtual ~ChaseMovement();

	virtual void movingPatern(Vec2d& pos, Vec2d& min, Vec2d& max, int moveAmountX, int moveAmountY) override;
	void setTextureForState();

private:
	void initializeWalkable();
	Entity* target;
	Entity* self;
	MovementState state;

	int aggressionRadius;
	int speed;
	int speedCounter;
	int simpleMovementCounter;

	int maxWidth;
	int maxHeight;
	int minWidth;
	int minHeight;
};