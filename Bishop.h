#pragma once

#include "Piece.h"

#define ABSOLUTE_VALUE -1

class Bishop : public Piece
{
public:
	Bishop(char type, string index);
	~Bishop();
	string move(Board* board, string source, string newIndex);

private:
	bool checkIfWayIsGood(Board* board, string currIndex, string newIndex, int distanceX, int distanceY);
};
