/*
 * BitBoard.cpp
 *
 *  Created on: Nov 14, 2011
 *      Author: joey
 */

#include "BitBoard.h"

using namespace std;



static int longBytes = sizeof(unsigned long);
static int longbits = longBytes * CHAR_BIT;

static BitBoard* leftShiftMask = NULL;
static BitBoard* rightShiftMask = NULL;

static unsigned long unusedMask = ZERO;
static int boardWidth = 0;
static int numLongs = 0;

// this deletes the static bitboards
// it is called from ~SetupCommands
void cleanupBitBoard()
{
	if (leftShiftMask!=NULL)
	{
		delete leftShiftMask;
		leftShiftMask = NULL;
	}
	if (rightShiftMask!=NULL)
	{
		delete rightShiftMask;
		rightShiftMask = NULL;
	}
	boardWidth = -1;
}



BitBoard::BitBoard()
{
	bits = new unsigned long[numLongs];
	memset(bits, 0, longBytes*numLongs);
}

BitBoard::BitBoard(int bWidth)
{
	// if the size changes, re-init
	if (bWidth != boardWidth) init(bWidth);

	bits = new unsigned long[numLongs];
	memset(bits, 0, longBytes*numLongs);
}

void BitBoard::init(int bWidth)
{
	boardWidth = bWidth;
	int extraBits = (boardWidth*boardWidth) % longbits;
	int extra = ( extraBits == 0 ? 0 : 1);
	numLongs = (boardWidth*boardWidth/longbits) + extra;

	// Unused bits mask
	int i;
	for (i = 0; i < extraBits; ++i)
	{
		unusedMask |= (ONE << i);
	}

	// Left shift mask
	if (leftShiftMask!=NULL)
	{
		delete leftShiftMask;
	}
	leftShiftMask = new BitBoard();
	for (i = 0; i < boardWidth; ++i)
	{
		leftShiftMask->set(i*boardWidth, true);
	}
	*leftShiftMask = ~(*leftShiftMask);

	// Right shift mask
	if (rightShiftMask!=NULL)
	{
		delete rightShiftMask;
	}
	rightShiftMask = new BitBoard();
	for (i = 0; i < boardWidth; ++i)
	{
		rightShiftMask->set( (i*boardWidth) + (boardWidth-1), true);
	}
	*rightShiftMask = ~(*rightShiftMask);

}

BitBoard::BitBoard(const BitBoard& board)
{
	bits = new unsigned long[numLongs];
	memcpy(bits, board.bits, numLongs * longBytes);
}

BitBoard::~BitBoard()
{
	delete[] bits;
}

bool BitBoard::get(int i)
{
	return ((bits[i/longbits] >> (i%longbits)) & ONE) != 0;
}

bool BitBoard::get(int r, char c)
{
	int i = util::getIndex(r, c, boardWidth);

	return get(i);
}

void BitBoard::set(int i, bool val)
{
	if (val) bits[i/longbits] |= (ONE << (i%longbits));
	else bits[i/longbits] &= ~(ONE << (i%longbits));
}

void BitBoard::clear()
{
	int index;
	for (index = 0; index < numLongs; ++index)
	{
		bits[index] = ZERO;
	}
}

int BitBoard::getBoardWidth() const
{
	return boardWidth;
}

int BitBoard::bitCount()
{
	int count = 0;
	int i;
	for (i = 0; i < boardWidth*boardWidth; ++i)
	{
		count += get(i);
	}
	return count;
}


void BitBoard::putStone(int r, char c)
{
	int i = util::getIndex(r, c, boardWidth);
	putStone(i);
}

void BitBoard::putStone(int i)
{
	bits[i/longbits] |= ONE << (i%longbits);
}

void BitBoard::removeStone(int r, char c)
{
	int i = util::getIndex(r, c, boardWidth);
	removeStone(i);
}

void BitBoard::removeStone(int i)
{
	bits[i/longbits] &= ~(ONE << i%longbits);
}


BitBoard& BitBoard::operator=(const BitBoard& b)
{
	if (this == &b)
	{
		return *this;
	}

	memcpy(bits, b.bits, numLongs * longBytes);

	return *this;
}

BitBoard& BitBoard::operator|=(const BitBoard& b)
{
	int index;
	for (index = 0; index < numLongs; ++index)
	{
		bits[index] |= b.bits[index];
	}
	return *this;
}

BitBoard& BitBoard::operator&=(const BitBoard& b)
{
	int index;
	for (index = 0; index < numLongs; ++index)
	{
		bits[index] &= b.bits[index];
	}
	return *this;
}

const BitBoard BitBoard::operator~() const
{
	BitBoard bb(*this);
	int index;
	for (index = 0; index < numLongs; ++index)
	{
		bb.bits[index] = ~(bb.bits[index]);
	}
	return bb;
}

const BitBoard BitBoard::operator&(const BitBoard& b) const
{
	BitBoard bb(*this);
	int index;
	for (index = 0; index < numLongs; ++index)
	{
		bb.bits[index] &= b.bits[index];
	}
	return bb;
}

const BitBoard BitBoard::operator|(const BitBoard& b) const
{
	BitBoard bb(*this);
	int index;
	for (index = 0; index < numLongs; ++index)
	{
		bb.bits[index] |= b.bits[index];
	}
	return bb;
}

const BitBoard BitBoard::operator<<(int shift) const
{
	BitBoard bb(*this);
	int index = 0;
	bb.bits[index] <<= shift;
	if (shift==1) bb.bits[index] &= leftShiftMask->getBits()[index];
	for (index = 1; index < numLongs; ++index)
	{
		bb.bits[index] <<= shift;
		bb.bits[index] |= (bits[index-1] >> (longbits - shift));
		if (shift==1) bb.bits[index] &= leftShiftMask->getBits()[index];
	}
	bb.bits[numLongs-1] &= unusedMask;
	return bb;
}

const BitBoard BitBoard::operator>>(int shift) const
{
	BitBoard bb(*this);
	int index;
	bb.bits[numLongs-1] &= unusedMask;
	for (index = 0; index < numLongs-1; ++index)
	{
		bb.bits[index] >>= shift;
		bb.bits[index] |= bits[index+1] << (longbits - shift);
		if (shift==1) bb.bits[index] &= rightShiftMask->getBits()[index];
	}
	bb.bits[numLongs-1] >>= shift;
	if (shift==1) bb.bits[numLongs-1] &= rightShiftMask->getBits()[numLongs-1];
	return bb;
}

const string BitBoard::toString()
{
	string s;

	int mod = 0;
	if (getBoardWidth()>('I'-'A'))
	{
		mod = 1;
	}

	int limit = getBoardWidth()+'A'+mod;

	for (int r = getBoardWidth(); r >= 1; --r)
	{
		for (char c = 'A'; c < limit; ++c)
		{
			if (c=='I') ++c;

			char sym = '.';

			if (get(r, c)) sym = 'x';

			s.append(1, sym);
			s.append(1, ' ');
		}
		char buffer[3];
		sprintf(buffer, "%d", r);
		s.append(buffer);
		s.append(1, '\n');
	}
	for (char c = 'A'; c < getBoardWidth()+'A'+mod; ++c)
	{
		if (c=='I') ++c;
		s.append(1, c);
		s.append(1, ' ');
	}
	s.append(1, '\n');

	return s;
}

const bool BitBoard::equals(const BitBoard* bb2) const
{
	int i;
	for (i = 0; i < numLongs; ++i)
	{
		if (bits[i]!=bb2->bits[i]) return false;
	}
	// TODO: memcmp?
	return true;// memcmp(bits, bb2->bits, longBytes*numLongs);
}
