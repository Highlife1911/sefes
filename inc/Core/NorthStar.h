#pragma once
#include "RobotinoExtension.h"

#include <rec/robotino/api2/NorthStar.h>

#include "Module.h"
#include "Position.h"

/** \class RobotinoExtension::NorthStar
 *	\brief GPS Positioning sensor.
 *
 *	This sensor retrieves the current cartesian position of the robot.
 *	The sensor is exact when used inside the simulator but not in the real world.
 *
 *	\remark There is a bug inside the current simulator version that swaps x and
 *			y values. For this reason the compile switch SWAP_X_Y exists that
 *			corrects this error.
 */

namespace RobotinoExtension
{
class
	EXPORT_CLASS NorthStar : private rec::robotino::api2::NorthStar, public Observer
{
public:
	/**
	 *  Constructs the NorthStar and sets its owner.
	 *
	 *   \param id	ComId from the owning Robot.
	 */
	explicit NorthStar(const rec::robotino::api2::ComId &id);


	/**
	 *  Destroys the NorthStar.
	 */
	virtual ~NorthStar() = default;


	/**
	 *  Returns the last RobotPosition the sensor received.
	 */
	Position currentPosition() const;


	/**
	 *  Returns the last angle the sensor received.
	 */
	float currentAngle() const;

private:

	/**
	 *  Robotino API2 callback function.
	 */
	virtual void readingsEvent(const rec::robotino::api2::NorthStarReadings &) override final;
};
}
