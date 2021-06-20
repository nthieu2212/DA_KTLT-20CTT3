﻿#include "Header.h"
#include "Course_function.h"
#include"ConsoleProcess.h"
#include "read_data.h"
#include "login.h"
#include "staffFunction.h"
// hàm tổng quát, command_flag >=0, thì thêm data vào file, <0 xóa data khỏi file
void rewrite_course_of_student_file(User user, string fileName, string data, int command_flag) {
	fstream file_prv, file_aft;
	string oldName = fileName+csv_tail;
	string newName = fileName+"new"+csv_tail;
	file_prv.open(oldName, ios::in);
	file_aft.open(newName, ios::out);
	string temp;
	bool flag_change = true;
	while (file_prv.eof() == false) {
		//đọc, ghi lại số thứ tự
		/*getline(file_prv, temp, ',');
		file_aft << temp << ',';*/
		//đọc ghi lại mssv
		getline(file_prv, temp);
		string temp1 = "";
		int i = 0;
		for (i = 0; i < temp.length(); i++) {
			if (temp[i] == ',' || i == temp.length() - 1)
			{
				if (i == temp.length() - 1) {
					temp1 += temp[i];
				}
				break;
			}
			else if (temp[i] != ',') {
				temp1 += temp[i];
			}
		}
		if (user.ID.compare(temp1) != 0) {
			if (flag_change == true) {
				file_aft << temp;
				flag_change = false;
			}
			else {
				file_aft << '\n' << temp;
			}
		}
		else {
			if (command_flag >= 0) {
				temp1 = temp + ',' + data;
			}
			else {
				string temp2 = "";
				for (i = i + 1; i < temp.length(); i++) {
					if (temp[i] == ',' || i == temp.length() - 1)
					{
						if (i == temp.length() - 1) {
							temp2 += temp[i];
						}
						if (_strcmpi(temp2.c_str(), data.c_str()) != 0) {
							temp1 = temp1 + ',' + temp2;
						}
						temp2 = "";
					}
					else if (temp[i] != ',') {
						temp2 += temp[i];
					}
				}
			}
			if (flag_change == true) {
				file_aft << temp1;
				flag_change = false;
			}
			else {
				file_aft << '\n' << temp1;
			}
		}
	}
	file_prv.close();
	file_aft.close();
	// removing the existing file
	remove(oldName.c_str());
	// renaming the updated file with the existing file name
	rename(newName.c_str(), oldName.c_str());
}
//hàm ghi danh vào file khóa học tổng của staff, user là học sinh.
//void rewrite_course_of_staff_file(User user, string fileName, string ID_course, int command_flag) {
//	fstream file_prv, file_aft;
//	string oldName = fileName + csv_tail;
//	string newName = fileName + "new" + csv_tail;
//	file_prv.open(oldName, ios::in);
//	file_aft.open(newName, ios::out);
//	string temp;
//	bool flag_change = true;
//	while (file_prv.eof() == false) {
//		string str_num_of_student;
//		int num_of_student;
//		getline(file_prv, temp, ',');
//		if (flag_change == true) {
//			file_aft << temp;
//			flag_change = false;
//		}
//		else {
//			file_aft << '\n' << temp;
//		}
//		getline(file_prv, str_num_of_student);
//		num_of_student = stoi(str_num_of_student);
//		if (_strcmpi(temp.c_str(), ID_course.c_str()) != 0) {
//			file_aft << ',' << str_num_of_student;
//			for (int i = 0; i < num_of_student; i++) {
//				getline(file_prv, temp);
//				file_aft << '\n' << temp;
//			}
//		}
//		else {
//			if (command_flag >= 0) {
//				num_of_student++;
//				file_aft << ',' << to_string(num_of_student);
//				for (int i = 0; i < num_of_student - 1; i++) {
//					getline(file_prv, temp);
//					file_aft << '\n' << temp;
//				}
//				file_aft << '\n' << user.ID << ',' << "20CTT333";
//			}
//			else {
//				num_of_student--;
//				file_aft << ',' << to_string(num_of_student);
//				for (int i = 0; i < num_of_student + 1; i++) {
//					getline(file_prv, temp, ',');
//					if (_strcmpi(temp.c_str(), user.ID.c_str()) == 0) {
//						getline(file_prv, temp);
//					}
//					else {
//						file_aft << temp;
//						getline(file_prv, temp);
//						file_aft << '\n' << temp;
//					}
//				}
//			}
//		}
//	}
//	file_prv.close();
//	file_aft.close();
//	// removing the existing file
//	remove(oldName.c_str());
//	// renaming the updated file with the existing file name
//	rename(newName.c_str(), oldName.c_str());
//};
void rewrite_course_file(User user, string fileName, int command_flag) {
	fstream file_prv, file_aft;
	string oldName = fileName + csv_tail;
	string newName = fileName + "new" + csv_tail;
	file_prv.open(oldName, ios::in);
	file_aft.open(newName, ios::out);
	string temp;
	bool flag_change = true;
	while (file_prv.eof() == false) {
		//đọc, ghi lại số thứ tự
		/*getline(file_prv, temp, ',');
		file_aft << temp << ',';*/
		//đọc ghi lại mssv
		getline(file_prv, temp, ',');
		if (_strcmpi(temp.c_str(), user.info.IDstd.c_str()) == 0) {
			getline(file_prv, temp);
			continue;
		}
		else {
			if (flag_change == true) {
				file_aft << temp << ',';
				flag_change = false;
			}
			else {
				file_aft << '\n' << temp << ',';
			}
			getline(file_prv, temp);
			file_aft << temp;
		}
	}
	if (command_flag >= 0) {
		temp = user.info.IDstd + ',' + user.info.name + ',' + user.info.Class;
		if (flag_change == true) {
			file_aft << temp;
			flag_change = false;
		}
		else {
			file_aft << '\n' << temp;
		}
	}
	file_prv.close();
	file_aft.close();
	// removing the existing file
	remove(oldName.c_str());
	// renaming the updated file with the existing file name
	rename(newName.c_str(), oldName.c_str());
}
void enroll_course(User& A, SchoolYear s_y, int command_flag) {
	string semester_path = "file_save/SchoolYear/" + s_y.year + '/' + s_y.semester.Name + '/';
	string class_path = semester_path + "Class/";
	string course_path = semester_path + "Course/";
	//hàm trang trí
	//hàm hiện danh sách các môn học.
	string ID_course_input;
	if (command_flag >= 0) {
		viewCourse();
		cout << "\nEnter ID course you want to enroll: ";
	}
	else {
		read_course(A, s_y);
		cout << "\nEnter ID course you want to delete: ";
	}
	insertUserName(ID_course_input);
	fstream file_course_info;
	file_course_info.open(semester_path + "course_info.csv", ios::in);
	string temp;
	bool realine_flag = false, delete_flag = false;
	while (file_course_info.eof() == false) {
		getline(file_course_info, temp, ',');//đọc mã môn học
		//nếu so sánh được mã môn nhập vào có trong danh sách lớp học, cho phép ghi danh:
		if (_strcmpi(temp.c_str(), ID_course_input.c_str()) == 0) {
			string Name;
			getline(file_course_info, Name, ',');
			MarkNode* Mtemp = A.info.phead;
			//kiểm tra xem trong danh sách môn học của sinh viên đã có môn này hay chưa
			realine_flag = true;
			while (Mtemp != NULL) {
				if (_strcmpi(temp.c_str(), Mtemp->data.ID.c_str()) == 0) {
					//nếu có thì return.
					if (command_flag >=0) {
						cout << "\nFailed!! The course has been registered before.";
						return;
					}
					else {
						delete_flag = true;
						break;
					}
				}
				Mtemp = Mtemp->pNext;
			}
			if (command_flag>=0){
				//chưa có thì thêm vào danh sách.
				add_Tail_List_Mark(A.info.phead, temp,Name);
				//ghi them vao file;
				string file_cousre_of_class = class_path + A.info.Class;
				rewrite_course_of_student_file(A, file_cousre_of_class, temp, 1);
				string file_cousre = course_path + temp;
				rewrite_course_file(A, file_cousre, 1);
				cout << "\nSuccessfully!!!!";
			}
			else {
				if (delete_flag == true) {
					delete_Mark_node(A.info.phead, temp);
					string file_cousre_of_class = class_path + A.info.Class;
					rewrite_course_of_student_file(A, file_cousre_of_class, temp, -1);
					string file_cousre = course_path + temp;
					rewrite_course_file(A, file_cousre, -1);
					cout << "\nSuccessfully!!!!";
				}
				else {
					cout << "\nYou have not registered for this course yet!!";
				}
			}
		}
		// ngược lại so sánh không hợp lệ, đọc hết dòng, chạy đến dòng tiếp theo
		else {
			getline(file_course_info, temp);
		}
	}
	if (realine_flag == false) {
		cout << "\nFailed!! Invalid ID course";
		return;
	}
}
void MoveUpMenu(int X, int& Y) {
	Y = Y - 2;
	gotoxy(X, Y);
}
void MoveDownMenu(int X, int& Y) {
	Y = Y + 2;
	gotoxy(X, Y);
}
int MoveAndChoose(int a, string A[], int _X, int _Y) { //ham di chuyen len xuong va chon doi tuong trong cac dang menu
	char _COMMAND;
	int X = _X, Y = _Y;
	int i = 0;
	while (1) {
		_COMMAND = toupper(_getch());
		if (_COMMAND == 27) {
			return -1;
		}
		else {
			if (i >= 0 && i < a && Y <= 23 + a) {
				if (_COMMAND == 72 && Y > _Y) {
					textColor(496);
					gotoxy(X, Y);
					cout << A[i];
					MoveUpMenu(X, Y);
					i--;
					textColor(15);
					cout << A[i];
					textColor(496);
				}
				else if (_COMMAND == 80 && Y < _Y + 2 * (a - 1)) {
					textColor(496);
					gotoxy(X, Y);
					cout << A[i];
					MoveDownMenu(X, Y);
					i++;
					textColor(15);
					cout << A[i];
					textColor(496);
				}
				else if (_COMMAND == 13) {
					return i;
				}
			}
		}
	}
}
void drawMenuYear(string* S, int n, int x, int y) {
	hidePointer();
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			textColor(15);
			printtext(S[i], x, y + 2 * i);
			textColor(496);
		}
		else
			printtext(S[i], x, y + 2 * i);
	}
}
int getyearData(string* data1, int* data2, string filename) {

	ifstream f;
	f.open(filename, ios::in);
	string temp;
	int i = 0;
	getline(f, temp);
	while (!f.eof()) {
		getline(f, data1[i], ',');
		getline(f, temp);
		data2[i] = atoi(temp.c_str());
		i++;
	}
	return i;
}
void change_Year_Semester(SchoolYear &S) {
	string* year;
	int* semester;
	string filename = "file_save/year-semester.csv";
	int n = countLine(filename) - 1;
	year = new string[n];
	semester = new int[n];
	getyearData(year, semester, filename);
	system("cls");
	textColor(46);
	printtext("   ______    __                                        __  __                      ", 15, 4);
	printtext("  / ____/   / /_   ____ _   ____    ____ _  ___        \\ \\/ /  ___   ____ _   _____", 15, 5);
	printtext(" / /       / __ \\ / __ `/  / __ \\  / __ `/ / _ \\        \\  /  / _ \\ / __ `/  / ___/", 15, 6);
	printtext("/ /___    / / / // /_/ /  / / / / / /_/ / /  __/        / /  /  __// /_/ /  / /    ", 15, 7);
	printtext("\\____/   /_/ /_/ \\__,_/  /_/ /_/  \\__, /  \\___/        /_/   \\___/ \\__,_/  /_/     ", 15, 8);
	printtext("                                 /____/                                            ", 15, 9);
	textColor(496);
	drawMenuYear(year, n, 55, 15);
	int A = MoveAndChoose(n, year, 55, 15);
	if (A == -1) {
		return;
	}
	string* semester_of_year = new string[semester[A]];
	for (int i = 0; i < semester[A]; i++) {
		semester_of_year[i] = "Semester" + to_string(i + 1);
	}
	system("cls");
	textColor(46);
	printtext("   ______    __                                 ", 35, 5);
	printtext("  / ____/   / /_   ____ _   ____    ____ _  ___ ", 35, 6);
	printtext(" / /       / __ \\ / __ `/  / __ \\  / __ `/ / _ \\", 35, 7);
	printtext("/ /___    / / / // /_/ /  / / / / / /_/ / /  __/", 35, 8);
	printtext("\\____/   /_/ /_/ \\__,_/  /_/ /_/  \\__, /  \\___/ ", 35, 9);
	printtext("                                 /____/         ", 35, 10);
	printtext("   _____                                   __               ", 30, 23);
	printtext("  / ___/  ___    ____ ___   ___    _____  / /_  ___    _____", 30, 24);
	printtext("  \\__ \\  / _ \\  / __ `__ \\ / _ \\  / ___/ / __/ / _ \\  / ___/", 30, 25);
	printtext(" ___/ / /  __/ / / / / / //  __/ (__  ) / /_  /  __/ / /    ", 30, 26);
	printtext("/____/  \\___/ /_/ /_/ /_/ \\___/ /____/  \\__/  \\___/ /_/     ", 30, 27);
	printtext("                                                            ", 30, 28);
	textColor(496);
	drawMenuYear(semester_of_year, semester[A], 55, 15);
	int i=MoveAndChoose(semester[A], semester_of_year, 55, 15);
	if (i==-1) {
		return;
	}
	S.year = year[A];
	S.semester.Name = semester_of_year[i];
}
void DisPlay_Course_Of_Student(SchoolYear Y, User A) {
	char ch;
	do {
		hidePointer();
		read_course(A, Y);
		drawRectangle(27, 29, 60, 1, 10);
		textColor(496);
		string text = Y.semester.Name + "; Year: " + Y.year + ".   Press[C] to change!";
		printtext(text, 32, 29);
		ch = getch();
		//[ESC]
		if (ch == 27) {
			return;
		}
		else {
			//Control Up down 
			if (ch == 'c' || ch == 'C') //up
			{
				change_Year_Semester(Y);
				get_course(A, Y);
				read_course(A, Y);
			}
		}
	} while (true);
}
void edit_score(User& A, SchoolYear SY, int line, Mark* M) {
	char ch;
	int line_now = 1;
	int x = 15, y = 14;
	drawRectangle(1, y + line_now, 115, 1, 14);
	textBgColor(0, 14);
	view_1_line(M[line_now - 1], x, y + line_now);
	do {
		hidePointer();
		ch = _getch();
		//[ESC]
		if (ch == 27) {
			drawRectangle(1, y + line_now, 115, 1, 11);
			textBgColor(0, 11);
			view_1_line(M[line_now - 1], x, y + line_now);
			break;
		}
		else {
			//Control Up down 
			if (ch == 72 && line_now > 1) //up
			{
				drawRectangle(1, y + line_now, 115, 1, 11);
				textBgColor(0, 11);
				view_1_line(M[line_now - 1], x, y + line_now);

				line_now--;
				drawRectangle(1, y + line_now, 115, 1, 14);
				textBgColor(0, 14);
				view_1_line(M[line_now - 1], x, y + line_now);
			}
			if (ch == 80 && line_now < line) //down
			{
				drawRectangle(1, y + line_now, 115, 1, 11);
				textBgColor(0, 11);
				view_1_line(M[line_now - 1], x, y + line_now);

				line_now++;
				drawRectangle(1, y + line_now, 115, 1, 14);
				textBgColor(0, 14);
				view_1_line(M[line_now - 1], x, y + line_now);
			}
			if (ch == 13) {
				string fCheck = "file_save/SchoolYear/" + SY.year + '/' + SY.semester.Name + "/Course/score/" + M[line_now - 1].ID + csv_tail;
				fstream fcheck;
				fcheck.open(fCheck, ios::in);
				if (!fcheck.good())
				{
					gotoxy(x + 42, y + line_now);
					cout << "Fail!! This subject has not been graded by the teacher yet.";
					Sleep(900);
					drawRectangle(1, y + line_now, 115, 1, 14);
					textBgColor(0, 14);
					view_1_line(M[line_now - 1], x, y + line_now);
					fcheck.close();
					continue;
				}
				else {
					fcheck.close();
					int y_now = y + line_now;
					int x_now = x + 42, x_max = x + 70, x_min = x + 42;
					string S[] = { to_string(M[line_now - 1].Midterm_Mark),to_string(M[line_now - 1].Final_Mark),to_string(M[line_now - 1].Other_Mark) };
					drawRectangle(x + 42, y_now, 14, 1, 15);
					textBgColor(0, 15);
					printtext(to_string(M[line_now - 1].Midterm_Mark), x + 42, y_now);
					char CH;
					do
					{
						CH = _getch();
						//ESC
						if (CH == 27) {
							drawRectangle(x_now, y_now, 14, 1, 14);
							textBgColor(0, 14);
							printtext(S[(x_now - x_min) / 14], x_now, y_now);
							break;
						}
						else {
							//Left 
							if (CH == 75 && x_now > x_min) {
								drawRectangle(x_now, y_now, 14, 1, 14);
								textBgColor(0, 14);
								printtext(S[(x_now - x_min) / 14], x_now, y_now);

								x_now = x_now - 14;
								drawRectangle(x_now, y_now, 14, 1, 15);
								textBgColor(0, 15);
								printtext(S[(x_now - x_min) / 14], x_now, y_now);
							}
							//Right
							if (CH == 77 && x_now < x_max) {
								drawRectangle(x_now, y_now, 14, 1, 14);
								textBgColor(0, 14);
								printtext(S[(x_now - x_min) / 14], x_now, y_now);

								x_now = x_now + 14;
								drawRectangle(x_now, y_now, 14, 1, 15);
								textBgColor(0, 15);
								printtext(S[(x_now - x_min) / 14], x_now, y_now);
							}

							//[ENTER]
							if (CH == 13) {
								drawRectangle(x_now, y_now, 14, 1, 15);
								textBgColor(0, 15);
								float i;
								string mark;
								int flag = 0;
								do {
									mark = "";
									gotoxy(x_now, y_now);
									insertMark(mark, 5, flag);
									if (flag == -1) {
										drawRectangle(x_now, y_now, 14, 1, 15);
										textBgColor(0, 15);
										printtext(S[(x_now - x_min) / 14], x_now, y_now);
										break;
									}
									else {
										i = atof(mark.c_str());
										if (i > 10) {
											gotoxy(x_now, y_now);
											cout << "Erroll!!";
											Sleep(900);
											drawRectangle(x_now, y_now, 14, 1, 15);
										}
									}
								} while (i > 10);
								if (flag == 0) {
									int a = (x_now - x_min) / 14;
									switch (a)
									{
									case 0:
										M[line_now - 1].Midterm_Mark = i;
										S[(x_now - x_min) / 14] = to_string(M[line_now - 1].Midterm_Mark);
										break;
									case 1:
										M[line_now - 1].Final_Mark = i;
										S[(x_now - x_min) / 14] = to_string(M[line_now - 1].Final_Mark);
										break;
									case 2:
										M[line_now - 1].Other_Mark = i;
										S[(x_now - x_min) / 14] = to_string(M[line_now - 1].Other_Mark);
										break;
									default:
										break;
									}
									M[line_now - 1].Total_Mark = 0.3 * M[line_now - 1].Midterm_Mark + 0.6 * M[line_now - 1].Final_Mark + 0.1 * M[line_now - 1].Other_Mark;
									drawRectangle(1, y + line_now, 115, 1, 14);
									textBgColor(0, 14);
									view_1_line(M[line_now - 1], x, y + line_now);
									drawRectangle(x_now, y_now, 14, 1, 15);
									textBgColor(0, 15);
									printtext(S[(x_now - x_min) / 14], x_now, y_now);
									save_Mark(A, M, line_now - 1, SY);
								}
							}

						}
					} while (true);
				}

			}
		}
	} while (true);
	textBgColor(0, 15);
}
void DisPlay_Mark_Of_Student(SchoolYear Y, User A) {
	char ch;
	do {
		hidePointer();
		view_all_score_of_1_student(A, Y);
		drawRectangle(27, 29, 60, 1, 6);
		textColor(499);
		string text = Y.semester.Name + "; Year: " + Y.year + ".   Press[C] to change!";
		printtext(text, 32, 29);
		ch = getch();
		//[ESC]
		if (ch == 27) {
			return;
		}
		else {
			if (ch == 'c' || ch == 'C') 
			{
				change_Year_Semester(Y);
				get_course(A, Y);
				view_all_score_of_1_student(A, Y);
			}
		}
	} while (true);
	textBgColor(0, 15);
}

