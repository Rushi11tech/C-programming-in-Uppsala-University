#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_LINE_LENGTH 1000
#define NUM_PATTERNS 20

const char* patterns[] = {
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

int pattern_to_digit(const char* pattern) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(pattern, patterns[i]) == 0 || strcmp(pattern, patterns[i + 10]) == 0) {
            return i;
        }
    }
    return -1;  
}

int get_calibration_value(const char* line) {
    regex_t regex;
    regmatch_t matches[1];
    char pattern[100];
    int first_digit = -1, last_digit = -1;

    strcpy(pattern, "");
    for (int i = 0; i < NUM_PATTERNS; i++) {
        if (i > 0) strcat(pattern, "|");
        strcat(pattern, patterns[i]);
    }

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Find first digit
    if (regexec(&regex, line, 1, matches, 0) == 0) {
        char match[20];
        int len = matches[0].rm_eo - matches[0].rm_so;
        strncpy(match, line + matches[0].rm_so, len);
        match[len] = '\0';
        first_digit = pattern_to_digit(match);
    }

    // Find last digit
    int start = strlen(line) - 1;
    while (start >= 0) {
        if (regexec(&regex, line + start, 1, matches, 0) == 0) {
            char match[20];
            int len = matches[0].rm_eo - matches[0].rm_so;
            strncpy(match, line + start + matches[0].rm_so, len);
            match[len] = '\0';
            last_digit = pattern_to_digit(match);
            break;
        }
        start--;
    }

    regfree(&regex);

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