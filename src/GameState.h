/*
 * GameState.h
 *
 *  Created on: Nov 14, 2011
 *      Author: joey
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <vector>
#include <string>
#include "BoardState.h"

#include <iostream>
using namespace std;

class GameState
{
private:
	vector<string> initialWhite;
	vector<string> initialBlack;
	vector<string> blackMoves;
	vector<string> whiteMoves;
	BoardState * bs;
	int size;
	static float komi;
	bool isBlackTurn;
public:
	GameState(int size);
	GameState();
	virtual ~GameState();

	void init(int size);
	void clear();

	const string toString();
	int getSize();
	static float getKomi();
	static void setKomi(float komi);

	bool play(string color, string move);
	bool undo();

	BoardState * getBoardState();
};


#endif /* GAMESTATE_H_ */
