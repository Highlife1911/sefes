#pragma once
#include "RobotinoExtension.h"

#include "Wrapper/callback_type.h"

/**
 *  Constructs a lasersensor and sets its owner.
 *
 *  \param robot_handle Handle from the owning robot.
 *  \return A new lasersensor handle or Null on failure. Also might set an error Message.
 */
EXPORT void *lasersensorConstruct(void *robot_handle);

/**
 *  Destroys a lasersensor.
 *
 *  \param lasersensor_handle Handle from the lasersensor to destroy.
 *  \remark Never fails but might set an error Message when Handle is invalid.
 */
EXPORT void lasersensorDestroy(void *lasersensor_handle);

/**
 *  The current lasersensor data.
 *
 *  \param lasersensor_handle Handle from the lasersensor the data is requested.
 *  \return A laserSensorReadings Handle or Null on failure.
 */
EXPORT void *lasersensorData(void *lasersensor_handle);

/**
 *  Destroys a laserSensorReadings object.
 *
 *  \param lasersensorreadings_handle Handle of the laserSensorReadings to destroy.
 *  \remark Never fails but might set an error Message when Handle is invalid.
 */
EXPORT void lasersensorDataDestroy(void *lasersensorreadings_handle);

/**
 *  Registers a callback that gets called when new data is availiable.
 *
 *  \param lasersensor_handle Handle from the lasersensor the status is requested.
 *	\param callback Pointer to a void (*)(void) function, an instance of Callback or Null to remove the callback.
 *	\param type A member of the callback_type enumeration.
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool lasersensorDataCallback(void *lasersensor_handle, void *callback, callback_type type = func_ptr);

/**
 *  Raw data from laserSensorReadings.
 *
 *  \param lasersensorreadings_handle Handle of the laserSensorReadings the data is requested.
 *  \return A pointer to an array with the size of lasersensorreadingsNumberOfRays() or Null when Handle is invalid.
 *  \remark The data pointer becomes invalid when the object gets destroyed.
 */
EXPORT float *lasersensorreadingsDistances(void *lasersensorreadings_handle);

/**
 *  Number of laser scans from laserSensorReadings.
 *
 *  \param lasersensorreadings_handle Handle of the laserSensorReadings the data is requested.
 *  \return Number of laser scans or a negative value when Handle is invalid.
 */
EXPORT int lasersensorreadingsNumberOfRays(void *lasersensorreadings_handle);

/**
 *  Scan angle from laserSensorReadings.
 *
 *  \param lasersensorreadings_handle Handle of the laserSensorReadings the data is requested.
 *  \return Angle of laser scans or a negative value when Handle is invalid.
 */
EXPORT float lasersensorreadingsScanAngle(void *lasersensorreadings_handle);
