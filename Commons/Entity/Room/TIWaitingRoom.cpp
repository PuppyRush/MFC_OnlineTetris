//
// Created by pi on 8/21/18.
//

#include "TIWaitingRoom.h"
#include "../../TObjectContainerFactory.h"
#include "../../TAtomic.h"

using namespace std;

TIWaitingRoom::TIWaitingRoom(const RoomInfo& roominfo)
	:TIRoom(roominfo)
{
	this->setRoomNumber(TAtomic::newWaitingRoomNumber());
}

const tetris::t_error TIWaitingRoom::enter(const UserInfo &userinfo)
{

	return this->_enter(userinfo);
}

const tetris::t_error TIWaitingRoom::enter(const TetrisUser &userinfo)
{

	return this->_enter(userinfo);
}

const tetris::t_error TIWaitingRoom::exit(const tetris::t_unique user)
{

	return this->_exit(user);
}


tetris::t_error TIWaitingRoom::addGameRoom(const RoomInfo& room)
{
    if (m_roommap.count(room.unique) == 0)
    {
        m_roommap.insert(make_pair(room.unique, make_shared<RoomInfo>(room)) );
        return toUType( TIRoom::errorCode::Ok);
    }
    else
        return toUType(TIRoom::errorCode::Exist);
}

tetris::t_error TIWaitingRoom::removeGameRoom(const tetris::t_unique unique)
{
    if (m_roommap.count(unique))
    {
        m_roommap.erase(unique);
        return toUType(TIRoom::errorCode::Ok);
    }
    else
        return toUType(TIRoom::errorCode::Empty);
}


const std::shared_ptr<vector<RoomInfo>> TIWaitingRoom::getWaitingRoomsInfo()
{
    const auto roomcon = TObjectContainerFactory::get()->getContainer<TIWaitingRoom>();
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
