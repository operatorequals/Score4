

#include "Board/Checker.h"

#include "Board/Board.h"

#include "GameInstance.h"


void GameInstance::createBackup(Board &b){

	backupPlayer = current;

	for (short i = 0; i < ROWS; i++)
		for (short j = 0; j < COLS; j++){

			if (board->get(i,j)->occupiedBy == 0)
				backupBoard[i][j] = 0;

			else if (board->get(i,j)->occupiedBy->owner == current)
				backupBoard[i][j] = 1;

			else if (board->get(i,j)->occupiedBy->owner == waiting)
				backupBoard[i][j] = 2;
		}
}


GameInstance::GameInstance(Board &b, Player *c, Player *w){

	board = &b;
	current = c;
	waiting = w;

	createBackup(*board);
}


GameInstance::GameInstance(Board &b, Player *c, Player *w, short lm){

	board = &b;
	current = c;
	waiting = w;
	lastMove = lm;

	createBackup(*board);
}


GameInstance::GameInstance(const GameInstance& gi){

	board = gi.board;
	current = gi.current;
	waiting = gi.waiting;
	lastMove = gi.lastMove;

	createBackup(*board);
}


GameInstance& GameInstance::operator= (const GameInstance& gi){

	if (this == &gi) return *this;

	board = gi.board;
	current = gi.current;
	waiting = gi.waiting;

	createBackup(*board);

	return *this;
}


GameInstance::~GameInstance(){


}

void GameInstance::swapPlayers(){
	Player* temp = current; current = waiting; waiting = temp;
}


void GameInstance::backup(){

	board->clear();

	if (backupPlayer != current)
		swapPlayers();	
	
	for (short i = 0; i < ROWS; i++)
		for (short j = 0; j < COLS; j++)

			if (backupBoard[i][j] == 1)
				board->move(j,current);

			else if (backupBoard[i][j] == 2)
				board->move(j,waiting);

}

