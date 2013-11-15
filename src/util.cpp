/*
 * util.cpp
 *
 *  Created on: Nov 15, 2011
 *      Author: joey
 */

#include "util.h"
#include <stdio.h>

namespace util
{


void stringtolower(char * c)
{
	for (unsigned int i=0; i<strlen(c); ++i)
	{
		c[i] = tolower(c[i]);
	}
}

int removeid(char buffer[])
{
	int id = 0;
	unsigned int i=0;
	if (strlen(buffer)==0 || isalpha(buffer[0]))
	{
		id = -1;
	}
	else
	{
		while (i<strlen(buffer) && isdigit(buffer[i]))
		{
			id = (id*10) + (buffer[i]-'0');
			buffer[i] = ' ';
			++i;
		}
	}

	return id;
}

void clean(char buffer[])
{
	bool incomment = false;
	for (unsigned int i = 0; i < strlen(buffer); ++i)
	{
		if (buffer[i] == '#')
		{
			incomment = true;
		}

		// remove control chars
		if ( (buffer[i]<' ' && buffer[i]!='\n') || incomment )
		{
			buffer[i] = ' ';
		}
	}
}


bool arrayContains(const string array[], const int len, string s)
{
	for (int i = 0; i < len; ++i)
	{
		if (strcmp(array[i].c_str(), s.c_str()) == 0)
		{
			return true;
		}
	}

	return false;
}

int getIndex(int row, char col, int size)
{
	int r = row - 1;
	int c = toupper(col);

	if (c>'I')
	{
		--c;
	}

	c -= 'A';

	int i = (r*size) + c;

	if (i>=(size*size))
	{
		cerr << "Error: invalid index -> " << row << "," << col << " is > " << (size*size) << endl;
	}

	return i;
}

string getPos(int index, int size)
{
	int row = (index / size) + 1;
	char col = (index % size) + 'A';
	if (col == 'I')
	{
		col++;
	}

	string pos = "";
	char buffer[10];
	sprintf(buffer, "%c%d", col, row);
	pos.append(buffer);

	return pos;
}



} // end namespace
