#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

//Function Declaration
void languageOption();
void english();
void malay();
void staffEnglish();
void staffMalay();
void studentEnglish();
void studentMalay();
void invalid();
void displayGradeScale();

//Language (Extra Feature)
int language;

//Formula Variable 
double GPAS1, GPAS2, GPAS3;
double CGPAS1, CGPAS2, CGPAS3;
double GRADE_POINTS1, GRADE_POINTS2, GRADE_POINTS3;
double TOTAL_QUALITY_POINTS1, TOTAL_QUALITY_POINTS2, TOTAL_QUALITY_POINTS3;
int TOTAL_CREDIT_HOURSS1, TOTAL_CREDIT_HOURSS2, TOTAL_CREDIT_HOURSS3;

//Course Variable
int CREDIT_HOURS;
int SEMESTER;
int noOfCourse, courseAction;
char COURSE_CODE[30], GRADE[10];

//Student'details Variable
char NAME[30];
char ID[10];

//Mode Variable
int IDENTITY;
int action = 0;

//Grade Scale & Language Option
void main()
{
	displayGradeScale();
	printf("\n\n");

	do {
		languageOption();
		if (language == 1)
		{
			english();
			if (IDENTITY == 1) {
				staffEnglish();
			}
			else if (IDENTITY == 2)
				studentEnglish();
			else if (IDENTITY == 3)
				system("pause");
			else
				invalid();
		}

		else if (language == 2)
		{
			malay();
			if (IDENTITY == 1)
				staffMalay();
			else if (IDENTITY == 2)
				studentMalay();
			else if (IDENTITY == 3)
				system("pause");
			else
				invalid();
		}

		else if (language == 3)
			return 0;

		else
			invalid();

		printf("\nAny other action? Select 1/2\n1. Yes\n2. No\n");
		scanf("%d", &action);

	} while (action == 1);

	printf("\n");
	printf("Thank you for using the GPA/CGPA calculator.\n");
	return;

}

void languageOption()
{
	printf("1. English\n");
	printf("2. Bahasa Melayu\n");
	printf("3. Exit\n");
	printf("Select your language : ");
	scanf("%d", &language);
	return 0;
}

void english()
{
	printf("\n\n");
	printf("--------------------------------------------------\n");
	printf("---[WELCOME TO KOLEJ PASAR GPA/CGPA CALCULATOR]---\n");
	printf("--------------------------------------------------\n");
	printf("\n");
	printf("1. Staff Administration\n");
	printf("2. Student\n");
	printf("3. Exit\n");
	printf("\n");
	printf("Enter  1 / 2 to select your identity : ");
	scanf("%d", &IDENTITY);
	return 0;
}

void malay()
{
	printf("\n\n");
	printf("---------------------------------------------------------\n");
	printf("---[SELAMAT DATANG KE KOLEJ PASAR GPA/CGPA KALKULATOR]---\n");
	printf("---------------------------------------------------------\n");
	printf("\n");
	printf("1. Kakitangan Kolej Pasar\n");
	printf("2. Mahasiswa\n");
	printf("3. Keluar\n");
	printf("\n");
	printf("Masuk 1/2 untuk memilih identiti : ");
	scanf("%d", &IDENTITY);
	return 0;
}

