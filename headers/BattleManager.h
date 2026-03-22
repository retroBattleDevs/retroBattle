#pragma once
#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include "headers/Entity.h"
#include "TestEntity.h"
#include <vector>
#include <iostream>
#include <curses.h>
#include <Windows.h>
#include <string>

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
	BattleState currentState;
	std::vector<Entity*> entityList;
	void DrawUI();
	void printLog(std::string strg);
	void printELog(std::string strg);
	void printMoveLog(int selectedMove, int selectedTarget);
	void printHeroStats();
	void printHeroMoves(int selectedMove);
	void printEnemyStats(int selectedTarget);
	void changeState(BattleState state);
	bool isValidMove(int selectedMove);
	bool isValidTarget(int selectedTarget);
	void moveSelectAction(int& selectedMove,int input);
	void targetSelectAction(int& selectedTarget,int input);
	void performMoveAction(int selectedMove, int selectedTarget);
	void performMove(int selectedMove,int selectedTarget);
	void nextTurn();
	int checkWinner();
	void cleanMem();

public:
	BattleManager();
	int startBattle(Entity* hero, Entity* enemy, int enemyCount);
};
#endif