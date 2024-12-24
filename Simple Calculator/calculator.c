#include <stdio.h>
#include <math.h>

double division(double, double);
double modulus(int, int);
double square(double);

void print_menu();

int main()
{
    int choice;
    double first, second, result;
    while (1)
    {
        print_menu();
        scanf("%d", &choice);
        if (choice == 8)
            break;

        if (choice < 1 || choice > 8)
        {
            fprintf(stderr, " Invalid Menu Choice. ");
            continue;
        }
        if (choice == 7)
        {
            printf("\n Please enter number : ");
            scanf("%lf", &first);
        }
        else
        {
            printf("\n Please enter first number : ");
            scanf("%lf", &first);
            printf(" Now, enter second number : ");
            scanf("%lf", &second);
        }

        switch (choice)
        {
        case 1: /* Add */
            result = first + second;
            break;
        case 2: /* Subtract */
            result = first - second;
            break;
        case 3: /* Multiply */
            result = first * second;
            break;
        case 4: /* Divide */
            result = division(first, second);
            break;
        case 5: /* Modulus */
            result = modulus(first, second);
            break;
        case 6: /* Power */
            result = pow(first, second);
            break;
        case 7: /* Square root */
            result = sqrt(first);
        default:
            break;
        }
        if (!isnan(result))
            printf("\n Result of operation is : %0.2f ", result);
    }

    return 0;
}

double division(double a, double b)
{
    if (b == 0)
    {
        fprintf(stderr, " Invalid Argument for Division");
        return NAN;
    }
    else
    {
        return a / b;
    }
}

double modulus(int a, int b)
{
    if (b == 0)
    {
        fprintf(stderr, " Invalid Argument for Modulus");
        return NAN;
    }
    else
    {
        return a % b;
    }
}
double square(double a)
{
    if (a < 0)
    {
        fprintf(stderr, " Invalid Argument for Square root ");
        return NAN;
    }
    else
    {
        return sqrt(a);
    }
}
void print_menu()
{
    printf("\n\n-----------------------------------------");
    printf("\n WelCome to Simple Claculator \n");
    printf("\n Choose one pf the follwing options : ");
    printf("\n 1. Add");
    printf("\n 2. Subtract");
    printf("\n 3. Multiply");
    printf("\n 4. Divide");
    printf("\n 5. Modulus");
    printf("\n 6. Power");
    printf("\n 7. Square root");
    printf("\n 8. Exit");
    printf("\n Now, enter your choice : ");
}
