#pragma once
#include "RobotinoExtension.h"

#include "Wrapper/callback_type.h"

/**
 *  Constructs a bumper and sets its owner.
 *
 *  \param robot_handle Handle from the owning robot.
 *  \return A new bumper handle or Null on failure. Also might set an error Message.
 */
EXPORT void *bumperConstruct(void *robot_handle);

/**
 *  Destroys a bumper.
 *
 *  \param bumper_handle Handle from the bumper to destroy.
 *  \remark Never fails but might set an error Message when Handle is invalid.
 */
EXPORT void bumperDestroy(void *bumper_handle);

/**
 *  The current bumper status.
 *
 *  \param bumper_handle Handle from the bumper the status is requested.
 *  \return The status as bool or a negative value on failure.
 */
EXPORT int bumperStatus(void *bumper_handle);

/**
 *  Registers a callback that gets called when new data is availiable.
 *
 *  \param bumper_handle Handle from the bumper the status is requested.
 *	\param callback Pointer to a void (*)(void) function, an instance of Callback or Null to remove the callback.
 *	\param type A member of the callback_type enumeration.
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool bumperStatusCallback(void *bumper_handle, void *callback, callback_type type = func_ptr);
