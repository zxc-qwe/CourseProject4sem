#pragma once

#include "includes.h"
using namespace std;
class SClient
{
	unsigned short server_port;
	SOCKET s;
public:
	int menuadmin();
	int usermenu();
	void sendToS(string str);
	string recvFromS();
	void UserWork();
	void add_user();
	void userlist();
	void deleteuser();
	void add_expert();
	void expertmenu();
	void expertwork();
	void expertlist();
	void deleteexpert();
	void evaluate();
	void calculation();
	void connectToS();
	SClient();
	~SClient();
	void startMenu();
};

//class ServerWork
//{
//public:
//	SOCKET server_socket;
//	ServerWork(SOCKET s);
//	
//};