
#include <string>
#include "Mechanics.h"


using namespace std;

int main(int argc, char **argv){

Mechanics* mech;

if (argc > 1){

	if (string(argv[1]) == "-log")
		mech = new Mechanics(-1);	//keep a game log at /logs while playing normally
}

else
	mech = new Mechanics(0);
//0 is Console, 1 is Widget Graphics, 2 is OpenGL Graphics

mech->gameLoop();
}
