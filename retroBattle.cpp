#include "retroBattle.h"

int RUNNING = 1;

void keyDispatcher(metrics& mtr, const char c, Terrain *terrain, EntityManager *mgr) {

	Player *player = static_cast<Player*>(mgr->getPlayer());
	Vec2d position = player->getPosition();

	switch (c) {
		case 'a':
			position.x--;
			break;
		case 'd':
			position.x++;
			break;
		case 'w':
			position.y--;
			break;
		case 's':
			position.y++;
			break;
		case 'm':
			if (!mtr.displayWindow) {
				mtr.displayWindow = 1;
				displayMetrics(mtr);
			} else {
				hideMetrics(mtr);
			}
			break;
		case 'b':
			mgr->showBoundingBox = (mgr->showBoundingBox == true) ? false : true;
			break;
		case 'x':
			if (displayDialog()) {
				clearScreen();
				RUNNING = 0;
			}
			return;
		case 'i':
			if (!player->showStats) {
				player->showStats = 1;
				player->displayStats();
			} else {
				player->hideStats();
			}
			break;
    }

	player->roomCheck(terrain, position);

	if (mgr->canWalkTo(player, position)) {
		player->setPosition(position);
	}
}
void initWindowsAPI(void) {
	HWND hwnd = GetConsoleWindow();
	HWND owner = GetWindow(hwnd, GW_OWNER);
	SendMessage(owner, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	Sleep(10);
}
void initPDCurses(void) {
	initscr();
	curs_set(0);
	noecho();
	nodelay(stdscr, true);
	if (has_colors()) {
		start_color();
	}
}
int main() {
	using namespace std;
	
	initWindowsAPI();
	drawLogo(50, 20);
	initPDCurses();

	metrics mtr = { 0 };
	initTimeCounter(mtr);

	int _rows = 0,
		_cols = 0;
	getmaxyx(stdscr, _rows, _cols);

	//textureManager
	TextureManager textureManager;

	//color pairs
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_CYAN);
	init_pair(6, COLOR_BLACK, COLOR_RED);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);

	init_color(LIGHT_GREEN_COLOR, 714, 917, 203);
	init_pair(8, LIGHT_GREEN_COLOR, COLOR_BLACK);
	init_pair(9, COLOR_BLUE, COLOR_BLACK);
	init_color(BROWN_COLOR, 867, 718, 527);
	init_pair(10, BROWN_COLOR, COLOR_BLACK);

	int x = 10, y = 10;

	float time_diff = 0;

	Terrain terrain;
	Player *player = static_cast<Player*>(terrain.room[1][1].entity_manager->getPlayer());

	BattleManager battleManager;

	Item* relic1 = new Relic(Vec2d(10, 10), 5, RelicType::AttackBoost);
	Item* relic2 = new Relic(Vec2d(20, 20), 5, RelicType::SpeedBoost);
	Item* relic3 = new Relic(Vec2d(30, 30), 5, RelicType::HealthBoost);
	std::vector<Item*> relics = { relic1, relic2, relic3 };

	while (RUNNING) {

		updateTimeCounter(mtr);
		calculateFPS(mtr);

		// Drawing of the Entities goes here.
		terrain.room[player->terrain_room_x][player->terrain_room_y].drawSelf();
		for (Item* r : relics) {
			if (r) {
				r->drawSelf();
			}
		}
		terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager->renderAll();
		mvprintw(_rows - 1, 0, "Player Stats [ Health: %d    Attack: %d    Defence: %d    Speed: %d ]", player->getHealth(), player->getAttack(), player->getDefence(), player->getSpeed());
		
		displayMetrics(mtr);
		static_cast<Player*>(player)->displayStats();

		// Collision detection and response goes here
		/*
		if (collisionDetectionBoundinBox(entityManager.getPlayer(), entityManager.getEnemies())) {
			mvprintw(0, 40, "Collision!!");
		}
		*/
		
		// Relics Collision Detection
		for (Item*& r : relics) {
			if (r && circleCollisionItem(terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager->getPlayer(), r, 5.0f)) {

				Relic* relic = static_cast<Relic*>(r);
				relic->onPickUp(*static_cast<Player*>(player));

				// Meldung anzeigen
				int midY = _rows / 2;
				int midX = _cols / 2;
				mvprintw(midY, midX - 7, "RELIC COLLECTED!");
				mvprintw(midY + 1, midX - 18, "Your stats have been increased.");

				nodelay(stdscr, false);
				getch();
				nodelay(stdscr, true);

				player->setAttack(player->getAttack() + 20);
				player->addRelic();

				delete r;
				r = nullptr;

				break;
			}
		}

		//Gatekeeper win state
		if (terrain.gateKeeper != nullptr &&
			player->terrain_room_x == terrain.gatekeeperRoomX &&
			player->terrain_room_y == terrain.gatekeeperRoomY) {

			float distanceX = calculateAbsoluteDistance(player->getPosition().x, terrain.gateKeeper->getPosition().x);
			float distanceY = calculateAbsoluteDistance(player->getPosition().y, terrain.gateKeeper->getPosition().y);

		
			if (distanceX < 4.0f && distanceY < 4.0f) {
				clearScreen();
				if (player->getRelicCount() >= 3) {
				
					mvprintw(15, 45, "GATEKEEPER: Access granted. You have proven yourself!");
					mvprintw(17, 45, "CONGRATULATIONS, YOU HAVE WON THE GAME!");
					mvprintw(20, 45, "Do you want to play again? [y/N]");
					refresh();

					nodelay(stdscr, false);
					char input = getch();
					if (input == 'y' || input == 'Y') {
						
						player->relicCount = 0;
						terrain.removeGatekeeper();
						terrain.positionGatekeeper();
						for (Item*& r : relics) {
							delete r;   
							r = nullptr;
						}

						relics[0] = new Relic(Vec2d(10, 10), 5, RelicType::AttackBoost);
						relics[1] = new Relic(Vec2d(20, 20), 5, RelicType::SpeedBoost);
						relics[2] = new Relic(Vec2d(30, 30), 5, RelicType::HealthBoost);
					}

					else {
					
						RUNNING = 0;
					}
					nodelay(stdscr, true);
				}
				else {
					mvprintw(15, 40, "GATEKEEPER: No, you don't have enough relics.");
					mvprintw(16, 40, "Bring me first enough relics to win! (Current: %d / 3)", player->getRelicCount());
					player->setPosition(player->getPosition() - (player->getDirection() * 2));
					refresh();

					nodelay(stdscr, false);
					getch();
					nodelay(stdscr, true);
				}
				clearScreen();
			}
		}
	

		// BattleManager Collision Detection 
		auto collider = circleCollisionDetection(terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager->getPlayer(), terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager->getEnemies());
		if (collider.size() > 0) {

			//start battle and save result
			int battleResult = battleManager.startBattle(terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager->getPlayer(), collider.front(), 1);

			//battle won
			if (battleResult == 1) {
				terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager->removeEntity(collider.front());
			}
			//battle lost
			else {
				//end the program
				clearScreen();
				return 0;
			}
		}

		refresh();

		int c = getch(stdin);
		keyDispatcher(mtr, c, &terrain, terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager);

		// Sleep so much as we need to keep us at 60 fps. 
		time_diff = mtr.deltaTime > 0.016666 ? 0 : (0.016666 - mtr.deltaTime) * 100000;
		usleep(time_diff);

		// clear screen
		wclear(stdscr);
	}

	endwin();

	return 0;
}