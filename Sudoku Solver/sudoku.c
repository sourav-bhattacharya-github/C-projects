#include <stdio.h>

#define N 9

int puzzle[N][N] = {
    // {3, 0, 0, 0, 2, 0, 0, 7, 0},
    // {9, 0, 0, 5, 0, 0, 0, 1, 4},
    // {0, 1, 6, 3, 7, 0, 0, 0, 8},
    // {2, 0, 0, 8, 0, 0, 0, 0, 1},
    // {5, 0, 0, 0, 4, 1, 8, 0, 0},
    // {0, 8, 9, 0, 0, 0, 0, 5, 0},
    // {0, 0, 5, 0, 1, 0, 2, 8, 0},
    // {0, 4, 0, 0, 0, 6, 0, 9, 3},
    // {7, 3, 1, 0, 8, 2, 0, 0, 0},

    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9},
};

void show_puzzle(int puzzle[N][N]);
int valid_move(int puzzle[N][N], int row, int col, int val);
int solve_puzzle(int puzzle[N][N], int row, int col);

int main()
{
  printf("\n\t***Welcome to Sudoku Solver***\n");
  printf("\nGiven Puzzle");
  show_puzzle(puzzle);
  if (solve_puzzle(puzzle, 0, 0))
  {
    printf("\nThe puzzle is solved");
    show_puzzle(puzzle);
  }
  else
  {
    printf("\nNo solution exists\n");
  }
  return 0;
}

void show_puzzle(int puzzle[N][N])
{
  printf("\n+-------+-------+-------+");
  for (int row = 0; row < N; row++)
  {
    if (row % 3 == 0 && row != 0)
    {
      printf("\n|-------+-------+-------|");
    }
    printf("\n");
    for (int col = 0; col < N; col++)
    {
      if (col % 3 == 0)
      {
        printf("| ");
      }
      if (puzzle[row][col] != 0)
      {
        printf("%d ", puzzle[row][col]);
      }
      else
      {
        printf("  ");
      }
    }
    printf("|");
  }
  printf("\n+-------+-------+-------+\n");
}

int valid_move(int puzzle[N][N], int row, int col, int val)
{
  // valid row and cloumn check
  for (int i = 0; i < N; i++)
  {
    if (puzzle[row][i] == val || puzzle[i][col] == val)
    {
      return 0;
    }
  }

  int start_row = row - row % 3;
  int start_col = col - col % 3;

  for (int i = 0; i < 3; i++) // check 3x3 grid
  {
    for (int j = 0; j < 3; j++)
    {
      if (puzzle[i + start_row][j + start_col] == val)
      {
        return 0;
      }
    }
  }

  return 1;
}

int solve_puzzle(int puzzle[N][N], int row, int col)
{

  if (col == N) // move to next row if column is out of bound
  {
    if (row == N - 1) // base case for recursion
    {
      return 1; // puzzle is solved
    }
    row++;
    col = 0;
  }

  if (puzzle[row][col] != 0)
  {
    return solve_puzzle(puzzle, row, col + 1);
  }

  for (int val = 1; val <= N; val++)
  {
    if (valid_move(puzzle, row, col, val))
    {
      puzzle[row][col] = val;                 // assign the value
      if (solve_puzzle(puzzle, row, col + 1)) // recursive call
      {
        return 1;
      }
      puzzle[row][col] = 0; // backtrack
    }
  }

  return 0;
}