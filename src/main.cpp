#include "PositionalRobot.h"

#include <iostream>
#include <thread>
#include <vector>

#include "shared.h"

int main()
{
	std::vector<std::thread> threads;
	for (int i = 0; i < shared::numberOfRobots; ++i)
	{
		threads.emplace_back([i]()
		{
			try
			{
				PositionalRobot	rob(i);
				rob.run();
			}
			catch (std::exception &e)
			{
				std::cout << e.what();
			}
		});
	}

	for (auto &thread : threads)
	{
		thread.join();
	}

	return EXIT_SUCCESS;
}
