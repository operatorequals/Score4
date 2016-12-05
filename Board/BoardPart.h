

#ifndef BOARD_PART
#define BOARD_PART

#include "Checker.h"

class BoardPart{

public:
	Checker *occupiedBy ;
	BoardPart *up, *right, *downDiag, *upDiag;


	BoardPart(){

		init(0,0,0,0);
	}


	BoardPart(BoardPart *dd, BoardPart *r, BoardPart *ud, BoardPart *u){

		init(dd,r,ud,u);
	}

	BoardPart(BoardPart &bp){

		occupiedBy = bp.occupiedBy;
		up = bp.up;
		right = bp.right;
		downDiag = bp.downDiag;
		upDiag = bp.upDiag;
	}

	~BoardPart(){
		if (occupiedBy)	delete occupiedBy;
		if (up)	delete up;
		if (right) delete right;
		if (upDiag) delete upDiag;
		if (downDiag) delete downDiag;
	}

private:
	void init(BoardPart *dd, BoardPart *r, BoardPart *ud, BoardPart *u){

		occupiedBy = 0;
		up = u;
		right = r;
		downDiag = dd;
		upDiag = ud;
	}
};


#endif

