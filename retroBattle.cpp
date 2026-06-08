#include "retroBattle.h"
#include "headers/general_funcs.h"



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
	AnimatorManager animationManager(textureManager);

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

	Terrain terrain(animationManager);
	Player *player = static_cast<Player*>(terrain.room[1][1].entity_manager->getPlayer());

	BattleManager battleManager;

	

	while (RUNNING) {

		updateTimeCounter(mtr);
		calculateFPS(mtr);

		// Drawing of the Entities goes here.

		Room& currentRoom = terrain.room[player->terrain_room_x][player->terrain_room_y];

		currentRoom.drawSelf();
		currentRoom.drawRelics();
		currentRoom.entity_manager->renderAll();

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
		

		// vor dem Aufruf: merken, wie viele Relics der Spieler hatte
		int relicsBefore = player->getRelicCount();

		currentRoom.updateRelics(player);

		// wenn sich RelicCount erhöht hat → Meldung anzeigen
		if (player->getRelicCount() > relicsBefore) {
			int midY = _rows / 2;
			int midX = _cols / 2;
			mvprintw(midY, midX - 7, "RELIC COLLECTED!");
			mvprintw(midY + 1, midX - 18, "Your stats have been increased.");

			nodelay(stdscr, false);
			getch();
			nodelay(stdscr, true);
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
				
					mvprintw(15, 45, "GATEKEEPER: Access granted. You have proven yourself worthy!");
					mvprintw(17, 45, "CONGRATULATIONS, YOU HAVE WON THE GAME!");
					mvprintw(20, 45, "Do you want to play again? [y/N]");
					refresh();

					nodelay(stdscr, false);
					char input = getch();
					if (input == 'y' || input == 'Y') {
						
						player->relicCount = 0;
						player->setAttack(10);
						terrain.removeGatekeeper();
						terrain.positionGatekeeper();
						for (int x = 0; x < 3; ++x) {
							for (int y = 0; y < 3; ++y) {
								terrain.room[x][y].spawnRelics();
							}
						}

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
			auto enemies = getEnemiesInRadius(terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager->getPlayer(), terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager->getEnemies(), 20);
			int battleResult = battleManager.startBattle(terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager->getPlayer(), enemies);

			//battle won
			if (battleResult == 1) {
				for (Entity* enemy : enemies) {
					if (enemy) {
						terrain.room[player->terrain_room_x][player->terrain_room_y].entity_manager->removeEntity(enemy);
					}
				}
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