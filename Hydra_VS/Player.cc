#include <string>
#include <iostream>
#include "Game.h"
#include "Player.h"
#include "GameManager.h"
#include <algorithm>
#include <random>
using namespace std;


Player::Player(vector<string> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		this->drawPile.push_back(vec[i]);
	}
	this->reserve = "";
	this->playingCard = "";
	this->actionNumber = 1;
}

//Checks if all three conditions for a player to have won is met
bool Player::winCheck()
{
	if (drawPile.size() == 0 && discardPile.size() == 0 && reserve == "")
	{
		return true;
	}
	return false;
}

void Player::switchReserve()
{
	//check if reserve is empty, then place
	if (reserve == "")
	{
		reserve = playingCard;
		playingCard = "";
	}
	//if reserve has a card, then switch
	else
	{
		string temp = reserve;
		reserve = playingCard;
		playingCard = temp;
	}
}

//Returns reserve to discard pile at the end of a player's turn 
void Player::returnReserve()
{
	if (reserve != "")
	{
		discardPile.push_back(reserve);
		reserve = "";
	}
}

//Returns playing card to discard pile at the end of a player's turn
void Player::returnPlayingCard()
{
	if (playingCard != "")
	{
		discardPile.push_back(playingCard);
		playingCard = "";
	}
}

//Moves the oldest head into the player's discard pile when split
void Player::headToDiscardPile(vector<string> head)
{
	for (int i = 0; i < head.size(); i++)
	{
		if (head[i][head[i].size() - 1] == 'J')
		{
			head[i] = "joker";
		}
	}
	move(head.begin(), head.end(), back_inserter(discardPile));
}

//Draws a card, return false if not possible (last  card in reserve), otherwise true
bool Player::cardDraw()
{
	if (drawPile.size() == 0 && discardPile.size() == 0)
	{
		return false;
	}
	else if (drawPile.size() == 0)
	{
		shuffle(discardPile.begin(), discardPile.end(), random_device());
		move(discardPile.begin(), discardPile.end(), back_inserter(drawPile));
		discardPile.erase(discardPile.begin(), discardPile.end());
	}
	playingCard = drawPile[0];
	drawPile.erase(drawPile.begin());

	return true;
}

//Getter and setter methods
void Player::setJoker(string value)
{
	playingCard = value + "J";
}

string Player::getPlayingCard()
{
	return playingCard;
}
void Player::setPlayingCard(string card)
{
	playingCard = card;
}

string Player::getReserve()
{
	return reserve;
}
void Player::setReserve(string card)
{
	reserve = card;
}

int Player::getDrawPileSize()
{
	return drawPile.size();

}
int Player::getDiscardPileSize()
{
	return discardPile.size();
}

int Player::getActionNumber()
{
	return actionNumber;
}
void Player::setActionNumber(int number)
{
	actionNumber = number;
}




