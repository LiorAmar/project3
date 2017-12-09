#include "Knight.h"

//**********************************************
//Name:Knight
//Input: char type, string index
//Output:
//Description:c'tor
//**********************************************
Knight::Knight(char type, std::string index) : Piece(type, index)
{
}




//**********************************************
//Name:~Knight
//Input:
//Output:
//Description:d'tor
//**********************************************
Knight::~Knight()
{
}



//**********************************************
//Name:move
//Input: Board* board, std::string currIndex, std::string newIndex
//Output:std::string
//Description: the knight move checks
//**********************************************
string Knight::move(Board* board, string currIndex, string newIndex)
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
	if ((makeAbsoluteValue(distanceX) == DISTANCE && makeAbsoluteValue(distanceY) == 1) || (makeAbsoluteValue(distanceX) == 1 && makeAbsoluteValue(distanceY) == DISTANCE))  //Checks if it is an illegal move of the piece
	{
		return "0";
	}
	else
	{
		return "6";
	}
}