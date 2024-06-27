
#include "Console.h"
#include"struct.h"
#include "User.h"
#include "Login.h"
#include "Student.h"
#include "Class.h"
const int yPos = 13;
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
	size_t x = ((width - s.length()) / 2) + left + 1;
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
void notifyBox(string noti)
{
	hideCursor(true);
	system("cls");
	//set kich thuoc khung thong bao
	int width = 45;
	int height = 5;
	int left = 40;
	int top = 9;
	int yPos = 11;

	gotoXY(57, 8);
	cout << "NOTIFICATION";
	//alignRow(45, yPos, noti, 37);
	height += (yPos - 11);

	drawBox(width, height, left, top);
	yPos++;

	gotoXY(45, yPos);
	cout << noti;

	int key = _getch(); //dung man hinh, nguoi dung nhap ky tu bat ky thi tiep tuc
	system("cls");
}
//hàm chuyển sang chuỗi dạng wstring
wstring strToWstr(string s) {
	int len;
	int sLength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), sLength, 0, 0);
	std::wstring r(len, L'\0');
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), sLength, &r[0], len);
	return r;
}
//hàm tạo header cho background (màu)
void headerBackGround(int x, int y)
{
	gotoXY(x, y); cout << " ___  ___  _______   __    __   __    __   _____" << endl;
	gotoXY(x, y + 1); cout << " | |__| |  |  ___|  |  \\  /  |  | |  | |  |  ___| " << endl;
	gotoXY(x, y + 2); cout << " |  __  |  | |      | | \\/ | |  | |  | |  |___  |  " << endl;
	gotoXY(x, y + 3); cout << " | |  | |  | |___   | |    | |  | |__| |   ___| | " << endl;
	gotoXY(x, y + 4); cout << " |_|  |_|  |_____|  |_|    |_|  |______|  |_____| " << endl;
}
void bodyBackground(int x, int y)
{
	gotoXY(x, y); cout << "  __________   _________    ________   ____________  _________    ____       " << endl;
	gotoXY(x, y + 1); cout << "  |   __   |   |  ___  |   |   __   |  |____  ____|  |  ____  |   |  |       " << endl;
	gotoXY(x, y + 2); cout << "  |  |  |  |   |  | |  |   |  |  |  |      |  |      |  |  |  |   |  |       " << endl;
	gotoXY(x, y + 3); cout << "  |  |__|  |   |  | |  |   |  |__|  |      |  |      |  |__|  |   |  |        " << endl;
	gotoXY(x, y + 4); cout << "  |  ______|   |  | |  |   |  __   /       |  |      |   __   |   |  |        " << endl;
	gotoXY(x, y + 5); cout << "  |  |         |  | |  |   |  | \\  \\       |  |      |  |  |  |   |  |         " << endl;
	gotoXY(x, y + 6); cout << "  |  |         |  |_|  |   |  |  \\  \\      |  |      |  |  |  |   |  |-----.     " << endl;
	gotoXY(x, y + 7); cout << "  |__|         |_______|   |__|   \\__\\     |__|      |__|  |__|   |________|   " << endl;
}
void footerBackground()
{
	hideCursor(true);
	int width = 80;
	int height = 1;
	int left = 20;
	int top = 24;
	int percent = 21;
	drawBox(width, height, left, top);
	for (int i = 0; i < 80; i++) {
		gotoXY(i + 21, 25); cout << char(219);
		gotoXY(95, 23); cout << percent << "%";
		percent++;
		Sleep(25);
	}
	system("cls");
}

void loginSystem()
{
	//xoa man hinh va load cac du lieu co san tu file
	system("cls");
	getListUsers();
	schoolYearPath = "./data/" + currentSchoolYear;// tao duong dan den file nam hoc hien tai

	//vong lap de thao tac voi giao dien dang nhap
	//ham se chuyen sang giao dien khac khi tai khoan dang nhap dung
	while (true)
	{
		hideCursor(false);//an con tro
		loginUI();// hien ra cua so dang nhap

		if (currentUser == NULL)
		{
			notifyBox("Login Fail");
		}
		else
		{
			notifyBox("Login Succesful");
			break;
		}
	}

	if (currentUser->isStaff) //la staff thi chuyen sang giao dien cua staff
	{
		//staffMenu();
		StaffMenu();
	}
	else //nguoc lai la giao dien cua student
	{
		//studentMenu()
		StudentMenu();
	}
	system("cls");

	deleteClassNameList(listClassName);
	deleteListClasses(listClasses);
	delete[]listClassName;
	delete[]listClasses;
}

void waittingscreen()
{
	hideCursor(true);
	system("cls");
	headerBackGround(35, 2);
	bodyBackground(22, 10);
	footerBackground();

	loginSystem();
}

// Hàm in menu và highlight tùy chọn được chọn
void printMenu(const vector<string>& options, int currentOption, int k) {//.Ham nay dung de in ra MENU cua 1 trang con.
	// dùng để xóa những gì đã hiển thị trên của sổ console , nghĩa là sau khi nhấn 1 trong các phím w /s thì nó sẽ chuyển sang 1 op khác nhưng cái dòng menu vs op cũ đc chọn vẫn còn nếu k dùng lệnh này, muốn rõ hơn thì xóa dòng này r chạy chương trình là biết.
	system("cls");
	for (int i = 0; i < options.size(); ++i) {
		if (i == currentOption) {
			//.Nếu là currOp thì mình đổi màu chữ--> cout ra op --> đổi lại màu chữ trắng . còn k phải curOp thì mình sẽ cout thôi, nghĩa là àu chữ trắng
			// Thay đổi màu sắc chữ cho cả dòng code sau này , nếu k có lệnh trả lại màu chữ ban đầu thì màu chữ đc in ra luôn là xanh lá
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			gotoXY(53, k);
			cout << options[i] << endl;
			k++;
			// Trả lại màu sắc mặc định sau khi in xong dòng chữ của của phần tử curr trong vector,sau lệnh này thì những dòng chữ đc in ra co màu trắng (hủy lệnh thay đổi màu chữ phía trên).
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		else {
			gotoXY(53, k);
			cout << options[i] << endl;
			k++;
		}
	}
}

//phần xử lý ngày tháng năm
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
Date CurrentDate() {
	// Lấy thời gian hiện tại
	std::time_t t = std::time(nullptr);
	// Khởi tạo cấu trúc tm
	std::tm now;
	// Chuyển đổi sang cấu trúc tm sử dụng localtime_s
	localtime_s(&now, &t);

	// In ra ngày tháng hiện tại
	// Tạo đối tượng Date và gán các giá trị
	Date d;
	d.day = now.tm_mday;
	d.month = now.tm_mon + 1;
	d.year = now.tm_year + 1900;

	return d;
}
