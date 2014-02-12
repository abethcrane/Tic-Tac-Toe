CC = gcc
CFLAGS = -Wall -Werror
SOURCES = tictactoeMain.c tictactoeCurrent.c tictactoeGamePlay.c tictactoePlayers.c
HEADERS = tictactoe.h

default: tictac

tictac: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(SOURCES)

clean:
	-rm -f tictac
