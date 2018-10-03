//
// Created by pi on 8/21/18.
//

#include "TIGameRoom.h"
#include "../../TObjectContainerFactory.h"

TIGameRoom::TIGameRoom(const RoomInfo& roominfo)
	:TIRoom(roominfo)
{

}

const tetris::t_error TIGameRoom::enter(const UserInfo& userinfo)
{
	auto usercon =  TObjectContainerFactory::get()->getContainer<TetrisUser>();
	if(usercon->exist(userinfo.unique))
	{
		//auto newroom = TGameRoom::makeGameRoom(userinfo);
		//usercon->at(userinfo.unique)->setPlace(property_distinguish::GameRoom, newroom->getUnique()));


		//this->addGameRoom(roominfo); aafsdfsdfgs??
	}
	else
		assert(0);

	this->_enter(userinfo);
}
const tetris::t_error TIGameRoom::enter(const TetrisUser& userinfo)
{

	this->_enter(userinfo);
}
const tetris::t_error TIGameRoom::exit(const tetris::t_unique user)
{

	//this->_exit(userinfo);
}