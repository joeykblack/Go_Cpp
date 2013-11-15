/*
 * MCUCTAgent.cpp
 *
 *  Created on: Feb 29, 2012
 *      Author: joey
 */

#include "MCUCTAgent.h"

#include "RAVEManager.h"

#include "../util.h"
#include "../config.h"

#include <time.h>
#include <stdio.h>
#include <iostream>
using namespace std;


MCUCTAgent::MCUCTAgent()
{
	root = NULL;
	bestMove = NULL;
	rave = NULL;
}

MCUCTAgent::~MCUCTAgent()
{
	if (root != NULL)
	{
		delete root;
	}

	if (rave != NULL)
	{
		delete rave;
	}
}


string MCUCTAgent::genmove(BoardState* bs, string color)
{
	time_t start;
	time(&start);

	bool isBlack = ( !color.empty() ? color.at(0)=='b' : false );

	// re-point root to bestMove delete other children
	if (root != NULL)
	{
		UCTNode* newroot = root->repointBestMove(bestMove);
		delete root;
		root = newroot;
	}

	// re-point root to move opponent chose
	if (root != NULL)
	{
		UCTNode* newroot = root->repointRoot(bs);
		delete root;
		root = newroot;
	}

	// if no root, create a new one
	if (root == NULL)
	{
		root = new UCTNode(bs, isBlack); // current board as root
	}

	if (rave == NULL)
	{
		rave = new RAVEManager(bs->getBoardWidth());
	}

	bool timeLimmited = config::agentLimitter.compare("time")==0;

	// visit as many times as time allows
	while ( (timeLimmited ?
				difftime(time(NULL), start) < config::secondsPerMove
				: root->getVisits() < config::numberOfIterations ) )
	{
		root->visitChildren(rave);
	}

	// best based on highest win rate
	bestMove = root->getBestMove();
	string result;

	if (bestMove != NULL && bestMove->isResign())
	{
		result = "resign";
	}
	else if (bestMove == NULL || bestMove->isPass())
	{
		// no valid moves
		// or worst rate >= pass rate
		result = "pass";
	}
	else
	{
		int move = bestMove->getMove();
		result = util::getPos(move, bs->getBoardWidth());
	}

	return result;
}


void MCUCTAgent::explain()
{
	root->showUCTValues(*rave);

}



