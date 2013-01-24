// Unit Testing for TicTacToe
// Bethany Crane
// 25/11/10

// should prolly also test a lack of side effects

#include <stdio.h>
#include <assert.h>
#include "tictactoe.h"

void testTocTacToe();

//static void testSelectGame          ();
static void testComputerPlayer      ();
static void testHumanPlayer         ();
static void printResult             ();
static void testSetGrid             (); // is now called reset grid
//static void testPrintGrid           ();
static void testSetCell             (); // needs to incorporate the pastmoves testing
static void testPotentialWin        ();
static void testThreatToBlock       ();
static void testWhoAmI              ();   
static void testWhoIsOpponent       ();
static void testGameOver            ();
static void testFindWinnerNumber    ();
static void testIsGridFull          ();
static void testNumMovesPlayed      ();
static void testIsLegal             ();
static void testIsLegalInput        ();
static void testPlayerToNumber      ();
static void testNumberToPlayer      ();

void testTicTacToe () {

   //testSelectGame          ();
   testComputerPlayer      ();
   testHumanPlayer         (); 
   testSetGrid             ();
   //testPrintGrid           ();
   testSetCell             ();
   testPotentialWin        ();
   testThreatToBlock       ();
   testWhoAmI              ();   
   testWhoIsOpponent       ();
   testGameOver            ();
   testFindWinnerNumber    ();
   testIsGridFull          ();
   testNumMovesPlayed      ();
   testIsLegal             ();
   testIsLegalInput        ();
   testPlayerToNumber      ();
   testNumberToPlayer      ();

   printf ("All PlayerView tests passed!\n");

}

static void testComputerPlayer      () {

   printf("** Testing computerPlayer\n");

   int x;
   int y;

   // Test 1.1: Test a grid with one play on it
   printf("* computerPlayer - Test 1.1\n");
   printf("* Testing a grid with one play on it\n");
   printf("* Expected result is to play in the first free square\n");
   
   grid    testGrid11 = {{'.','.','X'}, {'.','.','.'}, {'.','.','.'}}; 
   grid correctGrid11 = {{'O','.','X'}, {'.','.','.'}, {'.','.','.'}}; 
  
   computerPlayer(testGrid11);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid11[x][y] == correctGrid11[x][y]);
      }
   }   
   
   printf("** Test 1.1 - PASSED\n\n");   
   
   // Test 1.2: Test a grid with one play on it
   printf("* computerPlayer - Test 1.2\n");
   printf("* Testing a grid with one play on it\n");
   printf("* Expected result is to play in the first free square\n");
   
   grid    testGrid12 = {{'X','.','.'}, {'.','.','.'}, {'.','.','.'}}; 
   grid correctGrid12 = {{'X','O','.'}, {'.','.','.'}, {'.','.','.'}}; 
  
   computerPlayer(testGrid12);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid12[x][y] == correctGrid12[x][y]);
      }
   }   
   
   printf("** Test 1.2 - PASSED\n\n");    
   
   // Test 2: Test a grid with the potential to win in the next move
   printf("* computerPlayer - Test 2\n");
   printf("* Testing a grid with the ability to win in the next move\n");
   
   grid    testGrid2 = {{'X','.','O'}, {'.','.','O'}, {'.','.','X'}}; 
   grid correctGrid2 = {{'X','.','O'}, {'.','X','O'}, {'.','.','X'}}; 
  
   computerPlayer(testGrid2);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid2[x][y] == correctGrid2[x][y]);
      }
   }   
   
   printf("** Test 2 - PASSED\n\n");   
   
   // Test 3: Test a grid with the potential to either win or block
   printf("* computerPlayer - Test 3\n");
   printf("* Testing a grid with the ability to win or block in the next move\n");
   printf("* Expected outcome is to win the game\n");
   
   grid    testGrid3 = {{'X','O','.'}, {'O','O','.'}, {'X','.','X'}}; 
   grid correctGrid3 = {{'X','O','.'}, {'O','O','.'}, {'X','X','X'}}; 
  
   computerPlayer(testGrid3);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid3[x][y] == correctGrid3[x][y]);
      }
   }   
   
   printf("** Test 3 - PASSED\n\n");  
   
   // Test 4: Test a grid without the potential to win,
   // but the potential to block the opponent from doing so
   printf("* computerPlayer - Test 4\n");
   printf("* Testing a grid with the ability to block the opponent in the next move\n");
   
   grid    testGrid4 = {{'X','.','.'}, {'O','.','O'}, {'X','.','.'}}; 
   grid correctGrid4 = {{'X','.','.'}, {'O','X','O'}, {'X','.','.'}}; 
  
   computerPlayer(testGrid4);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid4[x][y] == correctGrid4[x][y]);
      }
   }   
   
   printf("** Test 4 - PASSED\n\n");  
   
   printf("** All computerPlayer tests passed!\n\n\n");               

}


