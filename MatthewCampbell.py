#Base User Class
class user:
#Initialize
    def __init__(self, firstname, lastname, Id, schedule):
        self.firstname = firstname
        self.lastname = lastname
        self.Id = Id
        self.schedule = schedule
    def setfirstname(self, name):
        firstname = name
    def setlastname(self, name):
        lastname = name
    def setid(self, val):
        Id = val
    def setschedule(self, schedule):
        Schedule = schedule
    def showstats(self):
        print(self.firstname, self.lastname, self.Id, self.schedule)
#Function to search for courses (all) 
    def search(self):
        for row in cur.execute('SELECT * FROM COURSE'):
            print(row)
#Function to search for courses (based on parameter)
    def searchparameter(self):
        p1 = int(input("Select which parameter to search by (1)CRN, (2)TITLE, (3)DEPT, (4)TIME, (5)DAY, (6)SEMESTER, (7)YEAR, (8)CREDITS: "))
        #CRN
        if p1==1:
            p2 = int(input("Enter the parameter: "))
            cursor = con.execute("SELECT * FROM COURSE WHERE CRN=?", (p2,))
            course1 = cursor.fetchall()
            for row in course1:
                print(row)
        #TITLE
        elif p1==2:
            p2 = str(input("Enter the parameter: "))
            cursor = con.execute("SELECT * FROM COURSE WHERE TITLE=?", (p2,))
            course1 = cursor.fetchall()
            for row in course1:
                print(row)
        #DEPT
        elif p1==3:
            p2 = str(input("Enter the parameter: "))
            cursor = con.execute("SELECT * FROM COURSE WHERE DEPT=?", (p2,))
            course1 = cursor.fetchall()
            for row in course1:
                print(row)
        #TIME
        elif p1==4:
            p2 = str(input("Enter the parameter: "))
            cursor = con.execute("SELECT * FROM COURSE WHERE TIME=?", (p2,))
            course1 = cursor.fetchall()
            for row in course1:
                print(row)
        #DAY
        elif p1==5:
            p2 = str(input("Enter the parameter: "))
            cursor = con.execute("SELECT * FROM COURSE WHERE DAY=?", (p2,))
            course1 = cursor.fetchall()
            for row in course1:
                print(row)
        #SEMESTER
        elif p1==6:
            p2 = str(input("Enter the parameter: "))
            cursor = con.execute("SELECT * FROM COURSE WHERE SEMESTER=?", (p2,))
            course1 = cursor.fetchall()
            for row in course1:
                print(row)
        #YEAR
        elif p1==7:
            p2 = int(input("Enter the parameter: "))
            cursor = con.execute("SELECT * FROM COURSE WHERE YEAR=?", (p2,))
            course1 = cursor.fetchall()
            for row in course1:
                print(row)
        #CREDITS
        elif p1==8:
            p2 = int(input("Enter the parameter: "))
            cursor = con.execute("SELECT * FROM COURSE WHERE CREDITS=?", (p2,))
            course1 = cursor.fetchall()
            for row in course1:
                print(row)

#STUDENT CLASS
class student(user):
#Initialize
    def __init__(self, firstname, lastname, Id, schedule):
        super().__init__(firstname, lastname, Id, schedule)    
#Function to add course to semester schedule (Based on CRN)
    def addcourse(self):
        crn1 = int(input("Select the CRN of course you would like to add to your schedule: "))
        cursor = con.execute("SELECT * FROM COURSE WHERE CRN=?", (crn1,))
        course1 = cursor.fetchall()
        #cursor = con.execute("SELECT NAME, SURNAME FROM STUDENT WHERE MAJOR=?", (major1,))
        #f = con.execute("SELECT TITLE, NAME, SURNAME FROM INSTRUCTOR WHERE DEPT=?", (major1,))
        #roster = f.fetchall() + cursor.fetchall()
        return course1[0]
#Function to remove course to semester schedule (Based on CRN)
    def dropcourse(self):
        print("UNSETUP FUNCTION TO REMOVE COURSE FROM SCHEDULE")
