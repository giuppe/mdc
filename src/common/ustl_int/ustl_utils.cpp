
#include "ustl_utils.h"
#include <cassert>

#ifdef USING_USTL


string::size_type UstlUtils::string_find_last_of(const string& obj, char c)
{
	string::size_type pos = 0;
	string::size_type last_pos = 0;
	while(pos!=string::npos)
	{
		pos=obj.find(c);
		last_pos = pos;
	}
	return last_pos;
	
}
	
string UstlUtils::string_substr(const string& obj, string::size_type position)
{
	return obj.substr(position, obj.size()-position);
	
}


#endif
