#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    char name[100];
    int age;
    float salary;
};

struct Booking {
    char customerName[100];
    int roomNumber;
    int days;
    char roomCategory[2];
}booking;

void showAllEmployees() { 
    FILE *file = fopen("employee.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    struct Employee employee;
    printf("\t\t\t\t\t    Employee Records\n");
    printf("\t\t\t\t\t-------------------------\n");
    printf("\t\t\t\t\tName\tAge\tSalary\n");
     printf("\t\t\t\t\t-------------------------\n");

    while (fread(&employee, sizeof(struct Employee), 1, file)) {
        printf("\t\t\t\t\t%s\t%d\t%.2f\n", employee.name, employee.age, employee.salary);
    }

    fclose(file);
}

void registerNewEmployee() { 
    FILE *file = fopen("employee.txt", "a");
    if (file == NULL) {
        printf("\t\tError opening the file.\n");
        return;
    }

    struct Employee employee;
    printf("\t\tEnter employee name: ");
    scanf("\t\t%s", employee.name);

    printf("\t\tEnter employee age: ");
    scanf("\t\t%d", &employee.age);

    printf("\t\tEnter employee salary: ");
    scanf("\t\t%f", &employee.salary);

    fwrite(&employee, sizeof(struct Employee), 1, file);
    fclose(file);

    printf("\t\tEmployee registered successfully.\n");
}

void updateEmployeeRecord() { 
    FILE *file = fopen("employee.txt", "r+");
    if (file == NULL) {
        printf("\t\tError opening the file.\n");
        return;
    }

    char searchName[100];
    printf("\t\tEnter the name of the employee to update: ");
    scanf("\t\t%s", searchName);

    struct Employee employee;
    int found = 0;
    while (fread(&employee, sizeof(struct Employee), 1, file)) {
        if (strcmp(employee.name, searchName) == 0) {
            printf("\t\tEnter employee's new age: ");
            scanf("\t\t%d", &employee.age);

            printf("\t\tEnter employee's new salary: ");
            scanf("\t\t%f", &employee.salary);

            fseek(file, -sizeof(struct Employee), SEEK_CUR);
            fwrite(&employee, sizeof(struct Employee), 1, file);

            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        printf("\t\tEmployee record updated successfully.\n");
    } else {
        printf("\t\tEmployee not found.\n");
    }
}

void deleteEmployeeRecord() {
    FILE *file = fopen("employee.txt", "r+");
    if (file == NULL) {
        printf("\t\tError opening the file.\n");
        return;
    }

    char searchName[100];
    printf("\t\tEnter the name of the employee to delete: ");
    scanf("\t\t%s", searchName);

    struct Employee employee;
    int found = 0;
    while (fread(&employee, sizeof(struct Employee), 1, file)) {
        if (strcmp(employee.name, searchName) == 0) {
            fseek(file, -sizeof(struct Employee), SEEK_CUR);
            fwrite("\0", sizeof(struct Employee), 1, file);

            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        printf("\t\tEmployee record deleted successfully.\n");
    } else {
        printf("\t\tEmployee not found.\n");
    }
}

void showAllBookings() { 
    FILE *file = fopen("booking.txt", "r");
    if (file == NULL) {
        printf("\t\tError opening the file.\n");
        return;
    }

    struct Booking booking;
    printf("\t\t\t\t\t          Booking Records\n");
    printf("\t\t\t\t------------------------------------------------------\n");
    printf("\t\t\t\tCustomer Name\tRoom Number\tDays\tRoom Category\n");
    printf("\t\t\t\t------------------------------------------------------\n");

    while (fread(&booking, sizeof(struct Booking), 1, file)) {
        printf("\t\t\t\t%s\t\t  %d\t\t%d\t    %s\n", booking.customerName, booking.roomNumber, booking.days, booking.roomCategory);
    }

    fclose(file);
}

void makeNewBooking() { 
    FILE *file = fopen("booking.txt", "a");
    if (file == NULL) {
        printf("\t\tError opening the file.\n");
        return;
    }

    struct Booking booking;
    printf("\t\tEnter customer name: ");
    scanf("\t\t%s", booking.customerName);

    printf("\t\tEnter room number: ");
    scanf("\t\t%d", &booking.roomNumber);

    printf("\t\tEnter number of days: ");
    scanf("\t\t%d", &booking.days);

    printf("\t\tEnter room category (S/L/B/E): ");
    scanf("\t\t%s", booking.roomCategory);

    fwrite(&booking, sizeof(struct Booking), 1, file);
    fclose(file);

    printf("\t\tBooking made successfully.\n\n");
	generateReceipt(booking);
}

void generateReceipt(struct Booking booking) {
    float chargesPerDay, discount = 0, tax = 1500;
    
    printf("\t\t-----JADE HOTEL-----\n");
    printf("\t\t--------------------\n");
    printf("\n\t\t--- Receipt ---\n");
    printf("\t\tCustomer Name: %s\n", booking.customerName);
    printf("\t\tRoom Number: %d\n", booking.roomNumber);
    printf("\t\tDays: %d\n", booking.days);
    printf("\t\tRoom Category: %s\n", booking.roomCategory);

    switch (booking.roomCategory[0]) {
        case 'S':
            chargesPerDay = 12000;
            if (booking.days >= 4)
                discount = 0.2 * chargesPerDay;
            break;
        case 'L':
            chargesPerDay = 10500;
            if (booking.days >= 10)
                discount = 0.12 * chargesPerDay;
            break;
        case 'B':
            chargesPerDay = 7500;
            if (booking.days >= 12)
                discount = 0.1 * chargesPerDay;
            break;
        case 'E':
            chargesPerDay = 5000;
            if (booking.days >= 12)
                discount = 0.05 * chargesPerDay;
            break;
        default:
            printf("\t\tInvalid room category.\n");
            return;
    }

    float totalCharges = chargesPerDay * booking.days;
    float netAmount = totalCharges - discount + tax;

    printf("\t\tCharges per day: %.2f\n", chargesPerDay);
    printf("\t\tTotal Charges: %.2f\n", totalCharges);
    printf("\t\tDiscount: %.2f\n", discount);
    printf("\t\tTax: %.2f\n", tax);
    printf("\t\tNet Amount: %.2f\n", netAmount);
}

char admin_entry[20] = {'y'};

int main() {
	time_t t;
	time(&t);
	int choice,i;
    

     //Welcome screen
        for(i=0;i<120;i++){
		
		printf("-");}
		for(i=0;i<120;i++){
		
		printf("*");}
	    printf("\n\t\t\t\t\tWELCOME TO JADE HOTEL MANAGEMENT SYSTEM\n\n");
	    for(i=0;i<120;i++){
		
		printf("*");}
	    for(i=0;i<120;i++){
		
		printf("-");}
		printf("\n\n");
		 
		printf("Our service is based on our values of integrity, teamwork and trust.\nWe take ownership and pride in everything we do.\n\n");                                      

		for(i=0;i<120;i++){
		
		printf("-");}
	    printf("\n\t\t\t\tCurrent date and time : %s",ctime(&t));
	    for(i=0;i<120;i++){
		
		printf("-");}
	printf(" \n Press any key to continue:");
	
	getch();	
    system("cls");
	
    char pass[10];
                char filepass[10];

                FILE *passw;
                passw = fopen("pass.txt","r");

                //admins password prompt
                printf("\n\tHello admin!\n\tPlease enter the password to continue --> ");

                for(i=0; i<6; i++){
                    scanf("%s",pass);
                    fscanf(passw,"%s",filepass);
                    if (strcmp(filepass,pass) == 0) {
                        printf("\n\tAccess granted!\n");
                        printf("\tPress any key to continue:");
                      	getch();	
                        system("cls");
                        fclose(passw);
                        break;
                    }
                    else{
                     printf("\n\tIncorrect password, please try again.");
                     printf("\n\tYou have %d trys left ",5-i-1);
                     printf("\n\n\tEnter password >> ");
                    }
                    if(i==4){
                        fclose(passw);
                        return 0;
                    }

               
                }

                 //re-entry if
                while(admin_entry[0] =='y'){

        do {
        printf("\n\t\t\t------------------------------------------------------------------\n");
        printf("\n\t\t\t------------------ Jade Hotel Management System ------------------\n");
        printf("\n\t\t\t------------------------------------------------------------------\n");
        printf("\t\t\t\t\t\tMAIN MENU\n");
        printf("\n\t\t\t------------------------------------------------------------------\n");
        printf("\t\t\t\t\t1. Show all employees\n");
        printf("\t\t\t\t\t2. Register new employee\n");
        printf("\t\t\t\t\t3. Update employee record\n");
        printf("\t\t\t\t\t4. Delete employee record\n");
        printf("\t\t\t\t\t5. Show all bookings\n");
        printf("\t\t\t\t\t6. Create new booking + Generate Receipt\n");
        printf("\t\t\t\t\t7. Exit\n");
        printf("\n\t\t\t------------------------------------------------------------------\n");
        printf("\t\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);
        system("cls");
		
        switch (choice) {
            case 1:
                system("cls");
                printf("\n\n");
				showAllEmployees();
				printf("\n\n\n\n\n");
                break;
            case 2:
                system("cls");
                printf("\n\n");
				registerNewEmployee();
				printf("\n\n\n\n\n");
                break;
            case 3:
                system("cls");
                printf("\n\n");
				updateEmployeeRecord();
				printf("\n\n\n\n\n");
                break;
            case 4:
                system("cls");
                printf("\n\n");
				deleteEmployeeRecord();
				printf("\n\n\n\n\n");
                break;
            case 5:
                system("cls");
                printf("\n\n");
				showAllBookings();
				printf("\n\n");
                break;
            case 6:
                system("cls");
                printf("\n\n");
				makeNewBooking();
				printf("\n\n");
                break;
            case 7:
            	system("cls");
            	printf("\n");
				generateReceipt(booking);
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("\t\tInvalid choice. Please try again.\n");
                break;
        }
    } while (choice != 7);
    printf("Would you like to continue? (y/n)\n");
                scanf("%s",admin_entry);

                }
                if(strcmp(admin_entry,"n") == 0){
                    printf("Exiting...\n");
                    printf("\e[1;1H\e[2J");
                    printf("\n >Exited<\n\n");
                    //system("clear");
                    return 0;
                }
                else{
                    printf("\t\tWrong entry!\nExiting...\n");
                    return 0;
                }
                return 0;
            }

        

