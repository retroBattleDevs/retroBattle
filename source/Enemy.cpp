#include "headers/Enemy.h"

Enemy::Enemy() : Entity() {}

Enemy::Enemy(int id, Vec2d min, Vec2d max, Vec2d position) : Entity(id, min, max, position) {
	movement = new RandomMovement();
}

Enemy::~Enemy() {
	delete movement;
}

EntityTypes::Type Enemy::getType() const {
	return EntityTypes::Type::Enemy;
}

void Enemy::drawSelf() const {
	attron(COLOR_PAIR(2));
	mvprintw(position.y - 1, position.x - 2, "\\_O_/");
	mvprintw(position.y,     position.x - 2, "  H   ");
	mvprintw(position.y + 1, position.x - 2, " / \\ ");
	attroff(COLOR_PAIR(2));
}
