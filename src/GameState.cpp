/*
 * GameState.cpp
 *
 *  Created on: Nov 14, 2011
 *      Author: joey
 */

#include "GameState.h"

#include <cstdlib>
#include <cstring>

#include <iostream>
#include <vector>
using namespace std;

float GameState::komi = 7.5;

GameState::GameState()
{
	size = 0;
	bs = NULL;
}

GameState::GameState(int size)
{
	init(size);
}

void GameState::init(int size)
{
	this->size = size;
	if (bs)
	{
		delete bs;
	}
	bs = new BoardState(size);
	isBlackTurn = true;
}

GameState::~GameState()
{
	initialBlack.clear();
	initialWhite.clear();
	blackMoves.clear();
	whiteMoves.clear();
	size = 0;

	delete bs;
}

void GameState::clear()
{
	initialBlack.clear();
	initialWhite.clear();
	blackMoves.clear();
	whiteMoves.clear();

	init(size);
}

int GameState::getSize()
{
	return size;
}

float GameState::getKomi()
{
	return GameState::komi;
}

void GameState::setKomi(float komi)
{
	GameState::komi = komi;
}


bool GameState::play(string color, string move)
{
	bool isBlack = ( !color.empty() ? color.at(0)=='b' : isBlackTurn );

	(isBlack ? blackMoves : whiteMoves).push_back(move);

	bool valid = true;

	// if not pass or resign
	if (move.size()<4)
	{
		valid = bs->playStone(
				atoi( move.substr(1, move.length()-1).c_str() ),
				move.at(0),
				isBlack);
	}

	if (valid)
	{
		isBlackTurn = !isBlack;
	}

	return valid;
}

bool GameState::undo()
{
	// did the last guy make a move? (or start of game)
	bool canUndo = (!isBlackTurn ? blackMoves : whiteMoves).size() > 0;

	if ( canUndo )
	{
		// clear board
		delete bs;
		bs = new BoardState(size);

		// set turn back
		isBlackTurn = !isBlackTurn;

		// remove last move from history
		(isBlackTurn ? blackMoves : whiteMoves).pop_back();

		vector<string>::iterator it;

		// place black stones
		for (it=initialBlack.begin(); it<initialBlack.end(); it++)
		{
			bs->putStone(
					atoi( (*it).substr(1, (*it).length()-1).c_str() ),
					(*it).at(0),
					true);
		}

		// place white stones
		for (it=initialWhite.begin(); it<initialWhite.end(); it++)
		{
			bs->putStone(
					atoi( (*it).substr(1, (*it).length()-1).c_str() ),
					(*it).at(0),
					false);
		}

		// replay up to undo
		vector<string>::iterator itb = blackMoves.begin();
		vector<string>::iterator itw = whiteMoves.begin();
		bool blackTurn = true;
		while (itb<blackMoves.end() || itw<whiteMoves.end())
		{
			it = (blackTurn ? itb : itw);
			bs->playStone(
					atoi( (*it).substr(1, (*it).length()-1).c_str() ),
					(*it).at(0),
					blackTurn);
			(blackTurn ? itb : itw)++;
			blackTurn = !blackTurn;
		}
	} // end can undo?

	return canUndo;
}


const string GameState::toString()
{
	return bs->toString();
}

BoardState* GameState::getBoardState()
{
	return bs;
}
