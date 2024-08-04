#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#pragma warning (disable: 4996)
#define MAX_SCHEDULES 30
#define MAX_BOOKINGS 80
#define MAX_RECORDS 100  
#define MAX_MEMBER 100
#define MAX_STAFFS 100
#define MAX_SEATS 80

typedef struct {
	char staffID[7];
	char name[20];
	char gender;
	char password[11];
	char position[30];
} staffInfo;

typedef struct {
	char passwordRecovery[5];
	staffInfo info;
}staffRecord;

// Structure variable for storing IC
typedef struct {
	int birthDate;
	int area;
	int uniqueID;
} IC;

// Members Info
struct Members {
	char name[31];
	char memberID[6];
	char gender;
	IC memberIC;
	int contactNum;
	char bookingID[6];
	char password[9];
	int passRecover;
};

typedef struct { //Structure for storing date and time
	char departureDate[12];
	char departureTime[5];
	char arrivalTime[5];
}DateTime;


typedef struct { //Structure for storing schedule information
	int number;
	char trainId[10];
	char departureLocation[30];
	char destination[30];
	DateTime dateTime[200];
	double fare;
	int distance;
	double duration;
	int availableSeats;
	char id[6];
}Schedule;

typedef struct {
	char bookingID[10];
	char memberID[10];
	char trainID[10];
	char bookingDate[12];
	char departureDate[12];
	int seatNumberRow[40];
	int seatNumberColumn[40];
	int quantity[10];
	char paymentInfo[100];
	double amount;
	char staffID[7];
} Booking;

typedef struct {
	Booking bookings[MAX_BOOKINGS];
	int numBookings;
}BookingManager;

typedef struct {
	Schedule schedules[MAX_SCHEDULES];
	int numSchedules;
} ScheduleManager;

typedef struct {
	staffInfo staffInfos[MAX_STAFFS];
	int numStaffs;
} StaffManager;


void SignIn(int* identity, char id[]) {
	FILE* readBinary;
	readBinary = fopen("memberdata.bin", "rb");
	if (!readBinary) {
		printf("File not exist!\n");
		return;
	}

	struct Members member[200];

	int count = 0;
	while (fread(&member[count], sizeof(struct Members), 1, readBinary) != 0) {
		count++;
	}

	fclose(readBinary);

	FILE* fptr = fopen("staff.txt", "r"); // Open the file in read mode
	if (fptr == NULL) {
		printf("Error opening file.\n");
		selectionStaff(); // Return to the main loop
		return;
	}

	staffRecord employee[100];

	for (int i = 0; i < 100; i++) {
		fscanf(fptr, "%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^\n]\n", employee[i].info.staffID,
			employee[i].info.name, &employee[i].info.gender, employee[i].info.password, employee[i].passwordRecovery, employee[i].info.position);
	}

	fclose(fptr);
	char password[15];
	printf("Enter Account ID :");
	scanf("%s", id);
	printf("Enter Password :");
	scanf("%s", password);

	for (int n = 0; n < MAX_MEMBER; n++) {
		if (strcmp(id, employee[n].info.staffID) == 0 && strcmp(password, employee[n].info.password) == 0) { //modify it for staff after woonwai
			*identity = 0;
			break;
		}

		else if (strcmp(id, member[n].memberID) == 0 && strcmp(password, member[n].password) == 0) {
			*identity = 1;
			break;
		}

	}

	while (*identity == -1) {
		printf("Invalid ID / Password. Please Try Again\n");
		printf("Enter Account ID :");
		scanf("%s", id);
		printf("Enter Password :");
		scanf("%s", password);

		for (int n = 0; n < MAX_MEMBER; n++) {
			if (strcmp(id, employee[n].info.staffID) == 0 && strcmp(password, employee[n].info.password) == 0) {
				*identity = 0;
				break;
			}

			else if (strcmp(id, member[n].memberID) == 0 && strcmp(password, member[n].password) == 0) {
				*identity = 1;
				break;
			}

		}

	}
}

int StaffInformationMain() {
	// Loop until the user chooses to exit the program
	while (1) {
		if (selectionStaff() == 0) {
			break; // Exit the loop if selection returns 0
		}
	}
	printf("\n=====You Have Already Exit. Have a great day!=====\n");
}

//This is a selection for staff when they enter staff mode
int selectionStaff() {
	int slt;

	do {
		printf("   ______________    ____________   _____   ____________  \n");
		printf("  / ___/_  __/   |  / ____/ ____/  /  _/ | / / ____/ __ \\ \n");
		printf(" \\___ \\ / / / /| | / /_  / /_      / //  |/ / /_  / / / / \n");
		printf(" ___/ // / / ___ |/ __/ / __/    _/ // /|  / __/ / /_/ /  \n");
		printf("/____//_/ /_/  |_/_/   /_/      /___/_/ |_/_/    \\____/   \n");

		printf("\n");
		printf("SELECT YOUR SERVE !!!\n");
		printf("--------------------------------------------\n");

		printf("1.Display\n");
		printf("2.Add Information\n");
		printf("3.Search Staff\n");
		printf("4.Modify Information\n");
		printf("5.Delete Information\n");
		printf("6.Password Forgot\n");
		printf("7.Exit\n");
		printf("Enter your selection here >>>>");
		rewind(stdin);
		scanf("%d", &slt);

		if (slt < 1 || slt > 7) {
			printf("Invalid selection. Please enter a number between 1 and 7.\n\n");
		}
	} while (slt < 1 || slt > 7); // Continue looping until a valid selection is made

	switch (slt) {
	case 1:
		system("cls");
		displayStaff();
		break;
	case 2:
		system("cls");
		addStaff();
		break;
	case 3:
		system("cls");
		searchStaff();
		break;
	case 4:
		system("cls");
		modifyStaff();
		break;
	case 5:
		system("cls");
		deleteeStaff();
		break;
	case 6:
		system("cls");
		forgotStaff();
		break;
	case 7:
		return 0;
		break;
	}
}

//Below is the 6 different function
int displayStaff() {
	FILE* fptr = fopen("staff.txt", "r"); // Open the file in read mode
	if (fptr == NULL) {
		printf("Error opening file.\n");
		selectionStaff(); // Return to the main loop
		return;
	}

	staffRecord employee[100];

	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("| %-8s | %-15s | %-2s | %-11s | %-17s | %-15s |\n", "Staff ID", "Name", "Gender", "Password", "Password Recovery", "Position");
	printf("------------------------------------------------------------------------------------------------------------------------\n");

	int i = 0;
	while (fscanf(fptr, "%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^\n]\n", employee[i].info.staffID, employee[i].info.name, &employee[i].info.gender, employee[i].info.password, employee[i].passwordRecovery, employee[i].info.position) != EOF) {
		printf("| %-8s | %-15s | %-6c | %-11s | %-17s | %-15s |\n", employee[i].info.staffID, employee[i].info.name, employee[i].info.gender, employee[i].info.password, employee[i].passwordRecovery, employee[i].info.position);
		i++;
	}

	printf("\n------------------------------------------------------------------------------------------------------------------------\n");
	fclose(fptr);// Close the file
	// Return to the main loop
	selectionStaff();
}

int addStaff() {
	FILE* fptr;
	if ((fptr = fopen("staff.txt", "a")) == NULL) {
		printf("Error opening file!");
		return;
	}

	staffRecord new_staff;
	char choice;

	do {

		// Input validation loop
		do {
			printf("Enter Staff Id: ");
			scanf(" %7[^\n]", new_staff.info.staffID);
		} while (!validateStaffId(new_staff.info.staffID)); // Repeat until valid staff ID is entered

		do {
			printf("Enter name: ");
			scanf(" %19[^\n]", new_staff.info.name);
		} while (!validateName(new_staff.info.name)); // Repeat until valid name is entered

		do {
			printf("Enter gender (M/F): ");
			scanf(" %c", &new_staff.info.gender);
		} while (!validateGender(new_staff.info.gender)); // Repeat until valid gender is entered

		do {
			printf("Enter password : ");
			scanf("%11s", new_staff.info.password);
		} while (!validatePassword(new_staff.info.password)); // Repeat until valid password is entered

		do {
			printf("Enter password recovery: ");
			scanf("%5s", new_staff.passwordRecovery);
		} while (!validatePasswordRecovery(new_staff.passwordRecovery)); // Repeat until valid recovery code is entered

		do {
			printf("Enter position: ");
			scanf(" %29[^\n]", new_staff.info.position);
		} while (!validatePosition(new_staff.info.position)); // Repeat until valid position is entered

		// Write the new record to the file
		fprintf(fptr, "\n%s|%s|%c|%s|%s|%s", new_staff.info.staffID, new_staff.info.name, new_staff.info.gender, new_staff.info.password, new_staff.passwordRecovery, new_staff.info.position);

		printf("\nAdd another record? (Y/N): ");
		scanf(" %c", &choice);

		// Flush the input buffer to prevent issues with subsequent input
		while (getchar() != '\n');

	} while (toupper(choice) == 'Y');

	fclose(fptr);

	// Display the message only after all records are added
	printf("Records added successfully.\n");

	// Go back to the selection menu
	selectionStaff();
}

