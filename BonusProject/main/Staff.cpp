
#include"Console.h"
#include"Login.h"
#include"SchoolYear.h"
#include"Staff.h"
#include"struct.h"
#include"Student.h"
#include"User.h"
using namespace std;
//Sau khi login thi ta da co currentUser ,viec bay h chi la xuat CurrentUser ra
const string path = "Data/Course/courses.csv";
void Profile() {//.OPTION 2
	int width = 40;
	int height = 7;
	int left = 40;
	int top = 8;
	int yPos = 10;
	Date dateOfBirth = currentUser->dateOfBirth;
	gotoXY(55, yPos - 4); cout << "HCMUS Portal";
	gotoXY(57, yPos - 2); cout << "Profile";
	gotoXY(48, yPos); cout << "Last name: " << currentUser->lastName;
	yPos++;
	gotoXY(48, yPos); cout << "First name: " << currentUser->firstName;
	yPos++;
	gotoXY(48, yPos); cout << "Gender: " << currentUser->gender;
	yPos++;
	if (!currentUser->isStaff) {
		gotoXY(48, yPos); cout << "Class: " << currentUser->className;
		yPos++;
		gotoXY(48, yPos); cout << "Student ID: " << currentUser->id;
		yPos++;
	}
	else {
		gotoXY(48, yPos); cout << "Staff ID: " << currentUser->id;
		yPos++;
	}
	gotoXY(48, yPos); cout << "Date of Birth: " << dateOfBirth.day << '/' << dateOfBirth.month << '/' << dateOfBirth.year;
	yPos += 2;
	gotoXY(48, yPos);
}

