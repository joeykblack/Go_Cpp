/*
 * complexOpps.cpp
 *
 *  Created on: Dec 2, 2011
 *      Author: joey
 */

#include "complexOpps.h"
#include <iostream>
#include <string>
using namespace std;

BitBoard* complexOpps::explode(BitBoard* stones)
{
    int size = stones->getBoardWidth();

    // Explode
    BitBoard* exploded = new BitBoard();
    *exploded = (*stones << ONE) | (*stones << size) | (*stones >> ONE) | (*stones >> size);

    return exploded;
}

/**
 * Finds liberties of defender by:
 * 1. Shift defender in all directions
 * 2. Remove original defender and attacker bits
 *
 * The result (liberties) is stored in defender
 */
BitBoard* complexOpps::findLibertiesAdjacentStones(BitBoard* origDefender, BitBoard* attacker)
{
    BitBoard *liberties = explode(origDefender);

	// Remove self contained bits
	// Remove blocking bits
	*liberties &= ~(*origDefender) & ~(*attacker);

	return liberties;
}


BitBoard* complexOpps::findStonesAdjacentLiberties(BitBoard* liberties, BitBoard* origDefender)
{
    BitBoard *stoneAdjacentLiberties = explode(liberties);

	// Intersect with original stones
	*stoneAdjacentLiberties &= *origDefender;

	return stoneAdjacentLiberties;
}


void complexOpps::fullyExpandLiveStoneIntoGroup(BitBoard* liveStones, BitBoard* defender)
{

	bool running = true;
	while (running)
	{
		// Find new live stones
		BitBoard* newlyDiscoveredLiveStones = complexOpps::findStonesAdjacentLiberties(liveStones, defender);
		*newlyDiscoveredLiveStones &= ~(*liveStones);

		// No new stones
		if (newlyDiscoveredLiveStones->bitCount()==0)
		{
			running = false;
		}
		// When we find no new live stones
		else
		{
			*liveStones |= *newlyDiscoveredLiveStones;
		}

		delete newlyDiscoveredLiveStones;
	}
}


const BitBoard complexOpps::expandBlocking(BitBoard* expander, BitBoard* blocker)
{
	int size = expander->getBoardWidth();
	return ((*expander << size) | (*expander << ONE) | (*expander >> size) | (*expander >> ONE) | *expander) & (~*blocker);
}


BitBoard* complexOpps::fullExpandBlocking(BitBoard* expander, BitBoard* blocker)
{
	BitBoard* result = new BitBoard(*expander);
	int oldCount = result->bitCount();
	*result = complexOpps::expandBlocking(result, blocker);
	while (result->bitCount() != oldCount)
	{
		oldCount = result->bitCount();
		*result = complexOpps::expandBlocking(result, blocker);
	}

	return result;
}


BitBoard* complexOpps::findStonesWithLiberties(BitBoard* attacker, BitBoard* defender)
{
	// Find liberties ( liberties = explodeBlocking(defender, attacker) )
	BitBoard* liberties = complexOpps::findLibertiesAdjacentStones(defender, attacker);

	// Find stones adjacent to liberties ( defender = explodeContaining(liberties, origDefender) )
	BitBoard* stonesWithLiberties = complexOpps::findStonesAdjacentLiberties(liberties, defender);
	delete liberties;

	// Expand liberated stones into their groups ( defender = fullyExpandBlocking(defender, attacker) )
	complexOpps::fullyExpandLiveStoneIntoGroup(stonesWithLiberties, defender);

	return stonesWithLiberties;
}
