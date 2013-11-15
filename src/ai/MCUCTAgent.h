/*
 * MCUCTAgent.h
 *
 *  Created on: Feb 29, 2012
 *      Author: joey
 */

#ifndef MCUCTAGENT_H_
#define MCUCTAGENT_H_

#include "AIAgent.h"
#include "UCTNode.h"
#include "RAVEManager.h"

class MCUCTAgent: public AIAgent
{
private:
	UCTNode* root;
	UCTNode* bestMove;
	RAVEManager* rave;
public:
	MCUCTAgent();
	virtual ~MCUCTAgent();

	string genmove(BoardState* bs, string color);
	void explain();
};

#endif /* MCUCTAGENT_H_ */