int searchStaff() {
	char idToSearch[10];
	printf("Enter staff ID to search: ");
	scanf("%9s", idToSearch);

	FILE* fptr;
	if ((fptr = fopen("staff.txt", "r")) == NULL) {
		printf("Error opening file!\n");
		return;
	}

	staffRecord employee;
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("| %-8s | %-15s | %-2s | %-7s | %-10s | %-15s |\n", "Staff ID", "Name", "Gender", "Password Recovery", "Password", "Position");
	printf("------------------------------------------------------------------------------------------------------------------------\n");

	int found = 0;
	while (fscanf(fptr, "%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^\n]\n", employee.info.staffID, employee.info.name, &employee.info.gender, employee.info.password, employee.passwordRecovery, employee.info.position) == 6) {
		if (strcmp(employee.info.staffID, idToSearch) == 0) {
			printf("| %-8s | %-15s | %-6c | %-17s | %-10s | %-15s |\n", employee.info.staffID, employee.info.name, employee.info.gender, employee.info.password, employee.passwordRecovery, employee.info.position);
			found = 1;
			break;
		}
	}

	if (!found) {
		printf("No record found with staff ID: %s\n", idToSearch);
	}

	printf("------------------------------------------------------------------------------------------------------------------------\n");
	fclose(fptr);
}

int modifyStaff() {
	char idToModify[10];
	printf("Enter staff ID to modify: ");
	scanf("%9s", idToModify);

	FILE* fptr, * tempPtr;
	if ((fptr = fopen("staff.txt", "r")) == NULL) {
		printf("Error opening file!\n");
		return;
	}

	if ((tempPtr = fopen("temp.txt", "w")) == NULL) {
		printf("Error opening temporary file!\n");
		fclose(fptr);
		return;
	}

	staffRecord employee;
	int found = 0;
	while (fscanf(fptr, "%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^\n]\n", employee.info.staffID, employee.info.name, &employee.info.gender, employee.info.password, employee.passwordRecovery, employee.info.position) == 6) {
		if (strcmp(employee.info.staffID, idToModify) == 0) {

			printf("Enter Staff Id: ");
			scanf(" %7[^\n]", employee.info.staffID);
			while (!validateStaffId(employee.info.staffID)) {
				printf("Enter Staff Id: ");
				scanf(" %7[^\n]", employee.info.staffID);
			}

			printf("Enter new name: ");
			scanf(" %19[^\n]", employee.info.name);
			while (!validateName(employee.info.name)) {
				printf("Enter new name: ");
				scanf(" %19[^\n]", employee.info.name);
			}

			printf("Enter new gender (M/F): ");
			scanf(" %c", &employee.info.gender);
			while (!validateGender(employee.info.gender)) {
				printf("Enter new gender (M/F): ");
				scanf(" %c", &employee.info.gender);
			}

			printf("Enter new password: ");
			scanf("%19s", employee.info.password);
			while (!validatePassword(employee.info.password)) {
				printf("Enter new password: ");
				scanf("%19s", employee.info.password);
			}

			printf("Enter new password recovery: ");
			scanf("%10s", employee.passwordRecovery);
			while (!validatePasswordRecovery(employee.passwordRecovery)) {
				printf("Enter new password recovery: ");
				scanf("%5s", employee.passwordRecovery);
			}

			printf("Enter new position: ");
			scanf(" %29[^\n]", employee.info.position);
			while (!validatePosition(employee.info.position)) {
				printf("Enter new position: ");
				scanf(" %29[^\n]", employee.info.position);
			}

			fprintf(tempPtr, "%s|%s|%c|%s|%s|%s\n", employee.info.staffID, employee.info.name, employee.info.gender, employee.info.password, employee.passwordRecovery, employee.info.position);
			found = 1;
		}
		else {
			fprintf(tempPtr, "%s|%s|%c|%s|%s|%s\n", employee.info.staffID, employee.info.name, employee.info.gender, employee.info.password, employee.passwordRecovery, employee.info.position);
		}
	}

	fclose(fptr);
	fclose(tempPtr);

	if (found) {
		printf("Record modified successfully.\n");
	}
	else {
		printf("No record found with staff ID: %s\n", idToModify);
	}

	remove("staff.txt");
	rename("temp.txt", "staff.txt");
	selectionStaff();
}

int deleteeStaff() {
	char idToDelete[10];
	printf("Enter staff ID to delete: ");
	scanf("%7s", idToDelete);

	FILE* fptr, * tempPtr;
	if ((fptr = fopen("staff.txt", "r")) == NULL) {
		printf("Error opening file!\n");
		return;
	}

	if ((tempPtr = fopen("temp.txt", "w")) == NULL) {
		printf("Error opening temporary file!\n");
		fclose(fptr);
		return;
	}

	staffRecord employee;
	int found = 0;
	while (fscanf(fptr, "%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^\n]\n", employee.info.staffID, employee.info.name, &employee.info.gender, employee.info.password, employee.passwordRecovery, employee.info.position) == 6) {
		if (strcmp(employee.info.staffID, idToDelete) != 0) {
			fprintf(tempPtr, "%s|%s|%c|%s|%s|%s\n", employee.info.staffID, employee.info.name, employee.info.gender, employee.info.password, employee.passwordRecovery, employee.info.position);
		}
		else {
			found = 1;
		}
	}

	fclose(fptr);
	fclose(tempPtr);

	if (found) {
		printf("Record deleted successfully.\n");
	}
	else {
		printf("No record found with staff ID: %s\n", idToDelete);
	}

	remove("staff.txt");
	rename("temp.txt", "staff.txt");
}

int forgotStaff() {
	char passToForgot[5];
	printf("Enter password recovery to get your password: ");
	scanf("%s", passToForgot);

	FILE* fptr;
	if ((fptr = fopen("staff.txt", "r")) == NULL) {
		printf("Error opening file!\n");
		return;
	}

	staffRecord employee;
	int found = 0;
	while (fscanf(fptr, "%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^\n]\n", employee.info.staffID, employee.info.name, &employee.info.gender, employee.info.password, employee.passwordRecovery, employee.info.position) == 6) {
		if (strcmp(employee.passwordRecovery, passToForgot) == 0) {
			printf("Your Password Is : %s\n\n", employee.info.password);
			found = 1;
			break;
		}
	}

	if (!found) {
		printf("No record found with your Password Recovery: %s\n", passToForgot);
	}

	fclose(fptr);
}

//validation check for staff detail input
int validateStaffId(const char* staffId) {
	// Check if the length is correct
	if (strlen(staffId) != 6) {
		printf("Invalid staff ID length. Staff ID must be 6 characters long.\n");
		return 0; // Invalid staff ID
	}

	// Check if the first three characters are "STF"
	if (strncmp(staffId, "STF", 3) != 0) {
		printf("Invalid staff ID format. Staff ID must start with 'STF'.\n");
		return 0; // Invalid staff ID
	}

	// Check if the last three characters are digits
	for (int i = 3; i < 6; i++) {
		if (!isdigit(staffId[i])) {
			printf("Invalid staff ID format. Last three characters must be digits.\n");
			return 0; // Invalid staff ID
		}
	}


	return 1; // If all checks pass, staff ID is valid
}

int validateGender(char gender) {
	if (gender == 'M' || gender == 'F') {
		return 1; // Valid gender
	}
	else {
		printf("Invalid gender. Please enter 'M' for male or 'F' for female.\n");
		return 0; // Invalid gender
	}
}

int validatePassword(const char* password) {
	// Perform password validation here (e.g., minimum length, complexity requirements)
	if (strlen(password) == 10) {
		return 1; // Valid password
	}
	else {
		printf("Invalid password. Password must be 10 characters long.\n");
		return 0; // Invalid password
	}
}

int validateName(const char* name) {
	if (strlen(name) > 0) {
		return 1; // Valid name
	}
	else {
		printf("Invalid name. Name cannot be empty.\n");
		return 0; // Invalid name
	}
}

int validatePasswordRecovery(const char* recovery) {
	if (strlen(recovery) == 4) {
		return 1; // Valid recovery code
	}
	else {
		printf("Invalid password recovery code.Password Recovery must be 4 characters long.\n");
		return 0; // Invalid recovery code
	}
}

int validatePosition(const char* position) {
	if (strlen(position) > 0) {
		return 1; // Valid position
	}
	else {
		printf("Invalid position. Position cannot be empty.\n");
		return 0; // Invalid position
	}
}

