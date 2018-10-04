/*
 * TWaitingRoom.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include <ctime>

#include "TWaitingRoom.h"
#include "TGameRoom.h"
#include "../../Commons/TObjectContainerFactory.h"
#include "../../Commons/TMessageSender.h"
#include "../../Commons/TMessageStruct.h"
#include "../../Commons/TMessageObject.h"
#include "../../Commons/structs.h"
#include "../../Commons/Validator.h"
#include "../../Commons/TypeTraits.h"
#include "../../Commons/TProperty.h"


TWaitingRoom::TWaitingRoom(const RoomInfo& roominfo)
:TIWaitingRoom(roominfo),
 m_waitingroomCon(TObjectContainerFactory::get()->getContainer<TIWaitingRoom>())
{
    registryMessage();
}

TWaitingRoom::~TWaitingRoom()
{
	// TODO Auto-generated destructor stub
}

void TWaitingRoom::registryMessage()
{
    this->addCaller(make_pair(toUType(GAMEROOM_MSG::CREAT_INIT), std::bind(&TWaitingRoom::recvCreateRoomInfo, this, std::placeholders::_1)));
}

const tetris::t_error TWaitingRoom::_validator(const TIRoom &room) const
{
	//const auto roominfo = room.getRoomInfo();
	//const auto roomname = roominfo->roomName;
	//if (!stringLengthCheck(roominfo->roomName, toUType(property::LengthMin), toUType(property::LengthMin)))
	//	return errorCode::NameLength;
	//
	//for (const auto _room : m_roomMap)
	//{
	//	if (_room.second->getRoomInfo()->roomName.compare(roomname) == 0)
	//		return errorCode::NameLength;
	//}
	//
	//const auto currentTime = time(NULL);
	//if (std::difftime(currentTime, roominfo->makeTime) < 0)
	//	return errorCode::PassedTime;
	//
	////if(roominfo->users.empty())
	////	return errorCode::Nobody;
	//
	//return errorCode::Ok;
}

void TWaitingRoom::sendWaitingUsers(const tetris::t_socket socketUnique)
{
    const auto userinfo = this->getUserInfo();
    const size_t size = userinfo->size();
    if(size==0)
        return;

    UserInfo* userinfoAry = new UserInfo[size];

    const auto routine = size/USER_LENGTH+1;
    size_t accu=0;
    for(size_t i=0 ; i < routine ; i++)
    {
        memset(userinfoAry,0,sizeof(UserInfo));
        for (size_t l = 0; l < USER_LENGTH && l < userinfo->size() ; l++)
            userinfoAry[l] = UserInfo(userinfo->at(l+accu).unique, userinfo->at(l+accu).name);
        accu += userinfo->size();

        const auto header2 = Header( toUType(Priority::Normal), toUType(WAITINGROOM_MSG::WAITINGROOM_USER));
        mWaitingUserInfo waitingroom_msg(header2, this->getUnique() ,userinfoAry, size);

        TMessageSender::get()->push( TMessageObject::toMessage(socketUnique,&waitingroom_msg));
    }

}
void TWaitingRoom::sendWaitingRooms(const tetris::t_socket socketUnique)
{
    const size_t totalRoomsize = m_roommap.size();
    if(totalRoomsize==0)
        return ;

    auto roominfoAry = new RoomInfo[totalRoomsize];

    const auto routine = totalRoomsize/ROOM_LENGTH+1;
    size_t accu=0;
    for(auto pair : m_roommap)
    {
        for (size_t l = 0; l < ROOM_LENGTH && l < totalRoomsize ; l++)
            roominfoAry[l] = RoomInfo(*pair.second.get());
        accu += totalRoomsize;

        const auto header2 = Header( toUType(Priority::Normal), toUType(WAITINGROOM_MSG::WAITINGROOMS_INFO));
        mWaitingRoomsInfo waitinguser_msg(header2,roominfoAry, totalRoomsize);

        TMessageSender::get()->push( TMessageObject::toMessage(socketUnique,&waitinguser_msg));
    }
}

void TWaitingRoom::sendWaitingRoomInfo(const tetris::t_socket socketUnique)
{
    const auto info = *TObjectContainerFactory::get()->getContainer<TIWaitingRoom>()->begin()->getRoomInfo().get();
    const auto header = Header( toUType(Priority::Normal), toUType(WAITINGROOM_MSG::WAITINGROOM_INFO));
    mWaitingRoomInfo roominfo(header,info);

    T_SEND(socketUnique, &roominfo);
}

void TWaitingRoom::recvCreateRoomInfo(const TMessageObject &obj)
{
    auto msg = TMessageObject::toMessage<mRoomInitInfo>(obj);
    RoomInfo roominfo(TAtomic::newUnique(), time(0) , msg.roominfo.roomName,
                    msg.roominfo.roomNumber, msg.roominfo.fullUserCount, 1);
    UserInfo master(msg.unique, m_userCon->at(msg.unique)->getUserName().c_str());

    updateWaitingRooms(roominfo, master);
}

void TWaitingRoom::updateWaitingRooms(const RoomInfo& roominfo, const UserInfo& master)
{
    property_error result;

    if(m_userCon->exist(master.unique))
    {
        addGameRoom(roominfo, master);
        TGameRoom::makeShared(roominfo, master);

        result = property_error::eOK;
    }
    else
        result = property_error::eFail;

    const auto header = Header( toUType(Priority::Normal), toUType(GAMEROOM_MSG::CREATE_GAMEROOM));
    mPermit permit(header, toUType(result));
    T_BROADCAST(&permit);
}