#include "stdafx.h"
#include "Pipe.h"
#include <iostream>
#include <thread>

#define SOURCE 2
#define DEST 3

void main()
{
	int turn = 0;
	int exchangeTurn = 0;
	string source = "";
	string result = "";
	string destination = "";
	Piece* currPiece;

	srand(time_t(NULL));

	Pipe p;
	bool isConnect = p.connect();

	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return;
		}
	}


	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	// YOUR CODE

	strcpy_s(msgToGraphics, "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0"); //initiates the graphic board

	p.sendMessageToGraphics(msgToGraphics);   // send the board string

											  // get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	Board* board = new Board();

	while (msgFromGraphics != "quit")
	{
		exchangeTurn = 0;

		source = msgFromGraphics.substr(0, SOURCE);  //Gets the value of the source inlay
		destination = msgFromGraphics.substr(SOURCE, DEST);  //Gets the value of the destination inlay
		currPiece = board->getPiece(source); //Gets the piece which is on the source inlay
		if (currPiece == nullptr)  //Checks if the piece exists
		{
			result = "2";
		}
		else if (currPiece->getTeam() != turn)
		{
			result = "2";
		}
		else
		{
			result = currPiece->moveManager(board, source, destination);
		}


		if (strcmp(result.c_str(), "0") == 0 || strcmp(result.c_str(), "1") == 0)  //Checks if there is going to be a movement of the piece
		{
			exchangeTurn = 1;  //Gives the permission to exchange te turn.
			board->deleteEaten(destination); //Deletes the piece which is in the new index (if there is a piece)
			board->completeMove(source, destination); //Changes the board according the movement
		}

		strcpy_s(msgToGraphics, result.c_str()); // msgToGraphics should contain the result of the operation

		p.sendMessageToGraphics(msgToGraphics);   // return result to graphics	

		board->printBoard();  //Prints the updated board
		if (exchangeTurn == 1)  //Checks if there is a permission to exchange the turn
		{
			if (turn == 0)  //exchanges the turn
			{
				turn = 1;
			}
			else
			{
				turn = 0;
			}
		}

		msgFromGraphics = p.getMessageFromGraphics();// get message from graphics

	}

	delete board;
	p.close();
}