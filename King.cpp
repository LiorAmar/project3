#include "King.h"

//**********************************************
//Name:King
//Input: char type, string index
//Output:none
//Description:c'tor
//**********************************************
King::King(char type, string index) : Piece(type, index)
{
}



//**********************************************
//Name:~King
//Input:none
//Output:none
//Description:d'tor
//**********************************************
King::~King()
{
}



//**********************************************
//Name:move
//Input: Board* board, std::string currIndex, std::string newIndex
//Output:std::string
//Description: the king move checks
//**********************************************
std::string King::move(Board* board, string currIndex, string newIndex)
{
	int distanceX = 0;
	int distanceY = 0;
	string basicChecksResult = "";

	basicChecksResult = basicChecks(board, newIndex);  //Does the basic examinations
	if (strcmp(basicChecksResult.c_str(), "") != 0)  //Checks if we got a negative result
	{
		return basicChecksResult;
	}

	//TO DO: option 4

	distanceX = int(currIndex[0]) - int(newIndex[0]);
	distanceY = int(currIndex[1]) - int(newIndex[1]);
	if (makeAbsoluteValue(distanceX) > 1 || makeAbsoluteValue(distanceY) > 1)  //Checks if it is an illegal move of the piece
	{
		return "6";
	}

	return "0";
}