#Function to print individual schedule
    def printsched(self):
        print("UNSETUP FUNCTON TO FORM AND PRINT SCHEDULE")

#INSTRUCTOR CLASS
class instructor(user):
#Initialize
    def __init__(self, firstname, lastname, Id, schedule):
        super().__init__(firstname, lastname, Id, schedule)
#Print course teaching schedule
    def printsched(self):
        print("UNSETUP FUNCTION TO FORM AND PRINT SCHEDULE")
#Print a course's roster (By CRN)
    def courseroster(self):
        crn1 = int(input("Select the CRN of course you would like to show the roster for: "))
        cursor = con.execute("SELECT DEPT FROM COURSE WHERE CRN=?", (crn1,))
        major = cursor.fetchall()
        major0 = major[0]
        major1 = major0[0]
        cursor = con.execute("SELECT NAME, SURNAME FROM STUDENT WHERE MAJOR=?", (major1,))
        f = con.execute("SELECT TITLE, NAME, SURNAME FROM INSTRUCTOR WHERE DEPT=?", (major1,))
        roster = f.fetchall() + cursor.fetchall()
        for row in roster:
            print(row)

#ADMIN CLASS
class admin(user):
#Initialize
    def __init__(self, firstname, lastname, Id):
        super().__init__(firstname, lastname, Id)
#Function to add a course to the system database
    def addsys(self):
        num1 = int(input("Enter course's CRN: "))
        num2 = str(input("Enter course's Title: "))
        num3 = str(input("Enter course's Dept: "))
        num4 = str(input("Enter course's Time: "))
        num5 = str(input("Enter course's Day: "))
        num6 = str(input("Enter course's Semester: "))
        num7 = int(input("Enter course's Year: "))
        num8 = int(input("Enter course's Credits: "))
        cur.execute("INSERT INTO COURSE VALUES (?, ?, ?, ?, ?, ?, ?, ?)", (num1, num2, num3, num4, num5, num6, num7, num8))
        con.commit()
#Function to remove a course from the system database (Based on CRN)
    def removesys(self):
        val1 = int(input("Enter CRN of course you would like to remove: "))
        cur.execute("DELETE FROM COURSE WHERE CRN=:CRN", {"CRN":val1})
        print("~ Course Removed ~")
        con.commit()
#Function to add Student to system
    def addstudent(self):
        print("~Called function to add student to a course~")
#Function to remove Student from system
    def removestudent(self):
        print("~Called function to remove student from a course~")
#Function to add instructor to system
    def addinstructor(self):
        print("F")
#Functon to remove instructor from system
    def removeinstructor(self):
        print("F")
#FUnction to link or unlink user to course
    def linkunlink(self):
        print("F")

#SQLITE3 INITIALIZATION
import sqlite3
con = sqlite3.connect('lab5.db')
con.execute("PRAGMA foreign_keys = ON")
cur = con.cursor()
#Create Course table (if not exists)
query = ('''CREATE TABLE IF NOT EXISTS COURSE
                (CRN        INT    PRIMARY KEY,
                TITLE       TEXT       NOT NULL,
                DEPT        TEXT       NOT NULL,
                TIME        TEXT       NOT NULL,
                DAY         TEXT       NOT NULL,
                SEMESTER    TEXT       NOT NULL,   
                YEAR        INT        NOT NULL,
                CREDITS     INT         NOT NULL
                );''')
#Execute table creation
con.execute(query)
#Create Admin Table
query = ('''CREATE TABLE IF NOT EXISTS ADMIN
                (ID INT PRIMARY KEY,
                NAME TEXT, SURNAME TEXT, 
                TITLE TEXT, 
                OFFICE TEXT, 
                EMAIL TEXT, 
                PASSWORD TEXT
                );''')
