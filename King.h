#pragma once

#include "Piece.h"

class King : public Piece
{
public:
	King(char type, std::string index);
	~King();

	std::string move(Board* board, std::string source, std::string newIndex);

private:

};