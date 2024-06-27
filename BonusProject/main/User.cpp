#include "struct.h"
#include "Console.h"
#include "User.h"
#include "Login.h"
#include "Student.h"

const int yPos = 13;
void initList(ListUser& list) {
	list.head = NULL;
	list.tail = NULL;
	list.size = 0;
}
// Ham khoi tao 1 NODE users bang cach doc thong tin users tu file csv
User* convertUserData(ifstream& data) {//.Doc thong tin 1 sinh vien ( vs bien truyen vao la chi vi cua con tro doc file) va tra ve 1 con tro User*
	User* userData = new User;
	Date dateOfBirth;
	string temp;
	//.Bat dau doc thong tin sinh vien tu file vao
	getline(data, userData->id, ',');
	if (userData->id == "") return NULL;
	getline(data, userData->password, ',');
	getline(data, userData->lastName, ',');
	getline(data, userData->firstName, ',');
	getline(data, userData->className, ',');
	getline(data, userData->gender, ',');
	getline(data, temp, ',');
	userData->dateOfBirth = strToDate(temp);
	getline(data, temp, ',');
	userData->academicYear = stoi(temp);
	getline(data, temp, '\n');
	if (temp == "TRUE") userData->isStaff = true;
	else userData->isStaff = false;
	userData->next = NULL;
	userData->prev = NULL;
	return userData;
}
//.Them 1 NODE vao cuoi dslk.--> OK!
void addUser(ListUser& list, User* user) {
	if (user == NULL) return;
	if (list.head == NULL) {
		list.head = list.tail = user;
	}
	else {
		list.tail->next = user;
		user->prev = list.tail;
		list.tail = user;
	}
	list.size++;
}
const string useDataPath = "Data/Accounts/users.csv";
//.Doc toan bo thong tin cac sinh vien va luu thong tin vao 1 dslk listUser --> OK!
void getListUsers() {
	ifstream fin(useDataPath);
	string  data = "";//.cai nay hoi thua(k can thiet).-->co the bo cmnl!
	getline(fin, data);// data luc nay chua toan bo noi dung file csv (co ca ki tu (\n) la xuong dong)-->data luc nay la toan bo noi dung cua file csv.
	initList(listUser);
	while (!fin.eof()) {//. duyet toi cuoi file csv thi dung.
		addUser(listUser, convertUserData(fin));//.Them 1 Node=convertUserData(fin) vao cuoi listUser
	}
}
void saveListUser() {
	ofstream fout(useDataPath);
	fout << "ID,Password,Last name,First name,Class,Gender,Date of Birth,Academic year,Staff" << endl;
	User* curr = listUser.head;
	while (curr != NULL) {
		string dateOfBirth = to_string(curr->dateOfBirth.day) + "/" + to_string(curr->dateOfBirth.month) + "/" + to_string(curr->dateOfBirth.year);
		fout << curr->id << "," << curr->password << "," << curr->lastName << "," << curr->firstName
			<< "," << curr->className << "," << curr->gender << "," << dateOfBirth << "," << to_string(curr->academicYear) << ",";
		if (curr->isStaff) fout << "TRUE";
		else fout << "FALSE";
		curr = curr->next;
		if (curr != NULL) fout << endl;
	}
	fout.close();
}
