#pragma once
#include "RobotinoExtension.h"

#include "Wrapper/callback_type.h"

/**
 *  Constructs network and sets its owner.
 *
 *  \param robot_handle Handle from the owning robot.
 *  \return A new network handle or Null on failure. Also might set an error Message.
 */
EXPORT void *networkConstruct(void *robot_handle);

/**
 *  Destroys the network.
 *
 *  \param network_handle Handle from the network to destroy.
 *  \remark Never fails but might set an error Message when Handle is invalid.
 */
EXPORT void networkDestroy(void *network_handle);

/**
 *  Returns the network id from this Adapter.
 *
 *  \param network_handle Handle from the network adapter the id is requested.
 */
EXPORT int networkId(void *network_handle);

/**
 *  Sends a message to a network device.
 *
 *  \param network_handle Handle from the network adapter the message is sended from.
 *  \param target_id The target of the network request.
 *	\param data Pointer to the message data.
 *	\param size Size of the message data in bytes.
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool networkSend(void *network_handle, int target_id, const char *data, size_t size);

/**
 *  Sends a message to all registered network device.
 *
 *	\param network_handle Handle from the network adapter the message is sended from.
 *	\param data Pointer to the message data.
 *	\param size Size of the message data in bytes.
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool networkBroadcast(void *network_handle, const char *data, size_t size);

/**
 *  Registers a callback that gets called when a new message arrives.
 *
 *  \param network_handle Handle from the network device the messages are requested.
 *	\param callback Pointer to a void (*)(void) function, an instance of Callback or Null to remove the callback.
 *	\param type A member of the callback_type enumeration.
 *  \return EXIT_FAILURE or EXIT_SUCCESS.
 */
EXPORT bool networkCallback(void *network_handle, void *callback, callback_type type = func_ptr);
