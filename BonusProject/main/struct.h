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
struct SemesterMark {
	float GPA = 0;
	float overallGPA = 0;
};
struct Class {
	string className;
	Class* prev;
	Class* next;
};
struct ListClasses {
	Class* head;
	Class* tail;
	int size;
};
struct Course {
	string id;
	string courseName;
	string teacherName;
	int credits;
	int numOfStudents;
	int NumofEroller;
	int academicYear;
	string weekDay;
	string session[2];
	Course* pNext;
};
struct ListCourse {
	Course* pHead;
};
struct Semester {
	int semester;
	Date startDate, endDate;
};
struct Registration{
	Date startDate, endDate;
};
//oo THANH
struct Student {
	string studentID;
	string lastName;
	string firstName;
	string gender;
	string socialID;
	Date dateOfBirth;
	int academicYear;
	double otherMark;
	double midtermMark;
	double finalMark;
	double avrMark;
	double GPA;
	double avrGPA;
};
struct NodeStudent {
	Student studentInfo;
	NodeStudent* next;
};
struct ListStudent {
	NodeStudent* head;
	NodeStudent* tail;
};
struct ScoreBoard {
	string nameCourse;
	double otherMark;
	double midtermMark;
	double finalMark;
	double avrMark;
};
struct NodeScoreBoard {
	ScoreBoard data;
	NodeScoreBoard* next;
};
struct ListScoreBoard {
	NodeScoreBoard* head;
	NodeScoreBoard* tail;
};

//
extern User* currentUser;
extern ListUser listUser;
extern Date currentDate;
extern string currentSchoolYear;
extern Semester currentSemester;
extern string semesterPath;
extern string schoolYearPath;


string dateToStr(Date date);
int dayofweek(int d, int m, int y);
Date strToDate(string str);

#endif
