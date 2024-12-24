#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

const int BAR_LENGTH = 50;
const int MAX_TASKS = 5;

typedef struct
{
    int id;
    int progress;
    int step;
} Task;

void print_bar(Task task);
void clear_screen();

int main()
{
    Task tasks[MAX_TASKS];
    srand(time(NULL));

    for (int i = 0; i < MAX_TASKS; i++)
    {
        tasks[i].id = i + 1;
        tasks[i].progress = 0;
        tasks[i].step = rand() % 10 + 5;
    }
    int tasks_incompelte = 1;
    while (tasks_incompelte)
    {
        tasks_incompelte = 0;

        // clear the screen
        clear_screen();

        for (int i = 0; i < MAX_TASKS; i++)
        {
            // add step in current progress
            tasks[i].progress += tasks[i].step;

            if (tasks[i].progress > 100) // cheak 100% or not
            {
                tasks[i].progress = 100;
            }
            else if (tasks[i].progress < 100)
            {
                tasks_incompelte = 1;
            }
            // print progress bar
            print_bar(tasks[i]);
        }
        sleep(1);
    }
    printf("\n All tasks completed! \n");
    return 0;
}

void print_bar(Task task)
{
    int bar_to_show = (task.progress * BAR_LENGTH) / 100;

    printf("\nTask %d: [", task.id);
    for (int i = 0; i < BAR_LENGTH; i++)
    {
        if (i < bar_to_show)
        {
            printf("=");
        }
        else
        {
            printf(" ");
        }
    }

    printf("] %d%%\n", task.progress);
}

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}