#include "retroBattle.h"

void keyDispatcher(metrics& mtr, const char c, EntityManager *mgr) {

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
			mgr->RUNNING = 0;
			break;
		case 'i':
			if (!player->showStats) {
				player->showStats = 1;
				player->displayStats();
			} else {
				player->hideStats();
			}
			break;
    }
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

	//color pairs
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_CYAN);
	init_pair(6, COLOR_BLACK, COLOR_RED);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);

	int x = 10, y = 10;

	float time_diff = 0;

	Entity* player = new Player(1, 5, 5, Vec2d(30.0, 30.0));
	Entity* enemy1 = new Enemy(2, 5, 5, Vec2d(60.0, 20.0));
	Entity* enemy2 = new Enemy(3, 5, 5, Vec2d(20.0, 30.0));
	Entity* enemy3 = new Enemy(4, 5, 5, Vec2d(45.0, 15.0));
	Entity* enemy4 = new Enemy(2, 5, 5, Vec2d(100.0, 20.0));
	Entity* enemy5 = new Enemy(3, 5, 5, Vec2d(120.0, 30.0));
	Entity* enemy6 = new Enemy(4, 5, 5, Vec2d(145.0, 15.0));

	//GateKeeper
	MersenneTwister tempRng;
	int randX = tempRng.getRandomNumber(5, _cols - 5);
	int randY = tempRng.getRandomNumber(5, _rows - 5);
	Entity* gateKeeper = new GateKeeper(7, 5, 5, Vec2d(randX, randY));
	


	std::vector<Entity*> entities = { player, enemy1, enemy2, enemy3, enemy4, enemy5, enemy6, gateKeeper };
	EntityManager entityManager(entities);
	/*
	entityManager.add(enemy2);
	entityManager.add(enemy3);
	*/

	BattleManager battleManager;

	Room startRoom = Room(_cols, _rows);

//	Item* relic = new Relic(Vec2d(0, 0), 5, RelicType::AttackBoost);

	Item* relic1 = new Relic(Vec2d(10, 10), 5, RelicType::AttackBoost);
	Item* relic2 = new Relic(Vec2d(20, 20), 5, RelicType::SpeedBoost);
	Item* relic3 = new Relic(Vec2d(30, 30), 5, RelicType::HealthBoost);

	std::vector<Item*> relics = { relic1, relic2, relic3 };


	while (entityManager.RUNNING) {
		// clear screen
		wclear(stdscr);
		updateTimeCounter(mtr);
		calculateFPS(mtr);

		// Drawing of the Entities goes here.
		startRoom.drawSelf();
		//if (relic) relic->drawSelf();
		for (Item* r : relics) {
			if (r) r->drawSelf();
		}

		entityManager.renderAll();


		displayMetrics(mtr);
		static_cast<Player*>(player)->displayStats();

		// Collision detection and response goes here
		/*
		if (collisionDetectionBoundinBox(entityManager.getPlayer(), entityManager.getEnemies())) {
			mvprintw(0, 40, "Collision!!");
		}
		*/

		//GateKeeper collision
		if (circleCollisionDetection(entityManager.getPlayer(), { gateKeeper }) != nullptr) {
			int midY = _rows / 2;
			int midX = _cols / 2;

			mvprintw(midY, midX - 4, "YOU WON!");
			mvprintw(midY + 1, midX - 15, "Press any key to restart...");
			
			
			nodelay(stdscr, false);
			getch();
			nodelay(stdscr, true);

			entityManager.getPlayer()->setPosition(Vec2d(30.0, 30.0));
			gateKeeper->setPosition(Vec2d(tempRng.getRandomNumber(5, _cols - 5), tempRng.getRandomNumber(5, _rows - 5)));
			continue;
		}

		//Relic collision
		for (Item*& r : relics) {
			if (r && circleCollisionItem(entityManager.getPlayer(), r, 5.0f)) {

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

				delete r;
				r = nullptr;

				break; 
			}
		}





			//if (relic && circleCollisionItem(entityManager.getPlayer(), relic, 5.0f)) {
			//	// Bildschirmmitte berechnen
			//	int midY = _rows / 2;
			//	int midX = _cols / 2;

			//	// Meldung anzeigen
			//	mvprintw(midY, midX - 7, "RELIC COLLECTED!");
			//	mvprintw(midY + 1, midX - 18, "Your attack buffs have been increased by 20%.");
			//	

			//	// Spiel kurz pausieren, bis Spieler bestätigt
			//	nodelay(stdscr, false);
			//	getch();
			//	nodelay(stdscr, true);

			//	// Effekt anwenden (Relic bufft Player)
			//	static_cast<Relic*>(relic)->onPickUp(*static_cast<Player*>(player));


			//	// Item entfernen (despawnen) - erst freigeben, dann Pointer nullen
			//	delete relic;
			//	relic = nullptr;

			//	continue;
			//}
			

		//check for collision
		Entity* collider = circleCollisionDetection(entityManager.getPlayer(), entityManager.getEnemies());
		if (collider != nullptr) {
			mvprintw(0, 40, "Circle Collision!!");

			//start battle and save result
			int battleResult = battleManager.startBattle(entityManager.getPlayer(), collider, 1);

			//battle won
			if (battleResult == 1) {
				entityManager.removeEntity(collider);
			}
			//battle lost
			else{
				//end the program
				return 0;
			}			
		}	
		
		//mvprintw(0, 0, "_rows: %d    _cols: %d", _rows, _cols);
		refresh();

		int c = getch(stdin);
		keyDispatcher(mtr, c, &entityManager);

		// Sleep so much as we need to keep us at 60 fps. 
		time_diff = mtr.deltaTime > 0.016666 ? 0 : (0.016666 - mtr.deltaTime) * 100000;
		usleep(time_diff);

		
	}

	endwin();
	clearScreen();
	
	return 0;
}
