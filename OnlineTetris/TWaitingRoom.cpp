#include "stdafx.h"
#include "TWaitingRoom.h"
#include "WaitingRoomDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


TWaitingRoom::TWaitingRoom()
{
	registryMessage();
}

TWaitingRoom::TWaitingRoom(const std::shared_ptr<RoomInfo> roominfo, const std::vector<UserInfo>& userinfoAry)
	:TIWaitingRoom()
{
	registryMessage();
}


TWaitingRoom::~TWaitingRoom()
{
}

const tetris::t_error TWaitingRoom::_validator(const TIRoom &room) const
{

	return toUType(property_error::eOK);
}

void TWaitingRoom::registryMessage()
{
	this->addCaller(make_pair(toUType(WAITINGROOM_MSG::WAITINGROOM_INFO), std::bind(&TWaitingRoom::updateWaitingRoom, this, std::placeholders::_1)));
	this->addCaller(make_pair(toUType(WAITINGROOM_MSG::WAITINGROOMS_INFO), std::bind(&TWaitingRoom::updateWaitingGameRooms, this,std::placeholders::_1)));
	this->addCaller(make_pair(toUType(WAITINGROOM_MSG::WAITINGROOM_USER), std::bind(&TWaitingRoom::updateWaitingUsers, this, std::placeholders::_1)));
	
}

void TWaitingRoom::updateWaitingGameRooms(const TMessageObject& msg)
{
	const auto info = TMessageObject::toMessage<mWaitingGameRoomInfo>(msg);
	WaitingRoomDlg::getDialog()->updateGameRooms(info);
	sizeof(RoomInfo);
}

void TWaitingRoom::updateWaitingRoom(const TMessageObject& msg)
{ 
	const auto info = TMessageObject::toMessage<mWaitingRoomInfo>(msg);
	WaitingRoomDlg::getDialog()->updateWaitingRoom(info);
	sizeof(RoomInfo);
}

void TWaitingRoom::updateWaitingUsers(const TMessageObject& msg)
{
	const auto info = TMessageObject::toMessage<mWaitingUserInfo>(msg);
	WaitingRoomDlg::getDialog()->updateRoomUser(info);
}

