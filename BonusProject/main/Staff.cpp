
#include"Console.h"
#include"Login.h"
#include"SchoolYear.h"
#include"Staff.h"
#include"struct.h"
#include"Student.h"
#include"User.h"
using namespace std;
//Sau khi login thi ta da co currentUser ,viec bay h chi la xuat CurrentUser ra

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
			cout << "Mat khau moi la : " << currentUser->password;
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

// Option 3
void ManageStudentMenu() {
	vector<string> options = { "School Year Information","Create class","List of classes","Exit" };
	int currentOption = 0;
	int onMenu3 = 0;
	char key;
	do {
		int k = 9;
		if (onMenu3 == 0) {
			printMenu(options, currentOption, k);
			textAlignCenter("MANAGE STUDENT MENU", 40, 40, 4);
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
					// Nut back
					onMenu3 = 100;
					key = 'q';
				}
				break;
			default:
				break;
			}
		}
		else if (onMenu3 == 2) { //.Option2
			// Ham create class
		}
		else if (onMenu3 == 1) {
			system("cls");
			cout << "<Goi ham la trang khi ma chon vao 1 OPTION co onMenu3=1 (OPTION 1)>" << endl;
			system("pause");

			// Ham school year information
		}
		else if (onMenu3 == 100) {
			// T tính exit thì nó quay lại cái hàm staff menu nó chạy, mà thấy hơi kì. Ai sửa chỗ này đi nha
			StaffMenu();
			break;
		}
	} while (key != 'q');
}

// Option 5
void Setting() {
	vector<string> options = { "Change password", "Log out", "Exit" };
	int currentOption = 0;
	int onMenu = 0;
	char key;
	do {
		int k = 9;
		if (onMenu == 0) {
			printMenu(options, currentOption, k);
			textAlignCenter("SETTING", 40, 40, 4);
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
					onMenu = 2; // Đặt biến onMenu thành false để chuyển đến trang mới
				}
				if (currentOption == 0) {//.Option 1
					onMenu = 1;
				}
				if (currentOption == 2) {
					// Nut back
					onMenu = 100;
					key = 'q';
				}
				break;
			default:
				break;
			}
		}
		else if (onMenu == 2) { //.Option2
			logout();
			// Chua xong
			loginUI();
		}
		else if (onMenu == 1) {
			changePassword();
			onMenu = 0;
		}
		else if (onMenu == 100) {
			StaffMenu();
			break;
		}
	} while (key != 'q');
}

