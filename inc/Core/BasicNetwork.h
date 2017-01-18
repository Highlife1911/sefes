#pragma once
#include "RobotinoExtension.h"

#include <map>
#include <mutex>
#include <vector>

#include "NetworkModule.h"

/** \class RobotinoExtension::Network
 *	\brief BasicNetwork adapter for communication.
 *
 *	This class implements a simple exchange of data over a custom
 *	NetworkId. The data gets supplied by a raw C-pointer. As an
 *	additional Parameter the size of the data is passed.
 *
 *	To allow communication there is also an set, that contains every
 *	valid NetworkId. The user can use it to keep track over valid
 *	communication targets.
 *
 *	This class represents the lowest level of Network communication.
 */

namespace RobotinoExtension
{

/**
 *  The NetworkId is basically an unique integer.
 */
typedef int NetworkId;

class
	EXPORT_CLASS BasicNetwork : public NetworkModule
{
public:

	BasicNetwork();


	/**
	 *  Destroys the network adapter.
	 */
	virtual ~BasicNetwork();


	/**
	 *  Returns the NetworkOd of This Object.
	 *	The NetworkId is an Integer greater 0.
	 */
	NetworkId getNetworkId() const;


	/**
	 *  Sends data to a specific Robotino that has the NetworkId target_id.
	 *
	 *	\param target_id	A valid NetworkId from a running Robotino.
	 *	\param data			Pointer to RAW data. The data should not be temporary.
	 *	\param size			The size of the data.
	 */
	void sendData(NetworkId target_id, const char *data, size_t size);


	/**
	 *  Sends data to all Robotinos that have a registered NetworkId.
	 *
	 *	\param data		Pointer to RAW data. The data should not be temporary.
	 *	\param size		The size of the data.
	 */
	void broadcastData(const char *data, size_t size);


	/**
	 *  Processes all messages that are send to this adapter and triggers its callback.
	 */
	void processEvents();

	/**
	 *  Returns an unique id for network communication.
	 */
	static NetworkId RegisterNetwork(BasicNetwork *adapter);


	/**
	 *  Unregisters an unique id for network communication.
	 */
	static void UnregisterNetwork(NetworkId id);


	/**
	 *  Returns a copy of a vector that contains all valid NetworkId's.
	 *	The vector might be out of date when used because of connections/ disconnections
	 *  from other threads.
	 */
	static std::vector<NetworkId> FindAllNetworkObjects();

protected:


	void send(const std::vector<char> &msg);


	/**
	 *  An unique NetworkId used for communication.
	 */
	NetworkId mNetworkId;


	/**
	 *  A vector that contains every NetworkId. Every access to this variable
	 *	needs to be secured with the NetworkMutex.
	 */
	static std::map<NetworkId, BasicNetwork *> NetworkObjects;


	/**
	 *  A mutex to schedule concurrent accesses to the NetworkId vector.
	 */
	static std::mutex NetworkMutex;


	static std::multimap<NetworkId, std::vector<char>> NetworkBuffer;
};

}