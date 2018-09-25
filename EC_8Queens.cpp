/**~*~*
  8 Queens Problem
 
  Extra Credit: This program prints one solution to the 8 Queens Puzzle.
  Change it to display and count all solutions.
 
  Run the program and save the output as a comment at the end of the source file
 
  NAME:HUY DUC DAO 22C
*~**/

#include <iostream>
#include <iomanip>
#include <string>

#include "StackADT.h"

using namespace std;

const int SIZE = 30;

int getValidSize(int low, int high, string msg);
bool threatened(int board[][SIZE], int row, int col, int boardSize);
void placeQueens(Stack<int> *stack, int boardSize,int row, int col,int board[][SIZE],int &);
void printBoard(Stack<int> *stack, int boardSize);

int main ( void )
{
	int count = 0;//keep count of how many possible solutions
	int  boardSize;
	Stack<int> *stack = new Stack<int>;

	cout << "\n\t **~*~** Eight Queens problem **~*~** \n\n"
	       "\t Place a queen in each row of the board\n"
	       "\t so that no two queens threaten each other. \n";

	boardSize = getValidSize (4, SIZE, "the board size: ");
	int  row, col;
	int	 board[SIZE][SIZE] = { 0 };	// 0 no queen: 1 queen
	row = 0;
	col = -1;
	placeQueens(stack, boardSize,row, col,board,count);

	cout << "\n\t **~*~** THE END **~*~** \n\n";
	system("PAUSE");
	return 0;
}

/**~*~*
   This function prompts the user to enter an integer number within a given range
   If the input is not valid (not a number or if it is outside of the range) it
   prompts the user to enter a new number, until the input is valid.
*~**/
int getValidSize(int low, int high, string msg)
{
    int num;

    do
    {
        cout << "\nPlease enter " << msg << " (" << low << " to " << high << "): ";
        cin >> num;
        cin.clear();          // to clear the error flag
        cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
    }while(cin.fail() || num < low || num > high);

    return num;
}

/**~*~*
  	Position queens on a game board so that no queen
	can capture any other queen.
*~**/
void placeQueens(Stack<int> *stack, int boardSize,int row, int col,int board[SIZE][SIZE],int &count)
{
	while (row < boardSize)
	{
		while (col < boardSize && row < boardSize)
		{
			col++;
			if (!threatened(board, row, col, boardSize))
			{
				board[row][col] = 1;
				stack->push(col);
				row++;
				col = -1;
			}
			while (col >= boardSize - 1)
			{
				if (stack->isEmpty())
				{
					cout << "There is a total of " << count << " possible solutions" << endl;
					return;
				}
				else
				{
					stack->pop(col);
					row--;
					board[row][col] = 0;
				}
			}
			//check if the stack is full of size
			//if so, the program will start printing the solution
			if (stack->getCount() == boardSize)
			{
				cout << "Solution #:" << count + 1 << endl;
				printBoard(stack, boardSize);
				stack->pop(col);
				row--;
				board[row][col] = 0;//backtracking
				count++;
			}
		}
	}
}

/**~*~*
 	Checks rows, columns, and diagonals for threatening queens
	- board contains current positions for queens.
    - row and col are position for new queen
    - boardSize is number of rows and cols in board.
	- returns true if guarded; false if not guarded
*~**/
bool threatened(int board[][SIZE], int row, int col, int boardSize)
{
	int r, c;

	// Check current col for a queen
	c = col;
	for (r = 0; r < row; r++)
	    if (board[r][c] == 1)
	       return true;

	// Check diagonal right-up
	for (r = row - 1, c = col + 1; r > -1 && c < boardSize; r--, c++)
	    if (board[r][c] == 1)
	       return true;

	// Check diagonal left-up
	for (r = row - 1, c = col - 1; r > -1 && c > -1; r--, c--)
	    if (board[r][c] == 1)
	       return true;

	return false;
}

