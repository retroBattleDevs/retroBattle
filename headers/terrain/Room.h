#ifndef ROOM_H
#define ROOM_H

#include "headers/MersenneTwister.h"
#include "external_libraries/PDCurses/curses.h"
#include "headers/EntityManager.h"
#include "headers/GateKeeper.h"
#include <vector>
#include "headers/items/Item.h"
#include "headers/items/Relic.h"

class Player;


class Room {
	public:
		Room();
		Room(const int newWidth, const int newHeight);
		virtual ~Room();

		Room(const Room &otherRoom);
		Room &operator = (const Room& otherRoom);
		Room(Room &&otherRoom);
		Room &operator = (Room &&otherRoom);
		GateKeeper *getGatekeeper();

		virtual void drawSelf() const;
		EntityManager *entity_manager;

		int room_init, room_id;
		int width, height, seed_1, seed_2;

		std::vector<Item*> relics;
		void spawnRelics();
		void drawRelics() const;
		void updateRelics(Player* player);


	protected:
		

	private:
};

#endif // ROOM_H