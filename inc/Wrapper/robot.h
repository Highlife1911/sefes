#pragma once
#include "RobotinoExtension.h"

/**
 *  Constructs a robot from a ip.
 *
 *	\remark Does not actually connect to the robot. It is neccessary to
 *		call robotConnect after this command in order to use all modules.
 *
 *  \param ip IP adress with port from the robot to connect with.
 *  \return A new robot handle or Null on failure. Also might set an error Message.
 */
EXPORT void *robotConstruct(const char *ip);

/**
 *  Destroys the robot and invalidates every other module.
 *
 *  \param robot_handle Handle from the robot to destroy.
 *  \remark Never fails but might set an error Message when Handle is invalid.
 */
EXPORT void robotDestroy(void *robot_handle);

/**
 *  Connects the robot and makes every other module usable. It is now
 *	possible to construct different modules with the robot handle.
 *
 *  \remark This method uses the ip the robot got constructed with.
 *
 *  \param robot_handle Handle from the robot to connect.
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool robotConnect(void *robot_handle);

/**
 *  Disconnects the robot and invalidates every other module.
 *
 *  \remark Destroy the modules before the robot.
 *
 *  \param robot_handle Handle from the robot to disconnect.
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool robotDisconnect(void *robot_handle);

/**
 *  Returns the connection status.
 *
 *  \remark This function can always be called.
 *
 *  \param robot_handle Handle from the robot the status is requested.
 *  \return true when connected and false otherwise.
 */
EXPORT bool robotIsConnected(void *robot_handle);

/**
 *  Updates all sensor readings and triggers all callbacks.
 *
 *  \remark This function should be called at least every 50 ms.
 *
 *  \param robot_handle Handle from the robot the status is requested.
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool robotProcessEvents(void *robot_handle);

/**
 *  Returns the ip the robot is associated to.
 *
 *  \remark This function can always be called.
 *
 *  \param robot_handle Handle from the robot the ip is requested.
 *  \return The ip adress when the robot is valid or null if not.
 */
EXPORT const char *robotGetAddress(void *robot_handle);
