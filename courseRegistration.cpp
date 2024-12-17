#include "courseRegistration.h"
#include <cstring>

/**
 * @brief Initializes an empty course list
 * @param LC Reference to the course list to be initialized
 */
void createList_Course(listCourse &LC)
{
  first(LC) = NULL;
}

/**
 * @brief Initializes an empty student list
 * @param LS Reference to the student list to be initialized
 */
void createList_Student(listStudent &LS)
{
  first(LS) = NULL;
}

/**
 * @brief Creates a new course element
 * @param newCourse Course details to be added
 * @return Pointer to the newly created course element
 */
adrCourse newElm_Course(infotypeCourse newCourse)
{
  adrCourse C = new elmCourse;
  info(C) = newCourse;
  next(C) = NULL;
  prev(C) = NULL;
  nextStudent(C) = NULL;
  return C;
}

/**
 * @brief Creates a new student element
 * @param newStudent Student details to be added
 * @return Pointer to the newly created student element
 */
adrStudent newElm_Student(infotypeStudent newStudent)
{
  adrStudent S = new elmStudent;
  info(S) = newStudent;
  next(S) = NULL;
  prev(S) = NULL;
  return S;
}

/**
 * @brief Displays the interactive menu and captures user selection
 * @return The selected menu option
 */
int selectMenu()
{
  cout << "\n+======================= COURSE REGISTRATION SYSTEM MENU =======================+" << endl;
  cout << "|  1.  Add a new course                                                       |" << endl;
  cout << "|  2.  Remove a course                                                        |" << endl;
  cout << "|  3.  Register for courses                                                   |" << endl;
  cout << "|  4.  Remove course registration                                             |" << endl;
  cout << "|  5.  Update student count for all courses                                   |" << endl;
  cout << "|  6.  Display all available courses                                          |" << endl;
  cout << "|  7.  Display students in a specific course and class                        |" << endl;
  cout << "|  8.  Display all courses and registered students                            |" << endl;
  cout << "|  9.  Search for a course with available quota                               |" << endl;
  cout << "|  10. Search for a specific student in a course                              |" << endl;
  cout << "|  11. Finalize course registration                                           |" << endl;
  cout << "|  0.  Exit                                                                   |" << endl;
  cout << "+=========================================================================+" << endl;
  cout << "\nPlease select an option: ";

  int input = 0;
  cin >> input;
  return input;
}

/**
 * @brief Adds a course to the course list
 * @param LC Reference to the course list
 * @param C Pointer to the course element to be added
 */
void addCourse(listCourse &LC, adrCourse &C)
{
  if (C == NULL)
  {
    cout << "Invalid course data." << endl;
    return;
  }

  // Validate string lengths
  if (!isValidStringLength(info(C).courseName, MIN_NAME_LENGTH, MAX_NAME_LENGTH))
  {
    cout << "Course name length must be between " << MIN_NAME_LENGTH << " and " << MAX_NAME_LENGTH << endl;
    delete C;
    C = NULL;
    return;
  }

  // Validate quota
  if (!isValidQuota(info(C).quota))
  {
    cout << "Invalid quota. Must be between " << MIN_QUOTA << " and " << MAX_QUOTA << endl;
    delete C;
    C = NULL;
    return;
  }

  // Validate student type
  if (!isValidStudentType(info(C).studentType))
  {
    cout << "Invalid student type. Must be either 'regular' or 'international'" << endl;
    delete C;
    C = NULL;
    return;
  }

  // Validate class name length
  if (info(C).className.length() > MAX_CLASS_NAME_LENGTH)
  {
    cout << "Class name too long. Maximum length is " << MAX_CLASS_NAME_LENGTH << endl;
    delete C;
    C = NULL;
    return;
  }

  // Check for duplicate course
  if (searchCourseByName(LC, info(C).courseName, info(C).className) != NULL)
  {
    cout << "Course with same name and class already exists." << endl;
    return;
  }

  if (first(LC) == NULL)
  {
    first(LC) = C; // Insert as the first element
  }
  else
  {
    adrCourse P = first(LC);
    while (next(P) != NULL)
    { // Traverse to the last element
      P = next(P);
    }
    prev(C) = P;
    next(P) = C;
  }
}

/**
 * @brief Removes a course from the course list
 * @param LC Reference to the course list
 * @param C Pointer to the course element to be removed
 */
