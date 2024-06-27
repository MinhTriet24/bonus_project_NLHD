#ifndef _CLASS_H_
#define _CLASS_H_

#include "Struct.h"
#include "Login.h"
#include "Console.h"
#include "User.h"
#include "Staff.h"

//hàm lấy đường dẫn đến lớp học cần truy cập
void takeClassPath(string Class);

//phần danh sách liên kết để lưu đường dẫn các lớp hiện đang có trong các năm
void InitListClassName(ListClassName*& list);
void addClassNameIntoList(ListClassName*& list, className info);
void loadDataFromFileToList();
void saveDataFromListToFile();
//Hàm sắp xếp lại tên cho đúng thứ tự (đẹp mắt)
void sortClassNameInList(ListClassName*& list);
void deleteClassNameList(ListClassName*& list);


//phần danh database cho quản lý lớp học
void InitListClassInSchoolYear(ListClassInSchoolYear*& list);
void addClassToListClassInSchoolYear(ListClassInSchoolYear*& list, Class info);
void InitListClasses(ListClasses*& list);
void addClassesIntoListClasses(ListClasses*& list, Classes dta);
void sortListClassNameInClassesList();
void deleteListClasses(ListClasses*& list);
void LoadAllDataOfClassIntoListClasses();
ndeClass* createdNewClassWithKeyBoard(string className, int numOfStudents);
ndeClass* createdNewClassWithFileData(string pathFile, string className);

//khai báo các hàm cho phần giao diện lớp học
int command(int& curPos, int minPos, int maxPos, function<int(int)> option);
int manageStudentOption(int curPos);
void manageStudentMainUI();
//xem danh sach lop va xem danh sach hoc sinh
int chooseStudentYear(int curPos);
void viewListStudentYearUI();
int commandForClass(int& curPos, int minPos, int maxPos, vector<ndeClass*> posArray, int& startPos, int& endPos, int& numPage, function<int(int, vector<ndeClass*>, int, int, int)> option);
int chooseClass(int curPos, vector<ndeClass*> posArray, int startPos, int endPos, int numPage);
void viewListOfClassUI(string currentStudentYear);
void viewStudentInClassUI(ndeClass* nodeClassCur);
//tao lop hoc moi
int chooseOperationToAddClass(int curPos);
void CreatedNewClassUI();
void InputClassUI();
void ImportClassDataUI();
//phan create va info cua schoolYear
void schoolYearInfomationUI();
void CreateSchoolYear();
void CreateSchoolYearUI();

extern Date startDate;
extern Date endDate;

#endif
