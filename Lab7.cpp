#include <iostream>
#include <string>
#include <time.h>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "Sqlite/sqlite3.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::vector;
using std::find;

string inputID;//Global variable for input ID accross all roles.

static int callBacklogin(void* data, int argc, char** argv, char** azColName); // callback function for login fucntion
static int callBackAllCourse(void* NotUsed, int argc, char** argv, char** azColName);// callback function for printing all courses
static int callBackCourse(void* NotUsed, int argc, char** argv, char** azColName);// print course information
static int callBackStudent(void* NotUsed, int argc, char** argv, char** azColName);// print student infomation
static int callBackcolnum(void* data, int argc, char** argv, char** azColname);
static void createTable(const char* d); // create student, instructor, admin, courses, student schedule, instructor schedule tables
static void populateTable(const char* d);// add data to tables for testing purposes
static int logInOut(const char* d);//function to log in and out
static void addorremovePeople(const char* d);// admin function to add or remove people from system
static void addorremoveCourse(const char* d);// admin function to add or remove courses from system
static void addordropCourse(const char* d);// student function to add or drop course from schedule
static void searchallCourse(const char* d);// all users search all course
static void searchCourse(const char* d, string crn);
static void assignInstructor(const char* d); // admin function to assign an instructor to a course. Must be in the same department
static void printSchedule(const char* d); //print student schedule
static void printRoster(const char* d); // print instructor course roster
static string getColName(sqlite3* db);
static string getUsername(sqlite3* db, int user, string ID);
static string getCourse(sqlite3* db, string CRN);

