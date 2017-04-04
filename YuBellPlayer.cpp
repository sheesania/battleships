/**
 * @brief AI for battleships
 * @file YuBellPlayer.cpp
 * @author Edric Yu, Alison Bell
 * @date April 2017
 *
 */

#include <iostream>
#include <cstdio>

#include "conio.h"
#include "YuBellPlayer.h"

using namespace conio;

/**
 * @brief Constructor that initializes any inter-round data structures.
 * @param boardSize Indication of the size of the board that is in use.
 *
 * The constructor runs when the AI is instantiated (the object gets created)
 * and is responsible for initializing everything that needs to be initialized
 * before any of the rounds happen. The constructor does not get called
 * before rounds; newRound() gets called before every round.
 */
YuBellPlayer::YuBellPlayer( int boardSize )
    :PlayerV2(boardSize)
{
    // Initialize inter-round structures
    initializeProbMap(this->opponentsHits);
}

/**
 * @brief Destructor placeholder.
 * If your code does anything that requires cleanup when the object is
 * destroyed, do it here in the destructor.
 */
YuBellPlayer::~YuBellPlayer( ) {}

/*
 * Private internal function that initializes a MAX_BOARD_SIZE 2D array of char to water.
 */
void YuBellPlayer::initializeBoard() {
    for(int row=0; row<boardSize; row++) {
	     for(int col=0; col<boardSize; col++) {
	        this->board[row][col] = WATER;
	     }
    }
}

void YuBellPlayer::initializeProbMap(int probMap[MAX_BOARD_SIZE][MAX_BOARD_SIZE]) {
  int edge = boardSize - 1;

	//corners
	probMap[0][0] = 2;
	probMap[0][edge] = 2;
	probMap[edge][0] = 2;
	probMap[edge][edge] = 2;

	//edges
	for (int i = 1; i < edge; i++) {
		probMap[0][i] = 3;
		probMap[edge][i] = 3;
		probMap[i][0] = 3;
		probMap[i][edge] = 3;
	}

	//the rest of the board, with increasing probabilities as we get closer to the center
	for (int round = 1; round < (boardSize/2); ++round) {
		for (int i = round; i <= edge - round; ++i) {
			probMap[round][i] = round + 3;
			probMap[i][round] = round + 3;
			probMap[edge - round][i] = round + 3;
			probMap[i][edge - round] = round + 3;
		}
	}

	//if the boardSize is odd, there will be one last center position to put a probability in
	if ((boardSize % 2) == 1) {
		probMap[boardSize/2][boardSize/2] = (boardSize/2) + 2;
	}
}

void YuBellPlayer::printProbMap() {
  for (int row = 0; row < boardSize; row++) {
		for (int col = 0; col < boardSize; col++) {
      cout << conio::gotoRowCol(20 + row, 30 + col) << opponentsHits[row][col] << " " << flush;
		}
    cout << endl;
	}
  cout << endl << endl;
}


/**
 * @brief Specifies the AI's shot choice and returns the information to the caller.
 * @return Message The most important parts of the returned message are
 * the row and column values.
 *
 * See the Message class documentation for more information on the
 * Message constructor.
 */
Message YuBellPlayer::getMove() {
    lastCol++;
    if( lastCol >= boardSize ) {
    	lastCol = 0;
    	lastRow++;
    }
    if( lastRow >= boardSize ) {
    	lastCol = 0;
    	lastRow = 0;
    }

    Message result( SHOT, lastRow, lastCol, "Bang", None, 1 );
    return result;
}

/**
 * @brief Tells the AI that a new round is beginning.
 * The AI show reinitialize any intra-round data structures.
 */
void YuBellPlayer::newRound() {
    /* DumbPlayer is too simple to do any inter-round learning. Smarter players
     * reinitialize any round-specific data structures here.
     */
    this->lastRow = 0;
    this->lastCol = -1;
    this->numShipsPlaced = 0;

    this->initializeBoard();
}

/**
 * @brief Gets the AI's ship placement choice. This is then returned to the caller.
 * @param length The length of the ship to be placed.
 * @return Message The most important parts of the returned message are
 * the direction, row, and column values.
 *
 * The parameters returned via the message are:
 * 1. the operation: must be PLACE_SHIP
 * 2. ship top row value
 * 3. ship top col value
 * 4. a string for the ship name
 * 5. direction Horizontal/Vertical (see defines.h)
 * 6. ship length (should match the length passed to placeShip)
 */
Message YuBellPlayer::placeShip(int length) {
    char shipName[10];
    // Create ship names each time called: Ship0, Ship1, Ship2, ...
    snprintf(shipName, sizeof shipName, "Ship%d", numShipsPlaced);

    // parameters = mesg type (PLACE_SHIP), row, col, a string, direction (Horizontal/Vertical)
    Message response( PLACE_SHIP, numShipsPlaced, 0, shipName, Horizontal, length );
    numShipsPlaced++;

    return response;
}

/**
 * @brief Updates the AI with the results of its shots and where the opponent is shooting.
 * @param msg Message specifying what happened + row/col as appropriate.
 */
void YuBellPlayer::update(Message msg) {
    switch(msg.getMessageType()) {
	case HIT:
	case KILL:
	case MISS:
	    board[msg.getRow()][msg.getCol()] = msg.getMessageType();
	    break;
	case WIN:
	    break;
	case LOSE:
	    break;
	case TIE:
	    break;
	case OPPONENT_SHOT:
      //update probability information about the opponent's shots
      this->opponentsHits[msg.getRow()][msg.getCol()]++;
	    break;
    }
}
