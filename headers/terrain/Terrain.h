#ifndef TERRAIN_H
#define TERRAIN_H

#include "Room.h"
#include "headers/GateKeeper.h"

class Terrain {
	public:
		Terrain();
		virtual ~Terrain();

		Room room[3][3];
	protected:

	private:
};

#endif // TERRAIN_H