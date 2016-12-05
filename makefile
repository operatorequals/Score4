#/*------------------------------------------------------------------------
# *	Πρώτη εργασία στην Τεχνητή νοημοσύνη.
# *
# *		Τωράκης Ιωάννης 3110207
# *
# *		Βαβάκος Αλέξανδρος 3110019
# *
# *		Σκαρπέτης Χαράλαμπος 3110180
# *
# *///---------------------------------------------------------------------


GAME_NAME = Score4
VERSION = 1.12
V_CHANGE = AI_improvement-logs_time-makefile
#has to change for every version


CC = g++
DEBUG = -g
CFLAGS = -o
WX = `wx-config --libs` `wx-config --cxxflags`
EXE = Score4.exe


AI_F = AI_Interfaces
IO_F = IO_Interfaces
BOARD_F = Board



$(EXE) : Game.cpp Mechanics.o Mechanics.h
	$(CC) -o $(EXE) Game.cpp   \
Mechanics.o \
GameInstance.o \
LogInterface.o ConsoleInterface.o \
RandomPlayer.o AIPlayer.o Board.o


Board.o: $(BOARD_F)/Board.cpp $(BOARD_F)/Board.h $(BOARD_F)/Checker.h $(BOARD_F)/BoardPart.h
	$(CC) -c $(BOARD_F)/Board.cpp


Mechanics.o: Mechanics.cpp Mechanics.h GameInstance.o\
Board.o \
RandomPlayer.o AIPlayer.o \
ConsoleInterface.o LogInterface.o
	$(CC) -c Mechanics.cpp



RandomPlayer.o: $(AI_F)/RandomPlayer.h
	$(CC) -c $(AI_F)/RandomPlayer.cpp


AIPlayer.o: $(AI_F)/AIPlayer.h Board.o
	$(CC) -c $(AI_F)/AIPlayer.cpp


GameInstance.o: GameInstance.cpp GameInstance.h Board.o
	$(CC) -c GameInstance.cpp


ConsoleInterface.o: $(IO_F)/ConsoleInterface.cpp $(IO_F)/IOInterface.h $(IO_F)/ConsoleInterface.h
	$(CC) -c $(IO_F)/ConsoleInterface.cpp


LogInterface.o: $(IO_F)/LogInterface.cpp $(IO_F)/IOInterface.h
	$(CC) -c $(IO_F)/LogInterface.cpp




all : Game.cpp Mechanics.o Mechanics.h
	$(CC) -o $(EXE) Game.cpp \
Mechanics.o GameInstance.o \
LogInterface.o ConsoleInterface.o \
RandomPlayer.o AIPlayer.o Board.o; \
rm *.o



clean:
	rm *.o

zip:
	zip $(GAME_NAME)_$(VERSION)_$(V_CHANGE).zip Game.cpp Mechanics.cpp Mechanics.h GameInstance.cpp GameInstance.h \
$(IO_F)/IOInterface.h $(IO_F)/ConsoleInterface.h $(IO_F)/ConsoleInterface.cpp \
$(IO_F)/LogInterface.h $(IO_F)/LogInterface.cpp \
$(AI_F)/Player.h $(AI_F)/AIPlayer.h $(AI_F)/RandomPlayer.h $(AI_F)/AIPlayer.cpp $(AI_F)/RandomPlayer.cpp \
$(BOARD_F)/Checker.h $(BOARD_F)/Board.h $(BOARD_F)/BoardPart.h $(BOARD_F)/Board.cpp \
makefile \
logs/ Score4_Documentation.pdf