void TrainSchedulingAdd(Schedule schedule[], int* numOfSchedule, char id[]) { // Function to add a train schedule
	int addaction;
	FILE* add;
	add = fopen("trainschedule.txt", "a"); //Open file for appending
	if (add == NULL) {
		printf("Unable to open file!!");
		return;
	}

	do {  //Prompt and input data for each field of the schedule
		printf("Enter Train ID :");
		rewind(stdin);
		scanf("%s", schedule[*numOfSchedule].trainId);
		printf("Enter Departure Location :");
		rewind(stdin);
		scanf("%[^\n]", schedule[*numOfSchedule].departureLocation);
		printf("Enter Destination :");
		rewind(stdin);
		scanf("%[^\n]", schedule[*numOfSchedule].destination);
		printf("Enter Departure Date :");
		rewind(stdin);
		scanf("%s", schedule[*numOfSchedule].dateTime[*numOfSchedule].departureDate);
		printf("Enter Departure Time :");
		rewind(stdin);
		scanf("%s", schedule[*numOfSchedule].dateTime[*numOfSchedule].departureTime);
		printf("Enter Arrival Time :");
		rewind(stdin);
		scanf("%s", schedule[*numOfSchedule].dateTime[*numOfSchedule].arrivalTime);
		printf("Enter Fare :");
		rewind(stdin);
		scanf("%lf", &schedule[*numOfSchedule].fare);
		printf("Enter Distance(km) :");
		rewind(stdin);
		scanf("%d", &schedule[*numOfSchedule].distance);
		printf("Enter Duration(hours) :");
		rewind(stdin);
		scanf("%lf", &schedule[*numOfSchedule].duration);
		printf("Enter Available Seats :");
		rewind(stdin);
		scanf("%d", &schedule[*numOfSchedule].availableSeats);

		// Write schedule information to file
		fprintf(add, "\n%d|%s|%s|%s|%s|%s|%s|%.2f|%d|%.2f|%d|%s", (*numOfSchedule + 1), schedule[*numOfSchedule].trainId, schedule[*numOfSchedule].departureLocation,
			schedule[*numOfSchedule].destination, schedule[*numOfSchedule].dateTime[*numOfSchedule].departureDate, schedule[*numOfSchedule].dateTime[*numOfSchedule].departureTime,
			schedule[*numOfSchedule].dateTime[*numOfSchedule].arrivalTime, schedule[*numOfSchedule].fare, schedule[*numOfSchedule].distance, schedule[*numOfSchedule].duration,
			schedule[*numOfSchedule].availableSeats, id);
		printf("Schedule added succesfully!\n");

		(*numOfSchedule)++;

		printf("Select 1 to add another schedule (any character to go back to PREVIOUS SECTION) : ");
		rewind(stdin);
		scanf("%d", &addaction);
	} while (addaction == 1);
	fclose(add);
}

void TrainSchedulingSearch(Schedule schedule[], int* numOfSchedule) { //Function to search for train schedules
	char from[50], to[50];

	printf("Enter Departure Destination : ");
	rewind(stdin);
	scanf("%[^\n]", from);
	printf("Enter Arrival Destination : ");
	rewind(stdin);
	scanf("%[^\n]", to);

	printf("%-5s\t%-10s\t%-20s\t%-20s\t%-10s\t%-10s\t%-10s\t%-7s\t%-10s\t%-15s\t%-10s\t%s\n",
		"No", "Train ID", "Departure Location", "Destination",
		"Departure Date", "Departure Time", "Arrival Time", "Fare", "Distance",
		"Duration", "Available Seats", "StaffID");
	printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	for (int n = 0; n < *numOfSchedule; n++) { //Compare with data stored in structure array

		if (strcmp(schedule[n].departureLocation, from) == 0 && strcmp(schedule[n].destination, to) == 0) {
			printf("%-5d\t%-10s\t%-20s\t%-20s\t%-10s\t%-10s\t%-10s\t%-7.2f\t%-10d\t%-15.2f\t%-10d\t%-5s\n",
				schedule[n].number, schedule[n].trainId, schedule[n].departureLocation,
				schedule[n].destination, schedule[n].dateTime[n].departureDate, schedule[n].dateTime[n].departureTime,
				schedule[n].dateTime[n].arrivalTime, schedule[n].fare, schedule[n].distance,
				schedule[n].duration, schedule[n].availableSeats, schedule[n].id);
		}

	}

}

void TrainSchedulingModify(Schedule schedule[], int* numOfSchedule, char id[]) { //Function to modify a train schedule
	int no;
	int foundIndex = -1;

	printf("\nWhich NO of Schedule to modify? ");
	rewind(stdin);
	scanf("%d", &no);

	for (int n = 0; n < *numOfSchedule; n++) { //Search for that particular schedule
		if (schedule[n].number == no) {
			foundIndex = n;
			break;
		}
	}


	if (foundIndex != -1) {
		printf("Enter Train ID :");
		rewind(stdin);
		scanf("%s", schedule[foundIndex].trainId);
		printf("Enter Departure Location :");
		rewind(stdin);
		scanf("%[^\n]", schedule[foundIndex].departureLocation);
		printf("Enter Destination :");
		rewind(stdin);
		scanf("%[^\n]", schedule[foundIndex].destination);
		printf("Enter Departure Date :");
		rewind(stdin);
		scanf("%s", schedule[foundIndex].dateTime[foundIndex].departureDate);
		printf("Enter Departure Time :");
		rewind(stdin);
		scanf("%s", schedule[foundIndex].dateTime[foundIndex].departureTime);
		printf("Enter Arrival Time :");
		rewind(stdin);
		scanf("%s", schedule[foundIndex].dateTime[foundIndex].arrivalTime);
		printf("Enter Fare :");
		rewind(stdin);
		scanf("%lf", &schedule[foundIndex].fare);
		printf("Enter Distance(km) :");
		rewind(stdin);
		scanf("%d", &schedule[foundIndex].distance);
		printf("Enter Duration(hours) :");
		rewind(stdin);
		scanf("%lf", &schedule[foundIndex].duration);
		printf("Enter Available Seats :");
		rewind(stdin);
		scanf("%d", &schedule[foundIndex].availableSeats);
		strcmp(schedule[foundIndex].id, id);

		printf("Schedule modified successfully!\n");
	}
	else {
		printf("Schedule with number %d not found.\n", no);
	}



	FILE* modify;
	modify = fopen("trainschedule.txt", "w");
	if (modify == NULL) {
		printf("Unable to open FILE!!\n");
		return;
	}

	for (int n = 0; n < *numOfSchedule; n++) {

		fprintf(modify, "%d|%s|%s|%s|%s|%s|%s|%.2f|%d|%.2f|%d|%s\n", schedule[n].number, schedule[n].trainId, schedule[n].departureLocation,
			schedule[n].destination, schedule[n].dateTime[n].departureDate, schedule[n].dateTime[n].departureTime,
			schedule[n].dateTime[n].arrivalTime, schedule[n].fare, schedule[n].distance, schedule[n].duration,
			schedule[n].availableSeats, schedule[n].id);
	}

	fclose(modify);
}

void TrainSchedulingDisplay(Schedule schedule[], int* numOfSchedule) { //Function to display all train schedules

	printf("%-5s\t%-10s\t%-20s\t%-20s\t%-10s\t%-10s\t%-10s\t%-7s\t%-10s\t%-15s\t%-10s\t%s\n",
		"No", "Train ID", "Departure Location", "Destination",
		"Departure Date", "Departure Time", "Arrival Time", "Fare", "Distance",
		"Duration", "Available Seats", "StaffID");
	printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	for (int n = 0; n < *numOfSchedule; n++) { //Print out all the data stored in structure array
		printf("%-5d\t%-10s\t%-20s\t%-20s\t%-10s\t%-10s\t%-10s\t%-7.2f\t%-10d\t%-15.2f\t%-10d\t%-5s\n",
			schedule[n].number, schedule[n].trainId, schedule[n].departureLocation,
			schedule[n].destination, schedule[n].dateTime[n].departureDate, schedule[n].dateTime[n].departureTime,
			schedule[n].dateTime[n].arrivalTime, schedule[n].fare, schedule[n].distance,
			schedule[n].duration, schedule[n].availableSeats, schedule[n].id);
	}
}

