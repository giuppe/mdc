
#include "defs.h"
#include "receiver.h"
#include "stream_repository.h"
#include <cassert>


void Receiver::action()
{
	StreamRepository* repo = StreamRepository::instance();
	ReceiveFilterList* filter_list = ReceiveFilterList::instance();
	
	assert(!"This function is a stub.");
	//-listen on port 5552

	//-receive every descriptor

	//-filter every descriptor with the help of a list, filled with result of ASRQs
	//--the list contains: sender ip and stream hash
	//--if the new descriptor fits on these constraints, write it to disk
}
