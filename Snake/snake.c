#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

void clear_screen();
int main()
{

  return 0;
}

void clear_screen()
{
#ifdef _Win32
  system("cls");
#else
  system("clear");
#endif
}
