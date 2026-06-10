#include "headers/terrain/Room.h"
#include "headers/Vec2D.h"
#include "headers/general_funcs.h"
#include "headers/textures/TextureManager.h"
#include "headers/textures/AnimatorManager.h"


Room::Room() {
	width = 0;
	height = 0;
    entity_manager = nullptr;
    room_init = 1;
    seed_1 = rand() % 100;
    seed_2 = rand() % 1000;
}

Room::Room(const int newWidth, const int newHeight) {
	width = newWidth - 1;
	height = newHeight - 1;
    entity_manager = nullptr;
    room_init = 1;
    seed_1 = rand() % 100;
    seed_2 = rand() % 1000;
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

GateKeeper *Room::getGatekeeper() {
    for (auto entity : entity_manager->entities) {
        if (entity->getType() == EntityTypes::Type::Gatekeeper) {
            return static_cast<GateKeeper*>(entity);
        }
    }
}

void Room::drawSelf() const {
    
    int pos_x = 0, pos_y = 0, half_height = height * 0.5, half_width = width * 0.5;

    attron(COLOR_PAIR(3));
    if (room_id == 0 || room_id == 10 || room_id == 20) {
        for (int i = 1; i < width; i++) {
            mvprintw(0, i, "-");
        }
    } else {
        for (int i = 1; i < width; i++) {
            mvprintw(0, i, "-");
            if (i == half_width - 4) {
                mvprintw(0, i, "|       |");
                mvprintw(1, i - 1, "/_________\\");
                mvprintw(2, i - 1, "|_________|");
                mvprintw(3, i - 2, "/___________\\");
                i += 8;
            }
        }
    }
    attroff(COLOR_PAIR(3));

    std::mt19937 rg(seed_1);
    for (int i = 0; i < 10; i++) {
        std::uniform_int_distribution<int>dist_1(1, width - 11);
        pos_x = dist_1(rg);
        std::uniform_int_distribution<int>dist_2(5, height - 2);
        pos_y = dist_2(rg);

        attron(COLOR_PAIR(10));
        mvprintw(pos_y - 4, pos_x, "  .-\"\"\"-.");
        mvprintw(pos_y - 3, pos_x, " /* * * *\\");
        mvprintw(pos_y - 2, pos_x, ":_.-:`:-._;");
        attroff(COLOR_PAIR(10));
        attron(COLOR_PAIR(7));
        mvprintw(pos_y - 1, pos_x, "    (_)");
        mvprintw(pos_y, pos_x, " \\|/(_)\\|/");
        attroff(COLOR_PAIR(7));
    }

    rg.seed(seed_2);
    for (int i = 0; i < 7; i++) {
        std::uniform_int_distribution<int>dist_3(1, width - 12);
        pos_x = dist_3(rg);
        std::uniform_int_distribution<int>dist_4(9, height - 1);
        pos_y = dist_4(rg);

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
    if (room_id == 10 || room_id == 11 || room_id == 12) {
        for (int i = 1; i < height - 1; i++) {
            mvprintw(i, 0, "|");
            if (i == half_height - 3) {
                mvprintw(i, 0, "--");
                mvprintw(i, width - 1, "--");
                i += 6;
                mvprintw(i, 0, "--");
                mvprintw(i, width - 1, "--");
                continue;
            }
            mvprintw(i, width, "|");
        }
    } else if (room_id == 0 || room_id == 1 || room_id == 2) {
        for (int i = 1; i < height - 1; i++) {
            mvprintw(i, 0, "|");
        }
        for (int i = 1; i < height - 1; i++) {
            if (i == half_height - 3) {
                mvprintw(i, width - 1, "--");
                i += 6;
                mvprintw(i, width - 1, "--");
                continue;
            }
            mvprintw(i, width, "|");
        }
    } else if (room_id == 20 || room_id == 21 || room_id == 22) {
        for (int i = 1; i < height - 1; i++) {
            mvprintw(i, width, "|");
        }
        for (int i = 1; i < height - 1; i++) {
            if (i == half_height - 3) {
                mvprintw(i, 0, "--");
                i += 6;
                mvprintw(i, 0, "--");
                continue;
            }
            mvprintw(i, 0, "|");
        }
    }

    if (room_id == 2 || room_id == 12 || room_id == 22) {
        for (int i = 1; i < width; i++) {
            mvprintw(height - 1, i, "-");
        }
    } else {
        for (int i = 1; i < width; i++) {
            mvprintw(height - 1, i, "-");
            if (i == half_width - 4) {
                mvprintw(height - 4, i - 3, "\\_____________/");
                mvprintw(height - 3, i - 2, "\\___________/");
                mvprintw(height - 2, i - 1, "\\ _______ /");
                mvprintw(height - 1, i, "|       |");
                i += 8;
            }
        }
    }
    attroff(COLOR_PAIR(3));
}

void Room::spawnRelics() {
    TextureManager textureManager;
    AnimatorManager animationManager(textureManager);
    //alte Relics aufräumen,falls vorhanden
    for (Item* r : relics) {
        delete r;       
    }
    relics.clear();

    for (int i = 0; i < 3; i++) {
        RelicType type;
        int r = rand() % 4; 
        if (r == 0) {
            type = RelicType::AttackBoost;
        }
        else if (r == 1) {
            type = RelicType::SpeedBoost;
        }
        else if (r == 2) {
            type = RelicType::HealthBoost;
        }
        else {
            type = RelicType::DefenceBoost;
        }

        Vec2d pos(0, 0); // pos ist eigentlich egal, wird in Item Konstruktor random gesetzt!

        Relic* relic = new Relic(pos, 5, type, animationManager.getAnimator("relic"));
        relics.push_back(relic);
    }
}

void Room::drawRelics() const {
    for (Item* r : relics) {
        if (r) {
            r->drawSelf();
        }
        
    }
}

void Room::updateRelics(Player* player) {
    for (Item*& r : relics) {
        if (r && circleCollisionItem(entity_manager->getPlayer(), r, 5.0f)) {

            Relic* relic = static_cast<Relic*>(r);
            relic->onPickUp(*player);

            delete r;
            r = nullptr;
            break;

        }
    }
}
