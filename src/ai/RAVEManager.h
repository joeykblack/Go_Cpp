/*
 * RAVEManager.h
 *
 *  Created on: Apr 12, 2012
 *      Author: joey
 */

#ifndef RAVEMANAGER_H_
#define RAVEMANAGER_H_

using namespace std;

class RAVEManager
{
private:
	int* wins;
	int* visits;
	int boardWidth;
public:
	RAVEManager(int width);
	virtual ~RAVEManager();
	void init(int width);

	void update(int index, int value);
	double getValue(int index) const;
	int getBoardWidth() const;

	int getWins(int index) const;
	int getVisits(int index) const;
};

#endif /* RAVEMANAGER_H_ */
