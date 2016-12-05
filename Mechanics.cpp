

#include "Mechanics.h"


Mechanics::Mechanics (short interType){

	if (interType < 0){
		ii = new ConsoleInputInterface();
		oi = new LogOutputInterface(new ConsoleOutputInterface());
	}
	else if (interType == 0){
		ii = new ConsoleInputInterface();
		oi = new ConsoleOutputInterface();
	}
	else if (interType == 1){

//		ii = new wxWidgetsInputInterface();		not implemented yet
//		oi = new wxWidgetsOutputInterface();

	}
	else if (interType == 2){

	}

	oi->splashScreen();
	initPlayers();

}


void Mechanics::initPlayers(){

short p1AI = 0;
short p2AI = 1;

string p1n = "";
string p2n = "";
	p1AI = ii->getPlayerType(1);
	p2AI = ii->getPlayerType(2);


	if (!p1AI)
		p1n = ii->getPlayersName(1);
	if (!p2AI)
		p2n = ii->getPlayersName(2);


	if (p1n.empty())
		p1n = "p1";

	if (p2n.empty())
		p2n = "p2";


	if (p1AI < 0)
		p1 = new RandomPlayer(p1n);
	else if (p1AI > 0)
		p1 = new AIPlayer(p1n , p1AI);
	else
		p1 = new Player(p1n,p1AI);

	if (p2AI < 0)
		p2 = new RandomPlayer(p2n);
	else if (p2AI > 0)
		p2 = new AIPlayer(p2n, p2AI);
	else
		p2 = new Player(p2n,p2AI);
}


Player* Mechanics::decideStart(short game){

	if (game % 2 == 1)
		return p1; // <--Each player plays 1st every second game
	else
		return p2;
}


void Mechanics::changeCurrentPlayer(){

	if (currentPlayer == p1)
		currentPlayer = p2;

	else if (currentPlayer == p2)
		currentPlayer = p1;
}


GameInstance Mechanics::exportGameInstance(){

	if (currentPlayer == p1)
		return GameInstance(board,currentPlayer,p2);
	else
		return GameInstance(board,currentPlayer,p1);
}


void Mechanics::gameLoop(){

	bool newGame = true;
	int gameCounter = 0;

	while(newGame){

		short choice = 0;
		short turn;
		gameCounter++;

		currentPlayer = decideStart(gameCounter);
		board.clear();
		oi->refreshTable(board, p1,p2); 


		for (turn = 1; turn <= ROWS*COLS; turn++){

			oi->playerPrompt(currentPlayer);

			do{
				if (currentPlayer->isAI == 0)
					choice = ii->getPlayersMove(currentPlayer);
				else{
					GameInstance gi = exportGameInstance();
					choice = currentPlayer->chooseMove(gi);		// AI's movement
				}

			} while (!(board.checkMoveValidity(choice)));	//breaks when move is valid--> when condition is >0

			board.move(choice,currentPlayer);

			oi->moveAnimation(choice,currentPlayer);

			oi->refreshTable(board, p1,p2); 

			if (board.winConditionCheck(currentPlayer))
				break;

			changeCurrentPlayer();
		}

		if (turn > ROWS*COLS)		//draw
			oi->draw_conclusion();
		else
			oi->win_loss_conclusion(true,currentPlayer);


		newGame = ii->newGamePrompt();
	}

		delete ii;
		delete oi;
						// GAME ENDS HERE
}

