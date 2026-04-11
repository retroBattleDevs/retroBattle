#ifndef GENERAL_FUNCS
#define GENERAL_FUNCS

// TODO: Verweisen Sie hier auf zusätzliche Header, die Ihr Programm erfordert.
#include <iostream>
#include <vector>
#include "headers/Entity.h"

float calculateWidthHeight(float max, float min);
float calculateAbsoluteDistance(float point1, float point2);
bool collisionDetectionBoundinBox(Entity* player, std::vector<Entity*> enemies);
bool circleCollisionDetection(Entity* player, std::vector<Entity*> enemies);
float getRadius(Entity *entity);

#endif // !GENERAL_FUNCS
