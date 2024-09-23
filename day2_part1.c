#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1000
#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

int is_game_possible(char *game) {
    char *set = strtok(NULL, ";");
    while (set != NULL) {
        char *cube = strtok(set, ",");
        while (cube != NULL) {
            int count = 0;
            char color[10] = {0};
            sscanf(cube, " %d %s", &count, color);
            
            if ((strcmp(color, "red") == 0 && count > MAX_RED) ||
                (strcmp(color, "green") == 0 && count > MAX_GREEN) ||
                (strcmp(color, "blue") == 0 && count > MAX_BLUE)) {
                return 0;
            }
            
            cube = strtok(NULL, ",");
        }
        set = strtok(NULL, ";");
    }
    return 1;
}

int main() {
    FILE *file = fopen("2input.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int sum = 0;

    while (fgets(line, sizeof(line), file)) {
        char *game = strtok(line, ":");
        int game_id = atoi(game + 5);  // Skip "Game " prefix
        
        // Process the first set
        char *first_set = strtok(NULL, ";");
        if (first_set != NULL) {
            char *cube = strtok(first_set, ",");
            while (cube != NULL) {
                int count = 0;
                char color[10] = {0};
                sscanf(cube, " %d %s", &count, color);
                
                if ((strcmp(color, "red") == 0 && count > MAX_RED) ||
                    (strcmp(color, "green") == 0 && count > MAX_GREEN) ||
                    (strcmp(color, "blue") == 0 && count > MAX_BLUE)) {
                    game_id = 0;  // Mark game as impossible
                    break;
                }
                
                cube = strtok(NULL, ",");
            }
        }

        if (game_id != 0 && is_game_possible(NULL)) {
            sum += game_id;
        }
    }

    fclose(file);
    printf("The sum of the IDs of possible games is: %d\n", sum);

    return 0;
}