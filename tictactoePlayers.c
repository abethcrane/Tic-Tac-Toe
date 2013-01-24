// Computer AI file for TicTacToe
// Bethany Crane
// Current as of 29/11/10

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tictactoe.h"

GameState computerPlayer(GameState state) {

   bool played = FALSE;
   srand (time(NULL));
   
   int x = 0;
   int y = 0;
        
   // If you can win do so
   state = potentialWin(state);
  
   if (!isPotentialWin(state)) {

      // Else if you can stop the other player winning do that   
      state = threatToBlock(state);
      if (!isThreatToBlock(state)) {

         // If it's the first move play randomly
         if (numMovesPlayed(state) == 0) {
            x = rand() % ROWS;
            y = rand() % COLS;
            state = setCell(state, x,y, whoAmI(state));
            played = TRUE;              
                
         // Else play the next free square  
         } else {
            
            while ((x < ROWS) && (played == FALSE)) {
               y = 0;
               while ((y < COLS) && (played == FALSE)) {
                  if (isLegal(state, x, y)) {
                     state = setCell(state, x, y, whoAmI(state));
                     played = TRUE;
                  }
                  y++;
               }
               x++;
            }   
            
         }   
           
      } else if (isThreatToBlock(state) > 1) {
         if (getMode(state) == 1) {
            // Undo the moves played and graciously admit defeat
            state = undo(state);
            state = undo(state);       
            printf ("Well played, My Liege. The battle is yours.\n");
            state = giveUp(state);    
         } else if (getMode(state) == 3) {   
            // Leave all the threats as blocked and yell BAZINGA! before continuing the game
            printGrid(state);
            printf ("BAZINGA!\n");
            state = setGameState(state);
            state = giveUp(state);
         }
           
      }             
      
   }

   return state;
   
}
