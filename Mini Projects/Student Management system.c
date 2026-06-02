#include <stdio.h>
#include <string.h>

#define MAX 100

struct Student {
    int rollno;
    char name[50];
    int age;
    char department[50];
    float cgpa;
};

struct Student s[MAX];
int count = 0;


void addStudent() {
    printf("\nEnter Roll Number: ");
    scanf("%d", &s[count].rollno);

    printf("Enter Name: ");
    scanf(" %[^\n]", s[count].name);

    printf("Enter Age: ");
    scanf("%d", &s[count].age);

    printf("Enter Department: ");
    scanf(" %[^\n]", s[count].department);

    printf("Enter CGPA: ");
    scanf("%f", &s[count].cgpa);

    count++;
    printf("\nStudent Added Successfully!\n");
}


void displayStudents() {
    int i;

    if(count == 0) {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\n= STUDENT RECORDS =\n");

    for(i = 0; i < count; i++) {
        printf("\nStudent %d\n", i + 1);
        printf("Roll No    : %d\n", s[i].rollno);
        printf("Name       : %s\n", s[i].name);
        printf("Age        : %d\n", s[i].age);
        printf("Department : %s\n", s[i].department);
        printf("CGPA       : %.2f\n", s[i].cgpa);
    }
}


void searchStudent() {
    int roll, i;

    printf("\nEnter Roll Number to Search: ");
    scanf("%d", &roll);

    for(i = 0; i < count; i++) {
        if(s[i].rollno == roll) {
            printf("\nStudent Found!\n");
            printf("Roll No    : %d\n", s[i].rollno);
            printf("Name       : %s\n", s[i].name);
            printf("Age        : %d\n", s[i].age);
            printf("Department : %s\n", s[i].department);
            printf("CGPA       : %.2f\n", s[i].cgpa);
            return;
        }
    }

    printf("\nStudent Not Found!\n");
}


void updateStudent() {
    int roll, i;

    printf("\nEnter Roll Number to Update: ");
    scanf("%d", &roll);

    for(i = 0; i < count; i++) {
        if(s[i].rollno == roll) {

            printf("Enter New Name: ");
            scanf(" %[^\n]", s[i].name);

            printf("Enter New Age: ");
            scanf("%d", &s[i].age);

            printf("Enter New Department: ");
            scanf(" %[^\n]", s[i].department);

            printf("Enter New CGPA: ");
            scanf("%f", &s[i].cgpa);

            printf("\nRecord Updated Successfully!\n");
            return;
        }
    }

    printf("\nStudent Not Found!\n");
}


void deleteStudent() {
    int roll, i, j;

    printf("\nEnter Roll Number to Delete: ");
    scanf("%d", &roll);

    for(i = 0; i < count; i++) {
        if(s[i].rollno == roll) {

            for(j = i; j < count - 1; j++) {
                s[j] = s[j + 1];
            }

            count--;
            printf("\nRecord Deleted Successfully!\n");
            return;
        }
    }

    printf("\nStudent Not Found!\n");
}


void countStudents() {
    printf("\nTotal Number of Students: %d\n", count);
}

int main() {
    int choice;

    do {
        printf("\n\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Count Students\n");
        printf("7. Exit\n");

        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                countStudents();
                break;

            case 7:
                printf("\nThank You! Exiting Program...\n");
                break;

            default:
                printf("\nInvalid Choice! Please Try Again.\n");
        }

    } while(choice != 7);

    return 0;
}