void staffEnglish()
{
	printf("\n\n");
	printf("Enter student\'s name : ");
	rewind(stdin);
	scanf("%30[^\n]", NAME);
	printf("Enter student ID : ");
	scanf("%10s", ID);
	do {
		printf("Enter semester session ( 0 to return ) : ");
		rewind(stdin);
		scanf("%d", &SEMESTER);

		if (SEMESTER == 1) {
			printf("Enter number of courses taken : "); //Let user to enter number of courses taken
			scanf("%d", &noOfCourse);
			for (courseAction = 0; courseAction < noOfCourse; courseAction++)
			{
				printf("Enter course code %d : ", courseAction + 1);
				rewind(stdin);
				scanf("%8s", COURSE_CODE);
				printf("Grade Obtained : ");
				rewind(stdin);
				scanf("%s", GRADE);
				printf("Credit Hours : ");
				rewind(stdin);
				scanf("%d", &CREDIT_HOURS);

				if (strcmp(GRADE, "A") == 0 || strcmp(GRADE, "a") == 0)
					GRADE_POINTS1 = 4.00;

				else if (strcmp(GRADE, "A-") == 0 || strcmp(GRADE, "A-") == 0)
					GRADE_POINTS1 = 3.75;

				else if (strcmp(GRADE, "B+") == 0 || strcmp(GRADE, "b+") == 0)
					GRADE_POINTS1 = 3.50;

				else if (strcmp(GRADE, "B") == 0 || strcmp(GRADE, "b") == 0)
					GRADE_POINTS1 = 3.00;

				else if (strcmp(GRADE, "B-") == 0 || strcmp(GRADE, "b-") == 0)
					GRADE_POINTS1 = 2.75;

				else if (strcmp(GRADE, "C+") == 0 || strcmp(GRADE, "c+") == 0)
					GRADE_POINTS1 = 2.50;

				else if (strcmp(GRADE, "C") == 0 || strcmp(GRADE, "c") == 0)
					GRADE_POINTS1 = 2.00;

				else
					GRADE_POINTS1 = 0.00;

				//Formula
				TOTAL_QUALITY_POINTS1 += GRADE_POINTS1 * CREDIT_HOURS;
				TOTAL_CREDIT_HOURSS1 += CREDIT_HOURS;
			}
			GPAS1 = (double)TOTAL_QUALITY_POINTS1 / TOTAL_CREDIT_HOURSS1;
			CGPAS1 = (double)GPAS1;

			//Result
			printf("\n\n");
			printf("===========================================================\n");
			printf("Student Name                   : %s\n", NAME);
			printf("Student ID                     : %s\n", ID);
			printf("Quality Points Earned          : %.2f\n", TOTAL_QUALITY_POINTS1);
			printf("Total Quality Points Earned    : %.2f\n", TOTAL_QUALITY_POINTS1);
			printf("Credit Hours Earned            : %d\n", TOTAL_CREDIT_HOURSS1);
			printf("Total Credit Hours Earned      : %d\n", TOTAL_CREDIT_HOURSS1);
			printf("Student's GPA                  : %.2f\n", GPAS1);
			printf("Student's CGPA                 : %.2f\n", CGPAS1);
			printf("============================================================\n\n");
		}

		else if (SEMESTER == 2) {
			printf("Enter number of courses taken : "); //Let user to enter number of courses taken
			scanf("%d", &noOfCourse);
			for (courseAction = 0; courseAction < noOfCourse; courseAction++)
			{
				printf("Enter course code %d : ", courseAction + 1);
				rewind(stdin);
				scanf("%8s", COURSE_CODE);
				printf("Grade Obtained : ");
				rewind(stdin);
				scanf("%s", GRADE);
				printf("Credit Hours : ");
				rewind(stdin);
				scanf("%d", &CREDIT_HOURS);

				if (strcmp(GRADE, "A") == 0 || strcmp(GRADE, "a") == 0)
					GRADE_POINTS2 = 4.00;

				else if (strcmp(GRADE, "A-") == 0 || strcmp(GRADE, "A-") == 0)
					GRADE_POINTS2 = 3.75;

				else if (strcmp(GRADE, "B+") == 0 || strcmp(GRADE, "b+") == 0)
					GRADE_POINTS2 = 3.50;

				else if (strcmp(GRADE, "B") == 0 || strcmp(GRADE, "b") == 0)
					GRADE_POINTS2 = 3.00;

				else if (strcmp(GRADE, "B-") == 0 || strcmp(GRADE, "b-") == 0)
					GRADE_POINTS2 = 2.75;

				else if (strcmp(GRADE, "C+") == 0 || strcmp(GRADE, "c+") == 0)
					GRADE_POINTS2 = 2.50;

				else if (strcmp(GRADE, "C") == 0 || strcmp(GRADE, "c") == 0)
					GRADE_POINTS2 = 2.00;

				else
					GRADE_POINTS2 = 0.00;

				//Formula
				TOTAL_QUALITY_POINTS2 += GRADE_POINTS2 * CREDIT_HOURS;
				TOTAL_CREDIT_HOURSS2 += CREDIT_HOURS;
			}
			GPAS2 = (double)TOTAL_QUALITY_POINTS2 / TOTAL_CREDIT_HOURSS2;
			CGPAS2 = (double)(TOTAL_QUALITY_POINTS1 + TOTAL_QUALITY_POINTS2) / (TOTAL_CREDIT_HOURSS1 + TOTAL_CREDIT_HOURSS2);

			//Result
			printf("\n\n");
			printf("===========================================================\n");
			printf("Student Name                   : %s\n", NAME);
			printf("Student ID                     : %s\n", ID);
			printf("Quality Points Earned          : %.2f\n", TOTAL_QUALITY_POINTS2);
			printf("Total Quality Points Earned    : %.2f\n", TOTAL_QUALITY_POINTS1 + TOTAL_QUALITY_POINTS2);
			printf("Credit Hours Earned            : %d\n", TOTAL_CREDIT_HOURSS2);
			printf("Total Credit Hours Earned      : %d\n", TOTAL_CREDIT_HOURSS1 + TOTAL_CREDIT_HOURSS2);
			printf("Student's GPA                  : %.2f\n", GPAS2);
			printf("Student's CGPA                 : %.2f\n", CGPAS2);
			printf("============================================================\n\n");
		}

		else if (SEMESTER == 3) {
			printf("Enter number of courses taken : "); //Let user to enter number of courses taken
			scanf("%d", &noOfCourse);
			for (courseAction = 0; courseAction < noOfCourse; courseAction++)
			{
				printf("Enter course code %d : ", courseAction + 1);
				rewind(stdin);
				scanf("%8s", COURSE_CODE);
				printf("Grade Obtained : ");
				rewind(stdin);
				scanf("%s", GRADE);
				printf("Credit Hours : ");
				rewind(stdin);
				scanf("%d", &CREDIT_HOURS);

				if (strcmp(GRADE, "A") == 0 || strcmp(GRADE, "a") == 0)
					GRADE_POINTS3 = 4.00;

				else if (strcmp(GRADE, "A-") == 0 || strcmp(GRADE, "A-") == 0)
					GRADE_POINTS3 = 3.75;

				else if (strcmp(GRADE, "B+") == 0 || strcmp(GRADE, "b+") == 0)
					GRADE_POINTS3 = 3.50;

				else if (strcmp(GRADE, "B") == 0 || strcmp(GRADE, "b") == 0)
					GRADE_POINTS3 = 3.00;

				else if (strcmp(GRADE, "B-") == 0 || strcmp(GRADE, "b-") == 0)
					GRADE_POINTS3 = 2.75;

				else if (strcmp(GRADE, "C+") == 0 || strcmp(GRADE, "c+") == 0)
					GRADE_POINTS3 = 2.50;

				else if (strcmp(GRADE, "C") == 0 || strcmp(GRADE, "c") == 0)
					GRADE_POINTS3 = 2.00;

				else
					GRADE_POINTS3 = 0.00;

				//Formula
				TOTAL_QUALITY_POINTS3 += GRADE_POINTS3 * CREDIT_HOURS;
				TOTAL_CREDIT_HOURSS3 += CREDIT_HOURS;
			}
			GPAS3 = (double)TOTAL_QUALITY_POINTS3 / TOTAL_CREDIT_HOURSS3;
			CGPAS3 = (double)(TOTAL_QUALITY_POINTS1 + TOTAL_QUALITY_POINTS2 + TOTAL_QUALITY_POINTS3) / (TOTAL_CREDIT_HOURSS1 + TOTAL_CREDIT_HOURSS2 + TOTAL_CREDIT_HOURSS3);

			//Result
			printf("\n\n");
			printf("===========================================================\n");
			printf("Student Name                   : %s\n", NAME);
			printf("Student ID                     : %s\n", ID);
			printf("Quality Points Earned          : %.2f\n", TOTAL_QUALITY_POINTS3);
			printf("Total Quality Points Earned    : %.2f\n", TOTAL_QUALITY_POINTS1 + TOTAL_QUALITY_POINTS2 + TOTAL_QUALITY_POINTS3);
			printf("Credit Hours Earned            : %d\n", TOTAL_CREDIT_HOURSS3);
			printf("Total Credit Hours Earned      : %d\n", TOTAL_CREDIT_HOURSS1 + TOTAL_CREDIT_HOURSS2 + TOTAL_CREDIT_HOURSS3);
			printf("Student's GPA                  : %.2f\n", GPAS3);
			printf("Student's CGPA                 : %.2f\n", CGPAS3);
			printf("============================================================\n\n");
		}

		else {
			printf("Invalid semester\n");
			printf("\n");
		}

	} while (SEMESTER != 0);
	return 0;
}

