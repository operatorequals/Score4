
#include "LogInterface.h"

LogOutputInterface::LogOutputInterface(OutputInterface *con){

	playerFlag = 1;
	matchFlag = 1;

	console = con;

	string timeS = currentDateTime();
	gameLog.open(("logs/__gamelog__"+timeS+".s4.xml").c_str());
	gameLog<<"<GameCollection>"<<endl;
}


LogOutputInterface::~LogOutputInterface(){

	gameLog<<"</GameCollection>"<<endl;
	delete console;
	gameLog.close();
}


const void LogOutputInterface::splashScreen(){

	console->splashScreen();
}


const void LogOutputInterface::refreshTable(Board &board,Player *p1, Player *p2){

	console->refreshTable(board,p1,p2);

	if (matchFlag){
		matchFlag = 0;
		seconds = time(0);
	}

	if (playerFlag){
		cp1 = p1;
		cp2 = p2;
		gameLog	<< "< p1type = \""<<cp1->isAI<<"\" "
			<< "p2type = \""<<cp2->isAI<<"\" "
			<<">"<<endl<<endl;
		playerFlag = 0;
	}
}


void LogOutputInterface::win_loss_conclusion(bool win, const Player* pl){

	seconds = getSecondsAndReset(seconds);

	if (pl == cp1){
		gameLog<<"<game = \"1,0\" seconds = \""<<seconds<<"\" >"<<endl;	//xml format

		gameLog<<"<!--"<<endl;

		gameLog<< "Player "<< cp1->playerName <<" of type: "<< cp1->isAI <<" won"<<endl;
		gameLog<< "Player "<< cp2->playerName <<" of type: "<< cp2->isAI <<" lost"<<endl;

		gameLog<<"-->"<<endl;
	}
	else{
		gameLog<<"<game = \"0,1\" seconds = \""<<seconds<<"\" >"<<endl;	//xml format

		gameLog<<"<!--"<<endl;

		gameLog<< "Player "<< cp1->playerName <<" of type: "<< cp1->isAI <<" lost"<<endl;
		gameLog<< "Player "<< cp2->playerName <<" of type: "<< cp2->isAI <<" won"<<endl;

		gameLog<<"-->"<<endl;

	}

	gameLog<<"</game>"<<endl<<endl<<endl;

	console->win_loss_conclusion(win,pl);	//regular consoleOutput

}


void LogOutputInterface::draw_conclusion(){

	seconds = getSecondsAndReset(seconds);

	gameLog<<"<game = \"0.5,0,5\" seconds = \""<<seconds<<"\" >";	//xml format

	gameLog<<"<!--"<<endl;
	gameLog << "The game between "<<endl<< "Player "<< cp1->playerName <<" of type: "<< cp1->isAI;
	gameLog << "and "<<endl<< "Player "<< cp2->playerName <<" of type: "<< cp2->isAI<<endl;
	gameLog << " is a Draw"<<endl;
	gameLog<<"-->"<<endl;

	gameLog<<"</game>"<<endl<<endl<<endl;

	console->draw_conclusion();

}

