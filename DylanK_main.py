import sqlite3
import string
import pyautogui
import time

active = 1


def automatic():
    testchoice = input("Please Enter Which Test To Use: 1.Add/Remove Course(Student) 2.Assemble Course Roster("
                       "instructor) 3. Add/Remove Courses From System 4. Search For A Course 5.Search Courses From Para"
                       "meters 6.Switch To Manual\n")

    if testchoice == "1":  # Add/Remove From Schedule
        pyautogui.typewrite("1")  # User Type
        pyautogui.press("enter")  # Confirm
        time.sleep(1)
        pyautogui.typewrite("Mae")  # Username
        pyautogui.press("enter")  # Confirm
        time.sleep(1)
        pyautogui.typewrite("12345")  # Password
        pyautogui.press("enter")  # Confirm
        time.sleep(1)
        pyautogui.typewrite("3")  # Tell Software to Remove Course
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("9781")  # Remove Physics Class With ID 9871
        pyautogui.press("enter")  # Confirm
        time.sleep(1)
        pyautogui.typewrite("5")  # Logout
        pyautogui.press("enter")  # Confirm

    if testchoice == "2":  # Assemble roster
        pyautogui.typewrite("2")  # User Type
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("Joseph")  # Username
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("12345")  # Password
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("3")  # Function Choice
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("1000")  # Entering CRN
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("4")  # Entering CRN
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("5")  # Logout
        pyautogui.press("enter")  # Confirm

    if testchoice == "3":  # Change available courses
        pyautogui.typewrite("3")  # User Type
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("Vera")  # Username
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("12345")  # Password
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("3")  # Function
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("remove")  # Saying to remove a course
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("History")  # Password
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("4")  # Logout
        pyautogui.press("enter")  # Confirm

    if testchoice == "4":  # Search For A Course(Admin)
        pyautogui.typewrite("3")  # User Type
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("Vera")  # Username
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("12345")  # Password
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("2")  # Search
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("4")  # Logout
        pyautogui.press("enter")  # Confirm

    if testchoice == "5":  # Search A Course With Parameters(Student)
        pyautogui.typewrite("1")  # User Type
        pyautogui.press("enter")  # Confirm
        time.sleep(1)
        pyautogui.typewrite("Mark")  # Username
        pyautogui.press("enter")  # Confirm
        time.sleep(1)
        pyautogui.typewrite("12345")  # Password
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("0")  # Function
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("Department")  # Function
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("BSME")  # Function
        pyautogui.press("enter")  # Confirm
        pyautogui.typewrite("5")  # Logout
        pyautogui.press("enter")  # Confirm

    if testchoice == "6":
        return 0


