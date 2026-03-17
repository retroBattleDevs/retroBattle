#include "headers/Entity.h"
#include <iostream>

Entity::Entity() {
	position = Vec2d(0, 0);
	min = Vec2d(0, 0);
	max = Vec2d(0, 0);
	id = 0;
}
Entity::~Entity(){
	// delete ? 
}
Entity::Entity(const Entity& other) {
	position = other.position;
	min = other.min;
	max = other.max;
	id = other.id;
}
Entity& Entity::operator=(const Entity& other) {
	if (this != &other) {
		position = other.position;
		min = other.min;
		max = other.max;
		id = other.id;
	}
	return *this;
}
Entity::Entity(Entity&& other) noexcept {
	position = other.position;
	min = other.min;
	max = other.max;
	id = other.id;
}
Entity& Entity::operator=(Entity&& other) noexcept {
	if (this != &other) {
		position = other.position;
		min = other.min;
		max = other.max;
		id = other.id;
	}
	return *this;
}

void Entity::drawSelf() const {
	std::cout << "Drawing Entity by ID" << id << std::endl;
}
