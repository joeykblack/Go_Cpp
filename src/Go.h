//============================================================================
// Name        : Go.cpp
// Author      : Joey Black (joeykblack@gmail.com)
// Version     : 0
// Copyright   : My copyright notice
// Description : Entry point for Go program
//============================================================================



#ifndef GO_H_
#define GO_H_

#include "ai/AI.h"
#include "GameState.h"
#include "config.h"
#include "SysCommands.h"
#include "SetupCommands.h"
#include <ctype.h>
#include <cstring>

#include "parser.h"
#include "util.h"

#include <iostream>
using namespace std;


/*
 * --- Main ---
 */

int gtpMain()
{
	GameState* gs = new GameState;
	AI* ai = new AI(gs);
	SysCommands* sys = new SysCommands(gs);
	SetupCommands* setup = new SetupCommands(gs);

	srand(time(0));

//	setup for testing
	gs->init(9);

	char* buffer = new char[256];
	char* response = new char[5000];

	while (true)
	{
		memset(buffer, ' ', 256);
		buffer[0] = '\0';
		memset(response, ' ', 5000);
		buffer[0] = '\0';

		cin.getline(buffer, 256);
		util::stringtolower(buffer);

		int id = util::removeid(buffer);

		util::clean(buffer);

		vector<string> command = parser::parseInput(buffer);

		// get response
		response[0] = '\0';
		bool success = true;
		if (command.size()>0 && command.at(0).length()>0)
		{
			if (util::arrayContains(config::sys_commands,
					config::sys_commands_len, command.at(0)))
			{
				success = sys->process(command, response);
			}
			else if (util::arrayContains(config::setup_commands,
					config::setup_commands_len, command.at(0)))
			{
				success = setup->process(command, response);
			}
			else if (util::arrayContains(config::ai_commands,
					config::ai_commands_len, command.at(0)))
			{
				success = ai->process(command, response);
			}
			else
			{
				strcpy(response, config::error);
				success = false;
			}

			if (success)
			{
				cout << '=';
			}
			else
			{
				cout << '?';
			}

			if (id != -1)
			{
				cout << id;
			}
			if (strlen(response)>0)
			{
				cout << ' ' << response;
			}
			cout << endl << endl;
		}

		if (command.size()>0
				&& strcmp(command.at(0).c_str(), config::quit) == 0)
		{
			break;
		}
	}

	delete[] buffer;
	delete[] response;
	delete setup;
	delete sys;
	delete ai;
	delete gs;

	return 0;
}

#endif
