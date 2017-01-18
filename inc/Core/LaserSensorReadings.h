#pragma once
#include "RobotinoExtension.h"

#include <vector>

/** \class RobotinoExtension::LaserSensorReadings
 * 	\brief The sensor readings encapsulated in a class.
 */

namespace RobotinoExtension
{
class
	EXPORT_CLASS LaserSensorReadings
{
public:
	/**
	 *  Constructs a Dummy Readings object.
	 *
	 *	\remark This Dummy Object is only used when no data is available.
	 */
	LaserSensorReadings();


	/**
	 *  Constructs a Readings object with raw sensor data.
	 *
	 *	\param data		The pointer should have getNumberOfSensors() elements.
	 *	\param length	The number of rays the laser sensor used.
	 *	\param angle	The total scan angle.
	 */
	LaserSensorReadings(const float *const data, int length, float angle);


	/**
	 *  Destroys the distance sensor readings object. Every copy stays valid.
	 */
	virtual ~LaserSensorReadings() = default;


	/**
	 *  Returns the raw sensor readings.
	 */
	float *getDistances() const;


	/**
	 *  Returns the number of Rays. This number is equivalent to
	 *	the number of availiable distances.
	 */
	int getNumberOfRays() const;


	/**
	 *  Retruns the total scan angle. The rays are uniform distributed along this angle.
	 */
	float getScanAngle() const;

protected:

	/**
	 *  Raw data.
	 */
	std::vector<float> mData;


	/**
	 *  Raw angle.
	 */
	float mAngle;
};
}
