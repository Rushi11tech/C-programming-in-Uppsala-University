#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLORS 3
#define MAX_LINE_LENGTH 100

// Cube limits
#define RED_LIMIT 12
#define GREEN_LIMIT 13
#define BLUE_LIMIT 14

// Structure to hold cube counts for a game
typedef struct {
    int red, green, blue;
} CubeCount;

// Function to parse a subset of cubes (e.g., "3 red, 5 green, 4 blue")
CubeCount parse_subset(char *subset) {
    CubeCount count = {0, 0, 0};
    char *token = strtok(subset, ",");
    while (token != NULL) {
        int num;
        char color[10];
        sscanf(token, "%d %s", &num, color);
        if (strcmp(color, "red") == 0) {
            count.red += num;
        } else if (strcmp(color, "green") == 0) {
            count.green += num;
        } else if (strcmp(color, "blue") == 0) {
            count.blue += num;
        }
        token = strtok(NULL, ",");
    }
    return count;
}

// Function to check if the game is possible based on cube limits
// Function to check if the game is possible based on cube limits
int is_game_possible(char *line) {
    CubeCount total_count = {0, 0, 0};  // Initialize cumulative totals for the game
    char *game_part = strstr(line, ":");
    if (game_part == NULL) return 0;
    
    game_part++;  // Skip the colon
    char *subset = strtok(game_part, ";");
    
    while (subset != NULL) {
        CubeCount subset_count = parse_subset(subset);
        
        // Accumulate the subset count to the total count for the game
        total_count.red += subset_count.red;
        total_count.green += subset_count.green;
        total_count.blue += subset_count.blue;
        
        // Debugging output to track cumulative totals across all subsets
        printf("Subset parsed: Red = %d, Green = %d, Blue = %d\n", subset_count.red, subset_count.green, subset_count.blue);
        printf("Total so far: Red = %d, Green = %d, Blue = %d\n", total_count.red, total_count.green, total_count.blue);
        
        // Check if cumulative totals exceed any limits
        if (total_count.red > RED_LIMIT || total_count.green > GREEN_LIMIT || total_count.blue > BLUE_LIMIT) {
            printf("Game invalid due to exceeding cumulative color limit.\n");
            return 0;  // Game is invalid, exit early
        }
        
        subset = strtok(NULL, ";");
    }
    
    return 1;  // Game is valid if no limits were exceeded
}


int main() {
    FILE *file = fopen("inputtxt2.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    char line[MAX_LINE_LENGTH];
    int total_sum = 0;

    while (fgets(line, sizeof(line), file)) {
        int game_id;
        sscanf(line, "Game %d:", &game_id);

        if (is_game_possible(line)) {
            total_sum += game_id;
        }
    }

    fclose(file);

    printf("The sum of possible game IDs is: %d\n", total_sum);

    return 0;
}
