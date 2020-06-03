#pragma comment(lib, "ws2_32.lib")
#include "SServer.h"
#include "includes.h"
#include "filework.h"
using namespace std;

struct sign_in {
	char user_login[30];
	char user_password[30];
};

struct evaluation {
	float x1;
	float x2;
	float x3;
	float x4;
	float x5;
	float x6;
	float x7;
	float x8;
	float x9;
	float x10;
	float x11;
	float x12;
	float x13;
	float x14;
	float x15;
	float x16;
};

struct experts {
	char expert_login[30];
	char expert_password[30];
};

SServer::SServer()
{
	client_count = 0;
}

SServer::~SServer()
{
}

ClientWork::ClientWork(SOCKET s) {
	client_socket = s;
}



void SServer::startServer() {
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) /*return 0*/; // тут терминатора бы
	s = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(1024);
	local_addr.sin_addr.s_addr = 0;
	bind(s, (sockaddr*)&local_addr, sizeof(local_addr));
	if (s == SOCKET_ERROR) {
		cout << "Сокет не был создан\n";
	}

	if (::bind(s, (sockaddr*)&local_addr, sizeof(local_addr)) != SOCKET_ERROR) {
		printf("Сокет успешно привязан\n");
	}

	if (listen(s, 5) != SOCKET_ERROR) {
		printf("Старт прослушивания порта: %u\n", ntohs(local_addr.sin_port));
	}
	SOCKET client_socket;
	sockaddr_in client_addr;

	int client_addr_size = sizeof(client_addr);
	while (client_socket = accept(s, (sockaddr*)&client_addr, &client_addr_size))
	{
		client_count++;
		cout << "Подключился новый клиент!" << endl;
		cout << "Общее число клиентов: " << client_count << endl;
		thread th(&SServer::handle, this, client_socket);
		th.detach();
	}
}

void SServer::closeServer() {
	closesocket(s);
	WSACleanup();
	cout << "Сервер был остановлен." << endl;
}


