#ifndef Student_h
#define Student_h
#include"struct.h"   

// Điểm số
void StudentMenu();
NodeScoreBoard* makeNode(ScoreBoard sb);
void addScoreBoard(ListScoreBoard& l, ScoreBoard sb);
void initListScoreBoard(ListScoreBoard& l);
double avrMark(Student st);
void findStudentIDInCourse(string ID, ListScoreBoard& l);
void DisplayScoreBoard(ListScoreBoard l);
void findStudentIDInCourse2(string ID, ListCourse& hisCourse);

#endif