int main() {
	const char* dir = "assignment7.db";
	sqlite3* db;
	createTable(dir);
	populateTable(dir);

	string r = "1";
	while (r == "1") {
		LOGIN:
		int login;
		string loginChoice;
		login = logInOut(dir);
		if (login == 11) {
			string todoS;
		CONT_STUDENT:
			string contS;
			cout << "\nWhat would you like to do?" << endl;
			cout << "Press 1 to search all courses." << endl;
			cout << "Press 2 to search courses based on CRN" << endl;
			cout << "Press 3 to add or drop courses." << endl;
			cout << "Press 4 to print detailed schedule." << endl;
			cout << "Press any other key to logout." << endl;
			cout << "Choice: ";
			cin >> todoS;
			cout << endl;
			if (todoS == "1") {
				searchallCourse(dir);
			}
			else if (todoS == "2") {
				string courseCRN;
				cout << "What is the course CRN: ";
				cin >> courseCRN;
				searchCourse(dir, courseCRN);
			}
			else if (todoS == "3") {
				addordropCourse(dir);
			}
			else if (todoS == "4") {
				printSchedule(dir);
			}
			else {
				cout << "\nWould you like to login as another user? Press 1 to login as another user. Press any other key to exit: ";
				cin >> loginChoice;
				if (loginChoice == "1") {
					goto LOGIN;
				}
				else {
					break;
				}
			}
			cout << "\nWould you like to do something else or are you finished? Press 1 to choose another option. Press any key to login as another user or logout: ";
			cin >> contS;
			cout << endl;
			if (contS == "1") {
				goto CONT_STUDENT;
			}
			else {
				cout << "\nWould you like to login as another user? Press 1 to login as another user. Press any other key to logout and exit: ";
				cin >> loginChoice;
				if (loginChoice == "1") {
					goto LOGIN;
				}
				else {
					break;
				}
			}
		}
		else if (login == 12) {
			string todoI;
		CONT_INSTRUCTOR:
			string contI;
			cout << "\nWhat would you like to do?" << endl;
			cout << "Press 1 to search all courses." << endl;
			cout << "Press 2 to search courses based on CRN" << endl;
			cout << "Press 3 to print course roster." << endl;
			cout << "Press any other key to logout." << endl;
			cout << "Choice: ";
			cin >> todoI;
			cout << endl;
			if (todoI == "1") {
				searchallCourse(dir);
			}
			else if (todoI == "2") {
				string courseCRN;
				cout << "What is the course CRN: ";
				cin >> courseCRN;
				searchCourse(dir, courseCRN);
			}
			else if (todoI == "3") {
				printRoster(dir);
			}
			else {
				cout << "\nWould you like to login as another user? Press 1 to login as another user. Press any other key to exit: ";
				cin >> loginChoice;
				if (loginChoice == "1") {
					goto LOGIN;
				}
				else {
					break;
				}
			}
			cout << "\nWould you like to do something else or are you finished? Press 1 to choose another option. Press any key to login as another user or logout: ";
			cin >> contI;
			cout << endl;
			if (contI == "1") {
				goto CONT_INSTRUCTOR;
			}
			else {
				cout << "\nWould you like to login as another user? Press 1 to login as another user. Press any other key to logout and exit: ";
				cin >> loginChoice;
				if (loginChoice == "1") {
					goto LOGIN;
				}
				else {
					break;
				}
			}

		}
		else if (login == 13) {
			cout << "admin" << endl;
			string todoA;
		CONT_ADMIN:
			string contA;
			cout << "\nWhat would you like to do?" << endl;
			cout << "Press 1 to search all courses." << endl;
			cout << "Press 2 to search courses based on CRN" << endl;
			cout << "Press 3 to add or remove PEOPLE from the system." << endl;
			cout << "Press 4 to add or remove COURSES from the system." << endl;
			cout << "Press 5 to assign instructors to courses." << endl;
			cout << "Press any other key to logout." << endl;
			cout << "Choice: ";
			cin >> todoA;
			cout << endl;
			if (todoA == "1") {
				searchallCourse(dir);
			}
			else if (todoA == "2") {
				string courseCRN;
				cout << "What is the course CRN: ";
				cin >> courseCRN;
				searchCourse(dir, courseCRN);
			}
			else if (todoA == "3") {
				addorremovePeople(dir);
			}
			else if (todoA == "4") {
				addorremoveCourse(dir);
			}
			else if (todoA == "5") {
				assignInstructor(dir);
			}
			else {
				cout << "\nWould you like to login as another user? Press 1 to login as another user. Press any other key to exit: ";
				cin >> loginChoice;
				if (loginChoice == "1") {
					goto LOGIN;
				}
				else {
					break;
				}
			}
			cout << "\nWould you like to do something else or are you finished? Press 1 to choose another option. Press any key to login as another user or logout: ";
			cin >> contA;
			cout << endl;
			if (contA == "1") {
				goto CONT_ADMIN;
			}
			else {
				cout << "\nWould you like to login as another user? Press 1 to login as another user. Press any other key to logout and exit: ";
				cin >> loginChoice;
				if (loginChoice == "1") {
					goto LOGIN;
				}
				else {
					break;
				}
			}
		}
		else {
			cout << "SYSTEM EXIT!" << endl;
			break;
		}
	}
	//while (r == "1") {
	//	LOGIN:
	//	int login;
	//	string loginChoice;
	//	login = logInOut(dir);
	//	if (login == 11) {
	//		string todoS;
	//	CONT_STUDENT:
	//		string contS;
	//		cout << "\nWhat would you like to do?" << endl;
	//		cout << "Press 1 to search all courses." << endl;
	//		cout << "Press 2 to search courses based on CRN" << endl;
	//		cout << "Press 3 to add or drop courses." << endl;
	//		cout << "Press 4 to print detailed schedule." << endl;
	//		cout << "Press any other key to logout." << endl;
	//		cout << "Choice: ";
	//		cin >> todoS;
	//		cout << endl;
	//		if (todoS == "1") {
	//			searchallCourse(dir);
	//		}
	//		else if (todoS == "2") {
	//			string courseCRN;
	//			cout << "\nWhat is the course CRN: ";
	//			cin >> courseCRN;
	//			searchCourse(dir, courseCRN);
	//		}
	//		else if (todoS == "3") {
	//			addordropCourse(dir);
	//		}
	//		else if (todoS == "4") {
	//			printSchedule(dir);
	//		}
	//		else {
	//			cout << "\nWould you like to login as another user? Press 1 to login as another user. Press any other key to exit: ";
	//			cin >> loginChoice;
	//			if (loginChoice == "1") {
	//				goto LOGIN;
	//			}
	//			else {
	//				break;
	//			}
	//		}
	//		cout << "\nWould you like to do something else or are you finished? Press 1 to choose another option. Press any key to login as another user or logout: ";
	//		cin >> contS;
	//		cout << endl;
	//		if (contS == "1") {
	//			goto CONT_STUDENT;
	//		}
	//		else {
	//			cout << "\nWould you like to login as another user? Press 1 to login as another user. Press any other key to logout and exit: ";
	//			cin >> loginChoice;
	//			if (loginChoice == "1") {
	//				goto LOGIN;
	//			}
	//			else {
	//				break;
	//			}
	//		}
	//	}
	//	else if (login == 12) {
	//		string todoI;
	//	CONT_INSTRUCTOR:
	//		string contI;
	//		cout << "\nWhat would you like to do?" << endl;
	//		cout << "Press 1 to search all courses." << endl;
	//		cout << "Press 2 to search courses based on CRN" << endl;
	//		cout << "Press 3 to print course roster." << endl;
	//		cout << "Press any other key to logout." << endl;
	//		cout << "Choice: ";
	//		cin >> todoI;
	//		cout << endl;
	//		if (todoI == "1") {
	//			searchallCourse(dir);
	//		}
	//		else if (todoI == "2") {
	//			string courseCRN;
	//			cout << "\nWhat is the course CRN: ";
	//			cin >> courseCRN;
	//			searchCourse(dir, courseCRN);
	//		}
	//		else if (todoI == "3") {
	//			printRoster(dir);
	//		}
	//		else {
	//			cout << "\nWould you like to login as another user? Press 1 to login as another user. Press any other key to exit: ";
	//			cin >> loginChoice;
	//			if (loginChoice == "1") {
	//				goto LOGIN;
	//			}
	//			else {
	//				break;
	//			}
	//		}
	//		cout << "\nWould you like to do something else or are you finished? Press 1 to choose another option. Press any key to login as another user or logout: ";
	//		cin >> contI;
	//		cout << endl;
	//		if (contI == "1") {
	//			goto CONT_INSTRUCTOR;
	//		}
	//		else {
	//			cout << "\nWould you like to login as another user? Press 1 to login as another user. Press any other key to logout and exit: ";
	//			cin >> loginChoice;
	//			if (loginChoice == "1") {
	//				goto LOGIN;
	//			}
	//			else {
	//				break;
	//			}
	//		}

	//	}
	//	else if (login == 13) {
	//		cout << "admin" << endl;
	//		string todoA;
	//	CONT_ADMIN:
	//		string contA;
	//		cout << "\nWhat would you like to do?" << endl;
	//		cout << "Press 1 to search all courses." << endl;
	//		cout << "Press 2 to search courses based on CRN" << endl;
	//		cout << "Press 3 to add or remove PEOPLE from the system." << endl;
	//		cout << "Press 4 to add or remove COURSES from the system." << endl;
	//		cout << "Press 5 to assign instructors to courses." << endl;
	//		cout << "Press any other key to logout." << endl;
	//		cout << "Choice: ";
	//		cin >> todoA;
	//		cout << endl;
	//		if (todoA == "1") {
	//			searchallCourse(dir);
	//		}
	//		else if (todoA == "2") {
	//			string courseCRN;
	//			cout << "\nWhat is the course CRN: ";
	//			cin >> courseCRN;
	//			searchCourse(dir, courseCRN);
	//		}
	//		else if (todoA == "3") {
	//			addorremovePeople(dir);
	//		}
	//		else if (todoA == "4") {
	//			addorremoveCourse(dir);
	//		}
	//		else if (todoA == "5") {
	//			assignInstructor(dir);
	//		}
	//		else {
	//			cout << "\nWould you like to login as another user? Press 1 to login as another user. Press any other key to exit: ";
	//			cin >> loginChoice;
	//			if (loginChoice == "1") {
	//				goto LOGIN;
	//			}
	//			else {
	//				break;
	//			}
	//		}
	//		cout << "\nWould you like to do something else or are you finished? Press 1 to choose another option. Press any key to login as another user or logout: ";
	//		cin >> contA;
	//		cout << endl;
	//		if (contA == "1") {
	//			goto CONT_ADMIN;
	//		}
	//		else {
	//			cout << "\nWould you like to login as another user? Press 1 to login as another user. Press any other key to logout and exit: ";
	//			cin >> loginChoice;
	//			if (loginChoice == "1") {
	//				goto LOGIN;
	//			}
	//			else {
	//				//break;
	//				string test = "test";
	//				while (test == "test") {
	//					cout << "TESTING!" << endl;
	//				}
	//			}
	//		}
	//	}
	//	else {
	//		cout << "SYSTEM EXIT!" << endl;
	//		break;
	//	}
	//}
	return 0;
}

