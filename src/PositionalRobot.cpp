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
	std::mutex access;
	const int port = 12080;
	const std::string ip = "127.0.0.1:";
}

PositionalRobot::PositionalRobot(int id)
	: Robot(ip + std::to_string(port + id))
	, mNavigation(nullptr)
	, mNorthStar(nullptr)
	, mDrive(nullptr)
	, mid(id)
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

	isAllowedToMoveInPool = false;
	state = state_pool;
	cycle = 0;

	while (isConnected())
	{
		processEvents();

		switch (state)
		{
		case state_pool: poolEvent(); break;
		case state_poolToLane: poolToLaneEvent(); break;
		case state_lane: laneEvent(); break;
		case state_waitingRoom: waitingRoomEvent(); break;
		case state_archiveRoom: archiveRoomEvent(); break;
		case state_toPoolLane: toPoolLaneEvent(); break;
		case state_exitPoolLane: exitPoolLaneEvent(); break;
		case state_toStartingPositon: toStartingPositonEvent(); break;
		default:
			std::cout << "Unkown State: " << state << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void PositionalRobot::poolEvent()
{
	access.lock();
	auto &inst = shared::instance();
	//std::lock_guard<std::mutex> lock(access);

	if (!isAllowedToMoveInPool)
	{
		if (inst.movementInPool)
		{
			access.unlock();
			return;
		}
		inst.movementInPool = true;
		isAllowedToMoveInPool = true;
	}

	int i = rand() % shared::numberOfLanes;
	//for (int i = 0; i < shared::numberOfLanes; ++i)
	//{
		if (inst.canEnterLane[i])
		{
			inst.canEnterLane[i] = false;
			std::cout << "Robot " << mid << ": PoolToLaneEvent" << std::endl;
			state = state_poolToLane;
			lane = i;
			access.unlock();
			return;
		}
	//}
	access.unlock();
}

void PositionalRobot::poolToLaneEvent()
{
	auto &inst = shared::instance();
	std::lock_guard<std::mutex> lock(access);
	auto &pos = inst.lanePoints[lane][0];

	if (movement.isArrived)
	{
		movement.isArrived = false;
		std::cout << "Robot " << mid << ": LaneEvent" << std::endl;
		state = state_lane;

		isAllowedToMoveInPool = false;
		inst.movementInPool = false;

		return;
	}

	if (!movement.startedMovement)
	{
		movement.move(mNavigation, pos);
	}
}

void PositionalRobot::laneEvent()
{
	auto &inst = shared::instance();
	std::lock_guard<std::mutex> lock(access);
	auto &pos = inst.lanePoints[lane][1];

	if (movement.isArrived)
	{
		movement.isArrived = false;
		std::cout << "Robot " << mid << ": WaitingRoomEvent" << std::endl;
		state = state_waitingRoom;
		waitingPosition = -1;
		inst.canEnterLane[lane] = true;

		return;
	}

	if (!movement.startedMovement)
	{
		movement.move(mNavigation, pos);
	}
}

void PositionalRobot::waitingRoomEvent()
{
	auto &inst = shared::instance();
	std::lock_guard<std::mutex> lock(access);

	if (movement.isArrived)
	{
		movement.isArrived = false;
		waitingPosition = newWaitingRoomPosition;
	}

	if (waitingPosition == 0 && inst.isArchiveOccupied[lane] == false)
	{
		std::cout << "Robot " << mid << ": ArchiveRoomEvent" << std::endl;
		std::cout << "Archive " << lane << " is now occupied" << std::endl;
		inst.isArchiveOccupied[lane] = true;
		state = state_archiveRoom;
		inst.waitingRooms[lane].leave();
		return;
	}

	newWaitingRoomPosition = inst.waitingRooms[lane].position(mid);
	if (newWaitingRoomPosition != waitingPosition)
	{
		movement.move(mNavigation, inst.waitingRooms[lane].realPosition(newWaitingRoomPosition));
	}
}

void PositionalRobot::archiveRoomEvent()
{
	auto &inst = shared::instance();
	std::lock_guard<std::mutex> lock(access);
	auto &pos = inst.archiveRoomExit[lane];

	if (movement.isArrived)
	{
		++cycle;
		if (cycle > 100 && inst.canEnterToPoolLane[lane])
		{
			inst.canEnterToPoolLane[lane] = false;
			std::cout << "Archive " << lane << " is now free" << std::endl;
			inst.isArchiveOccupied[lane] = false;
			movement.isArrived = false;
			cycle = 0;
			toPoolPosition = 0;
			std::cout << "Robot " << mid << ": ToPoolLaneEvent" << std::endl;
			state = state_toPoolLane;
		}

		return;
	}

	if (!movement.startedMovement)
	{
		movement.move(mNavigation, pos);
	}
}

void PositionalRobot::toPoolLaneEvent()
{
	auto &inst = shared::instance();
	std::lock_guard<std::mutex> lock(access);

	if (movement.isArrived)
	{
		++toPoolPosition;
		if (toPoolPosition == inst.poolDrivePoints[lane].size() - 1)
		{
			movement.isArrived = false;
			std::cout << "Robot " << mid << ": ExitPoolEvent" << std::endl;
			state = state_exitPoolLane;
			return;
		}
	}

	if (!movement.startedMovement)
	{
		movement.move(mNavigation, inst.poolDrivePoints[lane][toPoolPosition]);
	}
}

void PositionalRobot::exitPoolLaneEvent()
{
	auto &inst = shared::instance();
	std::lock_guard<std::mutex> lock(access);

	if (!isAllowedToMoveInPool)
	{
		if (inst.movementInPool)
		{
			return;
		}
		inst.movementInPool = true;
		isAllowedToMoveInPool = true;
	}

	if (movement.isArrived)
	{
		movement.isArrived = false;
		std::cout << "Robot " << mid << ": ToStartingPositionEvent" << std::endl;
		state = state_toStartingPositon;
		inst.canEnterToPoolLane[lane] = true;
		return;
	}

	if (!movement.startedMovement)
	{
		movement.move(mNavigation, inst.poolDrivePoints[lane].back());
	}
}

void PositionalRobot::toStartingPositonEvent()
{
	auto &inst = shared::instance();
	std::lock_guard<std::mutex> lock(access);

	if (movement.isArrived)
	{
		movement.isArrived = false;
		std::cout << "Robot " << mid << ": PoolEvent" << std::endl;
		state = state_pool;
		return;
	}

	if (!movement.startedMovement)
	{
		movement.move(mNavigation, inst.startingPositions[mid]);
	}
}

void PositionalRobot::initializeComponents()
{
	mDrive = new RobotinoExtension::Drive(getComId());
	mNorthStar = new RobotinoExtension::NorthStar(getComId());

	mNavigation = new RobotinoExtension::Navigation(mDrive, mNorthStar);
	mNavigation->setCallback(&movement);
}

void PositionalRobot::destroyComponents()
{
	delete mNavigation;

	delete mDrive;
	delete mNorthStar;
}