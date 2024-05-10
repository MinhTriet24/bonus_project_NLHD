#include "SchoolYear.h"

const string useDataPath = "Data/Accounts/users.csv"; //tao tuong dan den file du lieu cua nguoi dung
//ListClasses listClasses; //chua dung toi class

//ham them mot khoa hoc vao danh sach khoa hoc
void addCourse(ListCourses& list, Course* course)
{
	if (course == NULL)
	{
		return;
	}
	if (list.head == NULL)
	{
		//cho node dau va cuoi la course neu danh sach rong
		list.head = list.tail = course;
		course->prev = NULL;
	}
	else
	{
		//neu danh sach khong rong, day vao node cuoi
		list.tail->next = course;
		course->prev = list.tail;
		list.tail = course;
	}

	list.size++;//tang kich thuoc cua danh sach len
}

//ham chuyen doi du lieu chuoi sang node course
Course* convertCourseData(ifstream& data)
{
	Course* course = new Course;
	string credits, maxStudents, numberRegistered, session, academicYear;

	getline(data, course->id, ',');// doc vao id cua khoa hoc
	if (course->id == "") return NULL;//neu id rong nghia la du lieu khong ton tai thi return

	getline(data, course->courseName, ',');//doc vao ten khoa hoc
	getline(data, course->teacherName, ',');//doc ten giao vien
	getline(data, credits, ',');//so tin chi
	course->credits = stoi(credits);//chuyen sang dang so
	getline(data, academicYear, ',');
	course->academicYear = stoi(academicYear);
	getline(data, maxStudents, ',');
	course->maxStudents = stoi(maxStudents);
	getline(data, numberRegistered, ',');
	course->numberRegistered = stoi(numberRegistered);
	getline(data, course->wDay, ',');
	getline(data, session, '\n');//doc vao tiet bat dau va ket thuc

	course->session[0] = session.substr(session.find('S'), 2);//tim so tiet bat dau
	session.erase(session.find('S'), 2);//xoa so tiet bat dau
	course->session[1] = session.substr(session.find('S'), 2);//tim so tiet ket thuc
	course->next = NULL;
	return course;
}

void getCurrentSchoolYear()
{
	const int beginSchoolYear = 9;//tao hang luu thang dau tieng trong nam hoc
	if (currentDate.month < beginSchoolYear) //neu thang hien tai chua qua thang bat dau nam hoc moi
	{
		currentSchoolYear = to_string(currentDate.year - 1) + "-" + to_string(currentDate.year);//nghia la nam hoc con la nam truoc
	}
	else
	{
		currentSchoolYear = to_string(currentDate.year) + "-" + to_string(currentDate.year + 1);//neu da qua thi nam hoc la nam hien tai va nam sau
	}
	//vd thang 5 nam 2023 thi nam hoc la 2022-2023
	//con thang 10 nam 2023 thi nam hoc la 2023-2024
}

void getCurrentSemester()
{
	ifstream fIn;
	string fileSemesterDataName = "data/" + currentSchoolYear + "/semester.dat";
	fIn.open(fileSemesterDataName); //mo file luu tru du lieu cua ky hoc hien tai

	if (!fIn) //neu khong ton tai file
	{
		currentSemester.semester = 0; //khoi tao hoc ky hien tai la 0
		currentSemester.startDate = strToDate("0/0/0");//thoi gian bat dau la 0
		currentSemester.endDate = strToDate("0/0/0");// thoi gian ket thuc la 0
		// nghia la hoc ky khong ton tai
		return;
	}

	fIn >> currentSemester.semester; //doc hoc ky hien tai dang lai hoc ky may
	string startDate, endDate, dataTmp;
	getline(fIn, dataTmp);//doc du lieu thua
	getline(fIn, startDate);//doc ngay bat dau hoc ky
	getline(fIn, endDate); //doc ngay ket thuc hoc ky

	if (startDate == "" || endDate == "") //neu 1 trong 2 ngay khong ton tai
	{
		currentSemester.semester = 0; //khoi tao hoc ky hien tai la 0
		currentSemester.startDate = strToDate("0/0/0");//thoi gian bat dau la 0
		currentSemester.endDate = strToDate("0/0/0");// thoi gian ket thuc la 0
	}
	else //nguoc lai
	{
		currentSemester.startDate = strToDate(startDate); //chuyen ngay doc duoc thanh ngay bat dau nam hoc duoi dang struct Date
		currentSemester.endDate = strToDate(endDate);
		semesterPath = "data/" + currentSchoolYear + "/semester" + to_string(currentSemester.semester); //lay duong dan den file hoc ky hien tai
	}

}

void getListCourses()
{
	ifstream fIn;
	string fileCoursesName = semesterPath + "/courses.csv"; //lay duong dan file den cac khoa hoc cua hoc ky hien tai
	fIn.open(fileCoursesName);

	if (!fIn.is_open() || !fIn) return; //return neu khong mo duoc hay khong ton tai file

	string tmpData; //bien string luu du lieu tam
	string start, end;

	getline(fIn, tmpData);
	start = tmpData.substr(tmpData.find(',') + 1, 10);//tim chuoi ngay bat dau trong chuoi tmpData
	//substr la chuoi con, ham find tro den vi tri cua ki tu, 10 la do lai cua chuoi ngay
	// vi du 24/12/2005 co do dai chuoi la 10
	end = tmpData.substr(tmpData.find('-') + 1, 10); //tuong tu ngay bat dau

	//luu ngay bat dau va ket thuc vao danh sach khoa hoc
	listCourses.startDate = strToDate(start);
	listCourses.endDate = strToDate(end);

	getline(fIn, tmpData);// doc du lieu tam
	while (!fIn.eof())
	{
		//addCourses(listCourses, convertCourseData(fIn));
	}
}