static int callBacklogin(void* data, int argc, char** argv, char** azColName) {
	*(string*)data = argv[0];
	return 0;
}

static int callBackAllCourse(void* NotUsed, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		cout << azColName[i] << ": " << argv[i] << endl;
		if (i == 8) {
			cout << endl;
		}
	}
	return 0;
}

static int callBackCourse(void* NotUsed, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		cout << azColName[i] << ": " << argv[i] << endl;
		if (i == 8) {
			cout << endl << endl;
		}
	}

	return 0;
}

static int callBackStudent(void* NotUsed, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		cout << azColName[i] << ": [" << argv[i] << "]  ";
		if (i == 4) {
			cout << endl << endl;;
		}
	}

	return 0;
}

static int callBackcolnum(void* data, int argc, char** argv, char** azColname) {
	*(int*)data = argc;
	return 0;
}

static void createTable(const char* file) {
	sqlite3* db;
	sqlite3_open(file, &db);
	string course = "CREATE TABLE IF NOT EXISTS COURSE("
		"CRN TEXT PRIMARY KEY, "
		"TITLE TEXT NOT NULL, "
		"DEPARTMENT TEXT NOT NULL, "
		"TIME TEXT NOT NULL, "
		"DOW TEXT NOT NULL, "
		"SEMESTER TEXT NOT NULL, "
		"YEAR TEXT NOT NULL, "
		"CREDITS TEXT NOT NULL, "
		"INSTRUCTOR TEXT NOT NULL, "
		"UNIQUE(CRN));";
	string student = "CREATE TABLE IF NOT EXISTS STUDENT("
		"ID TEXT PRIMARY KEY, "
		"FIRSTNAME TEXT NOT NULL, "
		"LASTNAME TEXT NOT NULL, "
		"GRADYEAR TEXT NOT NULL, "
		"MAJOR TEXT NOT NULL, "
		"EMAIL TEXT NOT NULL, "
		"LOGIN TEXT NOT NULL, "
		"PASSWORD TEXT NOT NULL,"
		"UNIQUE(ID));";
	string instructor = "CREATE TABLE IF NOT EXISTS INSTRUCTOR("
		"ID TEXT PRIMARY KEY, "
		"FIRSTNAME TEXT NOT NULL, "
		"LASTNAME TEXT NOT NULL, "
		"TITLE TEXT NOT NULL, "
		"HIREYEAR TEXT NOT NULL, "
		"DEPARTMENT TEXT NOT NULL, "
		"EMAIL TEXT NOT NULL, "
		"LOGIN TEXT NOT NULL, "
		"PASSWORD TEXT NOT NULL, "
		"UNIQUE(ID));";
	string admin = "CREATE TABLE IF NOT EXISTS ADMIN("
		"ID TEXT PRIMARY KEY, "
		"FIRSTNAME TEXT NOT NULL, "
		"LASTNAME TEXT NOT NULL, "
		"TITLE TEXT NOT NULL, "
		"OFFICE TEXT NOT NULL, "
		"EMAIL TEXT NOT NULL, "
		"LOGIN TEXT NOT NULL, "
		"PASSWORD TEXT NOT NULL, "
		"UNIQUE(ID));";
	/*string studentSchedule = "CREATE TABLE IF NOT EXISTS STUDENT_SCHEDULE("
		"ID TEXT PRIMARY KEY, "
		"STUDENT TEXT NOT NULL);";*/
	string student_course = "CREATE TABLE IF NOT EXISTS STUDENT_COURSE("
		"CRN TEXT NOT NULL, "
		"ID TEXT NOT NULL, "
		"FOREIGN KEY(CRN) REFERENCES COURSE(CRN), "
		"FOREIGN KEY(ID) REFERENCES STUDENT(ID));";

	sqlite3_exec(db, course.c_str(), NULL, NULL, NULL);
	sqlite3_exec(db, student.c_str(), NULL, NULL, NULL);
	sqlite3_exec(db, instructor.c_str(), NULL, NULL, NULL);
	sqlite3_exec(db, admin.c_str(), NULL, NULL, NULL);
	/*sqlite3_exec(db, studentSchedule.c_str(), NULL, NULL, NULL);*/
	sqlite3_exec(db, student_course.c_str(), NULL, NULL, NULL);
	sqlite3_close(db);
}

