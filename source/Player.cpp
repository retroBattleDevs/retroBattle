#include "headers/Player.h"

Player::Player() : Entity() {
	showStats = 0;
	statsWindow = nullptr;
}

Player::Player(int id, const int width, const int height, Vec2d position) : Entity(id, width, height, position) {
	showStats = 0;
	statsWindow = nullptr;
}

Player::~Player() {
	delwin(statsWindow);
	statsWindow = nullptr;
}

void Player::drawSelf() const {
	attron(COLOR_PAIR(1));
	mvprintw(position.y - 1, position.x - 1,  "\\O7");
	mvprintw(position.y,     position.x,        "H");
	mvprintw(position.y + 1, position.x - 1,  "/");
	mvprintw(position.y + 1, position.x + 1,    "L");
	attroff(COLOR_PAIR(1));
}

void Player::displayStats() {
	if (showStats) {
		if (statsWindow == nullptr) {
			statsWindow = subwin(stdscr, 4, 45, 1, 110);
		}
		wclear(statsWindow);
		box(statsWindow, 0, 0);
		mvwprintw(statsWindow, 1, 1, "x: %f    y: %f", getPosition().x, getPosition().y);
		mvwprintw(statsWindow, 2, 1, "Direction X: %.2f    Direction Y: %.2f", getDirection().x, getDirection().y);
	}
}

void Player::hideStats() {
	showStats = 0;
	delwin(statsWindow);
	statsWindow = nullptr;
}

EntityTypes::Type Player::getType() const {
	return EntityTypes::Type::Player;
}

/*
void Player::drawSelf(std::vector<std::vector<char*>> texture) {
	for (int y = 0; y < getHeigth(); y++) {
		for (int x = 0; x < getWidth(); x++) {
			std::cout << texture[x][y];
		}
		std::cout << std::endl;
	}
}
int Player::getHeigth() const {
	return this->heigth;
}

int Player::getWidth() const {
	return this->width;
}
*/