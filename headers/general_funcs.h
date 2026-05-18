#ifndef GENERAL_FUNCS
#define GENERAL_FUNCS

// TODO: Verweisen Sie hier auf zusätzliche Header, die Ihr Programm erfordert.
#include <iostream>
#include <vector>
#include "headers/Entity.h"

int displayDialog();
Vec2d ceilVec2d(Vec2d vec2);
Vec2d floorVec2d(Vec2d vec2);
float calculateWidthHeight(float max, float min);
float calculateAbsoluteDistance(float point1, float point2);
std::vector<Entity*> collisionDetectionBoundinBox(Entity* player, std::vector<Entity*> enemies);
std::vector<Entity*> circleCollisionDetection(Entity* player, std::vector<Entity*> enemies);
float getRadius(Entity *entity);
std::vector<Entity*> circleCollisionDetectionAggressionRadius(Entity* player, std::vector<Entity*> enemies, int radius);
std::vector<Entity*> getEnemiesInRadius(Entity* player, std::vector<Entity*> enemies, int radius);

bool inAggressionRadius(Entity* player, Entity* enemy, int radius);

#endif // !GENERAL_FUNCS
