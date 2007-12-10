#ifndef DEFS_H_
#define DEFS_H_

#define DEBUG

//#define USING_USTL 

#define LOG_LEVEL 3

#ifdef USING_USTL

#include <ustl.h>
using namespace ustl;

#ifndef USTL_UTILS_H_
#include "common/ustl_int/ustl_utils.h"
#endif

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

#include <SDL/SDL.h>
#ifndef LOG_MANAGER_H_
#include "common/log/log_manager.h"
#endif

#endif /*DEFS_H_*/
