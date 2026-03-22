#include "headers/BattleManager.h"


BattleManager::BattleManager(){
	entityList = {};
	turnCounter = 0;
	currentTurn = 0;
	totalEntities = 1;
	currentState = moveSelect;
}

int BattleManager::startBattle(Entity* hero, Entity* enemy, int enemyCount) {

	entityList.push_back(hero);

	entityList.push_back(enemy);
	for (int i = 1;i < enemyCount;i++) {
		turnCounter++;
		entityList.push_back(new TestEntity(*enemy));
	}

	totalEntities += enemyCount;

	wclear(stdscr);
	int input = -1;
	int selectedMove = -1;
	int selectedTarget = -1;
	while (true) {
		
		DrawUI();
		printHeroStats();
		printHeroMoves(selectedMove);
		printEnemyStats(selectedTarget);

		int winner = checkWinner();
		if (winner != 0) {
			cleanMem();
			return winner;
		}

		switch (currentState) {
		case moveSelect:
			moveSelectAction(selectedMove, input);
			break;
		case targetSelect:
			targetSelectAction(selectedTarget, input);
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

void BattleManager::DrawUI() {
	mvprintw(0, 0, std::string(209, '#').c_str());
	mvprintw(32, 0, std::string(209, '#').c_str());
	mvprintw(35, 0, std::string(209, '#').c_str());
	mvprintw(56, 0, std::string(209, '#').c_str());
	for (int i = 0;i <= 56;i++) {
		mvprintw(i, 0, "#");
		mvprintw(i, 209, "#");
	}
	for (int i = 35;i <= 56;i++) {
		mvprintw(i, 22, "#");
		mvprintw(i, 70, "#");
	}

	
}

void BattleManager::changeState(BattleState state){
	currentState = state;
}

bool BattleManager::isValidMove(int selectedMove)
{
	//here we will check if the entity has a move at that index
	//the programm will check if the pressed input is between 0 and the move count
	//for now hard coded to check if its 1
	return (selectedMove - '0' == 1);
}

bool BattleManager::isValidTarget(int selectedTarget)
{
	return (selectedTarget - '0' >= 1 && selectedTarget - '0' < totalEntities);
}

void BattleManager::moveSelectAction(int& selectedMove,int input){
	//heros turn
	if (currentTurn == 0) {
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
		selectedMove = '1';
		changeState(targetSelect);
	}
}

void BattleManager::targetSelectAction(int& selectedTarget,int input){
	//heros turn
	if (currentTurn == 0) {
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
		selectedTarget = '0';
		changeState(performSelectedMove);
	}
}

void BattleManager::performMoveAction(int selectedMove, int selectedTarget){
	performMove(selectedMove, selectedTarget);
	printMoveLog(selectedMove, selectedTarget);
	changeState(moveSelect);
}

void BattleManager::performMove(int selectedMove, int selectedTarget){
	int damage = entityList[currentTurn]->getAttack();
	int finalDamage = damage - entityList[selectedTarget - '0']->getDefence();
	if (finalDamage < 0) finalDamage = 0;
	entityList[selectedTarget - '0']->setHitPoints(entityList[selectedTarget - '0']->getHitPoints()-finalDamage);
}

void BattleManager::nextTurn(){
	currentTurn++;
	if (currentTurn >= totalEntities) {
		currentTurn = 0;
	}
}

int BattleManager::checkWinner(){
	if (entityList[0]->getHitPoints() <= 0) {
		printLog("Herro lost the battle (returning -1)");
		refresh();
		Sleep(5000);
		return -1;
	}
	bool endBattle = true;
	for (int i = 1;i < totalEntities;i++) {
		if (entityList[i]->getHitPoints() > 0) {
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

void BattleManager::cleanMem(){
	for (int i = 2;i < totalEntities;i++) {
		delete(entityList[i]);
	}
	totalEntities = 1;
	entityList = {};
	turnCounter = 0;
	currentTurn = 0;
	currentState = moveSelect;
}

void BattleManager::printLog(std::string strg) {
	mvprintw(33, 2, strg.c_str());
}

void BattleManager::printELog(std::string strg){
	mvprintw(34, 1, strg.c_str());
}

void BattleManager::printMoveLog(int selectedMove, int selectedTarget){
	int targetIndex = selectedTarget - '0';
	if (currentTurn == 0) {
		printLog("Hero hit enemy " + std::to_string(targetIndex) + " with normal attack");
	}
	else
	{
		printLog("Enemy hit hero with normal attack");
	}
	refresh();
}

void BattleManager::printHeroStats(){
	mvprintw(37, 3, "Hero:");
	mvprintw(38, 3, std::string(17, '-').c_str());
	mvprintw(39, 3, "Hp:");
	mvprintw(39, 12, "|%d/%d", entityList[0]->getHitPoints(), entityList[0]->getHealth());
	mvprintw(40, 3, "Attack:");
	mvprintw(40, 12, "|%d", entityList[0]->getAttack());
	mvprintw(41, 3, "Defence:");
	mvprintw(41, 12, "|%d", entityList[0]->getDefence());
}

void BattleManager::printHeroMoves(int selectedMove){
	mvprintw(37, 25, "Hero moves:");
	mvprintw(38, 25, std::string(43, '-').c_str());
	//this will comntain a for loop to print all the heros moves in a row
	//once moves are implementet
	if (selectedMove == '1') mvprintw(39, 24, ">");
	mvprintw(39, 25, "1: Normal Attack");
	mvprintw(39, 45, "|(accuracy 100%)");
	
}

void BattleManager::printEnemyStats(int selectedTarget){
	
	mvprintw(37, 73, "Enemy stats:");
	mvprintw(38, 73, std::string(43, '-').c_str());
	for (int i = 1;i < totalEntities;i++) {
		if(selectedTarget - '0' == i) mvprintw(39, 72 + ((i - 1) * 20), ">");
		mvprintw(39, 73 + ((i - 1) * 20), "Enemy %d", i);
		mvprintw(40, 73 + ((i - 1) * 20), "Hp:");
		mvprintw(40, 82 + ((i - 1) * 20), "|%d/%d", entityList[i]->getHitPoints(), entityList[i]->getHealth());
		mvprintw(41, 73 + ((i - 1) * 20), "Attack:");
		mvprintw(41, 82 + ((i - 1) * 20), "|%d", entityList[i]->getAttack());
		mvprintw(42, 73 + ((i - 1) * 20), "Defence:");
		mvprintw(42, 82 + ((i - 1) * 20), "|%d", entityList[i]->getDefence());
	}
	
}
