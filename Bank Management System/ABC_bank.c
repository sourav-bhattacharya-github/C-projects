#include <stdio.h>
#include <string.h>

int show_menu();
void create_account();
void deposite_money();
void withdraw_money();
void check_balance();

const char *ACCOUNT_FILE = "account.dat";
typedef struct
{
  char name[50];
  int acc_no;
  float balance;
} Account;

int main()
{

  while (1)
  {
    int choice = show_menu();

    switch (choice)
    {
    case 1: // Create Account
      create_account();
      break;
    case 2: // Deposite Money
      deposite_money();
      break;
    case 3: // Withdraw Money
      withdraw_money();
      break;
    case 4: // Check Balance
      check_balance();
      break;
    case 5: // Exit
      printf("Closing The ABC bank, Thanks for visit");
      return 0;
      break;

    default:
      printf("\nInvalid choice");
      break;
    }
  }

  return 0;
}

int show_menu()
{
  int choice;
  printf("\n\n*** Bank Management System ****");
  printf("\n1.Create Account");
  printf("\n2. Deposite Money");
  printf("\n3. Withdraw Money");
  printf("\n4. Check Balance");
  printf("\n5. Exit");
  printf("\nEnter your choice: ");
  scanf("%d", &choice);
  return choice;
}

void create_account()
{
  Account acc;

  // open file to store datils
  FILE *file = fopen(ACCOUNT_FILE, "ab+");
  if (file == NULL)
  {
    printf("\nUnable to open file!");
  }

  char ch;
  do
  {
    ch = getchar();
  } while (ch != '\n' && ch != EOF);

  printf("Enter your name: ");
  fgets(acc.name, sizeof(acc.name), stdin);
  int ind = strcspn(acc.name, "\n");
  acc.name[ind] = '\0';

  printf("Enter your account number: ");
  scanf("%d", &acc.acc_no);

  acc.balance = 0;

  // write in file
  fwrite(&acc, sizeof(acc), 1, file);
  fclose(file);

  printf("\nAccount created successfully");
}

void deposite_money()
{
  FILE *file = fopen(ACCOUNT_FILE, "rb+");
  if (file == NULL)
  {
    printf("Unable to open account file!");
    return;
  }

  int acc_number;
  float money;
  Account acc_read;

  printf("\nEnter your account number: ");
  scanf("%d", &acc_number);
  printf("Enter amount to deposit: ");
  scanf("%f", &money);

  while (fread(&acc_read, sizeof(acc_read), 1, file) != EOF)
  {
    if (acc_read.acc_no == acc_number)
    {
      acc_read.balance += money;
      fseek(file, -(long)sizeof(acc_read), SEEK_CUR);
      fwrite(&acc_read, sizeof(acc_read), 1, file);
      fclose(file);
      printf("\nSuccessfuly deposited Rs %.2f Now balance is Rs %.2f\n", money, acc_read.balance);
      return;
    }
  }

  fclose(file);
  printf("\nMoney could not be deposited as the Account no %d not found in records.\n", acc_number);
}

void withdraw_money()
{
  FILE *file = fopen(ACCOUNT_FILE, "rb+");
  if (file == NULL)
  {
    printf("Unable to open account file!");
    return;
  }

  int acc_number;
  float money;
  Account acc_read;

  printf("\nEnter your account number: ");
  scanf("%d", &acc_number);
  printf("Enter amount to withdraw: ");
  scanf("%f", &money);

  while (fread(&acc_read, sizeof(acc_read), 1, file) != EOF)
  {
    if (acc_read.acc_no == acc_number)
    {
      if (acc_read.balance >= money)
      {
        acc_read.balance -= money;

        // **move the cursor pointer
        fseek(file, -(long)sizeof(acc_read), SEEK_CUR);
        fwrite(&acc_read, sizeof(acc_read), 1, file); // write in the file
        fclose(file);
        printf("\nSuccessfuly withdraw Rs %.2f Now balance is Rs %.2f\n", money, acc_read.balance);
      }
      else
      {
        printf("Insufficient balance!");
      }

      fclose(file);
      return;
    }
  }

  fclose(file);
  printf("\nMoney could not be withdraw as the Account no %d not found in records.\n", acc_number);
}

void check_balance()
{
  FILE *file = fopen(ACCOUNT_FILE, "rb");
  if (file == NULL)
  {
    printf("\nUnable to open file!");
  }

  int acc_nuber;
  Account acc_read;

  printf("\nEnter your Account Number: ");
  scanf("%d", &acc_nuber);

  while (fread(&acc_read, sizeof(acc_read), 1, file))
  {
    if (acc_read.acc_no == acc_nuber) // if acc_number exit
    {
      printf("\nYour current balance id Rs %.2f", acc_read.balance);
      fclose(file);
      return;
    }
  }
  fclose(file);
  printf("\nAccount No: %d wae not find\n", acc_nuber);
}
