/*
 * Room.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <list>
#include <map>
#include <string>
#include <memory>

#include "../../Commons/TType.h"

class TServerUser;

typedef struct roomInfo;

using namespace std;
class Room
{
public:
	typedef struct pImp;

protected:
	explicit Room(const string roomname, const list<shared_ptr<TServerUser>> userQ);
	virtual ~Room();

private:
	shared_ptr<pImp> m_pImp;

	const bool addUser(shared_ptr<TServerUser> user);

	static const tetris::t_roomUnique getUnique() noexcept
	{
		static tetris::t_roomUniqueAtomic roomUnique(0);
		roomUnique.fetch_add(1);
		return roomUnique.load();
	}
};

