#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SIZE 200

int is_special(char ch) {
    return !isalnum(ch) && ch != '.' && ch != '\n';
}

long long compute_sum(char grid[][MAX_SIZE], int rows, int cols) {
    int r, c;
    char buffer[MAX_SIZE] = "\0";
    int buffer_index = 0;
    long long total_sum = 0;
    int is_special_char_found = 0;

    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            if (isdigit(grid[r][c])) {
                // Check surrounding characters to identify if it's surrounded by special characters
                if ((r > 0 && is_special(grid[r - 1][c])) ||  // Above
                    (r < rows - 1 && is_special(grid[r + 1][c])) ||  // Below
                    (c > 0 && is_special(grid[r][c - 1])) ||  // Left
                    (c < cols - 1 && is_special(grid[r][c + 1])) ||  // Right
                    (r > 0 && c > 0 && is_special(grid[r - 1][c - 1])) ||  // Top-left diagonal
                    (r > 0 && c < cols - 1 && is_special(grid[r - 1][c + 1])) ||  // Top-right diagonal
                    (r < rows - 1 && c > 0 && is_special(grid[r + 1][c - 1])) ||  // Bottom-left diagonal
                    (r < rows - 1 && c < cols - 1 && is_special(grid[r + 1][c + 1])))  // Bottom-right diagonal 
                {  
                    is_special_char_found = 1;
                }

                buffer[buffer_index++] = grid[r][c];
                buffer[buffer_index] = '\0';
                
            } else {
                // Process the buffer if it's not empty
                if (buffer[0] != '\0') {
                    if (is_special_char_found) {
                        char *end_ptr;
                        long long number = strtoll(buffer, &end_ptr, 10);
                        total_sum += number;
                        is_special_char_found = 0;
                    }
                    
                    buffer_index = 0;
                    buffer[0] = '\0';  // Clear buffer
                }
            }
        }
    }

    return total_sum;
}

void display_matrix(char grid[][MAX_SIZE], int rows, int cols) {
    int r, c;
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            printf("%c ", grid[r][c]);
        }
        printf("\n");
    }
}

int main() {
    FILE *file;
    char grid[MAX_SIZE][MAX_SIZE]; 
    char character;
    int row_count = 0, col_count = 0;

    // Open the file
    file = fopen("input3.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file.\n");
        return 1;
    }

    // Read the file
    while ((character = fgetc(file)) != EOF && row_count < MAX_SIZE) {
        if (character == '\n') {
            grid[row_count][col_count] = '\n';  
            row_count++;
            col_count = 0;
        } else if (col_count < MAX_SIZE) {
            grid[row_count][col_count] = character;
            col_count++;
        }
    }

    // Handle the last row if it doesn't end with a newline
    if (col_count > 0) {
        grid[row_count][col_count] = '\n';  
        row_count++;
    }

    // Calculate the sum and print it
    col_count++;
    printf("Sum is %lld\n", compute_sum(grid, row_count, col_count));

    fclose(file);
    return 0;
}
