#pragma once

#include "Movement.h"
#include "headers/Entity.h"
#include "headers/Player.h"
#include <functional>

class ChaseMovement : public Movement {
public:
	ChaseMovement(Entity* playerTarget);
	virtual ~ChaseMovement();

	virtual void movingPatern(Vec2d& pos, Vec2d& min, Vec2d& max, int moveAmountX, int moveAmountY) override;

private:
	void initializeWalkable();
	Entity* target;

	int maxWidth;
	int maxHeight;
	int minWidth;
	int minHeight;
};