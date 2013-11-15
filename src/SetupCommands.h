/*
 * SetupCommands.h
 *
 *  Created on: Nov 16, 2011
 *      Author: joey
 */

#ifndef SETUPCOMMANDS_H_
#define SETUPCOMMANDS_H_

#include "GameState.h"
#include <vector>

class SetupCommands
{
private:
	GameState * gs;
public:
	SetupCommands(GameState * gs);
	virtual ~SetupCommands();

	bool process(vector<string> command, char response[]);
};

#endif /* SETUPCOMMANDS_H_ */
