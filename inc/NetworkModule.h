#pragma once

#include <functional>

#include "Wrapper/client.hpp"

namespace RobotinoExtension
{
class
	EXPORT_CLASS NetworkModule
{
public:
	NetworkModule();

	virtual ~NetworkModule();

	void setCallback(std::function<void(const char *, int)> callback);
	void setCallback(Client *callback);
	void removeCallback();

protected:

	void callback(const char *data, int size) const;

private:

	std::function<void(const char *, int)> mCallback;
};
}
