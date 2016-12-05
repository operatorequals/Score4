

#ifndef AI_PLAYER
#define AI_PLAYER

#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "Player.h"

#include "../Board/Board.h"
#include "../GameInstance.h"


class GameInstance;


class AIPlayer : public Player{

	short NEXT_MOVE;

	unsigned short DEPTH, monteCarloGames;

	Player *MIN, *MAX ;

	void setDEPTH (short i)	{ DEPTH = i; }

	short minimax (Board &board, Player *min_max,short depth,short alpha, short beta);

	short minMove (Board &board, Player *min_max,short depth,short alpha, short beta);
	short maxMove (Board &board, Player *min_max,short depth,short alpha, short beta);

	std::vector<short> getAvailableMoves (Board &board);

	short evaluateBoard(GameInstance &gi);

	short monteCarloEvaluate(GameInstance &gi);

public:

	AIPlayer(std::string name, unsigned short i);


	const short chooseMove(GameInstance &gi);
};


#endif
