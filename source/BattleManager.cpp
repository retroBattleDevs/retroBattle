#include "headers/BattleManager.h"

BattleManager::BattleManager(){
	entityList = {};
	turnCounter = 0;
	currentTurn = 0;
	totalEntities = 1;
	roundCounter = 1;
	currentState = moveSelect;

	//fixed moves
	availableMoves.push_back(new AttackMove("Punch", 90, 10));
	availableMoves.push_back(new AttackMove("Heavy Punch", 60, 20));
	availableMoves.push_back(new AttackMove("Risky Punch", 30, 50));
	availableMoves.push_back(new HealMove("Weak Heal", 100, 15));
	availableMoves.push_back(new HealMove("Strong Heal", 30, 50));
	availableMoves.push_back(new BuffMove("Attack Buff", 100, 2, TargetStat::ATTACK, true));   // Buff
	availableMoves.push_back(new BuffMove("Speed DeBuff", 100, 2, TargetStat::SPEED, true));    // Buff
	availableMoves.push_back(new BuffMove("Dfns Debuff", 85, 1, TargetStat::DEFENSE, false));  // Debuff
}

int BattleManager::startBattle(Entity* hero, std::vector<Entity*>& enemies) {

	hero->resetBuffStages();
	for (Entity* enemy : enemies) {
		if (enemy) {
			enemy->resetBuffStages();
		}
	}

	entityList.push_back(hero);

	for (Entity* enemy : enemies) {
		if (enemy) {
			entityList.push_back(enemy);
			turnCounter++;
		}
	}


	totalEntities += 1 + static_cast<int>(enemies.size()) - 1;
	calculateTurnOrder();

	wclear(stdscr);
	int input = -1;
	int selectedMove = -1;
	int selectedTarget = -1;
	while (true) {
		
		DrawUI(selectedMove,selectedTarget);

		int winner = checkWinner();
		if (winner != 0) {
			resetForNextBattle();
			return winner;
		}

		//debug return
		if (input == 'k') {
			printLog("Hero won the battle");
			refresh();
			Sleep(5000);
			resetForNextBattle();
			return 1;
		}
		if (input == 'l') {
			printLog("Hero lost the battle");
			refresh();
			Sleep(5000);
			resetForNextBattle();
			return -1;
		}

		switch (currentState) {
		case moveSelect:
			moveSelectAction(selectedMove, input);
			break;
		case targetSelect:
			targetSelectAction(selectedMove, selectedTarget, input);
			break;
		case performSelectedMove:
			performMoveAction(selectedMove, selectedTarget);
			Sleep(3500);
			selectedMove = -1;
			selectedTarget = -1;
			nextTurn();
			break;
		default:
			break;
		}

		input = getch(stdin);
		wclear(stdscr);
	}

}

void BattleManager::changeState(BattleState state){
	currentState = state;
}

void BattleManager::calculateTurnOrder(){
	turnOrder.clear();

	for (int i = 0; i < totalEntities; i++) {
		turnOrder.push_back(i);
	}

	std::sort(turnOrder.begin(), turnOrder.end(), [this](int a, int b) {
		return entityList[a]->getFinalSpeed() > entityList[b]->getFinalSpeed();
	});
}

void BattleManager::moveSelectAction(int& selectedMove, int input){
	//heros turn
	if (isHerosTurn()) {
		if (input == -1) {
			
		}
		attron(COLOR_PAIR(1));
		mvprintw(23, 2, "Heros turn:");
		attroff(COLOR_PAIR(1));
		printELog("Use wasd to move trough the move list. Press space to lock in move.");
		if (input != -1) {
			switch (input) {
			case 's':
			case 'd':
				selectedMove++;
				if (selectedMove > availableMoves.size() - 1) {
					selectedMove = 0;
				}
				break;
			case 'w':
			case 'a':
				selectedMove--;
				if (selectedMove < 0) {
					selectedMove = availableMoves.size() - 1;
				}
				break;
			case ' ':
				if(selectedMove != -1)
				changeState(targetSelect);
			default:
				break;
			}
		}
	}
	//enemy turn
	else {
		attron(COLOR_PAIR(2));
		mvprintw(23, 2, "Enemys turn:");
		attroff(COLOR_PAIR(2));
		printELog("Choosing move");
		refresh();
		Sleep(2000);
		int randomIdx = rand() % availableMoves.size();
		selectedMove = (randomIdx);
		changeState(targetSelect);
	}
}

