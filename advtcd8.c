#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the node structure
typedef struct {
    char node[4];  // Current node name (e.g., "AAA")
    char left[4];  // Left node name
    char right[4]; // Right node name
} Node;

// Function to move to the next node based on instruction (L or R)
void move_to_next_node(char* current_node, char direction, Node nodes[], int node_count) {
    for (int i = 0; i < node_count; i++) {
        if (strcmp(nodes[i].node, current_node) == 0) {
            // If instruction is 'L', move to left node, otherwise to right node
            strcpy(current_node, direction == 'L' ? nodes[i].left : nodes[i].right);
            break;
        }
    }
}

int main() {
    FILE *file;
    char filename[100];      // File name variable
    char instructions[100];  // Stores the left/right instructions
    int node_count = 0;      // Number of nodes in the file
    Node nodes[100];         // Array to hold nodes (assuming a max of 100 nodes)

    // Ask user for the input file name
    printf("Enter the name of the input file: ");
    scanf("%s", filename);   // Take the file name from user input

    // Open the file using the filename entered by the user
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    // Read the instructions first (assumed to be on the first line)
    fscanf(file, "%s", instructions);

    // Read the node connections from the file (assumed to be in format: AAA = (BBB, CCC))
    while (fscanf(file, "%s = (%[^,], %[^)])", nodes[node_count].node, nodes[node_count].left, nodes[node_count].right) == 3) {
        node_count++;
    }

    // Close the file after reading
    fclose(file);

    // Start at node AAA
    char current_node[4] = "AAA";
    int step_count = 0;
    int instruction_len = strlen(instructions);

    // Loop until we reach ZZZ
    while (strcmp(current_node, "ZZZ") != 0) {
        char direction = instructions[step_count % instruction_len];
        move_to_next_node(current_node, direction, nodes, node_count);
        step_count++;
    }

    printf("Steps required to reach ZZZ: %d\n", step_count);

    return 0;
}