void SServer::handle(SOCKET client_socket) {
	string action;
	ClientWork client(client_socket);
	cout << "Запущен поток " << this_thread::get_id() << " для работы с клиентом" << endl;
	char login[100], password[100];
	recv(client_socket, login, sizeof(login), 0);
	recv(client_socket, password, sizeof(password), 0);

	FILE *fa;
	char admin_login[30], admin_password[30];
	int num = 0;
	char f = '0';
	fa = fopen("adminlist.txt", "r");
	fscanf(fa, "%d", &num);
	for (int i = 0; i < num; i++) {
		fscanf(fa, " %s", admin_login);
		fscanf(fa, " %s", admin_password);
	}
	fclose(fa);
	
	for (int i = 0; i < num; i++) {
		if (strcmp(admin_login, login) == 0) {
			if (strcmp(password, admin_password) == 0) {
				f = '1';
			}
		}
	}
	if (f == '0') {
		FILE *fb;
		char user_login[30], user_password[30];
		int num1 = 0;
		fb = fopen("userlist.txt", "r");
		fscanf(fb, "%d", &num);
		for (int i = 0; i < num; i++) {
			fscanf(fb, " %s", user_login);
			fscanf(fb, " %s", user_password);
		}
		fclose(fb);
		for (int i = 0; i < num; i++) {
			if (strcmp(user_login, login) == 0) {
				if (strcmp(password, user_password) == 0) {
					f = '2';
				}
			}
		}
	}
	if (f == '0') {
		FILE *fj;
		char expert_login[30], expert_password[30];
		int num2 = 0;
		fj = fopen("expertlist.txt", "r");
		fscanf(fj, "%d", &num);
		for (int i = 0; i < num; i++) {
			fscanf(fj, " %s", expert_login);
			fscanf(fj, " %s", expert_password);
		}
		fclose(fj);
		for (int i = 0; i < num; i++) {
			if (strcmp(expert_login, login) == 0) {
				if (strcmp(password, expert_password) == 0) {
					f = '3';
				}
			}
		}
	}

	cout << "Из потока " << this_thread::get_id() << " была получена строка: " << login << endl;
	cout << "Из потока " << this_thread::get_id() << " была получена строка: " << password << endl;
	
	send(client_socket, &f, sizeof(f), 0);

	
	while (true) {
		action = client.recvFromClient();

		if (action == "Exit")
			break;
		if (action == "Calculate") {
			float z1[4][4], z2[4][4];
			FILE *fq;
			fq = fopen("evaluation1.txt", "r");
			fscanf(fq, "%d", &num);
			evaluation * value;
			value = (struct evaluation*)malloc(num * sizeof(struct evaluation));
			for (int i = 0; i < num; i++) {
				fscanf(fq, "%f ", &value[i].x1);
				fscanf(fq, "%f ", &value[i].x2);
				fscanf(fq, "%f ", &value[i].x3);
				fscanf(fq, "%f ", &value[i].x4);
				fscanf(fq, "%f ", &value[i].x5);
				fscanf(fq, "%f ", &value[i].x6);
				fscanf(fq, "%f ", &value[i].x7);
				fscanf(fq, "%f ", &value[i].x8);
				fscanf(fq, "%f ", &value[i].x9);
				fscanf(fq, "%f ", &value[i].x10);
				fscanf(fq, "%f ", &value[i].x11);
				fscanf(fq, "%f ", &value[i].x12);
				fscanf(fq, "%f ", &value[i].x13);
				fscanf(fq, "%f ", &value[i].x14);
				fscanf(fq, "%f ", &value[i].x15);
				fscanf(fq, "%f ", &value[i].x16);
			}
			
			if (num == 2) {
				char message[15] = "Ok";
				send(client_socket, message, sizeof(message), 0);
				z1[0][0] = value[0].x1; z1[0][1] = value[0].x2; z1[0][2] = value[0].x3; z1[0][3] = value[0].x4; z1[1][0] = value[0].x5; z1[1][1] = value[0].x6; z1[1][2] = value[0].x7; z1[1][3] = value[0].x8;
				z1[2][0] = value[0].x9; z1[2][1] = value[0].x10; z1[2][2] = value[0].x11; z1[2][3] = value[0].x12; z1[3][0] = value[0].x13; z1[3][1] = value[0].x14; z1[3][2] = value[0].x15; z1[3][3] = value[0].x16;
				z2[0][0] = value[1].x1; z2[0][1] = value[1].x2; z2[0][2] = value[1].x3; z2[0][3] = value[1].x4; z2[1][0] = value[1].x5; z2[1][1] = value[1].x6; z2[1][2] = value[1].x7; z2[1][3] = value[1].x8;
				z2[2][0] = value[1].x9; z2[2][1] = value[1].x10; z2[2][2] = value[1].x11; z2[2][3] = value[1].x12; z2[3][0] = value[1].x13; z2[3][1] = value[1].x14; z2[3][2] = value[1].x15; z2[3][3] = value[1].x16;
				fclose(fq);
				
				float f[2][4] = { 0,0,0,0,0,0,0,0 };
				for (int i = 0;i < 4;i++)
				{
					for (int j = 0;j < 4;j++)
					{
						f[0][i] += z1[i][j];
						f[1][i] += z2[i][j];
					}
				}
				float Q[2][4];
				for (int i = 0;i < 4;i++)
				{
					for (int j = 0;j < 4;j++)
					{
						Q[0][j] = f[0][j] / 30;
						Q[1][j] = f[1][j] / 30;
					}
				}
				float W[4] = { 0,0,0,0 };
				for (int j = 0;j < 4;j++)
				{
					W[j] = Q[0][j] + Q[1][j];
					cout << W[j] << " ";
					send(client_socket, (char*)& W[j], sizeof(float), 0);
				}
				cout << endl;
				ofstream out;
				out.open("D:\\report.txt");
				if (out.is_open()) {
					out << "Сокращение отходов производства | Исключение промежуточного складирования | Устранение потерь от брака | Совешенствование пларирования потребности" << endl;
					out << "--------------------------------+-----------------------------------------+----------------------------+------------------------------------------" << endl;
					out << W[0] << setw(24) << "|" << W[1] << setw(34) << "|" << W[2] << setw(20) << "|" << W[3] << setw(19) << endl;
					out << "--------------------------------+-----------------------------------------+----------------------------+------------------------------------------";
				}
			}
			else {
				char message[15] = "Not enough";
				send(client_socket, message, sizeof(message), 0);
			}
		}
		if (action == "Evaluate") {
			float z[4][4];
			int num = 0;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					recv(client_socket, (char*)& z[i][j], sizeof(float), 0);
				}
			}
			FILE *fn;
			fn = fopen("evaluation1.txt", "r");
			fscanf(fn, "%d", &num);
			evaluation * value;
			value = (struct evaluation*)malloc(num * sizeof(struct evaluation));
			for (int i = 0; i < num; i++) {
				fscanf(fn, "%f ", &value[i].x1);
				fscanf(fn, "%f ", &value[i].x2);
				fscanf(fn, "%f ", &value[i].x3);
				fscanf(fn, "%f ", &value[i].x4);
				fscanf(fn, "%f ", &value[i].x5);
				fscanf(fn, "%f ", &value[i].x6);
				fscanf(fn, "%f ", &value[i].x7);
				fscanf(fn, "%f ", &value[i].x8);
				fscanf(fn, "%f ", &value[i].x9);
				fscanf(fn, "%f ", &value[i].x10);
				fscanf(fn, "%f ", &value[i].x11);
				fscanf(fn, "%f ", &value[i].x12);
				fscanf(fn, "%f ", &value[i].x13);
				fscanf(fn, "%f ", &value[i].x14);
				fscanf(fn, "%f ", &value[i].x15);
				fscanf(fn, "%f ", &value[i].x16);
			}
			fclose(fn);
			if (num == 2) {

			}
			else {
				FILE *fp;
				fp = fopen("evaluation1.txt", "w");
				num++;
				fprintf(fp, "%d", num);
				for (int i = 0; i < num - 1; i++) {
					fprintf(fp, " %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", value[i].x1, value[i].x2, value[i].x3, value[i].x4, value[i].x5, value[i].x6, value[i].x7, value[i].x8,
						value[i].x9, value[i].x10, value[i].x11, value[i].x12, value[i].x13, value[i].x14, value[i].x15, value[i].x16);
				}
				fprintf(fp, " %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", z[0][0], z[0][1], z[0][2], z[0][3], z[1][0], z[1][1], z[1][2],
					z[1][3], z[2][0], z[2][1], z[2][2], z[2][3], z[3][0], z[3][1], z[3][2], z[3][3]);

				fclose(fp);
			}
		}
		
		if (action == "Delete expert") {
			int num, flag = 0, b;
			char login[30];
			FILE *fl;
			fl = fopen("expertlist.txt", "r");
			fscanf(fl, "%d", &num);
			experts * expert;
			expert = (struct experts*)malloc(num * sizeof(struct experts));
			for (int i = 0; i < num; i++) {
				fscanf(fl, "%s ", expert[i].expert_login);
				fscanf(fl, "%s ", expert[i].expert_password);
			}
			fclose(fl);
			recv(client_socket, login, sizeof(login), 0);
			for (int i = 0; i < num; i++) {
				if (strcmp(expert[i].expert_login, login) == 0) {
					flag = 1;
					b = i;
					FILE * fm;
					fm = fopen("expertlist.txt", "w");
					num--;
					fprintf(fm, "%d", num);
					for (int i = 0; i < b; i++) {
						fprintf(fm, " %s %s", expert[i].expert_login, expert[i].expert_password);
					}
					for (int i = 0; i > b; i++) {
						fprintf(fm, " %s %s", expert[i].expert_login, expert[i].expert_password);
					}
					fclose(fm);
					send(client_socket, (char *)& flag, sizeof(int), 0);
					cout << "Эксперт " << login << " удален." << endl;
				}
			}
		}
		if (action == "Show experts") {
			int num = 0;
			char login[30], password[30];
			FILE *fk;
			fk = fopen("expertlist.txt", "r");
			fscanf(fk, "%d", &num);
			send(client_socket, (char*)& num, sizeof(int), 0);
			for (int i = 0; i < num; i++) {
				fscanf(fk, " %s", login);
				fscanf(fk, " %s", password);
				send(client_socket, login, sizeof(login), 0);
				send(client_socket, password, sizeof(login), 0);
			}
			fclose(fk);
		}
		if (action == "Add expert") {
			int num = 0, flag = 0;
			FILE *fh;
			fh = fopen("expertlist.txt", "r");
			fscanf(fh, "%d", &num);
			experts * expert;
			expert = (experts*)malloc(num * sizeof(experts));
			for (int i = 0; i < num; i++) {
				fscanf(fh, " %s", expert[i].expert_login);
				fscanf(fh, " %s", expert[i].expert_password);
			}
			fclose(fh);
			char  login[30], password[30];
			recv(client_socket, login, sizeof(login), 0);
			recv(client_socket, password, sizeof(password), 0);
			do {
				for (int i = 0; i < num; i++) {
					if (strcmp(expert[i].expert_login, login) == 0) {
						char message[32] = "Это имя эксперта уже занято";
						send(client_socket, message, sizeof(message), 0);
						flag = 1;
					}
				}
				break;
			} while (flag != 0);
			if (flag == 0) {
				char message[30] = "Эксперт успешно добавлен";
				FILE * fi;
				fi = fopen("expertlist.txt", "w");
				num++;
				fprintf(fi, "%d", num);
				for (int i = 0; i < num - 1; i++) {
					fprintf(fi, " %s %s", expert[i].expert_login, expert[i].expert_password);
				}
				fprintf(fi, " %s %s", login, password);
				cout << "Эксперт " << login << " добавлен.\n";
				send(client_socket, message, sizeof(message), 0);
				fclose(fi);
			}
		}
		if (action == "Delete user") {
			int num, flag = 0, b;
			char login[30];
			FILE *fg;
			fg = fopen("userlist.txt", "r");
			fscanf(fg, "%d", &num);
			sign_in * sign;
			sign = (struct sign_in*)malloc(num * sizeof(struct sign_in));
			for (int i = 0; i < num; i++) {
				fscanf(fg, "%s ", sign[i].user_login);
				fscanf(fg, "%s ", sign[i].user_password);
			}
			fclose(fg);
			recv(client_socket, login, sizeof(login), 0);
			for (int i = 0; i < num; i++) {
				if (strcmp(sign[i].user_login, login) == 0) {
					flag = 1;
					b = i;
					FILE * fh;
					fh = fopen("userlist.txt", "w");
					num--;
					fprintf(fh, "%d", num);
					for (int i = 0; i < b; i++) {
						fprintf(fh, " %s %s", sign[i].user_login, sign[i].user_password);
					}
					for (int i = 0; i > b; i++) {
						fprintf(fh, " %s %s", sign[i].user_login, sign[i].user_password);
					}
					fclose(fh);
					send(client_socket, (char *)& flag, sizeof(int), 0);
					cout << "Пользователь " << login << " удален." << endl;
				}
			}
			if (flag == 0) {
				cout << "Польователь с таким именем не был найден" << endl;
				send(client_socket, (char *)& flag, sizeof(int), 0);
			}
		}
		if (action == "Show users") {
			int num = 0;
			char login[30], password[30];
			FILE *ff;
			ff = fopen("userlist.txt", "r");
			fscanf(ff, "%d", &num);
			send(client_socket, (char*)& num, sizeof(int), 0);
			for (int i = 0; i < num; i++) {
				fscanf(ff, " %s", login);
				fscanf(ff, " %s", password);
				send(client_socket, login, sizeof(login), 0);
				send(client_socket, password, sizeof(login), 0);
			}
			fclose(ff);
			
		}
		if (action == "Add user") {
			int num = 0, flag = 0;
			FILE *fc;
			fc = fopen("userlist.txt", "r");
			fscanf(fc, "%d", &num);
			sign_in * sign;
			sign = (sign_in*)malloc(num * sizeof(sign_in));
			for (int i = 0; i < num; i++) {
				fscanf(fc, " %s", sign[i].user_login);
				fscanf(fc, " %s", sign[i].user_password);
			}
			fclose(fc);
			char  login[30], password[30];
			recv(client_socket, login, sizeof(login), 0);
			recv(client_socket, password, sizeof(password), 0);
			do {
				for (int i = 0; i < num; i++) {
					if (strcmp(sign[i].user_login, login) == 0) {
						char message[32] = "Это имя пользователя уже занято";
						send(client_socket, message, sizeof(message), 0);
						flag = 1;
					}
				}
				break;
			} while (flag != 0);
			if (flag == 0) {
				char message[30] = "Пользователь успешно добавлен";
				FILE * fd;
				fd = fopen("userlist.txt", "w");
				num++;
				fprintf(fd, "%d", num);
				for (int i = 0; i < num - 1; i++) {
					fprintf(fd, " %s %s", sign[i].user_login, sign[i].user_password);
				}
				fprintf(fd, " %s %s", login, password);
				cout << "Пользователь " << login << " добавлен.\n";
				send(client_socket, message, sizeof(message), 0);
				fclose(fd);
			}
		}
	}

	closesocket(client_socket);
	client_count--;
	cout << "Клиент из потока " << this_thread::get_id() << " был отключен." << endl;
	cout << "Всего клиентов: " << client_count << endl;
	
}

