#pragma once

#include <vector>
#include <headers/Entity.h>

class EntityManager {
public:
	EntityManager();
	EntityManager(std::vector<Entity*> entities);

	virtual ~EntityManager();
	EntityManager(const EntityManager& other);
	EntityManager& operator=(const EntityManager& other);
	EntityManager(EntityManager&& other) noexcept;
	EntityManager& operator=(EntityManager&& other) noexcept;

	void add(Entity* entity);
	void removeEntity(Entity* entity);
	void renderAll() const;

	size_t getEntityCount() const;
	int showBoundingBox;

	Entity* getPlayer() const;
	std::vector<Entity*> getEnemies() const;

private:
	std::vector<Entity*> entities;
};