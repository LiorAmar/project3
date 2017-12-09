#include "Bishop.h"

//**********************************************
//Name:Bishop
//Input: char type, string index
//Output:none
//Description: c'tor
//**********************************************
Bishop::Bishop(char type, string index) : Piece(type, index)
{
}


//**********************************************
//Name:~Bishop
//Input: none
//Output:none
//Description: d'tor
//**********************************************
Bishop::~Bishop()
{
}



//**********************************************
//Name:move
//Input: Board* board, std::string currIndex, std::string newIndex
//Output:std::string
//Description: the bishop move checks
//**********************************************
std::string Bishop::move(Board* board, std::string currIndex, std::string newIndex)
{
	int index = 0;
	int distanceX = 0;
	int distanceY = 0;
	std::string basicChecksResult = "";

	basicChecksResult = basicChecks(board, newIndex);  //Does the basic examinations
	if (strcmp(basicChecksResult.c_str(), "") != 0)  //Checks if we got a negative result
	{
		return basicChecksResult;
	}


	distanceX = int(newIndex[0]) - int(currIndex[0]);
	distanceY = int(newIndex[1]) - int(currIndex[1]);

	if (makeAbsoluteValue(distanceX) != makeAbsoluteValue(distanceY))  //Checks if it is an illegal move of the piece
	{
		return "6";
	}
	else if (!checkIfWayIsGood(board, currIndex, newIndex, distanceX, distanceY))  //Checks if there is any piece in the way of the bishop
	{
		return "6";
	}

	return "0";
}




//**********************************************
//Name:checkIfWayIsGood
//Input: Board* board, string currIndex, string newIndex, int distanceX, int distanceY
//Output:bool
//Description: the bishop move checks
//**********************************************
bool Bishop::checkIfWayIsGood(Board* board, string currIndex, string newIndex, int distanceX, int distanceY)
{
	int distance = 0;
	int smallDistanceX = 0;
	int smallDistanceY = 0;
	string tempIndex = currIndex;

	distance = makeAbsoluteValue(distanceX);
	smallDistanceX = distanceX / makeAbsoluteValue(distanceX); //Gets the distance between one inlay to another (int the way of the bishop)
	smallDistanceY = distanceY / makeAbsoluteValue(distanceY);

	for (int i = 1; i < distance; i++)  //Checks if there are any pieces in the rook's way
	{
		tempIndex[0] = char(int(tempIndex[0]) + smallDistanceX); //Changes the index according the next inlay that the bishop goes to
		tempIndex[1] = char(int(tempIndex[1]) + smallDistanceY);

		if (board->getPiece(tempIndex)) //Checks if a piece exists
		{
			return false;
		}
	}

	return true;
}