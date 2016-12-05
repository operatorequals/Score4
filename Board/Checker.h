

class Player;

#ifndef CHECKER
#define CHECKER

class Checker{

	public:
	const Player *owner;

	Checker(const Player *pl){
		owner = pl;
	}

	Checker(Checker& c){
		owner = c.owner;
	}

};

#endif