void staffMalay()
{
	printf("\n\n");
	printf("Masuk nama murid : ");
	rewind(stdin);
	scanf("%30[^\n]", NAME);
	printf("Masuk ID murid : ");
	scanf("%10s", ID);
	do {
		printf("Masuk sesi semester ( 0 untuk keluar ): ");
		rewind(stdin);
		scanf("%d", &SEMESTER);

		if (SEMESTER == 1) {
			printf("Masuk bilangan kursus diambil : "); //Let user to enter number of courses taken
			scanf("%d", &noOfCourse);
			for (courseAction = 0; courseAction < noOfCourse; courseAction++)
			{
				printf("Masuk Kod Kursus %d : ", courseAction + 1);
				rewind(stdin);
				scanf("%8s", COURSE_CODE);
				printf("Gred diperolehi : ");
				rewind(stdin);
				scanf("%s", GRADE);
				printf("Jam Kredit : ");
				rewind(stdin);
				scanf("%d", &CREDIT_HOURS);

				if (strcmp(GRADE, "A") == 0 || strcmp(GRADE, "a") == 0)
					GRADE_POINTS1 = 4.00;

				else if (strcmp(GRADE, "A-") == 0 || strcmp(GRADE, "A-") == 0)
					GRADE_POINTS1 = 3.75;

				else if (strcmp(GRADE, "B+") == 0 || strcmp(GRADE, "b+") == 0)
					GRADE_POINTS1 = 3.50;

				else if (strcmp(GRADE, "B") == 0 || strcmp(GRADE, "b") == 0)
					GRADE_POINTS1 = 3.00;

				else if (strcmp(GRADE, "B-") == 0 || strcmp(GRADE, "b-") == 0)
					GRADE_POINTS1 = 2.75;

				else if (strcmp(GRADE, "C+") == 0 || strcmp(GRADE, "c+") == 0)
					GRADE_POINTS1 = 2.50;

				else if (strcmp(GRADE, "C") == 0 || strcmp(GRADE, "c") == 0)
					GRADE_POINTS1 = 2.00;

				else
					GRADE_POINTS1 = 0.00;

				//Formula
				TOTAL_QUALITY_POINTS1 += GRADE_POINTS1 * CREDIT_HOURS;
				TOTAL_CREDIT_HOURSS1 += CREDIT_HOURS;
			}

			GPAS1 = (double)TOTAL_QUALITY_POINTS1 / TOTAL_CREDIT_HOURSS1;
			CGPAS1 = (double)GPAS1;

			//Result
			printf("\n\n");
			printf("===========================================================\n");
			printf("Nama murid                      : %s\n", NAME);
			printf("ID murid                        : %s\n", ID);
			printf("Point Kualiti diperolehi        : %.2f", TOTAL_QUALITY_POINTS1);
			printf("Jumlah Point Kualiti diperolehi : %.2f", TOTAL_QUALITY_POINTS1);
			printf("Jam kredit diperolehi           : %d\n", TOTAL_CREDIT_HOURSS1);
			printf("Jumlah jam kredit diperolehi    : %d\n", TOTAL_CREDIT_HOURSS1);
			printf("GPA murid                       : %.2f\n", GPAS1);
			printf("CGPA murid                      : %.2f\n", CGPAS1);
			printf("============================================================\n\n");
		}

		else if (SEMESTER == 2) {
			printf("Masuk bilangan kursus diambil : "); //Let user to enter number of courses taken
			scanf("%d", &noOfCourse);
			for (courseAction = 0; courseAction < noOfCourse; courseAction++)
			{
				printf("Masuk Kod Kursus %d : ", courseAction + 1);
				rewind(stdin);
				scanf("%8s", COURSE_CODE);
				printf("Gred diperolehi : ");
				rewind(stdin);
				scanf("%s", GRADE);
				printf("Jam Kredit : ");
				rewind(stdin);
				scanf("%d", &CREDIT_HOURS);

				if (strcmp(GRADE, "A") == 0 || strcmp(GRADE, "a") == 0)
					GRADE_POINTS2 = 4.00;

				else if (strcmp(GRADE, "A-") == 0 || strcmp(GRADE, "A-") == 0)
					GRADE_POINTS2 = 3.75;

				else if (strcmp(GRADE, "B+") == 0 || strcmp(GRADE, "b+") == 0)
					GRADE_POINTS2 = 3.50;

				else if (strcmp(GRADE, "B") == 0 || strcmp(GRADE, "b") == 0)
					GRADE_POINTS2 = 3.00;

				else if (strcmp(GRADE, "B-") == 0 || strcmp(GRADE, "b-") == 0)
					GRADE_POINTS2 = 2.75;

				else if (strcmp(GRADE, "C+") == 0 || strcmp(GRADE, "c+") == 0)
					GRADE_POINTS2 = 2.50;

				else if (strcmp(GRADE, "C") == 0 || strcmp(GRADE, "c") == 0)
					GRADE_POINTS2 = 2.00;

				else
					GRADE_POINTS2 = 0.00;

				//Formula
				TOTAL_QUALITY_POINTS2 += GRADE_POINTS2 * CREDIT_HOURS;
				TOTAL_CREDIT_HOURSS2 += CREDIT_HOURS;
			}
			GPAS2 = (double)TOTAL_QUALITY_POINTS2 / TOTAL_CREDIT_HOURSS2;
			CGPAS2 = (double)(TOTAL_QUALITY_POINTS1 + TOTAL_QUALITY_POINTS2) / (TOTAL_CREDIT_HOURSS1 + TOTAL_CREDIT_HOURSS2);

			//Result
			printf("\n\n");
			printf("===========================================================\n");
			printf("Nama murid                      : %s\n", NAME);
			printf("ID murid                        : %s\n", ID);
			printf("Point Kualiti diperolehi        : %.2f", TOTAL_QUALITY_POINTS2);
			printf("Jumlah Point Kualiti diperolehi : %.2f", TOTAL_QUALITY_POINTS1 + TOTAL_QUALITY_POINTS2);
			printf("Jam kredit diperolehi           : %d\n", TOTAL_CREDIT_HOURSS2);
			printf("Jumlah jam kredit diperolehi    : %d\n", TOTAL_CREDIT_HOURSS1 + TOTAL_CREDIT_HOURSS2);
			printf("GPA murid                       : %.2f\n", GPAS2);
			printf("CGPA murid                      : %.2f\n", CGPAS2);
			printf("============================================================\n\n");
		}

		else if (SEMESTER == 3) {
			printf("Masuk bilangan kursus diambil : "); //Let user to enter number of courses taken
			scanf("%d", &noOfCourse);
			for (courseAction = 0; courseAction < noOfCourse; courseAction++)
			{
				printf("Masuk Kod Kursus %d : ", courseAction + 1);
				rewind(stdin);
				scanf("%8s", COURSE_CODE);
				printf("Gred diperolehi : ");
				rewind(stdin);
				scanf("%s", GRADE);
				printf("Jam Kredit : ");
				rewind(stdin);
				scanf("%d", &CREDIT_HOURS);

				if (strcmp(GRADE, "A") == 0 || strcmp(GRADE, "a") == 0)
					GRADE_POINTS3 = 4.00;

				else if (strcmp(GRADE, "A-") == 0 || strcmp(GRADE, "A-") == 0)
					GRADE_POINTS3 = 3.75;

				else if (strcmp(GRADE, "B+") == 0 || strcmp(GRADE, "b+") == 0)
					GRADE_POINTS3 = 3.50;

				else if (strcmp(GRADE, "B") == 0 || strcmp(GRADE, "b") == 0)
					GRADE_POINTS3 = 3.00;

				else if (strcmp(GRADE, "B-") == 0 || strcmp(GRADE, "b-") == 0)
					GRADE_POINTS3 = 2.75;

				else if (strcmp(GRADE, "C+") == 0 || strcmp(GRADE, "c+") == 0)
					GRADE_POINTS3 = 2.50;

				else if (strcmp(GRADE, "C") == 0 || strcmp(GRADE, "c") == 0)
					GRADE_POINTS3 = 2.00;

				else
					GRADE_POINTS3 = 0.00;

				//Formula
				TOTAL_QUALITY_POINTS3 += GRADE_POINTS3 * CREDIT_HOURS;
				TOTAL_CREDIT_HOURSS3 += CREDIT_HOURS;
			}
			GPAS3 = (double)TOTAL_QUALITY_POINTS3 / TOTAL_CREDIT_HOURSS3;
			CGPAS3 = (double)(TOTAL_QUALITY_POINTS1 + TOTAL_QUALITY_POINTS2 + TOTAL_QUALITY_POINTS3) / (TOTAL_CREDIT_HOURSS1 + TOTAL_CREDIT_HOURSS2 + TOTAL_CREDIT_HOURSS3);

			//Result
			printf("\n\n");
			printf("===========================================================\n");
			printf("Nama murid                      : %s\n", NAME);
			printf("ID murid                        : %s\n", ID);
			printf("Point Kualiti diperolehi        : %.2f", TOTAL_QUALITY_POINTS3);
			printf("Jumlah Point Kualiti diperolehi : %.2f", TOTAL_QUALITY_POINTS1 + TOTAL_QUALITY_POINTS2 + TOTAL_QUALITY_POINTS3);
			printf("Jam kredit diperolehi           : %d\n", TOTAL_CREDIT_HOURSS3);
			printf("Jumlah jam kredit diperolehi    : %d\n", TOTAL_CREDIT_HOURSS1 + TOTAL_CREDIT_HOURSS2 + TOTAL_CREDIT_HOURSS3);
			printf("GPA murid                       : %.2f\n", GPAS3);
			printf("CGPA murid                      : %.2f\n", CGPAS3);
			printf("============================================================\n\n");
		}

		else {
			printf("Sesi semester tidak sah");
			printf("\n");
		}

	} while (SEMESTER != 0);
	return 0;
}

