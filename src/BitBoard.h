/*
 * BitBoard.h
 *
 *  Created on: Nov 14, 2011
 *      Author: joey
 */

#ifndef BITBOARD_H_
#define BITBOARD_H_

#include <string>
#include <ctype.h>
#include "util.h"

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <climits>
using namespace std;

#define ONE 1UL
#define ZERO 0UL


class BitBoard
{
private:
	unsigned long* bits;
public:
	BitBoard();
	BitBoard(int boardWidth);
	BitBoard(const BitBoard& board);
	virtual ~BitBoard();
	void init(int boardWidth);

	bool get(int i);
	bool get(int r, char c);
	void set(int i, bool val);
	void clear();
	int getBoardWidth() const;
	unsigned long* getBits() {return bits;}
	void setBits(unsigned long* b) {bits = b;}
	int bitCount();

	void putStone(int r, char c);
	void putStone(int i);
	void removeStone(int r, char c);
	void removeStone(int i);

	const bool equals(const BitBoard* bb2) const;

	BitBoard& operator=(const BitBoard& b);
	BitBoard& operator|=(const BitBoard& b);
	BitBoard& operator&=(const BitBoard& b);
	const BitBoard operator~() const;
	const BitBoard operator&(const BitBoard& b) const;
	const BitBoard operator|(const BitBoard& b) const;
	const BitBoard operator<<(int shift) const;
	const BitBoard operator>>(int shift) const;

	const string toString();
};


void cleanupBitBoard();

#endif /* BITBOARD_H_ */
