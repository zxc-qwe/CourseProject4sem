#pragma once
#include "includes.h"

class SServer
{
	//ServerListningInterface sInterface;
	unsigned short port;
	unsigned short client_count;
public:
	SServer();
	~SServer();
	void setPort(unsigned short port);
	void startServer();
	void closeServer();
	void handle(SOCKET client_socket);
	SOCKET s;
	WSAData wData;
};

class ClientWork 
{
public:
	SOCKET client_socket;
	ClientWork(SOCKET s);
	string recvFromClient();//bool hideLog
	void sendToClient(string str);
};