/**~*~*
	Print positions of chess queens on a game board
	- stack contains positions of queen.
    - boardSize is the number of rows and columns
*~**/
void printBoard (Stack<int> *stack, int boardSize)
{
	int col, stCol;

	Stack<int> *pOutStack = new Stack<int>;

	if (stack->isEmpty())
	{
	    cout << "There are no positions on this board\n";
	    return;
	}
	if (boardSize > 16)
	{
        cout << "Only boards <= 16 are printed!\n";
        return;
	}

	// Reverse stack
	while (!stack->isEmpty())
    {
	    stack->pop(stCol);
	    pOutStack->push(stCol);
    }

	// Print Column numbers
	cout << "\n           ";
	for(int i = 0; i < boardSize; i++)
        cout << setw(3) << i + 1 << "|";
    cout << endl;

    // print divider
	cout << "           ";
	for(int i = 0; i < boardSize; i++)
        cout << "--- ";
    cout << endl;

    // print board
	int row = 0;
	while (!pOutStack->isEmpty())
	{
	    pOutStack->pop(stCol);
		stack->push(stCol);//building the stack all over again
	    cout << "(" << setw(2) << row + 1 << ", " << setw(2) << stCol + 1 << "}  |";
	    for (col = 0; col < boardSize; col++)
	    {
	        if (stCol == col)
	            cout << " Q |";
            else
	            cout << "   |";
	    }
        cout << endl;
        cout << "           ";
	    for(int i = 0; i < boardSize; i++)
        {
            cout << "--- ";
        }
        cout << endl;

        row++;
    }
}

/**~*~*

         **~*~** Eight Queens problem **~*~**

         Place a queen in each row of the board
         so that no two queens threaten each other.

Please enter the board size:  (4 to 30): 5

             1|  2|  3|  4|  5|
           --- --- --- --- ---
( 1,  1}  | Q |   |   |   |   |
           --- --- --- --- ---
( 2,  3}  |   |   | Q |   |   |
           --- --- --- --- ---
( 3,  5}  |   |   |   |   | Q |
           --- --- --- --- ---
( 4,  2}  |   | Q |   |   |   |
           --- --- --- --- ---
( 5,  4}  |   |   |   | Q |   |
           --- --- --- --- ---

         **~*~** THE END **~*~**


Process returned 0 (0x0)   execution time : 1.685 s
*~**/

/**~*~*
         **~*~** Eight Queens problem **~*~**

         Place a queen in each row of the board
         so that no two queens threaten each other.

Please enter the board size:  (4 to 30): 30
Only boards <= 16 are printed!

         **~*~** THE END **~*~**


Process returned 0 (0x0)   execution time : 140.509 s
*~**/

