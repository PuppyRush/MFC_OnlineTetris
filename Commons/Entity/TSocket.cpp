#include "TSocket.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif

using namespace std;

TetrisSocket::TetrisSocket(const int domain, const int type, const int protocol, const IPString ip, const tetris::t_port port)
         :m_closeSocket(true),
         m_domain(domain),
         m_type(type),
         m_protocol(protocol),
         m_port(port),
         m_ip(ip),
         m_socket(0)
{
    using namespace tetris;
}

TetrisSocket::TetrisSocket(const int domain, const int type, const int protocol, tetris::t_socket socket)
         :m_closeSocket(true),
         m_domain(domain),
         m_type(type),
         m_protocol(protocol),
         m_socket(socket)
{
}

TetrisSocket::~TetrisSocket()
{

}

tetris::t_error TetrisSocket::accept()
{
    tetris::t_socket socket = _accept();
    if (socket>=0)
        return socket;
    else
        std::numeric_limits<tetris::t_socket>::max();
}

tetris::t_error TetrisSocket::connect()
{
    return _connect();
}

tetris::t_error TetrisSocket::close()
{
    _end();
    return _close(m_socket);
}

void TetrisSocket::_end()
{
    m_closeSocket = false;
}

void TetrisSocket::send(const TMessageObject& msg)
{
    const auto written = _sendTo(msg.getMessage(), msg.getSize());
    if (written <= 0)
    {
        //writeLog("error sendto");
    }
}

const TMessageObject TetrisSocket::recv()
{
    return _recvFrom();
}
