#include "stdafx.h"
#include "TWaitingRoom.h"
#include "WaitingRoomDialog.h"

TWaitingRoom::TWaitingRoom()
{
	registryMessage();
}

TWaitingRoom::TWaitingRoom(const std::shared_ptr<RoomInfo> roominfo, const std::vector<UserInfo>& userinfoAry)
	:TIWaitingRoom(roominfo, userinfoAry)
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
	this->addCaller(make_pair(toUType(SERVER_MSG::WAITINGROOM_INFO), std::bind(&TWaitingRoom::updateWaitingRoom, this, std::placeholders::_1)));
	this->addCaller(make_pair(toUType(SERVER_MSG::WAITINGROOM_USER), std::bind(&TWaitingRoom::updateWaitingUsers, this, std::placeholders::_1)));
}

void TWaitingRoom::updateWaitingRoom(const TMessageObject& msg)
{ 
	const auto info = TMessageObject::toMessage<mWaitingRoomInfo>(msg);
	WaitingRoomDlg::getDialog()->updateRoomInfo(info);
	sizeof(RoomInfo);
}

void TWaitingRoom::updateWaitingUsers(const TMessageObject& msg)
{
	const auto info = TMessageObject::toMessage<mWaitingUserInfo>(msg);
	WaitingRoomDlg::getDialog()->updateRoomUserInfo(info);
}