void TrainSchedulingDelete(Schedule schedule[], int* numOfSchedule, char id[]) { //Function to delete a train schedule
	Booking trainScheduleCompare[MAX_BOOKINGS];
	FILE* file = fopen("bookings.bin", "rb");
	if (file == NULL) {
		printf("Error opening file\n");
		return;
	}

	int index = 0;
	while (fread(&trainScheduleCompare[index], sizeof(Booking), 1, file) == 1) {
		index++;
	}

	int deleteNo;
	printf("Enter the schedule number you want to delete: ");
	scanf("%d", &deleteNo);

	int foundIndex = -1;
	for (int n = 0; n < *numOfSchedule; n++) {
		if (schedule[n].number == deleteNo) {
			foundIndex = n;
			break;
		}
	}

	// Check if the schedule has bookings
	for (int i = 0; i < index; i++) {
		if (strcmp(trainScheduleCompare[i].trainID, schedule[foundIndex].trainId) == 0) {
			printf("Schedule has bookings. Cannot delete!\n");
			return;
		}
	}

	if (foundIndex != -1) {
		for (int n = foundIndex; n < (*numOfSchedule - 1); n++) { //Move all the schedules one step forward after the deleted schedule  
			strcpy(schedule[n].trainId, schedule[n + 1].trainId);
			strcpy(schedule[n].departureLocation, schedule[n + 1].departureLocation);
			strcpy(schedule[n].destination, schedule[n + 1].destination);
			strcpy(schedule[n].dateTime[n].departureDate, schedule[n + 1].dateTime[n + 1].departureDate);
			strcpy(schedule[n].dateTime[n].departureTime, schedule[n + 1].dateTime[n + 1].departureTime);
			strcpy(schedule[n].dateTime[n].arrivalTime, schedule[n + 1].dateTime[n + 1].arrivalTime);
			schedule[n].fare = schedule[n + 1].fare;
			schedule[n].distance = schedule[n + 1].distance;
			schedule[n].duration = schedule[n + 1].duration;
			schedule[n].availableSeats = schedule[n + 1].availableSeats;
			strcpy(schedule[n].id, schedule[n + 1].id);
		}

		(*numOfSchedule)--;

		printf("Schedule %d deleted successfully.\n", deleteNo);

		FILE* delete;
		delete = fopen("trainschedule.txt", "w");
		if (delete == NULL) {
			printf("Unable to open FILE!!\n");
			return;
		}

		for (int n = 0; n < *numOfSchedule; n++) { //Write the changed schedule information into file
			fprintf(delete, "%d|%s|%s|%s|%s|%s|%s|%.2f|%d|%.2f|%d|%s\n", schedule[n].number, schedule[n].trainId, schedule[n].departureLocation,
				schedule[n].destination, schedule[n].dateTime[n].departureDate, schedule[n].dateTime[n].departureTime,
				schedule[n].dateTime[n].arrivalTime, schedule[n].fare, schedule[n].distance, schedule[n].duration,
				schedule[n].availableSeats, schedule[n].id);
		}

		fclose(delete);
	}
	else {
		printf("Schedule with number %d not found.\n", deleteNo);
	}
}

void TrainSchedulingMaintenance(Schedule schedule[], int* numOfSchedule, char id[]) { //Function to perform maintenance on a train schedule

	Booking trainScheduleCompare[MAX_BOOKINGS];
	FILE* file = fopen("bookings.bin", "rb");
	if (file == NULL) {
		printf("Error opening file\n");
		return;
	}

	int index = 0;
	while (fread(&trainScheduleCompare[index], sizeof(Booking), 1, file) == 1) {
		index++;
	}

	int action, no, foundIndex = -1;

	printf("\n\n1. Under Maintenance\n");
	printf("2. Maintenance Completed\n");
	printf("Action to be taken :");
	scanf("%d", &action);
	while (action != 1 && action != 2) {
		printf("Invalid action. Please Re-enter :");
		scanf("%d", &action);
	}

	if (action == 1) {
		printf("Enter Schedule Number :");
		scanf("%d", &no);

		for (int n = 0; n < *numOfSchedule; n++) {
			if (schedule[n].number == no) {
				foundIndex = n;
				break;
			}
		}

		// Check if the schedule has bookings
		for (int i = 0; i < index; i++) {
			if (strcmp(trainScheduleCompare[i].trainID, schedule[foundIndex].trainId) == 0) {
				printf("Schedule has bookings. Cannot be under MAINTENANCE!\n");
				return;
			}
		}

		if (foundIndex != -1) {
			strcpy(schedule[foundIndex].departureLocation, "Under Maintenance");
			strcpy(schedule[foundIndex].destination, "Under Maintenance");
			strcpy(schedule[foundIndex].id, id);
			printf("Schedule Under Maintenance!\n");
		}
		else {
			printf("Schedule with number %d not found.\n", no);
		}
	}

	else {
		printf("Enter Schedule Number :");
		scanf("%d", &no);
		for (int n = 0; n < *numOfSchedule; n++) {
			if (schedule[n].number == no) {
				foundIndex = n;
				break;
			}
		}


		if (foundIndex != -1) {
			printf("Enter Departure Location :");
			rewind(stdin);
			scanf("%[^\n]", schedule[foundIndex].departureLocation);
			printf("Enter Destination :");
			rewind(stdin);
			scanf("%[^\n]", schedule[foundIndex].destination);
			strcpy(schedule[foundIndex].id, id);
			printf("Schedule Maintenance Completed!\n");
		}
		else {
			printf("Schedule with number %d not found.\n", no);
		}
	}

	FILE* write;
	write = fopen("trainschedule.txt", "w");
	if (write == NULL) {
		printf("Unable to open FILE!!\n");
		return;
	}

	for (int n = 0; n < *numOfSchedule; n++) { //Write back the changed information into file

		fprintf(write, "%d|%s|%s|%s|%s|%s|%s|%.2f|%d|%.2f|%d|%s\n", schedule[n].number, schedule[n].trainId, schedule[n].departureLocation,
			schedule[n].destination, schedule[n].dateTime[n].departureDate, schedule[n].dateTime[n].departureTime,
			schedule[n].dateTime[n].arrivalTime, schedule[n].fare, schedule[n].distance, schedule[n].duration,
			schedule[n].availableSeats, schedule[n].id);
	}

	fclose(write);
}

void DisplaySeats() { //Function to display seats layout
	int Seats[40][4] = { 0 };
	int row, col;
	printf("\t \t Seats\n");
	printf("-----------------------------------------\n\n");
	printf("\t  1  2  3  4\n");

	for (row = 0; row < 40; row++)
	{
		printf("Rows %2d : ", row + 1);
		for (col = 0; col < 4; col++)
			printf("%d  ", Seats[row][col]);
		printf("\n");
	}
	printf("\n");

}

int TrainSchedulingMenu(char id[]) { //Function for the train scheduling menu

	int action;
	do {
		Schedule schedule[200] = { "" };
		FILE* scan;
		scan = fopen("trainschedule.txt", "r");
		int numOfSchedule = 0;
		if (scan == NULL) {
			printf("Unable to open FILE!!");
			return;
		}

		while (!feof(scan)) {
			fscanf(scan, "%d|%[^\|]|%[^\|]|%[^\|]|%[^\|]|%[^\|]|%[^\|]|%lf|%d|%lf|%d|%s\n", &schedule[numOfSchedule].number, schedule[numOfSchedule].trainId,
				schedule[numOfSchedule].departureLocation, schedule[numOfSchedule].destination, schedule[numOfSchedule].dateTime[numOfSchedule].departureDate,
				schedule[numOfSchedule].dateTime[numOfSchedule].departureTime, schedule[numOfSchedule].dateTime[numOfSchedule].arrivalTime,
				&schedule[numOfSchedule].fare, &schedule[numOfSchedule].distance,
				&schedule[numOfSchedule].duration, &schedule[numOfSchedule].availableSeats, schedule[numOfSchedule].id);

			numOfSchedule++;
		}

		fclose(scan);

		printf("\n");
		printf("\t***************************************\n");
		printf("\t*                                     *\n");
		printf("\t*           Train Scheduling          *\n");
		printf("\t*                                     *\n");
		printf("\t***************************************\n");
		printf("\n");

		printf("1. ADD schedule\n");
		printf("2. SEARCH schedule\n");
		printf("3. MODIFY schedule\n");
		printf("4. DISPLAY schedule\n");
		printf("5. DELETE schedule\n");
		printf("6. MAINTENANCE schedule\n");
		printf("7. DISPLAY SEATS\n");
		printf("0. BACK TO PREVIOUS PAGE\n");
		printf("\nSelect 0-7 : \n");
		rewind(stdin);
		scanf("%d", &action);
		while (action < 0 || action > 7) {
			printf("ERROR! Please Select 0-7 only : ");
			scanf("%d", &action);
		}

		if (action == 1)
			TrainSchedulingAdd(schedule, &numOfSchedule, id);
		else if (action == 2)
			TrainSchedulingSearch(schedule, &numOfSchedule);
		else if (action == 3) {
			TrainSchedulingDisplay(schedule, &numOfSchedule);
			TrainSchedulingModify(schedule, &numOfSchedule, id);
		}
		else if (action == 4)
			TrainSchedulingDisplay(schedule, &numOfSchedule);
		else if (action == 5) {
			TrainSchedulingDisplay(schedule, &numOfSchedule);
			TrainSchedulingDelete(schedule, &numOfSchedule, id);
		}
		else if (action == 6) {
			TrainSchedulingDisplay(schedule, &numOfSchedule);
			TrainSchedulingMaintenance(schedule, &numOfSchedule, id);
		}
		else if (action == 7) {
			DisplaySeats();
		}
		else
			break;
	} while (action != 0);
}

void TrainSchedulingMain(char id[]) { //Main function for the train scheduling system

	TrainSchedulingMenu(id);
}

