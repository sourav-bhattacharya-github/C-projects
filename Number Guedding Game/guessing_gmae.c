#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int random, guess;
    int no_of_guess = 0;

    srand(time(NULL));

    printf("\n Wlcome to the world of Guessing Number\n");

    random = rand() % 100 + 1; // Generating between 0 to 100

    // Check the guess
    do
    {
        printf("\n Please enter your guess between 1 to 100 : ");
        scanf("%d", &guess);
        no_of_guess++;

        if (guess < random)
        {
            printf(" Guess larger number. \n");
        }
        else if (guess > random)
        {
            printf(" Guess a smaller number. \n");
        }
        else
        {
            printf("\n Congratulations !!! You have successfully guess the number in %d attempts. \n", no_of_guess);
        }
    } while (random != guess);

    printf("\n Bye bye Thankyou for Playing  ^_^ ");
    printf("\n\n Developed by: Sourav Bhattacharya \n\n");

    return 0;
}