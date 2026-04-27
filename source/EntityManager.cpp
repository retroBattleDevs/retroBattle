#include "headers/EntityManager.h"

#include <algorithm>

EntityManager::EntityManager() {
	this->entities = std::vector<Entity*>();
	this->showBoundingBox = false;
	this->RUNNING = true;
	initializeWalkable();
}

EntityManager::EntityManager(std::vector<Entity*> entities) {
	this->entities = entities;
	this->showBoundingBox = false;
	this->RUNNING = true;
	initializeWalkable();
}

EntityManager::~EntityManager() = default;

EntityManager::EntityManager(const EntityManager& other) {
	this->entities = other.entities;
	this->showBoundingBox = false;
	this->RUNNING = true;
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
	this->RUNNING = true;
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

		if (e->movement) {
			if (canWalkTo(e->getPosition().x, e->getPosition().y)) {
				e->movement->movingPatern(e->position, e->min, e->max, 1, 1);
			}
			else {
				Vec2d invalidPosition = e->getPosition();
				if (invalidPosition.x <= minWidth) {
					e->movement->movingPatern(e->position, e->min, e->max, 1, 0);
				}
				else if (invalidPosition.x >= maxWidth) {
					e->movement->movingPatern(e->position, e->min, e->max, -1, 0);
				}
				else if (invalidPosition.y <= minHeight) {
					e->movement->movingPatern(e->position, e->min, e->max, 0, 1);
				}
				else if (invalidPosition.y >= maxHeight) {
					e->movement->movingPatern(e->position, e->min, e->max, 0, -1);
				}
			}
		}
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

void EntityManager::initializeWalkable() {
	for (int x = 0; x < this->maxWidth; x++) {
		for (int y = 0; y < this->maxHeight; y++) {
			walkableTerrain[x][y] = true;
		}
	}
}

bool EntityManager::canWalkTo(int x, int y) const {
	if (x < this->minWidth || x >= this->maxWidth || y < this->minHeight || y >= maxHeight) return false;
	return walkableTerrain[x][y];
}
