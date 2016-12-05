

#ifndef GAME_INSTANCE

#define GAME_INSTANCE


class GameInstance{

	short backupBoard[ROWS][COLS];

	Player *backupPlayer;

public:
	Board *board;

	Player *current, *waiting;

	short lastMove;


	void createBackup(Board &b);

	GameInstance(Board &b, Player *c, Player *w);

	GameInstance(Board &b, Player *c, Player *w, short lm);

	GameInstance(const GameInstance& gi);

	GameInstance& operator= (const GameInstance& gi);

	~GameInstance();


	void swapPlayers();

	void backup();
};

#endif
