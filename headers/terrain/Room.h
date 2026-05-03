#ifndef ROOM_H
#define ROOM_H

#include "external_libraries/PDCurses/curses.h"

class Room {
	public:
		Room();
		Room(const int newWidth, const int newHeight);
		virtual ~Room();

		Room(const Room &otherRoom);
		Room &operator = (const Room& otherRoom);
		Room(Room &&otherRoom);
		Room &operator = (Room &&otherRoom);

		virtual void drawSelf() const;
	protected:

		int width, height;
	private:
};

#endif // ROOM_H