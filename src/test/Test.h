/*
 * Test.cpp
 *
 *  Created on: Nov 28, 2011
 *      Author: joey
 */

#ifndef TEST_H_
#define TEST_H_

#include "../ai/AI.h"
#include "../GameState.h"
#include "../config.h"
#include "../SysCommands.h"
#include "../SetupCommands.h"
#include "../BoardState.h"
#include "../BitBoard.h"
#include <ctype.h>
#include <cstring>

#include "../parser.h"
#include "../util.h"

#include "TestRndPlayer.h"
#include "TestGreedyPlayer.h"
#include "TestUCTNode.h"
#include "TestComplexOpps.h"

#include <iostream>
using namespace std;



/*
 * --- Main ---
 */

int testMain()
{
	TestRndPlayer testRndPlayer;
	testRndPlayer.doTest();

	TestGreedyPlayer testGreedyPlayer;
	testGreedyPlayer.doTest();

	TestUCTNode testUCTNode;
	testUCTNode.doTest();

	TestComplexOpps testComplexOpps;
	testComplexOpps.doTest();

	return 0;
}

#endif
