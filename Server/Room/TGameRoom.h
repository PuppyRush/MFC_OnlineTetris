/*
 * TGameRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <unordered_map>
#include <mutex>

#include "../../Commons/Room/TIGameRoom.h"
#include "../../Commons/TType.h"
#include "../../Commons/TAtomic.h"

class TGameRoom : public TIGameRoom
{
public:

	enum class errorCode : tetris::t_error
	{
		Ok,
		DuplicatedRoomName = 0,
		OverNameLength,
		PassedTime,
		Nobody
	};

	enum class property : tetris::t_property
	{
		Size = 8
	};

	TGameRoom() {}
	explicit TGameRoom(const std::string roomname);
	virtual ~TGameRoom();

	virtual const tetris::t_error add(const std::shared_ptr<TetrisUser> user) override;
	virtual const tetris::t_error exit(const std::shared_ptr<TetrisUser> user) override;
	virtual const tetris::t_error insertRoom(std::shared_ptr<TIGameRoom> room) override;
    virtual const tetris::t_error regsiteMessage() override;

	inline static std::shared_ptr<TGameRoom> getRameRoom()
	{
		static auto waitingRoom = std::make_shared<TGameRoom>();
		return waitingRoom;
	}

private:
	TAtomic<tetris::t_roomUnique> m_unique;
	std::unordered_map< tetris::t_roomUnique, std::shared_ptr<TIGameRoom>> m_roomMap;
	const tetris::t_error _validator(const TIRoom &room) const override;
};
