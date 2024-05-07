#pragma once
#include "Struct.h"

void initList(ListUser& list);
User* convertUserData(ifstream& data);
void addUser(ListUser& list, User* user);
void getListUsers();