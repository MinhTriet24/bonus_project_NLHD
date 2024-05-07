#include "Struct.h"
#include "Console.h"
#include "User.h"
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
ListCourses listCourses;
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
		gotoXY(79, yPos + 2);
		if (isHidden) cout << char(254);
		else cout << " ";
		gotoXY(58 + passwrd.length(), yPos + 2);
		char ch;
		ch = _getch();
		if (ch == 13) {
			cout << endl;
			return passwrd;
		}
		else if (ch == 0) {
			ch = _getch();
			if (ch == 59) {
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
						cout << "\b \b";
						temp.pop_back();
					}
					for (int i = 0; i < passwrd.length(); i++) {
						cout << '*';
					}
				}
				isHidden = !isHidden;
			}
		}
		else if (ch == 8) {
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
void SiteToLogin() {
    loginUI();
    vector<string> options = { "User account","Profile","Manage Student","Manage Course","Setting","Exit" };
    int currentOption = 0;
    int onMenu3 = 0;
    char key;
    do {
        if (onMenu3 == 0) {
            printMenu(options, currentOption,10);
            drawBox(40, 10, 30, 7);
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
                if (currentOption == 5) {//.current Option ma bang options.size()-1 thi la phan tu cuoi va chung la "Thoat".
                    onMenu3 = 100;
                    key = 'q';
                }
                break;
            default:
                break;
            }
        }
        else if (onMenu3 == 2) {//.Option2

        }
        else if (onMenu3 == 1) {
            system("cls");
            cout << "<Goi ham la trang khi ma chon vao 1 OPTION co onMenu3=1 (OPTION 1)>" << endl;
			system("pause");
            //.<Goi ham la trang khi ma chon vao 1 OPTION co onMenu3=1 (OPTION 1)>
            onMenu3 = 0;//.Sau ham se la: onMenu3 = 0 de khi ta nhan 'q' de thoat khoi ham(trang) do thi no se dat onMenu3=0 de in ra lai trang MẸ
        }
        else if (onMenu3 == 100) {
            break;
        }
    } while (key != 'q');

}
