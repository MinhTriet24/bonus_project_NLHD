#include "Class.h"

//biến toàn cục của list classname
string ClassNamePath = "Data/ListClass/ListOfClasses.bin";
ListClassName* listClassName = NULL;

//biến toán cục của list classes
string operation = "classes";
string classLink;
ListClasses* listClasses = NULL;

//biến toàn cục để khởi tạo năm học mới
Date startDate;
Date endDate;
bool hasCreateSchoolYear = false;

//hàm lấy đường dẫn đến lớp học cần truy cập
void takeClassPath(string Class)
{
	classLink = "";
	classLink += "Data/ListClass";
	classLink = classLink + "/" + currentSchoolYear + "/" + operation + "/" + studentYear;
	classLink = classLink + "/" + Class + ".csv";
}

//code của phần danh sách lớp dùng để lưu trữ tên các lớp học
void InitListClassName(ListClassName*& list)
{
	list->pHead = NULL;
	list->pTail = NULL;
	list->numOfSchoolYear = 0;
}
void addClassNameIntoList(ListClassName*& list, className info)
{
	ncn n = new NodeClassName;
	n->info = info;
	n->pNext = NULL;

	if (list == NULL) return;
	if (list->pHead == NULL)
	{
		list->pHead = list->pTail = n;
		list->numOfSchoolYear++;
	}
	else
	{
		list->pTail->pNext = n;
		list->pTail = n;
		list->numOfSchoolYear++;
	}
}
void loadDataFromFileToList()
{
	ifstream fIn;
	fIn.open(ClassNamePath, ios::binary);
	if (!fIn.is_open())
	{
		cout << "Khong the mo file" << endl;
		return;
	}
	else
	{
		fIn.seekg(0, ios::beg);
		listClassName = new ListClassName[5];
		InitListClassName(listClassName);
		className tmpClassName;
		while (!fIn.eof())
		{
			int schoolYearLength = 0;
			fIn.read((char*)&schoolYearLength, sizeof(int));
			tmpClassName.schoolYear.resize(schoolYearLength);
			fIn.read(&tmpClassName.schoolYear[0], schoolYearLength);
			if (tmpClassName.schoolYear == "") break;

			int vecSz = 0;
			fIn.read((char*)(&vecSz), sizeof(int));
			tmpClassName.classesInTheSchoolYear.resize(vecSz);
			for (int i = 0; i < vecSz; i++)
			{
				int classNameLen = 0;
				fIn.read((char*)(&classNameLen), sizeof(int));
				tmpClassName.classesInTheSchoolYear[i].resize(classNameLen);
				fIn.read(&tmpClassName.classesInTheSchoolYear[i][0], classNameLen);
			}
			addClassNameIntoList(listClassName, tmpClassName);
		}

		fIn.close();
	}
}
void saveDataFromListToFile()
{
	ofstream fOut;
	fOut.open(ClassNamePath, ios::binary);
	if (!fOut.is_open())
	{
		cout << "Cant open this file" << endl;
		system("pause");
		return;
	}
	else
	{
		fOut.seekp(0, ios::beg);
		ncn tmp = listClassName->pHead;
		while (tmp != NULL)
		{
			int schoolYearLen = tmp->info.schoolYear.length();
			fOut.write((char*)(&schoolYearLen), sizeof(int));
			fOut.write(tmp->info.schoolYear.data(), schoolYearLen);

			int vecSz = tmp->info.classesInTheSchoolYear.size();
			fOut.write((char*)&(vecSz), sizeof(int));
			for (int i = 0; i < vecSz; i++)
			{
				int classNameLen = tmp->info.classesInTheSchoolYear[i].length();
				fOut.write((char*)(&classNameLen), sizeof(int));
				fOut.write(tmp->info.classesInTheSchoolYear[i].data(), classNameLen);
			}
			tmp = tmp->pNext;
		}
		fOut.close();
	}
}
void sortClassNameInList(ListClassName*& list)
{
	if (list == NULL || list->pHead == NULL) return;
	ncn nodeClassName = list->pHead;
	while (nodeClassName != NULL)
	{
		int posSecondYear = 0;
		for (int i = 0; i < nodeClassName->info.classesInTheSchoolYear.size(); i++)
		{
			if (nodeClassName->info.classesInTheSchoolYear[i] == "secondYear")
			{
				posSecondYear = i;
				break;
			}
		}

		for (int i = 1; i < posSecondYear - 1; i++)
		{
			for (int j = i + 1; j < posSecondYear; j++)
			{
				if (nodeClassName->info.classesInTheSchoolYear[i] > nodeClassName->info.classesInTheSchoolYear[j])
				{
					string temp = nodeClassName->info.classesInTheSchoolYear[i];
					nodeClassName->info.classesInTheSchoolYear[i] = nodeClassName->info.classesInTheSchoolYear[j];
					nodeClassName->info.classesInTheSchoolYear[j] = temp;
				}
			}
		}

		nodeClassName = nodeClassName->pNext;
	}
}
void deleteClassNameList(ListClassName*& list)
{
	if (list == NULL || list->pHead == NULL)
	{
		return;
	}
	while (list->pHead != NULL)
	{
		ncn tmp = list->pHead;
		list->pHead = tmp->pNext;
		delete tmp;
	}
}