con.execute(query)
#Create Instructor Table
query = ('''CREATE TABLE IF NOT EXISTS INSTRUCTOR
                (ID         INT     PRIMARY KEY,
                NAME        TEXT   NOT NULL,
                SURNAME     TEXT   NOT NULL,   
                TITLE       TEXT   NOT NULL,
                YEAROFHIRE  INT    NOT NULL,
                DEPT        TEXT   NOT NULL,
                EMAIL       TEXT   NOT NULL,
                PASSWORD    TEXT   NOT NULL
                );''')
#                FOREIGN KEY(DEPT) REFERENCES COURSE(CRN)   
con.execute(query)
#Create Student Table
query = ('''CREATE TABLE IF NOT EXISTS STUDENT
                (ID INT PRIMARY KEY,
                NAME TEXT,
                SURNAME TEXT,
                GRADYEAR INT,
                MAJOR TEXT,
                EMAIL TEXT, 
                PASSWORD TEXT
                );''')
#                FOREIGN KEY (MAJOR) REFERENCES COURSE (CRN)
con.execute(query)
#Print all values from each table
for row in cur.execute('SELECT * FROM COURSE'):
    print(row)
for row in cur.execute('SELECT * FROM STUDENT'):
    print(row)
for row in cur.execute('SELECT * FROM INSTRUCTOR'):
    print(row)
for row in cur.execute('SELECT * FROM ADMIN'):
    print(row)

#MAIN BODY (Text based GUI)
print("~~~ Welcome to the university scheduling system ~~~")
val1 = 1
#Execution loop
while val1 != 0:
    val1 = int(input("Enter 1 if you are a student, 2 if you are an instructor, 3 if you are an admin, or 0 to exit: "))
#Exit
    if val1 == 0:
        print("Exiting...")
        break
#Student
    elif val1 == 1:
        print("You have selected student: ")
#Login process
        valid = int(input("Enter your ID (1000n): "))
        valpass = str(input("Enter your password to login: "))
        valpassw = (valpass,)
        cursor = con.execute("SELECT PASSWORD FROM STUDENT WHERE ID=?", (valid,))
        valname1 = con.execute("SELECT NAME FROM STUDENT WHERE ID=?", (valid,))
        valsurname1 = con.execute("SELECT SURNAME FROM STUDENT WHERE ID=?", (valid,))
        valname = valname1.fetchall()[0]
        valsurname = valsurname1.fetchall()[0]
#Login pass
        if valpassw == cursor.fetchall()[0]:
            print("Login Succesful")
            print("Welcome " + valname[0] + " " + valsurname[0] + "!")
            #Initialize schedule
            dept1 = con.execute("SELECT MAJOR FROM STUDENT WHERE ID=?", (valid,))
            dept = dept1.fetchall()[0]
            cursor = con.execute("SELECT CRN FROM COURSE WHERE DEPT=?", (dept[0],))
            course = cursor.fetchall()[0]
            course1 = course[0]
            sched = []
            sched.append(course1)
            schedule = sched
            #Initialize student
            p1 = student(valname[0], valsurname[0], valid, schedule)
            for row in p1.schedule:
                print(row)
            #Choose action
            vals = int(input("Enter 1 to search for courses, 2 to add a course, 3 to drop a course, 4 to print schedule, or 0 to exit: "))
            #Exit
            if vals == 0:
                print("Exiting...")
            #Search
            elif vals == 1:
                search = int(input("Enter 1 to display all courses or enter 2 to search by a parameter: "))
                #Search all
                if search==1:
                    p1.search()
                #Search by parameter
                elif search==2:
                    p1.searchparameter()
            #Add course to schedule
            elif vals == 2:
                course1 = p1.addcourse()
                course2 = course1[0]
                print(course2)
                p1.schedule.append(course2)
                print(p1.schedule)
            #Remove course from schedule
            elif vals == 3:
                p1.dropcourse()
            #Print schedule
            elif vals == 4:
                p1.printsched()
            #If password is incorrect, execute this:
            else:
                print("Login Failed")
                break
#Instructor
    elif val1 == 2:
        print("You have selected instructor!")
