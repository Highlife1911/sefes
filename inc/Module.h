#pragma once

#include <functional>

#include "Wrapper/callback.hpp"

namespace RobotinoExtension
{
class
	EXPORT_CLASS Observer
{
public:
	Observer();
	virtual ~Observer();

	void setCallback(std::function<void(void)> callback);
	void setCallback(Callback *callback);
	void removeCallback();

protected:

	void callback() const;

private:

	std::function<void(void)> mCallback;
};
}
