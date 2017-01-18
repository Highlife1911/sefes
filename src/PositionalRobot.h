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

	virtual void event() override;

private:

	RobotinoExtension::Navigation *mNavigation;
	RobotinoExtension::NorthStar 	*mNorthStar;
	RobotinoExtension::Drive 		*mDrive;

	int mTarget;
};