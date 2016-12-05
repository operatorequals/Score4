

#ifndef BOARD
#define BOARD

#include "BoardPart.h"


//#define GAMEMODE_8x8

#define GAMEMODE_6x7

#ifdef GAMEMODE_6x7
#define ROWS 6	//rows = 6
#define COLS 7	//cols = 7
#endif


#ifdef GAMEMODE_8x8
#define ROWS 8	//rows = 8
#define COLS 8	//cols = 8
#endif



class Board{

	BoardPart board[ROWS][COLS];

	bool validNeighbour(short x, short y);		//board Initialization helper

	bool checkR(BoardPart* bp, const Player* pl, short count, short direction);


public:
	void initialize();

	const bool winConditionCheck(const Player* pl);

	const bool checkMoveValidity(short move);

	void move(short col,const Player *pl);

	void undoMove(short col);

	bool isFull();

	void clear();

	Board(){
		initialize();
	}

	Board(Board& b){
		initialize();
		for (short i = ROWS-1; i >= 0; i++)
			for (short j = COLS-1; j >= 0; j++)
				board[i][i].occupiedBy = b.get(i,j)->occupiedBy;
	}

	~Board(){
		for (short i = ROWS-1; i >= 0; i++)
			for (short j = COLS-1; j >= 0; j++)
				delete &board[i][j];
	}

	inline BoardPart* get(short row, short col) {return &board[row][col];}
};


#endif
