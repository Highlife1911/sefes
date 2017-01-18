#pragma once
#include "RobotinoExtension.h"

/**
 *  Constructs a drive and sets its owner.
 *
 *  \param robot_handle Handle from the owning robot.
 *  \return A new drive handle or Null on failure. Also might set an error Message.
 */
EXPORT void *driveConstruct(void *robot_handle);

/**
 *  Destroys a drive.
 *
 *  \param drive_handle Handle from the drive to destroy.
 *  \remark Never fails but might set an error Message when Handle is invalid.
 */
EXPORT void driveDestroy(void *drive_handle);

/**
 *  Drives forward.
 *
 *  \param drive_handle Handle from the drive the movement is requested.
 *	\param speed Speed in m/s that sould be greater 0 and not greater than driveMaxMovementSpeed().
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool driveForward(void *drive_handle, float speed);

/**
 *  Drives backward.
 *
 *  \param drive_handle Handle from the drive the movement is requested.
 *	\param speed Speed in m/s that sould be greater 0 and not greater than driveMaxMovementSpeed().
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool driveBackward(void *drive_handle, float speed);

/**
 *  Drives left.
 *
 *  \param drive_handle Handle from the drive the movement is requested.
 *	\param speed Speed in m/s that sould be greater 0 and not greater than driveMaxMovementSpeed().
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool driveLeft(void *drive_handle, float speed);

/**
 *  Drives right.
 *
 *  \param drive_handle Handle from the drive the movement is requested.
 *	\param speed Speed in m/s that sould be greater 0 and not greater than driveMaxMovementSpeed().
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool driveRight(void *drive_handle, float speed);

/**
 *  Rotates clockwise.
 *
 *  \param drive_handle Handle from the drive the movement is requested.
 *	\param speed Speed in rad/s that sould be greater 0 and not greater than driveMaxRotationSpeed().
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool driveRotateClockwise(void *drive_handle, float speed);

/**
 *  Rotates counter clockwise.
 *
 *  \param drive_handle Handle from the drive the movement is requested.
 *	\param speed Speed in rad/s that sould be greater 0 and not greater than driveMaxRotationSpeed().
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool driveRotateCounterClockwise(void *drive_handle, float speed);

/**
 *  Stops every movement
 *
 *  \param drive_handle Handle from the drive the movement should be stopped.
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool driveStop(void *drive_handle);

/**
 *  Max movement speed in m/s.
 */
EXPORT float driveMaxMovementSpeed();

/**
 *  Max rotation speed in rad/s.
 */
EXPORT float driveMaxRotationSpeed();

/**
 *  Low level movement function that needs to be called every 50 ms to keep moving.
 *	This function allows simultan movement in x and y direction while rotating.
 *
 *  \param drive_handle Handle from the drive the movement is requested.
 *	\param x speed and direction on the x axis.
 *	\param y speed and direction on the y axis.
 *	\param theta speed and direction of rotations.
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 *	\remark The input is not checked and too big values are causing a missbehaving simulation.
 */
EXPORT bool driveDirectMovement(void *drive_handle, float x, float y, float theta);
