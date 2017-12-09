#include "stdafx.h"
//#include "Piece.h"

//**********************************************
//Name: Piece
//Input: char type, string index
//Output:
//Description: c'tor
//**********************************************
Piece::Piece(char type, string index)
{
	_index = index;

	if (int(type) > ASCII_LETTER)  //Checks if it black or white
	{
		_team = 1;
	}
	else
	{
		_team = 0;
		//type = tolower(type);  //Makes it a small letter
	}

	_type = type;

}



//**********************************************
//Name: ~Piece
//Input: 
//Output:
//Description: d'tor
//**********************************************
Piece::~Piece()
{
	_index = "";
	_type = NULL;
	_team = 0;
}



//***********************************
//Name: getTeam()
//Input: void
//Output: int
//Description: returns _team
//***********************************
int Piece::getTeam()
{
	return _team;
}



//***********************************
//Name: getType()
//Input: void
//Output: char
//Description: returns _type
//***********************************
char Piece::getType()
{
	return _type;
}



//***********************************
//Name: getIndex()
//Input: void
//Output: string
//Description: returns _index
//***********************************
string Piece::getIndex()
{
	return _index;
}



//***********************************
//Name: setIndex()
//Input: string
//Output: void
//Description: sets _index
//***********************************
void Piece::setIndex(string newIndex)
{
	_index = newIndex;

}



//***********************************
//Name:makeAbsoluteValue
//Input: int value
//Output: int
//Description: sets _indexjust like math::abs
//***********************************
int Piece::makeAbsoluteValue(int value)
{
	if (value < 0)  //Checks if the value is negative
	{
		value = value * ABSOLUTE_VALUE;
	}

	return value;
}



//***********************************
//Name:basicChecks
//Input: Board* board, string newIndex
//Output: int
//Description: sets _indexjust like math::abs
//***********************************
string Piece::basicChecks(Board* board, string newIndex)
{
	string currIndex = "";
	string result = "";
	Piece* piece;


	currIndex = getIndex();  //Gets the current index of the piece


	if (newIndex[0] < 'a' || newIndex[0] > 'h' || newIndex[1] < '1' || newIndex[1] > '8')  //Checks if the index is valid
	{
		return "5";
	}

	piece = board->getPiece(newIndex);
	if (piece)  //Checks if it is an empty place in the board
	{
		if (getTeam() == piece->getTeam())  //Checks if the piece in the destination is not in the same team like the rook
		{
			return "3";
		}
	}

	if (currIndex[0] == newIndex[0] && currIndex[1] == newIndex[1])  //Checks if the source inlay and the destination inlay are the same
	{
		return "7";
	}

	return "";
}



//***********************************
//Name:underAttack
//Input: Board* board
//Output: bool
//Description: checks if there is chess
//***********************************
bool Piece::underAttack(Board* board, int team, std::string dest)
{
	int j, yEdge;
	std::string indexToCheck = (getTeam() == team) ? getIndex() : dest;
	if (getTeam() == 0)//white
	{
		j = -1;

		yEdge = '0';
	}
	else
	{
		j = 1;
		yEdge = '9';
	}

	string kingIndex = " ";
	string newIndex;
	bool isThreat = false;
	//check the king is in one of the axises(before)---y<=getY
	/*d*/
	newIndex = indexToCheck;
	for (int x = newIndex[0], y = newIndex[1]; (x >= 'a'&&x <= 'h') && y != yEdge; x += j, y += j)
	{
		newIndex[0] = x;
		newIndex[1] = y;
		if (isKing(newIndex, board, team))
		{
			kingIndex = newIndex;
			break;
		}
	}
	/*nd*/
	if (kingIndex == " ")
	{
		newIndex = indexToCheck;
		for (int x = newIndex[0], y = newIndex[1]; (x >= 'a'&&x <= 'h') && y != yEdge; x += j, y -= j)
		{
			newIndex[0] = x;
			newIndex[1] = y;
			if (isKing(newIndex, board, team))
			{
				kingIndex = newIndex;
				break;
			}
		}
	}
	/*x*/
	if (kingIndex == " ")
	{
		for (int i = 'h'; i >= 'a'; i--)
		{
			newIndex[0] = i;
			newIndex[1] = indexToCheck[1];
			if (isKing(newIndex, board, team))
			{
				kingIndex = newIndex;
				break;
			}

		}
	}
	/*y*/
	if (kingIndex == " ")
	{
		for (int i = getIndex()[1]; i != yEdge; i += j)
		{
			newIndex[0] = indexToCheck[0];
			newIndex[1] = i;
			if (this->isKing(newIndex, board, team))
			{
				kingIndex = newIndex;
				i = yEdge;
				break;
			}

		}
	}
	//if yes,check for threats(after)y>=getY
	if (kingIndex != " ")
	{
		isThreat = this->isThreat4King(board, kingIndex, dest);
	}

	return isThreat;
}

