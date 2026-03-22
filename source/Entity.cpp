#include "headers/Entity.h"
#include <iostream>

#include "external_libraries/PDCurses/curses.h"

Entity::Entity() {

	position = Vec2d(0, 0);
	min = Vec2d(0, 0);
	max = Vec2d(0, 0);
	id = 0;

	health = 100;
	hitPoints = 100;
	attack = 10;
	defence = 5;
}

// Testing Julian
Entity::Entity(int id, Vec2d min, Vec2d max, Vec2d position) {
	this->id = id;
	this->min = min;
	this->max = max;
	this->position = position;
}

Entity::~Entity() = default;

Entity::Entity(const Entity& other) {
	position = other.position;
	min = other.min;
	max = other.max;
	id = other.id;

	health = other.health;
	hitPoints = other.hitPoints;
	attack = other.attack;
	defence = other.defence;
}
Entity& Entity::operator=(const Entity& other) {
	if (this != &other) {
		position = other.position;
		min = other.min;
		max = other.max;
		id = other.id;

		health = other.health;
		hitPoints = other.hitPoints;
		attack = other.attack;
		defence = other.defence;
	}
	return *this;
}
Entity::Entity(Entity&& other) noexcept {
	position = other.position;
	min = other.min;
	max = other.max;
	id = other.id;

	health = other.health;
	hitPoints = other.hitPoints;
	attack = other.attack;
	defence = other.defence;
}
Entity& Entity::operator=(Entity&& other) noexcept {
	if (this != &other) {
		position = other.position;
		min = other.min;
		max = other.max;
		id = other.id;

		health = other.health;
		hitPoints = other.hitPoints;
		attack = other.attack;
		defence = other.defence;
	}
	return *this;
}

void Entity::drawSelf() const {
	std::cout << "Drawing Entity with ID" << id << std::endl;
}

void Entity::drawTesting() const {
	attron(COLOR_PAIR(1));
	mvprintw(position.y - 2, position.x - 2, "#####");
	mvprintw(position.y - 1, position.x - 2, "#   #");
	mvprintw(position.y, position.x - 2, "#   #");
	mvprintw(position.y + 1, position.x - 2, "#   #");
	mvprintw(position.y + 2, position.x - 2, "#####");
	attroff(COLOR_PAIR(1));
	mvprintw(position.y, position.x, "#");
}

Vec2d Entity::getPosition() const {
	return position;
}

Vec2d Entity::getMin() const {
	return min;
}

Vec2d Entity::getMax() const {
	return max;
}

int Entity::getId() const {
	return id;
}

void Entity::setPosition(Vec2d newPosition) {
	position = newPosition;
}

void Entity::setMin(Vec2d newMin) {
	min = newMin;
}

void Entity::setMax(Vec2d newMax) {
	max = newMax;
}