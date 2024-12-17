# Course Registration System

This project implements a **Course Registration System** using a doubly-linked list data structure in C++. It allows users to manage courses and student registrations efficiently. Features include adding and removing courses, registering students, managing quotas, and displaying registered students per course.

---

## Table of Contents

1. [Project Overview](#project-overview)
2. [Features](#features)
3. [Data Structures](#data-structures)
4. [How to Use](#how-to-use)
5. [Test Cases](#test-cases)
6. [Code Description](#code-description)
7. [Dependencies](#dependencies)
8. [Example Usage](#example-usage)
9. [Acknowledgments](#acknowledgments)

---

## Project Overview

The Course Registration System enables educational institutions to:

1. **Manage Course Details** (Course name, class section, student type, and quotas).
2. **Register Students** to available courses.
3. **Track Enrollments** with quotas and counts.
4. **Display Course Data** and registered student lists.
5. **Update and Delete Registrations**.

This system uses **doubly-linked lists** to manage both courses and their registered students efficiently.

---

## Features

1. **Add New Courses**  
   Users can add courses with specified attributes (name, class, quota, and student type).

2. **Remove Courses**  
   Courses can be deleted by specifying their name and class section.

3. **Register Students**  
   Students can register for courses with quota limits and validation checks.

4. **Update Registration**  
   Manage student-course relationships dynamically, with limits (max 3 courses per student).

5. **Display Data**

    - All courses with details (name, section, quota, current count).
    - Students registered in specific courses and sections.

6. **Quota Management**  
   Ensure quotas are respected during student registration.

7. **Finalization**  
   Option to finalize and clean up unutilized courses with no registered students.

---

## Data Structures

### Course List Structure

The system uses a doubly-linked list for courses, where each course points to:

1. **Next/Previous Course Nodes**
2. **List of Students** registered to the course.

```cpp
struct elmCourse {
    infotypeCourse info;      // Course details
    adrCourse next, prev;     // Pointers to next and previous courses
    adrStudent nextStudent;   // Head pointer to student list
};
```

### Student List Structure

Each course contains a linked list of students:

```cpp
struct elmStudent {
    infotypeStudent info;     // Student details
    adrStudent next, prev;    // Pointers to next and previous students
};
```

---

## How to Use

### Step 1: Clone the Repository

```bash
git clone https://github.com/username/course-registration.git
```

### Step 2: Open the Project in Code::Blocks

The project is intended to be run using **Code::Blocks version 20.03** or higher.

1. Open **Code::Blocks**.
2. Go to the menu **File > Open**.
3. Select the project file with the **.cbp** extension (e.g., `courseRegistration.cbp`).
4. Build and run the project.

### Step 3: Follow Interactive Menu

The system offers a menu with the following options:

1. Add a new course
2. Remove a course
3. Register for courses
4. Remove course registration
5. Update student count for all courses
6. Display all available courses
7. Display students in a specific course and class
8. Display all courses and registered students
9. Search for a course with available quota
10. Search for a specific student in a course
11. Finalize course registration
12. Exit

---

## Test Cases

Below are the predefined test cases to verify system functionality:

```cpp
// Test Case 1: Add new courses
1
3
Mathematics
A
30
regular
Fisika
B
25
regular
Programming
C
20
international

// Test Case 2: Add student and course registration
3
John
12345
1A
regular
2
Mathematics
A
Fisika
B

// Test Case 3: View all courses
6

// Test Case 4: View specific course students
7
Mathematics
A

// Test Case 5: Search course with quota
9
Mathematics
regular

// Test Case 6: Remove course registration
4
John
Mathematics

// Test Case 7: Add another student
3
Jane
67890
1B
international
1
Programming
C

// Test Case 8: Update student counts
5

// Test Case 9: View all data
8

// Test Case 10: Search student
10
Jane
Programming

// Test Case 11: Delete course
2
Fisika
B

// Test Case 12: Finalize registration
11
yes

// Test Case 13: Exit
0
```

---

## Code Description

-   **`courseRegistration.h`**: Contains type definitions, constants, and function prototypes.
-   **`courseRegistration.cpp`**: Implements all course and student management functionalities.
-   **`main.cpp`**: Contains the user interface and interactive menu logic.

### Key Functions:

-   **`addCourse`**: Adds a new course to the list.
-   **`deleteCourse`**: Removes a course from the list.
-   **`addStudent`**: Registers a student to a course.
-   **`deleteStudent`**: Removes a student from a course.
-   **`showCourses`**: Displays all courses.
-   **`showStudentInCourse`**: Displays students in a specific course.
-   **`searchCourseByQuota`**: Finds courses with available quotas.
-   **`clearAllCourses`**: Cleans up dynamically allocated memory.

---

## Dependencies

This project requires:

-   **Code::Blocks version 20.03** or higher
-   Standard C++11 compiler

No external libraries are needed.

---

## Example Usage

### Add Courses

```plaintext
Enter the number of courses to add (1-10): 3
Course 1 details:
Course Name: Mathematics
Class Name: A
Maximum Quota: 30
Student Type: regular
```

### Register Students

```plaintext
---- Student Registration ----
Name: John
Student ID: 12345
Original Class: 1A
Student Type: regular
Enter the number of courses to register for: 2
Enter the name of course 1: Mathematics
```

---

## Acknowledgments

This project demonstrates a basic **course registration system** using doubly-linked lists. It serves as an excellent resource for learning data structures and C++ programming.

Feel free to use this project for educational purposes or extend it for more advanced use cases. Feedback and contributions are welcome! 😊