static void populateTable(const char* file) {
	sqlite3* db;
	sqlite3_open(file, &db);

	int studentNum = 12;
	string studentID[] = { "10001", "10002", "10003", "10004", "10005", "10006", "10007", "10008", "10009", "10010", "10011", "10012" };
	string studentName[] = { "Isaac", "Marie","Nikola","Thomas","John","Grace","Mae","Mark","Michael","Ada","Tom","Tyler" };
	string studentSname[] = { "Newton","Curie","Tesla","Edison","von Neumann","Hopper","Jemison","Dean","Faraday","Lovelace","Hardy","Clayton" };
	string studentGradyear[] = { "1668", "1903" ,"1878","1879","1923","1928","1981","1979","1812","1832","1923","1936" };
	string studentMajor[] = { "BSAS", "BSAS","BSEE", "BSEE", "BSCO", "BCOS", "BSCH", "BSCO", "BSAS", "BCOS", "BSCH", "BSCO" };
	string studentEmail[] = { "newtoni", "curiem" ,"telsan","notcool","vonneumannj","hopperg","jemisonm","deanm","faradaym","lovelacea","hardyt","claytont" };
	string studentLogin[] = { "isaacn", "mariec" ,"nikolat","thomase","johnvn","graceh","maej","markd","michaelf","adal","tomh","tylerc" };
	string studentPassword[] = { "10001n", "10002c", "10003t", "10004e", "10005vn", "10006h", "10007j", "10008d", "10009f", "10010l", "10011h", "10012c" };

	for (int i = 0; i < studentNum; i++) {
		string student("INSERT OR IGNORE INTO STUDENT (ID, FIRSTNAME, LASTNAME, GRADYEAR, MAJOR, EMAIL, LOGIN, PASSWORD)"
			"VALUES('" + studentID[i] + "', '" + studentName[i] + "', '" + studentSname[i] + "', '" + studentGradyear[i] + "', '" + studentMajor[i] + "', '" + studentEmail[i] + "', '" + studentLogin[i] + "', '" + studentPassword[i] + "');");
		sqlite3_exec(db, student.c_str(), NULL, NULL, NULL);
	}

	int courseNum = 5;
	string courseCRN[] = { "33320", "33179", "32966", "33416", "33253" };
	string courseTitle[] = { "GENERAL CHEMISTRY I", "SOLID STATE DEVICES", "MEDICAL ROBOTICS & ASSISTIVE TECHNOLOGY", "MANUFACTURING PROCESSES", "PSYCHOLOGY OF LEADERSHIP" };
	string courseDep[] = { "Sciences", "Electrical & Comp Engineering", "Biomedical Engineering", "Mechanical Engineering", "Humanities Social Sciences" };
	string courseTime[] = { "3:30 pm - 4:50 pm", "2:00 pm - 3:20 pm", "8:00 am - 9:20 am", "10:00 am - 11:50 am", "01:00 pm - 02:50 pm" };
	string courseDOW[] = { "MW","WF", "TR", "F", "MW" };
	string courseSemester[] = { "Summer", "Summer", "Summer", "Summer", "Summer" };
	string courseYear[] = { "2022", "2022", "2022", "2022", "2022" };
	string courseCredits[] = { "4", "3", "4", "4", "4" };
	string courseInstructor[] = { "Michael T Tylinski", "Yugu Yang-Keathley", "Uri Feldman", "Michael Ryan Cameron", "Adam Payne" };

	for (int i = 0; i < courseNum; i++) {
		string course("INSERT OR IGNORE INTO COURSE (CRN, TITLE, DEPARTMENT, TIME, DOW, SEMESTER, YEAR, CREDITS, INSTRUCTOR)"
			"VALUES('" + courseCRN[i] + "', '" + courseTitle[i] + "', '" + courseDep[i] + "', '" + courseTime[i] + "', '" + courseDOW[i] + "', '" + courseSemester[i] + "', '" + courseYear[i] + "', '" + courseCredits[i] + "', '" + courseInstructor[i] + "');");
		sqlite3_exec(db, course.c_str(), NULL, NULL, NULL);
	}

	int instructorNum = 5;
	string instructorID[] = { "20001", "20002", "20003", "20004", "20005" };
	string instructorName[] = { "Joseph", "Nelson", "Galileo", "Katie", "Daniel" };
	string instructorSname[] = { "Fourier", "Patrick", "Galilei", "Bouman", "Bernoulli" };
	string instructorTitle[] = { "Full Prof.", "Full Prof.", "Full Prof.", "Associate Prof.", "Associate Prof." };
	string instructorHY[] = { "1820", "1994", "1600", "2019", "1760" };
	string instructorDep[] = { "Electrical & Comp Engineering", "Humanities Social Sciences", "Sciences", "Electrical & Comp Engineering", "Mechanical Engineering" };
	string instructorEmail[] = { "fourierj", "patrickn", "galileig", "boumank", "bernoullid" };
	string instructorLogin[] = { "josephf", "nelsonp", "galileog", "katieb", "danielb" };
	string instructorPassword[] = { "20001f", "20002p", "20003g", "20004b", "20005b" };

	for (int i = 0; i < instructorNum; i++) {
		string instructor("INSERT OR REPLACE INTO INSTRUCTOR (ID, FIRSTNAME, LASTNAME, TITLE, HIREYEAR, DEPARTMENT, EMAIL, LOGIN, PASSWORD)"
			"VALUES ('" + instructorID[i] + "','" + instructorName[i] + "','" + instructorSname[i] + "','" + instructorTitle[i] + "','" + instructorHY[i] + "','" + instructorDep[i] + "','" + instructorEmail[i] + "','" + instructorLogin[i] + "','" + instructorPassword[i] + "'); ");
		sqlite3_exec(db, instructor.c_str(), NULL, NULL, NULL);
	}

	int adminNum = 2;
	string adminID[] = { "30001","30002" };
	string adminName[] = { "Margaret","Vera" };
	string adminSname[] = { "Hamilton","Rubin" };
	string adminTitle[] = { "President","Vice-President" };
	string adminOffice[] = { "Dobbs 1600","Wentworth 101" };
	string adminEmail[] = { "hamiltonm","rubinv" };
	string adminLogin[] = { "margareth","verar" };
	string adminPassword[] = { "30001h","30002r" };

	for (int i = 0; i < adminNum; i++) {
		string admin("INSERT OR IGNORE INTO ADMIN (ID, FIRSTNAME, LASTNAME, TITLE, OFFICE, EMAIL, LOGIN, PASSWORD)"
			"VALUES ('" + adminID[i] + "','" + adminName[i] + "','" + adminSname[i] + "','" + adminTitle[i] + "','" + adminOffice[i] + "','" + adminEmail[i] + "','" + adminLogin[i] + "','" + adminPassword[i] + "');");
		sqlite3_exec(db, admin.c_str(), NULL, NULL, NULL);
	}
	sqlite3_close(db);
}

