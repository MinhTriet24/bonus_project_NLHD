#ifndef Student_h
#define Student_h
#include"struct.h"

// ListCourses enrolledCourses;	// Danh sách đã đăng ký
// ListCourses ValidCourses;		// Danh sách được đăng ký	   

void StudentMenu();
//void courseRegistationMenu();
//void getValidCourses();		// Đọc data từ file course tạo từ staff
//void getEnrolledCourse();  // Lưu mấy thằng courses đc đăng ký 
//void saveEnrolledCourse();  // Lưu vào file data mới
//void RegisterCourse();	// Hàm đăng ký
//void ViewEnrolledCourse();

ListStudent* loadFileDataOfStudent(string currentClass);
NodeStudent* createNewNodeStudent(Student& st);
void InitListStundent(ListStudent *&list);
void addStudentIntoListStudent(ListStudent*& list, Student newStudent);
void saveDataOfListStudent(string currentClass);
void removeStudentFollowID(List *&list, string ID);
#endif
