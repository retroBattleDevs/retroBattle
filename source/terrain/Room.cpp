#include "headers/terrain/Room.h"

Room::Room() {
	width = 0;
	height = 0;
    entity_manager = nullptr;
    room_init = 0;
}

Room::Room(const int newWidth, const int newHeight) {
	width = newWidth - 1;
	height = newHeight - 1;
    entity_manager = nullptr;
    room_init = 1;
}

Room::~Room() {
    if (entity_manager != nullptr)
        delete entity_manager;
}

Room::Room(const Room &otherRoom) {
    width = otherRoom.width;
    height = otherRoom.height;
    entity_manager = otherRoom.entity_manager;
    room_init = otherRoom.room_init;
}

Room &Room::operator = (const Room &otherRoom) {
    if (this != &otherRoom) {
        width = otherRoom.width;
        height = otherRoom.height;
        entity_manager = otherRoom.entity_manager;
        room_init = otherRoom.room_init;
    }
    return *this;
}

Room::Room(Room &&otherRoom) {
    width = otherRoom.width;
    height = otherRoom.height;
    entity_manager = otherRoom.entity_manager;
    room_init = otherRoom.room_init;

    otherRoom.width = 0;
    otherRoom.height = 0;
    otherRoom.entity_manager = nullptr;
    otherRoom.room_init = 0;
}

Room &Room::operator = (Room &&otherRoom) {
    if (this != &otherRoom) {
        width = otherRoom.width;
        height = otherRoom.height;
        entity_manager = otherRoom.entity_manager;
        room_init = otherRoom.room_init;

        otherRoom.width = 0;
        otherRoom.height = 0;
        otherRoom.entity_manager = nullptr;
        otherRoom.room_init = 0;
    }
    return *this;
}

void Room::drawSelf() const {
    
    int pos_x = 0, pos_y = 0;
	attron(COLOR_PAIR(3));
	mvprintw(0, 0, " ------------------------------------------------------------------------|       |-------------------------------------------------------------------------");
    mvprintw(1, 0, "                                                                        /_________\\");
    mvprintw(2, 0, "                                                                        |_________|");
    mvprintw(3, 0, "                                                                       /___________\\");
    attroff(COLOR_PAIR(3));

    std::srand(100);
    for (int i = 0; i < 10; i++) {
        pos_x = std::rand() % 150 + 1;
        pos_y = std::rand() % 39 + 5;
        attron(COLOR_PAIR(8));
        mvprintw(pos_y - 4, pos_x, "  .-\"\"\"-.");
        mvprintw(pos_y - 3, pos_x, " /* * * *\\");
        mvprintw(pos_y - 2, pos_x, ":_.-:`:-._;");
        attroff(COLOR_PAIR(8));
        attron(COLOR_PAIR(7));
        mvprintw(pos_y - 1, pos_x, "    (_)");
        mvprintw(pos_y, pos_x, " \\|/(_)\\|/");
        attroff(COLOR_PAIR(7));
    }

    std::srand(1000);
    for (int i = 0; i < 7; i++) {
        pos_x = std::rand() % 145 + 1;
        pos_y = std::rand() % 39 + 8;
        attron(COLOR_PAIR(8));
        mvprintw(pos_y - 8, pos_x + 4, ",*-.");
        mvprintw(pos_y - 7, pos_x + 4, "|  |");
        mvprintw(pos_y - 6, pos_x, ",.  |  |");
        mvprintw(pos_y - 5, pos_x, "| |_|  | ,.");
        mvprintw(pos_y - 4, pos_x, "`---.  |_| |");
        mvprintw(pos_y - 3, pos_x + 4, "|  .--`");
        mvprintw(pos_y - 2, pos_x + 4, "|  |");
        mvprintw(pos_y - 1, pos_x + 4, "|  |");
        attroff(COLOR_PAIR(8));
    }

    attron(COLOR_PAIR(3));
	for (int i = 1; i < height; i++) {
		mvprintw(i, 0, "|");
        if (i == 17) {
            mvprintw(i, 0, "--");
            mvprintw(i, width - 1, "--");
            i += 6;
            mvprintw(i, 0, "--");
            mvprintw(i, width - 1, "--");
            continue;
        }
		mvprintw(i, width, "|");
	}

    mvprintw(height - 3, 70, "\\_____________/");
    mvprintw(height - 2, 71, "\\___________/");
    mvprintw(height - 1, 72, "\\ _______ /");
	mvprintw(height, 0, " ------------------------------------------------------------------------|       |-------------------------------------------------------------------------");
	attroff(COLOR_PAIR(3));
}