void studentEnglish()
{
	printf("Enter Student ID to log in : ");
	scanf("%s", ID);
	do {
		printf("Enter which semester session ( 0 to exit ) : ");
		scanf("%d", &SEMESTER);
		if (SEMESTER == 1)
		{
			printf("\n\n");
			printf("===========================================================\n");
			printf("Student Name                   : %s\n", NAME);
			printf("Student ID                     : %s\n", ID);
			printf("Quality Points Earned          : %.2f\n", TOTAL_QUALITY_POINTS1);
			printf("Total Quality Points Earned    : %.2f\n", TOTAL_QUALITY_POINTS1);
			printf("Credit Hours Earned            : %d\n", TOTAL_CREDIT_HOURSS1);
			printf("Total Credit Hours Earned      : %d\n", TOTAL_CREDIT_HOURSS1);
			printf("Student's GPA                  : %.2f\n", GPAS1);
			printf("Student's CGPA                 : %.2f\n", CGPAS1);
			printf("============================================================\n\n");
		}

		else if (SEMESTER == 2)
		{
			printf("\n\n");
			printf("===========================================================\n");
			printf("Student Name                   : %s\n", NAME);
			printf("Student ID                     : %s\n", ID);
			printf("Quality Points Earned          : %.2f\n", TOTAL_QUALITY_POINTS2);
			printf("Total Quality Points Earned    : %.2f\n", TOTAL_QUALITY_POINTS1 + TOTAL_QUALITY_POINTS2);
			printf("Credit Hours Earned            : %d\n", TOTAL_CREDIT_HOURSS2);
			printf("Total Credit Hours Earned      : %d\n", TOTAL_CREDIT_HOURSS1 + TOTAL_CREDIT_HOURSS2);
			printf("Student's GPA                  : %.2f\n", GPAS2);
			printf("Student's CGPA                 : %.2f\n", CGPAS2);
			printf("============================================================\n\n");
		}

		else if (SEMESTER == 3)
		{
			printf("\n\n");
			printf("===========================================================\n");
			printf("Student Name                   : %s\n", NAME);
			printf("Student ID                     : %s\n", ID);
			printf("Quality Points Earned          : %.2f\n", TOTAL_QUALITY_POINTS3);
			printf("Total Quality Points Earned    : %.2f\n", TOTAL_QUALITY_POINTS1 + TOTAL_QUALITY_POINTS2 + TOTAL_QUALITY_POINTS3);
			printf("Credit Hours Earned            : %d\n", TOTAL_CREDIT_HOURSS3);
			printf("Total Credit Hours Earned      : %d\n", TOTAL_CREDIT_HOURSS1 + TOTAL_CREDIT_HOURSS2 + TOTAL_CREDIT_HOURSS3);
			printf("Student's GPA                  : %.2f\n", GPAS3);
			printf("Student's CGPA                 : %.2f\n", CGPAS3);
			printf("============================================================\n\n");
		}

		else
		{
			printf("Invalid semester");
			printf("\n\n");
		}
	} while (SEMESTER != 0);
	return 0;
}

