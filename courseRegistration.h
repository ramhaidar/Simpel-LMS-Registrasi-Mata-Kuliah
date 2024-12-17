#ifndef COURSEREGISTRATION_H_INCLUDED
#define COURSEREGISTRATION_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

/**
 * Macro definitions for simplified list traversal
 * Provides convenient access to list element properties
 */
#define first(L) (L).first
#define info(P) (P)->info
#define next(P) (P)->next
#define prev(P) (P)->prev
#define nextStudent(P) (P)->nextStudent

// Add validation range for quota
#define MIN_QUOTA 1
#define MAX_QUOTA 100

// Add student type constants for better type safety
#define STUDENT_TYPE_REGULAR "regular"
#define STUDENT_TYPE_INTERNATIONAL "international"

// Add validation for student type
#define isValidStudentType(type) ((type) == STUDENT_TYPE_REGULAR || (type) == STUDENT_TYPE_INTERNATIONAL)

// Add class name length limit
#define MAX_CLASS_NAME_LENGTH 10

// Add additional validation macros
#define isValidQuota(quota) ((quota) >= MIN_QUOTA && (quota) <= MAX_QUOTA)

// Add input validation limits
#define MAX_NAME_LENGTH 50
#define MIN_NAME_LENGTH 2
#define MAX_ID_LENGTH 20

// Add error codes
#define SUCCESS 0
#define ERROR_INVALID_INPUT -1
#define ERROR_QUOTA_FULL -2
#define ERROR_NOT_FOUND -3

// Add function to validate string length
#define isValidStringLength(str, min, max) ((str).length() >= (min) && (str).length() <= (max))

/**
 * @brief Represents the structure for course information
 * Contains details about a specific course offering
 */
typedef struct elmCourse *adrCourse;
struct infotypeCourse
{
    string courseName;  // Name of the course
    string className;   // Associated class section
    int quota;          // Maximum number of students allowed
    int Count;          // Current number of registered students
    string studentType; // Type of eligible students (e.g., regular/international)
};

/**
 * @brief Represents the structure for student information
 * Contains details about an individual student
 */
typedef struct elmStudent *adrStudent;
struct infotypeStudent
{
    string studentName; // Full name of the student
    string studentID;   // Unique identifier (ID) for the student
    string classOrigin; // Class the student originates from
    string studentType; // Type of the student (e.g., regular/international)
};

/**
 * @brief Represents a node structure for a course
 * Used to create a doubly-linked list of courses
 */
struct elmCourse
{
    infotypeCourse info;    // Course information
    adrCourse next;         // Pointer to the next course in the list
    adrCourse prev;         // Pointer to the previous course in the list
    adrStudent nextStudent; // Pointer to the list of students in this course
};

/**
 * @brief Represents a node structure for a student
 * Used to create a doubly-linked list of students
 */
struct elmStudent
{
    infotypeStudent info; // Student information
    adrStudent next;      // Pointer to the next student in the list
    adrStudent prev;      // Pointer to the previous student in the list
};

/**
 * @brief Manages a doubly-linked list of courses
 */
struct listCourse
{
    adrCourse first; // Pointer to the first course in the list
};

/**
 * @brief Manages a doubly-linked list of students
 */
struct listStudent
{
    adrStudent first; // Pointer to the first student in the list
};

// List Initialization Functions
/**
 * @brief Initialize an empty course list
 * @param LC Reference to the course list to initialize
 */
void createList_Course(listCourse &LC);

/**
 * @brief Initialize an empty student list
 * @param LS Reference to the student list to initialize
 */
void createList_Student(listStudent &LS);

// Element Creation Functions
/**
 * @brief Create a new course element
 * @param newCourse The details of the new course
 * @return Pointer to the newly created course element
 */
adrCourse newElm_Course(infotypeCourse newCourse);

/**
 * @brief Create a new student element
 * @param newStudent The details of the new student
 * @return Pointer to the newly created student element
 */
adrStudent newElm_Student(infotypeStudent newStudent);

