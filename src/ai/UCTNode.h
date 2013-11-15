/*
 * UCTNode.h
 *
 *  Created on: Feb 29, 2012
 *      Author: joey
 */

#ifndef UCTNODE_H_
#define UCTNODE_H_

#include "../GameState.h"
#include "RAVEManager.h"

class UCTNode
{
private:
	UCTNode** children;
	int numChildren;
	BoardState* bs;
	int index;

	int visits;
	int wins;
	bool isBlack;
	bool valid;
	bool resign;
	bool pass;
public:
	UCTNode(BoardState* bs, int index, bool isBlack);
	UCTNode(BoardState* bs, bool isBlack);
	virtual ~UCTNode();

	UCTNode* repointRoot(const BoardState* bs2);
	UCTNode* repointBestMove(UCTNode* bestMove);

	bool visit(RAVEManager* rave);
	void visitChildren(RAVEManager* rave);
	void createChildren();
	UCTNode* selectChild(const RAVEManager& rave);
	UCTNode* getBestMove();
	int getMove();
	bool isResign();
	bool isPass();
	double getUct(UCTNode* next);
	int getVisits();
	int getNumChildren();
	UCTNode* getChild(int index);
	BoardState* getBoardState();
	double customMod(UCTNode* next);

	void showUCTValues(const RAVEManager& rave);
};

#endif /* UCTNODE_H_ */
