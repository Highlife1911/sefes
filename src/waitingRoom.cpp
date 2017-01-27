#include "waitingRoom.h"

#include "shared.h"

std::pair<float, float> WaitingRoom::realPosition(int id)
{
	auto &inst = shared::instance();
	auto &pos = inst.waitingRoomExit[mid];

	return {pos.first + id * moffset, pos.second};
}