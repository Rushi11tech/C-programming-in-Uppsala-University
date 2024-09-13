#include <stdio.h>
#include <ctype.h>

int extract_calibration_value(const char *line) {
    int first_digit = -1, last_digit = -1;
    
    // Find the first digit
    for (int i = 0; line[i] != '\0'; i++) {
        if (isdigit(line[i])) {
            first_digit = line[i] - '0';
            break;
        }
    }

    // Find the last digit
    for (int i = 0; line[i] != '\0'; i++) {
        if (isdigit(line[i])) {
            last_digit = line[i] - '0';
        }
    }

    if (first_digit == -1 || last_digit == -1) {
        return 0;  // No digits found
    }

    return first_digit * 10 + last_digit;  // Combine to form a two-digit number
}

int main() {
    FILE *file = fopen("input1.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }

    char line[100];  // Buffer for each line
    int total = 0;   // Sum of calibration values

    // Read each line from the file
    while (fgets(line, sizeof(line), file)) {
        int value = extract_calibration_value(line);
        total += value;
    }

    fclose(file);

    printf("Total calibration value: %d\n", total);

    return 0;
}
