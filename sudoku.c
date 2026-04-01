#include <stdio.h>
#include <stdbool.h>

#define N 9

int grid[N][N] = {
    {5,3,0,0,7,0,0,0,0},
    {6,0,0,1,9,5,0,0,0},
    {0,9,8,0,0,0,0,6,0},
    {8,0,0,0,6,0,0,0,3},
    {4,0,0,8,0,3,0,0,1},
    {7,0,0,0,2,0,0,0,6},
    {0,6,0,0,0,0,2,8,0},
    {0,0,0,4,1,9,0,0,5},
    {0,0,0,0,8,0,0,7,9}
};

// Check if number can be placed
bool isSafe(int row, int col, int num) {

    // Row + Column check
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return false;
    }

    // 3x3 box check
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[startRow + i][startCol + j] == num)
                return false;

    return true;
}

// Solve using CSP (Backtracking)
bool solve() {

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {

            if (grid[row][col] == 0) {

                for (int num = 1; num <= 9; num++) {

                    if (isSafe(row, col, num)) {
                        grid[row][col] = num;

                        if (solve())
                            return true;

                        grid[row][col] = 0; // backtrack
                    }
                }

                return false; // no number fits
            }
        }
    }

    return true; // solved
}

// Validate initial grid (edge case)
bool isValidInitial() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] != 0) {
                int temp = grid[i][j];
                grid[i][j] = 0;

                if (!isSafe(i, j, temp))
                    return false;

                grid[i][j] = temp;
            }
        }
    }
    return true;
}

int main() {

    if (!isValidInitial()) {
        printf("Invalid Sudoku input!\n");
        return 0;
    }

    if (solve()) {
        printf("\nSudoku Solution:\n\n");

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                printf("%d ", grid[i][j]);
            printf("\n");
        }
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}
