import sqlite3
con = sqlite3.connect('lab5.db')
con.execute("PRAGMA foreign_keys = ON")

#Insert Courses
con.execute("INSERT INTO COURSE (CRN,TITLE,DEPT,TIME,DAY,SEMESTER,YEAR,CREDITS) \
VALUES (101, 'Intro to Sustainable Energy', 'BSEE', '3:30-5:00', 'MW', 'Summer', 2022, 4)")
con.execute("INSERT INTO COURSE (CRN,TITLE,DEPT,TIME,DAY,SEMESTER,YEAR,CREDITS) \
VALUES (102, 'Intro to Sociology', 'HUSS', '2-3:20', 'TR', 'Fall', 2022, 4)")
con.execute("INSERT INTO COURSE (CRN,TITLE,DEPT,TIME,DAY,SEMESTER,YEAR,CREDITS) \
VALUES (103, 'Applied Programming Concepts', 'BSCO', '2-3:20PM', 'MWF', 'Summer', 2022, 4)")
con.execute("INSERT INTO COURSE (CRN,TITLE,DEPT,TIME,DAY,SEMESTER,YEAR,CREDITS) \
VALUES (104, 'General World History', 'HUSS', '10-11:50', 'TR', 'Spring', 2023, 4)")
con.execute("INSERT INTO COURSE (CRN,TITLE,DEPT,TIME,DAY,SEMESTER,YEAR,CREDITS) \
VALUES (105, 'Signals and Systems', 'BSAS', '8-9:20', 'WF', 'Spring', 2023, 4)")
#Insert Admins
con.execute("INSERT INTO ADMIN (ID, NAME, SURNAME, TITLE, OFFICE, EMAIL, PASSWORD) \
VALUES (30001, 'Margaret', 'Hamilton', 'President', 'Dobbs 1600', 'hamiltonm', 'password')")
con.execute("INSERT INTO ADMIN (ID, NAME, SURNAME, TITLE, OFFICE, EMAIL, PASSWORD) \
VALUES (30002, 'Vera', 'Rubin', 'Vice-President', 'Wentworth 101', 'rubinv', 'password')")
#Insert Instructors
con.execute("INSERT INTO INSTRUCTOR (ID,NAME,SURNAME,TITLE,YEAROFHIRE,DEPT,EMAIL,PASSWORD) \
VALUES (20001, 'Joseph', 'Fourier', 'Full Prof.', 1820, 'BSEE', 'fourierj', 'password')")
con.execute("INSERT INTO INSTRUCTOR (ID,NAME,SURNAME,TITLE,YEAROFHIRE,DEPT,EMAIL,PASSWORD) \
VALUES (20002, 'Nelson', 'Patrick', 'Full Prof.', 1994, 'HUSS', 'patrickn', 'password')")
con.execute("INSERT INTO INSTRUCTOR (ID,NAME,SURNAME,TITLE,YEAROFHIRE,DEPT,EMAIL,PASSWORD) \
VALUES (20003, 'Galileo', 'Galilei', 'Full Prof.', 1600, 'BSAS', 'galileig', 'password')")
con.execute("INSERT INTO INSTRUCTOR (ID,NAME,SURNAME,TITLE,YEAROFHIRE,DEPT,EMAIL,PASSWORD) \
VALUES (20004, 'Alan', 'Turing', 'Associate Prof.', 1940, 'BSCO', 'turinga', 'password')")
con.execute("INSERT INTO INSTRUCTOR (ID,NAME,SURNAME,TITLE,YEAROFHIRE,DEPT,EMAIL,PASSWORD) \
VALUES (20005, 'Katie', 'Bouman', 'Assistant Prof.', 2019, 'BCOS', 'boumank', 'password')")
#Insert Students
con.execute("INSERT INTO STUDENT (ID,NAME,SURNAME,GRADYEAR,MAJOR,EMAIL,PASSWORD) \
VALUES (10001, 'Isaac', 'Newton', 1668, 'BSAS', 'newtoni', 'password')")
con.execute("INSERT INTO STUDENT (ID,NAME,SURNAME,GRADYEAR,MAJOR,EMAIL,PASSWORD) \
VALUES (10002, 'Marie', 'Curie', 1903, 'BSAS', 'curiem', 'password')")
con.execute("INSERT INTO STUDENT (ID,NAME,SURNAME,GRADYEAR,MAJOR,EMAIL,PASSWORD) \
VALUES (10003, 'Nikola', 'Tesla', 1878, 'BSEE', 'teslan', 'password')")
con.commit()
con.close()
