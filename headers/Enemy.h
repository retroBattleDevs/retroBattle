#pragma once

#include "Entity.h"

class Enemy : public Entity {
public:
	Enemy();
	Enemy(int id, Vec2d min, Vec2d max, Vec2d position);

	EntityTypes::Type getType() const override;
};