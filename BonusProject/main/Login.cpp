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

User* login(string id, string password) //kiem tra xem co ton tai id va mat khau trong danh sach nguoi dung hay khong
{
	User* account = listUser.pHead; //khoi tao bien chay la node dau cua danh sach nguoi dung
	while(account!=NULL) //lap den het danh sach
		{
			if(id==account->id) //truong hop gap id cua nguoi dung trong danh sach trung voi id duoc nhap
			{
				if(password == account->password) return account;//neu trung mat khau thi tra va nguoi dung do
				else return NULL;// khong trung mat khau nghia la nguoi dung nhap sai vi id chi co 1, tra ve node null
			}
			account = account->pNext;//chuyen qua nguoi dung ke tiep trong danh sach
		}
	return NULL; //sau khi chay vong lap ma khong tim thay user trung voi tai khoan duoc nhap thi tra ve null
}

void loginUI()
{
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 10;

	drawBox(width,height, left,top); //ve khung cho giao dien dang nhap
	
}


