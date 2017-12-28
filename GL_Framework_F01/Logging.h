#pragma once

///Helper Macros for Logging
///LOG: regular print
///ERR: print with file and function

#include "stl_include.h"
#include <Windows.h> //for coloring console output //https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c

#ifndef LOG(x)
#define LOG(x) do { \
					HANDLE  hConsole;  hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole, 8);\
					std::cerr << x << std::endl;\
					SetConsoleTextAttribute(hConsole, 15);\
				  } while (0)
#endif // !LOG(x)


#ifndef ERR(x)
	#define ERR(x) do { \
						HANDLE  hConsole;  hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole, 12);\
						std::cerr << "ERROR:\t"<< x  << "\n\tFile: " <<__FILE__ << "\n\tFuncion \"" << __func__ << "\" in Line " <<__LINE__<< std::endl; \
						SetConsoleTextAttribute(hConsole, 15);\
					  } while (0)
#endif // !ERR(x)

#ifndef ERR_GL(x)
#define ERR_GL(x) do { \
						HANDLE  hConsole;  hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole, 13 + 4*16);\
						std::cerr << "OpenGL:\t"<< x  << "\n\tFile: " <<__FILE__ << "\n\tFuncion \"" << __func__ << "\" in Line " <<__LINE__<< std::endl; \
						SetConsoleTextAttribute(hConsole, 15);\
					  } while (0)
#endif // !ERR_GL(x)