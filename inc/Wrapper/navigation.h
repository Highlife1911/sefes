#pragma once
#include "RobotinoExtension.h"

#include "Wrapper/callback_type.h"

/**
 *  Constructs navigation and sets its owner.
 *
 *  \param drive_handle Handle from a constructed drive.
 *  \param northstar_handle Handle from a constructed northstar.
 *  \return A new navigation handle or Null on failure. Also might set an error Message.
 */
EXPORT void *navigationConstruct(void *drive_handle, void *northstar_handle);

/**
 *  Destroys a navigation.
 *
 *  \param navigation_handle Handle from the navigation to destroy.
 *  \remark Never fails but might set an error Message when Handle is invalid.
 */
EXPORT void navigationDestroy(void *navigation_handle);

/**
 *  Drives a robot to a position.
 *
 *  \param navigation_handle Handle of the Navigation of the robot to move.
 *	\param x Position on the x axis.
 *	\param y Position on the y axis.
 *	\param speed The maximum movement speed.
 *	\param acceleration the maximum speed change per second.
 *  \remark Interrupts every other movement.
 */
EXPORT bool navigationDriveToPosition(void *navigation_handle, float x, float y, float speed, float acceleration);

/**
 *  Registers a callback that gets called when new data is availiable.
 *
 *  \param navigation_handle Handle from the navigation the status is requested.
 *	\param callback Pointer to a void (*)(void) function, an instance of Callback or Null to remove the callback.
 *	\param type A member of the callback_type enumeration.
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool navigationTargetReachedCallback(void *navigation_handle, void *callback, callback_type type = func_ptr);