//***********************************
//Name:isKing
//Input: string index, Board *board,int team
//Output: bool
//Description: checks if this is the asked king
//***********************************
bool Piece::isKing(string index, Board *board, int team)
{
	bool found = false;
	if (board->getPiece(index) != nullptr)
	{
		if (tolower(board->getPiece(index)->getType()) == 'k')
		{
			if (board->getPiece(index)->getTeam() == team)
			{
				found = true;
			}
		}
	}
	return found;
}



//***********************************
//Name:isThreat4King
//Input: Board* board, std::string kingIndex,std::string dest
//Output: bool
//Description: checks if there is chess
//***********************************
bool Piece::isThreat4King(Board* board, std::string kingIndex, std::string dest)
{
	Piece * king = board->getPiece(kingIndex);
	int team = king->getTeam();
	int j = (king->getTeam()) ? -1 : 1;
	int maxY = (king->getTeam()) ? '0' : '9';
	board->kingFlag = true;
	std::string newIndex = "  ";
	Piece * temp = nullptr;
	bool threat = false;
	newIndex = getIndex();
	if (board->getPiece(newIndex)->getTeam() != king->getTeam())
	{
		if (board->getPiece(newIndex)->move(board, newIndex, dest) == "0")
		{
			board->completeMove(newIndex, dest);
			if (board->getPiece(dest)->move(board, dest, kingIndex) == "0")
			{
				threat = true;

			}
			board->completeMove(dest, newIndex);
		}
	}
	if (!threat)
	{
		for (int y = kingIndex[1]; y != maxY; y += j)
		{
			for (int x = 'a'; x <= 'h'; x++)
			{
				newIndex[0] = x;
				newIndex[1] = y;
				temp = board->getPiece(newIndex);
				if (temp != nullptr)
				{
					if (temp->getTeam() != team)
					{
						if (newIndex != this->getIndex())
						{
							threat = (temp->move(board, newIndex, this->getIndex()) == "0");
						}
						if (threat)
						{
							if (newIndex != this->getIndex())
							{
								threat = (temp->move(board, this->getIndex(), kingIndex) == "0");
							}
						}
						if (threat)
						{
							x = 'h';
							y = maxY - j;
							break;
						}
					}
				}
			}
		}
	}
	board->kingFlag = false;
	return threat;
}



//***********************************
//Name:moveManager
//Input: Board* board, std::string kingIndex,std::string dest
//Output: std::string
//Description: the move control
//***********************************
std::string Piece::moveManager(Board* board, string source, string newIndex)
{
	std::string movingFlag = "0";
	if (underAttack(board, getTeam(), newIndex))
	{
		movingFlag = "4";
	}
	if (movingFlag == "0")
	{

		if (underAttack(board, ((getTeam() == 0) ? 1 : (getTeam() == 1) ? 0 : 0), newIndex))
		{
			movingFlag = "1";
		}

	}
	if (movingFlag == "0")
	{
		movingFlag = board->getPiece(source)->move(board, source, newIndex);
	}
	return movingFlag;
}

