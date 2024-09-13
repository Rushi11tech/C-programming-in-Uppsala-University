#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // For strlen
#include <limits.h> // For INT_MIN

#define MAX_ROWS 100
#define MAX_COLS 100

// Map and visited grid
char map[MAX_ROWS][MAX_COLS];
bool visited[MAX_ROWS][MAX_COLS];

// Direction vectors for moving
int dx[] = {-1, 1, 0, 0}; // Up, Down, Left, Right
int dy[] = {0, 0, -1, 1};
char directions[] = {'^', 'v', '<', '>'}; // Slope directions

int rows, cols;

// Function to check if a move is valid
bool isValid(int x, int y, int prev_x, int prev_y) {
    // Check boundaries
    if (x < 0 || x >= rows || y < 0 || y >= cols) return false;
    // Check if already visited
    if (visited[x][y]) return false;
    // Check if the current tile is a slope and whether we're moving in the correct direction
    if (map[prev_x][prev_y] == '>' && y <= prev_y) return false;
    if (map[prev_x][prev_y] == '<' && y >= prev_y) return false;
    if (map[prev_x][prev_y] == '^' && x >= prev_x) return false;
    if (map[prev_x][prev_y] == 'v' && x <= prev_x) return false;
    return true;
}

// DFS to find the longest path
int dfs(int x, int y) {
    if (x < 0 || x >= rows || y < 0 || y >= cols) return 0;
    if (visited[x][y]) return 0;

    visited[x][y] = true;
    int max_steps = 0;

    // Try all four directions
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isValid(nx, ny, x, y)) {
            int steps = dfs(nx, ny);
            if (steps > max_steps) {
                max_steps = steps;
            }
        }
    }

    visited[x][y] = false;
    return max_steps + 1;
}

int main() {
    FILE *input = fopen("input23.txt", "r");
    if (input == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    // Read the map from the file
    rows = 0;
    while (fgets(map[rows], MAX_COLS, input) != NULL) {
        // Print the row for debugging
        printf("Row %d: %s", rows, map[rows]);
        cols = strlen(map[rows]) - 1; // Ignore the newline character
        rows++;
    }
    fclose(input);

    int longest_hike = 0;

    // Initialize visited array
    memset(visited, 0, sizeof(visited));

    // Start DFS from the first row, where there's a path tile ('.')
    for (int y = 0; y < cols; y++) {
        if (map[0][y] == '.') {
            int hike_length = dfs(0, y);
            if (hike_length > longest_hike) {
                longest_hike = hike_length;
            }
        }
    }

    printf("The longest hike is %d steps.\n", longest_hike);

    return 0;
}
