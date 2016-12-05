

#ifndef _MECHANICS_

#define _MECHANICS_

#include "Board/Board.h"

#include "GameInstance.h"

#include "IO_Interfaces/IOInterface.h"
#include "IO_Interfaces/ConsoleInterface.h"
#include "IO_Interfaces/LogInterface.h"

#include "AI_Interfaces/Player.h"
#include "AI_Interfaces/AIPlayer.h"
#include "AI_Interfaces/RandomPlayer.h"


class Mechanics{

private:

	long time;

	InputInterface *ii;
	OutputInterface *oi;

	Player *p1,*p2;


	void changeCurrentPlayer();

	Player* decideStart(short game);

	void initPlayers();

public:
	Board board;

	Player *currentPlayer;


	Mechanics(short interType);

	Mechanics(Mechanics &m);

	void gameLoop();

	GameInstance exportGameInstance();
};


#endif
