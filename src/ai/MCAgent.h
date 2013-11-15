/*
 * MCAgent.h
 *
 *  Created on: Jan 3, 2012
 *      Author: joey
 */

#ifndef MCAGENT_H_
#define MCAGENT_H_

#include "AIAgent.h"

class MCAgent: public AIAgent
{
public:
	MCAgent();
	virtual ~MCAgent();

	string genmove(BoardState* bs, string color);
	void explain();
};

#endif /* MCAGENT_H_ */