/*

**~*~** Eight Queens problem **~*~**

Place a queen in each row of the board
so that no two queens threaten each other.

Please enter the board size:  (4 to 30): 5
Solution #:1

1|  2|  3|  4|  5|
--- --- --- --- ---
( 1,  1}  | Q |   |   |   |   |
--- --- --- --- ---
( 2,  3}  |   |   | Q |   |   |
--- --- --- --- ---
( 3,  5}  |   |   |   |   | Q |
--- --- --- --- ---
( 4,  2}  |   | Q |   |   |   |
--- --- --- --- ---
( 5,  4}  |   |   |   | Q |   |
--- --- --- --- ---
Solution #:2

1|  2|  3|  4|  5|
--- --- --- --- ---
( 1,  1}  | Q |   |   |   |   |
--- --- --- --- ---
( 2,  4}  |   |   |   | Q |   |
--- --- --- --- ---
( 3,  2}  |   | Q |   |   |   |
--- --- --- --- ---
( 4,  5}  |   |   |   |   | Q |
--- --- --- --- ---
( 5,  3}  |   |   | Q |   |   |
--- --- --- --- ---
Solution #:3

1|  2|  3|  4|  5|
--- --- --- --- ---
( 1,  2}  |   | Q |   |   |   |
--- --- --- --- ---
( 2,  4}  |   |   |   | Q |   |
--- --- --- --- ---
( 3,  1}  | Q |   |   |   |   |
--- --- --- --- ---
( 4,  3}  |   |   | Q |   |   |
--- --- --- --- ---
( 5,  5}  |   |   |   |   | Q |
--- --- --- --- ---
Solution #:4

1|  2|  3|  4|  5|
--- --- --- --- ---
( 1,  2}  |   | Q |   |   |   |
--- --- --- --- ---
( 2,  5}  |   |   |   |   | Q |
--- --- --- --- ---
( 3,  3}  |   |   | Q |   |   |
--- --- --- --- ---
( 4,  1}  | Q |   |   |   |   |
--- --- --- --- ---
( 5,  4}  |   |   |   | Q |   |
--- --- --- --- ---
Solution #:5

1|  2|  3|  4|  5|
--- --- --- --- ---
( 1,  3}  |   |   | Q |   |   |
--- --- --- --- ---
( 2,  1}  | Q |   |   |   |   |
--- --- --- --- ---
( 3,  4}  |   |   |   | Q |   |
--- --- --- --- ---
( 4,  2}  |   | Q |   |   |   |
--- --- --- --- ---
( 5,  5}  |   |   |   |   | Q |
--- --- --- --- ---
Solution #:6

1|  2|  3|  4|  5|
--- --- --- --- ---
( 1,  3}  |   |   | Q |   |   |
--- --- --- --- ---
( 2,  5}  |   |   |   |   | Q |
--- --- --- --- ---
( 3,  2}  |   | Q |   |   |   |
--- --- --- --- ---
( 4,  4}  |   |   |   | Q |   |
--- --- --- --- ---
( 5,  1}  | Q |   |   |   |   |
--- --- --- --- ---
Solution #:7

1|  2|  3|  4|  5|
--- --- --- --- ---
( 1,  4}  |   |   |   | Q |   |
--- --- --- --- ---
( 2,  1}  | Q |   |   |   |   |
--- --- --- --- ---
( 3,  3}  |   |   | Q |   |   |
--- --- --- --- ---
( 4,  5}  |   |   |   |   | Q |
--- --- --- --- ---
( 5,  2}  |   | Q |   |   |   |
--- --- --- --- ---
Solution #:8

1|  2|  3|  4|  5|
--- --- --- --- ---
( 1,  4}  |   |   |   | Q |   |
--- --- --- --- ---
( 2,  2}  |   | Q |   |   |   |
--- --- --- --- ---
( 3,  5}  |   |   |   |   | Q |
--- --- --- --- ---
( 4,  3}  |   |   | Q |   |   |
--- --- --- --- ---
( 5,  1}  | Q |   |   |   |   |
--- --- --- --- ---
Solution #:9

1|  2|  3|  4|  5|
--- --- --- --- ---
( 1,  5}  |   |   |   |   | Q |
--- --- --- --- ---
( 2,  2}  |   | Q |   |   |   |
--- --- --- --- ---
( 3,  4}  |   |   |   | Q |   |
--- --- --- --- ---
( 4,  1}  | Q |   |   |   |   |
--- --- --- --- ---
( 5,  3}  |   |   | Q |   |   |
--- --- --- --- ---
Solution #:10

1|  2|  3|  4|  5|
--- --- --- --- ---
( 1,  5}  |   |   |   |   | Q |
--- --- --- --- ---
( 2,  3}  |   |   | Q |   |   |
--- --- --- --- ---
( 3,  1}  | Q |   |   |   |   |
--- --- --- --- ---
( 4,  4}  |   |   |   | Q |   |
--- --- --- --- ---
( 5,  2}  |   | Q |   |   |   |
--- --- --- --- ---
There is a total of 10 possible solutions

**~*~** THE END **~*~**

Press any key to continue . . .

*/