static int logInOut(const char* file) {
	sqlite3* db;
	sqlite3_open(file, &db);

	int role;
	string username;
	string password;
	string systemUsername;
	string systemPassword;
	string inputUsername;
	string inputPassword;

	cout << "Please specify your role: Press 1 for Student. Press 2 for Instructor. Press 3 for Admin." << endl;
	cout << "Role: ";
	cin >> role;

	cout << "\nPlease enter your ID: ";
	cin >> inputID;
	for (int j = 0; j < 5; j++) {
		cout << "\nPlease enter your username: ";
		cin >> inputUsername;
		if (role == 1) {
			username = "SELECT LOGIN FROM STUDENT WHERE ID = '" + inputID + "';";
		}
		else if (role == 2) {
			username = "SELECT LOGIN FROM INSTRUCTOR WHERE ID = '" + inputID + "';";
		}
		else if (role == 3) {
			username = "SELECT LOGIN FROM ADMIN WHERE ID = '" + inputID + "';";
		}
		else {
			cout << "\nInvalid role!" << endl;
			continue;
		}
		sqlite3_exec(db, username.c_str(), callBacklogin, &systemUsername, NULL);
		if (inputUsername == systemUsername) {
			for (int k = 0; k < 5; k++) {
				cout << "Please enter you password: ";
				cin >> inputPassword;
				if (role == 1) {
					password = "SELECT PASSWORD FROM STUDENT WHERE ID = '" + inputID + "';";
				}
				else if (role == 2) {
					password = "SELECT PASSWORD FROM INSTRUCTOR WHERE ID = '" + inputID + "';";
				}
				else if (role == 3) {
					password = "SELECT PASSWORD FROM ADMIN WHERE ID = '" + inputID + "';";
				}
				else {
					cout << "\nInvalid Role!" << endl;
					continue;
				}
				sqlite3_exec(db, password.c_str(), callBacklogin, &systemPassword, NULL);
				if (inputPassword == systemPassword) {

					cout << "\nLogin Successful!" << endl;
					if (role == 1) {
						string studentName = getUsername(db, role, inputID);
						cout << "\nLogged in as Student!" << endl;
						cout << "Student name: [" << studentName << "]" << endl;

						return 11;
						break;
					}
					else if (role == 2) {
						string instructorName = getUsername(db, role, inputID);
						cout << "\nLogged in as Instructor!" << endl;
						cout << "Instructor name: [" << instructorName << "]" << endl;

						return 12;
						break;
					}
					else if (role == 3) {
						string adminName = getUsername(db, role, inputID);
						cout << "\nLogged in as Admin!" << endl;
						cout << "Admin name: [" << adminName << "]" << endl;

						return 13;
						break;
					}
				}
				else {
					cout << "\nIncorrect Password!" << endl;
					if (k == 4) {
						cout << "Maximum Attempts Reached!" << endl;
						return 0;
						break;
					}
				}
			}
		}
		else {
			cout << "\nIncorrect Username!" << endl;
			if (j == 4) {
				cout << "Maximum Attempts Reached!" << endl;
				return 0;
				break;
			}
		}
	}

	sqlite3_close(db);
}

static void addorremovePeople(const char* file) {
	sqlite3* db;
	sqlite3_open(file, &db);

	string choice;
	string role;
	string studentInfoName[8] = { "ID: ", "First Name: ", "Last Name: ", "Graduation Year: ", "Major: ", "Email: ", "Login: ", "Password: " };
	string instructorInfoName[9] = { "ID: ", "First Name: ", "Last Name: ", "Title: ", "Year of Hire: ", "Department: ", "Email: ", "Login: ", "Password: " };
	string adminInfoName[8] = { "ID: ", "First Name: ", "Last Name: ", "Title: ", "Office: ", "Email: ", "Login: ", "Password: " };
	string studentInfo[8];
	string instructorInfo[9];
	string adminInfo[8];

	string contO = "1";
	while (contO == "1") {
		cout << "Would you like to ADD or REMOVE people?" << endl;
		cout << "Press 1 to Add. Press 2 to Remove. Press any other key to exit: ";
		cin >> choice;
		if (choice == "1") {
			string contR = "1";
			while (contR == "1") {
				cout << "What role is the person you are trying to ADD? (Student, Instructor, Admin)" << endl;
				cout << "Press 1 for Student. Press 2 for Instructor. Press 3 for Admin. Press any other key to exit: ";
				cin >> role;
				if (role == "1") {
					string contS = "1";
					while (contS == "1") {
						cout << "Please enter the appropriate information: " << endl;
						for (int i = 0; i < 8; i++) {
							cout << studentInfoName[i];
							cin >> studentInfo[i];
						}
						string add("INSERT INTO STUDENT (ID, FIRSTNAME, LASTNAME, GRADYEAR, MAJOR, EMAIL, LOGIN, PASSWORD)"
							"VALUES('" + studentInfo[0] + "', '" + studentInfo[1] + "', '" + studentInfo[2] + "', '" + studentInfo[3] + "', '" + studentInfo[4] + "', '" + studentInfo[5] + "', '" + studentInfo[6] + "', '" + studentInfo[7] + "');");
						sqlite3_exec(db, add.c_str(), NULL, NULL, NULL);
						cout << "Sucessfully added [" << studentInfo[1] << " " << studentInfo[2] << "] to the system as a Student!" << endl;
						cout << "Would you like to add more students. Press 1 to add more students. Press any other key to add someone else, remove a person or exit: ";
						cin >> contS;
					}
				}
				else if (role == "2") {
					string contI = "1";
					while (contI == "1") {
						cout << "Please enter the appropriate information: " << endl;
						for (int i = 0; i < 9; i++) {
							cout << instructorInfoName[i];
							cin >> instructorInfo[i];
						}
						string add("INSERT INTO INSTRUCTOR (ID, FIRSTNAME, LASTNAME, TITLE, HIREYEAR, DEPARTMENT, EMAIL, LOGIN, PASSWORD)"
							"VALUES('" + instructorInfo[0] + "', '" + instructorInfo[1] + "', '" + instructorInfo[2] + "', '" + instructorInfo[3] + "', '" + instructorInfo[4] + "', '" + instructorInfo[5] + "', '" + instructorInfo[6] + "', '" + instructorInfo[7] + "', '" + instructorInfo[8] + "');");
						sqlite3_exec(db, add.c_str(), NULL, NULL, NULL);
						cout << "Successfully added [" << instructorInfo[1] << " " << instructorInfo[2] << "] to the system as an Instructor" << endl;
						cout << "Would you like to add more instructors? Press 1 to add more Instructors. Press any other key to add someone else, remove a person or exit: ";
						cin >> contI;
					}
				}
				else if (role == "3") {
					string contA = "1";
					while (contA == "1") {
						cout << "Please enter the appropriate information: " << endl;
						for (int i = 0; i < 8; i++) {
							cout << adminInfoName[i];
							cin >> adminInfo[i];
						}
						string add("INSERT INTO STUDENT (ID, FIRSTNAME, LASTNAME, TITLE, OFFICE, EMAIL, LOGIN, PASSWORD)"
							"VALUES('" + adminInfo[0] + "', '" + adminInfo[1] + "', '" + adminInfo[2] + "', '" + adminInfo[3] + "', '" + adminInfo[4] + "', '" + adminInfo[5] + "', '" + adminInfo[6] + "', '" + adminInfo[7] + "');");
						sqlite3_exec(db, add.c_str(), NULL, NULL, NULL);
						cout << "Successfully added [" << adminInfo[1] << " " << adminInfo[2] << "] to the system as an Admin!" << endl;
						cout << "Would you like to add more Admins? Press 1 to add more Admins. Press any other key to add someone else, remove a person or exit: ";
						cin >> contA;
					}
				}
				else {
					contR = role;
				}
			}
		}
		else if (choice == "2") {
			string contR2 = "1";
			while (contR2 == "1") {
				string id;
				cout << "Please enter the role of the person you are trying to REMOVE from the database?" << endl;
				cout << "Press 1 for Student. Press 2 for Instructor. Press 3 for Admin. Press any other key to exit: ";
				cin >> role;
				if (role == "1") {
					string contS = "1";
					while (contS == "1") {
						cout << "What is their ID?" << endl;
						cout << "ID: ";
						cin >> id;
						string student = getUsername(db, 1, id);
						string remove("DELETE FROM STUDENT WHERE ID = '" + id + "';");
						sqlite3_exec(db, remove.c_str(), NULL, NULL, NULL);
						cout << "Successfully removed [" << student << "] from the system!" << endl;
						cout << "Would you like to remove more students? Press 1 to remove more students. Press any other key to remove someone else, add people or exit: ";
						cin >> contS;
					}
					continue;
				}
				else if (role == "2") {
					string contI = "1";
					while (contI == "1") {
						cout << "What is their ID?" << endl;
						cout << "ID: ";
						cin >> id;
						string instructor = getUsername(db, 2, id);
						string remove("DELETE FROM INSTRUCTOR WHERE ID = '" + id + "';");
						sqlite3_exec(db, remove.c_str(), NULL, NULL, NULL);
						cout << "Successfully removed [" << instructor << "] from the system!" << endl;
						cout << "Would you like to remove more instructors? Press 1 to remove more instructors. Press any other key to remove someone else, add people or exit: ";
						cin >> contI;
					}
					continue;
				}
				else if (role == "3") {
					string contA = "1";
					while (contA == "1") {
						cout << "What is their ID?" << endl;
						cout << "ID: ";
						cin >> id;
						string admin = getUsername(db, 3, id);
						string remove("DELETE FROM ADMIN WHERE ID = '" + id + "';");
						sqlite3_exec(db, remove.c_str(), NULL, NULL, NULL);
						cout << "Successfully removed [" << admin << "] from the system!" << endl;
						cout << "Would you like to remove more admins? Press 1 to remove more admins. Press any other key to remove someone else, add people or exit: ";
						cin >> contA;
					}
					continue;
				}
				else {
					contR2 = role;
				}
			}
		}
		else {
			contO = choice;
		}
	}

	sqlite3_close(db);
}

