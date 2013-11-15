/*
 * MCAgent.cpp
 *
 *  Created on: Jan 3, 2012
 *      Author: joey
 */

#include "MCAgent.h"

#include <iostream>
using namespace std;

#include "../config.h"
#include "RndPlayer.h"


MCAgent::MCAgent()
{
}

MCAgent::~MCAgent()
{
}

string MCAgent::genmove(BoardState* bs, string color)
{
	int boardWidth = bs->getBlack()->getBoardWidth();
	bool isBlack = ( !color.empty() ? color.at(0)=='b' : false );
	int mod = 0;
	if (boardWidth>('I'-'A'))
	{
		mod = 1;
	}

	int row = 0;
	char col = 'A';
	int highScore = -1;

	for (int r = 1; r <= boardWidth; ++r)
	{
		for (char c = 'A'; c < boardWidth+'A'+mod; ++c)
		{
			if (c=='I') ++c; // skip I because it is not used in go

			int wins = 0;

			BoardState temp(bs);
			RndPlayer rndPlayer;
			if (temp.playStone(r, c, isBlack))
			{
				for (int game=0; game<config::numRndGamesPerMove; ++game)
				{
					if (rndPlayer.playRandomGame(&temp, isBlack)==isBlack) wins++;
				}
			}
			else
			{
				wins = -5;
			}

			if (wins > highScore)
			{
				highScore = wins;
				row = r;
				col = c;
			}

		}
	}


	string vertex = "";
	char v[2];

	if (highScore > config::numRndGamesPerMove/4)
	{
		v[0] = col;
		v[1] = (char)(row+'0');
		vertex.append(v);
	}
	else
	{
		vertex = "pass";
	}

	return vertex;
}


void MCAgent::explain()
{
	cout << "no" << endl;
}
