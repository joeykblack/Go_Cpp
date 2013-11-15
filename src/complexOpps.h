/*
 * complexOpps.h
 *
 *  Created on: Dec 2, 2011
 *      Author: joey
 */

#ifndef COMPLEXOPPS_H_
#define COMPLEXOPPS_H_

#include "BitBoard.h"

namespace complexOpps
{

BitBoard* explode(BitBoard* stones);
BitBoard* findLibertiesAdjacentStones(BitBoard* origDefender, BitBoard* attacker);
BitBoard* findStonesAdjacentLiberties(BitBoard* liberties, BitBoard* origDefender);
void fullyExpandLiveStoneIntoGroup(BitBoard* liveStones, BitBoard* defender);
BitBoard* fullExpandBlocking(BitBoard* expander, BitBoard* blocker);
const BitBoard expandBlocking(BitBoard* expander, BitBoard* blocker);
BitBoard* findStonesWithLiberties(BitBoard* attacker, BitBoard* defender);

}

#endif /* COMPLEXOPPS_H_ */
