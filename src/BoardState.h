/*
 * BoardState.h
 *
 *  Created on: Nov 14, 2011
 *      Author: joey
 */

#ifndef BOARDSTATE_H_
#define BOARDSTATE_H_

#include "BitBoard.h"

class BoardState
{
private:
	BitBoard *black;
	BitBoard *white;
	BitBoard *dead;
	int blackCaptured;
	int whiteCaptured;
	bool wasCapture;

	void removeDead(bool isBlack);
	bool isSuicide(bool isBlack, int i);
	bool isKo(int i) const;
	void undo(int i, bool isBlack, BitBoard *oldDead);
public:
	BoardState(int size);
	BoardState(const BoardState* bs);
	virtual ~BoardState();

	const string toString();
	bool equals(const BoardState* bs2) const;

	void putStone(int r, char c, bool isBlack);
	void putStone(int i, bool isBlack);
	void removeStone(int r, char c, bool isBlack);
	void removeStone(int i, bool isBlack);
	bool playStone(int r, char c, bool isBlack);
	bool playStone(int i, bool isBlack);
	bool basicValidation(int i) const;
	float* scoresArea();
	float* scoresTerritory();
	float* scoresEval();

	BitBoard* getBlack() const;
	BitBoard* getWhite() const;
	BitBoard* getDead();
	int getBoardWidth() const;
	bool wasCapturep();
};

#endif /* BOARDSTATE_H_ */