//phần code của danh sách các lớp học chính (có lưu trữ danh sách học sinh)
//Xu li tung lop hoc rieng le
void InitListClassInSchoolYear(ListClassInSchoolYear*& list)
{
	list->pHead = NULL;
	list->pTail = NULL;
	list->numClassInSchoolYear = 0;
}
void addClassToListClassInSchoolYear(ListClassInSchoolYear*& list, Class info)
{
	if (list == NULL) return;
	ndeClass* tmp = new ndeClass;
	tmp->classInfo = info;
	tmp->pNext = NULL;

	if (list->pHead == NULL)
	{
		list->pHead = list->pTail = tmp;
		list->numClassInSchoolYear++;
	}
	else
	{
		list->pTail->pNext = tmp;
		list->pTail = tmp;
		list->numClassInSchoolYear++;
	}
}
//Xu li cac thao tac lien quan den cac lop hoc trong nam hoc
void InitListClasses(ListClasses*& list)
{
	list->pHead = NULL;
	list->pTail = NULL;
	list->numOfClasses = 0;
}
void addClassesIntoListClasses(ListClasses*& list, Classes dta)
{
	nc tmp = new NodeClasses;
	tmp->classesInfo = dta;
	tmp->pNext = NULL;

	if (list == NULL) return;
	if (list->pHead == NULL)
	{
		list->pHead = list->pTail = tmp;
		list->numOfClasses++;
	}
	else
	{
		list->pTail->pNext = tmp;
		list->pTail = tmp;
		list->numOfClasses++;
	}
}
void deleteListClasses(ListClasses*& list)
{
	if (list == NULL || list->pHead == NULL)
	{
		return;
	}
	while (list->pHead != NULL)
	{
		nc tmp = list->pHead;
		list->pHead = tmp->pNext;
		delete tmp;
	}
}
void LoadAllDataOfClassIntoListClasses()
{
	loadDataFromFileToList();
	int numOfSchoolYear = listClassName->numOfSchoolYear;
	listClasses = new ListClasses[numOfSchoolYear];
	InitListClasses(listClasses);

	ncn nodeClassName = listClassName->pHead;
	while (nodeClassName != NULL)
	{
		Classes classes;
		classes.schoolYear = nodeClassName->info.schoolYear;
		currentSchoolYear = classes.schoolYear;

		string studentYearClass = "";
		vector<string> tmpVector = nodeClassName->info.classesInTheSchoolYear;
		classes.listClassInSy = new ListClassInSchoolYear[tmpVector.size() - 4];
		InitListClassInSchoolYear(classes.listClassInSy);

		for (int i = 0; i < tmpVector.size(); i++)
		{
			if (tmpVector[i] == "firstYear" || tmpVector[i] == "secondYear" || tmpVector[i] == "thirdYear" || tmpVector[i] == "finalYear")
			{
				studentYearClass = tmpVector[i];
				studentYear = tmpVector[i];
				continue;
			}
			Class classData;
			classData.className = tmpVector[i];
			classData.studentYear = studentYearClass;

			classData.StudentsOfClass = loadFileDataOfStudent(tmpVector[i]);
			addClassToListClassInSchoolYear(classes.listClassInSy, classData);
		}
		addClassesIntoListClasses(listClasses, classes);
		nodeClassName = nodeClassName->pNext;
	}

}
void sortListClassNameInClassesList()
{
	nc nodeClassesCur = listClasses->pHead;
	while (nodeClassesCur != NULL)
	{
		for (ndeClass* i = nodeClassesCur->classesInfo.listClassInSy->pHead; i->pNext != NULL; i = i->pNext)
		{
			for (ndeClass* j = i->pNext; j != NULL; j = j->pNext)
			{
				if (i->classInfo.studentYear == j->classInfo.studentYear)
				{
					if (i->classInfo.className > j->classInfo.className)
					{
						Class tmp = i->classInfo;
						i->classInfo = j->classInfo;
						j->classInfo = tmp;
					}
				}
			}
		}
		nodeClassesCur = nodeClassesCur->pNext;
	}
}
ndeClass* createdNewClassWithKeyBoard(string className, int numOfStudents)
{
	//Lop duoc tao se danh cho nam nhat nen khong can them danh sach sinh vien nam 2
	ndeClass* newNode = new ndeClass;
	newNode->classInfo.studentYear = "firstYear";
	newNode->classInfo.className = className;
	newNode->classInfo.StudentsOfClass = createdListStudentWithDataFromKeyBoard(className, numOfStudents);

	newNode->pNext = NULL;

	return newNode;
}
ndeClass* createdNewClassWithFileData(string pathFile, string className)
{
	ndeClass* newNode = new ndeClass;
	newNode->classInfo.studentYear = "firstYear";
	newNode->classInfo.className = className;
	newNode->classInfo.StudentsOfClass = readFileStudentFromPathToAddIntoClass(pathFile);

	newNode->pNext = NULL;

	return newNode;
}

