#pragma once

#include "headers/Entity.h"

class Enemy : public Entity {
public:
	Enemy();
	Enemy(int id, const int width, const int height, Vec2d position, Movement* movement);
	~Enemy();

	virtual void drawSelf() const override;

	EntityTypes::Type getType() const override;
};