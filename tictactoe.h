// Header file for TicTacToe
// Bethany Crane
// Current as of 29/11/10

#ifndef TICTACTOE_H
#define TICTACTOE_H

#define TRUE 1
#define FALSE 0

#define BLANK '.'
#define PLAYER_ONE 'X'
#define PLAYER_TWO 'O'

#define HUMAN 1
#define COMPUTER 2

#define NUM_PLAYERS 2
#define NUM_MOVES 9

#define ROWS 3
#define COLS 3

#define MIN_CELL 0
#define MAX_CELL 2

#define UNDO 'u'
#define RESET 'r'
#define CO_ORDS 'c'
#define FORFEIT 'f'

#define NUM_WAYS_TO_WIN 8

#define ASCII_ZERO 48


typedef int bool;
typedef char grid[ROWS][COLS];

typedef struct gameState *GameState;

// ** EDIT THE GAMESTATE ** //

   // Creates a new game state
   GameState createGameState ();
   // Sets the grid to the blank all 0 state, and resets the pastMoves
   GameState resetGrid(GameState state);
   // Sets the values in a GameState
   GameState setGameState (GameState state);
   // Frees the old game state
   void disposeGameState (GameState toBeDeleted);   
   
   // Sets the mode of play for human vs comupter
   GameState setMode(GameState state, int mode);   

   // Sets a cell to (default) the current player's move, or whatever is specified (e.g. blank)
   GameState setCell(GameState state, int x, int y, char value);

   // Undoes the last move
   GameState undo(GameState state);

   // If there is a play that will result in a win, do that
   GameState potentialWin(GameState state);
   // If there is a threat to block and no potential win, do that
   GameState threatToBlock(GameState state);

   // Allows the computer AI to concede the game early
   GameState giveUp(GameState state);


// * QUERY FUNCTIONS (QUERY THE GAMESTATE) * //

   // Prints the grid out
   void printGrid(GameState state);
   
   // Gets the mode of play for human vs comupter
   int getMode(GameState state);      

   // If there's a winner or the grid is full then the game is over
   int gameOver(GameState state);
   
   // Queries state for the number of moves played so far
   int numMovesPlayed(GameState state);  
   
   // Checks through the possible three in-a-row combinations, 
   // If any are played then the winning player is returned
   int findWinnerNumber(GameState state);
   
   // Queries the state to find your player
   char whoAmI(GameState state);   
   // Queries the state to find your opponent
   char whoIsOpponent(GameState state);

   // If the input is valid and the cell is free it's a legal move
   bool isLegal(GameState state, int x, int y);

   // Checks the grid to see if there are any 0 squares. if not the grid is full.
   bool isGridFull(GameState state);
   
   // Checks the state to see if a player has given up
   bool givenUp(GameState state);
   
   // Returns true if there's a way to win
   bool isPotentialWin (GameState state);
   // Returns true if there's a threat to block
   int isThreatToBlock (GameState state);
    
// ** GAME PLAYING ** //

   // ** USE THE GAME STATE, DO NOT EDIT IT ** //
      // Gives the user the choice of which game style they'd like to play (below)
      void selectGame(GameState state, int gameType);

      // Takes in the type of game play and prints results based on it
      void printResult(GameState state, int gameType, int playerNumber);
      
   // ** INDIRECTLY EDIT THE GAME STATE ** //
   
      // The computer as an AI player
      GameState computerPlayer(GameState state);
      // Allows the user to be a player
      GameState humanPlayer(GameState state);
      // Plays the two opponents against each other
      GameState playGame(GameState state, GameState (*functionOne)(GameState), GameState (*functionTwo)(GameState));


// ** NEWGAMESTATE HELPER FUNCTIONS: ** //

   // Uses myOpponent to determine the player
   char myPlayer(GameState state);   
   // Finds out who played the last move 
   char myOpponent(GameState state);
   // Checks through the array to see how many plays we're up to
   int numMovesSoFar(grid newGrid);

// ** GENERIC HELPER FUNCTIONS ** //

   // Takes in an 'X' or 'O' and outputs a 1 or 2
   int playerToNumber(char player);
   // Takes in a 1 or 2 and produces an 'X' or 'O'
   char numberToPlayer (int player);

   // Prints out the grid with co-ordinates labelled
   void printCoords();

   // Checks whether input is valid
   bool isLegalInput(int x, int y);   

#endif