void MemberInformationMain() {
	FILE* readBinary;
	readBinary = fopen("memberdata.bin", "rb");
	if (readBinary == NULL) {
		printf("File not exist!\n");
		return;
	}

	struct Members member[MAX_MEMBER];
	int count = 0;
	while (fread(&member[count], sizeof(struct Members), 1, readBinary))
		count++;

	int option; // Variables for selecting modules

	// Menu for selecting modules
	do {
		printf("MEMBER INFORMATION\n"
			"Select your option:\n"
			"(1) Add\n"
			"(2) Search\n"
			"(3) Modify\n"
			"(4) Display\n"
			"(5) Delete\n"
			"(6) Exit\n");

		do
		{
			printf("> ");
			rewind(stdin);
			scanf("%d", &option);

			// Error handling
			if (option < 1 || option > 6) {
				printf("Invalid option! Please try again.\n\n");
			}
		} while (option < 1 || option > 6);

		// Switch to the option entered
		switch (option) {
		case 1: MemberInfoAdd(); break;
		case 2: MemberInfoSearch(member, &count); break;
		case 3: MemberInfoModify(member, &count); break;
		case 4: MemberInfoDisplay(member, &count); break;
		case 5: MemberInfoDelete(member, &count); break;
		case 6: return;
		}
	} while (option != 6);
}

// Add new members info
int MemberInfoAdd() {
	struct Members newMember;

	printf("\n|| %-15s ADD MEMBERS %-15s ||\n", " ", " ");

	int keepLoop = 1; // Boolean variable for entering multiple members info

	while (keepLoop == 1) {
		printf("Name			: "); // Name
		rewind(stdin);
		scanf("%[^\n]", newMember.name);

		do {
			printf("Member ID		: "); // Member ID
			rewind(stdin);
			scanf("%s", newMember.memberID);

			// Check whether the array size is too much
			if (strlen(newMember.memberID) > 5)
				printf("\nMember ID is too long. Please enter again!\n");
		} while (strlen(newMember.memberID) > 5);

		do {
			printf("Gender (M/F)		: "); // Gender
			rewind(stdin);
			scanf(" %c", &newMember.gender);

			// Check the gender input only receive 'M' or 'F'
			if (newMember.gender != 'M' && newMember.gender != 'F')
				printf("\nYou could only enter \'M\' or \'F\'. Please enter again!\n");

		} while (newMember.gender != 'M' && newMember.gender != 'F');

		printf("IC Number		: "); // IC Number, must follow the format
		rewind(stdin); // The IC Number is formatted to receive limited digit numbers
		scanf("%06d-%02d-%04d", &newMember.memberIC.birthDate, &newMember.memberIC.area, &newMember.memberIC.uniqueID);

		printf("Contact Number		: "); // Contact Number
		rewind(stdin);
		scanf(" %011d", &newMember.contactNum); // The contact number is formatted to receive limited digit numbers

		do {
			printf("Booking ID		: "); // Booking ID
			rewind(stdin);
			scanf("%s", newMember.bookingID);

			// Check the array size is over
			if (strlen(newMember.bookingID) > 5)
				printf("\nBooking ID is too long. Please enter again!\n");
		} while (strlen(newMember.bookingID) > 5);

		do {
			printf("Password		: "); // Enter password
			rewind(stdin);
			scanf("%s", newMember.password);

			// Check whether the array size is over
			if (strlen(newMember.password) > 8)
				printf("\nPassword is too long. Please change another password.\n");
		} while (strlen(newMember.password) > 8);



		printf("Password Recovery	: "); // Enter password recovery
		rewind(stdin);
		scanf("%4d", &newMember.passRecover); // Formatted to receive 4 digits of number

		// Write data into the binary file
		FILE* fptr; // Open file and error handling
		fptr = fopen("memberdata.bin", "ab");
		if (fptr == NULL) {
			printf("File not exist!\n");
			return;
		}
		fwrite(&newMember, sizeof(struct Members), 1, fptr);
		fclose(fptr);


		do {
			printf("\nContinue adding member info?\n"
				"(1) Yes\n"
				"(2) No\n"
				"> ");
			rewind(stdin);
			scanf("%d", &keepLoop);

			// Error handling
			if (keepLoop != 1 && keepLoop != 2) {
				printf("Wrong input! Enter again!\n\n");
			}
		} while (keepLoop != 1 && keepLoop != 2);

		printf("\n");

		// If choose 2, which is no, exit the loop
	}

	printf("\n\n");
	return 0;
}

int MemberInfoSearch(struct Members member[], int* count) {
	char searchID[6] = "";
	int found = -1;

	// Enter the member ID that wishes to search
	printf("Enter Member ID		: ");
	rewind(stdin);
	scanf("%s", searchID);

	for (int i = 0; i < *count; i++) {
		if (strcmp(member[i].memberID, searchID) == 0)
			found = i;
	}


	printf("\n\n");

	// If not found, display "no", if found, display the info
	if (found == -1) {
		printf("No member found.\n");
	}
	else {
		printf("Name			: %s\n", member[found].name);
		printf("Member ID		: %s\n", member[found].memberID);
		printf("Gender			: %c\n", member[found].gender);
		printf("IC Number		: %06d-%02d-%04d\n", member[found].memberIC.birthDate, member[found].memberIC.area, member[found].memberIC.uniqueID);
		printf("Contact Number		: %010d\n", member[found].contactNum);
		printf("Booking ID		: %s\n", member[found].bookingID);
		printf("Password		: %s\n", member[found].password);
		printf("Password Recovery	: %d\n", member[found].passRecover);
	}

	printf("\n\n");
	return;
}

int MemberInfoModify(struct Members member[], int* count) {
	// Search the member ID that wishes to modify
	char modifyMember[6] = "";
	printf("Enter Member ID		: ");
	rewind(stdin);
	scanf("%s", modifyMember);

	int found = -1;

	for (int i = 0; i < *count; i++) {
		if (strcmp(modifyMember, member[i].memberID) == 0) {
			found = i;
			break;
		}
	}

	// If not found, display "no", if found, enter the input for the member
	if (found == -1) {
		printf("The Member ID does not exist.\n");
	}
	else {
		int confirmModify;
		do {
			confirmModify = 2;

			printf("\n\n");
			printf("Name			: "); // Enter Name
			rewind(stdin);
			scanf("%[^\n]", member[found].name);

			do {
				printf("Gender			: "); // Enter Gender
				rewind(stdin);
				scanf("%c", &member[found].gender);

				// Check the gender input
				if (member[found].gender != 'M' && member[found].gender != 'F')
					printf("\nYou could only enter \'M\' or \'F\'. Please try again!\n");

			} while (member[found].gender != 'M' && member[found].gender != 'F');


			printf("IC Number		: "); // Enter IC Number
			rewind(stdin);
			scanf("%06d-%02d-%04d", &member[found].memberIC.birthDate, &member[found].memberIC.area, &member[found].memberIC.uniqueID);

			printf("Contact Number		: "); // Enter contact number
			rewind(stdin);
			scanf("%011d", &member[found].contactNum);

			do {
				printf("Booking ID		: "); // Enter Booking ID
				rewind(stdin);
				scanf("%s", member[found].bookingID);

				// Check Booking ID array size is over or not
				if (strlen(member[found].bookingID) > 5)
					printf("\nBooking ID is too long. Please enter again!\n");
			} while (strlen(member[found].bookingID) > 5);

			do {
				printf("Password		: ");
				rewind(stdin);
				scanf("%s", member[found].password);

				// Check the password array size is over or not
				if (strlen(member[found].password) > 8)
					printf("\nPassword maximum could only have 8 characters, try again!\n");
			} while (strlen(member[found].password) > 8);

			printf("Password Recovery	: ");
			rewind(stdin);
			scanf("%04d", &member[found].passRecover);


			do {
				printf("\nConfirm Modification?\n"
					"(1) Yes\n"
					"(2) No\n"
					"> ");
				rewind(stdin);
				scanf("%d", &confirmModify);

				if (confirmModify != 1 && confirmModify != 2)
					printf("\nInvalid option. Try again!\n");
			} while (confirmModify != 1 && confirmModify != 2);

		} while (confirmModify == 2);


		// Open the file again to overwrite data into the binary file
		FILE* modify;
		modify = fopen("memberdata.bin", "wb");
		if (modify == NULL) {
			printf("File not exist.\n");
			return;
		}

		for (int i = 0; i < *count; i++)
			fwrite(&member[i], sizeof(struct Members), 1, modify);

		fclose(modify);
	}

	printf("\n\n");
	return 0;
}

int MemberInfoDisplay(struct Members member[], int* count) {
	for (int i = 0; i < 121; i++)
		printf("-");

	printf("\n%-30s  %-10s  %-6s  %-14s  %-11s  %-11s  %-8s  %-17s\n",
		"Name", "Member ID", "Gender", "Member IC",
		"Contact Num", "Booking ID", "Password", "Password Recovery");

	for (int i = 0; i < 121; i++)
		printf("-");

	printf("\n");

	// Display all the record in the binary file
	for (int i = 0; i < *count; i++) {
		printf("%-30s  %-10s  %-6c  %06d-%02d-%04d  %011d  %-11s  %-8s  %-17d\n",
			member[i].name, member[i].memberID, member[i].gender, member[i].memberIC.birthDate,
			member[i].memberIC.area, member[i].memberIC.uniqueID, member[i].contactNum,
			member[i].bookingID, member[i].password, member[i].passRecover);
	}

	printf("\n < %d Details Listed >\n", *count);

	printf("\n\n");
	return 0;
}

