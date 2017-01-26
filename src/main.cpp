#include "PositionalRobot.h"

#include <iostream>
#include <thread>
#include <vector>

#include "shared.h"

const int port = 12080;
const std::string ip = "127.0.0.1:";

int main()
{
	std::vector<std::thread> threads;
	for (int i = 0; i < shared::numberOfRobots; ++i)
	{
		const std::string ipPort = ip + std::to_string(port + i);
		threads.emplace_back([ipPort]()
		{
			try
			{
				PositionalRobot	rob(ipPort);
				rob.run();
			}
			catch (std::exception &e)
			{
				std::cout << e.what();
			}
		});
	}

	return EXIT_SUCCESS;
}