void BattleManager::targetSelectAction(int& selectedMove, int& selectedTarget,int input){
	if (selectedMove == -1) return;
	int moveIdx = selectedMove;
	BattleMove* move = availableMoves[moveIdx];
	MoveCategory cat = move->getCategory();
	//heros turn
	if (isHerosTurn()) {
		if (cat == MoveCategory::BUFF || cat == MoveCategory::HEAL) {
			selectedTarget = 0;
			changeState(performSelectedMove);
			return;
		}

		if (totalEntities == 2) {
			selectedTarget = 1;
			changeState(performSelectedMove);
			return;
		}

		if (selectedTarget == 0) {
			selectedTarget = 1;
		}

		printELog("Use wasd to move trough the enemy list. Press space to lock in target.");
		if (input != -1) {
			switch (input) {
			case 's':
			case 'd':
				selectedTarget++;
				if (selectedTarget > totalEntities - 1) {
					selectedTarget = 1;
				}
				break;
			case 'w':
			case 'a':
				selectedTarget--;
				if (selectedTarget < 1) {
					selectedTarget = totalEntities - 1;
				}
				break;
			case ' ':
				if (selectedTarget != -1) {
					changeState(performSelectedMove);
				}
			default:
				break;
			}
		}
	}
	//enemy turn
	else {
		if (cat == MoveCategory::BUFF || cat == MoveCategory::HEAL) {
			//terget itself
			selectedTarget = turnOrder[currentTurn];
		}
		else {
			//target hero
			selectedTarget = 0;
		}
		changeState(performSelectedMove);
	}
}

void BattleManager::performMoveAction(int selectedMove, int selectedTarget){
	performMove(selectedMove, selectedTarget);
	changeState(moveSelect);
}

void BattleManager::performMove(int selectedMove, int selectedTarget){
	int moveIndex = selectedMove;
	int targetIndex = selectedTarget;

	int entityIndex = turnOrder[currentTurn];

	BattleMove* move = availableMoves[moveIndex];
	Entity* executor = entityList[entityIndex];
	Entity* target = entityList[targetIndex];

	bool success = move->execute(*executor, *target);
	
	std::string executorName = (isHerosTurn()) ? "Hero " : "Enemy" + std::to_string(entityIndex);
	std::string logMsg;

	if (isHerosTurn()) {
		attron(COLOR_PAIR(1));
	}
	else
	{
		attron(COLOR_PAIR(2));
	}

	mvprintw(23, 2, executorName.c_str());

	logMsg = " used " + move->getName();
	attron(COLOR_PAIR(4));
	mvprintw(23, 8, logMsg.c_str());
	attroff(COLOR_PAIR(4));

	if (!success) {
		attron(COLOR_PAIR(2));
		printELog("... but it MISSED!");
		attroff(COLOR_PAIR(2));
		refresh();
		return;
	}
	else {
		attron(COLOR_PAIR(3));
		logMsg = "";
		switch (move->getCategory()) {
		case MoveCategory::ATTACK:
			logMsg += (isHerosTurn()) ? "on Enemy " + std::to_string(targetIndex) : " on Hero";
			break;
		case MoveCategory::HEAL:
			logMsg += "to recover HP!";
			break;
		case MoveCategory::BUFF:
			logMsg += "to boost stats!";
			break;
		case MoveCategory::DEBUFF:
			logMsg += "to weaken the foe!";
			break;
		}
	}

	printELog(logMsg);
	attroff(COLOR_PAIR(3));
	refresh();
}

void BattleManager::nextTurn(){
	bool foundValidTurn = false;

	while (!foundValidTurn) {
		currentTurn++;

		if (currentTurn >= totalEntities) {
			currentTurn = 0;
			roundCounter++;
			calculateTurnOrder();
		}

		int actorIdx = turnOrder[currentTurn];

		if (entityList[actorIdx]->getHealth() > 0) {
			foundValidTurn = true;
		}
	}
}

int BattleManager::checkWinner(){
	if (entityList[0]->getHealth() <= 0) {
		printLog("Herro lost the battle");
		refresh();
		Sleep(5000);
		return -1;
	}
	bool endBattle = true;
	for (int i = 1;i < totalEntities;i++) {
		if (entityList[i]->getHealth() > 0) {
			endBattle = false;
			break;
		}
	}
	if (endBattle) {
		printLog("Herro won the battle");
		refresh();
		Sleep(5000);
		return 1;
	}
	return 0;
}

bool BattleManager::isHerosTurn() const{
	int activeEntityIndex = turnOrder[currentTurn];
	return activeEntityIndex == 0;
}

void BattleManager::resetForNextBattle(){
	entityList = {};
	turnCounter = 0;
	currentTurn = 0;
	totalEntities = 1;
	roundCounter = 1;
	currentState = moveSelect;
}

