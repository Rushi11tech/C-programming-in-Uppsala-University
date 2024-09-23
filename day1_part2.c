#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1000

const char* number_words[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const int num_number_words = 10;

int find_digit(const char* str, int* index, int forward) {
    int i = *index;
    int len = strlen(str);
    
    while (i >= 0 && i < len) {
        if (isdigit(str[i])) {
            *index = i;
            return str[i] - '0';
        }
        
        for (int j = 0; j < num_number_words; j++) {
            if (forward) {
                if (strncmp(&str[i], number_words[j], strlen(number_words[j])) == 0) {
                    *index = i;
                    return j;
                }
            } else {
                if (i >= strlen(number_words[j]) - 1 &&
                    strncmp(&str[i - strlen(number_words[j]) + 1], number_words[j], strlen(number_words[j])) == 0) {
                    *index = i;
                    return j;
                }
            }
        }
        
        i += forward ? 1 : -1;
    }
    
    return -1;  // No digit found
}

int get_calibration_value(const char* line) {
    int first_index = 0;
    int last_index = strlen(line) - 1;
    
    int first_digit = find_digit(line, &first_index, 1);
    int last_digit = find_digit(line, &last_index, 0);
    
    if (first_digit == -1 || last_digit == -1) {
        return 0;  // Invalid line
    }
    
    return first_digit * 10 + last_digit;
}

int main() {
    char line[MAX_LINE_LENGTH];
    int sum = 0;

    while (fgets(line, sizeof(line), stdin)) {
        // Remove newline character if present
        line[strcspn(line, "\n")] = 0;
        
        int value = get_calibration_value(line);
        sum += value;
    }

    printf("Sum of all calibration values: %d\n", sum);
    return 0;
}