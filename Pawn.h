#pragma once

#include "Piece.h"

#define MAX_DISTANCE 2

class Pawn : public Piece
{
public:
	Pawn(char type, string index);
	~Pawn();
	string move(Board* board, string source, string newIndex);

private:
	bool _hasMoved;
};


