/*
 * config.h
 *
 *  Created on: Nov 14, 2011
 *      Author: joey
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
using namespace std;

namespace config
{

extern const int BLACK;
extern const int WHITE;

extern const bool isBlackAI;
extern const bool isBlackHuman;
extern const bool isBlackServer;

extern const bool isWhiteAI;
extern const bool isWhiteHuman;
extern const bool isWhiteServer;

extern const char quit[];
extern const char error[];

extern const char version[];

extern const char protocol_version[];

extern const char name[];

extern const int sys_commands_len;
extern const string sys_commands[];

extern const int setup_commands_len;
extern const string setup_commands[];

extern const int ai_commands_len;
extern const string ai_commands[];

extern const int tournament_commands_len;
extern const string tournament_commands[];

extern const int reg_commands_len;
extern const string reg_commands[];

extern const string agentType;

extern const double raveMod;
extern const int visitsBeforeTrust;

extern const int numRndGamesPerMove;
extern const int numRndMovesPerGame;
extern const double percentFull;

extern const int expandPoint;

extern const double UCTK;

extern const int secondsPerMove;
extern const string agentLimitter;
extern const int numberOfIterations;

extern const double resign;
extern const double pass;

extern const string scoring;
}

#endif /* CONFIG_H_ */
