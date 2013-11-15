#ifndef AIAGENT_H_
#define AIAGENT_H_

#include <string>
#include "../BoardState.h"
using namespace std;

class AIAgent
{
private:
public:
	virtual ~AIAgent() {};

	virtual string genmove(BoardState* bs, string color) = 0;
	virtual void explain() = 0; // print info about last move choice
};

#endif
