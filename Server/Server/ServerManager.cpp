/*
 * ServerManager.cpp
 *
 *  Created on: 2018. 2. 11.
 *      Author: cmk
 */


#include <memory.h>
#include <functional>

#include "ServerManager.h"
#include "MessageHeader.h"

using namespace std;
using namespace server_manager;

ServerManager::ServerManager()
:MAX_WAITING_COUNT(10)
{
	// TODO Auto-generated constructor stub
}

ServerManager::~ServerManager() {
	// TODO Auto-generated destructor stub
}

void* ServerManager::BeginServer(){

	struct sockaddr_in servaddr, cliaddr;
	int listen_sock, accp_sock[MAX_WAITING_COUNT];
	unsigned int addrlen = sizeof(servaddr);
	int i, status ;


	if((listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket Fail");
		exit(0);
	}

	memset(&servaddr, 0, sizeof(servaddr)); //0으로 초기화
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(5905);

	if(bind(listen_sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("bind Fail");
		exit(0);
	}

	while(1)
	{
		listen(listen_sock, MAX_WAITING_COUNT);

		puts("client wait....");

		auto accepted_socket = accept(listen_sock, reinterpret_cast<struct sockaddr *>(&cliaddr), &addrlen);
		if(accp_sock[0] < 0)
		{
			perror("accept fail");
			exit(0);
		}
		if(waitingPool.size()>MAX_WAITING_COUNT)
		{

		}

		connectionThreadParam param(cliaddr,accepted_socket);
		pthread_t tid=0;
		if((status = pthread_create(&tid, nullptr, &ServerManager::AcceptAndWaitConnectionClient, &param)) != 0)
		{
			printf("%d thread create error: %s\n", 0, strerror(status));
			exit(0);
		}
		waitingPool.push_back(tid);
		//pthread_join(tid[0], NULL);
	}

	return 0;

}

void* ServerManager::AcceptAndWaitConnectionClient(void* _sockParam)
{
	using namespace msg_header;

	const size_t buflen = 256;
	const auto sockParam = *reinterpret_cast<connectionThreadParam *>(_sockParam);
	char buf[buflen];
	memset(buf,0,buflen);
	while(1)
	{
		auto readn = read(sockParam.clientSocket, buf, buflen);
		if(readn <= 0)
		{
			perror("Read Error");
			return NULL;
		}

		auto Buffer = new char[readn];

		int header[HEADER_NUM] = {0};
		memcpy(header, Buffer, sizeof(size_t)*HEADER_NUM);

		mOnName onName;
		memset( &onName, 0, sizeof(onName));
		memcpy(&onName, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);

		/*writen = write(sockfd, buf, readn);
		if(readn != writen)
		{
			printf("write error %d : %d\n", readn, writen);
			return NULL;
		}*/
	}

}
