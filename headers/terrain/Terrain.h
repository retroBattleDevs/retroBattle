#ifndef TERRAIN_H
#define TERRAIN_H

#include "headers/terrain/Room.h"
#include "headers/GateKeeper.h"
#include "headers/textures/AnimatorManager.h"

class Terrain {
	public:
		Terrain(AnimatorManager& animatorManager);
		virtual ~Terrain();

		Room room[3][3];

		GateKeeper* gateKeeper;
		int gatekeeperRoomX;
		int gatekeeperRoomY;

		void positionGatekeeper();
		void removeGatekeeper();
	protected:

	private:
		AnimatorManager& animatorManager;
};

#endif // TERRAIN_H