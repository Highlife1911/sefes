#include "PositionalRobot.h"

#include <iostream>
#include <conio.h>

#include <Core/Drive.h>
#include <Core/NorthStar.h>
#include <Core/Position.h>

#include <Components/Navigation.h>

using RobotinoExtension::Position;

namespace
{
float randomFloat()
{
	const float min = -4.0f;
	const float max = 4.0f;
	const float dist = max - min;

	int val = rand();

	return (dist * static_cast<float>(val % 4096) / 4096) + min;
}

std::vector<Position> &buildList(int stops)
{
	static std::vector<Position> list;
	for (int i = 0; i < stops; i++)
	{
		float a = randomFloat();
		float b = randomFloat();

		std::cout << "Target " << i + 1 << ": (" << a << ", " << b << ")" << std::endl;
		list.push_back(Position(a, b));
	}

	return list;
}

const int NumberOfStops = 5;
std::vector<Position> &TargetList = buildList(NumberOfStops);
}

PositionalRobot::PositionalRobot(const std::string &ip)
	: Robot(ip)
	, mNavigation(nullptr)
	, mNorthStar(nullptr)
	, mDrive(nullptr)
	, mTarget(0)
{
	connect();
	initializeComponents();
}

PositionalRobot::~PositionalRobot()
{
	destroyComponents();
	disconnect();
}

void PositionalRobot::run()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));

	int current_target = -1;

	while (isConnected() && !_kbhit())
	{
		processEvents();

		if (current_target != mTarget)
		{
			current_target = mTarget;
			mNavigation->driveToPosition(TargetList[mTarget], 0.5f, 0.05f);
		}

		std::cout << ".";
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

void PositionalRobot::initializeComponents()
{
	mDrive = new RobotinoExtension::Drive(getComId());
	mNorthStar = new RobotinoExtension::NorthStar(getComId());

	mNavigation = new RobotinoExtension::Navigation(mDrive, mNorthStar);
	mNavigation->setCallback(this);
}

void PositionalRobot::event()
{
	mTarget++;
	mTarget %= NumberOfStops;
}

void PositionalRobot::destroyComponents()
{
	delete mNavigation;

	delete mDrive;
	delete mNorthStar;
}