void BattleManager::DrawUI(int selectedMove,int selectedTarget) {
	attron(COLOR_PAIR(1));
	mvprintw(0, 0, std::string(156, '-').c_str());
	mvprintw(22, 0, std::string(156, '-').c_str());
	mvprintw(25, 0, std::string(156, '-').c_str());
	mvprintw(40, 0, std::string(156, '-').c_str());
	for (int i = 1;i <= 39;i++) {
		mvprintw(i, 0, "|");
		mvprintw(i, 155, "|");
	}
	for (int i = 26;i <= 39;i++) {
		mvprintw(i, 22, "|");
		mvprintw(i, 70, "|");
	}
	attroff(COLOR_PAIR(1));

	//round counter and turn order
	mvprintw(1, 2, "Round: %d",roundCounter);
	mvprintw(2, 2, "Turn order: ");

	for (int i = 0;i < turnOrder.size();i++) {
		int entityIndex = turnOrder[i];

		bool isHeroAtThisPosition = (entityIndex == 0);
		std::string label;
		if (isHeroAtThisPosition) {
			label = "H ";
			attron(COLOR_PAIR(1));
		}
		else {
			label = "E" + std::to_string(entityIndex);
			attron(COLOR_PAIR(2));
		}
		if (i < turnOrder.size() - 1) {
			label += "->";
		}
		mvprintw(2, 14 + (i * 4), label.c_str());
		attroff(COLOR_PAIR(1));
		attroff(COLOR_PAIR(2));
		if (i == currentTurn) {
			mvprintw(1, 14 + (i * 4), "V");
		}
		
	}

	//stats
	printHeroStats();
	printHeroMoves(selectedMove);
	printEnemyStats(selectedTarget);
	drawBackGround(15,40);
	for (int i = 1;i < totalEntities;i++) {
		drawEnemy(12, 90 + (15 * i));
	}
	drawHero(3,14);
}

void BattleManager::printLog(std::string strg) {
	mvprintw(23, 2, strg.c_str());
}

void BattleManager::printELog(std::string strg){
	mvprintw(24, 2, strg.c_str());
}

void BattleManager::printHeroStats(){
	attron(COLOR_PAIR(1));
	mvprintw(27, 3, "Hero:");
	mvprintw(28, 3, std::string(17, '-').c_str());
	mvprintw(29, 3, "Hp:");
	mvprintw(29, 12, "|%d/%d", entityList[0]->getHealth(), entityList[0]->getHitPoints());
	mvprintw(30, 3, "Attack:");
	mvprintw(30, 12, "|%d (%d)", entityList[0]->getFinalAttack(), entityList[0]->getAttack());
	mvprintw(31, 3, "Defence:");
	mvprintw(31, 12, "|%d (%d)", entityList[0]->getFinalDefence(), entityList[0]->getDefence());
	mvprintw(32, 3, "Speed:");
	mvprintw(32, 12, "|%d (%d)", entityList[0]->getFinalSpeed(), entityList[0]->getSpeed());
	attroff(COLOR_PAIR(1));
}

void BattleManager::printHeroMoves(int selectedMove){
	attron(COLOR_PAIR(3));
	mvprintw(27, 25, "Available moves: | POW | ACU | TYPE");
	mvprintw(28, 25, std::string(43, '-').c_str());
	
	for (int i = 0; i < availableMoves.size(); i++) {
		int y = 29 + i;
		BattleMove* move = availableMoves[i];

		// Selection indicator
		if (selectedMove == i) {
			attron(COLOR_PAIR(5));
			mvprintw(y, 23, " > ");
		}
		else {
			attron(COLOR_PAIR(3));
			mvprintw(y, 23, "   ");
		}

		std::string typeStr = getShortType(move->getCategory());

		// Print the specific format:
		// Index: Name ,power: Val, Acc% , [Type]
		mvprintw(y, 26, "%d: %-12s , %3d, %3d%% , [%s]",
			i + 1,
			move->getName().c_str(),
			move->getValue(),
			move->getAccuracy(),
			typeStr.c_str());
	}
	
	attroff(COLOR_PAIR(3));
}

void BattleManager::printEnemyStats(int selectedTarget){
	
	attron(COLOR_PAIR(2));
	mvprintw(27, 73, "Enemy stats:");
	mvprintw(28, 73, std::string(43, '-').c_str());
	for (int i = 1;i < totalEntities;i++) {
		if (selectedTarget == i) {
			attron(COLOR_PAIR(6));
			mvprintw(29, 72 + ((i - 1) * 20), ">");
		} 
		mvprintw(29, 73 + ((i - 1) * 20), "Enemy %d", i);
		attron(COLOR_PAIR(2));
		mvprintw(30, 73 + ((i - 1) * 20), "Hp:");
		mvprintw(30, 82 + ((i - 1) * 20), "|%d/%d", entityList[i]->getHealth(), entityList[i]->getHitPoints());
		mvprintw(31, 73 + ((i - 1) * 20), "Attack:");
		mvprintw(31, 82 + ((i - 1) * 20), "|%d (%d)", entityList[i]->getAttack(), entityList[i]->getFinalAttack());
		mvprintw(32, 73 + ((i - 1) * 20), "Defence:");
		mvprintw(32, 82 + ((i - 1) * 20), "|%d (%d)", entityList[i]->getDefence(), entityList[i]->getFinalDefence());
		mvprintw(33, 73 + ((i - 1) * 20), "Speed:");
		mvprintw(33, 82 + ((i - 1) * 20), "|%d (%d)", entityList[i]->getFinalSpeed(), entityList[i]->getSpeed());
	}
	attroff(COLOR_PAIR(2));
	mvprintw(38, 73, "Stat format: |BuffedStat (BaseStat)");
}

