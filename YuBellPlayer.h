/**
 * @author Stefan Brandle, Jonathan Geisler
 * @date September, 2004
 *
 * Please type in your name[s] here:
 *
 */

#ifndef YUBELLPLAYER_H		// Double inclusion protection
#define YUBELLPLAYER_H

using namespace std;

#include "PlayerV2.h"
#include "Message.h"
#include "defines.h"

// DumbPlayer inherits from/extends PlayerV2

class YuBellPlayer: public PlayerV2 {
    public:
	YuBellPlayer( int boardSize );
	~YuBellPlayer();
	void newRound();
	Message placeShip(int length);
	Message getMove();
	void update(Message msg);

  void printProbMap(); //for testing

    private:

  int opponentsHits[MAX_BOARD_SIZE][MAX_BOARD_SIZE]; //where the opponent has shot
  void initializeProbMap(int probMap[MAX_BOARD_SIZE][MAX_BOARD_SIZE]); //populate a probability map with intial values

	void initializeBoard();
        int lastRow;
        int lastCol;
	int numShipsPlaced;
        char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
};

#endif
