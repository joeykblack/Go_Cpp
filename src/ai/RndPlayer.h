/*
 * RndPlayer.h
 *
 *  Created on: Jan 3, 2012
 *      Author: joey
 */

#ifndef RNDPLAYER_H_
#define RNDPLAYER_H_

#include "../BoardState.h"
#include "RAVEManager.h"

class RndPlayer
{
public:
	RndPlayer();

	bool playRandomGame(const BoardState* bs, bool isBlack);

	bool playGreedyGame(const BoardState* bs, bool isBlack);
	int findRandomCapture(const BoardState* bs, bool isBlack, int size);

	bool playRaveGame(const BoardState* bs, bool isBlack, RAVEManager* rave);
};

#endif /* RNDPLAYER_H_ */
