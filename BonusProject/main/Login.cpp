#include "Struct.h"
#include "Console.h"
#include "User.h"
#include"Staff.h"
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
// Ham kiem tra xem tai khoan va mat khau dc nhap vao co ton tai trong List (List duoc tao bang cach doc tu file csv)
User* login(string id, string password) {
	User* data = listUser.head;
	while (data != NULL) {
		if (id == data->id) {
			if (password == data->password) return data;
			else return NULL;
		}
		data = data->next;
	}
	return NULL;
}
string getPassword(bool isHidden) {
	string passwrd = "";
	while (true) {
		// In ra ký tự ô vuông sau HIDDEN nếu password đang bị che, kh in gì nếu password kh bị che
		gotoXY(79, yPos + 2);
		if (isHidden) cout << char(254);
		else cout << " ";
		// Đưa con trỏ về sau PASSWORD: 
		gotoXY(58 + passwrd.length(), yPos + 2);
		char ch = _getch();
		// Tạm dừng để nhập ký tự
		if (ch == 13) {
			// Ký tự enter. Nhập xong password. Trả về password luôn
			cout << endl;
			return passwrd;
		}
		else if (ch == 0) {
			ch = _getch();
			// Cái này hình như là mình nhấn F1 á
			if (ch == 59) {
				if (isHidden) {
					// Hiện password
					string temp = passwrd;
					while (temp.length() > 0) {
						cout << "\b \b";
						temp.pop_back();
						// Vòng while này để đưa con trỏ trở về lại vị trí đầu của password
					}
					cout << passwrd;
				}
				else {
					// Ẩn password
					string temp = passwrd;
					while (temp.length() > 0) {
						cout << "\b \b";
						temp.pop_back();
					}
					for (int i = 0; i < passwrd.length(); i++) {
						// Ẩn password bằng dấu *
						cout << '*';
					}
				}
				// Set lại giá trị biến bool
				isHidden = !isHidden;
			}
		}
		else if (ch == 8) {
			// Ký tự backspace -> xóa
			if (passwrd.length() > 0) {
				cout << "\b \b";
				// \b: dịch con trỏ lùi về 1 ký tự.
				// Đưa con trỏ lùi về 1 ký tự. Ghi đè dấu cách lên ký tự sau con trỏ. Rồi lại dịch con trỏ lùi về trước dấu cách
				//vd: Thanh -> Than_ -> Than
				passwrd.pop_back();
				// Hàm xóa 1 ký tự

			}
		}
		else if (passwrd.length() == 13) {
			// Vì khoảng cách từ lúc nhập đến từ HIDDEN là 14 nên password tối đa 13 ký tự
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
void loginUI() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 10;

	drawBox(width, height, left, top);
	textAlignCenter("HCMUS PORTAL", left, width, 6);
	textAlignCenter("LOGIN", left, width, 7);
	gotoXY(40, 8); cout << currentDate.wDay;
	gotoXY(40, 9); cout << dateToStr(currentDate);
	gotoXY(48, yPos);
	cout << "ID:";
	gotoXY(48, yPos + 2);
	cout << "PASSWORD:";
	gotoXY(72, yPos + 2);
	cout << " Hidden";
	cout << char(254);
	gotoXY(48, yPos + 3);
	cout << "(press F1 to show password)";
	gotoXY(55, yPos);
	getline(cin, id);
	password = getPassword(true);
	currentUser = login(id, password);
}

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
		cout << "New password: " << currentUser->password;
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

void userAccount() {//.OPTION 1
	gotoXY(55, 5); cout << "HCMUS Portal";
	const int width = 40;
	const int height = 7;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 10;
	vector<string> options = { "Change Password","Logout","Back" };
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



