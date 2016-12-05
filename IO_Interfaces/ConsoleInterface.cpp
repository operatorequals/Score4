
#include "ConsoleInterface.h"


const void ConsoleOutputInterface::splashScreen(){

cout<<"*************************************************************"<<endl;
cout<<"*     ==       ==       ==     ===     =====           ==   *"<<endl;
cout<<"*   =    =   =    =   =    =   =   =   =             =  =   *"<<endl;
cout<<"*    =       =        =    =   =  =    =            =====   *"<<endl;
cout<<"*      =     =        =    =   = =     ===              =   *"<<endl;
cout<<"*   =    =   =    =   =    =   =  =    =                =   *"<<endl;
cout<<"*     ==       ==       ==     =   =   =====            =   *"<<endl;
cout<<"*                                                           *"<<endl;
cout<<"*************************************************************"<<endl;
cout<<endl<<endl;

}



const void ConsoleOutputInterface::playerPrompt(Player* pl){

	cout<<endl;
	cout<< "It is "<<pl->playerName<<"'s turn"<<endl;
}


void ConsoleOutputInterface::draw_conclusion(){

	cout << "The game is a Draw"<<endl;
}


void ConsoleOutputInterface::win_loss_conclusion(bool win, const Player* pl){

	if (win)
		cout<< "Player "<< pl->playerName <<" won the match"<<endl;
}


const void ConsoleOutputInterface::refreshTable(Board &board,Player *p1, Player *p2){

	cout<<endl;
	for (int i = ROWS-1; i >= 0; i--){
		
//-----------------------------------------------------------------
		cout<<"|";
		for (int j = 0; j <= COLS-1; j++) cout<<"     |";
		cout<<endl;
//-----------------------------------------------------------------


		cout<<"|";
		
		for (int j = 0; j <= COLS-1; j++){


			if (!board.get(i,j)->occupiedBy)

				cout<<"  -  |";


			else if (board.get(i,j)->occupiedBy->owner == p1)
				
				cout<<" (1) |";


			else if (board.get(i,j)->occupiedBy->owner == p2)
				
				cout<<" (2) |";
		}
		cout<<endl;
	}

	cout<<" ";
	for (int j = 0; j <= COLS-1; j++){
		cout<<"  "<<"^"<<"   ";
	}

	cout<<endl<<" ";
	for (int j = 0; j <= COLS-1; j++){
		cout<<"  "<<j+1<<"   ";
	}

	cout<<endl;

}

//=================================================================================================


const bool ConsoleInputInterface::newGamePrompt(){
	
	string answer;

	while(1){

		cout<<"Want to play a new game? [yes/no]"<<endl;

		cin >> answer;
			
		if (!answer.compare("yes")) return true;

		if (!answer.compare("no")) return false;
	}
	
}


const short ConsoleInputInterface::getPlayersMove(Player *pl){

	cout<<endl;
	cout<< "Choose column [1-"<<COLS<<"]: ";
	int i;
	cin >> i;
	return i-1;
}


const string ConsoleInputInterface::getPlayersName(short i){

	if ((i == 1) || (i == 2))
		cout<<"Set Player "<<i<<" name: ";
	string name;
	cin >> name;
	return name;
}


const short ConsoleInputInterface::getPlayerType(short i){

	string type = "";
	short typen = 0;


	while (true){
		cout<<"Set Player "<<i<<" type"<<endl<< "[Random, Human, AIx x>0 is minimax depth]"<<endl;
		cin >> type;

		if (!type.compare("Human")){
			typen = 0;
			break;
		}

		if (!type.compare("Random")){
			typen = -1;
			break;
		}

		if (type.length() > 2)
		if ((type[0]=='A') && (type[1]=='I')){
			int AId = type[2] - '0';
			if (AId <= 0)
				continue;
			else{
				typen = AId;
				break;
			}
		}
	}
	return typen;

}


