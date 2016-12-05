

#ifndef PLAYER
#define PLAYER
#include <string>

class GameInstance;

class Player{

public:

	std::string playerName;
	short isAI;	// negative is Randomer, 0 is Human, 1 is minimax depth 1, 2 is minimax depth 2 ...
	virtual const short chooseMove(GameInstance &gi) {}	//unused if player is human


	Player(std::string n,short AI){

		playerName=n;
		isAI=AI;
	}

	Player(Player& pl){

		playerName=pl.playerName;
		isAI=pl.isAI;
	}

	~Player(){

	}
};
#endif

