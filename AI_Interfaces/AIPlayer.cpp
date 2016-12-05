

#include "AIPlayer.h"

AIPlayer::AIPlayer(std::string name, unsigned short i) : Player("AIPlayer "+name, i){

	setDEPTH(i);	//we need to make some restriction like 0 < DEPTH < 5 for performance issues..

	srand((unsigned)time(NULL));		//for Monte Carlo random moves

	monteCarloGames = 2000 / i;		//normalizing the difficulty-time ratio
//	monteCarloGames = 1500;			//brute force
}


const short AIPlayer::chooseMove(GameInstance &gi){

	MAX = gi.current;
	MIN = gi.waiting;
	NEXT_MOVE = 3;		//rule of thumb move

	minimax(*gi.board, MAX, 1,-1000,1000);	//kai de simazeutai
	return NEXT_MOVE;
}



std::vector<short> AIPlayer::getAvailableMoves (Board &board){		 // η κατάλληλη σειρά κινήσεων 0-6:
									 // 3  2 4  1 5  0 6
	std::vector<short> availableMoves;

	short move = COLS/2;

	for (short i = 0; i < COLS; i++){

		if (i % 2 == 1)
			move = move + i;
		else
			move = move - i;

		if (board.checkMoveValidity(move))
			availableMoves.push_back(move);
	}
	return availableMoves;
}


short AIPlayer::evaluateBoard(GameInstance &gi){

	short score;
	if (gi.board->winConditionCheck(gi.waiting))
		score = 101;				//score 101 	insta-win
	else
		score = monteCarloEvaluate(gi);		//score 0-100
	return score;

}


short AIPlayer::minimax (Board &board,Player *min_max,short depth,short alpha, short beta){

	maxMove(board,min_max,depth,alpha,beta);
}


short AIPlayer::maxMove(Board &board,Player *min_max,short depth,short alpha, short beta){

	GameInstance gi = GameInstance(board,MAX,MIN);

	if (board.winConditionCheck(MIN))
		return -evaluateBoard(gi);

	else if (depth > DEPTH)
		return -evaluateBoard(gi);

	else if (board.isFull())
		return -evaluateBoard(gi);

	else{
		short bestScore = -1000;

		short nmove;
		short score;

		std::vector <short> avMoves = getAvailableMoves(board);
		short size = avMoves.size();

		for (short i = 0; i < size; i++){

			nmove = avMoves[i];

			board.move(nmove, MAX);

			score = minMove(board, MIN, (depth+1),alpha,beta);

			board.undoMove(nmove);

			if (bestScore < score){
				bestScore = score;
				alpha = score;
				if (depth == 1) NEXT_MOVE = nmove;	//NEXT_MOVE is class-field (not function-field)
			}

			if (alpha >= beta){
				alpha = score;
				return bestScore;
			}
		}

		return bestScore;
	}
}	


short AIPlayer::minMove(Board &board, Player *min_max, short depth,short alpha, short beta){


	GameInstance gi = GameInstance(board,MIN,MAX);

	if (board.winConditionCheck(MAX))
		return evaluateBoard(gi);

	else if (depth > DEPTH)
		return evaluateBoard(gi);

	else if (board.isFull())
		return evaluateBoard(gi);

	else{
		short bestScore = 1000;

		short nmove;
		short score;

		std::vector <short> avMoves = getAvailableMoves(board);
		short size = avMoves.size();

		for (short i = 0; i < size; i++){
			
			nmove = avMoves[i];

			board.move(nmove, MIN);

			score = maxMove(board, MAX, (depth+1),alpha,beta);

			board.undoMove(nmove);

			if (bestScore > score){
				bestScore = score;	
				beta = score;
			}

			if (alpha >= beta){
				beta = score;
				return bestScore;
			}
	
		}

		return bestScore;
	}
}


short AIPlayer::monteCarloEvaluate(GameInstance &gi){

	short numberOfGames = monteCarloGames;
	short numberOfWins = 0;
	short numberOfLosses = 0;
	short numberOfDraws = 0;

	Player* callingPlayer = gi.waiting;	

	for (int i = 0; i < numberOfGames; i++){

		gi.backup();
		while(!gi.board->isFull()){

			std::vector <short> avMoves = getAvailableMoves(*gi.board);
			short size = 1;
			size = avMoves.size();

			short move = 3;
			if (size)
				move = avMoves[ (rand() % size) ];	//random move

			gi.board->move(move,gi.current);

			if (gi.board->winConditionCheck (gi.current))
				if (callingPlayer == gi.current){
					numberOfWins++;
					break;
				}
				else{
					numberOfLosses++;
					break;
				}

			gi.swapPlayers();
		}
	}

	gi.backup();

	numberOfDraws = numberOfGames - numberOfWins - numberOfLosses;

	short score =  (((numberOfWins + numberOfDraws/2) * 100) / numberOfGames);//can be optimized

//numberOfGames guaranted not 0

//cout<<"Wins: "<<numberOfWins<<" - Losses: "<< numberOfLosses<<" - Draws: "<<numberOfGames - numberOfWins  - numberOfLosses<<" --- Percentage of Winning: "<< score<< endl;	//debugging purpose

	return score;
}

