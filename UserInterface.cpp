
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
//.Dau tien ta phai doc thong tin toan bo sinh vien vao listUser, hay listUser la co san (available). Va file user.csv chứa thong tin toan bo User( id, pass, Ten,..) 
using namespace std;
namespace fs = filesystem;
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
	User *head;
	User *tail;
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
struct Class {
	string className;
	fs::path path;
	Class* prev;
	Class* next;
};
struct ListClasses {
	Class* head;
	Class* tail;
	int size;
};
//.Khai bao bien kieu nay la chi can khai bao 1 lan ma xai cho moi ham luon
string id, password;
User* currentUser = NULL;
ListUser listUser;
Date currentDate;
string currentSchoolYear;
Semester currentSemester;
string semesterPath;
ListCourses listCourses;
string schoolYearPath;
ListClasses listClasses;
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
	cout << char(201);
	int tmp = width;
	while (tmp--) {
		cout << char(205);//.=
	}
	gotoXY(left, top);//.chinh con tro ve lai toa do cu.
	int tmp1 = height,tmp2=top+1;
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
	tmp1 = width + left +1;//.la toa do x o thoi diem hien tai.
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
	int x = ((width - s.length()) / 2) + left +1;
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
User* login(string id, string password) {
	User* data =listUser.head;
	while (data != NULL) {
		if (id == data->id) {
			if (password == data->password) return data;
			else return NULL;
		}
		data = data->next;
	}
	return NULL;
}
//Ham an / hien con tro nhấp nháy tren man hinh Console--> OK!
void hideCursor(bool isHiden) {
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	cursor.bVisible = !isHiden;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
//.Ham lm hien thi pass or khong hien thi pass (khi nhan F1 --> isHidden == true--> k hien thi Pass , else false --> Hien thi pass) va them nx la ms dau nhap thi se in ra nhung ki tu * chu k in ra pass
string getPassword(bool isHidden) {
	string passwrd = "";
	while (true) {
		gotoXY(79, yPos + 2);
		if (isHidden) cout << char(254);
		else cout << " ";
		gotoXY(58 + passwrd.length(), yPos + 2);
		char ch;
		ch = _getch();
		if (ch == 13) {// Enter
			cout << endl;
			return passwrd;
		}
		else if (ch == 0) {// NULL
			ch = _getch();
			if (ch == 59) {// ;
				if (isHidden) {
					string temp = passwrd;
					while (temp.length() > 0) {
						cout << "\b \b";
						temp.pop_back();
					}
					cout << passwrd;
				}
				else {
					string temp = passwrd;
					while (temp.length() > 0) {
						cout << "\b \b";// \b la dai bien cho nut xoa (backspace). Vd: Hello\bHi == HellHi
						temp.pop_back();// loại bỏ kí tự cuoi cung cua chuoi
					}
					for (int i = 0; i < passwrd.length(); i++) {
						cout << '*';
					}
				}
				isHidden = !isHidden;
			}
		}
		else if (ch == 8) {// Space
			if (passwrd.length() > 0) {
				cout << "\b \b";
				passwrd.pop_back();
			}
		}
		else if (passwrd.length() == 13) {

		}
		else {
			passwrd += ch;
			if (isHidden) {
				cout << "*";
			}
			else cout << ch;
		}
	}
}
void initList(ListUser& list) {
	list.head = NULL;
	list.tail = NULL;
	list.size = 0;
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
// Ham khoi tao 1 NODE users bang cach doc thong tin users tu file csv
User* convertUserData(ifstream& data) {//.Doc thong tin 1 sinh vien ( vs bien truyen vao la chi vi cua con tro doc file) va tra ve 1 con tro User*
	User* userData = new User;
	Date dateOfBirth;
	string temp;
	//.Bat dau doc thong tin sinh vien tu file vao
	getline(data, userData->id, ',');
	if (userData->id == "") return NULL;
	getline(data, userData->password, ',');
	getline(data, userData->lastName, ',');
	getline(data, userData->firstName, ',');
	getline(data, userData->className, ',');
	getline(data, userData->gender, ',');
	getline(data, temp, ',');
	userData->dateOfBirth = strToDate(temp);
	getline(data, temp, ',');
	userData->academicYear = stoi(temp);
	getline(data, temp, '\n');
	if (temp == "TRUE") userData->isStaff = true;
	else userData->isStaff = false;
	userData->next = NULL;
	userData->prev = NULL;
	return userData;
}
//.Them 1 NODE vao cuoi dslk.--> OK!
void addUser(ListUser& list, User* user) {
	if (user == NULL) return;
	if (list.head == NULL) {
		list.head = list.tail = user;
	}
	else {
		list.tail->next = user;
		user->prev = list.tail;
		list.tail = user;
	}
	list.size++;
}
//.Doc toan bo thong tin cac sinh vien va luu thong tin vao 1 dslk listUser --> OK!
void getListUsers() {
	ifstream fin("D:/Users Information/users.csv");
	string  data = "";//.cai nay hoi thua(k can thiet).-->co the bo cmnl!
	getline(fin, data);// data luc nay chua toan bo noi dung file csv (co ca ki tu (\n) la xuong dong)-->data luc nay la toan bo noi dung cua file csv.
	initList(listUser);
	while (!fin.eof()) {//. duyet toi cuoi file csv thi dung.
		addUser(listUser, convertUserData(fin));//.Them 1 Node=convertUserData(fin) vao cuoi listUser
	}
}
void getCurrentSchoolYear() {
	const int beginSchoolYearMonth = 9;
	if (currentDate.month < beginSchoolYearMonth) {
		currentSchoolYear = to_string(currentDate.year - 1) + "-" + to_string(currentDate.year);
	}
	else {
		currentSchoolYear = to_string(currentDate.year) + "-" + to_string(currentDate.year + 1);
	}
}
void loginSystem() {
	system("cls");
	getListUsers();
	getCurrentSchoolYear();
	getCurrentSemester();
	getListCourses();
	schoolYearPath = "./data/" + currentSchoolYear;

	while (true) {
		hideCursor(false);
		loginUI();
		if (currentUser == NULL) {
			notifyBox("Login Fail");
		}
		else {
			notifyBox("Login Succesful");
			break;
		}
	}
	if (currentUser->isStaff) {
		staffMenu();
	}
	else {
		studentMenu();
	}
	system("cls");
}
int main() {
	//.Wigth of Screen is: 120 ; Height of Screen is: 30; .Need to form a box that is Middle of the Screen--> divide screen width and screen height into 3 parts.
	const int width = 40;//=120/3
	const int height = 10;//=30/3
	const int left = 40;
	const int top = 10;

	drawBox(width, height, left, top);
	textAlignCenter("HCMUS PORTAL", left, width, 6);
	textAlignCenter("LOGIN", left, width, 7);
	/*gotoXY(40, 8); cout << currentDate.wDay;
	gotoXY(40, 9); cout << dateToStr(currentDate);*/
	gotoXY(48,yPos);
	cout << "ID:";
	gotoXY(48, yPos + 2);
	cout << "PASSWORD:";
	gotoXY(73, yPos + 2);
	cout << " Hidden";
	cout << char(254);
	gotoXY(48, yPos + 3);
	cout << "(press F1 to show password)";
	gotoXY(53, yPos);//.chinh con tro lai toa do (48+7,yPos) nghia la truoc dong "ID:" 3 don vi! vi toa do cua ki tu ":" cua dong "ID" la (48+3,yPos).
	getline(cin, id);
	password = getPassword(true);
	currentUser = login(id, password);
	loginSystem;
}