#Login process
        valid = int(input("Enter your ID (2000n): "))
        valpass = str(input("Enter your password to login: "))
        valpassw = (valpass,)
        cursor = con.execute("SELECT PASSWORD FROM INSTRUCTOR WHERE ID=?", (valid,))
        valname1 = con.execute("SELECT NAME FROM INSTRUCTOR WHERE ID=?", (valid,))
        valsurname1 = con.execute("SELECT SURNAME FROM INSTRUCTOR WHERE ID=?", (valid,))
        valtitle1 = con.execute("SELECT TITLE FROM INSTRUCTOR WHERE ID=?", (valid,))
        valname = valname1.fetchall()[0]
        valsurname = valsurname1.fetchall()[0]
        valtitle = valtitle1.fetchall()[0]
#Login pass
        if valpassw == cursor.fetchall()[0]:
            print("Login Succesful")
            print("Welcome " + valtitle[0] + " " + valname[0] + " " + valsurname[0] + "!")
            #Initialize schedule
            dept1 = con.execute("SELECT DEPT FROM INSTRUCTOR WHERE ID=?", (valid,))
            dept = dept1.fetchall()[0]
            cursor = con.execute("SELECT CRN FROM COURSE WHERE DEPT=?", (dept[0],))
            course = cursor.fetchall()
            print(course)
            sched = []
            i = 0
            while i<len(course):
                course2 = course[i]
                sched.append(course2[0])
            print(sched)
            schedule = sched
            #Initialize instructor
            p2 = instructor(valname, valsurname, valid, schedule)
            #Options
            vali = int(input("Enter 1 to print schedule, 2 to print class list, 3 to search for course, or 0 to exit: "))
            #Exit
            if vali == 0:
                print("Exiting...")
            #Print Schedule
            elif vali == 1:
                print(p2.schedule)
                p2.printsched()
            #Print a course's roster
            elif vali == 2:
                p2.courseroster()
            #Search for courses (all and by parameter)
            elif vali == 3:
                p2.search()
            else:
                print("Login Failed")
                break
#Admin
    elif val1 == 3:
        print("You have selected admin!")
#Login process
        valid = int(input("Enter your ID (3000n): "))
        valpass = str(input("Enter your password to login: "))
        valpassw = (valpass,)
        cursor = con.execute("SELECT PASSWORD FROM ADMIN WHERE ID=?", (valid,))
        valname1 = con.execute("SELECT NAME FROM ADMIN WHERE ID=?", (valid,))
        valsurname1 = con.execute("SELECT SURNAME FROM ADMIN WHERE ID=?", (valid,))
        valtitle1 = con.execute("SELECT TITLE FROM ADMIN WHERE ID=?", (valid,))
        valname = valname1.fetchall()[0]
        valsurname = valsurname1.fetchall()[0]
        valtitle = valtitle1.fetchall()[0]
#Login pass
        if valpassw == cursor.fetchall()[0]:
            print("Login Succesful")
            print("Welcome " + valtitle[0] + " " + valname[0] + " " + valsurname[0] + "!")
            #Initialize admin
            p3 = admin(valname, valsurname, valid)
            vala = int(input("Enter 1 to add course to sys, 2 to remove course from sys, 3 to add instructor, 4 to remove instructor, 5 to add student, 6 to remove student, 7 link or unlink students/instructors to course, or 0 to exit: "))
            #Exit
            if vala == 0:
                print("Exiting...")
            #Add course to system
            elif vala == 1:
                p3.addsys()
            #Remove course from system
            elif vala == 2:
                p3.removesys()
            #Add instructor to system
            elif vala == 3:
                p3.addinstructor()
            #Remove instructor from system
            elif vala == 4:
                p3.removeinstructor()
            #Add student to system
            elif vala == 5:
                p3.addstudent()
            #Remove Student from system
            elif vala == 6:
                p3.removestudent()
            #Link or unlink user to course
            elif vala == 7:
                p3.linkunlink()
            #Failed login
            else:
                print("Login Failed")
                break
con.commit()    #Backup commit just incase
con.close()     #Close Database
