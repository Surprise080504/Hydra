#ifndef GAME
#define GAME

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "Player.h"
#include <memory>
#include "PrintInterface.h"
using namespace std;


class Game {

protected:
	map<int, vector<string>> heads;
	vector<shared_ptr<Player>> playerGroup;
	vector<shared_ptr<PrintInterface>> observerPrint;
	bool houseRules;

public:
	Game();
	void attachPrintObservers(shared_ptr<PrintInterface> observerPrint);
	void addPlayer(shared_ptr<Player> player);
	bool getHouseRules();
	void setHouseRules(bool value);
	virtual void beginGame(bool testing) = 0;
	virtual void endGame() = 0;
	int cardValue(string card);
	bool canPlay(string card);
	void printTurn(int roundCounter);
	void printGenericString(string printStr);
	void printGameAction(int playerNumber);
	shared_ptr<Player> getPlayer(int index);
	map<int, vector<string>>& getHeads();
	int getNumberOfPlayers();
};

#endif




