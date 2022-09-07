#ifndef COURSEREGISTRATION_H_INCLUDED
#define COURSEREGISTRATION_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;
#define first(L) (L).first
#define info(P) (P)->info
#define next(P) (P)->next
#define prev(P) (P)->prev
#define nextStudent(P) (P)->nextStudent



//ADT Parent Course

typedef struct elmCourse *adrCourse;
struct infotypeCourse{
    string courseName;
    string className;
    int quota;
    int Count;
    string studentType;
};
typedef struct elmStudent *adrStudent;
struct elmCourse{
    infotypeCourse info;
    adrCourse next;
    adrCourse prev;
    adrStudent nextStudent;
};
struct listCourse{
    adrCourse first;
};

//ADT Child Student

struct infotypeStudent{
    string studentName;
    string studentID;
    string classOrigin;
    string studentType;
};
struct elmStudent{
    infotypeStudent info;
    adrStudent next;
    adrStudent prev;
};
struct listStudent{
    adrStudent first;
};

//membuat list parent dan child
void createList_Course(listCourse &LC);
void createList_Student(listStudent &LS);
//membuat elemen parent dan child baru
adrCourse newElm_Course(infotypeCourse newCourse);
adrStudent newElm_Student(infotypeStudent newStudent);
//procedure menambah mata kuliah
void addCourse(listCourse &LC, adrCourse &C);
//procedure menghapus mata kuliah
void deleteCourse(listCourse &LC, adrCourse &C);
//procedure menambah mahasiswa
void addStudent(listCourse &LC, listStudent &LS, adrCourse C, adrStudent S);
//procedure menghapus mahasiswa
void deleteStudent(listCourse &LC, listStudent &LS, adrCourse C, adrStudent &S);
//procedure menghubungkan relasi mata kuliah dan mahasiswa
void setClass(listCourse &LC, listStudent &LS, adrStudent S, string courseName);
//procedure menghapus hubungan relasi mata kuliah dan mahasiswa
void deleteClass(listCourse &LC, listStudent &LS, string studentName, string courseName);
//procedure update jumlah mahasiswa di setiap mata kuliah
void updateCount(listCourse LC, listStudent LS);
//procedure menampilkan data semua mata kuliah beserta jumlah mahasiswa
void showCourses(listCourse LC);
//procedure menampilkan data mahasiswa di MK dan kelas tertentu
void showStudentInCourse(listCourse LC, listStudent LS, string course, string Class);
//procedure menampilkan semua data mata kuliah beserta mahasiswanya
void showAllData(listCourse LC, listStudent LS);
//Mencari nama mk tertentu dengan kuota masih tersedia
adrCourse searchCourseByQuota(listCourse LC, string course, string type);
//Mencari nama mahasiswa tertentu pada sebuah MK
void searchStudentInCourse(listCourse LC, listStudent LS, string name, string course, adrStudent &S, adrCourse &C);

int selectMenu();
#endif // COURSEREGISTRATION_H_INCLUDED
