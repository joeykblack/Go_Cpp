/*
 * config.cpp
 *
 *  Created on: Nov 15, 2011
 *      Author: joey
 */

#include "config.h"

namespace config
{

const int BLACK = 0;
const int WHITE = 0;

const bool isBlackAI = false;
const bool isBlackHuman = true;
const bool isBlackServer = false;

const bool isWhiteAI = true;
const bool isWhiteHuman = false;
const bool isWhiteServer = false;

const char quit[] = "quit";
const char error[] = "unknown command";

const char version[] = "0";

const char protocol_version[] = "2";

const char name[] = "JKB Go";

const int sys_commands_len = 7;
const string sys_commands[] = {
		"protocol_version",
		"name",
		"version",
		"known_command",
		"list_commands",
		"quit",
		"showboard"
};


const int setup_commands_len = 6;
const string setup_commands[] = {
		"boardsize",
		"clear_board",
		"komi",
		"fixed_handicap",
		"place_free_handicap",
		"set_free_handicap"
};

const int ai_commands_len = 6;
const string ai_commands[] = {
		"play",
		"genmove",
		"undo",
		"final_score",
		"reg_genmove",
		"explain" // not a gtp command
};


const int tournament_commands_len = 4;
const string tournament_commands[] = {
		"time_settings",
		"time_left",
		"final_score",
		"final_status_list"
};

const int reg_commands_len = 2;
const string reg_commands[] = {
		"load_sgf",
		"reg_genmove"
};

// types: mc, mcuct
const string agentType = "mcuct";

const double raveMod = 0.5; // weight applied to RAVE value
// How many visits before rave value is used over rnd selection
const int visitsBeforeTrust = 50;

const int numRndGamesPerMove = 100; // MC only

const int numRndMovesPerGame = 54; // not used
const double percentFull = 0.9; // what percent of board to fill in random game

const int expandPoint = 10;

const double UCTK = 0.5;

// on cgos server:
//  5 minutes sudden death on 9x9 ~ 10 sec/move
// Note: code will take a few cycles more than what is limited by time
const string agentLimitter = "time";
const int secondsPerMove = 15;
const int numberOfIterations = 5000;

const double resign = 0.01; // if best <= resign the resign
const double pass = 0.8; // if worst => pass then pass

const string scoring = "area"; // territory or area
} // end config
