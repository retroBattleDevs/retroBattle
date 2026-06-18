#include "headers/Player.h"
#include "headers/terrain/Terrain.h"

Player::Player() : Entity() {
	showStats = 0;
	statsWindow = nullptr;
	terrain_room_x = 1;
	terrain_room_y = 1;
	relicCount = 0;
}

Player::Player(int id, const int width, const int height, Vec2d position, Animator* animation) 
	: Entity(id, width, height, position), animation(animation) {
	showStats = 0;
	statsWindow = nullptr;
	terrain_room_x = 1;
	terrain_room_y = 1;
	relicCount = 0;
}

Player::~Player() {
	delwin(statsWindow);
	statsWindow = nullptr;
}

void Player::drawSelf() const {
	attron(COLOR_PAIR(1));
	if (animation != nullptr) {
		animation->drawDirection(this->position,this->direction);
	}
	else {
		mvprintw(position.y - 1, position.x - 1,  "\\O7");
		mvprintw(position.y,     position.x,        "H");
		mvprintw(position.y + 1, position.x - 1,  "/");
		mvprintw(position.y + 1, position.x + 1,    "L");
	}
	attroff(COLOR_PAIR(1));
}

void Player::displayStats(const int x, const int y) {
	if (showStats) {
		if (statsWindow == nullptr) {
			statsWindow = subwin(stdscr, 5, 45, x, y);
		}
		wclear(statsWindow);
		box(statsWindow, 0, 0);
		mvwprintw(statsWindow, 1, 1, "x: %f    y: %f", getPosition().x, getPosition().y);
		mvwprintw(statsWindow, 2, 1, "Direction X: %.2f    Direction Y: %.2f", getDirection().x, getDirection().y);

		mvwprintw(statsWindow, 3, 1, "Relics: %d", relicCount);
	}
}

void Player::hideStats() {
	showStats = 0;
	delwin(statsWindow);
	statsWindow = nullptr;
}

void Player::roomCheck(Terrain *terrain, Vec2d &pos) {
	int width = terrain->room[terrain_room_x][terrain_room_y].width;
	int height = terrain->room[terrain_room_x][terrain_room_y].height;

	if ((pos.x >= (width * 0.5) - 4 && pos.x <= (width * 0.5) + 4) && pos.y == 1) {
		if (terrain_room_y > 0) {

			terrain->room[terrain_room_x][terrain_room_y].entity_manager->removePlayer();

			terrain_room_y -= 1;
			pos.y = height - 3;
			terrain->room[terrain_room_x][terrain_room_y].entity_manager->add(this);
		}
	}
	if ((pos.x >= (width * 0.5) - 4 && pos.x <= (width * 0.5) + 4) && (pos.y == height - 2)) {
		if (terrain_room_y < 2) {

			terrain->room[terrain_room_x][terrain_room_y].entity_manager->removePlayer();

			terrain_room_y += 1;
			pos.y = 2;
			terrain->room[terrain_room_x][terrain_room_y].entity_manager->add(this);
		}
	}
	if (pos.x == 1 && (pos.y >= (height * 0.5) - 1 && pos.y <= (height * 0.5) + 1)) {
		if (terrain_room_x > 0) {

			terrain->room[terrain_room_x][terrain_room_y].entity_manager->removePlayer();

			terrain_room_x -= 1;
			pos.x = width - 2;
			terrain->room[terrain_room_x][terrain_room_y].entity_manager->add(this);
		}
	}
	if (pos.x == width - 1 && (pos.y >= (height * 0.5) - 1 && pos.y <= (height * 0.5) + 1)) {
		if (terrain_room_x < 2) {

			terrain->room[terrain_room_x][terrain_room_y].entity_manager->removePlayer();

			terrain_room_x += 1;
			pos.x = 2;
			terrain->room[terrain_room_x][terrain_room_y].entity_manager->add(this);
		}
	}
}

EntityTypes::Type Player::getType() const {
	return EntityTypes::Type::Player;
}

void Player::addRelic() {
	relicCount++;
}

int Player::getRelicCount() const {
	return relicCount;
}
