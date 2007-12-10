#ifndef DEFS_H_
#define DEFS_H_

#define DEBUG

//#define USING_USTL 1

#define LOG_LEVEL 3

#if USING_USTL

#include <ustl.h>
using namespace ustl;

#else

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


#endif


#include <SDL/SDL.h>
#include "common/log/log_manager.h"

#ifdef NOT_HAVING_SDL_H_

typedef Uint64 unsigned long;
typedef Sint64 long;

typedef Uint32 unsigned int;
typedef Sint32 int;


typedef Uint16 unsigned short;
typedef Sint16 short;


typedef Uint8 unsigned char;
typedef Sint8 char;
#endif




#endif /*DEFS_H_*/