void deleteCourse(listCourse &LC, adrCourse &C)
{
  if (C == NULL)
  {
    cout << "Course not found." << endl;
    return;
  }
  if (C == first(LC))
  {
    if (next(C) == NULL)
    {
      first(LC) = NULL; // List becomes empty
    }
    else
    {
      first(LC) = next(C);
      prev(first(LC)) = NULL;
      next(C) = NULL;
    }
  }
  else
  {
    adrCourse P = first(LC);
    while (P != NULL && P != C)
    { // Locate the course to delete
      P = next(P);
    }
    if (P != NULL)
    {
      if (next(P) == NULL)
      {
        next(prev(P)) = NULL;
        prev(P) = NULL;
      }
      else
      {
        adrCourse prec = prev(P);
        next(prec) = next(P);
        prev(next(P)) = prec;
        prev(P) = NULL;
        next(P) = NULL;
      }
    }
    else
    {
      cout << "Course not found." << endl;
    }
  }
}

/**
 * @brief Adds a student to a specific course
 * @param LC Reference to the course list
 * @param LS Reference to the student list
 * @param C Pointer to the course where the student will be added
 * @param S Pointer to the student to be added
 */
void addStudent(listCourse &LC, listStudent &LS, adrCourse C, adrStudent S)
{
  if (nextStudent(C) == NULL)
  {
    nextStudent(C) = S; // Insert as the first student
  }
  else
  {
    adrStudent P = nextStudent(C);
    while (next(P) != NULL)
    { // Traverse to the last student
      P = next(P);
    }
    prev(S) = P;
    next(P) = S;
  }
}

/**
 * @brief Removes a student from a specific course
 * @param LC Reference to the course list
 * @param LS Reference to the student list
 * @param C Pointer to the course from which the student will be removed
 * @param S Pointer to the student to be removed
 */
void deleteStudent(listCourse &LC, listStudent &LS, adrCourse C, adrStudent &S)
{
  if (S == nextStudent(C))
  {
    if (next(S) == NULL)
    {
      nextStudent(C) = NULL; // Student list becomes empty
    }
    else
    {
      nextStudent(C) = next(S);
      prev(nextStudent(C)) = NULL;
      next(S) = NULL;
    }
  }
  else
  {
    adrStudent P = nextStudent(C);
    while (P != NULL && P != S)
    { // Locate the student to delete
      P = next(P);
    }
    if (P != NULL)
    {
      if (next(P) == NULL)
      {
        next(prev(P)) = NULL;
        prev(P) = NULL;
      }
      else
      {
        adrStudent prec = prev(P);
        next(prec) = next(P);
        prev(next(P)) = prec;
        prev(P) = NULL;
        next(P) = NULL;
      }
    }
    else
    {
      cout << "Student not found." << endl;
    }
  }
}

/**
 * @brief Registers a student to a course
 * @param LC Reference to the course list
 * @param LS Reference to the student list
 * @param S Pointer to the student to be registered
 * @param courseName Name of the course
 */
void setClass(listCourse &LC, listStudent &LS, adrStudent S, string courseName)
{
  if (!isValidStringLength(courseName, MIN_NAME_LENGTH, MAX_NAME_LENGTH))
  {
    cout << "Invalid course name length." << endl;
    return;
  }

  if (first(LC) == NULL)
  {
    cout << "No courses available." << endl;
    return;
  }

  if (S == NULL)
  {
    cout << "Invalid student data." << endl;
    return;
  }

  // Check if student is already registered in 3 courses
  int courseCount = 0;
  adrCourse tempC = first(LC);
  while (tempC != NULL)
  {
    adrStudent tempS = nextStudent(tempC);
    while (tempS != NULL)
    {
      if (info(tempS).studentID == info(S).studentID)
      {
        courseCount++;
        if (courseCount >= 3)
        {
          cout << "Student has already registered for maximum number of courses (3)." << endl;
          return;
        }
      }
      tempS = next(tempS);
    }
    tempC = next(tempC);
  }

  // Find all available sections of the course
  bool foundCourse = false;
  adrCourse C = first(LC);
  while (C != NULL)
  {
    if (info(C).courseName == courseName &&
        info(C).studentType == info(S).studentType &&
        info(C).Count < info(C).quota)
    {

      foundCourse = true;
      cout << "Available class section: " << info(C).className
           << " (Current enrollment: " << info(C).Count
           << "/" << info(C).quota << ")" << endl;
    }
    C = next(C);
  }

  if (!foundCourse)
  {
    cout << "No available sections for course: " << courseName << endl;
    return;
  }

  // Ask user to select a class section
  string selectedClass;
  cout << "Enter class section to register for: ";
  cin >> selectedClass;

  // Find the selected course section
  C = first(LC);
  while (C != NULL)
  {
    if (info(C).courseName == courseName &&
        info(C).className == selectedClass &&
        info(C).studentType == info(S).studentType &&
        info(C).Count < info(C).quota)
    {

      // Check if student is already registered in this specific section
      adrStudent existingStudent = nextStudent(C);
      while (existingStudent != NULL)
      {
        if (info(existingStudent).studentID == info(S).studentID)
        {
          cout << "Student already registered in this course section." << endl;
          return;
        }
        existingStudent = next(existingStudent);
      }

      // Register student to the selected section
      addStudent(LC, LS, C, S);
      info(C).Count++;
      cout << "Student successfully registered to " << courseName
           << " (Section: " << selectedClass << ")" << endl;
      return;
    }
    C = next(C);
  }

  cout << "Invalid class section or section is full." << endl;
}

