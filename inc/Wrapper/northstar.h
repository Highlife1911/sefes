#pragma once
#include "RobotinoExtension.h"

#include "Wrapper/callback_type.h"

/**
 *  Constructs northstar and sets its owner.
 *
 *  \param robot_handle Handle from the owning robot.
 *  \return A new northstar handle or Null on failure. Also might set an error Message.
 */
EXPORT void *northstarConstruct(void *robot_handle);

/**
 *  Destroys the northstar.
 *
 *  \param northstar_handle Handle from the northstar to destroy.
 *  \remark Never fails but might set an error Message when Handle is invalid.
 */
EXPORT void northstarDestroy(void *northstar_handle);

/**
 *  Current position and rotation of the robot.
 *
 *  \param northstar_handle Handle from the network adapter the id is requested.
 *	\param x Pointer to a float the x coordinate gets written to or Null.
 *	\param y Pointer to a float the y coordinate gets written to or Null.
 *	\param angle Pointer to a float the angle gets written to or Null.
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool northstarPosition(void *northstar_handle, float *x, float *y, float *angle);

/**
 *  Registers a callback that gets called when new data is aviable.
 *
 *  \param northstar_handle Handle from the northstar the status is requested.
 *	\param callback Pointer to a void (*)(void) function, an instance of Callback or Null to remove the callback.
 *	\param type A member of the callback_type enumeration.
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool northstarPositionCallback(void *northstar_handle, void *callback, callback_type type = func_ptr);
