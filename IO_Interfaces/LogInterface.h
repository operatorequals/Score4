

#include <fstream>
#include <string>
#include <stdio.h>
#include <time.h>

#include "IOInterface.h"


class LogOutputInterface : public OutputInterface{

	OutputInterface *console;
	std::ofstream gameLog;
	Player *cp1,*cp2;
	bool matchFlag, playerFlag;
	long seconds;


	long getSecondsAndReset(long s){

		matchFlag = 1;
		return (time(0) - s);
	}


	//StackOverflow sample <
	const std::string currentDateTime() {

		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

		return buf;
	}
	//>

public:

	LogOutputInterface(OutputInterface *con);

	~LogOutputInterface();

	const void splashScreen();

	const void refreshTable(Board &board,Player *p1, Player *p2);

	void win_loss_conclusion(bool win, const Player* pl);

	void draw_conclusion();


};


