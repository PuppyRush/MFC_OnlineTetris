/*
 * TetrisUserServer.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include <string>

#include "TUserServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

TUserServer::TUserServer(const std::shared_ptr<TServerSocket> &socket, const t_unique unique)
	:m_socket(socket),
	m_unique(unique)
{
}

TUserServer::~TUserServer()
{
	// TODO Auto-generated destructor stub
}
