#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

static const std::string ERROR_NB_ARG      = "error: number of arguments.";
static const std::string ERROR_EMPTY_ARG   = "error: Filename or string to replace cannot be empty.";
static const std::string ERROR_OPEN_FILE   = "error: file cannot be opened.";
static const std::string ERROR_CREATE_FAIL = "error: file's creation failed.";

void search_and_replace(std::string& filename, std::string& str1, std::string& str2);