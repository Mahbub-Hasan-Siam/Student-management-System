#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Student {
    int id;
    char name[100];
    char department[50];
    float gpa;
};

struct Student students[MAX];
int count = 0;

// Function prototypes
void loadFromFile();
void saveToFile();
void addStudent();
void viewAllStudents();
void searchStudent();
void deleteStudent();
void menu();

int main() {
    loadFromFile();
    menu();
    saveToFile();
    return 0;
}

void menu() {
    int choice;

    do {
        printf("\n=== Student Management System ===\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Delete Student by ID\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch(choice) {
            case 1: addStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: printf("Saving and exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 5);
}

void addStudent() {
    if (count >= MAX) {
        printf("Database full!\n");
        return;
    }

    struct Student s;
    printf("\nEnter ID: ");
    scanf("%d", &s.id);
    getchar(); // consume newline

    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0'; // remove newline

    printf("Enter Department: ");
    fgets(s.department, sizeof(s.department), stdin);
    s.department[strcspn(s.department, "\n")] = '\0';

    printf("Enter GPA: ");
    scanf("%f", &s.gpa);

    students[count++] = s;
    printf("Student added successfully!\n");
}

void viewAllStudents() {
    if (count == 0) {
        printf("\nNo students found.\n");
        return;
    }

    printf("\n%-5s %-20s %-15s %-5s\n", "ID", "Name", "Department", "GPA");
    printf("---------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-15s %-5.2f\n", students[i].id, students[i].name, students[i].department, students[i].gpa);
    }
}

void searchStudent() {
    int id;
    printf("\nEnter ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("\nStudent Found:\n");
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Department: %s\n", students[i].department);
            printf("GPA: %.2f\n", students[i].gpa);
            return;
        }
    }
    printf("Student not found.\n");
}

void deleteStudent() {
    int id, index = -1;
    printf("\nEnter ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    for (int i = index; i < count - 1; i++) {
        students[i] = students[i + 1];
    }
    count--;
    printf("Student deleted successfully.\n");
}

void saveToFile() {
    FILE *fp = fopen("students.txt", "w");
    if (fp == NULL) {
        printf("Error saving file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%s,%.2f\n", students[i].id, students[i].name, students[i].department, students[i].gpa);
    }

    fclose(fp);
}

void loadFromFile() {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) return;

    while (fscanf(fp, "%d,%[^,],%[^,],%f\n", &students[count].id, students[count].name, students[count].department, &students[count].gpa) == 4) {
        count++;
    }

    fclose(fp);
}
