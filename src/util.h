/*
 * util.h
 *
 *  Created on: Nov 15, 2011
 *      Author: joey
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include <cstring>

#include <iostream>
using namespace std;

namespace util
{


void stringtolower(char * c);

int removeid(char buffer[]);

void clean(char buffer[]);


bool arrayContains(const string array[], const int len, string s);

int getIndex(int row, char col, int size);
string getPos(int index, int size);


} // end util


#endif /* UTIL_H_ */
