#pragma once
#include <functional>

#include "error.h"
#include "callback.hpp"
#include "callback_type.h"
#include "handle.hpp"

#include "Core/Robot.h"
using namespace RobotinoExtension;
using namespace std::placeholders;

template <typename MODULE>
void *construct(void *robot_handle)
{
	try
	{
		Robot *robot = checkHandle<Robot>(robot_handle);
		return insertHandle(new MODULE(robot->getComId()));
	}
	catch (std::exception &e)
	{
		setError(e.what());
		return nullptr;
	}
}

template <typename MODULE>
void *construct()
{
	try
	{
		return insertHandle(new MODULE());
	}
	catch (std::exception &e)
	{
		setError(e.what());
		return nullptr;
	}
}

template <typename MODULE>
void destroy(void *module_handle)
{
	try
	{
		checkHandle<MODULE>(module_handle);
		deleteHandle<MODULE>(module_handle);
	}
	catch (std::exception &e)
	{
		setError(e.what());
	}
}

template <typename MODULE>
bool call(void *module_handle, std::function<void(MODULE *)> func)
{
	try
	{
		func(checkHandle<MODULE>(module_handle));
		return EXIT_SUCCESS;
	}
	catch (std::exception &e)
	{
		setError(e.what());
		return EXIT_FAILURE;
	}
}

template <typename MODULE, typename RETURN>
RETURN value(void *module_handle, std::function<RETURN(MODULE *)> func, RETURN fail)
{
	try
	{
		return func(checkHandle<MODULE>(module_handle));
	}
	catch (std::exception &e)
	{
		setError(e.what());
		return fail;
	}
}

template <typename MODULE>
bool registerCallback(void *module_handle, void *callback, callback_type type)
{
	try
	{
		MODULE *module = checkHandle<MODULE>(module_handle);

		if (callback == nullptr)
		{
			module->removeCallback();
			return EXIT_SUCCESS;
		}

		switch (type)
		{
			case func_ptr:
				module->setCallback(static_cast<void(*)(void)>(callback));
				break;
			case class_ptr:
				module->setCallback(static_cast<Callback *>(callback));
				break;
			default:
				throw std::exception("Unsupported callback_type supplied!");
		}

		return EXIT_SUCCESS;
	}
	catch (std::exception &e)
	{
		setError(e.what());
		return EXIT_FAILURE;
	}
}
