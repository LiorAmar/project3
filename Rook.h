#pragma once
#include "Piece.h"

#define ABSOLUTE_VALUE -1

class Rook : public Piece
{
public:
	Rook(char type, string index);
	~Rook();
	string move(Board* board, string source, string newIndex);

private:
	bool checkIfWayIsGood(Board* board, string currIndex, string newIndex, int index);
};
