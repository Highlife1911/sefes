#pragma once

#include <set>
#include <mutex>
#include <utility>
#include <vector>

#include "waitingRoom.h"

struct shared
{
	static const int numberOfRobots = 8;
	static const int numberOfRooms = 3;
	static const int lanesPerRoom = 1;
	static const int numberOfLanes = lanesPerRoom * numberOfRooms;

	static shared& instance()
	{
		static shared sh;
		return sh;
	}

	shared();

	bool canEnterLane[numberOfLanes];
	bool canEnterToPoolLane[numberOfRooms];
	int numberOfRobotsInWaitingRoom[numberOfRooms];
	bool isArchiveOccupied[numberOfRooms];

	std::vector<std::pair<float, float>> lanePoints[numberOfLanes];
	std::vector<std::pair<float, float>> poolDrivePoints[numberOfLanes];

	std::pair<float, float> waitingRoomExit[numberOfRooms];
	std::pair<float, float> archiveRoomExit[numberOfRooms];

	std::pair<float, float> startingPositions[numberOfRobots];
	
	bool movementInPool;

	WaitingRoom waitingRooms[numberOfRooms];
};