// Course Management Functions
/**
 * @brief Add a course to the course list
 * @param LC Reference to the course list
 * @param C Pointer to the course element to be added
 */
void addCourse(listCourse &LC, adrCourse &C);

/**
 * @brief Remove a specific course from the list
 * @param LC Reference to the course list
 * @param C Pointer to the course element to be removed
 */
void deleteCourse(listCourse &LC, adrCourse &C);

// Student Management Functions
/**
 * @brief Add a student to a specific course
 * @param LC Reference to the course list
 * @param LS Reference to the student list
 * @param C Pointer to the course where the student will be added
 * @param S Pointer to the student to be added
 */
void addStudent(listCourse &LC, listStudent &LS, adrCourse C, adrStudent S);

/**
 * @brief Remove a student from a specific course
 * @param LC Reference to the course list
 * @param LS Reference to the student list
 * @param C Pointer to the course from which the student will be removed
 * @param S Pointer to the student to be removed
 */
void deleteStudent(listCourse &LC, listStudent &LS, adrCourse C, adrStudent &S);

// Registration Relation Functions
/**
 * @brief Link a student to a course for registration
 * @param LC Reference to the course list
 * @param LS Reference to the student list
 * @param S Pointer to the student to be registered
 * @param courseName Name of the course for registration
 */
void setClass(listCourse &LC, listStudent &LS, adrStudent S, string courseName);

/**
 * @brief Unlink a student from a course (remove registration)
 * @param LC Reference to the course list
 * @param LS Reference to the student list
 * @param studentName Name of the student to be unregistered
 * @param courseName Name of the course for deregistration
 */
void deleteClass(listCourse &LC, listStudent &LS, string studentName, string courseName);

// Utility and Display Functions
/**
 * @brief Update the count of students in each course
 * @param LC Reference to the course list
 * @param LS Reference to the student list
 */
void updateCount(listCourse LC, listStudent LS);

/**
 * @brief Display all courses with their details
 * @param LC Reference to the course list
 */
void showCourses(listCourse LC);

/**
 * @brief Display students registered in a specific course and class
 * @param LC Reference to the course list
 * @param LS Reference to the student list
 * @param course Name of the course
 * @param Class Name of the specific class section
 */
void showStudentInCourse(listCourse LC, listStudent LS, string course, string Class);

/**
 * @brief Display all courses and their registered students
 * @param LC Reference to the course list
 * @param LS Reference to the student list
 */
void showAllData(listCourse LC, listStudent LS);

/**
 * @brief Search for a course with available quota
 * @param LC Reference to the course list
 * @param course Name of the course to search
 * @param type Type of student for the course
 * @return Pointer to the course element with available quota, or NULL if none
 */
adrCourse searchCourseByQuota(listCourse LC, string course, string type);

/**
 * @brief Search for a specific student in a given course
 * @param LC Reference to the course list
 * @param LS Reference to the student list
 * @param name Name of the student to search
 * @param course Name of the course to search
 * @param S Output parameter for the found student pointer
 * @param C Output parameter for the found course pointer
 */
void searchStudentInCourse(listCourse LC, listStudent LS, string name, string course, adrStudent &S, adrCourse &C);

/**
 * @brief Display the menu and return the user's choice
 * @return The selected menu option
 */
int selectMenu();

/**
 * @brief Clears all courses and their associated students from the list
 * @param LC Reference to the course list to clear
 *
 * This function deallocates memory for all courses and their associated students
 * in the list. It ensures that no memory leaks occur by freeing all dynamically
 * allocated memory.
 */
void clearAllCourses(listCourse &LC);

/**
 * @brief Searches for a course by its name and class
 * @param LC Reference to the course list
 * @param course Name of the course to search for
 * @param Class Name of the class to search for
 * @return Pointer to the course element if found, or NULL if not found
 */
adrCourse searchCourseByName(listCourse LC, string course, string Class);

#endif // COURSEREGISTRATION_H_INCLUDED
