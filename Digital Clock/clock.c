#include <stdio.h>
#include <stdlib.h> // for clear the screen
#include <time.h>
#include <unistd.h> // this use to see continous time (by using sleep() function)

int input_format();
void fill_time(char *, int);
void fill_date(char *);
void clear_screen();

int main()
{
    char time[50], date[100];

    int format = input_format();

    while (1)
    {
        // create time with format
        fill_time(time, format);
        // create date
        fill_date(date);

        // clear screen
        clear_screen();

        // show the tme & date
        printf("Current Time : %s\n", time);
        printf("Date : %s\n", date);
        sleep(1);
    }
    return 0;
}

int input_format()
{
    int format;
    printf("\n Choose the time format : ");
    printf("\n 1. 24 Hours format");
    printf("\n 2. 12 Hours format (default)");
    printf("\n Make a choices (1 / 2) : ");
    scanf("%d", &format);
    return format;
}

void fill_time(char *buffer, int format)
{
    time_t raw_time;
    struct tm *current_time;

    time(&raw_time);
    current_time = localtime(&raw_time);
    if (format == 1)
    {
        strftime(buffer, 50, "%H:%M:%S", current_time);
    }
    else
    {
        strftime(buffer, 50, "%I:%M:%S %p", current_time);
    }
}

void fill_date(char *buffer)
{
    time_t raw_time;
    struct tm *current_time;
    time(&raw_time);
    current_time = localtime(&raw_time);

    strftime(buffer, 100, "%A %B %d %Y", current_time);
}

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}