//phần giao diện
int command(int& curPos, int minPos, int maxPos, function<int(int)> option) {
	int key = _getch();
	switch (key) {
	case 13:
		return option(curPos);
	case 'w':
		if (curPos > minPos) curPos--;
		else {
			curPos = maxPos;
		}
		break;
	case 's':
		if (curPos < maxPos) curPos++;
		else {
			curPos = minPos;
		}
		break;
	}
	return 1;
}
int manageStudentOption(int curPos) {
	switch (curPos) {
	case 0:
		system("cls");
		if (hasCreateSchoolYear)
		{
			schoolYearInfomationUI();
		}
		else
		{
			CreateSchoolYearUI();
		}
		break;
	case 1:
		CreatedNewClassUI();
		sortClassNameInList(listClassName);
		break;
	case 2:
		viewListStudentYearUI();
		break;
	case 3:
		saveDataFromListToFile();
		return 0;
		break;
	}
	return 1;
}
void manageStudentMainUI()
{
	LoadAllDataOfClassIntoListClasses();
	const int width = 40;
	const int height = 11;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 11;

	hideCursor(true);

	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "Manage Student";
		if (hasCreateSchoolYear == false)
		{
			gotoXY(53, yPos); cout << "Create School Year";
			yPos++;
		}
		else
		{
			gotoXY(53, yPos); cout << "School Year Infortion";
			yPos++;
		}
		gotoXY(53, yPos); cout << "Create Classes";
		yPos++;
		gotoXY(53, yPos); cout << "List Of Classes";
		yPos++;
		yPos++;
		gotoXY(58, yPos); cout << "Back";
		yPos = 11;
		if (curPos == 3) yPos++;
		gotoXY(49, curPos + yPos); cout << cursorLeft;
		gotoXY(75, curPos + yPos); cout << cursorRight;
		yPos = 11;
	} while (command(curPos, 0, 3, manageStudentOption));
}
//xem danh sách học sinh trong lớp học
int chooseStudentYear(int curPos)
{
	string currentStudentYear;
	switch (curPos) {
	case 0:
		currentStudentYear = "firstYear";
		break;
	case 1:
		currentStudentYear = "secondYear";
		break;
	case 2:
		currentStudentYear = "thirdYear";
		break;
	case 3:
		currentStudentYear = "finalYear";
		break;
	case 4:
		return 0;
		break;
	}

	viewListOfClassUI(currentStudentYear);

	return 1;
}
void viewListStudentYearUI()
{
	const int width = 40;
	const int height = 11;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;

	hideCursor(true);

	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "Manage Student";
		gotoXY(52, yPos); cout << "First Year Student";
		yPos++;
		gotoXY(52, yPos); cout << "Second Year Student";
		yPos++;
		gotoXY(52, yPos); cout << "Third Year Student";
		yPos++;
		gotoXY(52, yPos); cout << "Final Year Student";
		yPos++;
		yPos++;
		gotoXY(58, yPos); cout << "Back";
		yPos = 10;
		if (curPos == 4) yPos++;
		gotoXY(50, curPos + yPos); cout << cursorLeft;
		gotoXY(72, curPos + yPos); cout << cursorRight;
		yPos = 10;
	} while (command(curPos, 0, 4, chooseStudentYear));
}
void viewListOfClassUI(string currentStudentYear)
{
	const int width = 40;
	const int height = 11;
	const int left = 40;
	const int top = 8;

	system("cls");
	nc nodeClasses = listClasses->pHead;
	while (nodeClasses != NULL)
	{
		if (nodeClasses->classesInfo.schoolYear == currentSchoolYear)
		{
			break;
		}
		nodeClasses = nodeClasses->pNext;
	}

	ndeClass* ndeStart = new ndeClass;
	ndeStart = NULL;
	ndeClass* ndeEnd = new ndeClass;
	ndeEnd = NULL;
	int numClass = 0;

	if (nodeClasses == NULL) return;
	ndeClass* nodeClass = nodeClasses->classesInfo.listClassInSy->pHead;
	while (nodeClass != NULL)
	{
		if (nodeClass->classInfo.studentYear == currentStudentYear)
		{
			numClass++;
			if (numClass == 1)
			{
				ndeStart = nodeClass;
			}
			ndeEnd = nodeClass;
		}
		nodeClass = nodeClass->pNext;
	}

	if (ndeStart == NULL)
	{
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "List class";
		gotoXY(55, 14); cout << "Empty list..";
		int key = _getch();
		system("cls");
		return;
	}

	int curClass = 0;

	vector<ndeClass*> posOfFirstClassArray;
	ndeClass* tmp = ndeStart;

	int i = 1;
	while (tmp != ndeEnd->pNext)
	{
		if (i == 1)
		{
			posOfFirstClassArray.push_back(tmp);
		}
		if (i == 6)
		{
			i = 1;
			continue;
		}
		tmp = tmp->pNext;
		i++;
	}
	posOfFirstClassArray.push_back(ndeEnd->pNext);

	int startPos = 0;
	int endPos = 1;
	int numPage = 0;

	//hien thi cho nguoi dung
	int curPos = 0;
	int yPos = 10;

	do
	{
		curClass = 0;

		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "List class";

		for (ndeClass* i = posOfFirstClassArray[startPos]; i != posOfFirstClassArray[endPos]; i = i->pNext)
		{
			gotoXY(58, yPos); cout << i->classInfo.className;
			yPos++; curClass++;
		}
		yPos++;
		gotoXY(57, 16); cout << cursorRight;
		gotoXY(59, 16); cout << "Back" << endl;
		gotoXY(64, 16); cout << cursorLeft;
		yPos = 10;
		if (curPos == curClass) yPos = 16 - curClass;
		gotoXY(55, curPos + yPos); cout << cursorLeft;
		gotoXY(66, curPos + yPos); cout << cursorRight;
		yPos = 10;

	} while (commandForClass(curPos, 0, curClass, posOfFirstClassArray, startPos, endPos, numPage, chooseClass));
}
int commandForClass(int& curPos, int minPos, int maxPos, vector<ndeClass*> posArray, int& startPos, int& endPos, int& numPage, function<int(int, vector<ndeClass*>, int, int, int)> option)
{
	int key = _getch();
	switch (key) {
	case 13:
		return option(curPos, posArray, startPos, endPos, numPage);
	case 'w':
		if (curPos > minPos) curPos--;
		else {
			curPos = maxPos;
		}
		break;
	case 's':
		if (curPos < maxPos) curPos++;
		else {
			curPos = minPos;
		}
		break;
	case 'a':
		if (startPos == 0)
		{
			system("cls");
			break;
		}
		else
		{
			curPos = 0;
			system("cls");
			numPage--;
			startPos--;
			endPos--;
			break;
		}
	case 'd':
		if (startPos == posArray.size() - 2)
		{
			system("cls");
			break;
		}
		else
		{
			curPos = 0;
			startPos++;
			endPos++;
			numPage++;
			system("cls");
			break;
		}
	default:
		break;
	}
	return 1;
}
int chooseClass(int curPos, vector<ndeClass*> posArray, int startPos, int endPos, int numPage)
{
	startPos = 0;
	string currentStudentYear = posArray[startPos]->classInfo.studentYear;
	ndeClass* curNdeClass = posArray[startPos];
	int cnt = 0;
	int index = 5 * numPage + curPos;
	bool has = false;
	while (curNdeClass != NULL && curNdeClass->classInfo.studentYear == currentStudentYear)
	{
		if (cnt == index && curPos < 5)
		{
			has = true;
			system("cls");
			viewStudentInClassUI(curNdeClass);
			break;
		}
		else
		{
			cnt++;
			curNdeClass = curNdeClass->pNext;
		}
	}
	if (!has)
	{
		system("cls");
		return 0;
	}
	return 1;
}
void viewStudentInClassUI(ndeClass* nodeClassCur)
{
	int no = 1;
	int yPos = 2;
	int xPos = 17;

	system("cls");
	vector<NodeStudent*> posOfFirstStudentArray;
	NodeStudent* tmp = nodeClassCur->classInfo.StudentsOfClass->head;
	int i = 1;
	while (tmp != NULL)
	{
		if (i == 1)
		{
			posOfFirstStudentArray.push_back(tmp);
		}
		if (i == 21)
		{
			i = 1;
			continue;
		}
		tmp = tmp->next;
		i++;
	}
	posOfFirstStudentArray.push_back(NULL);

	int startPos = 0, endPos = 1;
	bool isUsed = true;
	int numFirstStuInLastPage = 0, numLastStudentInLastPage = 0;
	while (isUsed)
	{
		yPos = 2;
		xPos = 17;

		gotoXY(55, yPos); cout << "CLASS " << nodeClassCur->classInfo.className;
		yPos += 2;

		gotoXY(xPos, yPos); cout << "No |";
		gotoXY(xPos + 5, yPos); cout << "Student ID   |";
		gotoXY(xPos + 20, yPos); cout << "Last Name         |";
		gotoXY(xPos + 40, yPos); cout << "First Name   |";
		gotoXY(xPos + 55, yPos); cout << "Gender  |";
		gotoXY(xPos + 65, yPos); cout << "Date of Birth |";
		gotoXY(xPos + 81, yPos); cout << "Social ID";
		yPos++;
		NodeStudent* start = posOfFirstStudentArray[startPos];
		NodeStudent* end = posOfFirstStudentArray[endPos];


		if (startPos == posOfFirstStudentArray.size() - 2)
		{
			numFirstStuInLastPage = no;
		}

		for (NodeStudent* j = start; j != end; j = j->next)
		{
			gotoXY(xPos, yPos); cout << no; no++;
			gotoXY(xPos + 5, yPos); cout << j->studentInfo.studentID;
			gotoXY(xPos + 20, yPos); cout << j->studentInfo.lastName;
			gotoXY(xPos + 40, yPos); cout << j->studentInfo.firstName;
			gotoXY(xPos + 55, yPos); cout << j->studentInfo.gender;
			gotoXY(xPos + 65, yPos); cout << j->studentInfo.dateOfBirth.day << "/" << j->studentInfo.dateOfBirth.month << "/" << j->studentInfo.dateOfBirth.year;
			gotoXY(xPos + 81, yPos); cout << j->studentInfo.socialID;
			yPos++;
		}

		if (startPos == posOfFirstStudentArray.size() - 2)
		{
			numLastStudentInLastPage = no - 1;
		}

		gotoXY(57, yPos); cout << cursorRight;
		gotoXY(59, yPos); cout << "Back";
		gotoXY(64, yPos); cout << cursorLeft;
		gotoXY(xPos + 85, yPos); cout << "page " << startPos + 1;

		int key = _getch();
		switch (key) {
		case 'a':
			if (startPos == 0)
			{
				no = no - 20;
				system("cls");
				continue;
			}
			else
			{
				if (startPos == posOfFirstStudentArray.size() - 2)
				{
					no = no - (numLastStudentInLastPage - numFirstStuInLastPage + 2) - 19;
				}
				else
				{
					no -= 40;
				}
				startPos--;
				endPos--;
				system("cls");
				continue;
			}
			break;
		case 'd':
			if (startPos == posOfFirstStudentArray.size() - 2)
			{
				no = no - (numLastStudentInLastPage - numFirstStuInLastPage + 1);
				system("cls");
				continue;
			}
			else
			{
				startPos++;
				endPos++;
				system("cls");
				continue;
			}
			break;
		default:
			isUsed = false;
			break;
		}
	}
}
int chooseOperationToAddClass(int curPos)
{
	switch (curPos) {
	case 0:
		system("cls");
		InputClassUI();
		break;
	case 1:
		system("cls");
		ImportClassDataUI();
		break;
	case 2:
		return 0;
		break;
	}
	return 1;
}
void CreatedNewClassUI()
{
	const int width = 40;
	const int height = 11;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 12;

	hideCursor(true);

	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "Create Classes";
		gotoXY(50, yPos); cout << "Input class data";
		yPos++;
		gotoXY(50, yPos); cout << "Import class data file";
		yPos++;
		yPos++;
		gotoXY(59, yPos); cout << "Back";
		yPos = 12;
		if (curPos == 2) yPos++;
		gotoXY(48, curPos + yPos); cout << cursorLeft;
		gotoXY(75, curPos + yPos); cout << cursorRight;
		yPos = 12;
	} while (command(curPos, 0, 2, chooseOperationToAddClass));
}
void InputClassUI()
{
	string className;
	int numOfStudents;
	int no = 1;
	int yPos = 2;
	int xPos = 17;

	gotoXY(50, yPos); cout << "Input class name: "; getline(cin, className);
	gotoXY(48, yPos + 2); cout << "Input number students in class: "; cin >> numOfStudents;
	cin.ignore();

	ndeClass* newNode = createdNewClassWithKeyBoard(className, numOfStudents);

	//luu vao data base
	studentYear = "firstYear";
	takeClassPath(className);
	writeFileStudentFromNewClassIntoDatabase(newNode->classInfo.StudentsOfClass, className);

	nc nodeClassesCur = listClasses->pHead;
	while (nodeClassesCur != NULL)
	{
		if (nodeClassesCur->classesInfo.schoolYear == currentSchoolYear)
		{
			break;
		}
		nodeClassesCur = nodeClassesCur->pNext;
	}

	if (nodeClassesCur == NULL) return;
	ndeClass* nodeClassCur = nodeClassesCur->classesInfo.listClassInSy->pHead;
	while (nodeClassCur->pNext != NULL)
	{
		if (nodeClassCur->pNext->classInfo.studentYear == "secondYear")
		{
			break;
		}
		nodeClassCur = nodeClassCur->pNext;
	}

	if (nodeClassCur->pNext == NULL) return;
	newNode->pNext = nodeClassCur->pNext;
	nodeClassCur->pNext = newNode;

	sortListClassNameInClassesList();

	//luu cac lop hien tai vao list class name
	ncn nodeClassNameCur = listClassName->pHead;
	while (nodeClassNameCur != NULL)
	{
		if (nodeClassNameCur->info.schoolYear == currentSchoolYear)
		{
			break;
		}
		nodeClassNameCur = nodeClassNameCur->pNext;
	}

	int pos = 0;
	if (nodeClassNameCur == NULL) return;
	for (int i = 0; i < nodeClassNameCur->info.classesInTheSchoolYear.size() - 1; i++)
	{
		if (nodeClassNameCur->info.classesInTheSchoolYear[i + 1] == "secondYear")
		{
			pos = i + 1;
			break;
		}
	}
	nodeClassNameCur->info.classesInTheSchoolYear.insert(nodeClassNameCur->info.classesInTheSchoolYear.begin() + pos, className);

	system("cls");
}
void ImportClassDataUI()
{
	ndeClass* newNode = new ndeClass;

	string className, path;
	int yPos = 10;
	int xPos = 16;

	const int width = 40;
	const int height = 11;
	const int left = 40;
	const int top = 8;

	int academicYear;
	gotoXY(50, yPos); cout << "Input class name: "; getline(cin, className);
	gotoXY(50, yPos + 2); cout << "Input academic year: "; cin >> academicYear;
	cin.ignore();
	do
	{
		gotoXY(50, yPos + 4); cout << "Input path file: "; getline(cin, path);
		newNode = createdNewClassWithFileData(path, className);
	} while (newNode->classInfo.StudentsOfClass == NULL);


	//luu vao data base
	studentYear = "firstYear";
	takeClassPath(className);
	writeFileStudentFromNewClassIntoDatabase(newNode->classInfo.StudentsOfClass, className);

	nc nodeClassesCur = listClasses->pHead;
	while (nodeClassesCur != NULL)
	{
		if (nodeClassesCur->classesInfo.schoolYear == currentSchoolYear)
		{
			break;
		}
		nodeClassesCur = nodeClassesCur->pNext;
	}

	if (nodeClassesCur == NULL) return;
	ndeClass* nodeClassCur = nodeClassesCur->classesInfo.listClassInSy->pHead;
	while (nodeClassCur->pNext != NULL)
	{
		if (nodeClassCur->pNext->classInfo.studentYear == "secondYear")
		{
			break;
		}
		nodeClassCur = nodeClassCur->pNext;
	}

	if (nodeClassCur->pNext == NULL) return;
	newNode->pNext = nodeClassCur->pNext;
	nodeClassCur->pNext = newNode;

	sortListClassNameInClassesList();

	//luu cac lop hien tai vao list class name
	ncn nodeClassNameCur = listClassName->pHead;
	while (nodeClassNameCur != NULL)
	{
		if (nodeClassNameCur->info.schoolYear == currentSchoolYear)
		{
			break;
		}
		nodeClassNameCur = nodeClassNameCur->pNext;
	}

	int pos = 0;
	if (nodeClassNameCur == NULL) return;
	for (int i = 0; i < nodeClassNameCur->info.classesInTheSchoolYear.size() - 1; i++)
	{
		if (nodeClassNameCur->info.classesInTheSchoolYear[i + 1] == "secondYear")
		{
			pos = i + 1;
			break;
		}
	}
	nodeClassNameCur->info.classesInTheSchoolYear.insert(nodeClassNameCur->info.classesInTheSchoolYear.begin() + pos, className);

	system("cls");
}
void schoolYearInfomationUI()
{
	const int width = 40;
	const int height = 11;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 11;

	hideCursor(true);
	bool isUsed = true;
	system("cls");

	while (isUsed)
	{
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(50, 7); cout << "School year infomation";
		gotoXY(50, yPos); cout << "School year: ";
		gotoXY(63, yPos); cout << currentSchoolYear;
		yPos += 2;
		string sDate = dateToStr(startDate);
		gotoXY(50, yPos); cout << "Start date: "; cout << sDate;
		yPos += 2;
		string eDate = dateToStr(endDate);
		gotoXY(50, yPos); cout << "End date: "; cout << eDate;
		yPos += 2;
		gotoXY(49, yPos + 10); cout << "Press any key to go back... ";
		yPos = 11;

		int key = _getch();
		if (key)
		{
			isUsed = false;
			continue;
		}
	}
}
void CreateSchoolYear()
{
	schoolYearPath = "";
	schoolYearPath = "Data/ListClass/" + currentSchoolYear;

	wstring wp = strToWstr(schoolYearPath);
	LPCWSTR path = wp.c_str();

	//tao folder nam hoc moi va cac folder phu
	CreateDirectoryW(path, NULL);
	string operationPath = schoolYearPath + "/classes";
	wstring wpop = strToWstr(operationPath);
	LPCWSTR opePath = wpop.c_str();
	CreateDirectoryW(opePath, NULL);
	string firstYearFolder, secondYearFolder, thirdYearFolder, finalYearFolder;
	firstYearFolder = operationPath + "/firstYear";
	secondYearFolder = operationPath + "/secondYear";
	thirdYearFolder = operationPath + "/thirdYear";
	finalYearFolder = operationPath + "/finalYear";
	wstring wpfy = strToWstr(firstYearFolder);
	wstring wpsy = strToWstr(secondYearFolder);
	wstring wpty = strToWstr(thirdYearFolder);
	wstring wpfny = strToWstr(finalYearFolder);
	LPCWSTR fyPath = wpfy.c_str();
	LPCWSTR syPath = wpsy.c_str();
	LPCWSTR tyPath = wpty.c_str();
	LPCWSTR fnPath = wpfny.c_str();
	CreateDirectoryW(fyPath, NULL);
	CreateDirectoryW(syPath, NULL);
	CreateDirectoryW(tyPath, NULL);
	CreateDirectoryW(fnPath, NULL);

	//tao node classes va them cao list classes
	Classes newClasses;
	newClasses.schoolYear = currentSchoolYear;
	newClasses.listClassInSy = new ListClassInSchoolYear;
	InitListClassInSchoolYear(newClasses.listClassInSy);
	addClassesIntoListClasses(listClasses, newClasses);

	//sao danh sach cac lop nam cu qua nam hoc moi
	nc preSchoolYear = listClasses->pHead;
	if (preSchoolYear == NULL) return;
	while (preSchoolYear->pNext != NULL)
	{
		if (preSchoolYear->pNext->classesInfo.schoolYear == currentSchoolYear)
		{
			break;
		}
		preSchoolYear = preSchoolYear->pNext;
	}

	ndeClass* curNodeClasses = preSchoolYear->classesInfo.listClassInSy->pHead;

	while (curNodeClasses != NULL)
	{
		if (curNodeClasses->classInfo.studentYear == "finalYear") break;
		Class tranferClass;
		tranferClass.className = curNodeClasses->classInfo.className;
		string preStuYear = curNodeClasses->classInfo.studentYear;
		string stuYear;
		if (preStuYear == "firstYear") stuYear = "secondYear";
		else if (preStuYear == "secondYear") stuYear = "thirdYear";
		else if (preStuYear == "thirdYear") stuYear = "finalYear";
		tranferClass.studentYear = stuYear;
		tranferClass.StudentsOfClass = curNodeClasses->classInfo.StudentsOfClass;
		studentYear = stuYear;
		writeFileStudentFromNewClassIntoDatabase(tranferClass.StudentsOfClass, tranferClass.className);
		addClassToListClassInSchoolYear(newClasses.listClassInSy, tranferClass);

		curNodeClasses = curNodeClasses->pNext;
	}

	//luu vao list class name
	className newClassName;
	newClassName.schoolYear = currentSchoolYear;
	newClassName.classesInTheSchoolYear.push_back("firstYear");
	string curStuYear = "secondYear";
	newClassName.classesInTheSchoolYear.push_back(curStuYear);
	ndeClass* tmpNdeClass = newClasses.listClassInSy->pHead;
	while (tmpNdeClass != NULL)
	{
		if (tmpNdeClass->classInfo.studentYear != curStuYear)
		{
			curStuYear = tmpNdeClass->classInfo.studentYear;
			newClassName.classesInTheSchoolYear.push_back(curStuYear);
			newClassName.classesInTheSchoolYear.push_back(tmpNdeClass->classInfo.className);
			tmpNdeClass = tmpNdeClass->pNext;
			continue;
		}
		newClassName.classesInTheSchoolYear.push_back(tmpNdeClass->classInfo.className);
		tmpNdeClass = tmpNdeClass->pNext;
	}

	addClassNameIntoList(listClassName, newClassName);
	saveDataFromListToFile();

}
void CreateSchoolYearUI()
{
	system("cls");
	const int width = 40;
	const int height = 11;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 11;

	drawBox(width, height, left, top);

	hideCursor(false);
	gotoXY(55, 5); cout << "HCMUS Portal";
	gotoXY(53, 7); cout << "Create School Year";

	gotoXY(49, 13); cout << "Input current school year ";
	gotoXY(57, 14); getline(cin, currentSchoolYear);

	bool exits = false;
	nc tmp = listClasses->pHead;
	while (tmp != NULL)
	{
		if (tmp->classesInfo.schoolYear == currentSchoolYear)
		{
			exits = true;
			break;
		}
		tmp = tmp->pNext;
	}

	if (exits)
	{
		system("cls");
		hasCreateSchoolYear = true;
		startDate = strToDate("05/09/" + currentSchoolYear.substr(0, 4));
		endDate = strToDate("10/07/" + currentSchoolYear.substr(5, 4));
		return;
	}

	string sDate, eDate;

	gotoXY(49, 15); cout << "Start Date: "; getline(cin, sDate);
	gotoXY(49, 16); cout << "End Date: "; getline(cin, eDate);
	startDate = strToDate(sDate);
	endDate = strToDate(eDate);

	CreateSchoolYear();

	hasCreateSchoolYear = true;
}