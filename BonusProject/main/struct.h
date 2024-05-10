#ifndef _STRUCT_H_
#define _STRUCT_H_
// Tong hop cac struct

#include<cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <functional>
#include <time.h>
#include <direct.h>
#include <io.h>
#include <filesystem>
#include <sstream>
#include <vector>

//.Dau tien ta phai doc thong tin toan bo sinh vien vao listUser, hay listUser la co san (available). Va file user.csv chứa thong tin toan bo User( id, pass, Ten,..) 
using namespace std;
//namespace fs = filesystem;


struct Date {
	int year;
	int month;
	int day;
	string wDay;
};
struct User {
	string id;
	string password;
	string lastName;
	string firstName;
	string className;
	string gender;
	int academicYear;
	bool isStaff;
	Date dateOfBirth;
	User* prev;
	User* next;
};
struct ListUser {
	User* head;
	User* tail;
	int size;
};
struct Semester {
	int semester;
	Date startDate, endDate;
};
struct Course {
	string id;
	string courseName;
	string teacherName;
	int credits;
	int maxStudents = 50;
	int numberRegistered = 0;
	int academicYear;
	string wDay;
	string session[2];
	Course* prev;
	Course* next;
};
struct ListCourses {
	Course* head;
	Course* tail;
	Date startDate, endDate;
	int size;

};

extern User* currentUser;
extern ListUser listUser;
extern Date currentDate;
extern string currentSchoolYear;
extern Semester currentSemester;
extern string semesterPath;
extern ListCourses listCourses;
extern string schoolYearPath;
//struct Class {
//	string className;
//	fs::path path;
//	Class* prev;
//	Class* next;
//};
//struct ListClasses {
//	Class* head;
//	Class* tail;
//	int size;
//};


string dateToStr(Date date);
int dayofweek(int d, int m, int y);
Date strToDate(string str);

#endif