void userAccount() {//.OPTION 1
	gotoXY(55, 5); cout << "HCMUS Portal";
	const int width = 40;
	const int height = 7;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 10;
	vector<string> options = { "Change Password","Logout","Back"};
	int currentOption = 0;
	int onMenu3 = 0;
	char key;
	do {
		int k = 9;
		if (onMenu3 == 0) {
			printMenu(options, currentOption, k);
			drawBox(40, 10, 40, 7);
			textAlignCenter("User Account", 40, 40, 4);
			key = _getch(); // Nhận phím từ người dùng mà không cần nhấn Enter
			switch (key) {
			case 'w':
				if (currentOption > 0) {
					currentOption--;
				}
				break;
			case 's':
				if (currentOption < options.size() - 1) {
					currentOption++;
				}
				break;
			case 13: // Enter
				if (currentOption == 1) { // Chọn Option 2
					onMenu3 = 2; // Đặt biến onMenu thành false để chuyển đến trang mới
				}
				if (currentOption == 0) {//.Option 1
					onMenu3 = 1;
				}
				if (currentOption == 2) {//.current Option ma bang options.size()-1 thi la phan tu cuoi va chung la "Thoat".
					onMenu3 = 100;
					key = 'q';
				}
				break;
			default:
				break;
			}
		}
		else if (onMenu3 == 2) {//.Option2
			system("cls");
			loginSystem();
		}
		else if (onMenu3 == 1) {//.Option1
			system("cls");
			changePassword();
			/*system("pause");*/
			//.<Goi ham la trang khi ma chon vao 1 OPTION co onMenu3=1 (OPTION 1)>
			onMenu3 = 0;//.Sau ham se la: onMenu3 = 0 de khi ta nhan 'q' de thoat khoi ham(trang) do thi no se dat onMenu3=0 de in ra lai trang MẸ
		}
		else if (onMenu3 == 100) {
			break;
		}
	} while (key != 'q');
}
void logout() {
	currentUser = NULL;
}
void changePassword() {
	const int width = 40;
	const int height = 7;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;
	string currentPassword;

	hideCursor(false);
	
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(53, 7); cout << "Change Password";
		gotoXY(45, yPos); cout << "Current password: ";
		yPos++;
		yPos++;
		getline(cin, currentPassword);
		if (currentPassword == currentUser->password) {
			gotoXY(45, yPos); cout << "New password: ";
			yPos++;
			string tmp;
			getline(cin, tmp);
			currentUser->password = tmp;
			notifyBox("Successful");
			hideCursor(true);
			saveListUser();
			return;
		}
		else {
			gotoXY(45, 11); cout << "Wrong password!!!";
			system("pause");
		}
}
//.
void appendNumberToCSV(const std::string& filePath, Course*temp) {
	// Mở file .csv ở chế độ append (thêm vào cuối file)
	ofstream fout(filePath, std::ios_base::app);

	if (fout.is_open()) {
			string session = temp->session[0] + "-" + temp->session[1];
			fout << temp->id << "," << temp->courseName << "," << temp->teacherName << ","
				<< temp->credits << "," << temp->academicYear << "," << temp->numOfStudents << ","
				<< temp->NumofEroller << "," << temp->weekDay << "," << session;
		fout.close();
	}
	else {
		std::cerr << "Unable to open file";
	}
}
//.
void AddCourse(ListCourse& l, Course* p) {
	if (l.pHead == NULL) {
		l.pHead = p;
		l.pHead->pNext = NULL;
		return;
	}
	Course* k = l.pHead;
	while (k->pNext != NULL) {

		k = k->pNext;
	}
	k->pNext = p;
	k->pNext->pNext = NULL;
}
void ReadFileGetList(ListCourse& l, string fileName) {
	l.pHead = NULL;
	ifstream fin(fileName);
	string t1, t2;
	if (fin.is_open() == false) {
		cout << "Khong mo duoc file!";
		return;
	}
	else {
		getline(fin, t1);
		getline(fin, t2);
		while (fin.eof() == false) {
			Course* tmp = new Course();
			getline(fin, tmp->id, ',');
			getline(fin, tmp->courseName, ',');
			getline(fin, tmp->teacherName, ',');
			fin >> tmp->credits;
			fin.ignore();
			fin >> tmp->academicYear;
			fin.ignore();
			fin >> tmp->numOfStudents;
			fin.ignore();
			fin >> tmp->NumofEroller;
			fin.ignore();
			getline(fin, tmp->weekDay, ',');
			getline(fin, tmp->session[0], '-');
			getline(fin, tmp->session[1]);
			AddCourse(l, tmp);
		}
		fin.close();
	}
}
int CountCourse(ListCourse l) {
	int cnt = 0;
	Course* tmp = l.pHead;
	while (tmp != NULL) {
		cnt++;
		tmp = tmp->pNext;
	}
	return cnt;
}
void PrintTitle() {
	int x = 0, y = 0;
	gotoXY(x, y);
	cout << "Course ID";
	x += 13;
	gotoXY(x, y);
	cout << "Course Name";
	x += 35;
	gotoXY(x, y);
	cout << "Credits";
	x += 10;
	gotoXY(x, y);
	cout << "Academic";
	gotoXY(x, y + 1); cout << "  Years";
	x += 10;
	gotoXY(x, y);
	cout << "Number of";
	gotoXY(x, y + 1); cout << "Students";
	x += 10;
	gotoXY(x, y);
	cout << "Number of";
	gotoXY(x, y + 1);
	cout << "Enrollers";
	x += 13;
	gotoXY(x, y);
	cout << "weekDay";
	x += 10;
	gotoXY(x, y);
	cout << "Session" << endl;
}
void PrintListCourse(ListCourse l) {
	int x = 0, y = 0;
	gotoXY(x, y);
	cout << "Course ID";
	x += 13;
	gotoXY(x, y);
	cout << "Course Name";
	x += 35;
	gotoXY(x, y);
	cout << "Credits";
	x += 10;
	gotoXY(x, y);
	cout << "Academic";
	gotoXY(x, y + 1); cout << "  Years";
	x += 10;
	gotoXY(x, y);
	cout << "Number of";
	gotoXY(x, y + 1); cout << "Students";
	x += 10;
	gotoXY(x, y);
	cout << "Number of";
	gotoXY(x, y + 1);
	cout << "Enrollers";
	x += 13;
	gotoXY(x, y);
	cout << "weekDay";
	x += 10;
	gotoXY(x, y);
	cout << "Session" << endl;
	y++;
	x = 0;
	Course* tmp1 = l.pHead;
	x = 0, y = 4;
	while (tmp1 != NULL) {
		gotoXY(x, y);
		cout << tmp1->id;
		x += 13;
		gotoXY(x, y);
		cout << tmp1->courseName;
		x += 35;
		gotoXY(x, y);
		cout << tmp1->credits;
		x += 10;
		gotoXY(x, y);
		cout << tmp1->academicYear;
		x += 10;
		gotoXY(x, y);
		cout << tmp1->numOfStudents;

		x += 10;
		gotoXY(x, y);
		cout << tmp1->NumofEroller;

		x += 13;
		gotoXY(x, y);
		cout << tmp1->weekDay;

		x += 10;
		gotoXY(x, y);
		cout << tmp1->session[0] << "-" << tmp1->session[1] << endl;
		y++;
		x = 0;
		tmp1 = tmp1->pNext;
	}
}
void PrintCourseInLine(Course tmp1, int& x, int& y) {
	gotoXY(x, y);
	cout << tmp1.id;
	x += 13;
	gotoXY(x, y);
	cout << tmp1.courseName;
	x += 35;
	gotoXY(x, y);
	cout << tmp1.credits;
	x += 10;
	gotoXY(x, y);
	cout << tmp1.academicYear;
	x += 10;
	gotoXY(x, y);
	cout << tmp1.numOfStudents;

	x += 10;
	gotoXY(x, y);
	cout << tmp1.NumofEroller;

	x += 13;
	gotoXY(x, y);
	cout << tmp1.weekDay;

	x += 10;
	gotoXY(x, y);
	cout << tmp1.session[0] << "-" << tmp1.session[1] << endl;
}
void printMenu1(Course* options, int size, int currentOption) {
	//.Ham nay dung de in ra MENU cua 1 trang con.
	// dùng để xóa những gì đã hiển thị trên của sổ console , nghĩa là sau khi nhấn 1 trong các phím w /s thì nó sẽ chuyển sang 1 op khác nhưng cái dòng menu vs op cũ đc chọn vẫn còn nếu k dùng lệnh này, muốn rõ hơn thì xóa dòng này r chạy chương trình là biết.
	system("cls");
	int x = 0, y = 2;
	for (int i = 0; i <= size; i++) {
		if (i == currentOption) {
			if (i == size) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << endl << endl;
				cout << "                                                Back";
				y++;
				x = 0;
				// Trả lại màu sắc mặc định sau khi in xong dòng chữ của của phần tử curr trong vector,sau lệnh này thì những dòng chữ đc in ra co màu trắng (hủy lệnh thay đổi màu chữ phía trên).
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else {
				//.Nếu là currOp thì mình đổi màu chữ--> cout ra op --> đổi lại màu chữ trắng . còn k phải curOp thì mình sẽ cout thôi, nghĩa là àu chữ trắng
				// Thay đổi màu sắc chữ cho cả dòng code sau này , nếu k có lệnh trả lại màu chữ ban đầu thì màu chữ đc in ra luôn là xanh lá
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);

				PrintCourseInLine(options[i], x, y);
				y++;
				x = 0;
				// Trả lại màu sắc mặc định sau khi in xong dòng chữ của của phần tử curr trong vector,sau lệnh này thì những dòng chữ đc in ra co màu trắng (hủy lệnh thay đổi màu chữ phía trên).
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
		else {
			if (i == size) {
				cout << endl << endl;
				cout << "                                                Back";
				y++;
				x = 0;
			}
			else {
				PrintCourseInLine(options[i], x, y);
				y++;
				x = 0;
			}
		}
	}
}
Course* GetPreviuosCourse(ListCourse l, Course* p) {
	Course* tmp = l.pHead;
	while (tmp->pNext != NULL) {
		if (tmp->pNext->courseName == p->courseName && tmp->pNext->academicYear == p->academicYear && tmp->pNext->credits == p->credits && tmp->pNext->id == p->id && tmp->pNext->NumofEroller == p->NumofEroller && tmp->pNext->numOfStudents == p->numOfStudents && tmp->pNext->session == p->session && tmp->pNext->teacherName == p->teacherName && tmp->pNext->weekDay == p->weekDay)
		{
			return tmp;
		}
		tmp = tmp->pNext;
	}
	return NULL;

}
	void saveCourses(string path, ListCourse& l) {
		ofstream fout(path);
		fout << "Courses registration session:," << endl;
		fout << "ID,Course name,Teacher name,Credits,Academic year,Number of students, Number of enroller,Day of the week,Session" << endl;
		Course* temp = l.pHead;
		while (temp != NULL) {
			string session = temp->session[0] + "-" + temp->session[1];
			fout << temp->id << "," << temp->courseName << "," << temp->teacherName << ","
				<< temp->credits << "," << temp->academicYear << "," << temp->numOfStudents << ","
				<< temp->NumofEroller << "," << temp->weekDay << "," << session;
			temp = temp->pNext;
			if (temp != NULL) fout << endl;
		}
		fout.close();
	}
void DeleteCourse(ListCourse& l, Course p, string path) {

	Course* tmp = l.pHead;
	if (tmp->courseName == p.courseName && tmp->academicYear == p.academicYear && tmp->credits == p.credits && tmp->id == p.id && tmp->NumofEroller == p.NumofEroller && tmp->numOfStudents == p.numOfStudents && tmp->session[0] == p.session[0] && tmp->session[1] == p.session[1] && tmp->teacherName == p.teacherName && tmp->weekDay == p.weekDay)
	{
		l.pHead = tmp->pNext;
		delete tmp;
		return;
	}


	while (tmp != NULL) {
		if (tmp->courseName == p.courseName && tmp->academicYear == p.academicYear && tmp->credits == p.credits && tmp->id == p.id && tmp->NumofEroller == p.NumofEroller && tmp->numOfStudents == p.numOfStudents && tmp->session[0] == p.session[0] && tmp->session[1] == p.session[1] && tmp->teacherName == p.teacherName && tmp->weekDay == p.weekDay)
		{
			Course* tmp1 = GetPreviuosCourse(l, tmp);
			tmp1->pNext = tmp->pNext;
			delete tmp;
			break;
		}
		tmp = tmp->pNext;
	}
	saveCourses(path, l);//.Luu danh sach sau khi xoa course ve lai file courses.csv
	ReadFileGetList(l, path);
}
void printMenu3(const vector<string>& options, int currentOption, int k) {//.Ham nay dung de in ra MENU cua 1 trang con.
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
void Upper(string& s) {
	transform(s.begin(), s.end(), s.begin(), ::toupper);
}
Course* ConvertToArr(ListCourse l) {
	Course* tmp = l.pHead;
	int n = CountCourse(l);
	Course* c = new Course[n + 1];
	int i = 0;
	while (tmp != NULL) {
		c[i].academicYear = tmp->academicYear;
		c[i].courseName = tmp->courseName;
		c[i].credits = tmp->credits;
		c[i].id = tmp->id;
		c[i].NumofEroller = tmp->NumofEroller;
		c[i].numOfStudents = tmp->numOfStudents;
		c[i].session[0] = tmp->session[0];
		c[i].session[1] = tmp->session[1];
		c[i].teacherName = tmp->teacherName;
		c[i].weekDay = tmp->weekDay;
		tmp = tmp->pNext;
		i++;
	}
	return c;
}
void AddTail(ListCourse& l, Course* c) {
	if (l.pHead == NULL) {
		l.pHead = c;
		l.pHead->pNext = NULL;
		return;
	}
	Course* tmp = l.pHead;
	while (tmp->pNext != NULL) {
		tmp = tmp->pNext;
	}
	tmp->pNext = c;
	tmp->pNext->pNext = NULL;
}
Course* ConvertFromCourseToPointer(Course c) {
	Course* tmp = new Course;
	tmp->id = c.id;
	tmp->academicYear = c.academicYear;
	tmp->courseName = c.courseName;
	tmp->credits = c.credits;
	tmp->NumofEroller = c.NumofEroller;
	tmp->numOfStudents = c.numOfStudents;
	tmp->session[0] = c.session[0];
	tmp->session[1] = c.session[1];
	tmp->teacherName = c.teacherName;
	tmp->weekDay = c.weekDay;
	tmp->pNext = NULL;
	return tmp;
}
void ConvertFromArrToList(ListCourse& l, Course* c) {
	int size = CountCourse(l);
	l.pHead = NULL;
	for (int i = 0; i < size; i++) {
		Course* tmp1 = ConvertFromCourseToPointer(c[i]);
		AddTail(l, tmp1);
	}
}
void ChangeCourse(ListCourse& l, string path, int ans) {
	system("cls");
	Course course;
	Course* arr = ConvertToArr(l);
	string session;
	string id = course.id;
	gotoXY(55, 7); cout << "Change Course";
	hideCursor(false);
	gotoXY(45, 10); cout << "Course ID: ";
	gotoXY(45, 11); cout << "Course name:";
	gotoXY(45, 12); cout << "Teacher name: ";
	gotoXY(45, 13); cout << "Academic year: ";
	gotoXY(45, 14); cout << "Number of credits: ";
	gotoXY(45, 15); cout << "Nums of students: ";
	gotoXY(45, 16); cout << "Num of enrollers: ";
	gotoXY(45, 17); cout << "Weekday: ";
	gotoXY(45, 18); cout << "Session (S1,S2,S3,S4) (Format:XX-YY): ";

	gotoXY(56, 10); getline(cin, course.id);
	gotoXY(58, 11); getline(cin, course.courseName);
	gotoXY(59, 12); getline(cin, course.teacherName);
	gotoXY(60, 13); cin >> course.academicYear;
	gotoXY(64, 14); cin >> course.credits;
	gotoXY(64, 15); cin >> course.numOfStudents;
	cin.ignore();
	gotoXY(64, 16); cin >> course.NumofEroller;
	cin.ignore();
	gotoXY(54, 17); getline(cin, course.weekDay);
	Upper(course.weekDay);
	gotoXY(85, 18); getline(cin, session);
	Upper(session);
	course.session[0] = session.substr(session.find('S'), 2);
	session.erase(session.find('S'), 2);
	course.session[1] = session.substr(session.find('S'), 2);
	hideCursor(true);
	/*arr[ans] = course;*/
	arr[ans].id = course.id;
	arr[ans].academicYear = course.academicYear;
	arr[ans].credits = course.credits;
	arr[ans].courseName = course.courseName;
	arr[ans].teacherName = course.teacherName;
	arr[ans].weekDay = course.weekDay;
	arr[ans].NumofEroller = course.NumofEroller;
	arr[ans].numOfStudents = course.numOfStudents;
	arr[ans].session[0] = course.session[0];
	arr[ans].session[1] = course.session[1];
	ConvertFromArrToList(l, arr);
	saveCourses(path, l);
}
void Detail(ListCourse& l, int ans) {
	Course* c = ConvertToArr(l);
	gotoXY(45, 10); cout << "Course ID: " << c[ans].id;
	gotoXY(45, 11); cout << "Course name:" << c[ans].courseName;
	gotoXY(45, 12); cout << "Teacher name: " << c[ans].teacherName;
	gotoXY(45, 13); cout << "Academic year: " << c[ans].academicYear;
	gotoXY(45, 14); cout << "Number of credits: " << c[ans].credits;
	gotoXY(45, 15); cout << "Nums of students: " << c[ans].numOfStudents;
	gotoXY(45, 16); cout << "Num of enrollers: " << c[ans].NumofEroller;
	gotoXY(45, 17); cout << "Weekday: " << c[ans].weekDay;
	gotoXY(45, 18); cout << "Session (S1,S2,S3,S4): " << c[ans].session[0] << "-" << c[ans].session[1] << endl;

}

//code oo thanh
Student EnterStudent() {
	Student s;
	cout << "Enter ID: ";
	getline(cin, s.studentID);
	cout << "Enter Last Name: ";
	getline(cin, s.lastName);
	cout << "Enter First Name: ";
	getline(cin, s.firstName);
	cout << "Enter Gender: ";
	getline(cin, s.gender);
	cout << "Enter Date of Birth: " << endl;
	cout << "Enter day: ";
	cin >> s.dateOfBirth.day;
	cout << "Enter month: ";
	cin >> s.dateOfBirth.month;
	cout << "Enter year: ";
	cin >> s.dateOfBirth.year;
	cin.ignore();
	cout << "Enter Social ID: ";
	getline(cin, s.socialID);
	s.finalMark = 1 + rand() % 9;
	s.midtermMark = 1 + rand() % 9;
	s.otherMark = 1 + rand() % 9;
	return s;
}
void InitListStudent(ListStudent*& list) {
	list = new ListStudent;
	list->head = list->tail = NULL;
}

NodeStudent* createNewNodeStudent(Student& st) {
	NodeStudent* newStudent = new NodeStudent;
	newStudent->studentInfo = st;
	newStudent->next = NULL;
	return newStudent;
}

void addStudentIntoListStudent(ListStudent*& list, Student st) {
	NodeStudent* newStudent = createNewNodeStudent(st);
	if (list->head == NULL && list->tail == NULL) {
		list->head = list->tail = newStudent;
	}
	else {
		list->tail->next = newStudent;
		list->tail = newStudent;
	}
}	

double strToDouble(string& s) {
	return stod(s);
}

ListStudent* loadFileDataOfStudent(string ListFileName[], int ans)
{
	// Chỗ này là mình set đường dẫn
	string classPath = ListFileName[ans];

	ifstream fIn;
	fIn.open(classPath);
	if (!fIn.is_open())
	{
		cout << "Cant open this file" << endl;
		return NULL;
	}

	ListStudent* studentsInCurrentClass = new ListStudent[150];
	InitListStudent(studentsInCurrentClass);

	// Đọc qua dòng đầu chứa các tiêu đề
	string tmpData;
	getline(fIn, tmpData, '\n');
	while (getline(fIn, tmpData)) {
		istringstream ss(tmpData);
		Student newStudent;
		string s, dateOfBirth;
		string otherScore, midScore, finalScore;

		getline(ss, s, ',');
		if (s == "") break;

		getline(ss, newStudent.studentID, ',');
		getline(ss, newStudent.lastName, ',');
		getline(ss, newStudent.firstName, ',');
		getline(ss, newStudent.gender, ',');
		getline(ss, dateOfBirth, ',');
		newStudent.dateOfBirth = strToDate(dateOfBirth);
		getline(ss, newStudent.socialID, ',');

		getline(ss, otherScore, ',');
		newStudent.otherMark = strToDouble(otherScore);

		getline(ss, midScore, ',');
		newStudent.midtermMark = strToDouble(midScore);

		getline(ss, finalScore, '\n');
		newStudent.finalMark = strToDouble(finalScore);

		addStudentIntoListStudent(studentsInCurrentClass, newStudent);
	}

	cout << "Doc file thanh cong" << endl;
	fIn.close();
	return studentsInCurrentClass;
}
void saveDataOfListStudent(string currentClass, ListStudent* list) {//EXPORT	

	// Cho người dùng nhập tên lớp
	string classPath = currentClass;

	ofstream fOut;
	fOut.open(classPath);
	if (!fOut.is_open()) {
		cout << "Can't open this file. " << endl;
		return;
	}

	fOut << "N0, Student ID, Last Name, First Name, Gender, Date of birth, Social ID" << endl;
	NodeStudent* curr = list->head;
	int i = 1;
	while (curr != NULL) {
		string dateOfBirth = to_string(curr->studentInfo.dateOfBirth.day) + "/" + to_string(curr->studentInfo.dateOfBirth.month) + "/" + to_string(curr->studentInfo.dateOfBirth.year);
		fOut << i << "," << curr->studentInfo.studentID << "," << curr->studentInfo.lastName << "," << curr->studentInfo.firstName << ","
			<< curr->studentInfo.gender << "," << dateOfBirth << "," << curr->studentInfo.socialID;
		curr = curr->next;
		if (curr != NULL) {
			fOut << endl;
		}
		i++;

	}
	fOut.close();
}
void saveDataOfListStudent2(string currentClass, ListStudent* list) {

	// Cho người dùng nhập tên lớp
	string classPath = currentClass;

	ofstream fOut;
	fOut.open(classPath);
	if (!fOut.is_open()) {
		cout << "Can't open this file. " << endl;
		return;
	}

	fOut << "N0, Student ID, Last Name, First Name, Gender, Date of birth, Social ID, Other Mark, Midterm Mark, Final Mark" << endl;
	NodeStudent* curr = list->head;
	int i = 1;
	while (curr != NULL) {
		string dateOfBirth = to_string(curr->studentInfo.dateOfBirth.day) + "/" + to_string(curr->studentInfo.dateOfBirth.month) + "/" + to_string(curr->studentInfo.dateOfBirth.year);
		fOut << i << "," << curr->studentInfo.studentID << "," << curr->studentInfo.lastName << "," << curr->studentInfo.firstName << ","
			<< curr->studentInfo.gender << "," << dateOfBirth << "," << curr->studentInfo.socialID << "," << curr->studentInfo.otherMark
			<< "," << curr->studentInfo.midtermMark << "," << curr->studentInfo.finalMark;
		curr = curr->next;
		if (curr != NULL) {
			fOut << endl;
		}
		i++;
	}
	fOut.close();

}
void PrintListstudentOfClass(ListStudent* l) {
	NodeStudent* tmp1 = l->head;
	int y = 3;
	gotoXY(20, y); cout << "ID";
	gotoXY(33, y); cout << "LastName";
	gotoXY(50, y); cout << "FirstName";
	gotoXY(60, y); cout << "Gender";
	gotoXY(75, y); cout << "Date Of Birth";
	gotoXY(90, y); cout << "Social ID";
	y = 5;
	while (tmp1 != NULL) {
		gotoXY(20, y); cout << tmp1->studentInfo.studentID;
		gotoXY(33, y); cout << tmp1->studentInfo.lastName;
		gotoXY(50, y); cout << tmp1->studentInfo.firstName;
		gotoXY(60, y); cout << tmp1->studentInfo.gender;
		gotoXY(75, y); cout << tmp1->studentInfo.dateOfBirth.day << "/" << tmp1->studentInfo.dateOfBirth.month << "/" << tmp1->studentInfo.dateOfBirth.year;
		gotoXY(90, y); cout << tmp1->studentInfo.socialID;
		y++;
		tmp1 = tmp1->next;
	}
	cout << endl << endl << endl;
}
void ExportToCSV(ListStudent* l) {
	cout << "Enter File Name: ";
	string filename;
	getline(cin, filename);
	system("cls");
	saveDataOfListStudent(filename, l);
	notifyBox("EXPORT TO CSV COMPLETELY!");
}
void ImportScoreboard(ListStudent* l, string listFileName[], int ans) {
	l = loadFileDataOfStudent(listFileName, ans);
	notifyBox("IMPORTED SCOREBOARD!");
}
void ScoreListstudentOfClass(ListStudent* l) {
	NodeStudent* tmp1 = l->head;
	int y = 3;
	gotoXY(0, y); cout << "ID";
	gotoXY(13, y); cout << "LastName";
	gotoXY(30, y); cout << "FirstName";
	gotoXY(40, y); cout << "Gender";
	gotoXY(50, y); cout << "Date Of Birth";
	gotoXY(70, y); cout << "Social ID";
	gotoXY(85, y); cout << "Other Mark";
	gotoXY(97, y); cout << "Midterm Mark";
	gotoXY(110, y); cout << "Final Mark";
	y = 5;
	while (tmp1 != NULL) {
		gotoXY(0, y); cout << tmp1->studentInfo.studentID;
		gotoXY(13, y); cout << tmp1->studentInfo.lastName;
		gotoXY(30, y); cout << tmp1->studentInfo.firstName;
		gotoXY(40, y); cout << tmp1->studentInfo.gender;
		gotoXY(50, y); cout << tmp1->studentInfo.dateOfBirth.day << "/" << tmp1->studentInfo.dateOfBirth.month << "/" << tmp1->studentInfo.dateOfBirth.year;
		gotoXY(70, y); cout << tmp1->studentInfo.socialID;
		gotoXY(85, y); cout << tmp1->studentInfo.otherMark;
		gotoXY(97, y); cout << tmp1->studentInfo.midtermMark;
		gotoXY(110, y); cout << tmp1->studentInfo.finalMark;
		y++;
		tmp1 = tmp1->next;
	}
	cout << endl << endl << endl;
}
void ViewScoreboard(ListStudent* l, string listFileName[], int ans) {
	l = loadFileDataOfStudent(listFileName, ans);
	ScoreListstudentOfClass(l);

}
void AddStudent(ListStudent* l, string FileName[], int ans) {
	Student s = EnterStudent();
	addStudentIntoListStudent(l, s);
	saveDataOfListStudent2(FileName[ans], l);
	notifyBox("ADD STUDENT COMPLETELY!");
}
void removeStudentFollowID(ListStudent*& list, string ID) {
	NodeStudent* current = list->head;
	NodeStudent* prev = NULL;
	while (current != NULL) {
		if (current->studentInfo.studentID == ID) {
			NodeStudent* temp = current;
			if (prev == NULL) {
				//  node prev == NULL, nghĩa là current đang ở node đầu
				list->head = current->next;
				current = current->next;
			}
			else {
				prev->next = current->next;
				current = current->next;
			}
			delete temp;
		}
		else {
			// Cập nhật node prev đi theo node current
			prev = current;
			current = current->next;
		}
	}
}
Course EnterCourse() {
	Course course;
	string session;
	string id = course.id;
	hideCursor(false);
	gotoXY(55, 7); cout << "Change Course";
	gotoXY(45, 10); cout << "Course ID: ";
	gotoXY(45, 11); cout << "Course name:";
	gotoXY(45, 12); cout << "Teacher name: ";
	gotoXY(45, 13); cout << "Academic year: ";
	gotoXY(45, 14); cout << "Number of credits: ";
	gotoXY(45, 15); cout << "Nums of students: ";
	gotoXY(45, 16); cout << "Num of enrollers: ";
	gotoXY(45, 17); cout << "Weekday: ";
	gotoXY(45, 18); cout << "Session (S1,S2,S3,S4) (Format:XX-YY): ";

	gotoXY(56, 10); getline(cin, course.id);
	gotoXY(58, 11); getline(cin, course.courseName);
	gotoXY(59, 12); getline(cin, course.teacherName);
	gotoXY(60, 13); cin >> course.academicYear;
	gotoXY(64, 14); cin >> course.credits;
	gotoXY(64, 15); cin >> course.numOfStudents;
	cin.ignore();
	gotoXY(64, 16); cin >> course.NumofEroller;
	cin.ignore();
	gotoXY(54, 17); getline(cin, course.weekDay);
	Upper(course.weekDay);
	gotoXY(85, 18); getline(cin, session);
	Upper(session);
	course.session[0] = session.substr(session.find('S'), 2);
	session.erase(session.find('S'), 2);
	course.session[1] = session.substr(session.find('S'), 2);
	return course;
}
void AddCourseMenu(ListCourse &l) {
	vector<string> options = {"Input Course","Import Course From file CSV","Back"};
	int currentOption = 0;
	int onMenu3 = 0;
	char key;
	do {
		int k = 9;
		if (onMenu3 == 0) {
			printMenu(options, currentOption, k);
			textAlignCenter("STAFF MENU", 40, 40, 4);
			gotoXY(75, 5); cout << "Welcome ";
			gotoXY(75, 6); cout << currentUser->lastName << " " << currentUser->firstName;
			drawBox(40, 10, 40, 7);
			key = _getch(); // Nhận phím từ người dùng mà không cần nhấn Enter

			switch (key) {
			case 'w':
				if (currentOption > 0) {
					currentOption--;
				}
				break;
			case 's':
				if (currentOption < options.size() - 1) {
					currentOption++;
				}
				break;
			case 13: // Enter
				if (currentOption == 1) { // Chọn Option 2
					onMenu3 = 2; // Đặt biến onMenu thành false để chuyển đến trang mới
				}
				if (currentOption == 0) {//.Option 1
					onMenu3 = 1;
				}
				if (currentOption == 2) {//.current Option ma bang options.size()-1 thi la phan tu cuoi va chung la "Thoat".
					onMenu3 = 100;
					key = 'q';
				}
				break;
			default:
				break;
			}
		}
		else if (onMenu3 == 2) {//import
			system("cls");
			ReadFileGetList(l, "Data/Course/courses.csv");
			notifyBox("IMPORTED LIST COURSES COMPLETELY!");
			/*system("pause");*/
			onMenu3 = 0;
		}
		else if (onMenu3 == 1) {//Addcourse
			system("cls");
			Course course = EnterCourse();
			Course* p = ConvertFromCourseToPointer(course);
			AddCourse(l, p);
			appendNumberToCSV("Data/Course/courses.csv", p);
			notifyBox("ADD COURSE COMPLETELY!");
			onMenu3 = 0;//.Sau ham se la: onMenu3 = 0 de khi ta nhan 'q' de thoat khoi ham(trang) do thi no se dat onMenu3=0 de in ra lai trang MẸ
		}
		else if (onMenu3 == 100) {
			break;
		}
	} while (key != 'q');

}
void DispalyAfterChooseOneCourse(int ans, ListCourse& l, string path) {
	vector<string> options = { "View Detail","Change Course","Delete","List of student","Export to CSV ","Add Student","Import Scoreboard","View Scoreboard","Remove Student","Back" };
	string listFileName[5] = { "Data/StudentOfCourses/classOfCourse1.csv"};
	int currentOption = 0;
	int onMenu3 = 0;
	char key;
	do {
		int k = 9;
		if (onMenu3 == 0) {
			printMenu3(options, currentOption, k);
			textAlignCenter("CUSTOMIZED COURSES", 40, 40, 4);
			drawBox(40, 12, 40, 7);
			key = _getch(); // Nhận phím từ người dùng mà không cần nhấn Enter
			switch (key) {
			case 'w':
				if (currentOption > 0) {
					currentOption--;
				}
				break;
			case 's':
				if (currentOption < options.size() - 1) {
					currentOption++;
				}
				break;
			case 13: // Enter
				if (currentOption == 1) { // Chọn Option 2
					onMenu3 = 2; // Đặt biến onMenu thành false để chuyển đến trang mới
				}
				if (currentOption == 2) {
					onMenu3 = 3;
				}
				if (currentOption == 0) {//.Option 1
					onMenu3 = 1;
				}
				if (currentOption == 3) {
					onMenu3 = 4;
				}
				if (currentOption == 4) {
					onMenu3 = 5;
				}
				if (currentOption == 5) {
					onMenu3 = 6;
				}
				if (currentOption == 6) {
					onMenu3 = 7;
				}
				if (currentOption == 7) {
					onMenu3 = 8;
				}
				if (currentOption == 8) {
					onMenu3 = 9;
				}
				if (currentOption == 9) {
					onMenu3 = 100;
					key = 'q';
				}
				break;
			default:
				break;
			}
		}
		else if (onMenu3 == 1) {//.Detail
			system("cls");
			Detail(l, ans);
			system("pause");
			onMenu3 = 0;
		}
		else if (onMenu3 == 2) {//.Change Course
			system("cls");
			ChangeCourse(l, path, ans);
			notifyBox("COURSE UPDATED SUCCESSFULLY!");
			/*system("pause");*/
			onMenu3 = 0;
		}
		else if (onMenu3 == 3) {//.Option2->Delete
			system("cls");
			Course* p = ConvertToArr(l);
			DeleteCourse(l, p[ans], path);
			gotoXY(40, 15);
			notifyBox("DELETING SUCCESSFUL!");
			/*system("pause");*/
			onMenu3 = 0;
		}
		else if (onMenu3 == 4) {
			system("cls");
			ListStudent* list = loadFileDataOfStudent(listFileName, ans);
			PrintListstudentOfClass(list);
			/*string saveClass = listFileName[ans];
			saveDataOfListStudent(saveClass, list);*/
			system("pause");
			onMenu3 = 0;
		}
		else if (onMenu3 == 5) {//.Export to csv
			system("cls");
			ListStudent* list = loadFileDataOfStudent(listFileName, ans);
			ExportToCSV(list);
			onMenu3 = 0;
		}
		else if (onMenu3 == 6) {//.add student
			system("cls");
			ListStudent* l = loadFileDataOfStudent(listFileName, ans);
			AddStudent(l, listFileName, ans);
			onMenu3 = 0;
		}
		else if (onMenu3 == 7) {//.Import scoreboard
			system("cls");
			ListStudent* list = new ListStudent;
			ImportScoreboard(list, listFileName, ans);
			onMenu3 = 0;
		}
		else if (onMenu3 == 8) {//.View scoreboard
			system("cls");
			ListStudent* l = new ListStudent;
			ViewScoreboard(l, listFileName, ans);
			system("pause");
			onMenu3 = 0;
		}
		else if (onMenu3 == 9) {
			system("cls");
			cout << "Enter ID: ";
			string id;
			getline(cin, id);
			ListStudent* l = loadFileDataOfStudent(listFileName, ans);
			removeStudentFollowID(l, id);
			saveDataOfListStudent2(listFileName[ans], l);
			notifyBox("REMOVE COMPLETELY!");
			onMenu3 = 0;
		}
		else if (onMenu3 == 100) {//.Back
			break;
		}
	} while (key != 'q');

}

void ListCourseOptions(ListCourse& l, int& ans, string path) {//ans la de ta biet ta chon phan tu nao
	hideCursor(true);//Bat chuc nang an con tro nhap nhay tren man hinh
	int currentOption = 0;
	int onMenu3 = 0;
	char key;
	do {
		int k = 9;
		if (onMenu3 == 0) {
			Course* options = ConvertToArr(l);
			int size = CountCourse(l);
			printMenu1(options, size, currentOption);
			PrintTitle();
			key = _getch(); // Nhận phím từ người dùng mà không cần nhấn Enter
			switch (key) {
			case 'w':
				if (currentOption > 0) {
					currentOption--;
				}
				break;
			case 's':
				if (currentOption < size) {
					currentOption++;
				}
				break;
			case 13: // Enter
				if (currentOption == size) {//.current Option ma bang options.size()-1 thi la phan tu cuoi va chung la "Thoat".
					onMenu3 = 100;
					key = 'q';
				}
				else {
					onMenu3 = 1;
					ans = currentOption;
					//Chi co 1 trang duy nhat hien ra du chon op nao
				}
				break;
			default:
				break;
			}
		}
		else if (onMenu3 == 1) {
			system("cls");
			DispalyAfterChooseOneCourse(ans, l, path);
			/*system("pause");*/
			//.<Goi ham la trang khi ma chon vao 1 OPTION co onMenu3=1 (OPTION 1)>
			onMenu3 = 0;//.Sau ham se la: onMenu3 = 0 de khi ta nhan 'q' de thoat khoi ham(trang) do thi no se dat onMenu3=0 de in ra lai trang MẸ
		}
		else if (onMenu3 == 100) {
			break;
		}
	} while (key != 'q');
}
void CreateSemester(Semester& s) {
	cout << "Semester: ";
	cin >> s.semester;
	cout << "Start date: ";
	cout << endl << "Enter day: ";
	cin >> s.startDate.day;
	cout << endl << "Enter month: ";
	cin >> s.startDate.month;
	cout << endl << "Enter year: ";
	cin >> s.startDate.year;
	cout << "End date: ";
	cout << endl << "Enter day: ";
	cin >> s.endDate.day;
	cout << endl << "Enter month: ";
	cin >> s.endDate.month;
	cout << endl << "Enter year: ";
	cin >> s.endDate.year;

}
void SaveSemester(Semester s, string path) {
	ofstream fout(path);
	fout << s.semester << endl;
	fout << s.startDate.day << "/" << s.startDate.month << "/" << s.startDate.year << endl;
	fout << s.endDate.day << "/" << s.endDate.month << "/" << s.endDate.year;
	fout.close();
}
void ReadSemester(Semester&s, string path) {
	ifstream fin(path);
	fin >> s.semester;
	cin.ignore();
	fin >> s.startDate.day;
	fin.ignore();
	fin >> s.startDate.month;
	fin.ignore();
	fin >> s.startDate.year;
	fin.ignore();
	fin >> s.endDate.day;
	fin.ignore();
	fin >> s.endDate.month;
	fin.ignore();
	fin >> s.endDate.year;
	fin.close();
}
void CreateSemester1(Semester&s,string path,int check) {
	CreateSemester(s);
	SaveSemester(s, path);
	check++;
	notifyBox("CREATED SEMESTER COMPLETELY!");
}
void PrintSemester(Semester s) {
	int width = 40;
	int height = 7;
	int left = 40;
	int top = 8;
	int yPos = 10;
	gotoXY(57, yPos - 2); cout << "SEMESTER INFOMATION";
	gotoXY(48, yPos); cout << "Semester: " << s.semester;
	yPos++;
	gotoXY(48, yPos); cout << "Start Date: " << s.startDate.day << "/" << s.startDate.month << "/" << s.startDate.year;
	yPos++;
	gotoXY(48, yPos);  cout << "End Date: " << s.endDate.day << "/" << s.endDate.month << "/" << s.endDate.year;
	yPos++;
}
void CreateRegistration(Registration& s) {
	cout << "Start date: ";
	cout << endl << "Enter day: ";
	cin >> s.startDate.day;
	cout << endl << "Enter month: ";
	cin >> s.startDate.month;
	cout << endl << "Enter year: ";
	cin >> s.startDate.year;
	cout << "End date: ";
	cout << endl << "Enter day: ";
	cin >> s.endDate.day;
	cout << endl << "Enter month: ";
	cin >> s.endDate.month;
	cout << endl << "Enter year: ";
	cin >> s.endDate.year;

}
void SaveRegistration(Registration s, string path) {
	ofstream fout(path);
	fout << s.startDate.day << "/" << s.startDate.month << "/" << s.startDate.year << endl;
	fout << s.endDate.day << "/" << s.endDate.month << "/" << s.endDate.year;
	fout.close();
}
void ManageCourses() {
	vector<string> options = { "Create Semester","Create Registration Session","Add Courses ","List Courses", "Back" };
	int currentOption = 0;
	int onMenu3 = 0;
	string path = "Data/Course/courses.csv";
	string path1 = "Data/Semester/semester.txt";
	Semester s;
	Registration r;
	int ans = 0;
	char key;
	int check = 0;
	ListCourse l;
	l.pHead = NULL;
	do {
		int k = 9;
		if (onMenu3 == 0) {
			printMenu(options, currentOption, k);
			textAlignCenter("MANAGE COURSES", 40, 40, 4);
			drawBox(40, 10, 40, 7);
			key = _getch(); // Nhận phím từ người dùng mà không cần nhấn Enter
			switch (key) {
			case 'w':
				if (currentOption > 0) {
					currentOption--;
				}
				break;
			case 's':
				if (currentOption < options.size() - 1) {
					currentOption++;
				}
				break;
			case 13: // Enter
				if (currentOption == 1) { // Chọn Option 2
					onMenu3 = 2; // Đặt biến onMenu thành false để chuyển đến trang mới
				}
				if (currentOption == 0) {//.Option 1->Create Semester
					onMenu3 = 1;
				}
				if (currentOption == 2) {//.OP 3
					onMenu3 = 3;
				}
				if (currentOption == 3) {
					onMenu3 = 4;
				}
				if (currentOption == 4) {//.current Option ma bang options.size()-1 thi la phan tu cuoi va chung la "Thoat".
					onMenu3 = 100;
					key = 'q';
				}
				break;
			default:
				break;
			}
		}
		else if (onMenu3 == 3) {//.AddCourse
			system("cls");
			AddCourseMenu(l);
			onMenu3 = 0;
		}
		else if (onMenu3 == 1) {//Create Semester(check=0), Semester Infomation(check!=0)
			system("cls");
			if (check == 0) {
				CreateSemester1(s, path1, check);
				SaveSemester(s, "Data/Semester/semester.txt");
				check++;
				options[0] = "Semester Information";
			}
			else {
				PrintSemester(s);
				cout << endl << endl;
				system("pause");
			}
			onMenu3 = 0;
		}
		else if (onMenu3 == 2) {
			system("cls");
			CreateRegistration(r);
			SaveRegistration(r, "Data/Semester/RegistrationCourse.txt");
			notifyBox("CREATED REGISTRATION COURSE!");
			onMenu3 = 0;

		}
		else if (onMenu3 == 4) {
			if (l.pHead == NULL) {
				system("cls");
				notifyBox("LIST IS EMPTY!");
			}
			else {
				ListCourseOptions(l, ans, "Data/Course/courses.csv");
			}
			onMenu3 = 0;
		}
		else if (onMenu3 == 100) {
			break;
		}
	} while (key != 'q');

}
