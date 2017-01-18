#pragma once
#include "RobotinoExtension.h"

/**
 *  Generic Callback class that acts as an Observer for network purposes.
 */
class
	EXPORT_CLASS Client
{
public:
	Client()
	{
	}

	virtual ~Client()
	{
	}

	virtual void event(const char *const data, int size) = 0;
};
