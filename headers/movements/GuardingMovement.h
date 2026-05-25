#pragma once
#include "Movement.h"

class GuardingMovement : public Movement {
public:
	GuardingMovement(Vec2d positionA, Vec2d positionB);
	~GuardingMovement();

	virtual void movingPatern(Vec2d& pos, Vec2d& min, Vec2d& max, int moveAmountX, int moveAmountY) override;

private:
	Vec2d positionA;
	Vec2d positionB;
	Vec2d desiredPoint;
	int counter;
	bool moveToPosA;
	bool initMovement;

	int maxWidth;
	int maxHeight;
	int minWidth;
	int minHeight;

	void initializeWalkable();
};