#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char get_numeric_digit(char *str) {
    if (strstr(str, "one")) return '1';
    if (strstr(str, "two")) return '2';
    if (strstr(str, "three")) return '3';
    if (strstr(str, "four")) return '4';
    if (strstr(str, "five")) return '5';
    if (strstr(str, "six")) return '6';
    if (strstr(str, "seven")) return '7';
    if (strstr(str, "eight")) return '8';
    if (strstr(str, "nine")) return '9';
    return '0'; 
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Unable to open file");
        return 1;
    }

    char line[256];
    int total_sum = 0;

    while (fgets(line, sizeof(line), file)) {
        char first_digit = '0', last_digit = '0';
        int length = strlen(line);
        
        for (int i = 0; i < length; i++) {
            if (isdigit(line[i])) {
                if (first_digit == '0') first_digit = line[i];
                last_digit = line[i];
            } else if (line[i] == 'o' && line[i+1] == 'n' && line[i+2] == 'e') {
                if (first_digit == '0') first_digit = '1';
                last_digit = '1';
                i += 2; // Skip past "one"
            } else if (line[i] == 't' && line[i+1] == 'w' && line[i+2] == 'o') {
                if (first_digit == '0') first_digit = '2';
                last_digit = '2';
                i += 2; // Skip past "two"
            } else if (line[i] == 't' && line[i+1] == 'h' && line[i+2] == 'r' && line[i+3] == 'e' && line[i+4] == 'e') {
                if (first_digit == '0') first_digit = '3';
                last_digit = '3';
                i += 4; // Skip past "three"
            } else if (line[i] == 'f' && line[i+1] == 'o' && line[i+2] == 'u' && line[i+3] == 'r') {
                if (first_digit == '0') first_digit = '4';
                last_digit = '4';
                i += 3; // Skip past "four"
            } else if (line[i] == 'f' && line[i+1] == 'i' && line[i+2] == 'v' && line[i+3] == 'e') {
                if (first_digit == '0') first_digit = '5';
                last_digit = '5';
                i += 3; // Skip past "five"
            } else if (line[i] == 's' && line[i+1] == 'i' && line[i+2] == 'x') {
                if (first_digit == '0') first_digit = '6';
                last_digit = '6';
                i += 2; // Skip past "six"
            } else if (line[i] == 's' && line[i+1] == 'e' && line[i+2] == 'v' && line[i+3] == 'e' && line[i+4] == 'n') {
                if (first_digit == '0') first_digit = '7';
                last_digit = '7';
                i += 4; // Skip past "seven"
            } else if (line[i] == 'e' && line[i+1] == 'i' && line[i+2] == 'g' && line[i+3] == 'h' && line[i+4] == 't') {
                if (first_digit == '0') first_digit = '8';
                last_digit = '8';
                i += 4; // Skip past "eight"
            } else if (line[i] == 'n' && line[i+1] == 'i' && line[i+2] == 'n' && line[i+3] == 'e') {
                if (first_digit == '0') first_digit = '9';
                last_digit = '9';
                i += 3; // Skip past "nine"
            }
        }

        if (first_digit != '0' && last_digit != '0') {
            int calibration_value = (first_digit - '0') * 10 + (last_digit - '0');
            total_sum += calibration_value;
        }
    }

    fclose(file);
    printf("Total sum of calibration values: %d\n", total_sum);

    return 0;
}
