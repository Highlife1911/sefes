#pragma once
#include "RobotinoExtension.h"

#include <memory>

#include <rec/robotino/api2/DistanceSensorArray.h>

#include "Module.h"
#include "DistanceSensorReadings.h"

/** \class RobotinoExtension::DistanceSensor
 *	\brief A low range distance sensor arranged as a circle in an interval of 40°.
 *
 *	The class uses a history based analysis to correct wrong values.
 */

namespace RobotinoExtension
{
class
	EXPORT_CLASS DistanceSensor : private rec::robotino::api2::DistanceSensorArray, public Observer
{
public:
	/**
	 *  Constructs the distance sensor and sets the owner.
	 *
	 *   \param id	ComId from the owning Robot.
	 */
	explicit DistanceSensor(const rec::robotino::api2::ComId &id);


	/**
	 *  Destroys the distance sensor.
	 */
	virtual ~DistanceSensor() = default;


	/**
	 *  Returns a copy of the latest distance sensor readings.
	 *  The Object might be a dummy Object when no data is available.
	 */
	DistanceSensorReadings currentReadings() const;

protected:

	/**
	 *  The last received Distances. Might be invalid.
	 *
	 *	\remark	Check mHasData to test validness of this object.
	 */
	DistanceSensorReadings mReadings;


	/**
	 *  Stores the validness of the sensor data. False after construction until
	 *	the first call of processEvents() from Robot.
	 */
	bool mHasData;

private:

	/**
	 *  This function corrects wrong sensor readings using a history based analyse.
	 */
	void correctDataWithHistory();

	virtual void distancesChangedEvent(const float *distances, unsigned int size) override final;

	std::unique_ptr<float[]> mInputBuffer;


	/**
	 *  Disable copying of this Object.
	 */
	DistanceSensor(const DistanceSensor &);
	DistanceSensor &operator=(const DistanceSensor &);
};
}
