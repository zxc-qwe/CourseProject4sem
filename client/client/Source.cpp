#include "includes.h"
#include "class.h"
#include"SClient.h"
using namespace std;

void Users::checkInt(int &Value) {
	while (std::cin.fail() || std::cin.get() != '\n') {
		std::cout << "Invalid value. try again: ";
		std::cin.clear();
		rewind(stdin);
		std::cin >> Value;
	}
}
int Users::checkWord(char *str) {
	while (cin.get() != '\n') {
		rewind(stdin);
		return 0;
	}
	int i = -1;
	while (str[++i]) {
		if (!((str[i] >= '�' && str[i] <= '�') || (str[i] >= '�' && str[i] <= '�'))) {
			return 0;
		}
	}
	return 1;
}
int SClient::menuadmin() {
	system("cls");
	while (true) {
		system("cls");
		int choice;
		cout << "======= ���� �������������� =======" << endl;
		cout << "1. ������ � ��������������\n2. ������ � ����������\n3. �����\n��� �����: ";
		cin >> choice;
		Admin::checkInt(choice);
		cout << endl;

		switch (choice) {
		case 1:
			UserWork();
			break;
		case 2:
			expertwork();
			break;
		case 3:
			sendToS("Exit");
			return 0;
		}
	}
}
int SClient::usermenu() {
	system("cls");
	while (true) {
		system("cls");
		int choice;
		cout << "======= ���� ������������ =======" << endl;
		cout << "1. ������ ����� �����\n2.\n3. �����\n��� �����: ";
		cin >> choice;
		Admin::checkInt(choice);
		cout << endl;

		switch (choice) {
		case 1:
			sendToS("Calculate");
			calculation();
			break;
		case 3:	
			sendToS("Exit");
			return 0;
		}
	}
}

