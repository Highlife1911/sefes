#pragma once
#include "RobotinoExtension.h"

#include <rec/robotino/api2/LaserRangeFinder.h>

#include "LaserSensorReadings.h"
#include "Module.h"

/** \class RobotinoExtension::LaserSensor
 * 	\brief The optional LaserSensor distance sensor.
 *
 *	This sensor has a higher range than the distance sensor and
 *  also supplies move precise data. It is restricted to a small angle.
 */

namespace RobotinoExtension
{
class
	EXPORT_CLASS LaserSensor : private rec::robotino::api2::LaserRangeFinder, public Observer
{
public:
	/**
	 *  Constructs the LaserSensor and sets the owner.
	 *
	 *   \param id	ComId from the owning Robot.
	 */
	explicit LaserSensor(const rec::robotino::api2::ComId &id);


	/**
	 *  Destroys the LaserSensor.
	 */
	virtual ~LaserSensor() = default;


	/**
	 *  Returns a copy of the latest LaserSensor readings.
	 *  The Object might be a dummy Object when no data is available.
	 */
	LaserSensorReadings currentReadings() const;

protected:

	/**
	 *  The last received Distances. Might be invalid.
	 *
	 *	\remark	Check mHasData to test validness of this object.
	 */
	LaserSensorReadings mReadings;


	/**
	 *  Stores the validness of the sensor data. False after construction until
	 *	the first call of processEvents() from Robot.
	 */
	bool mHasData;

private:

	virtual void scanEvent(const rec::robotino::api2::LaserRangeFinderReadings &scan) override final;
};
}