int MemberInfoDelete(struct Members member[], int* count) {
	char deleteMember[6] = ""; // Variable for intended deleted Member ID
	int found = -1;

	printf("\n");

	do {
		printf("Enter ID	: "); // Enter Member ID
		rewind(stdin);
		scanf("%s", deleteMember);

		if (strlen(deleteMember) > 5)
			printf("\nYou could only enter 5 characters for the Member ID, try again!\n");
	} while (strlen(deleteMember) > 5);


	for (int i = 0; i < *count; i++) {
		if (strcmp(member[i].memberID, deleteMember) == 0) {
			found = i;
			break;
		}
	}

	if (found == -1) {
		printf("Member not found.\n");
	}
	else {
		while (found != *count) {
			if (found == *count)
				break;

			member[found] = member[found + 1];
			found++;
		}

		*count -= 1;

		// Open File
		FILE* delete;
		delete = fopen("memberdata.bin", "wb");
		if (delete == NULL) {
			printf("File not exist!\n");
			return;
		}

		for (int i = 0; i < *count; i++) {
			fwrite(&member[i], sizeof(struct Members), 1, delete);
		}

		fclose(delete);

		printf("Record of Member %s has deleted.\n", deleteMember);
	}

	printf("\n\n");
	return 0;
}

void MemberInfoForgotPassword() {
	FILE* readBinary;
	readBinary = fopen("memberdata.bin", "rb");
	if (!readBinary) {
		printf("File not exist!\n");
		return;
	}

	struct Members member[200];

	int count = 0;
	while (fread(&member[count], sizeof(struct Members), 1, readBinary) != 0) {
		count++;
	}

	fclose(readBinary);
	char findMember[6] = ""; // Variable for the intended search Member ID
	int matchPassRecover;
	int found;
	do {
		found = -1;

		printf("Enter your Member ID		: "); // Enter Member ID
		rewind(stdin);
		scanf("%s", findMember);

		printf("Enter your Password Recovery	: "); // Enter Password Recovery
		rewind(stdin);
		scanf("%d", &matchPassRecover);

		// Loop for searching the Member ID in the file with the inputted Member ID
		for (int i = 0; i < count; i++) {
			if (strcmp(member[i].memberID, findMember) == 0)
				found = i;
		}

		if (found != -1 && member[found].passRecover == matchPassRecover)
			printf("\nYour password is %s.\n", member[found].password);
		else // If not found, loop again
			printf("\nYour Member ID or Password Recovery is incorrect!\n");
	} while (!(found != -1 && member[found].passRecover == matchPassRecover));

	// Section for changing the passwordd
	int option;
	do {
		printf("\nDo you want to change your password?\n"
			"(1) Yes\n"
			"(2) No\n"
			"> ");
		rewind(stdin);
		scanf("%d", &option);

		// If yes, proceed the code, if no, exit the function
		if (option < 1 || option > 2)
			printf("Invalid option. Try again!\n");
	} while (option < 1 || option > 2);

	int confirm;

	if (option == 1) {
		confirm = 2;
		do {
			do {
				printf("\nEnter New Password	: "); // Enter new password
				rewind(stdin);
				scanf("%s", member[found].password);

				if (strlen(member[found].password) > 8)
					printf("The new password could only have maximum 8 characters. Try again!\n");
			} while (strlen(member[found].password) > 8);

			do { // Confirm modification
				printf("\nDo you confirm your changes?\n"
					"(1) Yes\n"
					"(2) No\n"
					"> ");
				rewind(stdin);
				scanf("%d", &confirm);

				if (confirm < 1 || confirm > 2)
					printf("Invalid option. Try again!\n");
			} while (confirm < 1 || confirm > 2);
		} while (confirm == 2);

		printf("\nYour password has been changed.\n");
	}

	// Open file for overwrite the binary file
	FILE* changePassword;
	changePassword = fopen("memberdata.bin", "wb");
	if (changePassword == NULL) {
		printf("File not exist.\n");
		return;
	}

	for (int i = 0; i < count; i++)
		fwrite(&member[i], sizeof(struct Members), 1, changePassword);

	fclose(changePassword);

	printf("\n\n");
	return 0;
}


void loadSchedules(ScheduleManager* manager, const char* schedulename) {

	FILE* file = fopen(schedulename, "r");
	if (file == NULL) {
		printf("Error opening file %s\n", schedulename);
		return;
	}

	int numSched = 0;

	while (numSched < MAX_SCHEDULES) {
		Schedule newSchedule;
		DateTime dateTime;
		int res = fscanf(file, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%lf|%d|%lf|%d|%s\n",
			&newSchedule.number, newSchedule.trainId,
			newSchedule.departureLocation, newSchedule.destination,
			dateTime.departureDate, dateTime.departureTime,
			dateTime.arrivalTime, &newSchedule.fare,
			&newSchedule.distance, &newSchedule.duration,
			&newSchedule.availableSeats, newSchedule.id);

		if (res == EOF || res != 12) {
			break;
		}

		(*manager).schedules[numSched] = newSchedule;
		numSched++;
	}

	fclose(file);

	(*manager).numSchedules = numSched;
}

int saveBookingsToFile(const char* bookingname, const BookingManager* bookingManager) {
	FILE* file = fopen(bookingname, "wb");
	if (file == NULL) {
		printf("Error opening file %s\n", bookingname);
		return -1;  // Return error code
	}

	size_t written = fwrite((*bookingManager).bookings, sizeof(Booking), (*bookingManager).numBookings, file);

	if (written != (*bookingManager).numBookings) {
		printf("Error writing data to file %s\n", bookingname);
		fclose(file);
		return -2;  // Return different error code
	}

	fclose(file);
	return 0;  // Return 0 on success
}


int loadBookingsFromFile(const char* bookingname, BookingManager* bookingManager) {
	FILE* file = fopen(bookingname, "rb");
	if (file == NULL) {
		printf("Error opening file %s\n", bookingname);
		return -1;
	}

	int index = 0;
	while (fread(&(*bookingManager).bookings[index], sizeof(Booking), 1, file) == 1) {
		index++;
	}


	(*bookingManager).numBookings = index;

	fclose(file);
	return 0;
}

double getFare(const ScheduleManager* scheduleManager, const char* trainID) {
	for (int i = 0; i < (*scheduleManager).numSchedules; i++) {
		if (strcmp((*scheduleManager).schedules[i].trainId, trainID) == 0) {
			return (*scheduleManager).schedules[i].fare;
		}
	}
	return -1.0;
}

bool isSeatBooked(int row, int column, const char* trainID, const BookingManager* bookingManager) {
	for (int i = 0; i < (*bookingManager).numBookings; i++) {
		if (strcmp((*bookingManager).bookings[i].trainID, trainID) == 0) {
			int quantity = (*bookingManager).bookings[i].quantity[0];
			for (int j = 0; j < quantity; j++) {
				if ((*bookingManager).bookings[i].seatNumberRow[j] == row && (*bookingManager).bookings[i].seatNumberColumn[j] == column) {
					return true;
				}
			}
		}
	}
	return false;
}

int is_leap_year(int year) {
	if (year % 400 == 0) return 1;
	if (year % 100 == 0) return 0;
	if (year % 4 == 0) return 1;
	return 0;
}