static void addorremoveCourse(const char* file) {
	sqlite3* db;
	sqlite3_open(file, &db);

	string choice;
	string courseInfoName[9] = { "CRN: ", "Title: ", "Department: ", "Time: ", "Day(s) of Week: ", "Semester: ", "Year: ", "Credits: ", "Instructor: "};
	string courseInfo[9];

	string contA = "1";
	while (contA == "1") {
		cout << "Would you like to ADD or REMOVE Courses?" << endl;
		cout << "Press 1 to Add. Press 2 to Remove. Press any other key to exit: ";
		cin >> choice;
		if (choice == "1") {
			string cont = "1";
			while (cont == "1") {
				cout << "Please enter the appropriate information:" << endl;
				for (int i = 0; i < 9; i++) {
					cout << courseInfoName[i];
					cin >> courseInfo[i];
				}
				string add("INSERT INTO COURSE (CRN, TITLE, DEPARTMENT, TIME, DOW, SEMESTER, YEAR, CREDITS, INSTRUCTOR)"
					"VALUES('" + courseInfo[0] + "', '" + courseInfo[1] + "', '" + courseInfo[2] + "', '" + courseInfo[3] + "', '" + courseInfo[4] + "', '" + courseInfo[5] + "', '" + courseInfo[6] + "', '" + courseInfo[7] + "', '" + courseInfo[8] + "');");
				sqlite3_exec(db, add.c_str(), NULL, NULL, NULL);
				cout << "Successfully added course to system!" << endl;
				cout << "Would you like to add more courses? Press 1 to add more. Press any other key to remove or exit: ";
				cin >> cont;
			}
		}
		else if (choice == "2") {
			string cont = "1";
			while (cont == "1") {
				string CRN;
				cout << "What is the CRN of the course you want to remove?" << endl;
				cout << "CRN: ";
				cin >> CRN;
				string remove("DELETE FROM COURSE WHERE CRN = '" + CRN + "';");
				sqlite3_exec(db, remove.c_str(), NULL, NULL, NULL);
				cout << "Successfully removed course with CRN [" << CRN << "] from the system!" << endl;
				cout << "Would you like to remove more courses. Press 1 to remove more courses. Press any other key to add a course or exit: ";
				cin >> cont;
			}
		}
		else {
			contA = choice;
		}
	}

	sqlite3_close(db);
}