void SServer::setPort(unsigned short port)
{
	this->port = port;
}

void ClientWork::sendToClient(string str)
{
	const int BUFFER_SIZE = 1024;
	char buf[BUFFER_SIZE];
	for (unsigned int i = 0; i < (str.length() / (BUFFER_SIZE - 1)); i++)
	{
		buf[0] = '1';
		str.copy(buf + 1, BUFFER_SIZE - 1, i * (BUFFER_SIZE - 1));
		send(client_socket, buf, sizeof(buf), 0);
	}
	buf[0] = '0';
	str.copy(buf + 1, BUFFER_SIZE - 1, str.length() / (BUFFER_SIZE - 1));
	buf[str.length() % (BUFFER_SIZE - 1) + 1] = '\0';
	send(client_socket, buf, sizeof(buf), 0);
}

string ClientWork::recvFromClient() 
{
	string result = "";
	const int BUFFER_SIZE = 1024;
	char buf[BUFFER_SIZE];
	recv(client_socket, buf, sizeof(buf), 0);

	result += buf + 1;
	while (buf[0] == 1)
	{
		result += buf + 1;
	}
	cout << "Поток " << setw(5) << this_thread::get_id() << " : получена строка ";
		cout << '\"' << result << '\"' << endl;

	return result;
}
