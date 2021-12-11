#ifndef PLAYER
#define PLAYER

#include <string>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Player {

private:
	int actionNumber;
	string playingCard;
	string reserve;
	vector<string> drawPile;
	vector<string> discardPile;

public:
	Player(vector<string> vect);
	bool winCheck();
	bool cardDraw();
	void switchReserve();
	void returnPlayingCard();
	void returnReserve();
	void headToDiscardPile(vector<string> head);
	void setJoker(string value);
	string getPlayingCard();
	void setPlayingCard(string card);
	string getReserve();
	void setReserve(string card);
	int getActionNumber();
	void setActionNumber(int actionNumber);
	int getDrawPileSize();
	int getDiscardPileSize();
	


};
#endif


