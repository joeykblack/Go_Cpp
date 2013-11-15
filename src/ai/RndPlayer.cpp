/*
 * RndPlayer.cpp
 *
 *  Created on: Jan 3, 2012
 *      Author: joey
 */

#include "RndPlayer.h"
#include <stdlib.h>
#include "../config.h"
#include "../complexOpps.h"
#include <vector>
#include <list>
#include <deque>
#include <functional>
#include <algorithm>

#include <iostream>
using namespace std;


RndPlayer::RndPlayer()
{
}

bool RndPlayer::playRandomGame(const BoardState* bs, bool isBlack)
{
	BoardState temp(bs);

	// only try to fill 'percentFull' of board
	int size = temp.getBoardWidth()*temp.getBoardWidth();
	int limit = (config::percentFull * size) - temp.getBlack()->bitCount() - temp.getWhite()->bitCount();
	for (int move = 0; move < limit; ++move)
	{
		isBlack = !isBlack;
		int i=0;
		int index;
		bool madePlay;
		do {
			i++;
			index = rand() % size;
			madePlay = temp.playStone(index, isBlack);
		} while ( !madePlay  && i<size );

		if (!madePlay) break; // board must be full
	}

	float* scores = temp.scoresEval();
	bool blackWins = scores[0]>scores[1];
	delete[] scores;

	return blackWins;
}


// TODO: find better capture algorithm
int RndPlayer::findRandomCapture(const BoardState* bs, bool isBlack, int size)
{
	vector<int> valid;

	BitBoard* opp = (isBlack) ? bs->getWhite() : bs->getBlack();
	BitBoard* me = (isBlack) ? bs->getBlack() : bs->getWhite();
	BitBoard* attacks = complexOpps::findLibertiesAdjacentStones(opp, me);
	BitBoard empty;
	empty = ~(*opp | *me);

	int index = -1;

	if (attacks->bitCount()>0)
	{
		int i;
		for (i = 0; i < size; ++i)
		{
			if (attacks->get(i))
			{
				BoardState temp(bs);
				if (temp.playStone(i, isBlack) && temp.wasCapturep())
				{
					index = i;
					break;
				}
			}
			else if (empty.get(i))
			{
				valid.push_back(i);
			}
		}
	}

	delete attacks;

	if (index == -1 && valid.size()>0)
	{
		return valid.at(rand() % valid.size());
	}

	return index;
}


bool RndPlayer::playGreedyGame(const BoardState* bs, bool isBlack)
{
	BoardState temp(bs);

	// only try to fill 'percentFull' of board
	int size = temp.getBoardWidth()*temp.getBoardWidth();
	int limit = (config::percentFull * size) - temp.getBlack()->bitCount() - temp.getWhite()->bitCount();

	for (int move = 0; move < limit; ++move)
	{
		isBlack = !isBlack;
		bool madePlay = false;

		int index = findRandomCapture(&temp, isBlack, size);
		if (index != -1)
		{
			madePlay = temp.playStone(index, isBlack); // slight chance of being invalid if suicide
		}

		if (!madePlay)
		{
			int i=0;
			do {
				i++;
				index = rand() % size;
				madePlay = temp.playStone(index, isBlack);
			}
			while ( !madePlay  && i<size );

			if (!madePlay) break; // board must be full
		}
	}

	float* scores = temp.scoresEval();
	bool blackWins = scores[0]>scores[1];
	delete[] scores;

	return blackWins;
}




struct comparer {
	RAVEManager* _rave;
	bool operator() (int a, int b)
	{
		return _rave->getValue(a) > _rave->getValue(b);
	}
} comp;

bool RndPlayer::playRaveGame(const BoardState* bs, bool isBlack, RAVEManager* rave)
{
	list<int> moves;
	int size = bs->getBoardWidth()*bs->getBoardWidth();
	int i;
	int count = 0;
	for (i = 0; i < size; i++)
	{
		moves.push_back(i);
		count += rave->getVisits(i);
	}

	if (count < (size * config::visitsBeforeTrust))
	{
		return playRandomGame(bs, isBlack);
	}

	comp._rave = rave;
	moves.sort(comp);

	BoardState temp(bs);

	// only try to fill 'percentFull' of board
	int limit = (config::percentFull * size) - temp.getBlack()->bitCount() - temp.getWhite()->bitCount();
	for (int move = 0; move < limit && moves.size() > 0; ++move)
	{
		isBlack = !isBlack;
		int rndIndex;
		bool madePlay;
		do {
			rndIndex = (moves.size()>10) ? rand()%10 : rand()%moves.size();
			list<int>::iterator it = moves.begin();
			advance(it, rndIndex);
			int index = *it;
			madePlay = temp.playStone(index, isBlack);
			moves.erase(it);
		} while ( !madePlay && moves.size()>0);

		if (!madePlay) break; // board must be full
	}

	float* scores = temp.scoresEval();
	bool blackWins = scores[0]>scores[1];
	delete[] scores;

	return blackWins;
}

