#ifndef TERRAIN_H
#define TERRAIN_H

#include "Room.h"
#include "headers/GateKeeper.h"
#include "headers/textures/AnimatorManager.h"

class Terrain {
	public:
		Terrain(AnimatorManager& animatorManager);
		virtual ~Terrain();

		Room room[3][3];
	protected:

	private:
		AnimatorManager& animatorManager;
};

#endif // TERRAIN_H