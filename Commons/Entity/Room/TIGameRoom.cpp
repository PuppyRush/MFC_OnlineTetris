//
// Created by pi on 8/21/18.
//

#include "TIGameRoom.h"
#include "../../TObjectContainerFactory.h"

TIGameRoom::TIGameRoom()
:TIRoom(property_distinguish::GameRoom)
{}

TIGameRoom::TIGameRoom(const RoomInfo& roominfo)
	:TIRoom(roominfo, property_distinguish::GameRoom)
{

}
