#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 3

typedef struct
{
  int player;
  int computer;
  int draw;
} Score;

int mode;

Score score = {.player = 0, .computer = 0, .draw = 0};

void input_mode();
void clear_screen();
void show_bord(char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void play_game();
void player_move(char board[BOARD_SIZE][BOARD_SIZE], char player);
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE], char player);

int main()
{
  srand(time(NULL));
  int choice;
  input_mode();
  do
  {
    play_game();
    printf("\nPlay again? (1 for yes, 0 for no): ");
    scanf("%d", &choice);
  } while (choice == 1);
  printf("\nBye by ethanks for playing.\n\n");

  return 0;
}

void input_mode()
{
  while (1)
  {
    printf("\nSelect mode: ");
    printf("\n1. With Friend: ");
    printf("\n2. Human(Standard): ");
    printf("\n3. God(Impossible to win): ");

    printf("\nEnter your choice: ");
    scanf("%d", &mode);

    if (mode != 1 && mode != 2 && mode != 3)
      printf("\nIncorrect choice enter (1 / 2)!!\n");
    else
      break;
  }
}

void clear_screen()
{
#ifdef _Win32
  system("cls");
#else
  system("clear");
#endif
}

void show_bord(char board[BOARD_SIZE][BOARD_SIZE])
{
  clear_screen();
  if (mode == 1)
    printf("\nScore - First Player: %d, Second Player: %d, Draws: %d", score.player, score.computer, score.draw);

  if (mode == 2 || mode == 3)
    printf("\nScore - Player X: %d, Computer: %d, Draws: %d", score.player, score.computer, score.draw);

  printf("\nTic-Tac-Toe\n");

  for (int i = 0; i < BOARD_SIZE; i++)
  {
    printf("\n");
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      printf(" %c ", board[i][j]);
      if (j < BOARD_SIZE - 1)
      {
        printf("|");
      }
    }

    if (i < BOARD_SIZE - 1)
    {
      printf("\n---+---+---");
    }
  }
  printf("\n\n");
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player)
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    if (board[i][0] == player && board[i][1] == player && board[i][2] == player) // chec row
    {
      return 1;
    }
    if (board[0][i] == player && board[1][i] == player && board[2][i] == player) // check Column
    {
      return 1;
    }

    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[2][0] == player && board[1][1] == player && board[0][2] == player))
    {
      return 1;
    }
  }

  return 0;
}

int check_draw(char board[BOARD_SIZE][BOARD_SIZE])
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      if (board[i][j] == ' ')
      {
        return 0;
      }
    }
  }

  return 1;
}

int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
  return !(row < 0 || col < 0 ||
           row > 2 || col > 2 ||
           board[row][col] != ' ');
}

void play_game()
{
  char board[BOARD_SIZE][BOARD_SIZE] = {
      {' ', ' ', ' '},
      {' ', ' ', ' '},
      {' ', ' ', ' '},
  };

  // choice playet
  char current_player = rand() % 2 == 0 ? 'X' : '0';

  while (1)
  {
    show_bord(board);
    if (current_player == 'X')
    {
      player_move(board, current_player);
      show_bord(board);
      if (check_win(board, current_player))
      {
        score.player++;
        show_bord(board);
        printf("\nCongratution You have won !!!");
        break;
      }

      current_player = '0';
    }
    else if (current_player == '0')
    {
      if (mode == 1)
      {
        player_move(board, current_player);
      }
      else if (mode == 2 || mode == 3)
      {
        computer_move(board, current_player);
      }

      show_bord(board);
      if (check_win(board, current_player))
      {
        score.computer++;
        show_bord(board);
        if (mode == 1)
        {
          printf("Your Frind Won!!");
        }
        if (mode == 2 || mode == 3)
        {
          printf("I won But you played will....");
        }
        break;
      }
      current_player = 'X';
    }

    if (check_draw(board))
    {
      score.draw++;
      show_bord(board);
      printf("It's a draw!");
      break;
    }
  }
}

void player_move(char board[BOARD_SIZE][BOARD_SIZE], char player)
{
  // if last palce
  int count = 0, last_i, last_j;
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      if (board[i][j] == ' ')
      {
        count++;
        last_i = i;
        last_j = j;
      }
    }
  }

  if (count == 1)
  {
    board[last_i][last_j] = player;
    return;
  }

  int row, col;
  printf("\nPlayer %c's turn.", player);
  do
  {
    printf("\nEnter row and column (1-3) for %c: ", player);
    scanf("%d", &row);
    scanf("%d", &col);

    // convertinr to zero base
    row--;
    col--;
  } while (!is_valid_move(board, row, col));

  board[row][col] = player;
}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE], char computer)
{
  // 1. Play for Immediate win
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      if (board[i][j] == ' ')
      {
        board[i][j] = computer;
        if (check_win(board, computer))
        {
          return;
        }
        board[i][j] = ' ';
      }
    }
  }

  // 2. Play for Immeditate Block
  char opponent = (computer == '0' ? 'X' : '0');
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      if (board[i][j] == ' ')
      {
        board[i][j] = opponent;
        if (check_win(board, opponent))
        {
          board[i][j] = computer;
          return;
        }
        board[i][j] = ' ';
      }
    }
  }
  // God Mode
  if (mode == 3)
  {
    // 3. Play Center if available
    if (board[1][1] == ' ')
    {
      board[1][1] = computer;
      return;
    }

    // 4. Play Corner if available
    int corner[4][2] = {
        {0, 0},
        {0, 2},
        {2, 0},
        {2, 2},
    };

    for (int i = 0; i < 4; i++)
    {
      if (board[corner[i][0]][corner[i][1]] == ' ')
      {
        board[corner[i][0]][corner[i][1]] = computer;
        return;
      }
    }
  }

  // 5. play first available move
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      if (board[i][j] == ' ')
      {
        board[i][j] = computer;
        return;
      }
    }
  }
}