static void testHumanPlayer         () {
// 
}

static void testSetGrid             () {
 
   printf("** Testing setGrid\n");
      
   grid correctGrid = {{'.','.','.'}, {'.','.','.'}, {'.','.','.'}};
   int x;
   int y;

   // Test 1: Start with a blank grid and end with a blank grid
   printf("* setGrid - Test 1\n");
   printf("* Testing starting with a blank grid\n");
  
   grid testGrid1 = {{'.','.','.'}, {'.','.','.'}, {'.','.','.'}};
  
   setGrid(testGrid1);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid1[x][y] == correctGrid[x][y]);
      }
   }
   
   printf("** Test 1 - PASSED\n\n");   
   
   // Test 2: Start with a full grid and end with a blank grid
   printf("* setGrid - Test 2\n");
   printf("* Testing starting with a full grid\n");
  
   grid testGrid2 = {{'X','O','X'}, {'X','O','X'}, {'X','O','X'}};
  
   setGrid(testGrid2);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid1[x][y] == correctGrid[x][y]);
      }
   }   
   
   printf("** Test 2 - PASSED\n\n");   

   // Test 3: Start with a mixed grid and end with a blank grid
   printf("* setGrid - Test 3\n");
   printf("* Testing starting with a mixed grid\n");
  
   grid testGrid3 = {{'X','.','.'}, {'.','O','X'}, {'X','.','X'}};
  
   setGrid(testGrid3);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid1[x][y] == correctGrid[x][y]);
      }
   }
   
   printf("** Test 3 - PASSED\n\n");   
   
   printf("** All setGrid tests passed!\n\n\n");   
   
}

static void testSetCell             () {

   printf("** Testing setCell\n");

   int x;
   int y;

   // Test 1: Test a blank, valid cell
   printf("* setCell - Test 1\n");
   printf("* Testing with a blank, valid cell\n");
  
   grid    testGrid1 = {{'.','.','.'}, {'.','.','.'}, {'.','.','.'}}; 
   grid correctGrid1 = {{'.','.','.'}, {'.','X','.'}, {'.','.','.'}}; 
  
   setCell(testGrid1, 1, 1, 'X');
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid1[x][y] == correctGrid1[x][y]);
      }
   }   
   
   printf("** Test 1 - PASSED\n\n");   
   
   // Test 2: Test a blank, valid cell and for side effects
   printf("* setCell - Test 2\n");
   printf("* Testing with a blank, valid cell\n");
   printf("* Testing for unwanted side effects\n");
  
   grid    testGrid2 = {{'X','.','O'}, {'.','X','.'}, {'O','.','.'}}; 
   grid correctGrid2 = {{'X','.','O'}, {'.','X','.'}, {'O','.','X'}}; 
  
   setCell(testGrid2, 2, 2, 'X');
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid2[x][y] == correctGrid2[x][y]);
      }
   }   
   
   printf("** Test 2 - PASSED\n\n");      
   
   // Test 3: Test a non-blank, valid cell
   printf("* setCell - Test 3\n");
   printf("* Testing with a non-blank, valid cell\n");
   
   grid    testGrid3 = {{'.','.','O'}, {'.','.','.'}, {'.','.','.'}}; 
   grid correctGrid3 = {{'.','.','.'}, {'.','.','.'}, {'.','.','.'}}; 
  
   setCell(testGrid3, 0, 2, '.');
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid3[x][y] == correctGrid3[x][y]);
      }
   }   
   
   printf("** Test 3 - PASSED\n\n");     
   
   // Test 4: Test a non-blank, valid cell
   printf("* setCell - Test 4\n");
   printf("* Testing with a non-blank, valid cell\n");
   
   grid    testGrid4 = {{'X','.','O'}, {'.','X','X'}, {'O','.','X'}}; 
   grid correctGrid4 = {{'X','.','O'}, {'.','X','.'}, {'O','.','X'}}; 
  
   setCell(testGrid4, 1, 2, '.');
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid4[x][y] == correctGrid4[x][y]);
      }
   }   
   
   printf("** Test 4 - PASSED\n\n");   
   
   // Test 5: Test an invalid cell
   printf("* setCell - Test 5\n");
   printf("* Testing with an invalid cell\n");
