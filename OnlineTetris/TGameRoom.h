#pragma once

#include "..\Commons\Entity\Room\TIGameRoom.h"

class TGameRoom : public TIGameRoom
{
public:
	virtual ~TGameRoom();
	virtual void registryMessage() override;
	virtual const tetris::t_error _validator(const TIRoom &room) const override;

	static auto get()
	{
		static auto room = tetris::t_ptr<TGameRoom>(new TGameRoom());
	}


private:
	TGameRoom();
	void createGameroom(const TMessageObject& msg);
};

