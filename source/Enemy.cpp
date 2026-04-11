#include "headers/Enemy.h"

EntityTypes::Type Enemy::getType() const {
	return EntityTypes::Type::Enemy;
}

Enemy::Enemy() : Entity() {}

Enemy::Enemy(int id, Vec2d min, Vec2d max, Vec2d position) : Entity(id, min, max, position) {}
