
#include "Console.h"
#include"struct.h"
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
// Hàm in menu và highlight tùy chọn được chọn
void printMenu(const vector<string>&options, int currentOption,int k) {//.Ham nay dung de in ra MENU cua 1 trang con.
    // dùng để xóa những gì đã hiển thị trên của sổ console , nghĩa là sau khi nhấn 1 trong các phím w /s thì nó sẽ chuyển sang 1 op khác nhưng cái dòng menu vs op cũ đc chọn vẫn còn nếu k dùng lệnh này, muốn rõ hơn thì xóa dòng này r chạy chương trình là biết.
    system("cls");
	k = yPos;
    for (int i = 0; i < options.size(); ++i) {
        if (i == currentOption) {
            //.Nếu là currOp thì mình đổi màu chữ--> cout ra op --> đổi lại màu chữ trắng . còn k phải curOp thì mình sẽ cout thôi, nghĩa là àu chữ trắng
            // Thay đổi màu sắc chữ cho cả dòng code sau này , nếu k có lệnh trả lại màu chữ ban đầu thì màu chữ đc in ra luôn là xanh lá
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			gotoXY(48, k);
            cout << options[i] << endl;
			k++;
            // Trả lại màu sắc mặc định sau khi in xong dòng chữ của của phần tử curr trong vector,sau lệnh này thì những dòng chữ đc in ra co màu trắng (hủy lệnh thay đổi màu chữ phía trên).
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        else {
			gotoXY(48, k);
            cout << options[i] << endl;
			k++;
        }
    }
}