void edit_score_in_list_course(User& A, SchoolYear SY) {
	string IDcourse = "ABC4";
	int n = 0;
	Mark* M = read_file_score_of_course(SY, IDcourse, n);
	char ch;
	int line_now = 0;
	int x = 10, y = 14;
	int tab_now=view_score_of_course_in_year(M, n);
	drawRectangle(1, y + line_now, 115, 1, 14);
	textBgColor(0, 14);
	view_1_score_of_course(M[tab_now * 10], x, y);
	int count = tab_now*10;
	do {
		if (tab_now == -1) {
			return;
		}
		hidePointer();
		ch = _getch();
		//[ESC]
		if (ch == 27) {
			tab_now = view_score_of_course_in_year(M, n);
			break;
		}
		else {
			//Control Up down 
			if (ch == 72 && line_now > 0) //up
			{
				drawRectangle(1, y + line_now, 115, 1, 11);
				textBgColor(0, 11);
				view_1_score_of_course(M[count], x, y+line_now);

				line_now--;
				count--;
				drawRectangle(1, y + line_now, 115, 1, 14);
				textBgColor(0, 14);
				view_1_score_of_course(M[count], x, y + line_now);
			}
			else if (ch == 72 && line_now == 0 && count>0) {
				count--;
				drawRectangle(0, y, 120, 11, 11);
				view_10_score_of_course(M, count, n, x, y);
				drawRectangle(1, y + line_now, 115, 1, 14);
				textBgColor(0, 14);
				view_1_score_of_course(M[count], x, y + line_now);
			}
			else if (ch == 80 && line_now < 9) //down
			{
				drawRectangle(1, y + line_now, 115, 1, 11);
				textBgColor(0, 11);
				view_1_score_of_course(M[count ], x, y + line_now);

				line_now++;
				count++;
				drawRectangle(1, y + line_now, 115, 1, 14);
				textBgColor(0, 14);
				view_1_score_of_course(M[count], x, y+line_now);
			}
			else if (ch == 80 && line_now == 9 && count < n-2) {
				count++;
				drawRectangle(0, y, 120, 11, 11);
				view_10_score_of_course(M, count-9, n, x, y);
				drawRectangle(1, y + line_now, 115, 1, 14);
				textBgColor(0, 14);
				view_1_score_of_course(M[count], x, y + line_now);
			}
			if (ch == 13) {
				string fCheck = "file_save/SchoolYear/" + SY.year + '/' + SY.semester.Name + "/Course/score/" + M[line_now - 1].ID + csv_tail;
				fstream fcheck;
				fcheck.open(fCheck, ios::in);
				if (!fcheck.good())
				{
					gotoxy(x + 42, y + line_now);
					cout << "Fail!! This subject has not been graded by the teacher yet.";
					Sleep(900);
					drawRectangle(1, y + line_now, 115, 1, 14);
					textBgColor(0, 14);
					view_1_line(M[line_now - 1], x, y + line_now);
					fcheck.close();
					continue;
				}
				else {
					fcheck.close();
					int y_now = y + line_now;
					int x_now = x + 42, x_max = x + 70, x_min = x + 42;
					string S[] = { to_string(M[line_now - 1].Midterm_Mark),to_string(M[line_now - 1].Final_Mark),to_string(M[line_now - 1].Other_Mark) };
					drawRectangle(x + 42, y_now, 14, 1, 15);
					textBgColor(0, 15);
					printtext(to_string(M[line_now - 1].Midterm_Mark), x + 42, y_now);
					char CH;
					do
					{
						CH = _getch();
						//ESC
						if (CH == 27) {
							drawRectangle(x_now, y_now, 14, 1, 14);
							textBgColor(0, 14);
							printtext(S[(x_now - x_min) / 14], x_now, y_now);
							break;
						}
						else {
							//Left 
							if (CH == 75 && x_now > x_min) {
								drawRectangle(x_now, y_now, 14, 1, 14);
								textBgColor(0, 14);
								printtext(S[(x_now - x_min) / 14], x_now, y_now);

								x_now = x_now - 14;
								drawRectangle(x_now, y_now, 14, 1, 15);
								textBgColor(0, 15);
								printtext(S[(x_now - x_min) / 14], x_now, y_now);
							}
							//Right
							if (CH == 77 && x_now < x_max) {
								drawRectangle(x_now, y_now, 14, 1, 14);
								textBgColor(0, 14);
								printtext(S[(x_now - x_min) / 14], x_now, y_now);

								x_now = x_now + 14;
								drawRectangle(x_now, y_now, 14, 1, 15);
								textBgColor(0, 15);
								printtext(S[(x_now - x_min) / 14], x_now, y_now);
							}

							//[ENTER]
							if (CH == 13) {
								drawRectangle(x_now, y_now, 14, 1, 15);
								textBgColor(0, 15);
								float i;
								string mark;
								int flag = 0;
								do {
									mark = "";
									gotoxy(x_now, y_now);
									insertMark(mark, 5, flag);
									if (flag == -1) {
										drawRectangle(x_now, y_now, 14, 1, 15);
										textBgColor(0, 15);
										printtext(S[(x_now - x_min) / 14], x_now, y_now);
										break;
									}
									else {
										i = atof(mark.c_str());
										if (i > 10) {
											gotoxy(x_now, y_now);
											cout << "Erroll!!";
											Sleep(900);
											drawRectangle(x_now, y_now, 14, 1, 15);
										}
									}
								} while (i > 10);
								if (flag == 0) {
									int a = (x_now - x_min) / 14;
									switch (a)
									{
									case 0:
										M[line_now - 1].Midterm_Mark = i;
										S[(x_now - x_min) / 14] = to_string(M[line_now - 1].Midterm_Mark);
										break;
									case 1:
										M[line_now - 1].Final_Mark = i;
										S[(x_now - x_min) / 14] = to_string(M[line_now - 1].Final_Mark);
										break;
									case 2:
										M[line_now - 1].Other_Mark = i;
										S[(x_now - x_min) / 14] = to_string(M[line_now - 1].Other_Mark);
										break;
									default:
										break;
									}
									M[line_now - 1].Total_Mark = 0.3 * M[line_now - 1].Midterm_Mark + 0.6 * M[line_now - 1].Final_Mark + 0.1 * M[line_now - 1].Other_Mark;
									drawRectangle(1, y + line_now, 115, 1, 14);
									textBgColor(0, 14);
									view_1_line(M[line_now - 1], x, y + line_now);
									drawRectangle(x_now, y_now, 14, 1, 15);
									textBgColor(0, 15);
									printtext(S[(x_now - x_min) / 14], x_now, y_now);
									save_Mark(A, M, line_now - 1, SY);
								}
							}

						}
					} while (true);
				}

			}
		}
	} while (true);
	textBgColor(0, 15);
}