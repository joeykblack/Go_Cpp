/*
 * SetupCommands.cpp
 *
 *  Created on: Nov 16, 2011
 *      Author: joey
 */

#include "SetupCommands.h"
#include "BitBoard.h"
#include <cstdlib>
#include <cstring>
#include <string>

SetupCommands::SetupCommands(GameState * gs)
 : gs(gs)
{
}

SetupCommands::~SetupCommands()
{
	cleanupBitBoard(); // this is not really good, but oh well
}


bool SetupCommands::process(vector<string> command, char response[])
{
	bool success = true;

	/*
	 * boardsize
	 */
	if (command.at(0).compare("boardsize")==0)
	{
		if (command.size()<2)
		{
			success = false;
			strcpy(response, "missing size param");
		}
		else
		{
			int size = atoi(command.at(1).c_str());
			if (size == 0)
			{
				success = false;
				strcpy(response, "unacceptable size");
			}
			else
			{
				gs->init(size);
			}
		}
	}
	/*
	 * clear_board
	 */
	else if (command.at(0).compare("clear_board")==0)
	{
		gs->clear();
	}
	/*
	 * komi
	 */
	else if (command.at(0).compare("komi")==0)
	{
		if (command.size()<2)
		{
			success = false;
			strcpy(response, "missing komi param");
		}
		else
		{
			float komi = atof(command.at(1).c_str());
			gs->setKomi(komi);
		}
	}
	/*
	 * fixed_handicap
	 */
//	else if (command.at(0).compare("fixed_handicap")==0)
//	{
//		strcpy(response, "");
//	}
//	else if (command.at(0).compare("place_free_handicap")==0)
//	{
//		strcpy(response, "");
//	}
//	else if (command.at(0).compare("set_free_handicap")==0)
//	{
//		strcpy(response, "");
//	}
	else
	{
		strcat(response, "not implemented yet (setup): ");
		strcat(response, command.at(0).c_str());
	}

	return success;
}
