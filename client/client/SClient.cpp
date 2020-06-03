#include "SClient.h"
#include "class.h"
#define BREAK_THREAD 1;
#pragma warning(disable:4996)

//ServerWork::ServerWork(SOCKET s)
//{
//	server_socket = s;
//}

SClient::SClient()
{
}


SClient::~SClient()
{
}

void SClient::connectToS()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0);
	s = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(1024);
	dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	while (connect(s, (sockaddr*)&dest_addr, sizeof(dest_addr)) == SOCKET_ERROR)
	{
		cout << "Ошибка соединения с сервером, проверьте статус сервера и повторите попытку" << endl;
		system("pause");
	}
	cout << "======== АВТОРИЗАЦИЯ ========" << endl;
	cout << "Введите логин: ";
	char login[100], password[100], flag = '0', flag1 = '1';
	cin.getline(login, 100);
	cout << "Введите пароль: ";
	cin.getline(password, 100);
	//char rezult[1000];
	send(s, login, sizeof(login), 0);
	send(s, password, sizeof(password), 0);

	recv(s, &flag, sizeof(flag), 0);

	if (flag == '0') {
		cout << "Неверный логин или пароль\n";
		system("pause");
		sendToS("Exit");
	}
	if (flag == '1') {
		menuadmin();
	}
	if (flag == '2') {
		usermenu();
	}
	if (flag == '3') {
		expertmenu();
	}

	closesocket(s);
}
void SClient::sendToS(string str)
{
	const int BUFFER_SIZE = 1024;
	char buf[BUFFER_SIZE];
	for (int i = 0; i < (str.length() / (BUFFER_SIZE - 1)); i++)
	{
		buf[0] = '1';
		str.copy(buf + 1, BUFFER_SIZE - 1, i * (BUFFER_SIZE - 1));
		try {
			if (send(s, buf, sizeof(buf), 0) == SOCKET_ERROR)
				throw BREAK_THREAD;
		}
		catch (int e) {
			cout << "Возникло исключение. Номер исключения " << e << endl;
		}
	}
	buf[0] = '0';
	str.copy(buf + 1, BUFFER_SIZE - 1, str.length() / (BUFFER_SIZE - 1));
	buf[str.length() % (BUFFER_SIZE - 1) + 1] = '\0';
	try {
		if (send(s, buf, sizeof(buf), 0) == SOCKET_ERROR)
			throw BREAK_THREAD;
	}
	catch (int e) {
		cout << "Возникло исключение. Номер исключения " << e << endl;
	}
}
string SClient::recvFromS()
{
	string result = "";
	const int BUFFER_SIZE = 1024;
	char buf[BUFFER_SIZE];
	try {
		if (recv(s, buf, sizeof(buf), 0) == SOCKET_ERROR)
			throw BREAK_THREAD;
	}
	catch (int e) {
		cout << "Возникло исключение. Номер исключения " << e << endl;
	}
	result += buf + 1;
	while (buf[0] == 1)
	{
		try {
			if (recv(s, buf, sizeof(buf), 0) == SOCKET_ERROR)
				throw BREAK_THREAD;
		}
		catch (int e) {
			cout << "Возникло исключение. Номер исключения " << e << endl;
		}
		result += buf + 1;
	}
	return result;

}
void SClient::startMenu()
{
	bool back = 0;
	while (!back)
	{
		system("cls");
		system("title Стартовое меню");
		cout << "Добро пожаловать в приложение магазина \"Инь-янь\"" << endl;
		cout << "1. Авторизация\n2. Регистрация\n0. Выход\n";
		int swich;
		cin >> swich;
		switch (swich)
		{
		case 1:
		
			break;
		case 2:
			break;
		case 0:
			sendToS("Exit");
			back = 1;
			break;
		}
	}
}