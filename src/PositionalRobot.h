#pragma once
#include <array>

#include <Core/Forward.h>
#include <Core/Robot.h>

#include <Wrapper/callback.hpp>

class PositionalRobot : public RobotinoExtension::Robot, protected Callback
{
public:
	explicit PositionalRobot(const std::string &ip);
	virtual ~PositionalRobot();

	void run();

protected:

	void initializeComponents();
	void destroyComponents();

	void event() override;

	void poolEvent();
	void poolToLaneEvent();
	void laneEvent();
	void waitingRoomEvent();

private:

	RobotinoExtension::Navigation *mNavigation;
	RobotinoExtension::NorthStar  *mNorthStar;
	RobotinoExtension::Drive 	  *mDrive;

	enum states
	{
		state_pool,
		state_poolToLane,
		state_lane,
		state_waitingRoom,
		state_archiveRoom,
		state_toPoolLane
	} state;

	bool isAllowedToMoveInPool;
	int lane;
	bool isArrived;
	bool startedMovement;
};