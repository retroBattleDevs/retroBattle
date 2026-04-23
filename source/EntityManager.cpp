#include "headers/EntityManager.h"

#include <algorithm>

EntityManager::EntityManager() {
	this->entities = std::vector<Entity*>();
	this->showBoundingBox = false;
}

EntityManager::EntityManager(std::vector<Entity*> entities) {
	this->entities = entities;
	this->showBoundingBox = false;
}

EntityManager::~EntityManager() = default;

EntityManager::EntityManager(const EntityManager& other) {
	this->entities = other.entities;
	this->showBoundingBox = false;
}

EntityManager& EntityManager::operator=(const EntityManager& other) {
	if (this != &other) {
		this->entities = other.entities;
	}
	return *this;
}

EntityManager::EntityManager(EntityManager&& other) noexcept {
	this->entities = other.entities;
	this->showBoundingBox = false;
}

EntityManager& EntityManager::operator=(EntityManager&& other) noexcept {
	if (this != &other) {
		this->entities = other.entities;
	}
	return *this;
}

void EntityManager::add(Entity* entity) {
	if (entity != nullptr) {
		this->entities.push_back(entity);
	}
}

void EntityManager::removeEntity(Entity* entity) {
	auto it = std::find(entities.begin(), entities.end(), entity);
	if (it != entities.end()) {
		delete* it;
		entities.erase(it);
	}
}

void EntityManager::renderAll() const {
	for (Entity* e : entities) {
		if (showBoundingBox)
		    e->drawBoundingBox();
		else
			e->drawSelf();

		if (e->movement)
		    e->movement->movingPatern(e->position, e->min, e->max, 1, 1);
	}
}

Entity* EntityManager::getPlayer() const {
	for (auto& e : entities) {
		if (e->getType() == EntityTypes::Type::Player) {
			return e;
		}
	}
}

std::vector<Entity*> EntityManager::getEnemies() const {
	std::vector<Entity*> enemies;
	for (auto& enemy : entities) {
		if (enemy->getType() == EntityTypes::Type::Enemy) {
			enemies.push_back(enemy);
		}
	}
	return enemies;
}


size_t EntityManager::getEntityCount() const {
	return entities.size();
}