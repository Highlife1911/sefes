#pragma once

#include <mutex>
#include <set>
#include <typeinfo>

struct hull
{
	hull(void *p, const std::type_info &info)
		: ptr(p)
		, type(info)
	{
	}

	void *ptr;
	const std::type_info &type;
};

extern std::mutex handle_mutex;
extern std::set<hull *> handle_table;

template <typename MODULE>
void *insertHandle(MODULE *handle)
{
	if (handle)
	{
		std::lock_guard<std::mutex> lock(handle_mutex);
		hull *h = new hull(handle, typeid(MODULE));
		handle_table.insert(h);
		return h;
	}

	return nullptr;
}

template <typename MODULE>
void deleteHandle(void *raw_handle)
{
	if (raw_handle)
	{
		std::lock_guard<std::mutex> lock(handle_mutex);
		hull *handle = static_cast<hull *>(raw_handle);
		std::set<hull *>::iterator it = handle_table.find(handle);
		if (it == handle_table.end())
		{
			throw std::runtime_error("Internal programming error");
		}
		if ((*it)->type != typeid(MODULE))
		{
			setError("Wrong deleter specified!");
			return;
		}
		delete static_cast<MODULE *>((*it)->ptr);
		handle_table.erase(handle);
		delete handle;
		handle = nullptr;
	}
}

template <typename MODULE>
MODULE *checkHandle(void *handle)
{
	if (handle == nullptr)
	{
		throw std::exception("Invalid handle used: Handle is null.");
	}

	std::lock_guard<std::mutex> lock(handle_mutex);

	std::set<hull *>::iterator raw_handle = handle_table.find(static_cast<hull *>(handle));
	if (raw_handle == handle_table.end())
	{
		throw std::exception("Handle has no entry inside the HandleTable.");
	}

	if ((*raw_handle)->type != typeid(MODULE))
	{
		throw std::exception("Wrong handle type commited.");
	}

	return static_cast<MODULE *>((*raw_handle)->ptr);
}
