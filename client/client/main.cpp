#include "class.h"
#include "includes.h"
#include "SClient.h"
using namespace std;


int main()
{
	setlocale(LC_ALL, "RUS");
	//������������� ���������� WinSock
	SClient client;
	client.connectToS();	
}