def student(username):
    choicest = 0
    while (choicest != 5):
        choicest = input("Hello student, Choose a function\n0.Search Courses with Condition 1.Search courses 2.Add "
                         "Courses 3.Drop Course 4.Print Schedule 5.Logout\n")
        choicest = int(choicest)
        if choicest == 0:
            condition = ""
            condition = input("Search by one of the following: Title, Department, Time, Day(s) Held, Semester,"
                              "Year, Credits, Teacher, Roster \n")
            condition.capitalize()
            subcondition = ""
            subcondition = input("Enter the value for the condition: ")
            sqlcommand = "SELECT TITLE FROM COURSES WHERE " + condition + " = '" + subcondition + "';"
            cursor.execute(sqlcommand)
            courseswcond = cursor.fetchall()
            sqlcommand = "SELECT CRN FROM COURSES WHERE " + condition + " = '" + subcondition + "';"
            cursor.execute(sqlcommand)
            courseswcond = cursor.fetchall()
            courseswcond = courseswcond[0]

            print("Course CRN: ")
            print(courseswcond[0])
        if choicest == 1:
            sqlcommand = "SELECT TITLE FROM COURSES;"
            cursor.execute(sqlcommand)
            courses = cursor.fetchall()
            print(courses)
        if choicest == 2:  # Add course
            studentid = ""
            sqlcommand = "SELECT ID FROM STUDENT WHERE NAME = '" + username + "';"
            cursor.execute(sqlcommand)
            studentid = cursor.fetchall()
            studentid = studentid[0]

            chngesched = input("Enter the course number to add to your schedule: ")
            chngesched = str(chngesched)

            sqlcommand = "SELECT TIME FROM Courses WHERE CRN = '" + chngesched + "';"
            cursor.execute(sqlcommand)
            time = cursor.fetchall()
            time = time[0]

            sqlcommand = "SELECT Schedule FROM STUDENT WHERE NAME = '" + username + "';"
            cursor.execute(sqlcommand)
            schedule = cursor.fetchall()
            schedule = schedule[0]
            sqlcommand = "SELECT TIME FROM Courses WHERE CRN = '" + str(schedule[0]) + "';"
            cursor.execute(sqlcommand)
            timenew = cursor.fetchall()
            timenew = timenew[0]

            if timenew == time:
                print("Sorry Your Courses Conflict")
            else:
                studentid = str(studentid[0])
                sqlcommand = ("INSERT INTO Courses (ROSTER) VALUES(" + studentid + ") ;")
                cursor.execute(sqlcommand)
                sqliteConnection.commit()
                sqlcommand = "UPDATE STUDENT SET SCHEDULE = '" + chngesched + "' WHERE NAME = '" + username + "';"
                cursor.execute(sqlcommand)
                sqliteConnection.commit()

        if choicest == 3:  # Remove course
            studentid = ""
            sqlcommand = "SELECT ID FROM STUDENT WHERE NAME = '" + username + "';"
            cursor.execute(sqlcommand)
            studentid = cursor.fetchall()
            studentid = studentid[0]
            chngesched = input("Enter the course number to remove to your schedule")
            sqlcommand = ("UPDATE COURSES SET ROSTER = '' WHERE CRN = '" + chngesched + "' ;")
            cursor.execute(sqlcommand)
            sqlcommand = ("UPDATE STUDENT SET SCHEDULE = '' WHERE NAME = '" + username + "'; ")
            cursor.execute(sqlcommand)
            sqlcommand = ("DELETE FROM COURSES WHERE NAME = '" + chngesched + "'; ")
            cursor.execute(sqlcommand)
            sqliteConnection.commit()
        if choicest == 4:
            sqlcommand = "SELECT SCHEDULE FROM STUDENT WHERE NAME = '" + username + "';"
            cursor.execute(sqlcommand)
            output = cursor.fetchall()
            output = output[0]
            print("Your Schedule is: " + output[0])
    print("Logging Out")


def instructor(username):
    choicein = 0
    while choicein != 4:
        choicein = input(
            "Hello Instructor, Choose a function\n 1.Search Courses By Parameter 2.Search Courses 3.Print Roster 4.Logo"
            "ut")
        choicein = int(choicein)
        if choicein == 1:
            print("")
            condition = ""
            condition = input("Search by one of the following: Title, Department, Time, Day(s) Held, Semester,"
                              "Year, Credits, Teacher, Roster ")
            condition.capitalize()
            subcondition = ""
            subcondition = input("Enter the value for the condition")
            sqlcommand = "SELECT FROM COURSES WHERE " + condition + " = '" + subcondition + "';"
        if choicein == 2:
            sqlcommand = "SELECT TITLE FROM COURSES;"
            cursor.execute(sqlcommand)
            courses = cursor.fetchall()
            print(courses)
        if choicein == 3:
            classprint = input("Enter A CRN to print the roster of")
            sqlcommand = "SELECT ROSTER FROM COURSES WHERE CRN = '" + classprint + "';"
            cursor.execute(sqlcommand)
            classprint = cursor.fetchall()
            print("The Roster Is: ")
            print(classprint)
    print("Logging Out")


