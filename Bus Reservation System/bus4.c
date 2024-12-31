#include <stdio.h>
#include <stdlib.h> // for clear the screen
#include <string.h>

#define MAX_BUSES 10
#define MAX_SEATS 20
#define CREDENTIAL_LENGTH 100
#define MAX_USER 10

typedef struct
{
    int bus_id;
    char bus_name[50];
    int seats[MAX_SEATS];
    char name[MAX_SEATS][CREDENTIAL_LENGTH];
} Bus;

typedef struct
{
    char user_name[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
    int ticket_number;
} Users;

Bus buses[MAX_BUSES];
Users user[MAX_USER];
int user_count = 0;

void initialize_buses();
int show_menu();
void user_registration();
void user_login();
void book_ticket();
void cancel_ticket();
void check_bus_status();
void input_credential(char *username, char *password);
int is_exist(char *username, char *password);

int main()
{
    printf("\033[H\033[J");

    printf("\n\n\t\t*** Bus Reservation System ****\n");
    initialize_buses();
    while (1)
    {
        int choice = show_menu();

        switch (choice)
        {
        case 1: // user reg
            user_registration();
            break;
        case 2: // user reg
            user_login();
            break;
        case 3: // user reg
            book_ticket();
            break;
        case 4: // user reg
            cancel_ticket();
            break;
        case 5: // user reg
            check_bus_status();
            break;
        case 6: // exist
            printf("\nClosing the ticket booking system, thanks for visiting");
            printf("\n\n\t\t\t Developed by Sourav Bhattacharya!!!\n\n");
            return 0;
            break;

        default:
            printf("\nInvalid choice");
            break;
        }
    }

    printf("\n\n\t\t\t\t Developed by Sourav Bhattacharya!!!\n\n");

    return 0;
}

int show_menu()
{
    int choice;
    printf("\n-------------------------------\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Book Ticket\n");
    printf("4. Cancel Ticket\n");
    printf("5. Check Bus Status\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    return choice;
}

void initialize_buses()
{
    for (int i = 0; i < MAX_BUSES; i++)
    {
        buses[i].bus_id = i + 1;
        sprintf(buses[i].bus_name, "Bus %d", i + 1);
        for (int j = 0; j < MAX_SEATS; j++)
        {
            buses[i].seats[j] = 0;          // 0 indicates seat is available
            sprintf(buses[i].name[j], " "); // "" no booked
        }
    }
}

void input_credential(char *username, char *password)
{

    fflush(stdin); // clear input buffer

    printf("Enter username : ");
    fgets(username, CREDENTIAL_LENGTH, stdin);

    printf("Enter password: ");
    fgets(password, CREDENTIAL_LENGTH, stdin);
}

int is_exist(char *username, char *password)
{
    for (int i = 0; i < MAX_USER; i++)
    {
        if (strcmp(user[i].user_name, username) == 0 && strcmp(user[i].password, password) == 0)
        {
            return i;
        }
    }
    return -1;
}

void user_registration()
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
    input_credential(username, password);
    int exist = is_exist(username, password);
    if (exist == -1)
    {
        user[user_count].ticket_number = 0;
        strncpy(user[user_count].user_name, username, CREDENTIAL_LENGTH - 1);
        user[user_count].user_name[CREDENTIAL_LENGTH - 1] = '\0';
        strncpy(user[user_count].password, password, CREDENTIAL_LENGTH - 1);
        user[user_count].password[CREDENTIAL_LENGTH - 1] = '\0';
        printf("\nUser registered successfully!\n");
        user_count++;
    }
    if (exist != -1)
    {
        printf("\nAlready exist.");
    }
}

void user_login()
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];

    input_credential(username, password);
    int index = is_exist(username, password);

    if (index != -1)
    {
        printf("\nUser logged is successfully %s ", user[index].user_name);
        if (user[index].ticket_number > 0)
        {
            printf("\nYour booked tickets: \n");
            for (int i = 0; i < MAX_BUSES; i++)
            {
                for (int j = 0; j < MAX_SEATS; j++)
                {
                    if (strcmp(buses[i].name[j], user[index].user_name) == 0)
                    {
                        printf("Bus ID: %d, Seat Number: %d, Name: %s", i + 1, j + 1, buses[i].name[j]);
                    }
                }
            }
        }
        if (user[index].ticket_number == 0)
        {
            printf("\nNo ticket booked yet!");
        }
    }
    if (index == -1)
    {
        printf("\nInvalid username or password!\n");
    }

    return;
}