void SClient::UserWork() {
	system("cls");
	int choice;
	cout << "======= ������ � �������������� =======" << endl;
	cout << "1. �������� ������������\n2. �������� �������������\n3. ������� ������������\n4. �����\n��� �����: ";
	cin >> choice;
	Admin::checkInt(choice);
	cout << endl;

	switch (choice) {
	case 1:
		sendToS("Add user");
		add_user();
		break;
	case 2:
		sendToS("Show users");
		userlist();
		break;
	case 3:
		sendToS("Delete user");
		deleteuser();
		break;
	case 4:
		return;
	}
}
void SClient::expertmenu() {
	system("cls");
	while (true) {
		system("cls");
		int choice;
		cout << "======= ���� �������� =======" << endl;
		cout << "1. ����������� ������\n2. �������� ������\n3. �����\n��� �����: ";
		cin >> choice;
		Admin::checkInt(choice);
		cout << endl;

		switch (choice) {
		case 1:
			sendToS("Evaluate");
			evaluate();
			break;
		case 2:
			break;
		case 3:
			sendToS("Exit");
			return;
		}
	}
}
void SClient::calculation() {
	system("cls");
	char message[15];
	recv(s, message, sizeof(message), 0);
	if (message == "Ok") {
		cout << "======= ������ ����� ����� =======" << endl;
		cout << "1 - ���������� ������� ������������\n2 - ���������� �������������� �������������\n3 - ���������� ������ �� �����\n4 - ���������������� ������������ �����������\n\n";
		float W[4] = { 0, 0, 0, 0 };
		for (int i = 0; i < 4; i++) {
			recv(s, (char*)& W[i], sizeof(float), 0);
			cout << "��� ���� " << i+1 << " w[" << i+1 << "] ����� " << W[i] << endl;
		}
		system("pause");
	}
	if (message == "Not enough") {
		cout << "������������ ��������� ������ ��� ������� ����� �����";
		system("pause");
	}
}
void SClient::evaluate() {
	system("cls");
	int num;
	cout << "======= ����������� ������ =======" << endl;
	cout << "1 - ���������� ������� ������������\n2 - ���������� �������������� �������������\n3 - ���������� ������ �� �����\n4 - ���������������� ������������ �����������\n\n";
	float z[4][4];
	int x;
	z[0][0] = 0; z[1][1] = 0; z[2][2] = 0; z[3][3] = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j || (i == 1 && j == 0) || (i == 2 && j == 0) || (i == 2 && j == 1)) {

			}
			else {
				cout << "������� ������ �������� " << i + 1 << " ������������ " << j + 1 << " (x/30): ";
				do {
					cin >> x;
					if (x < 0 || x > 30) {
						cout << "���������� ������ �������� � ���������� [0;30]: ";
						cin >> x;
					}
				} while (x < 0 && x > 30);
				z[i][j] = (float)x / 30.0f;
				int y = 30 - x;
				z[j][i] = (float)y / 30.0f;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			send(s, (char*)& z[i][j], sizeof(float), 0);
		}
	}
}
void SClient::expertwork() {
	system("cls");
	int choice;
	cout << "======= ������ � ���������� =======" << endl;
	cout << "1. �������� ��������\n2. �������� ���������\n3. ������� ��������\n4. �����\n��� �����: ";
	cin >> choice;
	Admin::checkInt(choice);
	cout << endl;

	switch (choice) {
	case 1:
		sendToS("Add expert");
		add_expert();
		break;
	case 2:
		sendToS("Show experts");
		expertlist();
		break;
	case 3:
		sendToS("Delete expert");
		deleteexpert();
		break;
	case 4:
		return;
	}
}
void SClient::deleteexpert() {
	system("cls");
	int flag;
	char login[30];
	cout << "======= �������� �������� =======" << endl;
	cout << "������� ��� �������� ��� ��������: ";
	cin.getline(login, 30);
	send(s, login, sizeof(login), 0);
	recv(s, (char *)& flag, sizeof(int), 0);
	if (flag == 1) {
		cout << "������� " << login << " ������." << endl;
	}
	if (flag == 0) {
		cout << "������� � ����� ������ �� ��� ������." << endl;
	}
	system("pause");
}
void SClient::expertlist() {
	system("cls");
	int num;
	char login[30], password[30];
	cout << "              ��� ��������              |          ������          " << endl;
	cout << "==========================================================================" << endl;
	recv(s, (char*)& num, sizeof(int), 0);
	if (num == 0) {
		cout << "                       ��� ���������                         " << endl;
	}
	else {
		for (int i = 0; i < num; i++) {
			recv(s, login, sizeof(login), 0);
			recv(s, password, sizeof(password), 0);
			printf("%28s            | %19s\n", login, password);
		}
	}
	system("pause");
}
void SClient::add_expert() {
	system("cls");
	char login[30], password[30], message[32];
	//string answer;
	cout << "======= ���������� �������� =======" << endl;
	cout << "������� ��� ��������: ";
	cin.getline(login, 30);
	cout << "������� ������: ";
	cin.getline(password, 30);
	send(s, login, sizeof(login), 0);
	send(s, password, sizeof(password), 0);
	//answer = recvFromS();
	recv(s, message, sizeof(message), 0);

	cout << endl << message << endl;
}
void SClient::add_user() {
	system("cls");
	char login[30], password[30], message[32];
	//string answer;
	cout << "======= ���������� ������������ =======" << endl;
	cout << "������� ��� ������������: ";
	cin.getline(login, 30);
	cout << "������� ������: ";
	cin.getline(password, 30);
	send(s, login, sizeof(login), 0);
	send(s, password, sizeof(password), 0);
	//answer = recvFromS();
	recv(s, message, sizeof(message), 0);
	
	cout << endl << message << endl;
	system("pause");
}
void SClient::deleteuser() {
	system("cls");
	int flag;
	char login[30];
	cout << "======= �������� ������������ =======" << endl;
	cout << "������� ��� ������������ ��� ��������: ";
	cin.getline(login, 30);
	send(s, login, sizeof(login), 0);
	recv(s, (char *)& flag, sizeof(int), 0);
	if (flag == 1) {
		cout << "������������ " << login << " ������." << endl;
	}
	if (flag == 0) {
		cout << "������������ � ����� ������ �� ��� ������." << endl;
	}
	system("pause");
}
void SClient::userlist() {
	system("cls");
	int num;
	char login[30], password[30];
	cout << "            ��� ������������            |          ������          " << endl;
	cout << "==========================================================================" << endl;
	recv(s, (char*)& num, sizeof(int), 0);
	if (num == 0) {
		cout << "                       ��� �������������                         " << endl;
	}
	else {
		for (int i = 0; i < num; i++) {
			recv(s, login, sizeof(login), 0);
			recv(s, password, sizeof(password), 0);
			printf("%28s            | %19s\n", login, password);
		}
	}
	system("pause");
}