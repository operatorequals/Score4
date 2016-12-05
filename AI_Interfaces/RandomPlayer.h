

#ifndef RANDOM_PLAYER
#define RANDOM_PLAYER

#include "Player.h"
#include <string>
#include <ctime>
#include <cstdlib>

#include "../Board/Board.h"

class RandomPlayer : public Player{

public:

	RandomPlayer(std::string name) ;

	const short chooseMove(GameInstance &gi);
};

#endif
