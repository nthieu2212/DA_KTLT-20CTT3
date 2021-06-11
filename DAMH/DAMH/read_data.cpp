﻿#include "Header.h"
#include "read_data.h"
#include"ConsoleProcess.h"

void read_1_info(User& A, ifstream &f) {
	string NO_temp;
	getline(f, NO_temp, ',');
	A.info.NO_inclass =	stoi(NO_temp);
	getline(f, A.info.IDstd, ',');// giáo viên thì sẽ là id đăng nhập
	getline(f, A.info.name, ',');
	getline(f, A.info.Bir, ',');
	getline(f, A.info.sex, ',');
	getline(f, A.info.IDsocial);
}
//
void read_info(User& A) {
	string fileName;
	if (A.role == 1) {
		fileName = "file_save/Class/"+A.info.Class + csv_tail;
	}
	else {
		fileName = "file_save/SchoolYear/2020-2021/staff.csv";
	}
	ifstream info_file;
	info_file.open(fileName, ios::in);
	string temp;
	getline(info_file, temp);
	while (info_file.eof() == false) {
		read_1_info(A, info_file);
		if (A.ID.compare(A.info.IDstd) == 0) {
			break;
		}
		else {
			continue;
		}
	}
	info_file.close();
}
void Output_info(User A) {
	system("cls");
	printtext(" _            ___                                     _               ", 20, 2);
	printtext("(_)          / __)                               _   (_)              ", 20, 3);
	printtext(" _  ____   _| |__   ___    ____  ____   _____  _| |_  _   ___   ____  ", 20, 4);
	printtext("| ||  _ \\ (_   __) / _ \\  / ___)|    \\ (____ |(_   _)| | / _ \\ |  _ \\ ", 20, 5);
	printtext("| || | | |  | |   | |_| || |    | | | |/ ___ |  | |_ | || |_| || | | |", 20, 6);
	printtext("|_||_| |_|  |_|    \\___/ |_|    |_|_|_|\\_____|   \\__)|_| \\___/ |_| |_|", 20, 7);
	drawRectangle(30, 12, 50, 16, 11);
	printtext("Ho va ten: " + A.info.name, 35, 15);
	if (A.role == 1) {
		printtext("Ma so sinh vien: " + A.info.IDstd, 35, 17);
	}
	else {
		printtext("email : " + A.info.IDstd + "@hcmus.edu.vn", 35, 17);
	}
	printtext("ngay sinh: " + A.info.Bir, 35, 19);
	printtext("gioi tinh: " + A.info.sex, 35, 21);
	printtext("chuc vu: " + (A.role == 1) ? "Hoc sinh" : "Admin", 35, 23);
	printtext("CMND/CCCD: " + A.info.IDsocial, 35, 25);
	textBgColor(0, 15);
	system("pause");
}

void read_course(User& A, SchoolYear y)
{
	system("cls");
	/*string fileName, fileName2, flag, flag2;
	Course co;
	fileName = "file_save/Class/20CTT3_course_1_2020.csv";
	ifstream courseFile;
	int i = 1;
	courseFile.open(fileName, ios::in);

	if (!courseFile.is_open())
		std::cout << "reading file error!";*/
	gotoxy(1, 5); std::cout << "Order";
	gotoxy(8, 5); std::cout << "Id course";
	gotoxy(19, 5); std::cout << "Course name";
	gotoxy(35, 5); std::cout << "Lecturer";
	gotoxy(50, 5); std::cout << "Max student";
	gotoxy(63, 5); std::cout << "Student";
	gotoxy(72, 5); std::cout << "Schedule";
	gotoxy(88, 5); std::cout << "Start date";
	gotoxy(105, 5); std::cout << "End date" << std::endl;

	ifstream f;
	string fileName = "file_save/Class/" + A.info.Class + "_1_2020" + csv_tail;// chỉ là thử nghiệm, sau khi có hàm đọc học kì sẽ thay đổi.
	f.open(fileName, ios::in);
	init_List_Mark(A.info.phead);
	while (f.eof() == false) {
		string temp;
		getline(f, temp, ',');
		if (temp.compare(A.ID) != 0) {
			getline(f, temp);
		}
		else {
			getline(f, temp);
			string IDtemp = "";
			for (int i = 0; i < temp.length(); i++) {
				if (temp[i] == ',' || i == temp.length() - 1)
				{
					if (i == temp.length() - 1) {
						IDtemp += temp[i];
					}
					add_Tail_List_Mark(A.info.phead, IDtemp);
					IDtemp = "";
				}
				else if (temp[i] != ',') {
					IDtemp += temp[i];
				}
			}
		}
	}
	f.close();
	ifstream fi;
	fileName = "file_save/Class/SchoolYear/" + y.year + "/" + y.semester.Name + "/course_info.csv";
	MarkNode* tempo = new MarkNode;
	tempo = A.info.phead;
	string fl;	
	Course co;
	int i = 1;
	while (tempo != NULL)
	{
		fi.open(fileName, ios::in);
		getline(fi, fl);
		while (!fi.eof())
		{
			getline(fi, fl, ','); 
			read1CourseInfor(co, fi);
			if (co.ID_course.compare(tempo->ID) == 0)
			{
				gotoxy(1, 5 + i); std::cout << i;
				gotoxy(8, 5 + i); std::cout << co.ID_course;
				gotoxy(19, 5 + i); std::cout << co.name;
				gotoxy(35, 5 + i); std::cout << co.teacher;
				gotoxy(50, 5 + i); std::cout << co.Max_student;
				gotoxy(63, 5 + i); std::cout << co.Num_of_std_now;
				gotoxy(72, 5 + i); std::cout << co.Schedule;
				gotoxy(88, 5 + i); std::cout << co.date_star;
				gotoxy(105, 5 + i); std::cout << co.date_end;
				i++;
				tempo = tempo->pNext;
				break;
			}
		}
		fi.close();
	}

		system("pause");
}

void read1CourseInfor(Course& A, ifstream& f)
{
	string flag;//luu tru thong tin dang int tam thoi;
	getline(f, flag,',');
	getline(f, A.ID_course, ',');

	getline(f, A.name, ',');
	getline(f, A.teacher, ',');
	getline(f, flag, ',');
	A.Num_of_std_now= stoi(flag, 0, 10);
	getline(f, flag, ',');
	A.Max_student = stoi(flag, 0, 10);
	getline(f, A.Schedule, ',');
	getline(f, A.date_star, ',');
	getline(f, A.date_end, ',');
}
void init_List_Mark(MarkNode*& head) {
	head = NULL;
}
void add_Tail_List_Mark(MarkNode*& head, string A) {
	//khởi tạo 1 node
	MarkNode* n1 = new MarkNode;
	n1->ID = A;
	n1->pNext = NULL;
	MarkNode* temp = head;
	if (head == NULL) {
		head = n1;
		return;
	}
	else {
		while (temp->pNext != NULL) {
			temp = temp->pNext;
		}
		temp->pNext = n1;
	}
}

