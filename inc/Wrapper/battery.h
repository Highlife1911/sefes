#pragma once
#include "RobotinoExtension.h"

#include "Wrapper/callback_type.h"

/**
 *  Constructs a battery and sets its owner.
 *
 *  \param robot_handle Handle from the owning robot.
 *  \return A new battery handle or Null on failure. Also might set an error Message.
 */
EXPORT void *batteryConstruct(void *robot_handle);

/**
 *  Destroys a battery.
 *
 *  \param battery_handle Handle from the battery to destroy.
 *  \remark Never fails but might set an error Message when Handle is invalid.
 */
EXPORT void batteryDestroy(void *battery_handle);

/**
 *  The current battery charge status in percent.
 *
 *  \param battery_handle Handle from the battery the power is requested.
 *  \return The charge status as a float between 0 and 1 or a negative value on failure.
 */
EXPORT float batteryPower(void *battery_handle);

/**
 *  Registers a callback that gets called when new data is availiable.
 *
 *  \param battery_handle Handle from the battery the power is requested.
 *	\param callback Pointer to a void (*)(void) function, an instance of Callback or Null to remove the callback.
 *	\param type A member of the callback_type enumeration.
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool batteryPowerCallback(void *battery_handle, void *callback, callback_type type = func_ptr);
