#include <stdio.h>
#include <stdbool.h>

#define MAX 20  // Maximum board size

// Function to print the chessboard
void printBoard(int board[MAX][MAX], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

// Function to check if a queen can be placed on board[row][col]
bool isSafe(int board[MAX][MAX], int row, int col, int N) {
    int i, j;

    // Check this column on upper side
    for (i = 0; i < row; i++) {
        if (board[i][col]) {
            return false;
        }
    }

    // Check upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    // Check upper diagonal on right side
    for (i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j]) {
            return false;
        }
    }

    return true;
}

// Function to solve the N-Queens problem using backtracking
bool solveNQUtil(int board[MAX][MAX], int row, int N) {
    // If all queens are placed, return true
    if (row >= N) {
        return true;
    }

    // Try placing this queen in all columns one by one
    for (int col = 0; col < N; col++) {
        // Check if it is safe to place the queen
        if (isSafe(board, row, col, N)) {
            // Place this queen on board[row][col]
            board[row][col] = 1;

            // Recur to place the rest of the queens
            if (solveNQUtil(board, row + 1, N)) {
                return true;
            }

            // If placing queen in board[row][col] does not lead to a solution
            // then remove the queen from board[row][col]
            board[row][col] = 0;
        }
    }

    return false;
}

// Function to solve the N-Queens problem
void solveNQ(int N) {
    int board[MAX][MAX] = {0};

    if (solveNQUtil(board, 0, N) == false) {
        printf("Solution does not exist");
        return;
    }

    printBoard(board, N);
}

int main() {
    int N;

    // Input number of queens (size of the board)
    printf("Enter the number of queens: ");
    scanf("%d", &N);

    if (N <= 0 || N > MAX) {
        printf("Invalid number of queens. Please enter a value between 1 and %d.\n", MAX);
        return 1;
    }

    printf("Solution for %d queens:\n", N);
    solveNQ(N);

    return 0;
}

