#include "courseRegistration.h"

//membuat list parent dan child
void createList_Course(listCourse &LC){
    first(LC) = NULL;
};
void createList_Student(listStudent &LS){
    first(LS) = NULL;
};
//membuat elemen parent dan child baru
adrCourse newElm_Course(infotypeCourse newCourse){
    adrCourse C = new elmCourse;
    info(C) = newCourse;
    next(C) = NULL;
    prev(C) = NULL;
    nextStudent(C) = NULL;
    return C;
};
adrStudent newElm_Student(infotypeStudent newStudent){
    adrStudent S = new elmStudent;
    info(S) = newStudent;
    next(S) = NULL;
    prev(S) = NULL;
    return S;
};
//procedure menambah mata kuliah
void addCourse(listCourse &LC, adrCourse &C){

    if(first(LC) == NULL){//insert first
        first(LC) = C;
    }else{//insert last
        adrCourse P = first(LC);
        while(next(P) != NULL){//P diset menunjuk elemen terakhir di list
            P = next(P);
        }
        prev(C) = P;
        next(P) = C;
    }
};

//procedure menghapus mata kuliah
void deleteCourse(listCourse &LC, adrCourse &C){

    //menghapus data mata kuliah berdasarkan letak
    if(C == first(LC)){ //jika letak address mata kuliah di awal
        if(next(C) == NULL){
            first(LC) = NULL;
        }else{
            first(LC) = next(C);
            next(C) = NULL;
            prev(first(LC)) = NULL;
        }
    }else{
        adrCourse found = NULL; //mencari letak address mata kuliah selain di awal
        adrCourse P = first(LC);
        while(P != NULL && found == NULL){
            if(P == C){
                found = P;
            }
            P = next(P);
        }
        if(found != NULL){
            if(next(found) == NULL){//jika letak mata kuliah ada di akhir, menggunakan delete last
                next(prev(found)) = NULL;
                prev(found) = NULL;
            }else{//jika letak mata kuliah berada di tengah, menggunakan delete before
                adrCourse prec = prev(found);
                next(prec) = next(found);
                prev(next(found)) = prec;
                prev(found) = NULL;
                next(found) = NULL;
            }
        }else{
            cout << "Data mata kuliah tidak ditemukan"<<endl;
        }
    }
};

//procedure menambah mahasiswa
void addStudent(listCourse &LC, listStudent &LS, adrCourse C, adrStudent S){

    if(nextStudent(C) == NULL){//insert first
        nextStudent(C) = S;
    }else{//insert last
        adrStudent P = nextStudent(C);
        while(next(P) != NULL){//P diset menunjuk elemen terakhir di list
            P = next(P);
        }
        prev(S) = P;
        next(P) = S;
    }
};

//procedure menghapus mahasiswa
void deleteStudent(listCourse &LC, listStudent &LS, adrCourse C, adrStudent &S){

    if(S == nextStudent(C)){//delete first
        if(next(S) == NULL){
            nextStudent(C) = NULL;
        }else{
            nextStudent(C) = next(S);
            next(S) = NULL;
            prev(nextStudent(C)) = NULL;
        }
    }else{
        adrStudent found = NULL;
        adrStudent P = nextStudent(C);
        while(next(P) != NULL && found == NULL){
            if(P == S){
                found = P;
            }
            P = next(P);
        }
        if(found != NULL){
            if(next(found) == NULL){
                next(prev(found)) = NULL;
                prev(found) = NULL;
            }else{
                adrStudent prec = prev(S);
                next(prec) = next(S);
                prev(next(S)) = prec;
                prev(S) = NULL;
                next(S) = NULL;
            }

        }else{
            cout<< "Data mahasiswa tidak ditemukan."<<endl;
        }
    }
};

//procedure menghubungkan relasi mata kuliah dan mahasiswa
void setClass(listCourse &LC, listStudent &LS, adrStudent S, string courseName){
    adrCourse C = searchCourseByQuota(LC, courseName, info(S).studentType);

    //menyambungkan relasi
    if(C != NULL){
        addStudent(LC, LS, C, S);
    }else{
        cout << "Kuota pada mata kuliah "<< courseName <<" tidak tersedia :("<<endl;
    }
};

//procedure menghapus hubungan relasi mata kuliah dan mahasiswa
void deleteClass(listCourse &LC, listStudent &LS, string studentName, string courseName){
    adrStudent S = NULL;
    adrCourse C = NULL;
    searchStudentInCourse(LC, LS, studentName, courseName, S, C);
    cout<< info(C).courseName<<endl;
    cout<< info(S).studentName<<endl;

    //menghapus relasi
    deleteStudent(LC, LS, C, S);
};

//procedure update jumlah mahasiswa di setiap mata kuliah
void updateCount(listCourse LC, listStudent LS){
    adrCourse C = first(LC);

    while(C != NULL){
        adrStudent S = nextStudent(C);
        while(S != NULL){
            info(C).Count += 1;
            S = next(S);
        }
        C = next(C);
    }
};