void book_ticket()
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
    input_credential(username, password);
    int index = is_exist(username, password);

    if (index != -1)
    {
        int bus_id, seat_number, continue_booking = 1;
        while (continue_booking)
        {
            printf("Enter bus ID (1-%d): ", MAX_BUSES);
            scanf("%d", &bus_id);
            printf("Enter seat number (1-%d): ", MAX_SEATS);
            scanf("%d", &seat_number);

            if (bus_id > 0 && bus_id <= MAX_BUSES && seat_number > 0 && seat_number <= MAX_SEATS)
            {
                if (buses[bus_id - 1].seats[seat_number - 1] == 0)
                {
                    buses[bus_id - 1].seats[seat_number - 1] = 1;
                    sprintf(buses[bus_id - 1].name[seat_number - 1], user[index].user_name);
                    user[index].ticket_number++;
                }
                else
                {
                    printf("\nSeat already booked!");
                }
            }
            else
            {
                printf("Invalid bus ID or seat number!");
            }

            printf("\nDo you want to book another ticket? (1/0): ");
            scanf("%d", &continue_booking);
        }
    }
    if (index == -1)
    {
        printf("\nInvalid username or password!\n");
    }

    return;
}

void cancel_ticket()
{

    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
    input_credential(username, password);
    int index = is_exist(username, password);

    if (index != -1)
    {
        int bus_id, seat_number, continue_cancelling = 1;
        while (continue_cancelling)
        {
            printf("Enter bus ID (1-%d): ", MAX_BUSES);
            scanf("%d", &bus_id);
            printf("Enter seat number (1-%d): ", MAX_SEATS);
            scanf("%d", &seat_number);

            if (bus_id > 0 && bus_id <= MAX_BUSES && seat_number > 0 && seat_number <= MAX_SEATS)
            {
                if (buses[bus_id - 1].seats[seat_number - 1] == 1 && strcmp(buses[bus_id - 1].name[seat_number - 1], username) == 0)
                {
                    buses[bus_id - 1].seats[seat_number - 1] = 0;
                    sprintf(buses[bus_id - 1].name[seat_number - 1], " ");
                    user[index].ticket_number--;
                    printf("\nTicket cancelled successfully!");
                }
                else
                {
                    if (user[index].ticket_number == 0)
                    {
                        printf("\nNo Tciket booked by %s!", user[index].user_name);
                    }
                    else
                    {
                        printf("\nSeat is not booked!");
                    }
                }
            }
            else
            {
                printf("\nInvalid bus ID or seat number!");
            }

            printf("\nDo you want to cancel another ticket? (1/0): ");
            scanf("%d", &continue_cancelling);
        }
    }

    if (index == -1)
    {
        printf("\nInvalid username or password!\n");
    }

    return;
}

void check_bus_status()
{
    int bus_id;
    printf("Enter bus ID(1-%d): ", MAX_BUSES);
    scanf("%d", &bus_id);
    if (bus_id > 0 && bus_id <= MAX_BUSES)
    {
        printf("\nBus ID: %d\n", buses[bus_id - 1].bus_id);
        printf("Bus Name: %s\n", buses[bus_id - 1].bus_name);
        printf("Seat Status:\n");
        for (int i = 0; i < MAX_SEATS; i++)
        {
            printf("Seat %d: %s\t", i + 1, buses[bus_id - 1].seats[i] == 0 ? "Available" : "Booked   ");
            if ((i + 1) % 4 == 0)
            {
                printf("\n");
            }
        }
    }
    else
    {
        printf("Invalid bus ID!\n");
    }
}
