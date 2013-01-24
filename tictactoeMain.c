// Main file for TicTacToe
// Bethany Crane
// Current as of 29/11/10

#include <stdio.h>
#include <stdlib.h>
#include "tictactoe.h"

int main (int argc, char *argv[]) {            

   int gameType;

   printf 
   ("Please choose the combination of players:\n \
     1: computer vs computer\n \
     2: human vs computer\n \
     3: human vs human\n");
              
   scanf ("%d", &gameType);
   
   GameState state = createGameState ();

   selectGame(state, gameType); 
   
   disposeGameState(state);
   
   return EXIT_SUCCESS;
   
}
