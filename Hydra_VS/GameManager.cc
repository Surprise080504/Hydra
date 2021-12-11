#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include "Game.h"
#include "Player.h"
#include "GameManager.h"


using namespace std;

const int SPLIT_HEAD_NUM = 2;
const int STARTING_PLAYER_NUM = 1;

GameManager::GameManager(bool test)
{
	this->playerNumber = STARTING_PLAYER_NUM;
	this->testingModeOn = test;
	this->roundCounter = 0;
}

void GameManager::beginGame(bool testing)
{
	//House rules set up
	printGenericString("In this version of house rules, you are also allowed to place a card if it has a suit that matches the top card of the head\n");
	evaluateHouseRules();

	//First card set up
	roundCounter++;
	map<int, vector<string>>::iterator it = heads.begin();
	playerGroup[playerNumber - 1]->cardDraw();
	if (testing)
	{
		testingMode();
	}
	it->second.push_back(playerGroup[playerNumber - 1]->getPlayingCard());
	endTurn();
	printTurn(roundCounter);

	//Begins the next player's turn until the win conditions are met
	while (!playerGroup[playerNumber - 1]->winCheck())
	{
		beginTurn();
	}
}

//Ends the game
void GameManager::endGame()
{
	printGenericString("Player " + to_string(playerNumber) + " wins!\n");

	string key = "";
	while (key != "q")
	{
		printGenericString("Press q to quit the game\n");
		cin >> key;
	}
}

//Prints the top card of a head 
string GameManager::topCard(int headNum)
{
	return heads[headNum][0];
}


//Corrects the player number for the new turn, prints and calls the action manager
void GameManager::beginTurn()
{
	if (playerNumber < playerGroup.size())
	{
		playerNumber++;
	}
	//New round starts 
	else
	{
		playerNumber = 1;
		evaluateHouseRules();
		roundCounter++;
		printTurn(roundCounter);
	}
	printGenericString("Player " + to_string(playerNumber) + ", it is your turn.\n");
	playerGroup[playerNumber - 1]->setActionNumber(heads.size());
	actionManager();
}

//Draws a card, by calling player's card draw 
void GameManager::cardDraw()
{
	playerGroup[playerNumber - 1]->setActionNumber(playerGroup[playerNumber - 1]->getActionNumber() - 1);
	if (!playerGroup[playerNumber - 1]->cardDraw())
	{
		//Last card is in reserve
		playerGroup[playerNumber - 1]->setActionNumber(0);
		playerGroup[playerNumber - 1]->setPlayingCard("");
	}
}

//Allows user to set the value and suit of the card in hand (playingCard)
void GameManager::testingMode()
{
	string value = "";
	string suit = "";

	printGenericString("Card value?\n");
	cin >> value;
	if (cardValue(value) != -1)
	{
		//Does not ask for suit if value is joker
		if (value != "joker")
		{
			printGenericString("Suit?\n");
			cin >> suit;
			if (suit != "H" && suit != "D" && suit != "S" && suit != "C")
			{
				printGenericString("Invalid suit.\n\n");
				testingMode();
			}
			else
			{
				playerGroup[playerNumber - 1]->setPlayingCard(value + suit);
			}
		}
		else
		{
			playerGroup[playerNumber - 1]->setPlayingCard(value);
		}
	}
	else
	{
		printGenericString("Invalid suit.\n\n");
		testingMode();
	}

}

