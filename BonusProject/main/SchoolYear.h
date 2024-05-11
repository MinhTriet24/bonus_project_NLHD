#ifndef _SCHOOLYEAR_H_
#define _SCHOOLYEAR_H_

#include "Struct.h"
#include "Login.h"
#include "Console.h"
#include "User.h"
void addCourse(ListCourses& list, Course* course);
Course* convertCourseData(ifstream& data);
void getCurrentSchoolYear();
void getCurrentSemester();
void getListCourses();


#endif
