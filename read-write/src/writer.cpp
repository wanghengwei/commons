#include "writer.h"

void Writer::work()
{
	Reader::wait();
	if (Reader::counter() > 0)
	{
		Reader::signal();
		wait();
	}

}
