/*
 * AI.cpp
 *
 *  Created on: Nov 14, 2011
 *      Author: joey
 */

#include "AI.h"
#include <string>
#include <cstring>
#include "../config.h"
#include <cstdlib>
#include "MCAgent.h"
#include "MCUCTAgent.h"

#include <stdio.h>
#include <iostream>
using namespace std;

AI::AI(GameState * gs)
 : gs(gs)
{
	if ( config::agentType.compare("mc")==0 )
	{
		agent = new MCAgent();
	}
	else if ( config::agentType.compare("mcuct")==0 )
	{
		agent = new MCUCTAgent();
	}
	else
	{
		agent = NULL;
	}
}

AI::~AI()
{
	delete agent;
}

bool AI::process(vector<string> command, char response[])
{
	bool success = true;

	if (command.at(0).compare("play")==0)
	{
		if (command.size()==3)
		{
			success = gs->play(command.at(1), command.at(2));
		}
		else
		{
			string s;
			success = gs->play(s, command.at(1));
		}

		if (!success)
		{
			strcpy(response, "not a valid move");
		}
	}
	else if (command.at(0).compare("genmove")==0)
	{
		string s = agent->genmove(gs->getBoardState(), command.at(1));
		gs->play(command.at(1), s);
		strcpy(response, s.c_str());
	}
	else if (command.at(0).compare("reg_genmove")==0)
	{
		string s = agent->genmove(gs->getBoardState(), command.at(1));
		strcpy(response, s.c_str());
	}
	else if (command.at(0).compare("undo")==0)
	{
		if ( ! gs->undo() )
		{
			strcpy(response, "cannot undo");
		}
	}
	else if (command.at(0).compare("final_score")==0)
	{
		float* scores;
		if (strcmp(config::scoring.c_str(), "territory"))
		{
			scores = gs->getBoardState()->scoresTerritory();
		}
		else
		{
			scores = gs->getBoardState()->scoresArea();
		}

		if (scores[0]>scores[1])
		{
			sprintf(response, "B+%.1f", (scores[0]-scores[1]));
		}
		else if (scores[0]<scores[1])
		{
			sprintf(response, "W+%.1f", (scores[1]-scores[0]));
		}
		else
		{
			sprintf(response, "0");
		}

		delete[] scores;
	}
	else if (command.at(0).compare("explain")==0)
	{
		agent->explain();
	}
	else
	{
		strcpy(response, "not implemented ai");
	}
	return success;
}
