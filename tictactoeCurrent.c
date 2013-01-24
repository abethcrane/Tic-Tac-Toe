// TicTacToe
// Bethany Crane
// Current as of 29/11/2010

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "tictactoe.h"

// Grid co-ordinates for the 8 possible ways to win
int X1[] = {0, 0, 0, 0, 0, 0, 1, 2};
int Y1[] = {0, 2, 2, 1, 0, 0, 0, 0};
int X2[] = {1, 1, 1, 1, 1, 0, 1, 2};
int Y2[] = {1, 1, 2, 1, 0, 1, 1, 1};
int X3[] = {2, 2, 2, 2, 2, 0, 1, 2};
int Y3[] = {2, 0, 2, 1, 0, 2, 2, 2};

struct gameState {

   // Contains the game grid
   grid newGrid;
   
   // The history of the game (x co-ords)
   int pastMovesX[NUM_MOVES];

   // The history of the game (y co-ords)
   int pastMovesY[NUM_MOVES];
   
   // The number of moves played throughout the game
   int movesPlayed;

   // The X or O of the current player
   char player;
   
   // The X or O of the opponent
   char opponent;
   
   // The 1 or 2 of the current player
   int currentPlayerNumber;
   
   // For the computer AI
   bool isTherePotentialWin;
   
   // Also for the computer AI
   int howManyThreats;
   
   // The mode of play for human vs computer
   int mode;
   
   // Has the computer given up?
   bool givenUp;

};


GameState createGameState() {

   // Puts the GameState on the heap
   GameState newState = malloc(sizeof(struct gameState));
   
   // Checks that the malloc worked properly (otherwise it would return NULL)
   assert (newState != NULL);

   newState = resetGrid (newState);

   return newState;
}

GameState resetGrid(GameState state) {
   
   int x;
   int y;
   for (x = 0; x < ROWS; x++) {
      for (y = 0; y < COLS; y++) {
         state -> newGrid[x][y] = BLANK;     
      }
   }
   
   int i;
   for (i = 0; i < NUM_MOVES; i++) {
      state -> pastMovesX[i] = -1;
      state -> pastMovesY[i] = -1;
   }

   state -> movesPlayed = 0;
  
   state -> player = PLAYER_ONE;
   
   state -> opponent = PLAYER_TWO;
   
   state -> isTherePotentialWin = FALSE;
   
   state -> howManyThreats = FALSE;
   
   // The default mode means nothing changes, which is the same as indifference mode, which is 2
   state -> mode = 2; 
   
   state -> givenUp = FALSE;
   
   return state;
   
}

GameState setGameState (GameState state) {

   state -> movesPlayed = numMovesSoFar(state -> newGrid);

   state -> player = myPlayer(state);
   
   state -> opponent = myOpponent(state);
   
   state -> isTherePotentialWin = FALSE;
   
   state -> howManyThreats = FALSE;
   
   return state;
 
}

void disposeGameState (GameState toBeDeleted) {
   assert (toBeDeleted != NULL);
   free (toBeDeleted);
}

GameState setMode(GameState state, int mode) {

   state -> mode = mode;
   
   return state;

}

int getMode (GameState state) {

   return state -> mode;

}

void printCoords() {

   // Print grid co-ordinates
   
   /* 
       |   |
    0,0|0,1|0,2
    ---|---|---
    1,0|1,1|1,2
    ---|---|---
    2,0|2,1|2,2
       |   |
   */
   
   printf("   |   |   \n");
   printf("0,0|0,1|0,2\n");
   printf("---|---|---\n");
   printf("1,0|1,1|1,2\n");
   printf("---|---|---\n");
   printf("2,0|2,1|2,2\n");   
   printf("   |   |   \n");
   printf("\n");

}

void printGrid(GameState state) {

   /*  |   |
    _x_|_o_|_x_
    _o_|_x_|_o_
     o | x | x
       |   |
   */
   printf("   |   |   \n");
   printf("_%c_|_%c_|_%c_\n", state -> newGrid[0][0],  state -> newGrid[0][1],  state -> newGrid[0][2]);
   printf("_%c_|_%c_|_%c_\n", state -> newGrid[1][0],  state -> newGrid[1][1],  state -> newGrid[1][2]);
   printf(" %c | %c | %c \n", state -> newGrid[2][0],  state -> newGrid[2][1],  state -> newGrid[2][2]);
   printf("   |   |   \n\n");
           
}

