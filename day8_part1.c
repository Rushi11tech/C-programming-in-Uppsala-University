#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NODES 1000
#define NODE_LENGTH 3
#define MAX_INSTRUCTIONS 1000

typedef struct {
    char name[NODE_LENGTH + 1];
    char left[NODE_LENGTH + 1];
    char right[NODE_LENGTH + 1];
} Node;

Node nodes[MAX_NODES];
int node_count = 0;
char instructions[MAX_INSTRUCTIONS];

int find_node(const char* name) {
    for (int i = 0; i < node_count; i++) {
        if (strcmp(nodes[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void add_node(const char* name, const char* left, const char* right) {
    if (node_count >= MAX_NODES) {
        fprintf(stderr, "Too many nodes\n");
        exit(1);
    }
    strcpy(nodes[node_count].name, name);
    strcpy(nodes[node_count].left, left);
    strcpy(nodes[node_count].right, right);
    node_count++;
}

int main() {
    char line[100];
    int instruction_count = 0;

    // Read instructions
    if (fgets(instructions, sizeof(instructions), stdin) == NULL) {
        fprintf(stderr, "Failed to read instructions\n");
        return 1;
    }
    instruction_count = strlen(instructions) - 1;  // Remove newline
    
    // Skip empty line
    fgets(line, sizeof(line), stdin);

    // Read nodes
    while (fgets(line, sizeof(line), stdin) != NULL) {
        char name[4], left[4], right[4];
        if (sscanf(line, "%3s = (%3s, %3s)", name, left, right) == 3) {
            add_node(name, left, right);
        }
    }

    // Navigate the network
    int current_node = find_node("AAA");
    int steps = 0;
    int instruction_index = 0;

    while (strcmp(nodes[current_node].name, "ZZZ") != 0) {
        if (instructions[instruction_index] == 'L') {
            current_node = find_node(nodes[current_node].left);
        } else {
            current_node = find_node(nodes[current_node].right);
        }

        steps++;
        instruction_index = (instruction_index + 1) % instruction_count;

        if (current_node == -1) {
            fprintf(stderr, "Invalid node encountered\n");
            return 1;
        }
    }

    printf("Steps required to reach ZZZ: %d\n", steps);
    return 0;
}