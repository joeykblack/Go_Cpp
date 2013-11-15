/*
 * parser.h
 *
 *  Created on: Nov 15, 2011
 *      Author: joey
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include <string>
#include <cstring>

#include <iostream>
using namespace std;


namespace parser
{

vector<string> parseInput (char input[])
{
	vector<string> result;
	unsigned int i = 0;
	unsigned int len = strlen(input);

	// skip spaces
	for (; i<len && input[i]==' '; ++i) { }

	// get command
	char command[30];
	command[0] = '\0';
	for (; i<len && input[i]!=' '; ++i)
	{
		int clen = strlen(command);
		command[clen] = input[i];
		command[clen+1] = '\0';
	}
	result.push_back(command);

	// skip spaces
	for (; i<len && input[i]==' '; ++i) { }

	// get args
	while (i<len)
	{
		char args[30];
		args[0] = '\0';
		for (; i<len && input[i]!=' '; ++i)
		{
			int alen = strlen(args);
			args[alen] = input[i];
			args[alen+1] = '\0';
		}
		result.push_back(args);

		// skip spaces
		for (; i<len && input[i]==' '; ++i) { }
	}

	return result;
}


}

#endif /* PARSER_H_ */
