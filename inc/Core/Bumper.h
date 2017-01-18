#pragma once
#include "RobotinoExtension.h"

#include <rec/robotino/api2/Bumper.h>

#include "Module.h"

/** \class RobotinoExtension::Bumper
 *	\brief Collision detection system that gets informed about the Bumper status.
 *
 *	The default bumper with basic callbacks.
 */

namespace RobotinoExtension
{
class
	EXPORT_CLASS Bumper : private rec::robotino::api2::Bumper, public Observer
{
public:
	/**
	 *  Constructs the bumper and sets its owner.
	 *
	 *   \param id	ComId from the owning Robot.
	 */
	explicit Bumper(const rec::robotino::api2::ComId &id);


	/**
	 *  Destroys the bumper.
	 */
	virtual ~Bumper() = default;


	/**
	 *  Returns the current bumper status.
	 */
	bool isTouching() const;

private:

	virtual void bumperEvent(bool hasContact) override final;


	/**
	 *  Disable copying of this Object.
	 */
	Bumper(const Bumper &);
	Bumper &operator=(const Bumper &);
};
}
