#ifndef REBSTRING_H
#define REBSTRING_H

#include <string>


class RebString
{
	char* data;
public:
	RebString()
	{
		data = 0;
	}

		void erase()
	{
		if (data != 0)
		{
			data = 0;
		}
	}

	unsigned int size()
	{
		if(sizeof(data[0] > 0))
		{
		return sizeof(data)/sizeof(data[0]) - 1;
		}
		else
		return 0;
	}

	const char* operator = (const char * e)
	{
		erase();
		data = (char*)e;
		return e;
	}

	operator std::string ()
	{
		std::string ret;
		if(size() > 0)
		{
		ret = data;
		}
		return ret;
	}

	~RebString()
	{
		erase();
	}

};


#endif