/**
 * @brief Unregisters a student from a course
 * @param LC Reference to the course list
 * @param LS Reference to the student list
 * @param studentName Name of the student
 * @param courseName Name of the course
 */
void deleteClass(listCourse &LC, listStudent &LS, string studentName, string courseName)
{
  if (!isValidStringLength(studentName, MIN_NAME_LENGTH, MAX_NAME_LENGTH) ||
      !isValidStringLength(courseName, MIN_NAME_LENGTH, MAX_NAME_LENGTH))
  {
    cout << "Invalid name length." << endl;
    return;
  }

  if (studentName.empty() || courseName.empty())
  {
    cout << "Invalid student name or course name." << endl;
    return;
  }

  adrCourse C = NULL;
  adrStudent S = NULL;
  searchStudentInCourse(LC, LS, studentName, courseName, S, C);
  if (C != NULL && S != NULL)
  {
    deleteStudent(LC, LS, C, S);
    info(C).Count--; // Update count immediately
    cout << "Student successfully unregistered from course." << endl;
  }
  else
  {
    cout << "Registration not found." << endl;
  }
}

/**
 * @brief Updates the count of registered students for each course
 * @param LC Reference to the course list
 * @param LS Reference to the student list
 */
void updateCount(listCourse LC, listStudent LS)
{
  adrCourse C = first(LC);
  while (C != NULL)
  {
    info(C).Count = 0; // Reset count
    adrStudent S = nextStudent(C);
    while (S != NULL)
    {
      info(C).Count++;
      S = next(S);
    }
    C = next(C);
  }
}

/**
 * @brief Displays all available courses with details
 * @param LC Reference to the course list
 */
void showCourses(listCourse LC)
{
  adrCourse C = first(LC);
  if (C == NULL)
  {
    cout << "\n+===================================+" << endl;
    cout << "|       No courses available        |" << endl;
    cout << "+===================================+" << endl;
  }
  else
  {
    cout << "\n+======================= COURSE LIST =======================+" << endl;
    cout << "| No | Course Name    | Class | Quota | Enrolled | Type    |" << endl;
    cout << "+----+--------------+-------+-------+----------+---------+" << endl;
    int i = 1;
    while (C != NULL)
    {
      printf("| %-2d | %-12s | %-5s | %-5d | %-8d | %-7s |\n",
             i,
             info(C).courseName.c_str(),
             info(C).className.c_str(),
             info(C).quota,
             info(C).Count,
             info(C).studentType.c_str());
      C = next(C);
      i++;
    }
    cout << "+----+--------------+-------+-------+----------+---------+" << endl;
  }
}

/**
 * @brief Displays students registered in a specific course and class
 * @param LC Reference to the course list
 * @param LS Reference to the student list
 * @param course Name of the course
 * @param Class Name of the class
 */
