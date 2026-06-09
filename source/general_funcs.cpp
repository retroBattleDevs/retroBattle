#include "headers/general_funcs.h"

#include <cmath>
#include <vector>
#include <Windows.h>

int displayDialog() {
	mvprintw(20, 60, "Are you sure you want to quit? [y/N]");
	refresh();
	char input = getchar();
	if (input == 'y' || input == 'Y') {
		return 1;
	}
	return 0;
}

Vec2d ceilVec2d(Vec2d vec2) {
	return Vec2d(ceilf(vec2.x), ceilf(vec2.y));
}

Vec2d floorVec2d(Vec2d vec2) {
	return Vec2d(floorf(vec2.x), floorf(vec2.y));
}

float calculateWidthHeight(float max, float min) {
	return max - min;
}

// Euclidean Distance
float calculateAbsoluteDistance(float point1, float point2) {
	float distance = point1 - point2;
	return sqrtf(distance * distance);
}

/*
This function should be used
*/
std::vector<Entity*> collisionDetectionBoundinBox(Entity* player, std::vector<Entity*> enemies) {
	Vec2d playerMin = player->getMin();
	Vec2d playerMax = player->getMax();
	Vec2d playerCurrentPosition = player->getPosition();
	std::vector<Entity*> collidingEnemies;

	for (auto& enemy : enemies) {
		Vec2d enemyMin = enemy->getMin();
		Vec2d enemyMax = enemy->getMax();
		Vec2d enemyCurrentPosition = enemy->getPosition();

		// calculate distance between centers
		// calculate distance between centers
		float distanceX = calculateAbsoluteDistance(playerCurrentPosition.x, enemyCurrentPosition.x);
		float distanceY = calculateAbsoluteDistance(playerCurrentPosition.y, enemyCurrentPosition.y);

		// calculate combined half width and height
		float combinedHalfWidth = (calculateWidthHeight(playerMax.x, playerMin.x) + calculateWidthHeight(enemyMax.x, enemyMin.x)) / 2;
		float combinedHalfHeigth = (calculateWidthHeight(playerMax.y, playerMin.y) + calculateWidthHeight(enemyMax.y, enemyMin.y)) / 2;

		if ((distanceX < combinedHalfWidth) && (distanceY < combinedHalfHeigth)) {
			collidingEnemies.push_back(enemy);
		}
	}
	return collidingEnemies;
}


// Radius is currently biggest part of hitbox, the half height
/*
 If the Absolute Distance is less than the combined radii -> Collision
*/
float getRadius(Entity *entity) {
	Vec2d vec2dMin = entity->getMin();
	Vec2d vec2dMax = entity->getMax();

	return (calculateWidthHeight(vec2dMax.y, vec2dMin.y) / 2);
}

std::vector<Entity*> circleCollisionDetection(Entity* player, std::vector<Entity*> enemies) {
	Vec2d playerCurrentPosition = player->getPosition();
	float playerRadius = getRadius(player);
	std::vector<Entity*> collidingEnemies;

	for (auto& enemy : enemies) {
		Vec2d enemyCurrentPosition = enemy->getPosition();

		float absoluteDistanceX = calculateAbsoluteDistance(playerCurrentPosition.x, enemyCurrentPosition.x);
		float absoluteDistanceY = calculateAbsoluteDistance(playerCurrentPosition.y, enemyCurrentPosition.y);
		float combinedRadii = playerRadius + getRadius(enemy);

		if ((absoluteDistanceX < combinedRadii) && (absoluteDistanceY < combinedRadii)) {
			collidingEnemies.push_back(enemy);
		}
	}
	return collidingEnemies;
}

std::vector<Entity*> circleCollisionDetectionAggressionRadius(Entity* player, std::vector<Entity*> enemies, int radius) {
	Vec2d playerCurrentPosition = player->getPosition();
	float playerRadius = getRadius(player);
	std::vector<Entity*> angryEnemies;

	for (auto& enemy : enemies) {
		Vec2d enemyCurrentPosition = enemy->getPosition();

		float absoluteDistanceX = calculateAbsoluteDistance(playerCurrentPosition.x, enemyCurrentPosition.x);
		float absoluteDistanceY = calculateAbsoluteDistance(playerCurrentPosition.y, enemyCurrentPosition.y);

		if ((absoluteDistanceX < radius) && (absoluteDistanceY < radius)) {
			angryEnemies.push_back(enemy);
		}
	}
	return angryEnemies;
}

bool inAggressionRadius(Entity* player, Entity* enemy, int radius) {
	Vec2d playerCurrentPosition = player->getPosition();
	float playerRadius = getRadius(player);

	Vec2d enemyCurrentPosition = enemy->getPosition();

	float absoluteDistanceX = calculateAbsoluteDistance(playerCurrentPosition.x, enemyCurrentPosition.x);
	float absoluteDistanceY = calculateAbsoluteDistance(playerCurrentPosition.y, enemyCurrentPosition.y);

	if ((absoluteDistanceX < radius) && (absoluteDistanceY < radius)) {
		return true;
	}

	return false;
}

std::vector<Entity*> getEnemiesInRadius(Entity* player, std::vector<Entity*> enemies, int radius) {
	Vec2d playerCurrentPosition = player->getPosition();
	float playerRadius = getRadius(player);
	std::vector<Entity*> collidingEnemies;

	for (auto& enemy : enemies) {
		Vec2d enemyCurrentPosition = enemy->getPosition();

		float absoluteDistanceX = calculateAbsoluteDistance(playerCurrentPosition.x, enemyCurrentPosition.x);
		float absoluteDistanceY = calculateAbsoluteDistance(playerCurrentPosition.y, enemyCurrentPosition.y);

		if ((absoluteDistanceX < radius) && (absoluteDistanceY < radius)) {
			collidingEnemies.push_back(enemy);
		}
	}
	return collidingEnemies;
}

