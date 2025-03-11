class Student:
    def __init__(self,student_id,name,age,grade):
        self.student_id = student_id
        self.name = name
        self.age = age
        self.grade = grade
    
    def __str__(self):
        return f"ID: {self.student_id}, Name: {self.name}, Age: {self.age}"
    
students = []

def add_student(student_id,name,age,grade):
    student = Student(student_id,name,age,grade)
    students.append(student)
    print(f"Student {name} added successfully")

def display_students():
    if not students:
        print("No students in the system")
        return
    print("\n List of students")
    for student in students:
        print(student)

def search_student(student_id):
    for student in students:
        if student.student_id == student_id:
            print("\n Student Found")
            print(student)
            return
    print("Student not found")

def remove_student(student_id):
    global students
    students = [student for student in students if student.student_id != student_id]
    print("Student with ID has been removed")


add_student(1,"Alice",20,"A")
add_student(2,"Bob",21,"B")
search_student("Alice")
remove_student(2)
display_students()