
#ifndef _IO_INTERFACES_

#define _IO_INTERFACES_

#include <string>

#include "../Board/Board.h"
#include "../AI_Interfaces/Player.h"

using namespace std;

class InputInterface{

public:

virtual const string getPlayersName(short player){}

virtual const short getPlayerType(short player){}

virtual const bool newGamePrompt(){};

virtual const short getPlayersMove(Player *pl){};

virtual ~InputInterface(){}
};



class OutputInterface{

public:


virtual const void splashScreen(){};

virtual const void playerPrompt(Player* pl){};

virtual const void refreshTable(Board &board,Player *p1, Player *p2){};

virtual const void moveAnimation(short move, Player *pl){};

virtual void win_loss_conclusion(bool win, const Player* pl){};

virtual void draw_conclusion(){};

virtual ~OutputInterface(){}

};


#endif
