#include "Staff.h"

void StaffMenu() {
	vector<string> options = { "User account","Profile","Manage Student","Manage Course","Setting","Exit" };
	int currentOption = 0;
	int onMenu3 = 0;
	char key;
	do {
		// k là tọa độ y
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
		else if (onMenu3 == 3) {
			ManageStudentMenu();
		}
		else if (onMenu3 == 4) {
			void ManageCourseMenu();
		}
		else if (onMenu3 == 5) {
			Setting();
		}
		else if (onMenu3 == 100) {
			break;
		}
	} while (key != 'q');

}

void ManageStudentMenu() {
	vector<string> options = { "School Year Information","Create class","List of classes","Exit"};
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

void ProfileStaff() {

}