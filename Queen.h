#pragma once

#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"

class Queen : public Piece, public Rook, public Bishop
{
public:
	Queen(char type, string index);
	~Queen();
	string move(Board* board, string source, string newIndex);


private:
	string _queenIndex;
};