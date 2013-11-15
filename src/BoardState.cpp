/*
 * BoardState.cpp
 *
 *  Created on: Nov 14, 2011
 *      Author: joey
 */

#include "BoardState.h"
#include "util.h"
#include "complexOpps.h"
#include "GameState.h"
#include <sstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

BoardState::BoardState(int boardWidth)
{
	blackCaptured = 0;
	whiteCaptured = 0;
	black = new BitBoard(boardWidth);
	white = new BitBoard(boardWidth);
	dead = new BitBoard(boardWidth);
}

BoardState::BoardState(const BoardState* bs)
{
	blackCaptured = bs->blackCaptured;
	whiteCaptured = bs->whiteCaptured;
	black = new BitBoard( *(bs->black) );
	white = new BitBoard( *(bs->white) );
	dead = new BitBoard( *(bs->dead) );
}

BoardState::~BoardState()
{
	delete black;
	delete white;
	delete dead;
}

const string BoardState::toString()
{
	string s;

	int mod = 0;
	if (black->getBoardWidth()>('I'-'A'))
	{
		mod = 1;
	}

	for (int r = black->getBoardWidth(); r >= 1; --r)
	{
		for (char c = 'A'; c < black->getBoardWidth()+'A'+mod; ++c)
		{
			if (c=='I') ++c;

			char sym = '.';

			if (black->get(r, c)) sym = 'x';
			else if (white->get(r, c)) sym = 'o';

			s.append(1, sym);
			s.append(1, ' ');
		}
		char buffer[3];
		sprintf(buffer, "%d", r);
		s.append(buffer);
		s.append(1, '\n');
	}
	for (char c = 'A'; c < black->getBoardWidth()+'A'+mod; ++c)
	{
		if (c=='I') ++c;
		s.append(1, c);
		s.append(1, ' ');
	}

	char buffer[100];
	sprintf(buffer, "\nWhite (o) has captured %d stones.\nBlack (x) has captured %d stones.", blackCaptured, whiteCaptured);
	s.append(buffer);

	return s;
}


void BoardState::putStone(int i, bool isBlack)
{
	(isBlack ? black : white)->putStone(i);
}

void BoardState::putStone(int r, char c, bool isBlack)
{
	(isBlack ? black : white)->putStone(r, c);
}


void BoardState::removeStone(int r, char c, bool isBlack)
{
	(isBlack ? black : white)->removeStone(r, c);
}

void BoardState::removeStone(int i, bool isBlack)
{
	(isBlack ? black : white)->removeStone(i);
}


bool BoardState::playStone(int r, char c, bool isBlack)
{
	int i = util::getIndex(r, c, black->getBoardWidth());

	return playStone(i, isBlack);
}

bool BoardState::basicValidation(int i) const
{
	return ! ( black->get(i) || white->get(i) ) && !isKo(i);
}

bool BoardState::playStone(int i, bool isBlack)
{
	// is empty?
	bool valid = basicValidation(i);

	if (valid)
	{
		// play stone
		putStone(i, isBlack);

		// store copy of dead for undo
		BitBoard *oldDead = new BitBoard(*dead);

		// remove dead
		removeDead(isBlack);

		// test suicide
		valid = !isSuicide(isBlack, i);

		// undo if needed
		if (valid)
		{
			delete oldDead;
			int deadCount = dead->bitCount();
			wasCapture = deadCount > 0;
			(isBlack ? whiteCaptured : blackCaptured) += deadCount;
		}
		else
		{
			undo(i, isBlack, oldDead);
		}
	}

	return valid;
}



// TODO: capture is messed up!!! ahhhh
void BoardState::removeDead(bool isBlack)
{
	BitBoard* defender = (isBlack ? white : black);
	BitBoard* attacker = (isBlack ? black : white);

	// Find stones adjacent to liberties ( defender = explodeContaining(liberties, origDefender) )
	BitBoard* stonesWithLiberties = complexOpps::findStonesWithLiberties(attacker, defender);

	// Store dead stones
	*dead = (*defender) & ~(*stonesWithLiberties);

	// Replace defender with stonesWithLiberties
	if (isBlack)
	{
		*white = *stonesWithLiberties;
	}
	else
	{
		*black = *stonesWithLiberties;
	}

	delete stonesWithLiberties;
}

bool BoardState::isSuicide(bool isBlack, int i)
{
	bool suicide = false;

	BitBoard* attacker = (isBlack ? white : black);
	BitBoard* defender = (isBlack ? black : white);

	BitBoard* stonesWithLiberties = complexOpps::findStonesWithLiberties(attacker, defender);

	suicide = stonesWithLiberties->bitCount() != defender->bitCount();
	delete stonesWithLiberties;

	return suicide;
}

bool BoardState::isKo(int i) const
{
	return dead->get(i) && dead->bitCount()==1;
}

void BoardState::undo(int i, bool isBlack, BitBoard *oldDead)
{
	removeStone(i, isBlack);

	// put dead stones back
	if (isBlack)
	{
		*white |= *dead;
	}
	else
	{
		*black |= *dead;
	}

	// restore oldDead
	delete dead;
	dead = oldDead;
}

float* BoardState::scoresArea()
{
	float* scores = new float[2];

	BitBoard* blackArea = complexOpps::fullExpandBlocking(black, white);
	BitBoard* whiteArea = complexOpps::fullExpandBlocking(white, black);
	BitBoard notneutral = ~(*blackArea & *whiteArea);

	*blackArea &= notneutral & (~*black);
	*whiteArea &= notneutral & (~*white);

	// area scoring
	scores[0] = blackArea->bitCount() + black->bitCount();
	scores[1] = whiteArea->bitCount() + white->bitCount() + GameState::getKomi();

	delete blackArea;
	delete whiteArea;

	return scores;
}

float* BoardState::scoresTerritory()
{
	float* scores = new float[2];

	BitBoard* blackArea = complexOpps::fullExpandBlocking(black, white);
	BitBoard* whiteArea = complexOpps::fullExpandBlocking(white, black);
	BitBoard notneutral = ~(*blackArea & *whiteArea);

	*blackArea &= notneutral & (~*black);
	*whiteArea &= notneutral & (~*white);

	// territory scoring
	scores[0] = blackArea->bitCount() + whiteCaptured;
	scores[1] = whiteArea->bitCount() + blackCaptured + GameState::getKomi();

	delete blackArea;
	delete whiteArea;

	return scores;
}

float* BoardState::scoresEval()
{
	float* scores = new float[2];

	BitBoard* blackArea = complexOpps::fullExpandBlocking(black, white);
	BitBoard* whiteArea = complexOpps::fullExpandBlocking(white, black);
	BitBoard notneutral = ~(*blackArea & *whiteArea);

	*blackArea &= notneutral & (~*black);
	*whiteArea &= notneutral & (~*white);

	scores[0] = blackArea->bitCount() + whiteCaptured;
	scores[1] = whiteArea->bitCount() + blackCaptured;

	delete blackArea;
	delete whiteArea;

	return scores;
}

BitBoard* BoardState::getBlack() const
{
	return black;
}

BitBoard* BoardState::getWhite() const
{
	return white;
}

BitBoard* BoardState::getDead()
{
	return dead;
}

int BoardState::getBoardWidth() const
{
	return black->getBoardWidth();
}

bool BoardState::wasCapturep()
{
	return wasCapture;
}

bool BoardState::equals(const BoardState* bs2) const
{
	return blackCaptured==bs2->blackCaptured
			&& whiteCaptured==bs2->whiteCaptured
			&& black->equals(bs2->black)
			&& white->equals(bs2->white)
			&& dead->equals(bs2->dead);
}
