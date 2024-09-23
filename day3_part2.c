#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SIZE 200

long long get_number(char grid[][MAX_SIZE], int r, int c, int cols) {
    char buffer[MAX_SIZE] = {0};
    int buffer_index = 0;
    
    while (c > 0 && isdigit(grid[r][c-1])) {
        c--;
    }
    
    while (c < cols && isdigit(grid[r][c])) {
        buffer[buffer_index++] = grid[r][c++];
    }
    
    return atoll(buffer);
}

long long compute_gear_ratio_sum(char grid[][MAX_SIZE], int rows, int cols) {
    long long total_sum = 0;
    int r, c, i, j;

    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            if (grid[r][c] == '*') {
                int count = 0;
                long long numbers[2] = {0, 0};
                
                for (i = -1; i <= 1; i++) {
                    for (j = -1; j <= 1; j++) {
                        if (r+i >= 0 && r+i < rows && c+j >= 0 && c+j < cols) {
                            if (isdigit(grid[r+i][c+j])) {
                                long long num = get_number(grid, r+i, c+j, cols);
                                if (count < 2 && (count == 0 || num != numbers[0])) {
                                    numbers[count++] = num;
                                }
                                while (j+1 <= 1 && isdigit(grid[r+i][c+j+1])) j++;
                            }
                        }
                    }
                }
                
                if (count == 2) {
                    total_sum += numbers[0] * numbers[1];
                }
            }
        }
    }

    return total_sum;
}

int main() {
    char grid[MAX_SIZE][MAX_SIZE] = {0};
    int row_count = 0, col_count = 0;
    char line[MAX_SIZE];

    while (fgets(line, sizeof(line), stdin) && row_count < MAX_SIZE) {
        col_count = strlen(line);
        if (line[col_count - 1] == '\n') {
            line[--col_count] = '\0';
        }
        strncpy(grid[row_count], line, MAX_SIZE - 1);
        grid[row_count][MAX_SIZE - 1] = '\0';
        row_count++;
    }

    printf("Sum of gear ratios: %lld\n", compute_gear_ratio_sum(grid, row_count, col_count));

    return 0;
}