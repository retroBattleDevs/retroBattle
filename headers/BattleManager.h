#pragma once
#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include "headers/Entity.h"
#include <vector>
#include <iostream>
#include <curses.h>
#include <Windows.h>
#include <string>
#include <algorithm>
#include "headers/SubMoves.h";

enum BattleState {
	moveSelect,
	targetSelect,
	performSelectedMove,
};

class BattleManager {
private:
	int turnCounter;
	int totalEntities;
	int currentTurn;
	int roundCounter;
	BattleState currentState;
	std::vector<Entity*> entityList;
	std::vector<BattleMove*> availableMoves;
	//order index mapping
	std::vector<int> turnOrder;

	//prints
	void DrawUI(int selectedMove, int selectedTarget);
	void printLog(std::string strg);
	void printELog(std::string strg);
	void printHeroStats();
	void printHeroMoves(int selectedMove);
	void printEnemyStats(int selectedTarget);
	void drawBackGround(int y, int x);
	void drawEnemy(int y,int x);
	void drawHero(int y, int x);
	std::string getShortType(MoveCategory cat);

	//checkers and actions
	void changeState(BattleState state);
	void calculateTurnOrder();
	void moveSelectAction(int& selectedMove,int input);
	void targetSelectAction(int& selectedMove, int& selectedTarget, int input);
	void performMoveAction(int selectedMove, int selectedTarget);
	void performMove(int selectedMove,int selectedTarget);
	void nextTurn();
	int checkWinner();
	bool isHerosTurn() const;
	void resetForNextBattle();

public:
	BattleManager();
	int startBattle(Entity* hero, Entity* enemy, int enemyCount);
};
#endif