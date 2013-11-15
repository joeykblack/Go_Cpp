/*
 * UCTNode.cpp
 *
 *  Created on: Feb 29, 2012
 *      Author: joey
 */

#include "UCTNode.h"

#include "RndPlayer.h"
#include "../config.h"
#include "../util.h"

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


UCTNode::UCTNode(BoardState* bs, int index, bool isBlack)
{
	this->isBlack = !isBlack;
	this->index = index;
	this->bs = new BoardState(bs);

	valid = this->bs->playStone(index, this->isBlack); // move was not already made

	children = NULL;
	numChildren = -1;
	wins = 0;
	visits = 0;
	resign = false;
	pass = false;
}

// root
UCTNode::UCTNode(BoardState* bs, bool isBlack)
{
	this->isBlack = !isBlack; // root is last player's move
	this->index = -1; // we don't care what they did
	this->bs = new BoardState(bs); // move was already made

	valid = true; // it must have been valid

	children = NULL;
	numChildren = -1;
	wins = 0;
	visits = 0;
	resign = false;
	pass = false;
}

UCTNode::~UCTNode()
{
	if (numChildren != -1)
	{
		for (int i=0; i<numChildren; i++)
		{
			delete children[i];
		}
		delete[] children;
	}
	delete bs;
}


UCTNode* UCTNode::repointBestMove(UCTNode* bestMove)
{
	UCTNode* newRoot = NULL;

	if (numChildren != -1)
	{
		for (int i=0; i<numChildren; i++)
		{
			if (children[i] == bestMove)
			{
				newRoot = children[i];
			}
			else
			{
				delete children[i];
			}
		}
		delete[] children;
	}
	numChildren = -1; // children already deleted

	return newRoot;
}


UCTNode* UCTNode::repointRoot(const BoardState* bs2)
{
	UCTNode* newRoot = NULL;

	if (numChildren != -1)
	{
		for (int i=0; i<numChildren; i++)
		{
			if (children[i]->getBoardState()->equals(bs2))
			{
				newRoot = children[i];
			}
			else
			{
				delete children[i];
			}
		}
		delete[] children;
	}
	numChildren = -1;  // children already deleted

	return newRoot;
}


bool UCTNode::visit(RAVEManager* rave)
{
	bool isWin = false;

	if (visits < config::expandPoint)
	{
		RndPlayer rndPlayer;
//		isWin = (rndPlayer.playRaveGame(bs, isBlack, rave) == isBlack);
//		isWin = (rndPlayer.playRandomGame(bs, isBlack) == isBlack);
		isWin = (rndPlayer.playGreedyGame(bs, isBlack) == isBlack);
	}
	else
	{
		if (children == NULL)
		{
			createChildren();
		}

		UCTNode* best = selectChild(*rave);
		isWin = (best!=NULL ? !best->visit(rave) : true);
	}

	if (config::raveMod>0) rave->update(index, (isWin ? 1 : 0));

	wins += (isWin ? 1 : 0);
	visits++;

	return isWin;
}

void UCTNode::visitChildren(RAVEManager* rave)
{
	if (children == NULL)
	{
		createChildren();
	}

	if (numChildren>0)
	{
		UCTNode* best = selectChild(*rave);
		if (best!=NULL)
		{
			best->visit(rave);
		}
	}
	visits++;
}

void UCTNode::createChildren()
{
	BitBoard empty( ~*(bs->getBlack()) & ~*(bs->getWhite()) );
	UCTNode** c = new UCTNode*[empty.bitCount()];

	int limit = empty.getBoardWidth() * empty.getBoardWidth();
	int ci = 0;
	for (int i = 0; i < limit; i++)
	{
		if (empty.get(i))
		{
			c[ci] = new UCTNode(bs, i, isBlack);
			ci++;
		}
	}
	numChildren = ci;

	children = c;
}

// null=pass
UCTNode* UCTNode::selectChild(const RAVEManager& rave)
{
	double bestuct = 0;
	UCTNode* result = NULL;
	double uctValue = 0;

	for (int i = 0; i < numChildren; ++i)
	{
		UCTNode* next = children[i];

		if (next->valid)
		{
			if (next->visits > 0) // || rave.getVisits(next->index) > config::visitsBeforeTrust)
			{
				double winrate = (next->visits>0) ? (double)next->wins/next->visits : 0;
				double uct = getUct(next);
//				double custom = customMod(next);
				double r = (config::raveMod>0) ? config::raveMod * rave.getValue(next->index) : 0;
				uctValue = winrate + uct + r;// + custom;
			}
			else
			{
				uctValue = 10000 + (rand()%1000);
			}

			if (uctValue > bestuct)
			{
				bestuct = uctValue;
				result = next;
			}
		}
	}

	return result;
}

void UCTNode::showUCTValues(const RAVEManager& rave)
{
	int size = bs->getBoardWidth();
	for (int i = 0; i < numChildren; ++i)
	{
		UCTNode* next = children[i];

		double uctValue = 0;
		double winrate = 0;
		double r = 0;
		double uct = 0;
		double custom = 0;
		if (next->visits > 0)
		{
			winrate = (double)next->wins/next->visits;
			uct = getUct(next);
			r = (config::raveMod>0) ? config::raveMod * rave.getValue(next->index) : 0;
			custom = customMod(next);
			uctValue = winrate + uct + r + custom;
		}

		cout << util::getPos(next->index, size);
		printf(" uct: %8.4f  winrate: %8.4f  rave: %8.4f custom %8.4f total %8.4f visits: %8d rave wins: %8d rave visits: %8d\n",
				uct, winrate, r, custom, uctValue, next->visits,
				rave.getWins(next->index), rave.getVisits(next->index) );
	}
	cout << "total visits to root: " << visits << endl;
}


// null==pass
// resign?
UCTNode* UCTNode::getBestMove()
{
	double bestrate = 0;
	double worstrate = 100000;
	UCTNode* result = NULL;
	UCTNode* worst = NULL;
	double winrate = 0;

	for (int i = 0; i < numChildren; ++i)
	{
		UCTNode* next = children[i];

		if (next->valid && next->visits > 0)
		{
//			winrate = (double)next->wins/next->visits + customMod(next);
			winrate = next->visits;

			if (winrate > bestrate)
			{
				bestrate = winrate;
				result = next;
			}

			if (winrate < worstrate)
			{
				worstrate = winrate;
				worst = next;
			}
		}
	}

	bestrate = (double)result->wins/result->visits;
	worstrate = (double)worst->wins/worst->visits;
	if (result!=NULL && bestrate <= config::resign)
	{
		result->resign = true;
	}
	else if (result != NULL && worstrate >= config::pass)
	{
		result->pass = true;
	}

	return result;
}

bool UCTNode::isResign()
{
	return resign;
}

bool UCTNode::isPass()
{
	return pass;
}

int UCTNode::getMove()
{
	return index;
}

int UCTNode::getVisits()
{
	return visits;
}

double UCTNode::getUct(UCTNode* next)
{
	return (next->visits>0) ? config::UCTK * sqrt( log(visits) / (5 * next->visits) ) : 0;
}

double UCTNode::customMod(UCTNode* next)
{
	double mod = 0;
	int i = next->index;
	int width = bs->getBoardWidth();

	if (i!=-1 &&
			(i < width || i > ((width-1)*width)
					|| i%width==0 || i%width==(width-1)))
	{
		mod = -0.02;
	}

	return mod;
}

int UCTNode::getNumChildren()
{
	return numChildren;
}

UCTNode* UCTNode::getChild(int index)
{
	return children[index];
}

BoardState* UCTNode::getBoardState()
{
	return bs;
}