int is_valid_date(const char* date) {
	int day, month, year;

	if (sscanf(date, "%d/%d/%d", &day, &month, &year) != 3) {
		return 0;
	}

	if (year < 1900 || year > 2100) {
		return 0;
	}

	if (month < 1 || month > 12) {
		return 0;
	}

	if (day < 1 || day > 31) {
		return 0;
	}

	switch (month) {
	case 2:
		if (is_leap_year(year)) {
			if (day > 29) {
				return 0;
			}
		}
		else {
			if (day > 28) {
				return 0;
			}
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (day > 30) {
			return 0;
		}
		break;
	default:
		if (day > 31) {
			return 0;
		}
		break;
	}

	return 1;
}

void TicketAdd(BookingManager* bookingManager, const ScheduleManager* scheduleManager) {

	printf("Enter member ID: ");
	scanf("%s", (*bookingManager).bookings[(*bookingManager).numBookings].memberID);

	char trainID[10];
	int found = 0;

	do {
		printf("Enter train ID: ");
		scanf("%s", trainID);

		double fare = getFare(scheduleManager, trainID);
		if (fare == -1.0) {
			printf("Train ID %s does not exist. Please try again.\n", trainID);
		}
		else {
			found = 1;
			strcpy((*bookingManager).bookings[(*bookingManager).numBookings].trainID, trainID);
			printf("Fare for train ID %s is %.2f\n", trainID, fare);
			(*bookingManager).bookings[(*bookingManager).numBookings].amount = fare;
		}
	} while (!found);

	printf("Enter booking date (dd/mm/yyyy): ");
	char bookingDate[12];
	do {
		scanf("%s", bookingDate);
		if (!is_valid_date(bookingDate)) {
			printf("Invalid date, please re-enter (dd/mm/yyyy): ");
		}
	} while (!is_valid_date(bookingDate));
	strcpy((*bookingManager).bookings[(*bookingManager).numBookings].bookingDate, bookingDate);

	printf("Enter departure date (dd/mm/yyyy): ");
	char departureDate[12];
	do {
		scanf("%s", departureDate);
		if (!is_valid_date(departureDate)) {
			printf("Invalid date, please re-enter (dd/mm/yyyy): ");
		}
	} while (!is_valid_date(departureDate));
	strcpy((*bookingManager).bookings[(*bookingManager).numBookings].departureDate, departureDate);

	printf("Enter quantity: ");
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	scanf("%d", &(*bookingManager).bookings[(*bookingManager).numBookings].quantity[0]);

	printf("Enter payment type (CASH/PAYLATER): ");
	while ((c = getchar()) != '\n' && c != EOF);
	char paymentType[20];
	do {
		scanf("%s", paymentType);
		if (strcmp(paymentType, "CASH") != 0 && strcmp(paymentType, "PAYLATER") != 0) {
			printf("Invalid payment type. Please enter CASH or PAYLATER: ");
		}
	} while (strcmp(paymentType, "CASH") != 0 && strcmp(paymentType, "PAYLATER") != 0);
	strcpy((*bookingManager).bookings[(*bookingManager).numBookings].paymentInfo, paymentType);

	for (int i = 0; i < (*bookingManager).bookings[(*bookingManager).numBookings].quantity[0]; i++) {
		int row, column;
		bool seatAlreadyBooked;
		DisplaySeats();
		do {
			printf("Enter seat number %d (row column): ", i + 1);
			scanf("%d %d", &row, &column);
			while (row > 40 || column > 4) {
				printf("Invalid Seat. Please select again :");
				scanf("%d %d", &row, &column);
			}
			seatAlreadyBooked = isSeatBooked(row, column, (*bookingManager).bookings[(*bookingManager).numBookings].trainID, bookingManager, (*bookingManager).numBookings);

			if (seatAlreadyBooked) {
				printf("Seat %d-%d is already booked for the same train ID. Please choose another seat.\n", row, column);
			}
		} while (seatAlreadyBooked);

		(*bookingManager).bookings[(*bookingManager).numBookings].seatNumberRow[i] = row;
		(*bookingManager).bookings[(*bookingManager).numBookings].seatNumberColumn[i] = column;
	}

	(*bookingManager).bookings[(*bookingManager).numBookings].amount *= (*bookingManager).bookings[(*bookingManager).numBookings].quantity[0];

	int randomID;
	do {
		randomID = rand() % 9000 + 1000;
		sprintf((*bookingManager).bookings[(*bookingManager).numBookings].bookingID, "B%d", randomID);
	} while (!isUniqueID((*bookingManager).bookings[(*bookingManager).numBookings].bookingID, bookingManager, (*bookingManager).numBookings));

	printf("\nBooking successful! Your booking ID is %s\n", (*bookingManager).bookings[(*bookingManager).numBookings].bookingID);

	(*bookingManager).numBookings++;
}

int isUniqueID(const char* id, Booking* bookings, int numBookings) {
	for (int i = 0; i < numBookings; i++) {
		if (strcmp(id, bookings[i].bookingID) == 0) {
			return 0;
		}
	}
	return 1;
}


void displayMemberBookings(const char* memberID, BookingManager* bookingManager) {
	printf("Displaying bookings for member ID: %s\n", memberID);
	printf("Booking ID\tMember ID\tTrain ID\tBooking Date\tDeparture Date\tSeat\t\tQuantity\tPayment Info\tAmount\n");

	int found = 0;

	for (int i = 0; i < (*bookingManager).numBookings; i++) {
		Booking currentBooking = (*bookingManager).bookings[i];
		if (strcmp(currentBooking.memberID, memberID) == 0) {
			printf("%s\t\t%s\t\t%s\t\t%s\t%s\t", currentBooking.bookingID, currentBooking.memberID, currentBooking.trainID,
				currentBooking.bookingDate, currentBooking.departureDate);
			printf("%d-%d", currentBooking.seatNumberRow[0], currentBooking.seatNumberColumn[0]);

			for (int j = 1; j < currentBooking.quantity[0]; j++) {
				printf(", %d-%d", currentBooking.seatNumberRow[j], currentBooking.seatNumberColumn[j]);
			}

			printf("\t%d \t\t%-8s \t%-10.2lf\n", currentBooking.quantity[0], currentBooking.paymentInfo, currentBooking.amount);
			found = 1;
		}
	}

	if (!found) {
		printf("No bookings found for member ID: %s\n", memberID);
	}
}

void displayAsk(BookingManager* bookingManager, StaffManager* staffManager) {

	char memberID[20];
	printf("Enter your member ID: ");
	scanf("%19s", memberID);
	displayMemberBookings(memberID, bookingManager);

}

//Ticket Search Function
void TicketSearch(Booking* bookings, int numBookings, const char* bookingID) {
	int found = 0;
	for (int i = 0; i < numBookings; i++) {
		if (strcmp(bookings[i].bookingID, bookingID) == 0) {
			printf("==========================================\n");
			printf("Booking ID: %s\n", bookings[i].bookingID);
			printf("Member ID: %s\n", bookings[i].memberID);
			printf("Train ID: %s\n", bookings[i].trainID);
			printf("Booking Date: %s\n", bookings[i].bookingDate);
			printf("Departure Date: %s\n", bookings[i].departureDate);
			printf("Seat: ");
			printf("%d-%d", bookings[i].seatNumberRow[0], bookings[i].seatNumberColumn[0]);
			for (int j = 1; j < bookings[i].quantity[0]; j++) {
				printf(", %d-%d", bookings[i].seatNumberRow[j], bookings[i].seatNumberColumn[j]);
			}
			printf("\n");
			printf("Quantity: %d\n", bookings[i].quantity[0]);
			printf("Payment Info: %s\n", bookings[i].paymentInfo);
			printf("Amount: RM%.2lf\n", bookings[i].amount);
			printf("==========================================");
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("Booking with ID %s not found.\n", bookingID);
	}
}

void TicketCancel(Booking* bookings, int* numBookings, const char* bookingID, ScheduleManager* scheduleManager) {
	int found = 0;
	for (int i = 0; i < *numBookings; i++) {
		if (strcmp(bookings[i].bookingID, bookingID) == 0) {
			found = 1;
			printf("Booking ID: %s\n", bookings[i].bookingID);
			printf("Current quantity: %d\n", bookings[i].quantity[0]);
			printf("Enter the seat numbers you want to cancel : ");
			int seatRow, seatColumn;
			scanf("%d %d", &seatRow, &seatColumn);

			int seatIndex = -1;
			for (int j = 0; j < bookings[i].quantity[0]; j++) {
				if (bookings[i].seatNumberRow[j] == seatRow && bookings[i].seatNumberColumn[j] == seatColumn) {
					seatIndex = j;
					break;
				}
			}

			if (seatIndex == -1) {
				printf("The seat number you entered does not exist in the booking.\n");
				return;
			}

			for (int j = seatIndex; j < bookings[i].quantity[0] - 1; j++) {
				bookings[i].seatNumberRow[j] = bookings[i].seatNumberRow[j + 1];
				bookings[i].seatNumberColumn[j] = bookings[i].seatNumberColumn[j + 1];
			}

			bookings[i].quantity[0]--;

			double fare = getFare(scheduleManager, bookings[i].trainID);
			bookings[i].amount = bookings[i].quantity[0] * fare;

			printf("Successfully cancelled seat at row %d, column %d. New quantity: %d\n", seatRow, seatColumn, bookings[i].quantity[0]);
			printf("Please claim your refund at counter.\n");

			if (bookings[i].quantity[0] == 0) {
				for (int j = i; j < *numBookings - 1; j++) {
					bookings[j] = bookings[j + 1];
				}
				(*numBookings)--;
				printf("Booking with ID %s has been fully cancelled.\n", bookingID);
			}

			break;
		}
	}
	if (!found) {
		printf("Booking with ID %s not found.\n", bookingID);
	}
}

//To find the booking id
Booking* getBookingByID(Booking* bookings, int numBookings, const char* bookingID) {
	for (int i = 0; i < numBookings; i++) {
		if (strcmp(bookings[i].bookingID, bookingID) == 0) {
			return &bookings[i];
		}
	}
	return NULL;
}

// askForNewQuantity function
void askForNewQuantity(Booking* booking, const ScheduleManager* scheduleManager) {
	printf("Enter new quantity: ");
	scanf("%d", &(*booking).quantity[0]);
	(*booking).amount = getFare(scheduleManager, (*booking).trainID) * (*booking).quantity[0];
}

// askForNewSeatNumbers function
void askForNewSeatNumbers(Booking* booking, const ScheduleManager* scheduleManager, Booking* bookings, int numBookings, bool (*isSeatBookedFunc)(int, int, const char*, Booking*, int)) {
	for (int i = 0; i < (*booking).quantity[0]; i++) {
		int row, column;
		bool seatAlreadyBooked;

		do {
			printf("Enter seat number %d (row column): ", i + 1);
			scanf("%d %d", &row, &column);

			while (row > 40 || column > 4) {
				printf("Invalid Seat. Please select again :");
				scanf("%d %d", &row, &column);
			}

			seatAlreadyBooked = isSeatBookedFunc(row, column, (*booking).trainID, bookings, numBookings);

			if (seatAlreadyBooked) {
				printf("Seat %d-%d is already booked for the same train ID. Please choose another seat.\n", row, column);
			}
		} while (seatAlreadyBooked);

		(*booking).seatNumberRow[i] = row;
		(*booking).seatNumberColumn[i] = column;
	}
}

void TicketModify(Booking* bookings, int numBookings, const char* bookingID, BookingManager* bookingManager, ScheduleManager* scheduleManager) {
	Booking* booking = getBookingByID(bookings, numBookings, bookingID);
	if (booking == NULL) {
		printf("Booking with ID %s not found.\n", bookingID);
		return;
	}

	char newTrainID[10];
	double fare;
	do {
		printf("Enter new train ID: ");
		scanf("%s", newTrainID);

		fare = getFare(scheduleManager, newTrainID);
		if (fare == -1.0) {
			printf("Train ID %s does not exist. Please try again.\n", newTrainID);
		}
	} while (fare == -1.0);

	strcpy((*booking).trainID, newTrainID);
	printf("Fare for train ID %s is %.2f\n", newTrainID, fare);
	(*booking).amount = fare * (*booking).quantity[0];

	askForNewQuantity(booking, scheduleManager);
	askForNewSeatNumbers(booking, scheduleManager, bookings, numBookings, isSeatBooked);

	printf("Booking successfully modified for ID %s.\n", bookingID);
}

void TicketReceipt(const Booking* booking) {
	printf("================================================================\n");
	printf("             Booking Receipt\n");
	printf("================================================================\n");

	if (strcmp((*booking).paymentInfo, "PAYLATER") == 0) {
		printf("You have not paid RM%.2lf, please pay at the counter first.\n", (*booking).amount);
	}
	else if (strcmp((*booking).paymentInfo, "CASH") == 0) {
		printf("Booking ID:        %s\n", (*booking).bookingID);
		printf("Member ID:         %s\n", (*booking).memberID);
		printf("Train ID:          %s\n", (*booking).trainID);
		printf("Booking Date:      %s\n", (*booking).bookingDate);
		printf("Departure Date:    %s\n", (*booking).departureDate);
		printf("----------------------------------------------------------------\n");
		printf("Seat Numbers:\n");
		for (int i = 0; i < (*booking).quantity[0]; i++) {
			printf("                   %d-%d\n", (*booking).seatNumberRow[i], (*booking).seatNumberColumn[i]);
		}
		printf("----------------------------------------------------------------\n");
		printf("Quantity:          %d\n", (*booking).quantity[0]);
		printf("Payment Info:      %s\n", (*booking).paymentInfo);
		printf("Amount:            RM%.2lf\n", (*booking).amount);
		printf("================================================================\n");
		printf("Thank you for choosing our service!\n");
	}
	else {
		printf("Invalid payment method detected.\n");
	}

	printf("================================================================\n");
}

int TicketBookingMain() {
	// Initialize managers
	BookingManager bookingManager = { 0 };
	ScheduleManager scheduleManager = { 0 };
	StaffManager staffManager = { 0 };

	// Load data
	loadSchedules(&scheduleManager, "trainschedule.txt");
	srand(time(NULL));

	// Load bookings from file
	int loadResult = loadBookingsFromFile("bookings.bin", &bookingManager);
	if (loadResult != 0) {
		printf("Error loading bookings from file\n");
		return loadResult;
	}

	int choice = 0;
	do {
		printf("\n");
		printf("=====================\n");
		printf("   Ticket Booking    \n");
		printf("=====================\n");
		printf("1. Add Booking\n");
		printf("2. Display Bookings\n");
		printf("3. Search Booking\n");
		printf("4. Cancel Booking\n");
		printf("5. Modify Booking\n");
		printf("6. Generate Receipt\n");
		printf("7. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			TicketAdd(&bookingManager, &scheduleManager);
			break;
		case 2:
			displayAsk(&bookingManager, &staffManager);
			break;
		case 3:
		{
			char bookingID[10];
			printf("Enter Booking ID: ");
			scanf("%s", bookingID);
			TicketSearch(bookingManager.bookings, bookingManager.numBookings, bookingID);

		}
		break;
		case 4:
		{
			char bookingID[10];
			printf("Enter Booking ID to cancel: ");
			scanf("%s", bookingID);
			TicketCancel(bookingManager.bookings, &bookingManager.numBookings, bookingID, &scheduleManager);

		}
		break;
		case 5:
		{
			char bookingID[10];
			printf("Enter Booking ID to modify: ");
			scanf("%s", bookingID);
			TicketModify(bookingManager.bookings, bookingManager.numBookings, bookingID, &bookingManager, &scheduleManager);

		}
		break;
		case 6:
		{
			char bookingID[10];
			printf("Enter Booking ID to generate receipt: ");
			scanf("%s", bookingID);
			Booking* booking = getBookingByID(bookingManager.bookings, bookingManager.numBookings, bookingID);
			if (booking != NULL) {
				TicketReceipt(booking);
			}
			else {
				printf("Booking with ID %s not found.\n", bookingID);
			}
		}
		break;
		case 7:
			saveBookingsToFile("bookings.bin", &bookingManager);
			printf("Exiting...\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
			break;
		}
	} while (choice != 7);

	return 0;
}


void StaffScreen(char id[]) {
	int action = 0;
	do {
		printf("\n========================\n");
		printf("         STAFF\n");
		printf("========================\n");
		printf("1. Staff Information\n");
		printf("2. Member Information\n");
		printf("3. Train Scheduling\n");
		printf("4. LogOut\n");
		printf("Select 1-4 :");
		scanf("%d", &action);

		while (action < 1 || action > 4) {
			printf("Error. Please Try Again :");
			scanf("%d", &action);
		}

		if (action == 1) {
			StaffInformationMain();
		}
		else if (action == 2) {
			MemberInformationMain();
		}
		else if (action == 3) {
			TrainSchedulingMain(id);
		}
		else if (action == 4) {
			break;
		}
	} while (action != 4);
}

int main() {
	Schedule show;
	FILE* display;
	display = fopen("trainschedule.txt", "r");
	if (display == NULL) {
		printf("Error Opening File\n");
		return 0;
	}
	printf("%-5s\t%-10s\t%-20s\t%-20s\t%-10s\t%-10s\t%-10s\t%-7s\t%-10s\t%-15s\t%-10s\n",
		"No", "Train ID", "Departure Location", "Destination",
		"Departure Date", "Departure Time", "Arrival Time", "Fare", "Distance",
		"Duration", "Available Seats");
	printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	int no = 0;
	while (fscanf(display, "%d|%[^\|]|%[^\|]|%[^\|]|%[^\|]|%[^\|]|%[^\|]|%lf|%d|%lf|%d|%s\n", &show.number, show.trainId,
		show.departureLocation, show.destination, show.dateTime[no].departureDate,
		show.dateTime[no].departureTime, show.dateTime[no].arrivalTime,
		&show.fare, &show.distance,
		&show.duration, &show.availableSeats, show.id) != EOF) {

		printf("%-5d\t%-10s\t%-20s\t%-20s\t%-10s\t%-10s\t%-10s\t%-7.2f\t%-10d\t%-15.2f\t%-10d\n",
			show.number, show.trainId, show.departureLocation,
			show.destination, show.dateTime[no].departureDate, show.dateTime[no].departureTime,
			show.dateTime[no].arrivalTime, show.fare, show.distance,
			show.duration, show.availableSeats);

	}
	char id[10] = "";
	int action;
	int identity = -1;
	do {
		printf("\n\n");
		printf("===========================\n");
		printf("LLNW TRAIN TICKETING SYSTEM\n");
		printf("===========================\n");
		printf("1. Sign in\n");
		printf("2. Forgot Password\n");
		printf("3. Register Account\n");
		printf("0. Exit\n");
		printf("Select 0-3 :");
		scanf("%d", &action);

		while (action < 0 || action > 3) {
			printf("Error. Please Try Again :");
			scanf("%d", &action);
		}

		switch (action) {
		case 0:
			break;
		case 1:
			SignIn(&identity, id);
			if (identity == 0) {
				StaffScreen(id);
			}
			else if (identity == 1) {
				printf("\n========================\n");
				printf("         MEMBER\n");
				printf("========================\n");
				TicketBookingMain();
			}
			break;
		case 2:
			printf("1. Staff\n");
			printf("2. Member\n");
			printf("Select 1 or 2 :");
			scanf("%d", &action);
			if (action == 1)
				forgotStaff();
			else if (action == 2)
				MemberInfoForgotPassword();
			break;
		case 3:
			MemberInfoAdd();
			break;
		}
	} while (action != 0);
	printf("\nThank You. Have a Nice Day~");
}