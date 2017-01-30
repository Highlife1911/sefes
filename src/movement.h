#pragma once

#include <Core/Forward.h>
#include <Core/Position.h>
#include <Components/Navigation.h>

#include <Wrapper/callback.hpp>

struct Movement : public Callback
{
	bool isArrived = false;
	bool startedMovement = false;

	void move(RobotinoExtension::Navigation *navi, std::pair<float,float> pos, float speed = 0.65f)
	{
		isArrived = false;
		startedMovement = true;
		navi->driveToPosition(RobotinoExtension::Position(pos.first, pos.second), speed, -1.0f);
	}

	void event() override
	{
		isArrived = true;
		startedMovement = false;
	}
};