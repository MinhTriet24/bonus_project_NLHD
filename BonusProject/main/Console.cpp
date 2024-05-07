﻿#include "Struct.h"
#include "Console.h"
#include "User.h"
#include "Login.h"
#include "Student.h"
string id, password;
User* currentUser = NULL;
ListUser listUser;
Date currentDate;
string currentSchoolYear;
Semester currentSemester;
string semesterPath;
ListCourses listCourses;
string schoolYearPath;
int yPos = 13;
//ListClasses listClasses;
void getConsoleSize(int& width, int& height) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	width = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
	height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
}
//.--> OK!
void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//.Ve BOX -->OK!
void drawBox(int width, int height, int left, int top) {
	//.Left la x, top la y. Width va Height la luot la chieu rong va dai cua box muon ve.
	//.Tu code: 
	gotoXY(left, top);
	cout << char(201);// |-
	int tmp = width;
	while (tmp--) {
		cout << char(205);  //.=
	}
	gotoXY(left, top);//.chinh con tro ve lai toa do cu.
	int tmp1 = height, tmp2 = top + 1;
	while (tmp1--) {
		gotoXY(left, tmp2);
		cout << char(186);//.||
		tmp2++;
	}
	gotoXY(left, tmp2);//.tmp2 da +	1 o cuoi vong lap roi
	cout << char(200);
	tmp = width;
	while (tmp--) {
		cout << char(205);//.=
	}
	cout << char(188);//._|
	tmp2 = height + top;//.la toa do y o thoi diem hien tai.
	tmp1 = width + left + 1;//.la toa do x o thoi diem hien tai.
	int tmp3 = height;
	while (tmp3--) {
		gotoXY(tmp1, tmp2);
		cout << char(186);//.||
		tmp2--;
	}
	gotoXY(tmp1, tmp2);
	cout << char(187);//.-|
}
void textAlignCenter(string s, int left, int width, int y) {//.y la toa do y(tung do) , left la toa do x ma ta se in string s (hoanh do), width la hieu rong cua Box (Vi ta du dinh se in s tren box va dc can chinh giua theo chieu rong so vs box).
	int x = ((width - s.length()) / 2) + left + 1;
	gotoXY(x, y); cout << s;
}
string dateToStr(Date date) {//.chuyen 1 so int 1 thanh 01 , ma so 12 van la 12
	string str = "";
	if (date.day < 10) str += "0";
	str += to_string(date.day) + "/";
	if (date.month < 10) str += "0";
	str += to_string(date.month) + "/";
	str += to_string(date.year);
	return str;
}
int yPos = 13;
// Ham kiem tra xem tai khoan va mat khau dc nhap vao co ton tai trong List (List duoc tao bang cach doc tu file csv)
//Ham an / hien con tro nhấp nháy tren man hinh Console--> OK!
void hideCursor(bool isHiden) {
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	cursor.bVisible = !isHiden;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
int dayofweek(int d, int m, int y)
{
	static int t[] = { 0, 3, 2, 5, 0, 3,
					   5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 +
		y / 400 + t[m - 1] + d) % 7;
}
Date strToDate(string str) {
	Date date;
	date.day = stoi(str.substr(0, str.find('/')));
	str.erase(0, str.find('/') + 1);
	date.month = stoi(str.substr(0, str.find('/')));
	str.erase(0, str.find('/') + 1);
	date.year = stoi(str.substr(0, str.find('/')));
	str.erase(0, str.find('/') + 1);
	string wDay;
	switch (dayofweek(date.day, date.month, date.year)) {
	case 0:
		wDay = "Sun";
		break;
	case 1:
		wDay = "Mon";
		break;
	case 2:
		wDay = "Tue";
		break;
	case 3:
		wDay = "Wed";
		break;
	case 4:
		wDay = "Thu";
		break;
	case 5:
		wDay = "Fri";
		break;
	case 6:
		wDay = "Sat";
		break;
	}
	date.wDay = wDay;
	return date;

}

string DateToString(Date d)
{
	string dateString = ""; //khoi tao chuoi ngay
	
	if(d.day<10) dateString+="0";//neu ngay < 10 them 0 vao truoc cho dep
	dateString += to_string(d.day); //them vao ngay duoc chuyen thanh string vao
	dateString+="/"; //them dau gach de ngan cach ngay thang va nam

	if(d.month<10) dateString+="0"; // tuong tu voi ngay
	dateString+=to_string(d.month);
	dateString+="/";

	dateString+=to_string(d.year); //tuong tu nhu ngay

	return dateString; //tra ve chuoi duoc chuyen hoa tu ngay
}
