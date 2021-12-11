#ifndef PRINTINTERFACE
#define PRINTINTERFACE

#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Game.h"
using namespace std;
class Game;
class PrintInterface {

protected:

	weak_ptr<Game> currGame;
public:
	PrintInterface(shared_ptr<Game> &g);
	virtual void printRound(int roundCounter) = 0;
	virtual void printHeads() = 0;
	virtual void printPlayers(int playerNumber) = 0;
	virtual void printGenericString(string genString) = 0;
	virtual void printTurn(int roundCounter) = 0;
	virtual void printAction(int playerNumber) = 0;
};

#endif


