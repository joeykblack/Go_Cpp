/*
 * AIEngine.h
 *
 *  Created on: Nov 14, 2011
 *      Author: joey
 */

#ifndef AIENGINE_H_
#define AIENGINE_H_

#include "../GameState.h"
#include "AIAgent.h"
#include <vector>

class AI
{
private:
	GameState * gs;
	AIAgent * agent;
public:
	AI(GameState * gs);
	~AI();
	bool process(vector<string> command, char response[]);
};


#endif /* AIENGINE_H_ */
