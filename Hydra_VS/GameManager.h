#ifndef GAMEMANAGER
#define GAMEMANAGER

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "Player.h"
#include "Game.h"
#include <memory>

using namespace std;

class GameManager : public Game {

private:
	long playerNumber;
	int roundCounter;
	bool testingModeOn;

public:
	GameManager(bool test);
	void testingMode();
	void beginGame(bool test);
	void beginTurn();
	void cardDraw();
	void actionManager(); 
	void placeCard(int headNum);
	void headSplit();
	void endTurn();
	void endGame();
	string topCard(int headNum);
	void evaluateHouseRules();
};

#endif



