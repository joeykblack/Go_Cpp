/*
 * RAVEManager.cpp
 *
 *  Created on: Apr 12, 2012
 *      Author: joey
 */

#include "RAVEManager.h"

#include "../util.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <climits>
using namespace std;

static int intsize = sizeof(int);

RAVEManager::RAVEManager(int width)
{
	boardWidth = width;
	int size = width*width;

	visits = new int[size];
	memset(visits, 0, size*intsize);

	wins = new int[size];
	memset(wins, 0, size*intsize);
}

void RAVEManager::init(int width)
{
//	delete[] wins;
//	delete[] visits;
//
//	boardWidth = width;
//	wins = new int[width*width];
//	memset(wins, 0, width*width*intbits);
//	visits = new int[width*width];
//	memset(visits, 0, width*width*intbits);
}

RAVEManager::~RAVEManager()
{
	delete[] wins;
	delete[] visits;
}



void RAVEManager::update(int index, int value)
{
	visits[index]++;
	wins[index] += value;
}

double RAVEManager::getValue(int index) const
{
	return (visits[index]>0) ? ((double)wins[index]) / visits[index] : 0;
}

int RAVEManager::getBoardWidth() const
{
	return boardWidth;
}

int RAVEManager::getWins(int index) const
{
	return wins[index];
}


int RAVEManager::getVisits(int index) const
{
	return visits[index];
}


