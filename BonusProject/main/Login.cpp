#include "Struct.h"
#include "Console.h"
#include "User.h"
#include"Staff.h"
#include "Login.h"
#include "Student.h"
// Ham kiem tra xem tai khoan va mat khau dc nhap vao co ton tai trong List (List duoc tao bang cach doc tu file csv)
string id, password;
User* currentUser = NULL;
ListUser listUser;
Date currentDate;
string currentSchoolYear;
Semester currentSemester;
string semesterPath;
string schoolYearPath;
int yPos = 13;
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
	Date currDate = CurrentDate();
	drawBox(width, height, left, top);
	textAlignCenter("HCMUS PORTAL", left, width, 6);
	textAlignCenter("LOGIN", left, width, 7);
	gotoXY(40, 9); cout << dateToStr(currDate);
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
void StaffMenu() {
	Date currDate = CurrentDate();
	vector<string> options = { "User account","Profile","Manage Student","Manage Course","Exit" };
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
			gotoXY(40, 6); cout << dateToStr(currDate);
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
				if (currentOption == 4) {//.current Option ma bang options.size()-1 thi la phan tu cuoi va chung la "Thoat".
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
			Profile();
			system("pause");
			onMenu3 = 0;
		}
		else if (onMenu3 == 1) {
			system("cls");
			userAccount();
			onMenu3 = 0;//.Sau ham se la: onMenu3 = 0 de khi ta nhan 'q' de thoat khoi ham(trang) do thi no se dat onMenu3=0 de in ra lai trang MẸ
		}
		else if (onMenu3 == 4) {
			system("cls");
			ManageCourses();
			/*system("pause");*/
			onMenu3 = 0;
		}
		else if (onMenu3 == 100) {
			break;
		}
	} while (key != 'q');

}

