#include "includes.h"
#include "SServer.h"
#include "SClient.h"

using namespace std;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SServer server;
	//server.setPort(1024);
	server.startServer();
}