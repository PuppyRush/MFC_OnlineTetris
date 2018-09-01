//
// Created by pi on 8/21/18.
//

#include "TIWaitingRoom.h"

TIWaitingRoom::TIWaitingRoom(const tetris::t_roomUnique unique, const std::string roomname)
        :TIRoom(unique, roomname)
{

}

const tetris::t_error TIWaitingRoom::addRoom(const tetris::t_roomUnique roomUnique)
{
    if (m_roomSet.count(roomUnique) == 0)
    {
        m_roomSet.insert(roomUnique);
        return toUType( TIRoom::errorCode::Ok);
    }
    else
        return toUType(TIRoom::errorCode::Exist);
}

const tetris::t_error TIWaitingRoom::exitRoom(const tetris::t_roomUnique roomUnique)
{
    if (m_roomSet.count(roomUnique) > 0)
    {
        m_roomSet.erase(roomUnique);
        return toUType(TIRoom::errorCode::Ok);
    }
    else
        return toUType(TIRoom::errorCode::Empty);
}

const tetris::t_error TIWaitingRoom::existRoom(const tetris::t_roomUnique roomUnique)
{
    if (m_roomSet.count(roomUnique) )
        return true;
    else
        return false;
}