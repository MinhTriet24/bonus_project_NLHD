#include "Class.h"

void initList(ListClasses& list)
{
	//khoi tao danh sach lop hoc nhu binh thuong
	list.head = NULL;
	list.tail = NULL;
	list.size = 0;
}

void addClass(ListClasses& list, Class* course)
{

}

void saveClass(string path, ListStudent listStudent)
{
	ofstream fOut;
	fOut.open(path);
	if (!fOut.is_open()) return;

	fOut << "No,Student ID,Last name,First name,Gender,Date of Birth,Social ID,Academic year" << endl;
	Student* cur = listStudent.head;
	int no = 1;
	while (cur != NULL)
	{
		string dateOfBirth = to_string(cur->dateOfBirth.day) + "/" + to_string(cur->dateOfBirth.month) + "/" + to_string(cur->dateOfBirth.year);
		fOut << no << "," << cur->studentID << "," << cur->lastName << "," << cur->firstName << "," << cur->gender << "," << dateOfBirth << "," << cur->socialID << "," << cur->academicYear;
		no++;
		cur = cur->next;
		if (cur == NULL) cout << endl;
 	}
	fOut.close();
}

void getListClasses(string year)
{
	string pathFile = "";
	pathFile = "./data/" + currentSchoolYear + "/classes/" + year + "/";
	//initList(listClasses);

	string ext(".csv");
	for()
}
void viewListOfClasses();