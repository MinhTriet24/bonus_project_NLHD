#ifndef Login_h
#define Login_h
#include "Struct.h"
#include"Console.h"
void loginSystem();
void loginUI();
User* login(string id, string password);
void StaffMenu();
string getPassword(bool isHidden);
#endif
