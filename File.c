#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Define the structure for employee information
struct Employee {
    int empID;
    char name[50];
    char designation[50];
    float salary;
};
// Function to add employee information to the file
void addEmployee(FILE *file, struct Employee *emp) {
    fseek(file, 0, SEEK_END);
    fwrite(emp, sizeof(struct Employee), 1, file);
}
// Function to display employee information by employee ID
void displayEmployee(FILE *file, int empID) {
    struct Employee emp;
    int found = 0;
    rewind(file);
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.empID == empID) {
            printf("Employee ID: %d\n", emp.empID);
            printf("Name: %s\n", emp.name);
            printf("Designation: %s\n", emp.designation);
            printf("Salary: %.2f\n", emp.salary);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Employee with ID %d not found.\n", empID);
    }
}
// Function to delete employee information by employee ID
void deleteEmployee(FILE *file, int empID) {
    FILE *tempFile = fopen("temp.txt", "w");
    struct Employee emp;
    int found = 0;
    rewind(file);
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.empID != empID) {
            fwrite(&emp, sizeof(struct Employee), 1, tempFile);
        } else {
            found = 1;
        }
    }
    fclose(file);
    fclose(tempFile);
    remove("employee.txt");
    rename("temp.txt", "employee.txt");

    file = fopen("employee.txt","ab+");
    
    if (found) {
        printf("Employee with ID %d deleted successfully.\n", empID);
    } else {
        printf("Employee with ID %d not found.\n", empID);
    }
}

int main() {
    FILE *file = fopen("employee.txt", "ab+");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    int choice;
    struct Employee emp;
    do {
        printf("\n1. Add Employee\n2. Display Employee\n3. Delete Employee\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &emp.empID);
                printf("Enter Name: ");
                scanf("%s", emp.name);
                printf("Enter Designation: ");
                scanf("%s", emp.designation);
                printf("Enter Salary: ");
                scanf("%f", &emp.salary);
                addEmployee(file, &emp);
                break;
            case 2:
                printf("Enter Employee ID to display: ");
                scanf("%d", &emp.empID);
                displayEmployee(file, emp.empID);
                break;
            case 3:
                printf("Enter Employee ID to delete: ");
                scanf("%d", &emp.empID);
                deleteEmployee(file, emp.empID);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 4);
    fclose(file);
    return 0;
}