/*
 * SysCommands.h
 *
 *  Created on: Nov 15, 2011
 *      Author: joey
 */

#ifndef SYSCOMMANDS_H_
#define SYSCOMMANDS_H_

#include "GameState.h"
#include <vector>

class SysCommands
{
private:
	GameState * gs;
public:
	SysCommands(GameState * gs);
	~SysCommands();

	bool process(vector<string> command, char response[]);
};

#endif /* SYSCOMMANDS_H_ */
