#include "courseRegistration.h"
#include <iostream>
#include <limits>
#include <stdlib.h> // For system("CLS")

using namespace std;

int main()
{
    // Add input buffer clearing before string inputs
    cin.exceptions(ios::failbit | ios::badbit);

    try {
        listCourse LC;                    // List of courses
        listStudent LS;                   // List of students
        adrCourse C;                      // Pointer to a course element
        adrStudent S;                     // Pointer to a student element
        infotypeCourse newCourse;         // Data for a new course
        infotypeStudent newStudent;       // Data for a new student
        string course, type, name, Class; // Temporary variables for input
        int i, n, jumlah;                 // Counters and input variables
        int option = 0;                   // Menu selection
        string continueProgram = "Y";

        // Initialize course and student lists
        createList_Course(LC);
        createList_Student(LS);

        // Display menu and process user input
        do
        {
            try {
                option = selectMenu();
                cout << endl;

                switch (option)
                {
                case 1: // Add new courses
                    cout << "Enter the number of courses to add (1-10): ";
                    cin >> n;

                    // Input validation
                    while (cin.fail() || n < 1 || n > 10)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Please enter a valid number between 1 and 10: ";
                        cin >> n;
                    }

                    for (i = 1; i <= n; ++i)
                    {
                        cout << "Course " << i << " details:" << endl;
                        // Add input validation for course names
                        do {
                            cout << "Course Name: ";
                            cin >> newCourse.courseName;
                        } while (!isValidStringLength(newCourse.courseName, MIN_NAME_LENGTH, MAX_NAME_LENGTH));
                        
                        cout << "Class Name: ";
                        cin >> newCourse.className;
                        cout << "Maximum Quota: ";
                        cin >> newCourse.quota;
                        newCourse.Count = 0; // Initialize student count to 0
                        cout << "Student Type (e.g., regular/international): ";
                        cin >> newCourse.studentType;

                        // Clear input buffer before string inputs
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        C = newElm_Course(newCourse); // Create course element
                        addCourse(LC, C);             // Add course to the list
                        cout << endl;
                    }
                    break;

                case 2: // Remove a course
                    cout << "Enter the course details to delete:" << endl;
                    cout << "Course Name: ";
                    cin >> course;
                    cout << "Class Name: ";
                    cin >> Class;

                    C = first(LC);
                    while (C != NULL && (info(C).courseName != course || info(C).className != Class))
                    {
                        C = next(C);
                    }

                    deleteCourse(LC, C);

                    if (C != NULL)
                    {
                        cout << "Course list after deletion:" << endl;
                        showCourses(LC);
                    }
                    else
                    {
                        cout << "Course not found in the list." << endl;
                    }
                    break;

                case 3: // Register a student for courses
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                    cout << "---- Student Registration ----" << endl;
                    cout << "Name: ";
                    cin >> newStudent.studentName;
                    cout << "Student ID: ";
                    cin >> newStudent.studentID;
                    cout << "Original Class: ";
                    cin >> newStudent.classOrigin;

                    // Validate student type
                    do
                    {
                        cout << "Student Type (regular/international): ";
                        cin >> newStudent.studentType;
                    } while (!isValidStudentType(newStudent.studentType));

                    S = newElm_Student(newStudent); // Create student element
                    cout << endl;

                    cout << "Enter the number of courses to register for: ";
                    cin >> n;

                    jumlah = 0; // Count courses already registered
                    C = first(LC);
                    while (C != NULL)
                    {
                        adrStudent Mhs = nextStudent(C);
                        while (Mhs != NULL)
                        {
                            if (info(Mhs).studentName == newStudent.studentName)
                            {
                                jumlah++;
                            }
                            Mhs = next(Mhs);
                        }
                        C = next(C);
                    }

                    while ((n + jumlah) > 3)
                    {
                        cout << "Error: Maximum registration limit is 3 courses." << endl;
                        cout << "Remaining slots available: " << 3 - jumlah << "." << endl;
                        cout << "Re-enter the number of courses: ";
                        cin >> n;
                    }

                    for (i = 1; i <= n; ++i)
                    {
                        cout << "Enter the name of course " << i << ": ";
                        cin >> course;
                        setClass(LC, LS, S, course);
                    }
                    cout << endl;
                    break;

                case 4: // Remove a student's course registration
                    cout << "Enter the registration details to delete:" << endl;
                    cout << "Student Name: ";
                    cin >> name;
                    cout << "Course Name: ";
                    cin >> course;

                    deleteClass(LC, LS, name, course);
                    cout << "Registration list after deletion:" << endl;
                    showAllData(LC, LS);
                    break;

                case 5: // Update student count for courses
                    updateCount(LC, LS);
                    cout << "Status: Student counts updated successfully." << endl;
                    break;

                case 6: // Display all courses
                    cout << "Course List:" << endl
                        << endl;
                    showCourses(LC);
                    break;

                case 7: // Display students in a specific course and class
                    cout << "Enter the course details:" << endl;
                    cout << "Course Name: ";
                    cin >> course;
                    cout << "Class Name: ";
                    cin >> Class;

                    showStudentInCourse(LC, LS, course, Class);
                    cout << endl;
                    break;

                case 8: // Display all courses and registered students
                    cout << "All Course Registrations:" << endl;
                    showAllData(LC, LS);
                    break;

                case 9: // Search for a course with available quota
                    cout << "Enter the course name: ";
                    cin >> course;
                    cout << "Enter the student type (regular/international): ";
                    cin >> type;

                    C = searchCourseByQuota(LC, course, type);

                    if (C == NULL)
                    {
                        cout << "No available quota for course: " << course << " (" << type << ")" << endl;
                    }
                    else
                    {
                        cout << "Course Details:" << endl;
                        cout << "Name: " << info(C).courseName << endl;
                        cout << "Class: " << info(C).className << endl;
                        cout << "Max Quota: " << info(C).quota << endl;
                        cout << "Current Enrollment: " << info(C).Count << endl;
                        cout << "Student Type: " << info(C).studentType << endl;
                    }
                    break;

                case 10: // Search for a specific student in a course
                    cout << "Enter the student name: ";
                    cin >> name;
                    cout << "Enter the course name: ";
                    cin >> course;

                    searchStudentInCourse(LC, LS, name, course, S, C);

                    if (S == NULL)
                    {
                        cout << "Student not found in the specified course." << endl;
                    }
                    else
                    {
                        cout << "Student Details:" << endl;
                        cout << "Name: " << info(S).studentName << endl;
                        cout << "ID: " << info(S).studentID << endl;
                        cout << "Original Class: " << info(S).classOrigin << endl;
                        cout << "Type: " << info(S).studentType << endl;
                    }
                    break;

                case 11:
                {                        // Finalize course registration
                    string confirmation; // Declare variable at the top of this case
                    cout << "Do you want to finalize the registration? (yes/no): ";
                    cin >> confirmation;

                    if (confirmation == "yes")
                    {
                        C = first(LC);
                        while (C != NULL)
                        {
                            if (info(C).Count == 0)
                            {
                                deleteCourse(LC, C);
                            }
                            C = next(C);
                        }
                    }
                    else if (confirmation != "no")
                    {
                        cout << "Invalid input. Please enter yes or no." << endl;
                    }
                    break;
                }

                case 0: // Exit
                    cout << "Exiting the program. Goodbye!" << endl;
                    break;

                default:
                    cout << "Invalid option. Please try again." << endl;
                }
            } catch (const ios_base::failure& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please try again." << endl;
            }

            if (option != 0)
            {
                cout << "Return to the main menu? (Y/N): ";
                cin >> continueProgram;

                if (continueProgram == "N" || continueProgram == "n")
                {
                    break;
                }
                else if (continueProgram != "Y" && continueProgram != "y")
                {
                    cout << "Invalid input. Returning to the main menu." << endl;
                    continueProgram = "Y";
                }

                system("CLS"); // Clear the screen
            }
        } while (option != 0 && (continueProgram == "Y" || continueProgram == "y"));

        // Add proper cleanup before exit
        clearAllCourses(LC);
        return SUCCESS;
    } catch (const exception& e) {
        cout << "Program error: " << e.what() << endl;
        return ERROR_INVALID_INPUT;
    }
}
