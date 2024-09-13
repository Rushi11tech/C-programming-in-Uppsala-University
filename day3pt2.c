#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 200

int is_digit(char c) {
    return isdigit(c);
}

int is_special(char c) {
    return !is_digit(c) && c != '.' && c != '\n' && c != '#';
}

long long parse_number(char *buf) {
    char *endptr;
    return strtoll(buf, &endptr, 10);
}

long long calculate_gear_ratios(char matrix[][MAX_SIZE], int rows, int cols) {
    int i, j;
    long long total_sum = 0;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (matrix[i][j] == '*') {
                int num_count = 0;
                long long num1 = 0, num2 = 0;
                char buf[MAX_SIZE] = "\0";
                int buf_index = 0;

                // Check adjacent cells
                if (i > 0 && is_digit(matrix[i - 1][j])) { // Above
                    if (num_count == 0) {
                        num1 = matrix[i - 1][j] - '0';
                    } else {
                        num2 = matrix[i - 1][j] - '0';
                    }
                    num_count++;
                }
                if (i < rows - 1 && is_digit(matrix[i + 1][j])) { // Below
                    if (num_count == 0) {
                        num1 = matrix[i + 1][j] - '0';
                    } else {
                        num2 = matrix[i + 1][j] - '0';
                    }
                    num_count++;
                }
                if (j > 0 && is_digit(matrix[i][j - 1])) { // Left
                    if (num_count == 0) {
                        num1 = matrix[i][j - 1] - '0';
                    } else {
                        num2 = matrix[i][j - 1] - '0';
                    }
                    num_count++;
                }
                if (j < cols - 1 && is_digit(matrix[i][j + 1])) { // Right
                    if (num_count == 0) {
                        num1 = matrix[i][j + 1] - '0';
                    } else {
                        num2 = matrix[i][j + 1] - '0';
                    }
                    num_count++;
                }
                if (i > 0 && j > 0 && is_digit(matrix[i - 1][j - 1])) { // Top-left diagonal
                    if (num_count == 0) {
                        num1 = matrix[i - 1][j - 1] - '0';
                    } else {
                        num2 = matrix[i - 1][j - 1] - '0';
                    }
                    num_count++;
                }
                if (i > 0 && j < cols - 1 && is_digit(matrix[i - 1][j + 1])) { // Top-right diagonal
                    if (num_count == 0) {
                        num1 = matrix[i - 1][j + 1] - '0';
                    } else {
                        num2 = matrix[i - 1][j + 1] - '0';
                    }
                    num_count++;
                }
                if (i < rows - 1 && j > 0 && is_digit(matrix[i + 1][j - 1])) { // Bottom-left diagonal
                    if (num_count == 0) {
                        num1 = matrix[i + 1][j - 1] - '0';
                    } else {
                        num2 = matrix[i + 1][j - 1] - '0';
                    }
                    num_count++;
                }
                if (i < rows - 1 && j < cols - 1 && is_digit(matrix[i + 1][j + 1])) { // Bottom-right diagonal
                    if (num_count == 0) {
                        num1 = matrix[i + 1][j + 1] - '0';
                    } else {
                        num2 = matrix[i + 1][j + 1] - '0';
                    }
                    num_count++;
                }

                if (num_count == 2) {
                    total_sum += num1 * num2;
                }
            }
        }
    }

    return total_sum;
}

int main() {
    FILE *file;
    char matrix[MAX_SIZE][MAX_SIZE]; 
    char ch;
    int row_count = 0, col_count = 0;

    // Open the file
    file = fopen("input3.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file.\n");
        return 1;
    }

    // Read the file
    while ((ch = fgetc(file)) != EOF && row_count < MAX_SIZE) {
        if (ch == '\n') {
            matrix[row_count][col_count] = '\0';  
            row_count++;
            col_count = 0;
        } else if (col_count < MAX_SIZE - 1) {
            matrix[row_count][col_count++] = ch;
        }
    }

    // Handle the last row
    if (col_count > 0) {
        matrix[row_count][col_count] = '\0';  
        row_count++;
    }

    // Calculate the sum of gear ratios and print the result
    printf("Sum of all gear ratios is %lld\n", calculate_gear_ratios(matrix, row_count, col_count));

    fclose(file);
    return 0;
}