def admin(username):
    choicead = 0
    while choicead != 6:
        choicead = input("Hello Admin, Choose a function\n 1.Search Courses By Parameter 2.Search Courses 3.Add or "
                         "Remove Course 4. Logout")
        choicead = int(choicead)
        if choicead == 1:
            print("")
            condition = ""
            condition = input("Search by one of the following: Title, Department, Time, Day(s) Held, Semester,"
                              "Year, Credits, Teacher, Roster ")
            condition.capitalize()
            subcondition = ""
            subcondition = input("Enter the value for the condition")
            sqlcommand = "SELECT FROM COURSES WHERE " + condition + " = '" + subcondition + "';"
        if choicead == 2:
            sqlcommand = "SELECT TITLE FROM COURSES;"
            cursor.execute(sqlcommand)
            courses = cursor.fetchall()
            print(courses)

        if (choicead == 3):  # Remove a course
            addorrem = input("Would You like to add or remove a course?")

            if addorrem == "remove":
                victim = input("Enter a course name to remove")
                sqlcommand = ("DELETE FROM COURSES WHERE TITLE = '" + victim + "';")
                cursor.execute(sqlcommand)
                sqliteConnection.commit()
            if (addorrem == "add"):
                classtitle = input("Enter the class title")
                classcrn = input("Enter the class crn")
                sqlcommand = ("INSERT INTO COURSES (CRN,TITLE,DEPARTMENT,TIME,Day(s) Held,SEMESTER,YEAR,CREDITS,"
                              "TEACHER,ROSTER) VALUES('" + classcrn + "','" + classtitle + "','DEPT','TIME','DAYS',"
                                                                                           "'SEMESTER','YEAR','CREDITS');")
                cursor.execute(sqlcommand)
                sqliteConnection.commit()
                classdept = ""  # Will be implemented later
                classtime = ""
                classdays = ""
                classsemester = ""
                classyear = ""
                classcredits = ""
                classteacher = ""
            if (choicead == 4):  # Add/Remove Student
                addorrem = input("Would You like to add or remove a Student?")
                if addorrem == "remove":
                    victim = input("Enter His/Her Name")
                    sqlcommand = ("DELETE FROM COURSES WHERE NAME = '" + victim + "'; ")
                    cursor.execute(sqlcommand)
                if addorrem == "add":
                    victimfirst = input("Enter His/Her Name")
                    victimlast = input("Enter Last Name")
                    sqlcommand = "INSERT INTO STUDENT (ID,NAME,SURNAME,GRADYEAR,MAJOR,EMAIL,PASSWORD,SCHEDULE) "
                    "Values(1000,'" + victimfirst + "','" + victimlast + "','','','','',''); "
                    cursor.execute(sqlcommand)
                    sqliteConnection.commit()

            if choicead == 5:  # Add/Remove Instructor
                addorrem = input("Would You like to add or remove an Instructor?")
                if addorrem == "add":
                    victimfirst = input("Enter His/Her Name")
                    victimlast = input("Enter Last Name")
                    sqlcommand = "INSERT INTO INSTRUCTOR (ID,NAME,SURNAME,TITLE,HIREYEAR,DEPT,EMAIL,Password) "
                    "Values(2000,'" + victimfirst + "','" + victimlast + "','','','','',''); "
                    cursor.execute(sqlcommand)
                    sqliteConnection.commit()

                if addorrem == "remove":
                    victim = input("Enter His/Her Name")
                    sqlcommand = ("DELETE FROM COURSES WHERE NAME = '" + victim + "'; ")
                    cursor.execute(sqlcommand)
                    sqliteConnection.commit()
    print("Logging Out")


while active != 0:
    username = ""
    password = ""
    sqliteConnection = sqlite3.connect(
        "C:\\Users\\kaberd\\OneDrive - Wentworth Institute of Technology\\Documents\\Junior Year Part 2\\Applied "
        "programming\\Lab3\\assignment3.db")
    cursor = sqliteConnection.cursor()
    automatic()
    active = input("Please enter what type of user you are: 1.Student 2.Instructor/Teacher 3.Admin or 0 To Exit \n")
    print(active)
    active = int(active)
    cursor = sqliteConnection.cursor()

    if active == 1:
        username = input("Welcome Student, Please Enter Your Username\n")
        sqlcommand = "SELECT Password FROM STUDENT WHERE NAME = '" + username + "';"
        password = input("Please enter a password. Software will fail if nothing is entered\n")
        cursor.execute(sqlcommand)
        ans = cursor.fetchall()
        ans = ans[0]
        print(type(password))
        password = int(password)

        if password == ans[0]:
            print("Hello Student: " + username + "\n")
            student(username)

    if active == 2:
        username = input("Welcome Instructor, Please Enter Your Username\n")
        sqlcommand = "SELECT Password FROM INSTRUCTOR WHERE NAME = '" + username + "';"
        password = input("Please enter a password. Software will fail if nothing is entered\n")
        cursor.execute(sqlcommand)
        ans = cursor.fetchall()
        ans = ans[0]
        print(type(password))
        password = int(password)

        if password == ans[0]:
            print("Hello Instructor: " + username + "\n")
            instructor(username)
    if active == 3:
        username = input("Welcome ADMIN, Please Enter Your Username\n")
        sqlcommand = "SELECT PASSWORD FROM ADMIN WHERE NAME = '" + username + "';"
        password = input("Please enter a password. Software will fail if nothing is entered\n")
        cursor.execute(sqlcommand)
        ans = cursor.fetchall()
        ans = ans[0]
        print(type(password))
        password = int(password)

        if password == ans[0]:
            print("Hello Admin: " + username + "\n")
            admin(username)
    if active == 0:
        exit()
sqliteConnection.close()
