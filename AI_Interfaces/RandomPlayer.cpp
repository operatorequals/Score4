

#include "RandomPlayer.h"


RandomPlayer::RandomPlayer(std::string name) : Player("RandomPlayer "+name, -1){
	srand((unsigned)time(NULL));
}

const short RandomPlayer::chooseMove(GameInstance &gi){
	return ((rand() % COLS) );
}