bool circleCollisionItem(Entity* player, Item* item, float radius) {
	if (item == nullptr || player == nullptr) return false;

	float dx = player->getPosition().x - item->getPosition().x;
	float dy = player->getPosition().y - item->getPosition().y;

	float distance = sqrt(dx * dx + dy * dy);

	return distance < radius;
}

void restartGameAnimation(int row, int col) {
	col -= 6;

	refresh();
    mvprintw(row - 3, col, " :::::::: "); 
    mvprintw(row - 2, col, ":+:    :+:"); 
    mvprintw(row - 1, col, "       +:+"); 
    mvprintw(row, col,     "    +#++: "); 
    mvprintw(row + 1, col, "       +#+"); 
    mvprintw(row + 2, col, "#+#    #+#"); 
    mvprintw(row + 3, col, " ######## ");

	refresh();
	Sleep(1000);
    mvprintw(row - 3, col, " :::::::: ");
    mvprintw(row - 2, col, ":+:    :+:");
    mvprintw(row - 1, col, "      +:+ ");
    mvprintw(row, col,     "    +#+   ");
    mvprintw(row + 1, col, "  +#+     ");
    mvprintw(row + 2, col, " #+#      ");
    mvprintw(row + 3, col, "##########");

	refresh();
	Sleep(1000);
	mvprintw(row - 3, col, "    :::  ");
	mvprintw(row - 2, col, "  :+:+:  ");
	mvprintw(row - 1, col, "    +:+  ");
	mvprintw(row, col,     "    +#+  ");
	mvprintw(row + 1, col, "    +#+  ");
	mvprintw(row + 2, col, "    #+#  ");
	mvprintw(row + 3, col, "  #######");

	refresh();
	Sleep(1000);
	mvprintw(row - 3, col, "  ::::::: ");
	mvprintw(row - 2, col, " :+:   :+:");
	mvprintw(row - 1, col, " +:+  :+:+");
	mvprintw(row, col,     " +#+ + +:+");
	mvprintw(row + 1, col, " +#+#  +#+");
	mvprintw(row + 2, col, " #+#   #+#");
	mvprintw(row + 3, col, "  ####### ");
}


/*
bool collisionDetectionCircles(Entity *e1, Entity *e2) {
	float combinedRadii = getRadius(e1) + getRadius(e2);
	
	// Get current position and absolute distance between these points
	Vec2d e1CurrentPos = e1->getPosition();
	Vec2d e2CurrentPos = e2->getPosition();

	float absoluteDistanceX = calculateAbsoluteDistance(e1CurrentPos.x, e2CurrentPos.x);
	float absoluteDistanceY = calculateAbsoluteDistance(e1CurrentPos.y, e2CurrentPos.y);

	if ((absoluteDistanceX < combinedRadii) && (absoluteDistanceY < combinedRadii)) {
		return true;
	}

	return false;
}
bool collisionDetectionBoundinBox(Entity *e1, Entity *e2) {
	Vec2d e1Min = e1->getMin();
	Vec2d e1Max = e1->getMax();
	Vec2d e1CurrPos = e1->getPosition();

	Vec2d e2Min = e2->getMin();
	Vec2d e2Max = e2->getMax();

	Vec2d e2CurrPos = e2->getPosition();

	// calculate distance between centers
	float distanceX = calculateAbsoluteDistance(e1CurrPos.x, e2CurrPos.x);
	float distanceY = calculateAbsoluteDistance(e1CurrPos.y, e2CurrPos.y);

	// calculate combined half width and height
	float combinedHalfWidth = (calculateWidthHeight(e1Max.x, e1Min.x) + calculateWidthHeight(e2Max.x, e2Min.x)) / 2;
	float combinedHalfHeigth = (calculateWidthHeight(e1Max.y, e1Min.y) + calculateWidthHeight(e2Max.y, e2Min.y)) / 2;

	if ((distanceX < combinedHalfWidth) && (distanceY < combinedHalfHeigth)) {
		return true;
	}
	return false;
}

bool collisionDetectionBoundinBoxArray(Entity *e1, Entity *e2) {
	Vec2d e1Min = e1->getMin();
	Vec2d e1Max = e1->getMax();
	Vec2d e1CurrPos = e1->getPosition();

	while (e2 != nullptr) { // laeuft weiter mit garbage pointer

		Vec2d e2Min = e2->getMin();
		Vec2d e2Max = e2->getMax();
		if (e2Min.x < 0) { return false; }


		Vec2d e2CurrPos = e2->getPosition();

		// calculate distance between centers
		float distanceX = calculateAbsoluteDistance(e1CurrPos.x, e2CurrPos.x);
		float distanceY = calculateAbsoluteDistance(e1CurrPos.y, e2CurrPos.y);

		// calculate combined half width and height
		float combinedHalfWidth = (calculateWidthHeight(e1Max.x, e1Min.x) + calculateWidthHeight(e2Max.x, e2Min.x)) / 2;
		float combinedHalfHeigth = (calculateWidthHeight(e1Max.y, e1Min.y) + calculateWidthHeight(e2Max.y, e2Min.y)) / 2;

		if ((distanceX < combinedHalfWidth) && (distanceY < combinedHalfHeigth)) {
			return true;
		}
		e2++;
	}
	return false;
}
*/