//Manages the process of completing an action
void GameManager::actionManager()
{
	bool draw = true;
	//Repeats action while player has not won, still has some remianing or still has a card in hand
	while (!playerGroup[playerNumber - 1]->winCheck()
		&& ((playerGroup[playerNumber - 1]->getActionNumber() > 0) || (playerGroup[playerNumber - 1]->getActionNumber() == 0 && playerGroup[playerNumber - 1]->getPlayingCard() != "")))
	{

		//Draw card to start action
		if (draw)
		{
			cardDraw();
		}

		//Case where last card is in reserve playing card will be empty after cardDraw()
		if (playerGroup[playerNumber - 1]->getPlayingCard() == "")
		{
			break;
		}

		//Prints game situation and allows user to set card in hand if testing is on
		printGameAction(playerNumber);
		if (draw && testingModeOn)
		{
			testingMode();
		}

		draw = true;

		printGenericString("Player " + to_string(playerNumber) + " you are holding a");
		//Grammer bonus 
		if (playerGroup[playerNumber - 1]->getPlayingCard()[0] == '8' || playerGroup[playerNumber - 1]->getPlayingCard()[0] == 'A')
		{
			printGenericString("n");
		}
		printGenericString(" " + playerGroup[playerNumber - 1]->getPlayingCard() + ". Your move?\n");

		//Recieves command from user after having a card in hand and printing the situation
		int command;
		cin >> command;
		printGenericString("\n");

		//Reserve
		if (command == 0)
		{
			if (playerGroup[playerNumber - 1]->getReserve() == "")
			{
				draw = true;
			}
			else
			{
				draw = false;
			}
			playerGroup[playerNumber - 1]->switchReserve();
		}
		//Checks that the command is one of the existing heads
		else if (heads.find(command) != heads.end()) 
		{
			//Case where given a joker
			if (playerGroup[playerNumber - 1]->getPlayingCard() == "joker")
			{
				string jokerValue;
				printGenericString("Joker value? \n");
				cin >> jokerValue;
				if (cardValue(jokerValue) != -1)
				{
					playerGroup[playerNumber - 1]->setJoker(jokerValue);
					draw = true;
				}
				else
				{
					draw = false;
				}
			}
			if (draw)
			{
				//Case where player can not play this card (Checks that player choose a bad value for joker as well)
				if (!canPlay(playerGroup[playerNumber - 1]->getPlayingCard())
					&& playerGroup[playerNumber - 1]->getPlayingCard()[playerGroup[playerNumber - 1]->getPlayingCard().size() - 1] != 'J')
				{
					headSplit();
				}
				//Case where it is possible to play, however not on chosen head
				else if (((cardValue(topCard(command)) != 1) && (cardValue(playerGroup[playerNumber - 1]->getPlayingCard()) > cardValue(topCard(command))))
					&& (!houseRules || playerGroup[playerNumber - 1]->getPlayingCard()[playerGroup[playerNumber - 1]->getPlayingCard().size() - 1] != topCard(command)[topCard(command).size() - 1]))
				{
					printGenericString("Invalid command. \n");
					draw = false;
					if (playerGroup[playerNumber - 1]->getPlayingCard()[playerGroup[playerNumber - 1]->getPlayingCard().size() - 1] == 'J')
					{
						playerGroup[playerNumber - 1]->setPlayingCard("joker");
					}
				}
				//Case where is is possible to play on chosen head
				else
				{
					placeCard(command);
				}
			}
		}
		else
		{
			printGenericString("Invalid command. \n");
			draw = false;
		}
	}
	endTurn();
}

//Places card on top of head pile, sets action number to 0 if card placed matches the top card  
void GameManager::placeCard(int headNum)
{
	if (cardValue(playerGroup[playerNumber - 1]->getPlayingCard()) == cardValue(topCard(headNum)))
	{
		playerGroup[playerNumber - 1]->setActionNumber(0);
	}
	map<int, vector<string>>::iterator it = heads.find(headNum);
	it->second.insert(it->second.begin(), playerGroup[playerNumber - 1]->getPlayingCard());
	playerGroup[playerNumber - 1]->setPlayingCard("");
}

//Splits head so moves oldest head to discard pile, draws and places two cards as new heads, also sets action number to 0
void GameManager::headSplit()
{
	map<int, vector<string>>::iterator it = heads.begin();

	playerGroup[playerNumber - 1]->headToDiscardPile(it->second);
	playerGroup[playerNumber - 1]->returnReserve();
	playerGroup[playerNumber - 1]->returnPlayingCard();
	for (int i = 0; i < SPLIT_HEAD_NUM; i++)
	{
		cardDraw();
		if (testingModeOn)
		{
			testingMode();
		}
		vector<string> temp;
		temp.push_back(playerGroup[playerNumber - 1]->getPlayingCard());
		heads.insert({ heads.rbegin()->first + 1 , temp });
	}
	heads.erase(it->first);
	playerGroup[playerNumber - 1]->setActionNumber(0);
	playerGroup[playerNumber - 1]->setPlayingCard("");
}

//Resets playingCard and reserve at the end of each turn 
void GameManager::endTurn()
{
	playerGroup[playerNumber - 1]->setPlayingCard("");
	playerGroup[playerNumber - 1]->returnReserve();
}

//Asks if you would like the house rules on for the coming round (allowing you to dynamically change it)
void GameManager::evaluateHouseRules()
{
	string command;
	printGenericString("Type 'Yes' if you would like to turn on/continue to use house rules for the upcoming round.\n");
	cin >> command;
	if (command == "Yes" || command == "yes")
	{
		setHouseRules(true);
	}
	else
	{
		setHouseRules(false);
	}
}



