#pragma once
#include "RobotinoExtension.h"

#include "Wrapper/callback_type.h"

/**
 *  Constructs a distancesensor and sets its owner.
 *
 *  \param robot_handle Handle from the owning robot.
 *  \return A new distancesensor handle or Null on failure. Also might set an error Message.
 */
EXPORT void *distancesensorConstruct(void *robot_handle);

/**
 *  Destroys a distancesensor.
 *
 *  \param distancesensor_handle Handle from the distancesensor to destroy.
 *  \remark Never fails but might set an error Message when Handle is invalid.
 */
EXPORT void distancesensorDestroy(void *distancesensor_handle);

/**
 *  \return The number of distance sensors. This function never fails.
 */
EXPORT int distancesensorNumberOfSensors();

/**
 *  The current distancesensor data.
 *
 *  \param distancesensor_handle Handle from the distancesensor the data is requested.
 *  \return A distanceSensorReadings Handle or Null on failure.
 */
EXPORT void *distancesensorData(void *distancesensor_handle);

/**
 *  Destroys a distanceSensorReadings object.
 *
 *  \param distancesensorreadings_handle Handle of the distanceSensorReadings to destroy.
 *  \remark Never fails but might set an error Message when Handle is invalid.
 */
EXPORT void distancesensorDataDestroy(void *distancesensorreadings_handle);

/**
 *  Registers a callback that gets called when new data is availiable.
 *
 *  \param distancesensor_handle Handle from the distancesensor the status is requested.
 *	\param callback Pointer to a void (*)(void) function, an instance of Callback or Null to remove the callback.
 *	\param type A member of the callback_type enumeration.
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool distancesensorDataCallback(void *distancesensor_handle, void *callback, callback_type type = func_ptr);

/**
 *  Raw data from distanceSensorReadings.
 *
 *  \param distancesensorreadings_handle Handle of the distanceSensorReadings the data is requested.
 *  \return A pointer to an array with the size of distancesensorNumberOfSensors() or Null when Handle is invalid.
 *  \remark The data pointer becomes invalid when the object gets destroyed.
 */
EXPORT float *distancesensorreadingsDistances(void *distancesensorreadings_handle);

/**
 *  Data from distanceSensorReadings by sensor.
 *
 *  \param distancesensorreadings_handle Handle of the distanceSensorReadings the data is requested.
 *	\param position The Sensor the data is requested from.
 *  \return A positive float with the distance in m or a negative value of failure.
 */
EXPORT float distancesensorreadingsDistanceBySensor(void *distancesensorreadings_handle, int position);
