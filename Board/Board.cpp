
#include "Board.h"


bool Board::validNeighbour(short x, short y){		//board Initialization helper

	if ((x >= ROWS) || (x < 0))
		return false;

	if ((y >= COLS) || (y < 0))
		return false;

	return true;
}

void Board::initialize(){

	short downDiagX;
	short downDiagY;

	short rightX;
	short rightY;

	short upDiagX;
	short upDiagY;

	short upX;
	short upY;

	for (short j = COLS-1; j >= 0; j--){
		for (short i = ROWS-1; i >= 0; i--){

			board[i][j] = BoardPart();

			downDiagX = i-1;
			downDiagY = j+1;

			rightX = i;
			rightY = j+1;

			upDiagX = i+1;
			upDiagY = j+1;

			upX = i+1;
			upY = j;

			if (validNeighbour(downDiagX, downDiagY))
			board[i][j].downDiag = &board[downDiagX][downDiagY];				

			if (validNeighbour(rightX, rightY))
			board[i][j].right = &board[rightX][rightY];				

			if (validNeighbour(upDiagX, upDiagY))
			board[i][j].upDiag = &board[upDiagX][upDiagY];				

			if (validNeighbour(upX, upY))
			board[i][j].up = &board[upX][upY];				

		}
	}
}


bool Board::isFull(){

	short i = 0;
	while (COLS > i)
		if (board[ROWS-1][i++].occupiedBy == 0)	return false;

	return true;
}



bool Board::checkR(BoardPart* bp, const Player* pl, short count, short direction){

	if (count == 4)	return true;

	if (bp == 0)	return false;

	if ((bp->occupiedBy == 0) || (bp->occupiedBy->owner != pl))
		return false;
	

	if (direction == 0){

		if (checkR(bp->downDiag,pl,count+1, 1)) return true;

		if (checkR(bp->right,pl,count+1, 2)) return true;

		if (checkR(bp->upDiag,pl,count+1, 3)) return true;

		if (checkR(bp->up,pl,count+1, 4)) return true;
	}

	else if (direction == 1)	return checkR(bp->downDiag,pl,count+1,1);

	else if (direction == 2)	return checkR(bp->right,pl,count+1,2);

	else if (direction == 3)	return checkR(bp->upDiag,pl,count+1,3);

	else if (direction == 4)	return checkR(bp->up,pl,count+1,4);


	return false;
}

const bool Board::winConditionCheck(const Player* pl){

	short col = 0;
	short row = 0;

	for (col = 0; col < COLS; col++){

		row = 0;
		while ((row < ROWS) && (board[row][col].occupiedBy != 0)){
				
			if (board[row][col].occupiedBy->owner == pl){

				if (checkR(&board[row][col], pl, 0,0)) return true;
			}
			row++;
		}
	}

	return false;
}


const bool Board::checkMoveValidity(short move){

	if (move >= 0 && move <= COLS)

		if (board[ROWS-1][move].occupiedBy == 0){
			return true;	//if move is valid
		}
	return false;	//if stack is full
}


void Board::move(short col,const Player *pl){

	for (short i = 0; i < ROWS; i++){

		if (board[i][col].occupiedBy == 0){

			board[i][col].occupiedBy = new Checker(pl);
			return;
		}
	}
}


void Board::undoMove(short col){

	for (short i = ROWS-1; i >= 0; i--){

		if (board[i][col].occupiedBy != 0){

			delete 	board[i][col].occupiedBy;
			board[i][col].occupiedBy = 0;
			return;
		}
	}
}


void Board::clear(){

	for (short i = 0; i < ROWS; i++)
		for (short j = 0; j < COLS; j++){
			
			delete 	board[i][j].occupiedBy;
			board[i][j].occupiedBy = 0;

		}
}
