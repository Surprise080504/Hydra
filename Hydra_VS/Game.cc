#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "Game.h"
#include "Player.h"
#include "GameManager.h"
#include <memory>

using namespace std;

Game::Game()
{
	vector<string> head;
	this->heads.insert({ 1, head });
	this->houseRules = false;
}

//Adds a player to the player group 
void Game::addPlayer(shared_ptr<Player> player)
{
	this->playerGroup.push_back(move(player));
}

//Getter and setter methods
bool Game::getHouseRules()
{
	return houseRules;
}
void Game::setHouseRules(bool value)
{
	houseRules = value;
}

shared_ptr<Player> Game::getPlayer(int index)
{
	return playerGroup[index];
}
map<int, vector<string>>& Game::getHeads()
{
	return heads;
}
int Game::getNumberOfPlayers()
{
	return playerGroup.size();
}

//Helper function that converts card string to its numeric value, returns -1 if card value does not exist
int Game::cardValue(string card)
{
	if (card[0] == 'A')
	{
		return 1;
	}
	else if (card == "joker")
	{
		return 2;
	}
	else if (((int)card[0] - 48) > 1 && ((int)card[0] - 48) < 10)
	{
		return (int)card[0] - 48;
	}
	else if (card[0] == '1' && card[1] == '0')
	{
		return 10;
	}
	else if (card[0] == 'J')
	{
		return 11;
	}
	else if (card[0] == 'Q')
	{
		return 12;
	}
	else if (card[0] == 'K')
	{
		return 13;
	}
	else
	{
		return -1;
	}
}

//Returns true if it is possible for the player to play his card (with or without the house rules) 
bool Game::canPlay(string card)
{
	for (map<int, vector<string>>::iterator it = heads.begin(); it != heads.end(); ++it)
	{
		if (cardValue(card) <= cardValue(it->second[0]) || cardValue(it->second[0]) == 1
			|| (houseRules && card[card.size() - 1] == it->second[0][it->second[0].size() - 1]))
		{
			return true;
		}
	}
	return false;
}

void Game::attachPrintObservers(shared_ptr<PrintInterface> observerPrint)
{
	this->observerPrint.push_back(move(observerPrint));
}

//Prints before the game
void Game::printTurn(int roundCounter)
{
	for (int i = 0; i < observerPrint.size(); i++)
	{
		observerPrint[i]->printTurn(roundCounter);
	}

}

//Prints before every action
void Game::printGameAction(int playerNumber)
{
	for (int i = 0; i < observerPrint.size(); i++)
	{
		observerPrint[i]->printAction(playerNumber);
	}
}

//Prints everything else 
void Game::printGenericString(string printStr)
{
	for (int i = 0; i < observerPrint.size(); i++)
	{
		observerPrint[i]->printGenericString(printStr);
	}
}




