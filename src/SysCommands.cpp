/*
 * SysCommands.cpp
 *
 *  Created on: Nov 15, 2011
 *      Author: joey
 */

#include "SysCommands.h"
#include "config.h"
#include "util.h"
#include <cstring>
#include <string>

#include <iostream>
using namespace std;

SysCommands::SysCommands(GameState * gs)
 : gs(gs)
{

}

SysCommands::~SysCommands()
{

}

bool SysCommands::process(vector<string> command, char response[])
{
	bool success = true;

	if (command.at(0).compare("protocol_version")==0)
	{
		strcpy(response, config::protocol_version);
	}
	else if (command.at(0).compare("name")==0)
	{
		strcpy(response, config::name);
	}
	else if (command.at(0).compare("version")==0)
	{
		strcpy(response, config::version);
	}
	else if (command.at(0).compare("known_command")==0)
	{
		if ( command.size()>1
				&& (util::arrayContains(config::sys_commands, config::sys_commands_len, command.at(1))
					|| util::arrayContains(config::setup_commands, config::setup_commands_len, command.at(1))
					|| util::arrayContains(config::ai_commands, config::ai_commands_len, command.at(1))) )
		{
			strcpy(response, "true");
		}
		else
		{
			strcpy(response, "false");
		}
	}
	else if (command.at(0).compare("list_commands")==0)
	{
		int i = 0;
		for (i=0; i<config::sys_commands_len; ++i)
		{
			strcat(response, config::sys_commands[i].c_str());
			strcat(response, "\n");
		}
		for (i=0; i<config::setup_commands_len; ++i)
		{
			strcat(response, config::setup_commands[i].c_str());
			strcat(response, "\n");
		}
		for (i=0; i<config::ai_commands_len-1; ++i)
		{
			strcat(response, config::ai_commands[i].c_str());
			strcat(response, "\n");
		}
		strcat(response, config::ai_commands[config::ai_commands_len-1].c_str());
	}
	else if (command.at(0).compare("showboard")==0)
	{
		if (gs->getSize()>0)
		{
			strcat(response, "\n");
			strcat(response, gs->toString().c_str());
		}
	}
	else if (command.at(0).compare("quit")==0)
	{
		// do nothing
	}
	else
	{
		strcat(response, "not implemented yet (sys): ");
		strcat(response, command.at(0).c_str());
		success = false;
	}

	return success;
}