void studentMalay()
{
	printf("Masuk ID Murid untuk log masuk : ");
	scanf("%s", ID);
	do {
		printf("Masuk sesi semester  ( 0 untuk keluar ) : ");
		scanf("%d", &SEMESTER);
		if (SEMESTER == 1)
		{
			printf("\n\n");
			printf("===========================================================\n");
			printf("Nama murid                      : %s\n", NAME);
			printf("ID murid                        : %s\n", ID);
			printf("Point Kualiti diperolehi        : %.2f", TOTAL_QUALITY_POINTS1);
			printf("Jumlah Point Kualiti diperolehi : %.2f", TOTAL_QUALITY_POINTS1);
			printf("Jam kredit diperolehi           : %d\n", TOTAL_CREDIT_HOURSS1);
			printf("Jumlah jam kredit diperolehi    : %d\n", TOTAL_CREDIT_HOURSS1);
			printf("GPA murid                       : %.2f\n", GPAS1);
			printf("CGPA murid                      : %.2f\n", CGPAS1);
			printf("============================================================\n\n");
		}

		else if (SEMESTER == 2)
		{
			printf("\n\n");
			printf("===========================================================\n");
			printf("Nama murid                      : %s\n", NAME);
			printf("ID murid                        : %s\n", ID);
			printf("Point Kualiti diperolehi        : %.2f", TOTAL_QUALITY_POINTS2);
			printf("Jumlah Point Kualiti diperolehi : %.2f", TOTAL_QUALITY_POINTS1 + TOTAL_QUALITY_POINTS2);
			printf("Jam kredit diperolehi           : %d\n", TOTAL_CREDIT_HOURSS2);
			printf("Jumlah jam kredit diperolehi    : %d\n", TOTAL_CREDIT_HOURSS1 + TOTAL_CREDIT_HOURSS2);
			printf("GPA murid                       : %.2f\n", GPAS2);
			printf("CGPA murid                      : %.2f\n", CGPAS2);
			printf("============================================================\n\n");
		}

		else if (SEMESTER == 3)
		{
			printf("\n\n");
			printf("===========================================================\n");
			printf("Nama murid                      : %s\n", NAME);
			printf("ID murid                        : %s\n", ID);
			printf("Point Kualiti diperolehi        : %.2f", TOTAL_QUALITY_POINTS3);
			printf("Jumlah Point Kualiti diperolehi : %.2f", TOTAL_QUALITY_POINTS1 + TOTAL_QUALITY_POINTS2 + TOTAL_QUALITY_POINTS3);
			printf("Jam kredit diperolehi           : %d\n", TOTAL_CREDIT_HOURSS3);
			printf("Jumlah jam kredit diperolehi    : %d\n", TOTAL_CREDIT_HOURSS1 + TOTAL_CREDIT_HOURSS2 + TOTAL_CREDIT_HOURSS3);
			printf("GPA murid                       : %.2f\n", GPAS3);
			printf("CGPA murid                      : %.2f\n", CGPAS3);
			printf("============================================================\n\n");
		}

		else {
			printf("\nSesi semeter tidak sah\n");
			printf("\n\n");
		}

	} while (SEMESTER != 0);
	return 0;
}

void invalid()
{
	printf("\n\n");
	printf("Invalid option / Kesalahan pilihan\a\a\a\a");
	return 0;
}

void displayGradeScale()
{
	printf("Grade Scale :\n");
	printf("A  (80-100) - Outstanding     (4.00)\n");
	printf("A- (75-79)  - Excellent       (3.75)\n");
	printf("B+ (70-74)  - Very Good       (3.50)\n");
	printf("B  (65-69)  - Good            (3.00)\n");
	printf("B- (60-64)  - Above Average   (2.75)\n");
	printf("C+ (55-59)  - Average         (2.50)\n");
	printf("C  (50-54)  - Below Average   (2.00)\n");
	printf("F  (0-49)   - Weak            (0.00)\n");
	return 0;
}

