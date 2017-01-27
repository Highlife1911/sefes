#pragma once

#include <deque>

class WaitingRoom
{
public:
	int position(int robotid)
	{
		for (int i = 0; i < que.size(); ++i)
		{
			if (que[i] == robotid)
			{
				return i;
			}
		}
		que.push_back(robotid);
		return static_cast<int>(que.size() - 1);
	}

	void leave()
	{
		que.pop_front();
	}

	std::pair<float, float> realPosition(int id);

	std::deque<int> que;
	int mid;
	float moffset;
};