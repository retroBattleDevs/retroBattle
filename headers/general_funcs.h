#ifndef GENERAL_FUNCS
#define GENERAL_FUNCS

// TODO: Verweisen Sie hier auf zusätzliche Header, die Ihr Programm erfordert.
#include "headers/Entity.h"

float calculateWidthHeight(float max, float min);
float calculateAbsoluteDistance(float point1, float point2);
bool collisionDetectionBoundinBox(Entity *e1, Entity *e2);
bool collisionDetectionBoundinBoxArray(Entity *e1, Entity *e2);
float getRadius(Entity *entity);
bool collisionDetectionCircles(Entity *e1, Entity *e2);

#endif // !GENERAL_FUNCS
