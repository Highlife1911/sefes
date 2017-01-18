#pragma once
#include "RobotinoExtension.h"

#include <vector>

/** \class RobotinoExtension::DistanceSensorReadings
 *	\brief The sensor readings encapsulated in a class.
 *
 *	The data is pretty accurate and in m.
 */

namespace RobotinoExtension
{
/**
 *  The Robotino robot has 9 distance sensors. The sensors are uniformed
 *  distributed with an angle of 40°. The distance sensor at the front has an
 *  angle of 0°.
 *
 *  Use this enumeration to exactly identify each sensor.
 */
enum SensorPosition
{
	FRONT,
	FRONT_LEFT,
	LEFT_TOP,
	LEFT_BOTTOM,
	REAR_LEFT,
	REAR_RIGHT,
	RIGHT_BOTTOM,
	RIGHT_TOP,
	FRONT_RIGHT,
};

class
	EXPORT_CLASS DistanceSensorReadings
{
public:
	/**
	 *  Constructs a Dummy Readings object.
	 *
	 *	\remark This Dummy Object is only used when no data is available.
	 *  \throws Throws an exception if a function of this Object is called.
	 */
	DistanceSensorReadings();


	/**
	 *  Constructs a Readings object with raw sensor data.
	 *
	 *	\param data		The pointer should have getNumberOfSensors() elements.
	 */
	explicit DistanceSensorReadings(const float *const data);


	/**
	 *  Destroys the distance sensor readings object. Every copy stays valid.
	 */
	virtual ~DistanceSensorReadings() = default;


	/**
	 *  Get the raw Distances the sensor got constructed with.
	 */
	float *getDistances() const;


	/**
	 *  Get a specific distance by SensorPosition.
	 *
	 *	\param pos	The Position of the sensor from SensorPosition enum.
	 */
	float getDistanceBySensor(int pos) const;


	/**
	 *  Returns the actual number of usable distance sensors.
	 *  This number is hardware specific and (for now) always 9.
	 */
	static int NumberOfSensors();

protected:

	/**
	 *  Raw data.
	 */
	std::vector<float> mData;
};
}
