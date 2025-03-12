

from PyQt5.QtWidgets import *
import sys
import json
import os
import sqlite3

DB_NAME = "students.db"

def initialize_db():
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute("""
            CREATE TABLE IF NOT EXISTS students(
                id TEXT PRIMARY KEY,
                name TEXT NOT NULL,
                age INTEGER NOT NULL,
                grade TEXT NOT NULL
            )
    """)
    conn.commit()
    conn.close()

def save_data(student):
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute("INSERT into students (id,name,age,grade) values(?,?,?,?)", (student["ID"],student["Name"], student["Age"],student["Grade"]))
    conn.commit()
    conn.close()

def load_students_from_db():
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute("SELECT * from students")
    rows = cursor.fetchall()
    conn.close()
    return [{"ID":row[0],"Name:"row[1],"Age:"row[2],"Grade:"row[3]} for row in rows]

def load_students(filename="students.json"):
        if os.path.exists(filename):
            with open(filename,"r") as file:
                try:
                    return json.load(file)
                except json.JSONDecodeError:
                    return []
        return []

def save_students(students,filename="students.json"):
        with open(filename, "w") as file:
            json.dump(students,file, indent=4)

class StudentManagementApp(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Student Management App")
        self.setGeometry(100,100,500,400)
        self.students = load_students()
        
        layout = QVBoxLayout()
        self.student_list = QListWidget()
        layout.addWidget(self.student_list)

        self.id_label = QLabel("Student ID:")
        self.id_input = QLineEdit()
        self.name_label = QLabel("Name:")
        self.name_input = QLineEdit()

        self.age_label = QLabel("Age:")
        self.age_input = QLineEdit()
        self.grade_label = QLabel("Grade:")
        self.grade_input = QLineEdit()
        self.add_button = QPushButton("Add Student")
        self.search_button = QPushButton("Search Student")
        self.remove_button = QPushButton("Remove Student")
        self.update_button = QPushButton("Update Student")


        layout.addWidget(self.id_label)
        layout.addWidget(self.id_input)
        layout.addWidget(self.name_label)
        layout.addWidget(self.name_input)
        layout.addWidget(self.age_label)
        layout.addWidget(self.age_input)
        layout.addWidget(self.grade_label)
        layout.addWidget(self.grade_input)
        layout.addWidget(self.add_button)
        layout.addWidget(self.search_button)
        layout.addWidget(self.remove_button)
        layout.addWidget(self.update_button)

        self.add_button.clicked.connect(self.add_student)
        self.remove_button.clicked.connect(self.remove_student)
        self.search_button.clicked.connect(self.search_student)
        self.update_button.clicked.connect(self.update_student)
        self.setLayout(layout)

        self.update_display()
    
    def update_student(self):
        student_id = self.id_input.text()
        new_name = self.name_input.text()
        new_age = self.age_input.text()
        new_grade = self.grade_input.text()
        for student in self.students:
            if student['ID'] == student_id:
                if new_name:
                    student["Name"]=new_name
                if new_age:
                    student["Age"]=new_age
                if new_grade:
                    student["Grade"]=new_grade
                self.update_display()
                QMessageBox.information(self,"Success","Student details Updated")
                return
        QMessageBox.warning(self,"Not Found","Student Not Found")

    def add_student(self):
        student_id = self.id_input.text()
        name = self.name_input.text()
        age = self.age_input.text()
        grade = self.grade_input.text()

        if not(student_id and name and age and grade):
            QMessageBox.warning(self,"Input Error","All fields are required")
            return
        self.student_list.addItem(f"ID:{student_id}, Name:{name}")
        self.students.append({"ID":student_id,"Name":name,"Age":age,"Grade":grade})
        save_students(self.students)
        QMessageBox.information(self,"Success","Student added successfully")

    def search_student(self):
        student_id = self.id_input.text()
        for student in self.students:
            if student["ID"] == student_id:
                QMessageBox.information(self,"Student found",f"Name:{student['Name']}")
                return 
        QMessageBox.warning(self,"Not Found","Student Not Found")
    
    def update_display(self):
        self.student_list.clear()
        for student in self.students:
            self.student_list.addItem(f"ID:{student['ID']},Name:{student['Name']}")

    
    
    def remove_student(self):
        student_id = self.id_input.text()
        for student in self.students:
            if student["ID"] == student_id:
                self.students = [s for s in self.students if s["ID"] != student_id]
                self.update_display()
                QMessageBox.information(self,"Success","Student removed successfully")
                return
        QMessageBox.warning(self,"Not Found","Student Not Found")
    
    

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = StudentManagementApp()
    window.show()
    sys.exit(app.exec_())