void showStudentInCourse(listCourse LC, listStudent LS, string course, string Class)
{
  adrCourse C = first(LC);
  while (C != NULL)
  {
    if (info(C).courseName == course && info(C).className == Class)
      break;
    C = next(C);
  }

  if (C != NULL && nextStudent(C) != NULL)
  {
    cout << "\n+==================== STUDENT LIST ====================+" << endl;
    cout << "  Course: " << course << " | Class: " << Class << endl;
    cout << "+====+===============+=========+=============+==========+" << endl;
    cout << "| No |     Name     |   ID    |Origin Class |   Type  |" << endl;
    cout << "+----+-------------+---------+-------------+----------+" << endl;

    adrStudent S = nextStudent(C);
    int i = 1;
    while (S != NULL)
    {
      printf("| %-2d | %-11s | %-7s | %-11s | %-8s |\n",
             i,
             info(S).studentName.c_str(),
             info(S).studentID.c_str(),
             info(S).classOrigin.c_str(),
             info(S).studentType.c_str());
      S = next(S);
      i++;
    }
    cout << "+====+===============+=========+=============+==========+" << endl;
  }
  else
  {
    cout << "\n+================================================+" << endl;
    cout << "|    No students registered in this course        |" << endl;
    cout << "+================================================+" << endl;
  }
}

/**
 * @brief Displays all courses and their registered students
 * @param LC Reference to the course list
 * @param LS Reference to the student list
 */
void showAllData(listCourse LC, listStudent LS)
{
  if (first(LC) == NULL)
  {
    cout << "\n+===================================+" << endl;
    cout << "|         No data available         |" << endl;
    cout << "+===================================+" << endl;
    return;
  }

  cout << "\n+================ COURSE REGISTRATION DATA ================+" << endl;
  adrCourse C = first(LC);
  int i = 1;
  while (C != NULL)
  {
    cout << "+---------------------------------------------------+" << endl;
    cout << "| Course " << i << ": " << info(C).courseName << endl;
    cout << "| Class: " << info(C).className << endl;
    cout << "| Quota: " << info(C).quota << " | Registered: " << info(C).Count << endl;
    showStudentInCourse(LC, LS, info(C).courseName, info(C).className);
    C = next(C);
    i++;
  }
  cout << "+===================================================+" << endl;
}

/**
 * @brief Searches for a course with available quota
 * @param LC Reference to the course list
 * @param course Name of the course
 * @param type Type of student
 * @return Pointer to the course with available quota, or NULL if not found
 */
adrCourse searchCourseByQuota(listCourse LC, string course, string type)
{
  adrCourse C = first(LC);
  while (C != NULL)
  {
    if (info(C).courseName == course && info(C).Count < info(C).quota && info(C).studentType == type)
    {
      return C;
    }
    C = next(C);
  }
  return NULL;
}

/**
 * @brief Searches for a student in a specific course
 * @param LC Reference to the course list
 * @param LS Reference to the student list
 * @param name Name of the student
 * @param course Name of the course
 * @param S Output parameter for the student pointer
 * @param C Output parameter for the course pointer
 */
void searchStudentInCourse(listCourse LC, listStudent LS, string name, string course, adrStudent &S, adrCourse &C)
{
  C = first(LC);
  while (C != NULL)
  {
    S = nextStudent(C);
    while (S != NULL)
    {
      if (info(S).studentName == name && info(C).courseName == course)
      {
        return;
      }
      S = next(S);
    }
    C = next(C);
  }
  C = NULL;
  S = NULL;
}

/**
 * @brief Clears all courses and their associated students from the list
 * @param LC Reference to the course list to clear
 *
 * This function iterates through the course list and deallocates memory for
 * each course and its associated students. It ensures that all dynamically
 * allocated memory is freed, preventing memory leaks.
 *
 * - First, the course list head pointer is updated to the next course.
 * - Then, all students associated with the current course are deallocated.
 * - Finally, the course itself is deallocated.
 *
 * After processing all courses, the list is empty, and all memory is cleaned.
 */
void clearAllCourses(listCourse &LC)
{
  adrCourse current = first(LC);

  while (current != NULL)
  {
    adrCourse nextCourse = next(current);

    // Clear all students first
    adrStudent currentStudent = nextStudent(current);
    while (currentStudent != NULL)
    {
      adrStudent nextStudent = next(currentStudent);
      delete currentStudent;
      currentStudent = nextStudent;
    }

    // Then delete the course
    delete current;
    current = nextCourse;
  }

  first(LC) = NULL; // Reset the list head
}

/**
 * @brief Searches for a course by its name and class
 * @param LC Reference to the course list
 * @param course The name of the course to search for
 * @param Class The name of the class to search for
 * @return Pointer to the course element if found, or NULL if not found
 */
adrCourse searchCourseByName(listCourse LC, string course, string Class)
{
  adrCourse C = first(LC);
  while (C != NULL)
  {
    if (info(C).courseName == course && info(C).className == Class)
    {
      return C; // Course found
    }
    C = next(C);
  }
  return NULL; // Course not found
}
