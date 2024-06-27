#pragma once
#ifndef User_h
#define User_h
#include "Struct.h"
void initList(ListUser& list);
User* convertUserData(ifstream& data);
void addUser(ListUser& list, User* user);
void getListUsers();
void saveListUser();
#endif

