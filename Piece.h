#pragma once
#include "Board.h"
#include <iostream>
using namespace std;
class Board;
class Piece
{
public:
	Piece(char type, string index);
	~Piece();
	int getTeam();
	char getType();
	string getIndex();
	void setIndex(string newIndex);
	virtual string move(Board* board, string source, string newIndex) = 0;

	bool underAttack(Board* board, int team, std::string dest);
	bool isKing(string index, Board *board, int team);
	bool isThreat4King(Board* board, std::string kingIndex, std::string dest);
	std::string moveManager(Board* board, string source, string newIndex);

protected:
	static int makeAbsoluteValue(int value);
	string basicChecks(Board* board, string newIndex);

private:
	int _team;
	char _type;
	string _index;

};

