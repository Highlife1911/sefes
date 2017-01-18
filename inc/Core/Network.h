#pragma once
#include "RobotinoExtension.h"

#include <rec/robotino/api2/ComId.h>

#include "BasicNetwork.h"

/** \class RobotinoExtension::Network
 *	\brief Network adapter for communication between Robotinos.
 *
 *	This class implements a simple exchange of data over a custom
 *	NetworkId. The data gets supplied by a raw C-pointer. As an
 *	additional Parameter the size of the data is passed.
 *
 *	To allow communication there is also an set, that contains every
 *	valid NetworkId. The user can use it to keep track over valid
 *	communication targets.
 */

namespace RobotinoExtension
{

class
	EXPORT_CLASS Network : public BasicNetwork
{
public:
	/**
	 *  Constructs the Network adapter and sets the owner.
	 *  Also requests a global unique NetworkId that is needed
	 *	to identify a Robot.
	 *
	 *   \param id	ComId from the owning Robot.
	 */
	explicit Network(const rec::robotino::api2::ComId &id);


	/**
	 *  Destroys the network adapter.
	 */
	virtual ~Network();


	static void processEvents(const rec::robotino::api2::ComId &robot);

protected:

	static std::vector<std::pair<rec::robotino::api2::ComId, NetworkId>> AdapterAssociation;
};
}
