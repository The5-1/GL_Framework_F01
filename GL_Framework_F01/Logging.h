#pragma once

///Helper Macros for Logging
///LOG: regular print
///ERR: print with file and function

#include <iostream>

#define LOG(x) do { std::cerr << x << std::endl; } while (0)
#define ERR(x) do { std::cerr << "ERROR:\t"<< x  << "\n\tFile: " <<__FILE__ << "\n\tFuncion \"" << __func__ << "\" in Line " <<__LINE__<< std::endl; } while (0)


