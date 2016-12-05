

#ifndef _CONSOLE_INTERFACES_

#define _CONSOLE_INTERFACES_

#include <iostream>

#include "IOInterface.h"

class ConsoleOutputInterface : public OutputInterface{

public:
	const void splashScreen();

	const void playerPrompt(Player* pl);

	const void refreshTable(Board &board,Player *p1, Player *p2);

	void win_loss_conclusion(bool win, const Player* pl);

	void draw_conclusion();


};


//----------------------------------------------------------------------------------------------------------

class ConsoleInputInterface : public InputInterface{

public:
	const short getPlayersMove(Player *pl);

	const string getPlayersName(short i);

	const short getPlayerType(short i);

	const bool newGamePrompt();

};




#endif