GameState setCell(GameState state, int x, int y, char value) {
   
   assert(isLegalInput(x, y) || (value == BLANK));
   
   state -> newGrid[x][y] = value;
   
   // If we're not resetting the grid or undoing a move, add the new move to the history
   // Not '-1' because if this is the fourth move then numMovesPlayed is still at 3
   // So cell 3 is correct (fourth counting from 0)
   if ((value == PLAYER_ONE) || (value == PLAYER_TWO)) {
      state -> pastMovesX[numMovesPlayed(state)] = x;
      state -> pastMovesY[numMovesPlayed(state)] = y;
      state -> movesPlayed++;
   }
   
   return state;
      
}

GameState undo(GameState state) {
   
   assert (numMovesPlayed(state) > 0);
   
   
   // Find the co-ordinates of the last move
   // -1 because numMovesSoFar corresponds to the array cell one beneath it. 
   // E.g the first move increases the counter to 1, but edits the array cell 0
   int x = state -> pastMovesX[(numMovesPlayed(state))-1];
   int y = state -> pastMovesY[(numMovesPlayed(state))-1];
   
   // Set the cell with that co-ordinates to be blank
   state = setCell(state, x, y, BLANK);   
   
   // And now we set the pastMoves back to the default
   state -> pastMovesX[(numMovesPlayed(state))-1] = -1;
   state -> pastMovesY[(numMovesPlayed(state))-1] = -1;  
     
   state -> movesPlayed--;     
   
   return state;

}

GameState potentialWin(GameState state) {

   int i = 0;
   
   // If any two of the three in a row options are equal, play in the third
   while ((i < NUM_WAYS_TO_WIN) && (state -> isTherePotentialWin == FALSE)) {
             if ((state -> newGrid[X1[i]][Y1[i]] == state -> player) && 
                 (state -> newGrid[X2[i]][Y2[i]] == state -> player) && 
                 (state -> newGrid[X3[i]][Y3[i]] == BLANK)) {
              
         state = setCell(state, X3[i],Y3[i], state -> player);
         state -> isTherePotentialWin = TRUE;      
             
      } else if ((state -> newGrid[X1[i]][Y1[i]] == state -> player) && 
                 (state -> newGrid[X3[i]][Y3[i]] == state -> player) && 
                 (state -> newGrid[X2[i]][Y2[i]] == BLANK)) {
                 

         state = setCell(state, X2[i],Y2[i], state -> player);
         state -> isTherePotentialWin = TRUE;          
         
      } else if ((state -> newGrid[X3[i]][Y3[i]] == state -> player) && 
                 (state -> newGrid[X2[i]][Y2[i]] == state -> player) && 
                 (state -> newGrid[X1[i]][Y1[i]] == BLANK)) {
                 
         state = setCell(state, X1[i],Y1[i], state -> player); 
         state -> isTherePotentialWin = TRUE;
         
      }
      i++;
   }  
   
   return state;;
   
}

bool isPotentialWin (GameState state) {

   return state -> isTherePotentialWin;

}

GameState threatToBlock(GameState state) {

   int i = 0;
   int numThreats;
   int startThreats;

   // The mode depends on whether the game is played fairly or not
   switch (getMode(state)) {
      case 1: 
         // If it finds more than one, abort
         startThreats = NUM_WAYS_TO_WIN - 2; 
         numThreats = startThreats;
         break;
      case 2:
         // Find the first threat, play it, do nothing more
         startThreats = NUM_WAYS_TO_WIN - 1; 
         numThreats = startThreats;         
         break;
      case 3: 
         // Find and play all threats 
         startThreats = 0; 
         numThreats = startThreats;         
         break;
      default:
         break;
   };
      
   // If any two of the three in a row options are equal, play in the third
   while ((i < NUM_WAYS_TO_WIN) && (numThreats < NUM_WAYS_TO_WIN)) { 
   // = less optimal speed, however, gratious resignation && (state -> howManyThreats == FALSE)) {
             if ((state -> newGrid[X1[i]][Y1[i]] == state -> opponent) && 
                 (state -> newGrid[X2[i]][Y2[i]] == state -> opponent) && 
                 (state -> newGrid[X3[i]][Y3[i]] == BLANK)) {
          
         state = setCell(state, X3[i],Y3[i], state -> player);
         numThreats++;

      } else if ((state -> newGrid[X1[i]][Y1[i]] == state -> opponent) && 
                 (state -> newGrid[X3[i]][Y3[i]] == state -> opponent) && 
                 (state -> newGrid[X2[i]][Y2[i]] == BLANK)) {
                 
         state = setCell(state, X2[i],Y2[i], state -> player);
         numThreats++;
         
      } else if ((state -> newGrid[X3[i]][Y3[i]] == state -> opponent) && 
                 (state -> newGrid[X2[i]][Y2[i]] == state -> opponent) && 
                 (state -> newGrid[X1[i]][Y1[i]] == BLANK)) {
                 
         state = setCell(state, X1[i],Y1[i], state -> player); 
         numThreats++;
         
      }
      
      i++;
   }
  
   state -> howManyThreats = numThreats - startThreats;
  
   return state;
   
}