static void addordropCourse(const char* file) {
	sqlite3* db;
	sqlite3_open(file, &db);
	string studentName = getUsername(db, 1, inputID);
	string choice;
	string conta = "1";
	while (conta == "1") {
		cout << "Would you like to add or drop a course? Press 1 to add. Press 2 to drop. Press any other key to exit: ";
		cin >> choice;
		if (choice == "1") {
			string cont = "1";
			while (cont == "1") {
				string inputCRN;
				string systemCRN;
				cout << "What is the CRN of the course you want to add?" << endl;
				cout << "CRN: ";
				cin >> inputCRN;
				string getCourse("SELECT * FROM COURSE WHERE CRN = '" + inputCRN + "';");
				sqlite3_exec(db, getCourse.c_str(), callBacklogin, &systemCRN, NULL);
				if (inputCRN != systemCRN) {
					cout << "Course with CRN: " << inputCRN << " does not exist!" << endl;
					cout << "Would you like to try again? Press 1 to try again. Press any other key to exit: ";
					cin >> cont;
					continue;
				}
				else {
					string systemcheckCRN;
					string systemcheckID;
					string rowid;
					string checkID("SELECT ID FROM STUDENT_COURSE WHERE CRN = '" + systemCRN + "';");
					sqlite3_exec(db, checkID.c_str(), callBacklogin, &systemcheckID, NULL);
					string checkRowID("SELECT ROWID FROM STUDENT_COURSE WHERE CRN = '" + systemCRN + "';");
					sqlite3_exec(db, checkRowID.c_str(), callBacklogin, &rowid, NULL);
					string checkCRN("SELECT CRN FROM STUDENT_COURSE WHERE ROWID = '" + rowid + "';");
					sqlite3_exec(db, checkCRN.c_str(), callBacklogin, &systemcheckCRN, NULL);

					if (systemcheckCRN == systemCRN && systemcheckID == inputID) {
						cout << "You've already registered for this course!" << endl;
						cout << "Would you like to try again? Press 1 to try again. Press any other key to exit: ";
						cin >> cont;
						continue;
					}
					else {
						string addCourse("INSERT INTO STUDENT_COURSE (CRN, ID) VALUES ('" + systemCRN + "', '" + inputID + "');");
						sqlite3_exec(db, addCourse.c_str(), NULL, NULL, NULL);
						string courseTitle;
						string getCourse("SELECT TITLE FROM COURSE WHERE CRN = '" + systemCRN + "';");
						sqlite3_exec(db, getCourse.c_str(), callBacklogin, &courseTitle, NULL);
						cout << "Added " << courseTitle << " to " << studentName << "'s schedule!" << endl;
						cout << "Would you like to add more courses? Press 1 to add more. Press any other key to drop a course or exit: ";
						cin >> cont;
					}
				}
			}
		}
		else if (choice == "2") {
			string cont = "1";
			while (cont == "1") {
				string inputCRN;
				cout << "What is the CRN of the course you want to drop?" << endl;
				cout << "CRN: ";
				cin >> inputCRN;
				string rowid;
				string systemRowid;
				string systemCRN;
				string getRowid("SELECT ROWID FROM STUDENT_COURSE WHERE CRN = '" + inputCRN + "' AND ID = '" + inputID + "';");
				sqlite3_exec(db, getRowid.c_str(), callBacklogin, &rowid, NULL);
				string getCRN("SELECT CRN FROM STUDENT_COURSE WHERE ROWID = '" + rowid + "';");
				sqlite3_exec(db, getCRN.c_str(), callBacklogin, &systemCRN, NULL);
				if (inputCRN == systemCRN) {
					string remove("DELETE FROM STUDENT_COURSE WHERE ROWID = '" + rowid + "';");
					sqlite3_exec(db, remove.c_str(), NULL, NULL, NULL);
					string thisCourse = getCourse(db, inputCRN);
					cout << "Successfully dropped [" << thisCourse << "] from [" << studentName << "]'s schedule." << endl;
					cout << "Would you like to drop more courses? Press 1 to drop more courses. Press any other key to add a course or exit: ";
					cin >> cont;
				}
				else {
					cout << "You are not registered with course with CRN [" << inputCRN << "]." << endl;
					cout << "Would you like to try again? Press 1 to try again. Press any other key to exit: ";
					cin >> cont;
				}
			}
		}
		else {
			conta = choice;
		}
	}
}

static void searchallCourse(const char* file) {
	sqlite3* db;
	sqlite3_open(file, &db);
	string getCourse("SELECT * FROM COURSE;");
	sqlite3_exec(db, getCourse.c_str(), callBackAllCourse, NULL, NULL);

	sqlite3_close(db);
}

static void searchCourse(const char* file, string crn) {
	sqlite3* db;
	sqlite3_open(file, &db);
	string getCRN("SELECT * FROM COURSE WHERE CRN = '" + crn + "';");
	sqlite3_exec(db, getCRN.c_str(), callBackCourse, NULL, NULL);

	sqlite3_close(db);
}

static void assignInstructor(const char* file) {
	sqlite3* db;
	sqlite3_open(file, &db);
	string cont = "1";
	while (cont == "1") {
		string Instructor;
		string ID;
		string systemID;
		string CRN;
		string systemCRN;
		cout << "What is the ID of the instructor you want to assign to a course?" << endl;
		cout << "ID: ";
		cin >> ID;

		string checkID("SELECT * FROM INSTRUCTOR WHERE ID = '" + ID + "';");
		sqlite3_exec(db, checkID.c_str(), callBacklogin, &systemID, NULL);
		if (ID == systemID) {
			Instructor = getUsername(db, 2, ID);
			cout << "What is the CRN of the course this Instructor is assigned to?" << endl;
			cout << "CRN: ";
			cin >> CRN;

			string checkCRN("SELECT * FROM COURSE WHERE CRN = '" + CRN + "';");
			sqlite3_exec(db, checkCRN.c_str(), callBacklogin, &systemCRN, NULL);
			if (CRN == systemCRN) {
				string courseDep;
				string systemCoursedep;
				string instructorDep;
				string systemInstructordep;
				string checkCoursedep("SELECT DEPARTMENT FROM COURSE WHERE CRN = '" + CRN + "';");
				sqlite3_exec(db, checkCoursedep.c_str(), callBacklogin, &systemCoursedep, NULL);
				string checkInstructordep("SELECT DEPARTMENT FROM INSTRUCTOR WHERE ID = '" + ID + "';");
				sqlite3_exec(db, checkInstructordep.c_str(), callBacklogin, &systemInstructordep, NULL);
				if (systemCoursedep == systemInstructordep) {
					string assign("UPDATE COURSE SET INSTRUCTOR = '" + Instructor + "' WHERE CRN = '" + CRN + "';");
					sqlite3_exec(db, assign.c_str(), NULL, NULL, NULL);
					cout << "You assigned Instructor [" << Instructor << "] to course with CRN [" << CRN << "]" << endl;
					cout << "Would you like to assign another Instructor? Press 1 if Yes. Press any other key to exit: ";
					cin >> cont;
				}
				else {
					cout << "Course with CRN [" << CRN << "] does not lie in Instructor [" << Instructor << "]'s department." << endl;
					cout << "Press 1 to try again. Press any other key to exit: ";
					cin >> cont;
				}
			}
			else {
				cout << "No course exists with the CRN: [" << CRN << "]" << endl;
				cout << "Press 1 to try again. Press any other key to exit: ";
				cin >> cont;
			}
		}
		else {
			cout << "No Instructor exists with the ID: [" << ID << "]" << endl;
			cout << "Press 1 to try again. Press any other key to exit: ";
			cin >> cont;
		}
	}

	sqlite3_close(db);
}

