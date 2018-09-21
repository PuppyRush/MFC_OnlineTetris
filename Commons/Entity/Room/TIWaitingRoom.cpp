//
// Created by pi on 8/21/18.
//

#include "TIWaitingRoom.h"
#include "../../TObjectContainerFactory.h"

using namespace std;

TIWaitingRoom::TIWaitingRoom(const RoomInfo& roominfo)
	:TIRoom(roominfo)
{

}

const std::shared_ptr<vector<RoomInfo>> TIWaitingRoom::getWaitingRoomsInfo()
{
    const auto roomcon = TObjectContainerFactory::get()->getContainer<TIWaitingRoom>(property_distinguish::WaitingRoom);
    const size_t totalRoomsize = roomcon->size();
    auto rooms = make_shared<std::vector<RoomInfo>>();

    if(totalRoomsize==0)
        return rooms;

    rooms->reserve(totalRoomsize);
    auto roominfoAry = new RoomInfo[totalRoomsize];

    for(auto room : *roomcon)
    {
        rooms->push_back(RoomInfo(*room->getRoomInfo().get()));
    }

    return rooms;
}