#include"Console.h"
#include"Login.h"
#include"SchoolYear.h"
#include"Staff.h"
#include"struct.h"
#include"Student.h"
#include"User.h"

void StudentMenu() {
	vector<string> options = { "User account","Profile","Course Registration","Scoreboard","List of classes","List of courses","Setting","Exit" };
	int currentOption = 0;
	int onMenu3 = 0;
	char key;
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
				if (currentOption == 4) {
					onMenu3 = 5;
				}
				if (currentOption == 5) {
					onMenu3 = 6;
				}
				if (currentOption == 6) {
					onMenu3 = 7;
				}
				if (currentOption == 7) {//.current Option ma bang options.size()-1 thi la phan tu cuoi va chung la "Thoat".
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
			cout << "<Goi ham la trang khi ma chon vao 1 OPTION co onMenu3=1 (OPTION 1)>" << endl;
			system("pause");
			//.<Goi ham la trang khi ma chon vao 1 OPTION co onMenu3=1 (OPTION 1)>
			onMenu3 = 0;//.Sau ham se la: onMenu3 = 0 de khi ta nhan 'q' de thoat khoi ham(trang) do thi no se dat onMenu3=0 de in ra lai trang MẸ
		}
		else if (onMenu3 == 100) {
			break;
		}
		else if (onMenu3 == 3) {
			system("cls");
			// courseRegistationMenu();
			system("pause");
			onMenu3 = 0;
		}
		else if (onMenu3 == 4) {

		}
		else if (onMenu3 == 5) {

		}
		else if (onMenu3 == 6) {

		}
		else if (onMenu3 == 7) {

		}
	} while (key != 'q');

}

//void courseRegistationMenu(){
//	vector<string> options = { "Register Course","View Enrolled Courses" };
//	int currentOption = 0;
//	int onMenu3 = 0;
//	char key;
//	textAlignCenter("Course Registration", 40, 10, 5);
//	do {
//		int k = 9;
//		if (onMenu3 == 0) {
//			printMenu(options, currentOption, k);
//			textAlignCenter("Course Registration", 40, 40, 6);
//			drawBox(40, 10, 40, 7);
//			key = _getch(); // Nhận phím từ người dùng mà không cần nhấn Enter
//
//			switch (key) {
//			case 'w':
//				if (currentOption > 0) {
//					currentOption--;
//				}
//				break;
//			case 's':
//				if (currentOption < options.size() - 1) {
//					currentOption++;
//				}
//				break;
//			case 13: // Enter
//				if (currentOption == 1) { // Chọn Option 2
//					onMenu3 = 2; // Đặt biến onMenu thành false để chuyển đến trang mới
//				}
//				if (currentOption == 0) {//.Option 1
//					onMenu3 = 1;
//				}
//				if (currentOption == 2) {
//					//.current Option ma bang options.size()-1 thi la phan tu cuoi va chung la "Thoat".
//					onMenu3 = 100;
//					key = 'q';
//				}
//				break;
//			default:
//				break;
//			}
//		}
//		else if (onMenu3 == 1) {
//			system("cls");
//			cout << "Hiện lên danh sách môn để đăng ký" << endl;
//			system("pause");
//			onMenu3 = 0;
//		}
//		else if (onMenu3 == 2) {
//			system("cls");
//			cout << "Hiện lên danh sách lớp đã đăng ký" << endl;
//			system("pause");
//			onMenu3 = 0;
//		}
//		else if (onMenu3 == 100) {
//			break;
//		}
//	} while (key != 'q');
//
// 
//}

void InitListStudent(ListStudent*& list) {
	list = new ListStudent;
	list->head = list->tail = NULL;
	/*list->academicYear = 0;
	list->className = "";
	list->program = "";
	list->year = "";
	list->size = 0;*/
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

ListStudent* loadFileDataOfStudent(string currentClass)
{
	// Chỗ này là mình set đường dẫn
	string classPath = "D:/" + currentClass + ".csv";

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

void saveDataOfListStudent(string currentClass, ListStudent *list) {

	// Cho người dùng nhập tên lớp
	string classPath = "D:/" + currentClass + ".csv";

	ofstream fOut;
	fOut.open(classPath);
	if (!fOut.is_open()) {
		cout << "Can't open this file. " << endl;
		return;
	}

	fOut << "N0, Student ID, Last Name, First Name, Gender, Date of birth, Social ID, Other Mark, Midterm Mark, Final Mark" << endl;
	NodeStudent* curr = list->head;
	while (curr != NULL) {
		string dateOfBirth = to_string(curr->studentInfo.dateOfBirth.day) + "/" + to_string(curr->studentInfo.dateOfBirth.month) + "/" + to_string(curr->studentInfo.dateOfBirth.year);
		fOut << curr->studentInfo.studentID << "," << curr->studentInfo.lastName << "," << curr->studentInfo.firstName << ","
			<< curr->studentInfo.gender << "," << dateOfBirth << "," << curr->studentInfo.socialID << "," << curr->studentInfo.otherMark
			<< "," << curr->studentInfo.midtermMark << "," << curr->studentInfo.finalMark;
		curr = curr->next;
		if (curr != NULL) {
			fOut << endl;
		}
	
	}
	fOut.close();

}