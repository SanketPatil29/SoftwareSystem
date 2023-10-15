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
	char student_id[10];
    char password[10];
	char name[20];
    char dept[20];
    char age[10];
    char email[20];
    char address[30];
};

struct faculty
{
    char password[20];
	char faculty_id[11];
	char dept[20];
	char name[20];
    char address[30];
    char designation[20];
    char email[25];
};

// Structure to represent a course
struct course {
    char course_id[10];
    char course_name[10];
    char department[10];
    char seats[10];
    char credits[10];
};

struct student_course{
    char student_id[10];
    char course_id[10];
};

#endif // STRUCTURE_H