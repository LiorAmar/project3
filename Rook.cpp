#include "Rook.h"

//**********************************************
//Name:Rook
//Input: char type, string index
//Output:
//Description:c'tor
//**********************************************
Rook::Rook(char type, string index) : Piece(type, index)
{
}



//**********************************************
//Name:~Rook
//Input: 
//Output:
//Description:d'tor
//**********************************************
Rook::~Rook()
{
}



//**********************************************
//Name:move
//Input: Board* board, std::string currIndex, std::string newIndex
//Output:std::string
//Description: the Rook move checks
//**********************************************
string Rook::move(Board* board, string currIndex, string newIndex)
{
	int index = 0;
	string basicChecksResult = "";

	basicChecksResult = basicChecks(board, newIndex);  //Does the basic examinations
	if (strcmp(basicChecksResult.c_str(), "") != 0)  //Checks if we got a negative result
	{
		return basicChecksResult;
	}

	//TO DO: option 4

	if (currIndex[0] != newIndex[0] && currIndex[1] != newIndex[1])  //Checks if it is an illegal move of the piece
	{
		return "6";
	}

	if (currIndex[1] != newIndex[1]) //Checks where the difference in the indexes is
	{
		index = 1;
	}

	if (!checkIfWayIsGood(board, currIndex, newIndex, index))  //Checks if the way (from the source inlay to the destination inlay) is available
	{
		return "6";
	}

	return "0";
}



//**********************************************
//Name:checkIfWayIsGood
//Input: Board* board, string currIndex, string newIndex, int index
//Output:bool
//Description: checks if the way is empty..
//**********************************************
bool Rook::checkIfWayIsGood(Board* board, string currIndex, string newIndex, int index)
{
	int factor = 0;
	int distance = 0;
	string tempIndex = currIndex;

	distance = int(currIndex[index]) - int(newIndex[index]);  //Calculates the distance between the inlays

	if (distance < 0) //Makes sure that the distance will be positive
	{
		factor = 1;
		distance = distance * ABSOLUTE_VALUE;
	}
	else
	{
		factor = ABSOLUTE_VALUE;
	}

	for (int i = 1; i < distance; i++)  //Checks if there are any pieces in the rook's way
	{
		if (index == 0) //Checks where is the difference between the inlays
		{
			tempIndex[0] = char(int(tempIndex[0]) + factor);
			tempIndex[1] = currIndex[1];
		}
		else
		{
			tempIndex[1] = char(int(tempIndex[1]) + factor);
			tempIndex[0] = currIndex[0];
		}

		if (board->getPiece(tempIndex)) //Checks if a piece exists
		{
			return false;
		}
	}

	return true;
}