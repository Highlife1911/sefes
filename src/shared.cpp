#include "shared.h"

shared::shared()
{
	for(int i = 0; i < numberOfLanes; ++i){
		canEnterLane[i]	= true;
	}
	for(int i = 0; i < numberOfRooms; ++i){
		canEnterToPoolLane[i] = true;
		numberOfRobotsInWaitingRoom[i] = 0;
		isArchiveOccupied[i] = false;
	}

	lanePoints[0].push_back({7.0f , 0.5f});
	lanePoints[0].push_back({11.0f , 0.5f});
	lanePoints[1].push_back({3.0f , -4.0f});
	lanePoints[1].push_back({3.0f , -9.5f});
	lanePoints[2].push_back({-1.5f , 0.5f});
	lanePoints[2].push_back({-5.0f , 0.5f});

	waitingRoomExit[0] = {15.0f, 0.5f};
	waitingRoomExit[1] = {0.0f, -10.5f};
	waitingRoomExit[2]= {-9.0f, 0.5f};

	archiveRoomExit[0] = {17.8f, 1.3f};
	archiveRoomExit[1] = {-3.5f, -10.5f};
	archiveRoomExit[2] = {-11.7f, 1.5f};

	poolDrivePoints[0].push_back({17.8f ,8.5f});
	poolDrivePoints[0].push_back({6.0f ,8.5f});
	poolDrivePoints[0].push_back({6.0f ,6.0f});
	poolDrivePoints[1].push_back({-17.5f ,-10.5f});
	poolDrivePoints[1].push_back({-17.5f ,13.0f});
	poolDrivePoints[1].push_back({3.0f ,13.0f});
	poolDrivePoints[1].push_back({3.0f ,6.0f});
	poolDrivePoints[2].push_back({-11.7f ,8.5f});
	poolDrivePoints[2].push_back({0.0f ,8.5f});
	poolDrivePoints[2].push_back({0.0f ,6.0f});

	startingPositions[0] = {5.0f, -4.5f};
	startingPositions[1] = {7.5f ,-3.0f};
	startingPositions[2] = {8.0f ,2.0f};
	startingPositions[3] = {7.4f ,6.0f};
	startingPositions[4] = {-1.3f ,6.0f};
	startingPositions[5] = {-2.0f ,2.0f};
	startingPositions[6] = {-1.5f ,-3.0f};
	startingPositions[7] = {0.5f ,-4.5f};

	movementInPool = false;	

	waitingRooms[0].mid = 0;
	waitingRooms[0].moffset = -0.75f;

	waitingRooms[1].mid = 1;
	waitingRooms[1].moffset = 0.75f;

	waitingRooms[2].mid = 2;
	waitingRooms[2].moffset = 0.75f;
}