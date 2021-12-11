#ifndef PRINTCONSOLE
#define PRINTCONSOLE

#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "PrintInterface.h"
#include "Game.h"

using namespace std;

class PrintConsole : public PrintInterface {
public:
	PrintConsole(shared_ptr<Game> &g);
	void printRound(int roundCounter);
	void printHeads();
	void printPlayers(int playerNumber);
	void printGenericString(string genString);
	void printTurn(int roundCounter);
	void printAction(int playerNumber);
};

#endif



