#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include <memory>
#include "Game.h"
#include "GameManager.h"
#include "PrintConsole.h"
using namespace std;

PrintConsole::PrintConsole(shared_ptr<Game> &g) : PrintInterface(g)
{

}

//Print at the beginning of a turn
void PrintConsole::printTurn(int roundCounter)
{
	printRound(roundCounter);
	printHeads();
	printPlayers(0);
}

//Print round
void PrintConsole::printRound(int roundCounter)
{
	cout << endl << endl << "Round " << roundCounter << ":" << endl;
}

//Print heads
void PrintConsole::printHeads()
{
	cout << "Heads:" << endl;
	for (map<int, vector<string>>::iterator it = shared_ptr<Game>(currGame)->getHeads().begin(); it != shared_ptr<Game>(currGame)->getHeads().end(); ++it)
	{
		cout << it->first << ": ";
		cout << it->second[0] << " ";
		cout << "(" << it->second.size() << ")" << endl;
	}
	cout << endl;
}

//Print players (considering both case of in a player's turn or at the start of a round)
void PrintConsole::printPlayers(int playerNumber)
{
	cout << "Players:" << endl;
	for (int i = 0; i < shared_ptr<Game>(currGame)->getNumberOfPlayers(); i++)
	{
		cout << "Player " << i + 1 << ": " << shared_ptr<Game>(currGame)->getPlayer(i)->getDrawPileSize() + shared_ptr<Game>(currGame)->getPlayer(i)->getDiscardPileSize();
		cout << " (" << shared_ptr<Game>(currGame)->getPlayer(i)->getDrawPileSize() << " draw, " << shared_ptr<Game>(currGame)->getPlayer(i)->getDiscardPileSize() << " discard)";

		if (playerNumber > 0 && shared_ptr<Game>(currGame)->getPlayer(i) == shared_ptr<Game>(currGame)->getPlayer(playerNumber - 1))
		{
			cout << " + 1 in hand, " << shared_ptr<Game>(currGame)->getPlayer(i)->getActionNumber() << " remaining, ";
			if (shared_ptr<Game>(currGame)->getPlayer(i)->getReserve() == "")
			{
				cout << 0;
			}
			else
			{
				cout << 1;
			}
			cout << " in reserve" << endl;
		}
		else
		{
			cout << endl;
		}
	}
	cout << endl;

}

//Prints any other message not handled by a previous function
void PrintConsole::printGenericString(string genString)
{
	cout << genString;
}

//Called at the start of each action
void PrintConsole::printAction(int playerNumber)
{
	printHeads();
	printPlayers(playerNumber);
}











