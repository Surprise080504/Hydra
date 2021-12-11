#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include "Player.h"
#include "Game.h"
#include "GameManager.h"
#include "PrintInterface.h"
#include "PrintConsole.h"
#include <memory>

using namespace std;
const int NUM_SUIT = 4;
const int NUM_VALUE = 13;
const int NUM_JOKER = 2;
const int DECK_SIZE = NUM_SUIT * NUM_VALUE + NUM_JOKER;

int main(int argc, char* argv[]) {
	//Number of players
	int numPlayers = 0;
	while (numPlayers < 2)
	{
		cout << "How many players? (>1)" << endl;
		cin >> numPlayers;
		cout << endl;
	}

	//set up the deck 
	vector<string> deck;
	for (int i = 0; i < numPlayers; i++)
	{
		for (int s = 1; s <= NUM_SUIT; s++)
		{
			for (int v = 1; v <= NUM_VALUE; v++)
			{
				string suit = "";
				string value = "";

				if (s == 1)
				{
					suit = "D"; //"♦"
				}
				else if (s == 2)
				{
					suit = "S"; //"♠"
				}
				else if (s == 3)
				{
					suit = "C"; //"♣"
				}
				else
				{
					suit = "H"; //"♥"
				}


				if (v == 1)
				{
					value = "A";
				}
				else if (v == 11)
				{
					value = "J";
				}
				else if (v == 12)
				{
					value = "Q";
				}
				else if (v == 13)
				{
					value = "K";
				}
				else
				{
					value = to_string(v);
				}

				deck.push_back(value + suit);
			}
		}
		for (int j = 0; j < NUM_JOKER; j++)
		{
			deck.push_back("joker");
		}
	}
	shuffle(deck.begin(), deck.end(), random_device());

	//Testmode
	bool testing = (argc > 1 && string(argv[1]) == "-testing");
	int testDeckSize = 0;
	if (testing)
	{
		while (testDeckSize < 1 || testDeckSize > DECK_SIZE)
		{
			cout << "How many cards should each player have? (1-54)" << endl;
			cin >> testDeckSize;
			cout << endl;
		}
	}

	//Create game
	shared_ptr<Game> game(new GameManager(testing));

	//Set up the players
	for (int i = 0; i < numPlayers; i++)
	{
		vector<string> temp;
		if (testing)
		{
			move(deck.begin(), deck.begin() + testDeckSize, back_inserter(temp));
			deck.erase(deck.begin(), deck.begin() + testDeckSize);
		}
		else
		{
			move(deck.begin(), deck.begin() + DECK_SIZE, back_inserter(temp));
			deck.erase(deck.begin(), deck.begin() + DECK_SIZE);
		}
		shared_ptr<Player> player(new Player(temp));
		game->addPlayer(move(player));
	}

	//Set up observers
	shared_ptr<PrintInterface> printObserver(nullptr);
	printObserver = std::make_shared<PrintConsole>(game);
	game->attachPrintObservers(move(printObserver));

	//Begin and end game
	game->beginGame(testing);
	game->endGame();

}





