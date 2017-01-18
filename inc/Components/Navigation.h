#pragma once

#include "Module.h"

/** \class RobotinoExtension::Navigation
 *	\brief Navigation module that interacts with the drive and the north star.
 *
 *	A callback function can be used to take action when the target
 *	position is reached.
 */

namespace RobotinoExtension
{
class Drive;
class NorthStar;
class Position;

class
	EXPORT_CLASS Navigation : public Observer
{
public:
	/**
	 *  Constructs the navigation form a drive and a north star.
	 *	Both parameters must be from the same robot or the behaviour is undefined.
	 *
	 *	\param drive Handle from drive to use.
	 *	\param northstar Handle from north star to use.
	 */
	Navigation(Drive *drive, NorthStar *northstar);

	/**
	 *  Destroys the navigation.
	 */
	virtual ~Navigation() = default;

	/**
	 *  Drives to a position and interrupts other movement.
	 *
	 *	\param pos The position the robot needs to drive to.
	 *	\param speed The maximum movement speed.
	 *	\param acceleration the maximum speed change per second.
	 */
	virtual void driveToPosition(const Position &pos, float speed, float acceleration);

protected:

	NorthStar *mNorthStar;
	Drive *mDrive;

	static float DistanceThreshold()
	{
		return 0.1f;
	}

private:

	void moveTo(const Position &pos, float speed, float acceleration) const;
	static float computeRotationSpeed(float absAngle);
	static float calculateCorrectionAngleTo(const Position &sourcePos, float sourceAngle, const Position &targetPos);
	static float computeAngle(float xs, float ys, float xt, float yt);

	static const float PI;

	/**
	 *  Disable copying of this Object.
	 */
	Navigation(const Navigation &);
	Navigation &operator=(const Navigation &);
};
}
