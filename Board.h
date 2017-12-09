#pragma once
#include "Piece.h"
#include <iostream>
#define BOARD_LENGTH 8
#define ASCII_NUMBER 49
#define ASCII_LETTER 97
using namespace std;//we will change it until the last submission
class Piece;
class Board
{
public:
	Board();
	~Board();
	Piece* getPiece(std::string index);
	void completeMove(std::string source, std::string destination);
	void printBoard();
	void deleteEaten(std::string newIndex);

	bool kingFlag;
private:
	Piece* _board[BOARD_LENGTH][BOARD_LENGTH];
};
