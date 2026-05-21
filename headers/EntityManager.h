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
	void removePlayer();
	void renderAll() const;

	size_t getEntityCount() const;
	int showBoundingBox, RUNNING;

	Entity* getPlayer() const;
	std::vector<Entity*> getEnemies() const;

	bool canWalkTo(Entity* e, Vec2d newPosition) const;
	void initializeWalkable();

private:
	std::vector<Entity*> entities;

	int maxWidth;
	int maxHeight;
	int minWidth;
	int minHeight;
};