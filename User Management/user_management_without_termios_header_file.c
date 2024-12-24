#include <stdio.h>
#include <string.h>
#include <unistd.h>
// #include <termios.h>

#define CREDENTIAL_LENGTH 100
#define MAX_USER 10

typedef struct
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
} User;

User user[MAX_USER];
int user_count = 0;

int show_menu();
void register_user();
int login_user(); // return the user index
void input_credential(char *username, char *password);
void fix_fgets_input(char *);

int main()
{
    int option, user_index;

    while (1)
    {
        option = show_menu();

        switch (option)
        {
        case 1: /* Register */
            register_user();
            break;
        case 2: /* Login */
            user_index = login_user();
            if (user_index >= 0)
            {
                printf("\n Login successfully Welcome, %s! \n", user[user_index].username);
            }
            else
            {
                printf("\n Login faild! Incorrect username or password");
            }
            break;
        case 3: /* Exit */
            printf("\n Exiting Program \n\n");
            return 0;
            break;

        default:
            printf("\n Invalid option. Please try again !! \n");
            break;
        }
    }

    return 0;
}

int show_menu()
{
    int option;
    printf("\n Welcome to user Management");
    printf("\n 1. Register");
    printf("\n 2. Login");
    printf("\n 3. Exit");
    printf("\n Select an option : ");
    scanf("%d", &option);
    getchar();
    return option;
}

void register_user()
{
    if (user_count == MAX_USER)
    {
        printf("\n Maximun %d user are suported! No more registration allowed !! \n", MAX_USER);
        return;
    }
    printf("\n Register a new use");
    int new_index = user_count;

    // get username and password
    input_credential(user[new_index].username, user[new_index].password);

    user_count++;

    printf("\n Registration successful! \n");
}

int login_user()
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];

    // get password
    input_credential(username, password);

    for (int i = 0; i < CREDENTIAL_LENGTH; i++)
    {
        if (strcmp(username, user[i].username) == 0 && strcmp(password, user[i].password) == 0)
        {
            return i;
        }
    }

    return -1;
}

void input_credential(char *username, char *password)
{

    printf("\n Enter username : ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(username);

    // change termnal properties
    // struct termios old_props, new_props;

    printf("Enter password: ");
    fgets(password, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(password);
}
void fix_fgets_input(char *string)
{
    int index = strcspn(string, "\n"); // find the index of "\n" (means enter)
    string[index] = '\0';
}