static void printSchedule(const char* file) {
	sqlite3* db;
	sqlite3_open(file, &db);

	vector<string> schedule{};
	string studentRowcount;
	string getRowcountS("SELECT COUNT(*) FROM STUDENT_COURSE;");
	sqlite3_exec(db, getRowcountS.c_str(), callBacklogin, &studentRowcount, NULL);
	int studentRowcountint = stoi(studentRowcount);
	for (int i = 0; i < studentRowcountint; i++) {
		string studentRowcountstring = to_string(i);
		string CRN;
		string getSchedule("SELECT CRN FROM STUDENT_COURSE WHERE ID = '" + inputID + "' AND ROWID = '" + studentRowcountstring + "';");
		sqlite3_exec(db, getSchedule.c_str(), callBacklogin, &CRN, NULL);

		if (CRN != "") {
			if (find(schedule.begin(), schedule.end(), CRN) == schedule.end()) { //CRN not in schedule, add CRN
				schedule.push_back(CRN);
			}
		}
	}
	for (auto i = schedule.begin(); i < schedule.end(); i++) {
		string getCourse("SELECT * FROM COURSE WHERE CRN = '" + *i + "';");
		sqlite3_exec(db, getCourse.c_str(), callBackCourse, NULL, NULL);
	}

	sqlite3_close(db);
}

static void printRoster(const char* file) {
	sqlite3* db;
	sqlite3_open(file, &db);

	vector<string> courses{};
	string courseRowcount;
	string getCourseRC("SELECT COUNT(*) FROM COURSE;");
	sqlite3_exec(db, getCourseRC.c_str(), callBacklogin, &courseRowcount, NULL);

	int courseRowcountint = stoi(courseRowcount);
	string instructor = getUsername(db, 2, inputID);
	string CRN;
	for (int i = 1; i < courseRowcountint + 1; i++) {
		string courseRowcountstring = to_string(i);
		string getCRN("SELECT CRN FROM COURSE WHERE INSTRUCTOR = '" + instructor + "' AND ROWID = '" + courseRowcountstring + "';");
		sqlite3_exec(db, getCRN.c_str(), callBacklogin, &CRN, NULL);

		if (CRN != "") {
			if (find(courses.begin(), courses.end(), CRN) == courses.end()) { //CRN not in course, add CRN
				courses.push_back(CRN);
			}
		}
	}

	vector<string> students{};
	string scourseRowcount;
	string getRowcountSC("SELECT COUNT(*) FROM STUDENT_COURSE;");
	string ID;
	sqlite3_exec(db, getRowcountSC.c_str(), callBacklogin, &scourseRowcount, NULL);

	int scourseRowcountint = stoi(scourseRowcount);
	for (auto i = courses.begin(); i < courses.end(); i++) {
		for (int j = 1; j < scourseRowcountint + 3 ; j++) {

			string scourseRowcountstring = to_string(j);
			string getStudentID("SELECT ID FROM STUDENT_COURSE WHERE CRN = '" + *i + "' AND ROWID = '" + scourseRowcountstring + "';");
			sqlite3_exec(db, getStudentID.c_str(), callBacklogin, &ID, NULL);

			if (ID != "") {
				if (find(students.begin(), students.end(), ID) == students.end()) { //ID not in student, add ID
					students.push_back(ID);
				}
			}
		}

		string courseName;
		string getCourseName("SELECT TITLE FROM COURSE WHERE CRN = '" + *i + "';");
		sqlite3_exec(db, getCourseName.c_str(), callBacklogin, &courseName, NULL);
		cout << courseName << " ROSTER: " << endl;
		for (auto j = students.begin(); j < students.end(); j++) {
			string getStudent("SELECT FIRSTNAME, LASTNAME, GRADYEAR, MAJOR, EMAIL FROM STUDENT WHERE ID = '" + *j + "';");
			sqlite3_exec(db, getStudent.c_str(), callBackStudent, NULL, NULL);
		}
		students.clear();
	}

	sqlite3_close(db);
}

static string getColName(sqlite3* db) {
	int colNameNum;
	int crnNum;
	string colName;
	string getcrnNum("SELECT * FROM STUDENT_SCHEDULE;");
	sqlite3_exec(db, getcrnNum.c_str(), callBackcolnum, &crnNum, NULL);
	colNameNum = crnNum - 1;
	colName = "CRN" + to_string(colNameNum);
	return colName;
}

static string getUsername(sqlite3* db, int user, string ID) {
	string userRole;
	string userFname;
	string userLname;
	string userName;
	if (user == 1) {
		userRole = "STUDENT";
	}
	else if (user == 2) {
		userRole = "INSTRUCTOR";
	}
	else if (user == 3) {
		userRole = "ADMIN";
	}

	string getFname("SELECT FIRSTNAME FROM '" + userRole + "' WHERE ID = '" + ID + "'; ");
	string getLname("SELECT LASTNAME FROM '" + userRole + "' WHERE ID = '" + ID + "';");
	sqlite3_exec(db, getFname.c_str(), callBacklogin, &userFname, NULL);
	sqlite3_exec(db, getLname.c_str(), callBacklogin, &userLname, NULL);
	userName = userFname + " " + userLname;
	return userName;
}

static string getCourse(sqlite3* db, string CRN) {
	string courseTitle;
	string getCourse("SELECT TITLE FROM COURSE WHERE CRN = '" + CRN + "';");
	sqlite3_exec(db, getCourse.c_str(), callBacklogin, &courseTitle, NULL);
	return courseTitle;
}