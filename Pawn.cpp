#include "Pawn.h"

//**********************************************
//Name:Pawn
//Input: 
//Output:
//Description:c'tor
//**********************************************
Pawn::Pawn(char type, string index) : Piece(type, index)
{
	_hasMoved = false;
}



//**********************************************
//Name:~Pawn
//Input: 
//Output:
//Description:d'tor
//**********************************************
Pawn::~Pawn()
{
	_hasMoved = false;
}


//**********************************************
//Name:move
//Input: Board* board, std::string currIndex, std::string newIndex
//Output:std::string
//Description: the pawn move checks
//**********************************************
std::string Pawn::move(Board* board, string currIndex, string newIndex)
{
	int team = 0;
	int distanceX = 0;
	int distanceY = 0;
	string tempIndex = "";
	string basicChecksResult = "";
	Piece* piece;

	basicChecksResult = basicChecks(board, newIndex);  //Does the basic examinations
	if (strcmp(basicChecksResult.c_str(), "") != 0)  //Checks if we got a negative result
	{
		return basicChecksResult;
	}

	piece = board->getPiece(newIndex); //Gets the piece (or null) which is in this inlay

	team = getTeam();  //Gets the team of the piece
	distanceX = int(currIndex[0]) - int(newIndex[0]);
	distanceY = int(currIndex[1]) - int(newIndex[1]);

	if (team == 0 && distanceY > 0)  //Checks if the moving of the white pawn is legal
	{
		return "6";
	}
	if (team == 1 && distanceY < 0)  //Checks if the moving of the black pawn is legal
	{
		return "6";
	}

	if (distanceX == 0 && makeAbsoluteValue(distanceY) == MAX_DISTANCE)  //Checks if there is a piece in the way of the pawn
	{
		tempIndex = newIndex;
		tempIndex[1] = char(int(tempIndex[1]) + distanceY / makeAbsoluteValue(distanceY));
		if (board->getPiece(tempIndex)) //Checks if a piece exists in this certain index
		{
			return "6";
		}
	}

	distanceX = makeAbsoluteValue(distanceX);  //Makes the values positive (absolute value)
	distanceY = makeAbsoluteValue(distanceY);

	if ((distanceY == 0 && distanceX > 0) || (distanceY >= 1 && distanceX > 1) || (distanceY > 1 && distanceX >= 1) || (distanceY > 1 && _hasMoved == true) || (piece && distanceY == MAX_DISTANCE) || distanceY > MAX_DISTANCE) //Checks if there is an illegal movement
	{
		return "6";
	}
	if (distanceY == 1 && distanceX == 0)  //Checks if there is a piece in the index where the pawn is going to move
	{
		if (board->getPiece(newIndex)) //Checks if a piece exists in this certain index
		{
			return "6";
		}
	}
	if (distanceX == 1 && distanceY == 1)  //Checks if the pawn is gonna to eat
	{
		if (!board->getPiece(newIndex)) //Checks if a piece exists in this certain index
		{
			return "6";
		}
	}

	_hasMoved = true;

	return "0";
}