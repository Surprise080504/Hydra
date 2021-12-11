#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include "Game.h"
#include "GameManager.h"
#include "PrintInterface.h"

class Game;
PrintInterface::PrintInterface(shared_ptr<Game> &g)
{
	currGame = g;
}




