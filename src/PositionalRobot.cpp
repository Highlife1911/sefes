#include "PositionalRobot.h"

#include <iostream>
#include <mutex>

#include <Core/Drive.h>
#include <Core/NorthStar.h>
#include <Core/Position.h>

#include <Components/Navigation.h>

#include "shared.h"

namespace
{

}

PositionalRobot::PositionalRobot(const std::string &ip)
	: Robot(ip)
	, mNavigation(nullptr)
	, mNorthStar(nullptr)
	, mDrive(nullptr)
{
	connect();
	initializeComponents();
}

PositionalRobot::~PositionalRobot()
{
	destroyComponents();
	disconnect();
}

void PositionalRobot::run()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));

	startedMovement = false;
	isArrived = false;
	isAllowedToMoveInPool = false;
	state = state_pool;

	while (isConnected())
	{
		processEvents();

		switch (state)
		{
		case state_pool:
			poolEvent();
			break;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

void PositionalRobot::poolEvent()
{
	auto &inst = shared::instance();
	std::lock_guard<std::mutex> lock(inst.access);

	if (!isAllowedToMoveInPool)
	{
		if (inst.movementInPool)
		{
			return;
		}
		inst.movementInPool = true;
		isAllowedToMoveInPool = true;
	}

	for (int i = 0; i < shared::numberOfLanes; ++i)
	{
		if (inst.canEnterLane[i])
		{
			inst.canEnterLane[i] = false;
			state = state_poolToLane;
			lane = i;
			return;
		}
	}
}

void PositionalRobot::poolToLaneEvent()
{
	auto &inst = shared::instance();
	auto &pos = inst.lanePoints[lane][0];

	assert(isAllowedToMoveInPool);

	if (isArrived)
	{
		startedMovement = false;
		state = state_lane;
		isArrived = false;

		std::lock_guard<std::mutex> lock(inst.access);
		isAllowedToMoveInPool = false;
		inst.movementInPool = false;

		return;
	}

	if (startedMovement)
	{
		return;
	}

	startedMovement = true;
	mNavigation->driveToPosition(RobotinoExtension::Position(pos.first, pos.second), 0.5f, 1.0f);
}

void PositionalRobot::laneEvent()
{
	auto &inst = shared::instance();
	auto &pos = inst.lanePoints[lane][1];

	if (isArrived)
	{
		startedMovement = false;
		state = state_waitingRoom;
		isArrived = false;

		std::lock_guard<std::mutex> lock(inst.access);
		inst.canEnterLane[lane] = true;

		return;
	}

	if (startedMovement)
	{
		return;
	}

	startedMovement = true;
	mNavigation->driveToPosition(RobotinoExtension::Position(pos.first, pos.second), 0.5f, 1.0f);
}

void PositionalRobot::waitingRoomEvent()
{
	auto &inst = shared::instance();
}

void PositionalRobot::initializeComponents()
{
	mDrive = new RobotinoExtension::Drive(getComId());
	mNorthStar = new RobotinoExtension::NorthStar(getComId());

	mNavigation = new RobotinoExtension::Navigation(mDrive, mNorthStar);
	mNavigation->setCallback(this);
}

void PositionalRobot::event()
{
	isArrived = true;
}

void PositionalRobot::destroyComponents()
{
	delete mNavigation;

	delete mDrive;
	delete mNorthStar;
}