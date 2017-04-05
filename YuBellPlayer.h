/**
 * @author Edric Yu, Alison Bell
 * @date April 2017
 *
 */

#ifndef YUBELLPLAYER_H		// Double inclusion protection
#define YUBELLPLAYER_H

using namespace std;

#include "PlayerV2.h"
#include "Message.h"
#include "defines.h"

struct Ship {
	int row;
	int col;
	int length;
  Direction direction;
	int score;
};

class YuBellPlayer: public PlayerV2 {
    public:
    	YuBellPlayer( int boardSize );
    	~YuBellPlayer();
    	void newRound();
    	Message placeShip(int length);
    	Message getMove();
    	void update(Message msg);

      //testing and debugging functions
      void printProbMap();
      void printShipsPlaced();

    private:

      int opponentsHits[MAX_BOARD_SIZE][MAX_BOARD_SIZE]; //where the opponent has shot
      int shipsPlaced[MAX_BOARD_SIZE][MAX_BOARD_SIZE]; //where we have placed ships this round
      void initializeProbMap(int probMap[MAX_BOARD_SIZE][MAX_BOARD_SIZE]); //populate a probability map with intial values
      void initializeShipsPlaced();
      Ship scoreShipPlacement(Ship ship);
      vector<Ship> getScoreAdjustedPositions(vector<Ship> positions);

    	void initializeBoard();
      int lastRow;
      int lastCol;
	    int numShipsPlaced;
      char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
};

#endif
