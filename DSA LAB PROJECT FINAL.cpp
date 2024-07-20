#include <iostream>
#include <string>


using namespace std;

const int MAX_USERS = 100; // Maximum number of users

// Struct to hold user data
struct User {
    int id;
    string name;
    int age;
    int year_in_university; // Current year in uni
    string dept;
};

void bubbleSort(User arr[], int size, string sort_according_to) {
    bool swapped;
    for (int i = 0; i < size - 1; ++i) {
        swapped = false;
        for (int j = 0; j < size - 1 - i; ++j) {
            // Sort according to year
            if(sort_according_to == "year"){
                if (arr[j].year_in_university > arr[j + 1].year_in_university) {
                    User temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    swapped = true;
                }
            } 
            // Sort according to ID
            else {
                if (arr[j].id > arr[j + 1].id) {
                    User temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    swapped = true;
                }
            }
        }
        if(!swapped) break;
    }
}

void traverseStudent (User std[], int size){
    for(int i=0; i<size ; i++){
        cout<<std[i].id<<" \t "<<std[i].name<<" \t "<<std[i].dept<<" \t "<<std[i].year_in_university<<" \t "<<std[i].age<<endl;
    }
}

// &cs_size and &bba_size === passing them as a reference variable to update them
void insertIntoDepartment( User all_student[], User cs_dept[], User bba_dept[], int all_std_size, int &cs_size, int &bba_size  ){
    for(int i = 0 ; i<all_std_size ; i++){
        if(all_student[i].dept == "BBA"){
            bba_dept[bba_size] = all_student[i];
            bba_size++;
        } else {
            cs_dept[cs_size] = all_student[i];
            cs_size++;
        }
    }
}


// Add New Student into ALL Students
void addStudent(User student[], int &student_size){
    cout<<"--- Enter Information ---"<<endl;
    cout<<"ID (integer) : ";
    cin>>student[ student_size ].id;
    cin.ignore(); // Ignore the newline character after the number input
    cout<<"Name : ";
    getline(cin, student[ student_size ].name);
    // for better presentation 
    int nameLength = student[student_size].name.length();
    for(int i = nameLength; i<12; i++ ){
        student[student_size].name += " ";  // Add spaces if length is less than 12 
    }
    cout<<"Department (CS or BBA) : ";
    cin>>student[ student_size ].dept;
    cout<<"Current Year : ";
    cin>>student[ student_size ].year_in_university;
    cout<<"Age : ";
    cin>>student[ student_size ].age;
    
    student_size++;
    cout<<"\n------ Student Added Successfully !! ------ "<<endl;
}


// Find Student - Binary & Linear Search
void findStudent(User student[], int size){
    string name;
    int option, id;
    cout<<"\n1. Find with Name \n2. Find With ID"<<endl;
    cout<<"Enter Choice : ";
    cin>>option;
    
    User temp_student[10];
    int temp_size;
    bool found;

    // For binary search
    int start, end;
    switch (option) {
        case 1:
            cout<<"Enter Name : ";
            cin.ignore();
            getline(cin, name);
            found = false;
            temp_size = 0;
            //Linear Search
            for(int i =0; i<size; i++){
                if(student[i].name == name){
                    temp_student[temp_size] = student[i];
                    temp_size++;
                    found = true;
                } 
            }
        break;
        
        case 2:
            cout<<"Enter ID : ";
            cin>>id;
            found = false;
            temp_size = 0;
            bubbleSort(student, size, "id");
            // Binary Search
            start = 0; 
            end = size -1;
            while( start <= end ) {
                int mid = end + (start - end)/2;
                if(student[mid].id == id){
                    temp_student[temp_size] = student[mid];
                    temp_size++;
                    found = true;
                    break;
                }
                else if(student[mid].id < id){
                    start = mid + 1;
                } else {
                    end = mid - 1;
                }
            }
        break;
            
        
        default:
            cout<<"**** Invalid Option ! **** "<<endl;
        break;
    }
    if(found) {
        cout<<"\n---- Student found  ----"<<endl;
        cout<<"\nID \t Name \t\t Dept. \t Year \t Age"<<endl;
        traverseStudent(temp_student, temp_size);
    } else {
        cout<<"\n---- Student not found !! ----"<<endl;
        cout<<"Message: There might be a Typo or Student doesn't exist \n Verify it by visiting student list."<<endl;
    }
    
}


// ---- Stack - Trash holding removed students
void push(User stack[], int &top, User removed_student){
    if(top == 10-1 ){
        cout<<"\n *** Stack Overflow - Trash is full ***"<<endl;
        return;
    } else if(! removed_student.name.empty()  ) {
        top++;
        stack[top] = removed_student;
    }
}