//procedure menampilkan data semua mata kuliah beserta jumlah mahasiswa
void showCourses(listCourse LC){
    adrCourse C = first(LC);

    if(C == NULL){
        cout<<"Tidak ada mata kuliah yang ditawarkan."<<endl;
    }else{
        int i = 1;
        cout<<"---------------------------------------------------------------------------------------------------"<<endl;
        cout<< "| No \t | Mata kuliah \t\t | Kelas \t | Kuota | Jumlah Mahasiswa \t | Jenis Mahasiswa" <<endl;
        cout<<"---------------------------------------------------------------------------------------------------"<<endl;
        while(C != NULL){
            if(info(C).courseName.length() < 10){
                cout<< "|"<<i<<"\t | "<<info(C).courseName <<"\t\t | "<<info(C).className<< "\t | "<< info(C).quota<<"\t | "<<info(C).Count<<"\t\t\t | "<<info(C).studentType <<endl;
            }else{
                cout<< "|"<<i<<"\t | "<<info(C).courseName <<"\t | "<<info(C).className<< "\t | "<< info(C).quota<<"\t | "<<info(C).Count<<"\t\t\t | "<<info(C).studentType <<endl;
            }

            i++;
            C = next(C);
    }
    cout<<"---------------------------------------------------------------------------------------------------"<<endl;
    }


};

//procedure menampilkan data mahasiswa di MK dan kelas tertentu
void showStudentInCourse(listCourse LC, listStudent LS, string course, string Class){
    //mencari letak address course dan Class
    adrCourse C = first(LC);
    while(C != NULL ){
        if(info(C).courseName == course && info(C).className == Class){
            break;
        }
        C = next(C);
    }

    //menampilkan data mahasiswa
    if(nextStudent(C)== NULL){
        cout<<"Tidak terdapat mahasiswa yang terdaftar di mata kuliah ini."<<endl;
        cout<<endl;
    }else{
        adrStudent S = nextStudent(C);
        int i = 1;
        cout<< "Data Mahasiswa Mata Kuliah "<<course<<" Kelas "<<Class<<endl;
        cout<<endl;
        cout<<"-------------------------------------------------------------------------"<<endl;
        cout<< "No \t| Nama \t\t| NIM \t| Kelas Asal \t| Jenis Mahasiswa"<<endl;
        cout<<"-------------------------------------------------------------------------"<<endl;
        while(S != NULL){
            if(info(S).studentName.length() < 10){
                cout<< i << "\t| " <<info(S).studentName<<"\t\t| "<<info(S).studentID<<"\t| "<<info(S).classOrigin<<"\t| "<<info(S).studentType<<endl;
            }else{
                cout<< i << "\t| " <<info(S).studentName<<"\t| "<<info(S).studentID<<"\t| "<<info(S).classOrigin<<"\t| "<<info(S).studentType<<endl;
            }
            i++;
            S = next(S);
        }
        cout<<"-------------------------------------------------------------------------"<<endl;
        cout<<endl;
    }
};
//procedure menampilkan semua data mata kuliah beserta mahasiswanya
void showAllData(listCourse LC, listStudent LS){
    adrCourse C = first(LC);
    int i = 1;

    cout << "========== DATA REGISTRASI MATA KULIAH =========="<<endl;
    while(C != NULL){
        cout << "[          MATA KULIAH "<< i <<"          ]"<<endl;
        cout << "Mata Kuliah : "<< info(C).courseName<<endl;
        cout << "Kelas       : "<< info(C).className<<endl;
        cout << "Kuota Maksimal  : "<< info(C).quota<<endl;
        cout << "Jumlah Mahasiswa: "<< info(C).Count<<endl;
        cout << "Jenis Mahasiswa : "<< info(C).studentType<<endl;
        cout << "Data Mahasiswa  : "<<endl;
        cout << endl;
        showStudentInCourse(LC, LS, info(C).courseName, info(C).className);
        C = next(C);
        i++;
    }
};
//Mencari nama mk tertentu dengan kuota masih tersedia
adrCourse searchCourseByQuota(listCourse LC, string course, string type){
    adrCourse C = first(LC);
    while(C != NULL){
        if(info(C).courseName == course && info(C).Count < info(C).quota && info(C).studentType == type){
            return C;
            break;
        }
        C = next(C);
    }
    return NULL;
};

//Mencari nama mahasiswa tertentu pada sebuah MK
void searchStudentInCourse(listCourse LC, listStudent LS, string name, string course, adrStudent &S, adrCourse &C){
    C = LC.first;

    while (C != NULL)
    {
        S = C->nextStudent;

        while (S != NULL)
        {
            if (S->info.studentName == name && C->info.courseName == course)
            {
                return;
            }

            S = S->next;
        }

        C = C->next;
    }
    C = NULL;
    S = NULL;
};

int selectMenu(){
    cout<<"___________________________ MENU ______________________________________________"<<endl;
    cout<<"1. Menambahkan data mata kuliah baru"<<endl;
    cout<<"2. Menghapus mata kuliah"<<endl;
    cout<<"3. Mendaftar registrasi mata kuliah"<<endl;
    cout<<"4. Menghapus registrasi mata kuliah"<<endl;
    cout<<"5. Mengupdate jumlah mahasiswa di setiap mata kuliah" <<endl;
    cout<<"6. Menampilkan semua data mata kuliah yang ditawarkan beserta jumlah mahasiswa"<<endl;
    cout<<"7. Menampilkan data mahasiswa di mata kuliah dan kelas tertentu"<<endl;
    cout<<"8. Menampilkan seluruh mata kuliah beserta data mahasiswanya"<<endl;
    cout<<"9. Mencari nama mata kuliah tertentu dengan kuota masih tersedia"<<endl;
    cout<<"10. Mencari nama mahasiswa tertentu pada sebuah mata kuliah"<<endl;
    cout<<"11. Finalisasi registrasi"<<endl;
    cout<<"0. Exit"<<endl;
    cout<<"Masukkan menu : ";

    int input = 0;
    cin>> input;

    return input;
};
