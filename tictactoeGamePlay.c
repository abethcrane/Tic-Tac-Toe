// Game Playing file for TicTacToe
// Bethany Crane
// Current as of 29/11/10

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tictactoe.h"

void selectGame(GameState state, int gameType) {

   int mode;
   int playerNumber;

   switch (gameType) {
      case 1:
      
         state = playGame(state, &computerPlayer, &computerPlayer);
         break;
         
      case 2:
      
         printf ("Please choose a mode:\n");
         printf ("   1: sympathetic\n");
         printf ("   2: indifferent\n");
         printf ("   3: cruel and twisted\n");            
         
         scanf ("%d", &mode);
         assert (mode > 0);
         assert (mode < 4);   
         
         state = setMode(state, mode);
         
         printf ("Please enter which player you would like to be:\n");
         printf ("   1: Player One\n");
         printf ("   2: Player Two\n");     
         
         scanf ("%d", &playerNumber);
         assert (playerNumber > 0);
         assert (playerNumber < (NUM_PLAYERS + 1)); 

         if (playerNumber == 1) {      
            state = playGame(state, &humanPlayer, &computerPlayer);
         } else if (playerNumber == 2) {
            state = playGame(state, &computerPlayer, &humanPlayer);
         }
         
         break;
         
      case 3:
      
         state = playGame(state, &humanPlayer, &humanPlayer);
         break;
         
      default:
      
         printf ("Bad input; program terminating\n");
         break;
         
   };
   
   // If the computer didn't abort early because it predicted its death
   if (!givenUp(state)) {
      printGrid(state);
      // Prints the results at the end on account of selectGame has all the data it needs
      printResult(state, gameType, playerNumber);  
   }
}

GameState playGame(GameState state, GameState (*functionOne)(GameState), GameState (*functionTwo)(GameState)) {

   int nextPlayer;
   
   // Print out the grid with co-ordinates labelled
   printCoords();
   
   printf ("Entering 'c' will reprint the grid with labelled co-ordinates\n");
   printf ("Entering 'u' will undo the past two moves, allowing you to redo your last one\n");
   printf ("Entering 'r' will reset the game to the blank grid\n\n");

   printf ("Entering 'f' will forfeit the game\n\n");

   printf ("Valid co-ordinates are between %d and %d, format x,y\n\n", MIN_CELL, MAX_CELL);
   
   // While the game isn't won and the grid isn't full 
   // (and while the computer hasn't given up before its ineveitable defeat)
   while (gameOver(state) == FALSE) { 

      printGrid(state);
   
      state = setGameState(state);
     
      nextPlayer = playerToNumber(whoAmI(state));
      printf("Player %d's turn\n", nextPlayer);
      
      if (nextPlayer == 1) {
         state = functionOne(state);
      } else {
         state = functionTwo(state);
      }                
     
   } 

   return state;

}

GameState humanPlayer(GameState state) {

   char inputX;
   char inputY;
   
   int x;
   int y;
   char space;
   
   bool input = FALSE;   
   int loopCounter = 0; 
   
   printf ("Please enter a cell co-ordinate to play\n");  

   while ((input == FALSE) && (loopCounter < 5)) { // Arbitrary loop counter value
      
      scanf ("\n");
      scanf ("%c", &inputX);
         
      // In case of special characters 
      if (inputX == UNDO) {
      
         state = undo(state);
         // We need to go back two moves, so that the user can undo *their* move, not the computer's
         state = undo(state);
         printf ("Please enter a new move\n");
         printGrid(state);
         loopCounter--; // So that this doesn't count as a move
         
      } else if (inputX == RESET) {
      
         state = resetGrid(state);
         input = TRUE; // Exit the loop
         
      } else if (inputX == CO_ORDS) {
      
         printCoords();
         printGrid(state);
         printf ("Please enter a new move\n");
         loopCounter--; //So that this doesn't count as a move
      
      } else if (inputX == FORFEIT) {
         
         state = giveUp(state);
         printf ("Player %c has given up! The robot overlord is victorious again!\n", whoAmI(state));  
         input = TRUE; // Exit the loop
         
      // Back to the game
      } else {
         
         // Checking the format of the input
         space = getchar();         
         if ((space == ' ') || (space == ',') || (space == '\n')) {
         
            scanf("%c", &inputY);
            
            // Convert the character inputs into numbers for setCell
            x = (int)inputX - ASCII_ZERO;
            y = (int)inputY - ASCII_ZERO;
            
            if (isLegal(state, x, y)) {
               state = setCell(state, x, y, whoAmI(state));
               input = TRUE;
               
            } else if (isLegalInput(x, y)) {
               printf ("Sorry, invalid move; try again\n");
               
            } else if (loopCounter == 4) {
               printf ("Valid input is between %d and %d, you've used up all your attempts\n", 
                      MIN_CELL, MAX_CELL);
                      
               // Kill the program.
               assert (loopCounter == 5); 
               
            } else {
               printf 
               ("Valid input is between %d and %d; try again\n",
                MIN_CELL, MAX_CELL);
             }
             
         // If they've entered it badly formatted
         } else {
         
            printf ("Valid input is in the form x,y; try again\n");
            
            // Read in any extraneous characters to create a new slate for the next input
            space = getchar();
            while (space != '\n') {
               space = getchar();
            }
            
         }
      }     

      loopCounter++;

   } 
   
   return state;
   
}

void printResult(GameState state, int gameType, int playerNumber) {

   int winner = findWinnerNumber(state);
   int computerNumber = (playerNumber % NUM_PLAYERS) + 1;

   switch (gameType) {
      case 1:
      
         // If there is a winner (1 or 2)
         if (winner > 0) {
            printf("Player %d (%c) wins!\n", 
                   winner, 
                   numberToPlayer(winner));
         } else {
            printf("Jack's game; nobody wins\n");
         }
         
         break;
         
      case 2:
      
         if (winner == playerNumber) {
            printf ("Congratulations! You win!\n");
         } else if (winner == computerNumber) {
            switch (getMode(state)) { 
               case 1:
                  printf ("Nice try, better luck next time?\n");
                  break;
               case 2:
                  printf ("You lost. You lasted %d moves\n", numMovesPlayed(state));
                  break;
               case 3:
                  printf ("I'm sorry, the computer ran over your baby.\n"); 
                  break;
               default:
                  break;                             
               }        
            } else {
               printf ("Jack won. Lucky bastard.\n");
            }
            
         break;
         
      case 3:
      
         if (winner == playerToNumber(PLAYER_ONE)) {
            printf("Player One wins!\n");
         } else if (winner == playerToNumber(PLAYER_TWO)) {
            printf("Player Two wins!\n");
         } else {
            printf("You were worthy adversories, but Jack claims the game\n");
         }   
         
         break;
         
      default:
      
         printf ("Bad input; program terminating\n");
         break;
         
   };

}
