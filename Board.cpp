#include "stdafx.h"


//**********************************************
//Name: Board
//Input: none
//Output:none
//Description: Instructor
//**********************************************
Board::Board()
{
	kingFlag = false;
	string whiteIndex = "";
	string blackIndex = "";

	_board[0][0] = new Rook('R', "a1");  //Creates the white "important" pieces
	_board[1][0] = new Knight('N', "b1");
	_board[2][0] = new Bishop('B', "c1");
	_board[3][0] = new King('K', "d1");
	_board[4][0] = new Queen('Q', "e1");
	_board[5][0] = new Bishop('B', "f1");
	_board[6][0] = new Knight('N', "g1");
	_board[7][0] = new Rook('R', "h1");

	whiteIndex = "a2";  //Initiates the indexes of the pawns
	blackIndex = "a7";

	for (int i = 0; i < BOARD_LENGTH; i++) //Creates the pawns
	{
		_board[i][1] = new Pawn('P', whiteIndex);  //Creates a new white pawn
		_board[i][6] = new Pawn('p', blackIndex);   //Creates a new black pawn

		whiteIndex[0] = char(int(whiteIndex[0]) + 1);  //Changes the the index of a white pawn
		blackIndex[0] = char(int(blackIndex[0]) + 1);  //Changes the the index of a black pawn
	}

	for (int i = 2; i < 6; i++)  //Initiates the rest of the board
	{
		for (int j = 0; j < BOARD_LENGTH; j++)
		{
			_board[j][i] = nullptr;
		}
	}

	_board[0][7] = new Rook('r', "a8");  //Creates the white "important" pieces
	_board[1][7] = new Knight('n', "b8");
	_board[2][7] = new Bishop('b', "c8");
	_board[3][7] = new King('k', "d8");
	_board[4][7] = new Queen('q', "e8");
	_board[5][7] = new Bishop('b', "f8");
	_board[6][7] = new Knight('n', "g8");
	_board[7][7] = new Rook('r', "h8");
}
//********************
//Destructor
//input: none
//output: none
//********************

Board::~Board()
{
	for (int i = 0; i < BOARD_LENGTH; i++)  //Checks every inlay in the board
	{
		for (int j = 0; j < BOARD_LENGTH; j++)
		{
			if (_board[i][j]) //Checks if there is a piece in this certain inlay
			{
				delete _board[i][j];
			}
		}
	}
}
//**********************************************
//The function returns a certain piece which is in the board
//input: the index of the piece
//output: the requested piece
//**********************************************
Piece* Board::getPiece(string index)
{
	int x = int(index[0] - ASCII_LETTER);  //changes it to a number
	int y = int(index[1] - ASCII_NUMBER);

	return _board[x][y];
}
//**********************************************
//The function moves a certain piece from one place to another
//input: the source index, the destination index
//output: none
//**********************************************
void Board::completeMove(string source, string destination)
{
	int sourceX = int(source[0] - ASCII_LETTER);  //changes it to a number
	int sourceY = int(source[1] - ASCII_NUMBER);
	int destX = int(destination[0] - ASCII_LETTER);
	int destY = int(destination[1] - ASCII_NUMBER);

	_board[destX][destY] = _board[sourceX][sourceY];  //exchanges the index of the piece
	_board[sourceX][sourceY] = nullptr;

	_board[destX][destY]->setIndex(destination);  //Sets the new Index
}



//**********************************************
//Name: printBoard
//Input: none
//Output:none
//Description: prints the board
//**********************************************
void Board::printBoard()
{
	for (int i = 0; i < BOARD_LENGTH; i++)  //Prints the board
	{
		for (int j = 0; j < BOARD_LENGTH; j++)
		{
			if (_board[j][i])  //Checks if the piece exists
			{
				cout << _board[j][i]->getType() << " ";
			}
			else
			{
				cout << "# ";
			}
		}

		cout << endl;
	}
}


//**********************************************
//Name: deleteEaten
//Input: string index
//Output:void
//Description: delete's piece
//**********************************************
void Board::deleteEaten(string index)
{
	int i = int(index[0]) - ASCII_LETTER;
	int j = int(index[1]) - ASCII_NUMBER;

	if (_board[i][j])  //Checks if there is a piece in this certain inlay
	{
		delete _board[i][j];
	}
}