User pop(User stack[], int &top){
    if(top == -1){
        cout<<"\n *** Stack underflow - No student present in the trash ***"<<endl;
        return stack[top];
    } else {
        top--;
    }
    return stack[ top + 1 ];
}

void peak(User stack[], int top){
    if(top == -1){
        cout<<"\n *** Trash is empty ***"<<endl;
    } else {
        cout<<"======= Trash ======="<<endl;
        cout<<"\nID \t Name \t\t Dept. \t Year \t Age"<<endl;
        for(int i = top; i>=0; i--){
            cout<<stack[i].id<<" \t "<<stack[i].name<<" \t "<<stack[i].dept<<" \t "<<stack[i].year_in_university<<" \t "<<stack[i].age<<endl;
        }

    }
}

User removeStudent(User student[], int &student_size){
    int id;
    cout<<"\nEnter ID : ";
    cin>>id;
    User temp;
    bool found = false;
    for(int i=0; i<student_size; i++){
        if(student[i].id == id){
            temp  = student[i];
            found = true;
            // Filling the gape if present
            for(int j = i; j < student_size-1; j++){
                student[j] = student[j+1];
            }
            student_size--;
            break;
        }
    }
    if(!found){
        cout<<"\n**** Invalid ID ****"<<endl;
    } else {
        cout<<" **** The Student "<<temp.name<<" ("<<temp.id<<") is removed ! **** "<<endl;
        return temp;
    }
}

void restoreStudent(User student[], int &student_size, User restored_student){
    if(! restored_student.name.empty()){
        cout<<"------ Student restored Successfully !! ------ "<<endl;
        student[student_size] = restored_student;
        student_size++;
    } 
}

int main(){
    cout<<"\n----------- AABS STUDENT MANAGEMENT -----------"<<endl<<endl;
    int numOfUsers;
    
    User students[MAX_USERS]; // Array to store user data
    User cs_student[MAX_USERS];
    User bba_student[MAX_USERS];

    User trash_student[10]; // Stack of trash
    int top = -1;


    // Default Students.
    students[0].id = 1;
    students[0].name = "Sheikh Bilal";
    students[0].age = 21;
    students[0].year_in_university = 3;
    students[0].dept = "CS";

    students[1].id = 2;
    students[1].name = "Ali Fazal";
    students[1].age = 22;
    students[1].year_in_university = 2;
    students[1].dept = "BBA";

    students[2].id = 3;
    students[2].name = "Hamza Khan";
    students[2].age = 22;
    students[2].year_in_university = 1;
    students[2].dept = "CS";

    int option,
        students_size=3,
        cs_student_size=0,
        bba_student_size =0,    
        loop=1, 
        sub_choice;

    while(loop==1){
        cout<<"\n====== MENU ======"<<endl;
        cout<<"1. Show Student \n2. Add New Student \n3. Find Student \n4. Remove Student \n5. Restore Student (trash) \n6. View Trash \n7. Exit"<<endl;
        cout<<"\nEnter Choice : ";
        cin>>option;
        switch (option) {
        case 1:
            cout<<"1. All Student (Sorted according to IDs) \n2. All Students (sorted according to current year in University) \n3. According to Department (Sorted according to IDs)"<<endl;
            cout<<"\nEnter choice : ";
            cin>>sub_choice;
            cout<<"\nID \t Name \t\t Dept. \t Year \t Age"<<endl;
            if(sub_choice == 1){
                bubbleSort(students, students_size, "id");
                traverseStudent(students, students_size);

            } else if(sub_choice == 2){
                bubbleSort(students, students_size, "year");
                traverseStudent(students, students_size);
            } else if(sub_choice == 3 ){
                insertIntoDepartment(students, cs_student, bba_student, students_size, cs_student_size, bba_student_size);
                bubbleSort(cs_student, cs_student_size, "id");
                bubbleSort(bba_student, bba_student_size, "id");

                cout<<"\n-- Computer Science --"<<endl;
                traverseStudent(cs_student, cs_student_size);

                cout<<"\n-- BBA --"<<endl;
                traverseStudent(bba_student, bba_student_size);
            }
            break;
        
        case 2:
            addStudent(students, students_size);
            bubbleSort(students, students_size, "id");

            break;
        
        case 3: 
            findStudent(students, students_size);
            break;

        case 4:
             push(trash_student, top, removeStudent(students, students_size));
             break;
            
        case 5:
            restoreStudent(students, students_size, pop(trash_student, top));
            break;    

        case 6: 
            peak(trash_student, top);
            break;

        case 7:
            cout<<"\n---- Exit Successfully !! ----\n\n"<<endl;
            loop = 0;
            break;
        default:
            break;
        }
    }




}