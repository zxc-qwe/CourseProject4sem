#pragma once
#include "includes.h"
#include "SClient.h"

struct UserBase {
	char login[30], password[30];
};
struct AdminBase {
	char login[30], password[30];
};
struct ExpertBase {
	
};

class Users {
protected:
	char login[20], password[20];
	
public:
	static void checkInt(int &Value);
	static int checkWord(char *str);
};

class Admin : public Users {
protected:
	char login[20], password[20];
};

template <typename T>
class exc {
	string error;
public:
	exc(string e) { error = e; }
	string what_error() { return error; }
};