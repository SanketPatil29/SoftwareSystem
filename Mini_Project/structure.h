struct UserCredentials
{
    char username[100];
    char pass[100];
};
struct UserCredentials adminCredentials = {"sanket patil", "0051"};

struct student
{
	char login_id[20];
    char password[20];
	char dept[20];
	char name[30];
    char age[10];
    char email[25];
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