#pragma once
#include "RobotinoExtension.h"

/**
 *  Reads the last error.
 *
 *  \return Error Message that is only valid until the next error occurs.
 */
EXPORT const char *getLastError();

/**
 *  Sets the last error.
 *
 *  \param error Message that will also be written to a log file.
 *	\remark This function is threadsafe.
 */
void setError(const char *error);
