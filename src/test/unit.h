/*
 * unit.h
 *
 *  Created on: Apr 17, 2012
 *      Author: joey
 */

#ifndef UNIT_H_
#define UNIT_H_

#include "../ai/AI.h"
#include "../GameState.h"
#include "../config.h"
#include "../SysCommands.h"
#include "../SetupCommands.h"
#include "../BoardState.h"
#include "../BitBoard.h"
#include "../ai/RndPlayer.h"
#include "../util.h"
#include "../ai/UCTNode.h"
#include <ctype.h>
#include <cstring>
#include <time.h>


#include <iostream>
using namespace std;

class UnitTest
{
public:
	virtual void doTest() = 0;
};


#endif /* UNIT_H_ */
