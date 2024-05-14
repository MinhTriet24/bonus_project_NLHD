#include "Student.h"


void StudentMenu() {
	vector<string> options = { "User account","Profile","Course Registration","Scoreboard","List of classes","List of courses","Setting","Exit" };
	int currentOption = 0;
	int onMenu3 = 0;
	char key;
	textAlignCenter("STUDENT MENU", 40, 10, 5);
	do {
		// k là tọa độ y để in ra các option
		int k = 9;
		if (onMenu3 == 0) {
			// Hàm in option với option hiện tại được thay màu chữ
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
				if (currentOption == 1) { // Chọn Option 2. Mảng option tính từ chỉ số 0
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
		else if (onMenu3 == 3) {

		}
		//.Con tiep
	} while (key != 'q');

}


