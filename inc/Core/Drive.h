#pragma once
#include "RobotinoExtension.h"

#include <atomic>
#include <functional>
#include <thread>

#include <rec/robotino/api2/OmniDrive.h>

/** \class RobotinoExtension::Drive
 *	\brief Movement class with basic api2 abstraction.
 */

namespace RobotinoExtension
{
class
	EXPORT_CLASS Drive : private rec::robotino::api2::OmniDrive
{
public:
	/**
	 *  Constructs the drive and sets the owner.
	 *
	 *   \param id	ComId from the owning Robot.
	 */
	explicit Drive(const rec::robotino::api2::ComId &id);


	/**
	 *  Destroys the drive.
	 */
	virtual ~Drive();


	/**
	 *  Drives the robot forward.
	 *
	 *	\param speed Robot speed in m/s.
	 *
	 *  \remark Stops every other movement.
	 */
	void driveForward(float speed);


	/**
	 *  Drives the robot backward.
	 *
	 *	\param speed Robot speed in m/s.
	 *
	 *  \remark Stops every other movement.
	 */
	void driveBackward(float speed);


	/**
	 *  Drives the robot left.
	 *
	 *	\param speed Robot speed in m/s.
	 *
	 *  \remark Stops every other movement.
	 */
	void driveLeft(float speed);


	/**
	 *  Drives the robot right.
	 *
	 *	\param speed Robot speed in m/s.
	 *
	 *  \remark Stops every other movement.
	 */
	void driveRight(float speed);


	/**
	 *  Rotates the robot clockwise.
	 *
	 *	\param speed Rotation speed in rad/s.
	 *
	 *  \remark Stops every other movement.
	 */
	void rotateClockwise(float speed);


	/**
	 *  Rotates the robot counter clockwise.
	 *
	 *	\param speed Rotation speed in rad/s.
	 *
	 *  \remark Stops every other movement.
	 */
	void rotateCounterClockwise(float speed);


	/**
	 *  Stops the robot movement.
	 */
	void stop();


	/**
	 *  Returns the maximum possible movement speed in m/s.
	 */
	static float MaxMovementSpeed()
	{
		return 0.7f;
	}


	/**
	 *  Returns the maximum possible rotating speed in rad/s.
	 */
	static float MaxRotationSpeed()
	{
		return 0.5f;
	}


	void drive(float x, float y, float theta);

	/**
	 *  Low Level Hardware function. Does NOT check input values.
	 *	Big values cause undefined behaviour inside the simulator.
	 */
	void hardwareDrive(float x, float y, float theta);


	/**
	 *  Every movement needs to refresh every once in a while.
	 *	This function returns the time in ms between each refresh.
	 */
	static int GetMovementInterval()
	{
		return 50;
	}


	/**
	 *  Replaces the movement thread function with another.
	 *	This function runs in a second thread.
	 *
	 *	\param func	A function that should be called when the movement interval triggers.
	 */
	void updateMovementThread(std::function<void()> func);


	/**
	*  Sets the speed for every movement action.
	*
	*  \remark Has no effect when already moving.
	*
	*  \param speed	Movement speed in mm/s. Setting a speed of 0 will result
	*					in movements at the maximum possible speed.
	*/
	static void checkMovementSpeed(float speed);


	/**
	*  Sets the speed for every rotation.
	*
	*  \remark Has no effect when already rotating.
	*
	*  \param speed	Rotating speed in rad/s. Setting a rotating speed of 0
	*					will result in rotations at the maximum possible speed.
	*/
	static void checkRotatingSpeed(float speed);


	std::atomic<bool> mInterrupt;

private:

	void threadDrive(float x, float y, float theta);


	std::thread mMovementThread;

	/**
	 *  Disable copying of this Object.
	 */
	Drive(const Drive &);
	Drive &operator=(const Drive &);
};
}