// i don't know how to test if an assertion in my main program fails....
   
   grid    testGrid5 = {{'X','.','O'}, {'.','X','.'}, {'O','.','X'}}; 
   grid correctGrid5 = {{'X','.','O'}, {'.','X','.'}, {'O','.','X'}}; 
  
   setCell(testGrid5, 3, 2, '.');
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid5[x][y] == correctGrid5[x][y]);
      }
   }   
   
   printf("** Test 5 - PASSED\n\n");         
   
   // Test 6: Test an invalid cell
   printf("* setCell - Test 6\n");
   printf("* Testing with an invalid cell\n");
   
   grid    testGrid6 = {{'X','.','O'}, {'.','X','.'}, {'O','.','X'}}; 
   grid correctGrid6 = {{'X','.','O'}, {'.','X','.'}, {'O','.','X'}}; 
  
   setCell(testGrid6, 1, -1, '.');
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid6[x][y] == correctGrid6[x][y]);
      }
   }   
   
   printf("** Test 6 - PASSED\n\n");   
   
   printf("** All setCell tests passed!\n\n\n");          

}

static void testPotentialWin        () {

   printf("** Testing potentialWin\n");

   int x;
   int y;

   // Test 1: No win
   printf("* potentialWin - Test 1\n");
   printf("* Testing a grid with no potential wins\n");
   
   grid    testGrid1 = {{'X','.','.'}, {'O','.','O'}, {'X','.','.'}}; 
   grid correctGrid1 = {{'X','.','.'}, {'O','.','O'}, {'X','.','.'}}; 
  
   potentialWin(testGrid1);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid1[x][y] == correctGrid1[x][y]);
      }
   }   
   
   printf("** Test 1 - PASSED\n\n");   
   
   // Test 2.1: Potential Diagonal Win 1
   printf("* potentialWin - Test 2.1\n");
   printf("* Testing a diagonal potential win\n");
   
   grid    testGrid21 = {{'X','.','O'}, {'.','.','O'}, {'.','.','X'}}; 
   grid correctGrid21 = {{'X','.','O'}, {'.','X','O'}, {'.','.','X'}}; 
  
   potentialWin(testGrid21);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid21[x][y] == correctGrid21[x][y]);
      }
   }   
   
   printf("** Test 2.1 - PASSED\n\n");      
   
   // Test 2.2: Potential Diagonal Win 2
   printf("* potentialWin - Test 2.2\n");
   printf("* Testing a diagonal potential win\n");
   
   grid    testGrid22 = {{'.','.','.'}, {'O','X','.'}, {'X','.','O'}}; 
   grid correctGrid22 = {{'.','.','X'}, {'O','X','.'}, {'X','.','O'}}; 
  
   potentialWin(testGrid22);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid22[x][y] == correctGrid22[x][y]);
      }
   }   
   
   printf("** Test 2.2 - PASSED\n\n"); 
   
   // Test 3.1: Potential Vertical Win 1
   printf("* potentialWin - Test 3.1\n");
   printf("* Testing a vertical potential win\n");
   
   grid    testGrid31 = {{'X','.','.'}, {'.','.','O'}, {'X','O','.'}}; 
   grid correctGrid31 = {{'X','.','.'}, {'X','.','O'}, {'X','O','.'}}; 
  
   potentialWin(testGrid31);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid31[x][y] == correctGrid31[x][y]);
      }
   }   
   
   printf("** Test 3.1 - PASSED\n\n");       
   
   // Test 3.2: Potential Vertical Win 2
   printf("* potentialWin - Test 3.2\n");
   printf("* Testing a vertical potential win\n");
   
   grid    testGrid32 = {{'.','O','X'}, {'.','O','.'}, {'X','.','X'}}; 
   grid correctGrid32 = {{'.','O','X'}, {'.','O','.'}, {'X','O','X'}}; 
  
   potentialWin(testGrid32);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid32[x][y] == correctGrid32[x][y]);
      }
   }   
   
   printf("** Test 3.2 - PASSED\n\n");  
   
   // Test 3.3: Potential Vertical Win 3
   printf("* potentialWin - Test 3.3\n");
   printf("* Testing a vertical potential win\n");
   
   grid    testGrid33 = {{'X','.','.'}, {'.','X','O'}, {'X','.','O'}}; 
   grid correctGrid33 = {{'X','.','O'}, {'.','X','O'}, {'X','.','O'}}; 
  
   potentialWin(testGrid33);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid33[x][y] == correctGrid33[x][y]);
      }
   }   
   
   printf("** Test 3.3 - PASSED\n\n");               
   
   // Test 4.1: Potential Horizontal Win 1
   printf("* potentialWin - Test 4.1\n");
   printf("* Testing a horizontal potential win\n");
   
   grid    testGrid41 = {{'X','.','.'}, {'O','.','O'}, {'X','.','X'}}; 
   grid correctGrid41 = {{'X','.','.'}, {'O','O','O'}, {'X','.','X'}}; 
  
   potentialWin(testGrid41);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid41[x][y] == correctGrid41[x][y]);
      }
   }   
   
   printf("** Test 4.1 - PASSED\n\n");                 
   
   
   // Test 4.2: Potential Horizontal Win 2
   printf("* potentialWin - Test 4.2\n");
   printf("* Testing a horizontal potential win\n");
   
   grid    testGrid42 = {{'X','X','.'}, {'.','.','.'}, {'O','.','O'}}; 
   grid correctGrid42 = {{'X','X','X'}, {'.','.','.'}, {'O','.','O'}}; 
  
   potentialWin(testGrid42);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid42[x][y] == correctGrid42[x][y]);
      }
   }   
   
   printf("** Test 4.2 - PASSED\n\n");     
   
   // Test 4.3: Potential Horizontal Win 3
   printf("* potentialWin - Test 4.3\n");
   printf("* Testing a horizontal potential win\n");
   
   grid    testGrid43 = {{'X','.','.'}, {'X','.','X'}, {'O','.','O'}}; 
   grid correctGrid43 = {{'X','.','.'}, {'X','.','X'}, {'O','O','O'}}; 
  
   potentialWin(testGrid43);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid43[x][y] == correctGrid43[x][y]);
      }
   }   
   
   printf("** Test 4.3 - PASSED\n\n");     
     
   // Test 5.1: Two potential wins
   printf("* potentialWin - Test 5.1\n");
   printf("* Testing precedent of potential wins\n");
   
   grid    testGrid51 = {{'X','O','O'}, {'.','.','O'}, {'X','.','X'}}; 
   grid correctGrid51 = {{'X','O','O'}, {'.','X','O'}, {'X','.','X'}}; 
  
   potentialWin(testGrid51);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid51[x][y] == correctGrid51[x][y]);
      }
   }   
   
   printf("** Test 5.1 - PASSED\n\n");    
   
   // Test 5.2: Two potential wins
   printf("* potentialWin - Test 5.2\n");
   printf("* Testing precedent of potential wins\n");
   
   grid    testGrid52 = {{'O','.','X'}, {'O','O','.'}, {'X','.','X'}}; 
   grid correctGrid52 = {{'O','.','X'}, {'O','O','x'}, {'X','.','X'}}; 
  
   potentialWin(testGrid52);
   
	for (x = 0; x < ROWS; x++) {
	   for (y = 0; y < COLS; y++) {
	      assert (testGrid52[x][y] == correctGrid52[x][y]);
      }
   }   
   
   printf("** Test 5.2 - PASSED\n\n");         
   
   printf("** All potentialWin tests passed!\n\n\n");      

}

