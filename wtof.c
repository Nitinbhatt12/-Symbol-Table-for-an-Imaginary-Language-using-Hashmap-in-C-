#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashmap.h"

// Function to check if the string can be converted to an integer
int isInteger(char *str) {
    char *endptr;
    strtol(str, &endptr, 10);
    return *endptr == '\0';  // If the whole string was converted to an integer
}

// Function to check if the string can be converted to a float
int isFloat(char *str) {
    char *endptr;
    strtof(str, &endptr);
    return *endptr == '\0';  // If the whole string was converted to a float
}

// Function to check if the string is a valid string (non-numeric)
int isString(char *str) {
    return !isInteger(str) && !isFloat(str);
}

int main() {
    FILE* file = fopen("program.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[100];
    Hashtable* current_scope = NULL;  // Current scope

    while (fgets(line, sizeof(line), file)) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "begin") == 0) {
            // Create a new scope and link it to the current scope
            current_scope = make(current_scope);
            printf("New scope created\n");
        } else if (strcmp(line, "end") == 0) {
            // End the current scope and revert to the parent scope
            if (current_scope == NULL) {
                fprintf(stderr, "No active scope to end\n");
                return 1;
            }
            Hashtable* parent_scope = current_scope->parent;
            end(current_scope);
            current_scope = parent_scope;
            printf("Scope ended\n");
        } else if (strstr(line, "assign") == line) {
            // Process assignment in the current scope
            if (current_scope == NULL) {
                fprintf(stderr, "No active scope for assignment\n");
                return 1;
            }
            char key[100];
            char value_str[100];
            union Data value;
            enum DataType type;

            sscanf(line, "assign %s %s", key, value_str);

            if (isInteger(value_str)) {
                value.i = atoi(value_str);
                type = INT;
            } else if (isFloat(value_str)) {
                value.f = atof(value_str);
                type = FLOAT;
            } else if (isString(value_str)) {
                strcpy(value.str, value_str);
                type = STRING;
            } else {
                fprintf(stderr, "Unknown type for value: %s\n", value_str);
                continue;
            }

            insert(current_scope, key, value, type);
            printf("Assigned %s = %s\n", key, value_str);
        } else if (strstr(line, "print") == line) {
            // Process print command in the current scope
            if (current_scope == NULL) {
                fprintf(stderr, "No active scope for print\n");
                return 1;
            }
            char key[100];
            sscanf(line, "print %s", key);
            display(current_scope, key);
        }
    }

    fclose(file);
    return 0;
}