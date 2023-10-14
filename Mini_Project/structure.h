#ifndef STRUCTURE_H
#define STRUCTURE_H

struct UserCredentials
{
    char admin_id[100];
    char pass[100];
};
struct UserCredentials adminCredentials = {"admin01", "0051"};

struct student
{
	char student_id[20];
    char password[20];
	char name[30];
    char dept[20];
    char age[10];
    char email[25];
    char address[100];
};

struct faculty
{
    char password[20];
	char faculty_id[11];
	char dept[20];
	char name[30];
    char address[100];
    char designation[25];
    char email[25];
};

// Structure to represent a course
struct course {
    char course_id[50];
    char course_name[100];
    char department[50];
    int seats;
    int credits;
};

#endif // STRUCTURE_H