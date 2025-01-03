/**
 * Converts a decimal number to its binary representation and prints it.
 * 
 * @param n The decimal number to be converted.
 */
void decimalToBinary(int n);

/**
 * Converts a binary number (given as a string) to its decimal representation.
 * 
 * @param binary The binary number as a string.
 * @return The decimal representation of the binary number.
 */
int binaryToDecimal(char *binary);

/**
 * Converts a decimal number to its octal representation and prints it.
 * 
 * @param n The decimal number to be converted.
 */
void decimalToOctal(int n);

/**
 * Converts a hexadecimal number (given as a string) to its binary representation and prints it.
 * 
 * @param hex The hexadecimal number as a string.
 */
void hexadecimalToBinary(char *hex);

/**
 * Converts a binary number (given as a string) to its hexadecimal representation and prints it.
 * 
 * @param binary The binary number as a string.
 */
void binaryToHexadecimal(char *binary);

/**
 * The main function that provides a menu-driven interface for number system conversions.
 * 
 * @return Exit status of the program.
 */
int main();
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void decimalToBinary(int n) {
    int binaryNum[32];
    int i = 0;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int j = i - 1; j >= 0; j--)
        printf("%d", binaryNum[j]);
    printf("\n");
}

int binaryToDecimal(char *binary) {
    int decimal = 0;
    int length = strlen(binary);
    for (int i = 0; i < length; i++) {
        if (binary[length - i - 1] == '1') {
            decimal += pow(2, i);
        }
    }
    return decimal;
}

void decimalToOctal(int n) {
    int octalNum[32];
    int i = 0;
    while (n != 0) {
        octalNum[i] = n % 8;
        n = n / 8;
        i++;
    }
    for (int j = i - 1; j >= 0; j--)
        printf("%d", octalNum[j]);
    printf("\n");
}

void hexadecimalToBinary(char *hex) {
    int i = 0;
    while (hex[i]) {
        switch (hex[i]) {
            case '0': printf("0000"); break;
            case '1': printf("0001"); break;
            case '2': printf("0010"); break;
            case '3': printf("0011"); break;
            case '4': printf("0100"); break;
            case '5': printf("0101"); break;
            case '6': printf("0110"); break;
            case '7': printf("0111"); break;
            case '8': printf("1000"); break;
            case '9': printf("1001"); break;
            case 'A': case 'a': printf("1010"); break;
            case 'B': case 'b': printf("1011"); break;
            case 'C': case 'c': printf("1100"); break;
            case 'D': case 'd': printf("1101"); break;
            case 'E': case 'e': printf("1110"); break;
            case 'F': case 'f': printf("1111"); break;
            default: printf("\nInvalid hexadecimal digit %c", hex[i]);
        }
        i++;
    }
    printf("\n");
}

void binaryToHexadecimal(char *binary) {
    int decimal = binaryToDecimal(binary);
    printf("%X\n", decimal);
}

int main() {
    int choice, decimal;
    char binary[32], hex[32];

    while (1) {
        printf("Number System Conversion Program\n");
        printf("1. Decimal to Binary\n");
        printf("2. Binary to Decimal\n");
        printf("3. Decimal to Octal\n");
        printf("4. Hexadecimal to Binary\n");
        printf("5. Binary to Hexadecimal\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a decimal number: ");
                scanf("%d", &decimal);
                decimalToBinary(decimal);
                break;
            case 2:
                printf("Enter a binary number: ");
                scanf("%s", binary);
                printf("Decimal: %d\n", binaryToDecimal(binary));
                break;
            case 3:
                printf("Enter a decimal number: ");
                scanf("%d", &decimal);
                decimalToOctal(decimal);
                break;
            case 4:
                printf("Enter a hexadecimal number: ");
                scanf("%s", hex);
                hexadecimalToBinary(hex);
                break;
            case 5:
                printf("Enter a binary number: ");
                scanf("%s", binary);
                binaryToHexadecimal(binary);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}