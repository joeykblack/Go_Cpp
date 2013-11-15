/*
 * TestUCTNode.cpp
 *
 *  Created on: Apr 17, 2012
 *      Author: joey
 */

#include "TestUCTNode.h"

TestUCTNode::TestUCTNode()
{
}

TestUCTNode::~TestUCTNode()
{
}


void repointRootTest()
{
	BoardState bs1(9);
	BoardState bs2(9);

	bs1.playStone(0, true);
	UCTNode* n1 = new UCTNode(&bs1, false);
	n1->createChildren();

	bs2.playStone(0, true);
	bs2.playStone(1, false);

	n1 = n1->repointRoot(&bs2);

	if (n1 != NULL)
	{
		cout << "root found" << endl;
	}
	else
	{
		cout << "root not found" << endl;
	}

	delete n1;
}


void TestUCTNode::doTest()
{
	cout << "TestUCTNode" << endl;
	repointRootTest();
	cout << endl;
}


