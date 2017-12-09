#pragma once

#include "Piece.h"

#define DISTANCE 2

class Knight : public Piece
{
public:
	Knight(char type, std::string index);
	~Knight();
	std::string move(Board* board, std::string source, std::string newIndex);

private:
};
