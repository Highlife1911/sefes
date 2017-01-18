#pragma once
#include "RobotinoExtension.h"

/**
 *  Generic Callback class that acts as an Observer.
 */
class
	EXPORT_CLASS Callback
{
public:
	Callback()
	{
	}

	virtual ~Callback()
	{
	}

	virtual void event() = 0;
};
