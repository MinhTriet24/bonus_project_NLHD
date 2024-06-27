#pragma once
#ifndef Header_h
#define Header_h
#include"struct.h"
#include "Class.h"
const char cursorLeft = char(175);
const char cursorRight = char(174);

void Profile();
void StaffMenu();
void userAccount();
void changePassword();
void logout();
void AddCourse(ListCourse& l, Course* p);
void ReadFileGetList(ListCourse& l, string fileName);
int CountCourse(ListCourse l);
void PrintTitle();
void PrintListCourse(ListCourse l);
void PrintCourseInLine(Course tmp1, int& x, int& y);
void printMenu1(Course* options, int size, int currentOption);
Course* GetPreviuosCourse(ListCourse l, Course* p);
void saveCourses(string path, ListCourse& l);

void DeleteCourse(ListCourse& l, Course p, string path);
void printMenu3(const vector<string>& options, int currentOption, int k);
void Upper(string& s);
Course* ConvertToArr(ListCourse l);
void AddTail(ListCourse& l, Course* c);
Course* ConvertFromCourseToPointer(Course c);
void ConvertFromArrToList(ListCourse& l, Course* c);
void ChangeCourse(ListCourse& l, string path, int ans);
void Detail(ListCourse& l, int ans);
void ListOfStudentInCourse(string listFileName[], int ans);
void DispalyAfterChooseOneCourse(int ans, ListCourse& l, string path);
void ListCourseOptions(ListCourse& l, int& ans, string path);
void ManageCourses();
void removeStudentFollowID(ListStudent*& list, string ID);

//các hàm liên quan đến danh sách học sinh
//các hàm dùng chung
NodeStudent* createNewNodeStudent(Student& st);
void InitListStudent(ListStudent*& list);
void addStudentIntoListStudent(ListStudent*& list, Student st);
//hàm dùng cho phần courses (khóa học)
void AddStudent(ListStudent* l, string FileName[], int ans);
void ViewScoreboard(ListStudent* l, string listFileName[], int ans);
void ScoreListstudentOfClass(ListStudent* l);
void ImportScoreboard(ListStudent* l, string listFileName[], int ans);
void ExportToCSV(ListStudent* l);
void PrintListstudentOfClass(ListStudent* l);
void saveDataOfListStudent(string currentClass, ListStudent* list);
void saveDataOfListStudentWithMark(string currentClass, ListStudent* list);
ListStudent* loadFileDataOfStudent(string ListFileName[], int ans);
double strToDouble(string& s);
Student EnterStudent();
//hàm dùng cho phần lớp học
ListStudent* loadFileDataOfStudent(string currentClass);
ListStudent* createdListStudentWithDataFromKeyBoard(string className, int numOfStudents);
ListStudent* readFileStudentFromPathToAddIntoClass(string pathFile);
void writeFileStudentFromNewClassIntoDatabase(ListStudent* list, string className);
void deleteStudentList(ListStudent*& list);

#endif
