#pragma once
#include "RobotinoExtension.h"

#include "rec/robotino/api2/PowerManagement.h"

#include "Module.h"

/** \class RobotinoExtension::Battery
 *	\brief Battery class that supplies a basic power management.
 *
 *	This class holds the current Voltage output of the Battery.
 *	To simplify its usage the value gets converted to a percentage.
 *
 *	A callback function can be used to take action when the power
 *	level runs low.
 */

namespace RobotinoExtension
{
class
	EXPORT_CLASS Battery : private rec::robotino::api2::PowerManagement, public Observer
{
public:
	/**
	 *  Constructs the battery and sets its owner.
	 *
	 *   \param id	ComId from the owning Robot.
	 */
	explicit Battery(const rec::robotino::api2::ComId &id);


	/**
	 *  Destroys the battery.
	 */
	virtual ~Battery() = default;


	/**
	 *  Returns the current power level. It ranges from 0 to 1.
	 */
	float currentPower() const;

private:

	virtual void readingsEvent(float battery_voltage, float system_current, bool ext_power, int num_chargers, const char *batteryType, bool batteryLow, int batteryLowShutdownCounter) override final;

	/**
	 *  Converts a volatge to a percentage as float from 0 to 1.
	 *	The percentage means the charge level of the battery.
	 */
	static float voltageToPercentage(float v);


	/**
	 *  Disable copying of this Object.
	 */
	Battery(const Battery &);
	Battery &operator=(const Battery &);
};
}
