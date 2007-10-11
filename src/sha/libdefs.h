#if !defined(__LIBDEFS_H)
#define LIBDEFS_H

/*
   {{{ includes 
 */

#define MUTILS_USE_MHASH_CONFIG

#ifdef WIN32
# define WIN32DLL_DEFINE __declspec( dllexport)
#else
# define WIN32DLL_DEFINE
#endif

#define RAND32 (mutils_word32) ((mutils_word32)rand() << 17 ^ (mutils_word32)rand() << 9 ^ rand())

#endif
