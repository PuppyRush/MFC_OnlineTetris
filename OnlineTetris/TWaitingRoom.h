#pragma once

#include "../Commons/Entity/Room/TIWaitingRoom.h"

class TWaitingRoom : public TIWaitingRoom
{
public:
	~TWaitingRoom();

	virtual void registryMessage() override;
	virtual const tetris::t_error _validator(const TIRoom &room) const override;
	//void getWaitingUsers(const shared_ptr<WaitingRoom> waitRoom);

	static shared_ptr<TWaitingRoom> get()
	{
		static auto room = std::shared_ptr<TWaitingRoom>(new TWaitingRoom());
		return room;
	}

private:
	TWaitingRoom();
	TWaitingRoom(const std::shared_ptr<RoomInfo> roominfo, const std::vector<UserInfo>& userinfoAry);
	void updateWaitingRoom(const TMessageObject& msg);
	void updateWaitingUsers(const TMessageObject& msg);
};

