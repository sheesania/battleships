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

class Ship {
	public:
		int row;
		int col;
		int length;
	  Direction direction;
		double score;

		bool operator<(const Ship &ship) const;
};

class Point {
	public:
		int row;
		int col;
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
			int shipPlacementScoring[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
      int currentRound; //how many rounds we have played up to this one
      void initializeProbMap(int probMap[MAX_BOARD_SIZE][MAX_BOARD_SIZE]); //populate a probability map with intial values
      void initializeShipsPlaced();
      Ship scoreShipPlacement(Ship ship);
      vector<Ship> getScoreAdjustedPositions(vector<Ship> positions);
      void updatePlacedShips(Ship ship);
			vector<Point> hits;

			Point findOpenSpaceRight(int row, int col);
			Point findOpenSpaceLeft(int row, int col);
			Point findOpenSpaceUp(int row, int col);
			Point findOpenSpaceDown(int row, int col);
			Point emptyPoint;
			int killCount;

    	void initializeBoard();
      int lastRow;
      int lastCol;
	    int numShipsPlaced;
			int attackMap[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
			int attackProbabilities[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
			vector<int> shipLengths;
			void missed(int row, int col);
			bool onBoard(int x);
			bool onBoard(int x, int y);
			int getAttackMax();
      char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
};

#endif
