#pragma once
#include <array>

#include <Core/Robot.h>

#include "movement.h"

class PositionalRobot : public RobotinoExtension::Robot
{
public:
	explicit PositionalRobot(int id);
	virtual ~PositionalRobot();

	void run();

protected:

	void initializeComponents();
	void destroyComponents();

	void poolEvent();
	void poolToLaneEvent();
	void laneEvent();
	void waitingRoomEvent();
	void archiveRoomEvent();
	void toPoolLaneEvent();
	void exitPoolLaneEvent();
	void toStartingPositonEvent();

private:

	RobotinoExtension::Navigation *mNavigation;
	RobotinoExtension::NorthStar  *mNorthStar;
	RobotinoExtension::Drive 	  *mDrive;

	const int mid;

	enum states
	{
		state_pool,
		state_poolToLane,
		state_lane,
		state_waitingRoom,
		state_archiveRoom,
		state_toPoolLane,
		state_exitPoolLane,
		state_toStartingPositon
	} state;

	Movement movement;

	bool isAllowedToMoveInPool;
	int lane;
	int cycle;
	int toPoolPosition;
	int waitingPosition;
	int newWaitingRoomPosition;
};