#include "Queen.h"
#include "Bishop.h"
#include <iostream>
#include <string>

/*
_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);  //Checks if there is a memory leak
*/


//**********************************************
//Name:Queen
//Input: char type, string index
//Output:
//Description: c'tor
//**********************************************
Queen::Queen(char type, string index) : Piece(type, index), Rook(type, index), Bishop(type, index)
{
	_queenIndex = index;
}



//**********************************************
//Name:~Queen
//Input: 
//Output:
//Description: d'tor
//**********************************************
Queen::~Queen()
{
	_queenIndex = "";
}



//**********************************************
//Name:move
//Input: Board* board, std::string currIndex, std::string newIndex
//Output:std::string
//Description: the queen move checks
//**********************************************
std::string Queen::move(Board* board, std::string currIndex, std::string newIndex)
{
	std::string result = "";
	std::string index = (board->kingFlag) ? currIndex : _queenIndex;

	result = Rook::move(board, index, newIndex);  //Checks if the queen moves like a rook

	if (strcmp(result.c_str(), "0") == 0 && !board->kingFlag)  //Returns a confirmation if the queen moves like a rook
	{
		_queenIndex = newIndex;
		return result;
	}

	index = (board->kingFlag) ? currIndex : _queenIndex;
	result = Bishop::move(board, index, newIndex); //Checks if the queen moves like a bishop

	if (strcmp(result.c_str(), "0") == 0 && !board->kingFlag)  //Returns a confirmation if the queen moves like a bishop
	{
		_queenIndex = newIndex;
	}

	return result;
}
