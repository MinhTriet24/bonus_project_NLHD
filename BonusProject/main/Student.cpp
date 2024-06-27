#include"Console.h"
#include"Login.h"
#include"Staff.h"
#include"struct.h"
#include"Student.h"
#include"User.h"

void StudentMenu() {
	vector<string> options = { "User account","Profile","Scoreboard","List of courses","Exit" };
	int currentOption = 0;
	int onMenu3 = 0;
	char key;
	ListScoreBoard l;
	ListCourse hisCourse;
	textAlignCenter("STUDENT MENU", 40, 10, 5);
	do {
		int k = 9;
		if (onMenu3 == 0) {
			printMenu(options, currentOption, k);
			textAlignCenter("STUDENT MENU", 40, 40, 4);
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
				if (currentOption == 2) {//.OP 3
					onMenu3 = 3;
				}
				if (currentOption == 3) {
					onMenu3 = 4;
				}
				if (currentOption == 4) { // Option Exit
					//.current Option ma bang options.size()-1 thi la phan tu cuoi va chung la "Thoat".
					onMenu3 = 100;
					key = 'q';
				}
				break;
			default:
				break;
			}
		}
		else if (onMenu3 == 2) { //.Option2
			system("cls");
			Profile();
			system("pause");
			onMenu3 = 0;
		}
		else if (onMenu3 == 1) {
			system("cls");
			userAccount();
			onMenu3 = 0;
		}
		else if (onMenu3 == 3) {
			system("cls");
			findStudentIDInCourse(currentUser->id, l);
			DisplayScoreBoard(l);
			cout << endl;
			system("pause");
			onMenu3 = 0;
		}
		else if (onMenu3 == 4) {
			system("cls");
			findStudentIDInCourse2(currentUser->id, hisCourse);
			PrintListCourse(hisCourse);
			cout << endl;
			system("pause");
			onMenu3 = 0;
		}
		else if (onMenu3 == 100) {
			break;
		}
	} while (key != 'q');

}

NodeScoreBoard* makeNode(ScoreBoard sb) {
	NodeScoreBoard* newScoreBoard = new NodeScoreBoard;
	newScoreBoard->data = sb;
	newScoreBoard->next = NULL;
	return newScoreBoard;
}
void initListScoreBoard(ListScoreBoard& l) {
	l.head = l.tail = NULL;
}
void addScoreBoard(ListScoreBoard& l, ScoreBoard sb) {
	NodeScoreBoard* newScoreBoard = makeNode(sb);
	if (l.head == NULL && l.tail == NULL) {
		l.head = l.tail = newScoreBoard;
	}
	else {
		l.tail->next = newScoreBoard;
		l.tail = newScoreBoard;
	}
}
double avrMark(Student st) {
	return (st.otherMark * 0.2 + st.midtermMark * 0.3 + st.finalMark * 0.5);
}
void findStudentIDInCourse(string ID, ListScoreBoard& l) {
	string classOfCourse[11] = { "classOfCourse1", "classOfCourse2", "classOfCourse3", "classOfCourse4" , "classOfCourse5", "classOfCourse6" , "classOfCourse7" , "classOfCourse8" , "classOfCourse9" , "classOfCourse10" };
	ListCourse NameOfCourse;
	ReadFileGetList(NameOfCourse, "Data/Course/courses.csv");
	ifstream fIn;

	initListScoreBoard(l);

	Course* tmp = NameOfCourse.pHead;
	int i = 0;


	while (tmp != NULL) {
		string path = "Data/StudentOfCourses/" + classOfCourse[i] + ".csv";
		fIn.open(path);
		if (!fIn.is_open()) {
			break;
		}

		string tmpData;
		getline(fIn, tmpData, '\n');
		while (getline(fIn, tmpData)) {
			istringstream ss(tmpData);
			Student stTemp;
			Course* belongToHim;
			ScoreBoard newScoreBoard;
			string s, dateOfBirth;
			string otherScore, midScore, finalScore;

			getline(ss, s, ',');
			if (s == "") break;

			getline(ss, stTemp.studentID, ',');
			getline(ss, stTemp.lastName, ',');
			getline(ss, stTemp.firstName, ',');
			getline(ss, stTemp.gender, ',');
			getline(ss, dateOfBirth, ',');
			getline(ss, stTemp.socialID, ',');
			getline(ss, otherScore, ',');
			stTemp.otherMark = strToDouble(otherScore);
			getline(ss, midScore, ',');
			stTemp.midtermMark = strToDouble(midScore);
			getline(ss, finalScore, '\n');
			stTemp.finalMark = strToDouble(finalScore);

			if (stTemp.studentID == ID) {
				newScoreBoard.nameCourse = tmp->courseName;
				newScoreBoard.otherMark = stTemp.otherMark;
				newScoreBoard.midtermMark = stTemp.midtermMark;
				newScoreBoard.finalMark = stTemp.finalMark;
				newScoreBoard.avrMark = avrMark(stTemp);
				addScoreBoard(l, newScoreBoard);
				break;
			}
		}
		fIn.close();
		tmp = tmp->pNext;
		i++;
	}
}
void DisplayScoreBoard(ListScoreBoard l)
{
	int x = 16, y = 4;
	gotoXY(x, y);
	cout << "Course Name";
	x += 30;
	gotoXY(x, y);
	cout << "Other Mark";
	x += 15;
	gotoXY(x, y);
	cout << "Midterm Mark";
	x += 15;
	gotoXY(x, y);
	cout << "Final Mark";
	x += 15;
	gotoXY(x, y);
	cout << "Avr Mark";
	NodeScoreBoard* tmp1 = l.head;
	x = 16, y = y + 2;
	while (tmp1 != NULL) {
		gotoXY(x, y);
		cout << tmp1->data.nameCourse;
		x += 35;
		gotoXY(x, y);
		cout << tmp1->data.otherMark;
		x += 15;
		gotoXY(x, y);
		cout << tmp1->data.midtermMark;
		x += 15;
		gotoXY(x, y);
		cout << tmp1->data.finalMark;
		x += 13;
		gotoXY(x, y);
		cout << tmp1->data.avrMark;
		y++;
		x = 16;
		tmp1 = tmp1->next;
	}
}

void findStudentIDInCourse2(string ID, ListCourse& hisCourse) {
	string classOfCourse[11] = { "classOfCourse1", "classOfCourse2", "classOfCourse3", "classOfCourse4" , "classOfCourse5", "classOfCourse6" , "classOfCourse7" , "classOfCourse8" , "classOfCourse9" , "classOfCourse10" };
	ListCourse NameOfCourse;
	ReadFileGetList(NameOfCourse, "Data/Course/courses.csv");
	ifstream fIn;

	hisCourse.pHead = NULL;

	Course* tmp = NameOfCourse.pHead;
	int i = 0;


	while (tmp != NULL) {
		Course* set = tmp;
		string path = "Data/StudentOfCourses/" + classOfCourse[i] + ".csv";
		fIn.open(path);
		if (!fIn.is_open()) {
			tmp = tmp->pNext;
			i++;
			continue;
		}

		string tmpData;
		getline(fIn, tmpData, '\n');
		while (getline(fIn, tmpData)) {
			istringstream ss(tmpData);
			string s;
			Student stTemp;

			getline(ss, s, ',');
			if (s == "") break;

			getline(ss, stTemp.studentID, ',');

			if (stTemp.studentID == ID) {
				AddCourse(hisCourse, tmp);
				break;
			}
		}
		fIn.close();
		tmp = set;
		tmp = tmp->pNext;
		i++;
	}
}
