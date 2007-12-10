#ifndef USTL_UTILS_H_
#define USTL_UTILS_H_

#include "../../defs.h"

#ifdef USING_USTL

class UstlUtils
{
private:
	static string::size_type string_find_last_of(const string& obj, char c);
public:	
	static string string_substr(const string& obj, string::size_type position);
	
	static void string_insert(const string& obj, string::size_type position, const string& value);
};


#endif

#endif /*USTL_UTILS_H_*/
