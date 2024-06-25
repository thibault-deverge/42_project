#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "error.hpp"

/*
***** CONSTANTS *****
*/
static const int PARSING_ERROR = -1;
static const int MIN_PORT = 1084;
static const int MAX_PORT = 49151;

/*
***** PROTOTYPES *****
*/
int parse_arguments(int argc, char **argv);