int isThreatToBlock(GameState state) {

   return state -> howManyThreats;

}

GameState giveUp(GameState state) {

   state -> givenUp = TRUE;
   
   return state;
}

bool givenUp(GameState state) {

   return state -> givenUp;

}

bool gameOver(GameState state) {

   bool isGameOver = FALSE;

   if (findWinnerNumber(state) != FALSE) {
      isGameOver = TRUE;
   } else if (isGridFull(state) == TRUE) {
      isGameOver = TRUE;
   } else if (givenUp(state) == TRUE) {
      isGameOver = TRUE;
   }

   return isGameOver;
   
}

int findWinnerNumber(GameState state) {

   int winner = FALSE;
   int i = 0;
   
   // Loop through each combination and compare the three in-a-row cells
   // If they are equal, the game is won by that cell holder.
   while ((i < NUM_WAYS_TO_WIN) && (winner == FALSE)) {
   
      if ((state -> newGrid[X1[i]][Y1[i]] == state -> newGrid[X2[i]][Y2[i]]) && 
          (state -> newGrid[X1[i]][Y1[i]] ==state -> newGrid[X3[i]][Y3[i]]) && 
          (state -> newGrid[X1[i]][Y1[i]] != BLANK)) {
         winner = state -> newGrid[X1[i]][Y1[i]];
      }
      
      i++;
      
   }        
   
   winner = playerToNumber(winner);

   return winner;
   
}

char whoAmI (GameState state) {

   return state -> player;
   
}

char whoIsOpponent(GameState state) {

   return state -> opponent;

}

int numMovesPlayed(GameState state) {

   return state -> movesPlayed;
   
}

bool isGridFull (GameState state) {

   int isFull = FALSE;
   
   if (numMovesPlayed(state) == NUM_MOVES) {
      isFull = TRUE;
   }
   
   return isFull;

}

bool isLegal (GameState state, int x, int y) {

   bool legal = FALSE;
   
   if (isLegalInput(x,y) && (state -> newGrid[x][y] == BLANK)) {
      legal = TRUE;
   }

   return legal;

}

bool isLegalInput (int x, int y) {

   bool legalInput = FALSE;
   
   if ((x >= MIN_CELL) && (x <= MAX_CELL) && 
       (y >= MIN_CELL) && (y <= MAX_CELL)) {
      legalInput = TRUE;
   }
   
   return legalInput;
   
}

// *** Helper Functions for newGameState *** //
char myPlayer (GameState state) {

   char player;

   if (myOpponent(state) == PLAYER_ONE) {
      player = PLAYER_TWO;
   } else {
      player = PLAYER_ONE;
   }   

   return player;
   
}

char myOpponent(GameState state) {

   int numMoves = numMovesSoFar(state -> newGrid) - 1;
   char opponent = state -> newGrid[state -> pastMovesX[numMoves]][state -> pastMovesY[numMoves]];
   
   return opponent;

}

int numMovesSoFar(grid newGrid) {

   int movesPlayed = 0;
   int x;
   int y;
   
   for (x = 0; x < ROWS; x++) {
      for (y = 0; y < COLS; y++) {
         if (newGrid[x][y] != BLANK) {
            movesPlayed++;
         }
      }
   }   

   return movesPlayed;
 
}

// *** End Helper Functions for newGameState *** //

int playerToNumber(char player) {

   int playerNumber;
   
   if (player == 0) {
      playerNumber = 0;
   } else if (player ==  PLAYER_ONE) {
      playerNumber = 1;
   } else if (player == PLAYER_TWO) {
      playerNumber = 2;
   }

   return playerNumber;

}

char numberToPlayer (int player) {

   char playerChar;
   
   if (player == 1) {
      playerChar = PLAYER_ONE;
   } else if (player == 2) {
      playerChar = PLAYER_TWO;
   }
   
   return playerChar;

}
