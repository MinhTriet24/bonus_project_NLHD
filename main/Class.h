#ifndef _CLASS_H_
#define _CLASS_H_

#include "Struct.h"
#include "Login.h"
#include "Console.h"
#include "User.h"
#include "SchoolYear.h"

void initList(ListClasses& list);
void addClass(ListClasses& list, Class* course);
void saveClass(string path, ListStudent listStudent);
void getListClasses(string year);
void viewListOfClasses();



#endif
