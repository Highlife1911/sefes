#pragma once
#include "RobotinoExtension.h"

#include <string>

#include <rec/robotino/api2/Com.h>

/** \class RobotinoExtension::Robot
 *	\brief The basic Robot designed for ease-of-use and extensibility.
 *
 *  The Robot either connects locally with the simulator (1.4.2 or above) or
 *	with an already started Robotino. It is intended to run every Robot in an
 *  extra thread to ensure RTAI functionality. Keep in mind that this Program
 *	does not run at any time on the Robotino. Instead it runs on a server that
 *  communicates over a TCP socket with a service daemon.
 *
 *  This class uses a 2 Phase Construction. The constructor initializes the Com
 *	Object. The connect() function is the second phase of the initialization
 *  process. At the end of the connect() funtion the virtual function
 *  initializeComponente() is called. This is requiert because the initialization
 *  of Robot Modules need a valid ComId returned by API2 connect to work properly.
 *  The initializeComponents tries to default construct every Observer that is
 *	still in an invalid state. You can overwrite this function to use your own
 *  Implementations.
 *
 *	\remark	Use only one thread per Robot because it lacks thread safety.
 */

namespace RobotinoExtension
{
class
	EXPORT_CLASS Robot
{
public:

	/**
	 *  Constructs the robot and sets the IP. This function also
	 *	initializes the API2 but does not establish a connection.
	 *
	 *  \param ip	A plain IP without port.
	 *
	 *	\remark	Keep in mind that you can not use any functions of this
	 *			object until a connection is successfully established.
	 */
	explicit Robot(const std::string &ip = "127.0.0.1");


	/**
	 *  Destroys the robot and disconnects if necessary. Do not destroy
	 *  this object when there is still a thread running the main function.
	 */
	virtual ~Robot();


	/**
	 *  Connects the robot with a real robot or the simulator using the IP
	 *  supplied with the Constructor. This functions is blocking until a
	 *  connection got accepted or rejected.
	 *
	 *  \remark This function should be called only once for every robot.
	 *
	 *  \throws A runtime_error occurs when the connection gets rejected
	 *			or the robot is already connected.
	 */
	void connect();


	/**
	 *  Disconnects a connected robot. This function also invalidates every
	 *  API2 functionality.
	 *
	 *  \remark Do not call this function when a thread still runs the Robot.
	 *  \remark Automatically called when destructed and still connected.
	 */
	void disconnect();


	/**
	 *  Returns the connection Status.
	 */
	bool isConnected() const;


	/**
	 *  Returns the IP the Robot got at construction time. This function
	 *  does not interfere with the connectionStatus and is always callable.
	 */
	std::string getAddress() const;


	/**
	 *  Returns the API2 ComId. This id is only valid when connected.
	 *	Hence the ComId becomes invalid when disconnecting.
	 *
	 *	\throws	Throws an exception when called and not connected.
	 */
	rec::robotino::api2::ComId getComId() const;


	/**
	 *  Calls the virtual Callback function of every Observer. Place this
	 *  function inside your event loop because it updates the data for
	 *  every component.
	 *
	 *  \remark This function should be called as fast as possible to get
	 *			the initial sensor data.
	 */
	void processEvents();

private:

	/**
	 *  The API2 Com object. Keeps track of the connection status.
	 */
	rec::robotino::api2::Com mConnection;
};
}
