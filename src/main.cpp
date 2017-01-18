#include "PositionalRobot.h"

#include <iostream>

int main()
{
	try
	{
		PositionalRobot	rob(ROBOTINO_IP);
		rob.run();
	}
	catch ( std::exception &e )
	{
		std::cout << e.what();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
