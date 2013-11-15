/*
 * TestGreedyPlayer.cpp
 *
 *  Created on: Apr 17, 2012
 *      Author: joey
 */

#include "TestGreedyPlayer.h"



TestGreedyPlayer::TestGreedyPlayer()
{
}

TestGreedyPlayer::~TestGreedyPlayer()
{
}

void testGreedyGame1()
{
	GameState gs;
	AI ai(&gs);
	SysCommands sys(&gs);
	SetupCommands setup(&gs);
	RndPlayer rndPlayer;

	gs.init(9);
	gs.play("b", "a1");
	gs.play("w", "a2");
	gs.play("w", "b1");

	bool expectedWinnerIsBlack = false;
	int i;
	double count = 0;
	double limit = 100;

	time_t start;
	time(&start);

	for (i=0; i<limit; ++i)
	{
		count += (rndPlayer.playGreedyGame(gs.getBoardState(), false) == expectedWinnerIsBlack ? 1 : 0);
	}
	cout << limit << " game time: " << difftime(time(NULL), start) << endl;
	cout << "Percent good results: " << (count/limit) << endl;
}

void testGreedyGame2()
{
	GameState gs;
	AI ai(&gs);
	SysCommands sys(&gs);
	SetupCommands setup(&gs);
	RndPlayer rndPlayer;

	gs.init(9);
	gs.play("w", "a1");
	gs.play("w", "a2");
	gs.play("w", "b1");
	gs.play("w", "b2");

	gs.play("b", "a3");
	gs.play("b", "b3");
	gs.play("b", "c1");

	bool expectedWinnerIsBlack = true;
	int i;
	double count = 0;
	double limit = 100;

	time_t start;
	time(&start);

	for (i=0; i<limit; ++i)
	{
		count += (rndPlayer.playGreedyGame(gs.getBoardState(), false) == expectedWinnerIsBlack ? 1 : 0);
	}
	cout << limit << " game time: " << difftime(time(NULL), start) << endl;
	cout << "Percent good results: " << (count/limit) << endl;
}

void TestGreedyPlayer::doTest()
{
	cout << "TestGreedyPlayer (Greedy)" << endl;
	testGreedyGame1();
	testGreedyGame2();
	cout << endl;
}