void BattleManager::drawBackGround(int y, int x){
	int pos_y = y;
	int pos_x = x;

	attron(COLOR_PAIR(3));
	mvprintw(pos_y - 13, pos_x, "               )\\         O_._._._A_._._._O         /(");
	mvprintw(pos_y - 12, pos_x, "                \\`--.___,'=================`.___,--'/");
	mvprintw(pos_y - 11, pos_x, "                 \\`--._.__                 __._,--'/");
	mvprintw(pos_y - 10, pos_x, "                   \\  ,. l`~~~~~~~~~~~~~~~'l ,.  /");
	mvprintw(pos_y - 9, pos_x, "       __            \\||(_)!_!_!_.-._!_!_!(_)||/            __");
	mvprintw(pos_y - 8, pos_x, "       \\\\`-.__        ||_|____!!_|;|_!!____|_||        __,-'//");
	mvprintw(pos_y - 7, pos_x, "        \\\\    `==---='-----------'='-----------`=---=='    //");
	mvprintw(pos_y - 6, pos_x, "        | `--.                                         ,--' |");
	mvprintw(pos_y - 5, pos_x, "         \\  ,.`~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~',.  /");
	mvprintw(pos_y - 4, pos_x, "           \\||  ____,-------._,-------._,-------.____  ||/");
	mvprintw(pos_y - 3, pos_x, "            ||\\|___!`=======\"!`=======\"!`=======\"!___|/||");
	mvprintw(pos_y - 2, pos_x, "            || |---||--------||-| | |-!!--------||---| ||");
	mvprintw(pos_y - 1, pos_x, "  __O_____O_ll_lO_____O_____O|| |'|'| ||O_____O_____Ol_ll_O_____O__");
	mvprintw(pos_y    , 1, std::string(154, '-').c_str());
	attroff(COLOR_PAIR(3));
}

void BattleManager::drawEnemy(int y, int x){
	attron(COLOR_PAIR(2));
	mvprintw(y + 0, x, "    _____");
	mvprintw(y + 1, x, " \\_\\(),()/_/");
	mvprintw(y + 2, x, "   (,___,)");
	mvprintw(y + 3, x, "  ,-/`~`\\-,___");
	mvprintw(y + 4, x, " / /).:.('--._)");
	mvprintw(y + 5, x, "{_[ (_,_)");
	mvprintw(y + 6, x, "    | Y |");
	mvprintw(y + 7, x, "   /  |  \\");
	mvprintw(y + 8, x, "   """ """");
	attroff(COLOR_PAIR(2));
}

void BattleManager::drawHero(int y, int x){
	attron(COLOR_PAIR(1));
	mvprintw(y + 0, x, "      _ _");
	mvprintw(y + 1, x, "     /.-.`.");
	mvprintw(y + 2, x, "    //o;o\\ \\");
	mvprintw(y + 3, x, "    \\\\_-_/)/");
	mvprintw(y + 4, x, "    _`) ( _\\\\");
	mvprintw(y + 5, x, " .`) '-.-' ( `.");
	mvprintw(y + 6, x, "/ `/   .   \\`. \\");
	mvprintw(y + 7, x, "\\ \\\\___A___/_` /");
	mvprintw(y + 8, x, " '-)|)=@=(|(-'`\\");
	mvprintw(y + 9, x, "   |/\\   /\\|  )/");
	mvprintw(y + 10, x, "   /__\\_/__\\");
	mvprintw(y + 11, x, "  '---' '---'");
	mvprintw(y + 12, x, "   \\ /   \\ /");
	mvprintw(y + 13, x, "   ( )   ( )");
	mvprintw(y + 14, x, "   /_\\   /_\\");
	mvprintw(y + 15, x, "  '---' '---'");
	mvprintw(y + 16, x, "   \\ /   \\ /");
	mvprintw(y + 17, x, "   /_\\   /_\\");
	attroff(COLOR_PAIR(1));
}

std::string BattleManager::getShortType(MoveCategory cat) {
	switch (cat) {
	case MoveCategory::ATTACK: return "A";
	case MoveCategory::BUFF:   return "B";
	case MoveCategory::DEBUFF: return "DB";
	case MoveCategory::HEAL:   return "H";
	default:                   return "?";
	}
}