static void testThreatToBlock       () {
// sample grid - one threat
// sample grid - lots of threats
// sample grid - no threats
// sample grids with threats and potential wins (should ignore them)
}

static void testWhoAmI              ();   {
// test all the legal number of moves played
// test illegal ones too (a, X, -1, 10)
// is nine legal or illegal?
}

static void testWhoIsOpponent       () {
// test whoAmI() being 1, 2, 0, a (legal, illegal)
}

static void testGameOver            () {
// test case where grid is full and there's a win
// test if it's won but not full
// test not full, no win
}

static void testFindWinnerNumber    () {
// sample grids, test when it stops, whether it picks up first or not
// test lots of ^
// try ones with no wins, some with multiple
// check it loops the right amount of time
// and comes out with the right winChar and winNum
// ADTwise i'd only be able to test the output, so winNum
}

static void testIsGridFull          () {
// sample grids, test a whole heap of them
// test with valid and invalid input (it's irrelevant for these functions)
}

static void testNumMovesPlayed      () {
// sample grids, test a whole heap of them
// test with valid and invalid input (it's irrelevant for these functions)
}

static void testIsLegal             () {
// test legalInput, legal blank
// test illegal input, legal blank
// test legal input, illegal blank
// test illegal input, illegal blank
// legal input = 0 - 2
// illegal input = 4, 6, -2, 30, a, X, O
// legal blank = draw a grid up, find some. etc
}

static void testIsLegalInput        () {
// test with legal x, legal y
// test with legal x, illegal y,
// test with illegal x, legal y,
// test with illegal x, illegal y,
// illegal = -1, 3, a, X, 42, !
// legal = 0, 1, 2
}

static void testPlayerToNumber      () {
// test with both legal (X, O)
// test differing illegal - 0, 1, 2, 1, -1, 43, 1
}

static void testNumberToPlayer      () {
// test with both legal (1, 2)
// test differing illegal - X, O, 0, -1, 43, 1
} 
