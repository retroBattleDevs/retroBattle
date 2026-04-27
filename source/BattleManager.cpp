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
	availableMoves.push_back(new BuffMove("Focus", 100, 2, TargetStat::ATTACK, true));   // Buff
	availableMoves.push_back(new BuffMove("Sprint", 100, 2, TargetStat::SPEED, true));    // Buff
	availableMoves.push_back(new BuffMove("Armor Break", 85, 1, TargetStat::DEFENSE, false));  // Debuff
}

int BattleManager::startBattle(Entity* hero, Entity* enemy, int enemyCount) {

	hero->resetBuffStages();
	enemy->resetBuffStages();

	entityList.push_back(hero);

	entityList.push_back(enemy);
	for (int i = 1;i < enemyCount;i++) {
		turnCounter++;
		entityList.push_back(enemy);
	}

	totalEntities += enemyCount;
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
			resetForNextBattle();
			return 1;
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

bool BattleManager::isValidMove(int selectedMove)
{
	int moveIdx = selectedMove - '1';

	return (moveIdx >= 0 && moveIdx < availableMoves.size());
}

bool BattleManager::isValidTarget(int selectedTarget)
{
	return (selectedTarget - '0' >= 1 && selectedTarget - '0' < totalEntities);
}

void BattleManager::moveSelectAction(int& selectedMove,int input){
	//heros turn
	if (isHerosTurn()) {
		printLog("Heros turn: Please select a move from moves list");
		if (input != -1) selectedMove = input;
		if (selectedMove == -1) return;
		if (!isValidMove(input)) {
			printELog("Invalid selection. Please choose a different move.");
		}
		else {
			changeState(targetSelect);
		}
	}
	//enemy turn
	else {
		printLog("Enemys turn: Chossing move");
		refresh();
		Sleep(2000);
		int randomIdx = rand() % availableMoves.size();
		selectedMove = (randomIdx + 1) + '0';
		changeState(targetSelect);
	}
}

void BattleManager::targetSelectAction(int& selectedMove, int& selectedTarget,int input){
	if (selectedMove == -1) return;
	int moveIdx = selectedMove - '1';
	BattleMove* move = availableMoves[moveIdx];
	MoveCategory cat = move->getCategory();
	//heros turn
	if (isHerosTurn()) {
		if (cat == MoveCategory::BUFF || cat == MoveCategory::HEAL) {
			printLog("Hero selected " + move->getName() + " move");
			selectedTarget = '0';
			changeState(performSelectedMove);
			return;
		}

		printLog("Please select a target from targets list");

		if (input != -1) selectedTarget = input;
		if (selectedTarget == -1) return;

		if (!isValidTarget(input)) {
			printELog("Invalid selection. Please choose a different target.");
		}
		else {
			changeState(performSelectedMove);
		}
	}
	//enemy turn
	else {
		if (cat == MoveCategory::BUFF || cat == MoveCategory::HEAL) {
			//terget itself
			selectedTarget = (char)(turnOrder[currentTurn] + '0');
		}
		else {
			//target hero
			selectedTarget = '0';
		}
		changeState(performSelectedMove);
	}
}

void BattleManager::performMoveAction(int selectedMove, int selectedTarget){
	performMove(selectedMove, selectedTarget);
	changeState(moveSelect);
}

void BattleManager::performMove(int selectedMove, int selectedTarget){
	int moveIndex = selectedMove - '1';
	int targetIndex = selectedTarget - '0';

	int entityIndex = turnOrder[currentTurn];

	BattleMove* move = availableMoves[moveIndex];
	Entity* executor = entityList[entityIndex];
	Entity* target = entityList[targetIndex];

	bool success = move->execute(*executor, *target);
	
	std::string executorName = (isHerosTurn()) ? "Hero " : "Enemy " + std::to_string(entityIndex);
	std::string logMsg;

	if (!success) {
		logMsg = (executorName + " used " + move->getName() + "... but it MISSED!");
	}
	else {
		logMsg = (executorName + " used " + move->getName());
		switch (move->getCategory()) {
		case MoveCategory::ATTACK:
			logMsg += (isHerosTurn()) ? " on Enemy " + std::to_string(targetIndex) : " on the Hero";
			break;
		case MoveCategory::HEAL:
			logMsg += " to recover HP!";
			break;
		case MoveCategory::BUFF:
			logMsg += " to boost stats!";
			break;
		case MoveCategory::DEBUFF:
			logMsg += " to weaken the foe!";
			break;
		}
	}

	printLog(logMsg);
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
		printLog("Herro lost the battle (returning -1)");
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
		printLog("Herro won the battle (returning 1)");
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
	for (int i = 2;i < totalEntities;i++) {
		delete(entityList[i]);
	}
	
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
}

void BattleManager::printLog(std::string strg) {
	mvprintw(23, 2, strg.c_str());
}

void BattleManager::printELog(std::string strg){
	mvprintw(24, 1, strg.c_str());
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
		if (selectedMove - '1' == i) {
			mvprintw(y, 23, " > ");
		}
		else {
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
		if(selectedTarget - '0' == i) mvprintw(29, 72 + ((i - 1) * 20), ">");
		mvprintw(29, 73 + ((i - 1) * 20), "Enemy %d", i);
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

std::string BattleManager::getShortType(MoveCategory cat) {
	switch (cat) {
	case MoveCategory::ATTACK: return "A";
	case MoveCategory::BUFF:   return "B";
	case MoveCategory::DEBUFF: return "DB";
	case MoveCategory::HEAL:   return "H";
	default:                   return "?";
	}
}
