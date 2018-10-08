//
// Created by pi on 8/21/18.
//

#include <chrono>
#include <random>

#include "TIGameRoom.h"
#include "../../TObjectContainerFactory.h"

using namespace std;

TIGameRoom::TIGameRoom()
:TIRoom(property_distinguish::GameRoom)
{}

TIGameRoom::TIGameRoom(const RoomInfo& roominfo)
	:TIRoom(roominfo, property_distinguish::GameRoom)
{

}


std::string TIGameRoom::getBasicGoomNameArbitary()
{
	
	static const char names[][toUType(TIRoom::property::LengthMax)]
		= { {"enjoy!" },
		{"come on guy"},
		{"IM A newbie"},
		{"look at this!"}};
	static constexpr size_t rowsize = sizeof(names) / toUType(TIRoom::property::LengthMax);

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	static std::mt19937_64 ranNum(seed);

	return string(names[ranNum()%rowsize]);
}