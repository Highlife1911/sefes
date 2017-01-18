#pragma once
/**
 *  \mainpage The RobotinoExtension library
 *
 *	<h1>Introduction</h1>
 *
 *	This is the automatic generated documentation for the RobotinoExtension library.
 *	The library is written in plain C++ and using the Boost C++ library for C++11 features.
 *	There is a additional Java-Wrapper generated from our sources using SWIG.
 *
 *  We use a 3 layer model to develop on top of festo's API2. The RobotinoExtension::Core
 *	library represents the lowest level in this hirachie. It is the only part that interacts
 *	with festo's API2 directly. There is also no interaction between modules. To simplify
 *	further developement the Core library unificates all units to:
 *	<ul>
 *		<li>Distance in m</li>
 *		<li>Speed in m/s</li>
 *		<li>Angle in rad</li>
 *		<li>Angle speed in rad/s</li>
 *		<li>Battery capacity in % ranges from 0 to 1</li>
 *	</ul>
 *
 *  The Robot either connects locally with the simulator (1.4.2 or above) or
 *	with an already started Robotino. It is inteded to run every Robot in an
 *  extra thread to ensure RTAI functionality. Keep in mind that this Programm
 *	does not run at any time on the Robotino. Instead it runs on a server that
 *  communicates over a TCP socket with a service daemon. The Robot itself can
 *	act as a Server, but this is not recommended for multiple Robots because
 *	the Robot has only a slow single core cpu.
 *
 *  The Robot uses a 2 Phase Construction. The constructor initializes the Com
 *	Object. The connect() function is the second phase of the initialization
 *  process. At the end of the connect() funtion the virtual function
 *  initializeComponente() is called. This is requiert because the initialization
 *  of Robot Modules need a valid ComId returned by API2 connect to work properly.
 *  The initializeComponents tries to default construct every Observer that is
 *	still in an invalid state. You can overwrite this function to use your own
 *  Implementations.
 *
 *  \image html overview.png
 */


/**
*  Set up the environment specific defines. Also disable some unimportant warnings.
*
*  /define	EXPORT_CORE	The plattform dll export macro for classes.
*						Resolves for correct export/import code for Windows and Linux.
*/

#ifdef WIN32
#  pragma warning(disable: 4251)
#  pragma warning(disable: 4275)
#  ifdef EXPORT_EXTENSION
#	 define EXPORT_CLASS __declspec(dllexport)
#  else
#	 define EXPORT_CLASS __declspec(dllimport)
#  endif
#else
#  ifndef SWIG
#	 define EXPORT_CLASS __attribute__ ((visibility ("default")))
#    define nullptr Null
#    define override
#    define final
#  endif
#endif
#define EXPORT extern "C" EXPORT_CLASS
