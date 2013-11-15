/*
 * TestComplexOpps.cpp
 *
 *  Created on: Apr 18, 2012
 *      Author: joey
 */

#include "TestComplexOpps.h"

#include "../complexOpps.h"

TestComplexOpps::TestComplexOpps()
{
}

TestComplexOpps::~TestComplexOpps()
{
}



void testFindLibertiesAdjacentStones()
{
	int boardWidth = 9;

	BitBoard attacker(boardWidth);
	attacker.putStone(8, 'a');
	attacker.putStone(9, 'b');

	BitBoard defender(boardWidth);
	defender.putStone(9, 'a');

	BitBoard* libsAdjStones = complexOpps::findLibertiesAdjacentStones(&defender, &attacker);

	if (libsAdjStones->bitCount()>0)
	{
		cout << "fail: testFindLibertiesAdjacentStones" << endl;
	}
	else
	{
		cout << "pass: testFindLibertiesAdjacentStones" << endl;
	}

	delete libsAdjStones;
}

void testFindStonesAdjacentLiberties()
{
	int boardWidth = 9;

	BitBoard liberties(boardWidth);

	BitBoard defender(boardWidth);
	defender.putStone(9, 'a');

	BitBoard* stonesAdjLibs = complexOpps::findStonesAdjacentLiberties(&liberties, &defender);

	if (stonesAdjLibs->bitCount()>0)
	{
		cout << "fail: testFindStonesAdjacentLiberties" << endl;
	}
	else
	{
		cout << "pass: testFindStonesAdjacentLiberties" << endl;
	}

	delete stonesAdjLibs;
}

void testFullyExpandLiveStoneIntoGroup()
{
	int boardWidth = 9;

	BitBoard stonesWithLiberties(boardWidth);

	BitBoard defender(boardWidth);
	defender.putStone(9, 'a');

	complexOpps::fullyExpandLiveStoneIntoGroup(&stonesWithLiberties, &defender);

	if (stonesWithLiberties.bitCount()>0)
	{
		cout << "fail: testFullyExpandLiveStoneIntoGroup" << endl;
	}
	else
	{
		cout << "pass: testFullyExpandLiveStoneIntoGroup" << endl;
	}
}

void testFindStonesWithLiberties()
{
	int boardWidth = 9;

	BitBoard attacker(boardWidth);
	attacker.putStone(8, 'a');
	attacker.putStone(9, 'b');

	BitBoard defender(boardWidth);
	defender.putStone(9, 'a');

	BitBoard* stonesWithLibs = complexOpps::findStonesWithLiberties(&attacker, &defender);

	if (stonesWithLibs->bitCount()>0)
	{
		cout << "fail: testFindStonesWithLiberties" << endl;
	}
	else
	{
		cout << "pass: testFindStonesWithLiberties" << endl;
	}

	delete stonesWithLibs;
}


void TestComplexOpps::doTest()
{
	cout << "TestComplexOpps:" << endl;
	testFindLibertiesAdjacentStones();
	testFindStonesAdjacentLiberties();
	testFullyExpandLiveStoneIntoGroup();
	testFindStonesWithLiberties();
	cout << endl;
}
